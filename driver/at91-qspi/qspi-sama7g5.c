// Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "div.h"
#include "string.h"
#include "arch/at91-qspi/qspi.h"
#include "spi_flash/spi_nor.h"
#include "debug.h"
#include "pmc.h"
#include "timer.h"

#include "qspi-common.h"

#define QSPI_TIMEOUT			1000000 /* us */
#define QSPI_SYNC_TIMEOUT		300000  /* us */
#define QSPI_DLLCFG_THRESHOLD_FREQ	90000000U

/**
 * struct qspi_pcal - Pad Calibration Clock Division
 * @pclk_rate: peripheral clock rate.
 * @pclkdiv: calibration clock division. The clock applied to the calibration
 *	     cell is divided by pclkdiv + 1.
 */
struct qspi_pcal {
	u32 pclk_rate;
	u8 pclk_div;
};

#ifdef CONFIG_AT91_QSPI_OCTAL
#define QSPI_PCAL_ARRAY_SIZE     8
static const struct qspi_pcal pcal[QSPI_PCAL_ARRAY_SIZE] = {
	{25000000, 0},
	{50000000, 1},
	{75000000, 2},
	{100000000, 3},
	{125000000, 4},
	{150000000, 5},
	{175000000, 6},
	{200000000, 7},
};
#endif

struct qspi_mode {
	u8 cmd_buswidth;
	u8 addr_buswidth;
	u8 data_buswidth;
	u32 config;
};

static const struct qspi_mode qspi_modes[] = {
	{ 1, 1, 1, QSPI_IFR_WIDTH_SINGLE_BIT_SPI },
	{ 1, 1, 2, QSPI_IFR_WIDTH_DUAL_OUTPUT },
	{ 1, 1, 4, QSPI_IFR_WIDTH_QUAD_OUTPUT },
	{ 1, 2, 2, QSPI_IFR_WIDTH_DUAL_IO },
	{ 1, 4, 4, QSPI_IFR_WIDTH_QUAD_IO },
	{ 2, 2, 2, QSPI_IFR_WIDTH_DUAL_CMD },
	{ 4, 4, 4, QSPI_IFR_WIDTH_QUAD_CMD },
	{ 1, 1, 8, QSPI_IFR_WIDTH_OCT_OUTPUT },
	{ 1, 8, 8, QSPI_IFR_WIDTH_OCT_IO },
	{ 8, 8, 8, QSPI_IFR_WIDTH_OCT_CMD },
};

static inline bool qspi_is_compatible(const struct spi_flash_command *cmd,
				      const struct qspi_mode *mode)
{
	if (mode->cmd_buswidth != spi_flash_protocol_get_inst_nbits(cmd->proto))
		return false;

	if (mode->addr_buswidth !=
	    spi_flash_protocol_get_addr_nbits(cmd->proto))
		return false;

	if (mode->data_buswidth !=
	    spi_flash_protocol_get_data_nbits(cmd->proto))
		return false;

	return true;
}

static int qspi_find_mode(const struct spi_flash_command *cmd)
{
	u32 i;

	for (i = 0; i < ARRAY_SIZE(qspi_modes); i++)
		if (qspi_is_compatible(cmd, &qspi_modes[i]))
			return i;
	return -1;
}

static int qspi_reg_sync(struct qspi_priv *aq)
{
	u32 val;

	return qspi_readl_poll_timeout(aq->reg_base + QSPI_SR, val,
				       !(val & QSPI_SR_SYNCBSY),
				       QSPI_SYNC_TIMEOUT);
}

static int qspi_update_config(struct qspi_priv *aq)
{
	int ret;

	ret = qspi_reg_sync(aq);
	if (ret)
		return ret;
	qspi_writel(QSPI_CR_UPDCFG, aq, QSPI_CR);
	return qspi_reg_sync(aq);
}

static int qspi_set_mode_bits(const struct spi_flash_command *cmd,
			      u32 *icr, u32 *ifr)
{
	unsigned int mode_cycle_bits, mode_bits;

	*icr |= QSPI_ICR_OPT(cmd->mode);
	*ifr |= QSPI_IFR_OPTEN;

	switch (*ifr & QSPI_IFR_WIDTH) {
	case QSPI_IFR_WIDTH_SINGLE_BIT_SPI:
	case QSPI_IFR_WIDTH_DUAL_OUTPUT:
	case QSPI_IFR_WIDTH_QUAD_OUTPUT:
	case QSPI_IFR_WIDTH_OCT_OUTPUT:
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
	case QSPI_IFR_WIDTH_OCT_IO:
	case QSPI_IFR_WIDTH_OCT_CMD:
		mode_cycle_bits = 8;
	default:
		return -1;
	}

	mode_bits = cmd->num_mode_cycles * mode_cycle_bits;
	switch (mode_bits) {
	case 1:
		*ifr |= QSPI_IFR_OPTL_1BIT;
		break;
	case 2:
		*ifr |= QSPI_IFR_OPTL_2BIT;
		break;
	case 4:
		*ifr |= QSPI_IFR_OPTL_4BIT;
		break;
	case 8:
		*ifr |= QSPI_IFR_OPTL_8BIT;
		break;
	default:
		return -1;
	}

	return 0;
}

static int qspi_set_cfg(struct qspi_priv *aq,
			const struct spi_flash_command *cmd, u32 *offset)
{
	u32 iar, icr, ifr;
	int mode, ret;

	iar = 0;
	icr = QSPI_ICR_INST(cmd->inst);
	ifr = QSPI_IFR_INSTEN;

	mode = qspi_find_mode(cmd);
	if (mode < 0)
		return mode;
	ifr |= qspi_modes[mode].config;

	if (cmd->num_mode_cycles) {
		ret = qspi_set_mode_bits(cmd, &icr, &ifr);
		if (ret)
			return ret;
	}

	/* Set the number of dummy cycles. */
	if (cmd->num_wait_states)
		ifr |= QSPI_IFR_NBDUM_(cmd->num_wait_states);

	if (cmd->addr_len) {
		ifr |= QSPI_IFR_ADDRL(cmd->addr_len - 1) | QSPI_IFR_ADDREN;
		iar = QSPI_IAR_ADDR(cmd->addr);
	}

	/* offset of the data access in the QSPI memory space */
	*offset = iar;

	/* Set data enable */
	if (cmd->data_len) {
		ifr |= QSPI_IFR_DATAEN;
		if (cmd->addr_len)
			ifr |= QSPI_IFR_TFRTYPE_MEM;
	}

	/*
	 * If the QSPI controller is set in regular SPI mode, set it in
	 * Serial Memory Mode (SMM).
	 */
	if (aq->mr != QSPI_MR_SMM) {
		qspi_writel(QSPI_MR_SMM, aq, QSPI_MR);
		ret = qspi_update_config(aq);
		if (ret)
			return ret;
		aq->mr = QSPI_MR_SMM;
	}

	/* Clear pending interrupts */
	(void)qspi_readl(aq, QSPI_ISR);

	/* Set QSPI Instruction Frame registers */
	if (cmd->addr_len && !cmd->data_len)
		qspi_writel(iar, aq, QSPI_IAR);

	if ((cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ ||
	    (cmd->flags & SFLASH_TYPE_MASK) == SFLASH_TYPE_READ_REG) {
		qspi_writel(icr, aq, QSPI_RICR);
	} else {
		qspi_writel(icr, aq, QSPI_WICR);
		if (cmd->data_len)
			qspi_writel(QSPI_WRACNT_NBWRA(cmd->data_len),
				    aq, QSPI_WRACNT);
	}

	qspi_writel(ifr, aq, QSPI_IFR);

	return qspi_update_config(aq);
}

static int qspi_transfer(struct qspi_priv *aq,
			 const struct spi_flash_command *cmd, u32 offset)
{
	int err;
	u32 val;

	if (!cmd->data_len) {
		/* Start the transfer. */
		err = qspi_reg_sync(aq);
		if (err)
			return err;
		qspi_writel(QSPI_CR_STTFR, aq, QSPI_CR);

		return qspi_readl_poll_timeout(aq->reg_base + QSPI_ISR, val,
					       val & QSPI_ISR_CSRA,
					       QSPI_TIMEOUT);
	}

	/* Send/Receive data. */
	if (cmd->rx_data) {
		memcpy(cmd->rx_data, aq->mem + offset, cmd->data_len);

		if (cmd->addr_len) {
			err = qspi_readl_poll_timeout(aq->reg_base + QSPI_SR,
						      val,
						      !(val & QSPI_SR_RBUSY),
						      QSPI_SYNC_TIMEOUT);
			if (err)
				return err;
		}
	} else if (cmd->tx_data) {
		memcpy(aq->mem + offset, cmd->tx_data, cmd->data_len);

		err = qspi_readl_poll_timeout(aq->reg_base + QSPI_ISR, val,
					      val & QSPI_ISR_LWRA,
					      QSPI_TIMEOUT);
		if (err)
			return err;
	} else {
		/* Stop here for continuous read */
		return 0;
	}

	/* Release the chip-select. */
	err = qspi_reg_sync(aq);
	if (err)
		return err;
	qspi_writel(QSPI_CR_LASTXFER, aq, QSPI_CR);

	return qspi_readl_poll_timeout(aq->reg_base + QSPI_ISR, val,
				       val & QSPI_ISR_CSRA,
				       QSPI_TIMEOUT);
}

static int qspi_exec(void *priv, const struct spi_flash_command *cmd)
{
	struct qspi_priv *aq = priv;
	u32 offset;
	int err;

	dbg_very_loud("at91-qspi: cmd->inst = %x\n", cmd->inst);

	if (cmd->addr + cmd->data_len > aq->mmap_size) {
		dbg_info("QSPI: Address exceeds the MMIO window size\n");
		return -1;
	}

	if (cmd->addr_len > 4)
		return -1;

	err = qspi_set_cfg(aq, cmd, &offset);
	if (err)
		return err;

	return qspi_transfer(aq, cmd, offset);
}

#ifdef CONFIG_AT91_QSPI_OCTAL
static int qspi_set_pad_calibration(struct qspi_priv *aq, u32 hz)
{
	u32 status, val;
	int i, ret;
	u8 pclk_div = 0;

	for (i = 0; i < QSPI_PCAL_ARRAY_SIZE; i++) {
		if (aq->pclk_rate <= pcal[i].pclk_rate) {
			pclk_div = pcal[i].pclk_div;
			break;
		}
	}

	/*
	 * Use the biggest divider in case the peripheral clock exceeds
	 * 200MHZ.
	 */
	if (aq->pclk_rate > pcal[QSPI_PCAL_ARRAY_SIZE - 1].pclk_rate)
		pclk_div = pcal[QSPI_PCAL_ARRAY_SIZE - 1].pclk_div;

	/* Disable QSPI while configuring the pad calibration. */
	status = qspi_readl(aq, QSPI_SR);
	if (status & QSPI_SR_QSPIENS) {
		ret = qspi_reg_sync(aq);
		if (ret)
			return ret;
		qspi_writel(QSPI_CR_QSPIDIS, aq, QSPI_CR);
	}

	/*
	 * The analog circuitry is not shut down at the end of the calibration
	 * and the start-up time is only required for the first calibration
	 * sequence, thus increasing performance. Set the delay between the Pad
	 * calibration analog circuitry and the calibration request to 2us.
	 */
	qspi_writel(QSPI_PCALCFG_AAON |
		    QSPI_PCALCFG_CLKDIV(pclk_div) |
		    QSPI_PCALCFG_CALCNT(2 * (aq->pclk_rate / 1000000)),
		    aq, QSPI_PCALCFG);

	/* DLL On + start calibration. */
	qspi_writel(QSPI_CR_DLLON | QSPI_CR_STPCAL, aq, QSPI_CR);
	ret =  qspi_readl_poll_timeout(aq->reg_base + QSPI_SR, val,
				       (val & QSPI_SR_DLOCK) &&
				       !(val & QSPI_SR_CALBSY),
				       QSPI_TIMEOUT);

	/* Refresh analogic blocks every 1 ms.*/
	qspi_writel(QSPI_REFRESH_DELAY_COUNTER(hz / 1000), aq, QSPI_REFRESH);

	return ret;
}
#endif /* CONFIG_AT91_QSPI_OCTAL */

static int qspi_set_gclk(struct qspi_priv *aq, u32 hz)
{
	u32 status, val;
	unsigned int max_gclk_rate;
	int ret;

	/* Disable DLL before setting GCLK */
	status = qspi_readl(aq, QSPI_SR);
	if (status & QSPI_SR_DLOCK) {
		qspi_writel(QSPI_CR_DLLOFF, aq, QSPI_CR);
		ret = qspi_readl_poll_timeout(aq->reg_base + QSPI_SR, val,
					      !(val & QSPI_SR_DLOCK),
					      QSPI_TIMEOUT);
		if (ret)
			return ret;
	}

	if (hz > QSPI_DLLCFG_THRESHOLD_FREQ)
		qspi_writel(QSPI_DLLCFG_RANGE, aq, QSPI_DLLCFG);
	else
		qspi_writel(0, aq, QSPI_DLLCFG);

	pmc_enable_generic_clock(CONFIG_SYS_ID_QSPI, GCK_CSS_SYSPLL_CLK, 0);
	max_gclk_rate = pmc_get_generic_clock(CONFIG_SYS_ID_QSPI);
	pmc_enable_generic_clock(CONFIG_SYS_ID_QSPI, GCK_CSS_SYSPLL_CLK,
				 ((max_gclk_rate + hz - 1) / hz) - 1);
	dbg_very_loud("max_gclk_rate = %u, hz = %u, div = %u\n",
		      max_gclk_rate, hz, ((max_gclk_rate + hz - 1) / hz) - 1);

	return 0;
}

static int qspi_set_freq(void *priv, u32 hz)
{
	struct qspi_priv *aq = priv;
	u32 val;
	int ret;

	ret = qspi_set_gclk(aq, hz);
	if (ret)
		return ret;

#ifdef CONFIG_AT91_QSPI_OCTAL
	ret = qspi_set_pad_calibration(priv, hz);
	if (ret)
		return ret;
#else
	qspi_writel(QSPI_CR_DLLON, aq, QSPI_CR);
	ret =  qspi_readl_poll_timeout(aq->reg_base + QSPI_SR, val,
				       val & QSPI_SR_DLOCK,
				       QSPI_TIMEOUT);
#endif

	/* Set the QSPI controller by default in Serial Memory Mode */
	qspi_writel(QSPI_MR_SMM, aq, QSPI_MR);
	ret = qspi_update_config(aq);
	if (ret)
		return ret;
	aq->mr = QSPI_MR_SMM;

	/* Enable the QSPI controller. */
	ret = qspi_reg_sync(aq);
	if (ret)
		return ret;
	qspi_writel(QSPI_CR_QSPIEN, aq, QSPI_CR);
	ret = qspi_readl_poll_timeout(aq->reg_base + QSPI_SR, val,
				      val & QSPI_SR_QSPIENS,
				      QSPI_SYNC_TIMEOUT);
	if (ret)
		return ret;

#ifdef CONFIG_AT91_QSPI_OCTAL
	ret = qspi_readl_poll_timeout(aq->reg_base + QSPI_ISR, val,
				      val & QSPI_ISR_RFRHD, QSPI_TIMEOUT);
#endif

	qspi_writel(0xffff, aq, QSPI_TOUT);

	return ret;
}

static int qspi_set_mode(void *priv, u8 mode)
{
	struct qspi_priv *aq = priv;
	u32 reg, mask, val;

	reg = qspi_readl(aq, QSPI_SCR);

	mask = QSPI_SCR_CPHA | QSPI_SCR_CPOL;
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
		val = QSPI_SCR_CPOL | QSPI_SCR_CPHA;
		break;

	default:
		return -1;
	}

	if ((reg & mask) == val)
		return 0;

	reg = (reg & ~mask) | val;
	qspi_writel(reg, aq, QSPI_SCR);
	return qspi_update_config(aq);
}

static int qspi_init(void *priv)
{
	struct qspi_priv *aq = priv;
	int ret;

	at91_qspi_hw_init();

	pmc_enable_periph_clock(CONFIG_SYS_ID_QSPI, PMC_PERIPH_CLK_DIVIDER_NA);
	aq->pclk_rate = pmc_periph_clock_get_rate(CONFIG_SYS_ID_QSPI);

	ret = qspi_reg_sync(aq);
	if (ret)
		return ret;
	qspi_writel(QSPI_CR_SWRST, aq, QSPI_CR);

	return 0;
}

static int qspi_cleanup(void *priv)
{
	struct qspi_priv *aq = priv;
	int ret;

	ret = qspi_reg_sync(aq);
	if (ret)
		return ret;
	qspi_writel(QSPI_CR_QSPIDIS, aq, QSPI_CR);

	ret = qspi_reg_sync(aq);
	if (ret)
		return ret;
	qspi_writel(QSPI_CR_SWRST, aq, QSPI_CR);
	return 0;
}

const struct spi_ops qspi_ops = {
	.init		= qspi_init,
	.cleanup	= qspi_cleanup,
	.set_freq	= qspi_set_freq,
	.set_mode	= qspi_set_mode,
	.exec		= qspi_exec,
};
