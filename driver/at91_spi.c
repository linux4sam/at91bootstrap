// Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "hardware.h"
#include "spi.h"
#include "arch/at91_spi.h"
#include "arch/at91_pio.h"
#include "gpio.h"
#include "debug.h"
#include "div.h"
#include "board.h"
#include "pmc.h"

static inline unsigned int spi_readl(unsigned int reg)
{
	return readl(CONFIG_SYS_BASE_SPI + reg);
}

static inline void spi_writel(unsigned int reg, unsigned int value)
{
	writel(value, CONFIG_SYS_BASE_SPI + reg);
}

void at91_spi_cs_activate(void)
{
	pio_set_value(CONFIG_SYS_SPI_PCS, 0);
}

void at91_spi_cs_deactivate(void)
{
	pio_set_value(CONFIG_SYS_SPI_PCS, 1);
}

void at91_spi_enable(void)
{
	spi_writel(SPI_CR, AT91C_SPI_SPIEN);
}

void at91_spi_disable(void)
{
	spi_writel(SPI_CR, AT91C_SPI_SPIDIS);
}

int at91_spi_init(unsigned int pcs, unsigned int clock, unsigned int mode)
{
	unsigned int	ncs;
	unsigned int	scbr;
	unsigned int	reg;

	/* Reset SPI, sometimes the SPI may need twice reset */
	spi_writel(SPI_CR, AT91C_SPI_SWRST);
	spi_writel(SPI_CR, AT91C_SPI_SWRST);

	if (pcs == AT91C_SPI_PCS0_DATAFLASH) {
		ncs = 0;
	} else if (pcs == AT91C_SPI_PCS1_DATAFLASH) {
		ncs = 1;
	} else if (pcs == AT91C_SPI_PCS2_DATAFLASH) {
		ncs = 2;
	} else if (pcs == AT91C_SPI_PCS3_DATAFLASH) {
		ncs = 3;
	} else {
		dbg_info("SPI: Error pcs : %d\n", pcs);
		return -1;
	}

	reg = AT91C_SPI_MSTR
		| AT91C_SPI_MODFDIS
		| AT91C_SPI_PCS((~(1 << ncs) & 0xf));

	spi_writel(SPI_MR, reg);

	if (!clock)
		return -1;

	scbr = div(at91_get_ahb_clock(), clock);
	reg = AT91C_SPI_SCBR(scbr);
	reg |= AT91C_SPI_BITS_8;

	if (mode == SPI_MODE0) {
		reg |= AT91C_SPI_NCPHA;
	} else if (mode == SPI_MODE2) {
		reg |= (AT91C_SPI_NCPHA | AT91C_SPI_CPOL);
	} else if (mode == SPI_MODE3) {
		reg |= AT91C_SPI_CPOL;
	} else if (mode != SPI_MODE1) {
		dbg_info("SPI: Error mode : %d\n", mode);
		return -1;
	}

	spi_writel(SPI_CSR(ncs), reg);

	return 0;
}

void at91_spi_write_data(unsigned short data)
{
	while ((spi_readl(SPI_SR) & AT91C_SPI_TXEMPTY) == 0)
		;
	spi_writel(SPI_TDR, data);
	while ((spi_readl(SPI_SR) & AT91C_SPI_TDRE) == 0)
		;
}

unsigned int at91_spi_read_spi(void)
{
	while ((spi_readl(SPI_SR) & AT91C_SPI_RDRF) == 0)
		;
	return spi_readl(SPI_RDR) & 0xffff;
}

unsigned int at91_spi_read_sr(void)
{
	return spi_readl(SPI_SR);
}
