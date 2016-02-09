/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "hardware.h"
#include "board.h"
#include "qspi.h"
#include "pmc.h"
#include "div.h"
#include "string.h"
#include "arch/at91_qspi.h"

#ifndef CONFIG_SYS_BASE_QSPI
#define CONFIG_SYS_BASE_QSPI		AT91C_BASE_QSPI0
#endif

#ifndef CONFIG_SYS_BASE_QSPI_MEM
#define	CONFIG_SYS_BASE_QSPI_MEM	AT91C_BASE_QSPI0_MEM
#endif

static unsigned int qspi_get_base(void)
{
	return CONFIG_SYS_BASE_QSPI;
}

static unsigned int qspi_readl(unsigned int reg)
{
	return readl(qspi_get_base() + reg);
}

static void qspi_writel(unsigned int reg, unsigned int value)
{
	writel(value, qspi_get_base() + reg);
}

static int qspi_clock_init(unsigned int clock, unsigned int mode)
{
	unsigned int scbr;
	unsigned int reg;

	if (clock == 0) {
		scbr = 0;
	} else {
		scbr = div(MASTER_CLOCK + clock - 1, clock);
		if (scbr >= 1)
			scbr--;
	}

	reg = QSPI_SCR_SCBR_(scbr);
	if (mode == SPI_MODE1)
		reg |= QSPI_SCR_CPHA;
	else if (mode == SPI_MODE2)
		reg |= QSPI_SCR_CPOL;
	else if (mode == SPI_MODE3)
		reg |= (QSPI_SCR_CPOL | QSPI_SCR_CPHA);

	qspi_writel(QSPI_SCR, reg);

	return 0;
}

int qspi_init(unsigned int clock, unsigned int mode)
{
	unsigned int config;

	qspi_writel(QSPI_CR, QSPI_CR_QSPIDIS);
	qspi_writel(QSPI_CR, QSPI_CR_SWRST);

	qspi_clock_init(clock, mode);

	config = QSPI_MR_SMM_MEMORY; 
	qspi_writel(QSPI_MR, config);

	qspi_writel(QSPI_CR, QSPI_CR_QSPIEN);

	return 0;
}

int qspi_send_command(const qspi_command_t *cmd)
{
	unsigned int iar, icr, ifr;
	unsigned int offset;
	unsigned int sr, imr;

	iar = 0;
	icr = 0;
	ifr = (QSPI_IFR_WIDTH_(cmd->protocol) |
	       QSPI_IFR_TFRTYPE_(cmd->transfer_type));

	/* Compute instruction parameters */
	if (cmd->enable.bits.instruction) {
		icr |= QSPI_ICR_INST_(cmd->instruction);
		ifr |= QSPI_IFR_INSTEN;
	}

	/* Compute address parameters. */
	switch (cmd->enable.bits.address) {
	case 4:
		ifr |= QSPI_IFR_ADDRL_32_BIT;
		//break; /* fall through the 24bit (3 byte) address case */
	case 3:
		iar = (cmd->enable.bits.data) ? 0 : cmd->address;
		ifr |= QSPI_IFR_ADDREN;
		offset = cmd->address;
		break;
	case 0:
		offset = 0;
		break;
	default:
		return -1;
	}

	/* Compute option parameters. */
	if (cmd->enable.bits.mode && cmd->num_mode_cycles) {
		unsigned int mode_cycle_bits, mode_bits;

		icr |= QSPI_ICR_OPT_(cmd->mode);
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
	if (cmd->enable.bits.dummy)
		ifr |= QSPI_IFR_NBDUM_(cmd->num_dummy_cycles);

	/* Set data enable. */
	if (cmd->enable.bits.data) {
		ifr |= QSPI_IFR_DATAEN;

		/* Special case for Continuous Read Mode. */
		if (!cmd->tx_buf && !cmd->rx_buf)
			ifr |= QSPI_IFR_CRM;
	}

	/* Clear pending interrupts. */
	(void)qspi_readl(QSPI_SR);

	/* Set QSPI Instruction Frame registers. */
	qspi_writel(QSPI_IAR, iar);
	qspi_writel(QSPI_ICR, icr);
	qspi_writel(QSPI_IFR, ifr);

	/* Skip to the final steps if there is no data. */
	if (!cmd->enable.bits.data)
		goto no_data;

	/* Dummy read of QSPI_IFR to synchronize APB and AHB accesses. */
	(void)qspi_readl(QSPI_IFR);

	/* Stop here for Continuous Read. */
	if (cmd->tx_buf)
		/* Write data. */
		memcpy(qspi_memory_base() + offset, cmd->tx_buf, cmd->buf_len);
	else if (cmd->rx_buf)
		/* Read data. */
		memcpy(cmd->rx_buf, qspi_memory_base() + offset, cmd->buf_len);
	else
		/* Stop here for continuous read */
		return 0;

	/* Release the chip-select. */
	qspi_writel(QSPI_CR, QSPI_CR_LASTXFER);

no_data:
	/* Poll INSTruction End and Chip Select Rise flags. */
	imr = (QSPI_SR_INSTRE | QSPI_SR_CSR);
	sr = 0;
	while (sr != (QSPI_SR_INSTRE | QSPI_SR_CSR))
		sr |= qspi_readl(QSPI_SR) & imr;

	return 0;
}

unsigned char *qspi_memory_base(void)
{
	return (unsigned char *)CONFIG_SYS_BASE_QSPI_MEM;
}
