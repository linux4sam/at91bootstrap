// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "div.h"
#include "string.h"
#include "arch/at91-qspi/qspi.h"
#include "spi_flash/spi_nor.h"
#include "debug.h"
#include "timer.h"

#include "qspi-common.h"

static int qspi_set_freq(void *priv, u32 clock)
{
	struct qspi_priv *qspi = priv;
	unsigned int scbr;
	unsigned int reg;

	if (clock == 0) {
		scbr = 0;
	} else {
		scbr = div(MASTER_CLOCK + clock - 1, clock);
		if (scbr >= 1)
			scbr--;
	}

	reg = qspi_readl(qspi, QSPI_SCR);
	reg = (reg & ~QSPI_SCR_SCBR) | QSPI_SCR_SCBR_(scbr);
	qspi_writel(reg, qspi, QSPI_SCR);

	return 0;
}

static int qspi_set_mode(void *priv, u8 mode)
{
	struct qspi_priv *qspi = priv;
	unsigned int reg, val, msk;

	reg = qspi_readl(qspi, QSPI_SCR);

	msk = (QSPI_SCR_CPHA | QSPI_SCR_CPOL);
	switch (mode) {
	case SPI_MODE0:
		val = 0;
		break;

	case SPI_MODE1:
		val = QSPI_SCR_CPHA;
		break;

	case SPI_MODE2:
		val = QSPI_SCR_CPOL;
		break;

	case SPI_MODE3:
		val = (QSPI_SCR_CPOL | QSPI_SCR_CPHA);
		break;

	default:
		return -1;
	}

	if ((reg & msk) != val) {
		reg = (reg & ~msk) | val;
		qspi_writel(reg, qspi, QSPI_SCR);
	}

	return 0;
}

static int qspi_init(void *priv)
{
	struct qspi_priv *qspi = priv;

	at91_qspi_hw_init();

	qspi_writel(QSPI_CR_QSPIDIS, qspi, QSPI_CR);
	qspi_writel(QSPI_CR_SWRST, qspi, QSPI_CR);

	qspi_writel(QSPI_MR_SMM, qspi, QSPI_MR);
	qspi_writel(0, qspi, QSPI_SCR);

	qspi_writel(QSPI_CR_QSPIEN, qspi, QSPI_CR);

	return 0;
}

static int qspi_cleanup(void *priv)
{
	struct qspi_priv *qspi = priv;

	qspi_writel(QSPI_CR_QSPIDIS, qspi, QSPI_CR);
	qspi_writel(QSPI_CR_SWRST, qspi, QSPI_CR);

	return 0;
}

static int qspi_set_ifr_width(const struct spi_flash_command *cmd,
			      unsigned int *ifr)
{
	*ifr = 0;

	switch (cmd->proto) {
	case SFLASH_PROTO_1_1_1:
		*ifr |= QSPI_IFR_WIDTH_SINGLE_BIT_SPI;
		break;

	case SFLASH_PROTO_1_1_2:
		*ifr |= QSPI_IFR_WIDTH_DUAL_OUTPUT;
		break;

	case SFLASH_PROTO_1_2_2:
		*ifr |= QSPI_IFR_WIDTH_DUAL_IO;
		break;

	case SFLASH_PROTO_2_2_2:
		*ifr |= QSPI_IFR_WIDTH_DUAL_CMD;
		break;

	case SFLASH_PROTO_1_1_4:
		*ifr |= QSPI_IFR_WIDTH_QUAD_OUTPUT;
		break;

	case SFLASH_PROTO_1_4_4:
		*ifr |= QSPI_IFR_WIDTH_QUAD_IO;
		break;

	case SFLASH_PROTO_4_4_4:
		*ifr |= QSPI_IFR_WIDTH_QUAD_CMD;
		break;
#ifdef QSPI_IFR_DDREN
	case SFLASH_PROTO_1_4D_4D:
		*ifr |= QSPI_IFR_WIDTH_QUAD_IO | QSPI_IFR_DDREN;
		break;
#endif
	default:
		return -1;
	}

	return 0;
}

static int qspi_exec(void *priv, const struct spi_flash_command *cmd)
{
	struct qspi_priv *qspi = priv;
	unsigned int iar, icr, ifr;
	unsigned int offset;
	unsigned int sr, imr;
	unsigned int timeout = 1000000;

	dbg_very_loud("at91-qspi: cmd->inst = %x\n", cmd->inst);

	if (cmd->addr + cmd->data_len > qspi->mmap_size) {
		dbg_info("QSPI: Address exceeds the MMIO window size\n");
		return -1;
	}

	iar = 0;
	icr = 0;
	ifr = 0;

	if (qspi_set_ifr_width(cmd, &ifr))
		return -1;

	/* Compute instruction parameters. */
	icr |= QSPI_ICR_INST(cmd->inst);
	ifr |= QSPI_IFR_INSTEN;

	/* Compute address parameters. */
	switch (cmd->addr_len) {
	case 4:
		ifr |= QSPI_IFR_ADDRL_32_BIT;
		//break; /* fall through the 24bit (3 byte) address case */
	case 3:
		iar = cmd->data_len ? 0 : cmd->addr;
		ifr |= QSPI_IFR_ADDREN;
		offset = cmd->addr;
		break;
	case 0:
		offset = 0;
		break;
	default:
		return -1;
	}

	/* Compute option parameters. */
	if (cmd->num_mode_cycles) {
		unsigned int mode_cycle_bits, mode_bits;

		icr |= QSPI_ICR_OPT(cmd->mode);
		ifr |= QSPI_IFR_OPTEN;

		switch (ifr & QSPI_IFR_WIDTH) {
		case QSPI_IFR_WIDTH_SINGLE_BIT_SPI:
		case QSPI_IFR_WIDTH_DUAL_OUTPUT:
		case QSPI_IFR_WIDTH_QUAD_OUTPUT:
			mode_cycle_bits = 1;
			break;
		case QSPI_IFR_WIDTH_DUAL_IO:
		case QSPI_IFR_WIDTH_DUAL_CMD:
			mode_cycle_bits = 2;
			break;
		case QSPI_IFR_WIDTH_QUAD_IO:
		case QSPI_IFR_WIDTH_QUAD_CMD:
			mode_cycle_bits = 4;
			break;
		default:
			return -1;
		}

		mode_bits = cmd->num_mode_cycles * mode_cycle_bits;
		switch (mode_bits) {
		case 1:
			ifr |= QSPI_IFR_OPTL_1BIT;
			break;

		case 2:
			ifr |= QSPI_IFR_OPTL_2BIT;
			break;

		case 4:
			ifr |= QSPI_IFR_OPTL_4BIT;
			break;

		case 8:
			ifr |= QSPI_IFR_OPTL_8BIT;
			break;

		default:
			return -1;
		}
	}

	/* Set the number of dummy cycles. */
	if (cmd->num_wait_states)
		ifr |= QSPI_IFR_NBDUM_(cmd->num_wait_states);

	/* Set data enable. */
	if (cmd->data_len) {
		ifr |= QSPI_IFR_DATAEN;

		if (cmd->addr_len)
			ifr |= QSPI_IFR_TFRTYPE_MEM;

		/* Special case for Continuous Read Mode. */
		if (!cmd->tx_data && !cmd->rx_data)
			ifr |= QSPI_IFR_CRM;
	}

	/* Clear pending interrupts. */
	(void)qspi_readl(qspi, QSPI_SR);

	/* Set QSPI Instruction Frame registers. */
	qspi_writel(iar, qspi, QSPI_IAR);
#if defined(CONFIG_SAM9X60)
	if ((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ ||
	    (cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ_REG)
		qspi_writel(icr, qspi, QSPI_RICR);
	else
		qspi_writel(icr, qspi, QSPI_WICR);
#else
	if (cmd->data_len &&
	    ((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE ||
	     (cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_WRITE_REG))
		ifr |= QSPI_IFR_TFRTYPE_WRITE;
	qspi_writel(icr, qspi, QSPI_ICR);
#endif
	qspi_writel(ifr, qspi, QSPI_IFR);

	/* Skip to the final steps if there is no data. */
	if (!cmd->data_len)
		goto no_data;

	/* Dummy read of QSPI_IFR to synchronize APB and AHB accesses. */
	(void)qspi_readl(qspi, QSPI_IFR);

	/* Stop here for Continuous Read. */
	if (cmd->tx_data)
		/* Write data. */
		qspi_memcpy(qspi->mem + offset, cmd->tx_data, cmd->data_len, false);
	else if (cmd->rx_data)
		/* Read data. */
		qspi_memcpy(cmd->rx_data, qspi->mem + offset, cmd->data_len, false);
	else
		/* Stop here for continuous read */
		return 0;

	/* Release the chip-select. */
	qspi_writel(QSPI_CR_LASTXFER, qspi, QSPI_CR);

no_data:
	/* Poll INSTruction End and Chip Select Rise flags. */
	imr = (QSPI_SR_INSTRE | QSPI_SR_CSR);
	sr = 0;
	do {
		udelay(1);
		sr |= qspi_readl(qspi, QSPI_SR) & imr;
	} while ((!!(--timeout)) && (sr != imr));

	if (!timeout)
		dbg_info("Timeout waiting Instruction End! sr = %08x\n", sr);

	return 0;
}

const struct spi_ops qspi_ops = {
	.init		= qspi_init,
	.cleanup	= qspi_cleanup,
	.set_freq	= qspi_set_freq,
	.set_mode	= qspi_set_mode,
	.exec		= qspi_exec,
};
