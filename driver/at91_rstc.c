// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifdef CONFIG_RSTC

#include "common.h"
#include "hardware.h"
#include "rstc.h"
#include "arch/at91_rstc.h"

static inline void rstc_write(unsigned int offset, unsigned int value)
{
	writel(value, AT91C_BASE_RSTC + offset);
}

static inline unsigned int rstc_read(unsigned int offset)
{
	return readl(AT91C_BASE_RSTC + offset);
}

/*
 * The external reset is asserted during a time of 2^(ERSTL+1) Slow Clock cycles
 * the external reset length is 15ms (1/32768 * (2 ^ 9).
 */
#define EXTERNAL_RESET_LENGTH	8

void rstc_external_reset(void)
{
	unsigned int timeout = 100000;

	/* Set the external reset length */
	rstc_write(RSTC_RMR, AT91C_RSTC_ERSTL(EXTERNAL_RESET_LENGTH)
					| AT91C_RSTC_KEY_UNLOCK);

	/* Assert the NRST pin */
	rstc_write(RSTC_RCR, (AT91C_RSTC_EXTRST | AT91C_RSTC_RCRKEY));

	/* Wait for the software reset completed */
	while(rstc_read(RSTC_RSR) & AT91C_RSTC_SRCMP);

	while (--timeout)
		;
}

void cpu_reset()
{
	rstc_write(RSTC_RCR, AT91C_RSTC_RCRKEY
		| AT91C_RSTC_PROCRST	/* Processor Reset */
		| AT91C_RSTC_PERRST	/* Peripheral Reset */
		| AT91C_RSTC_EXTRST);	/* External Reset (assert nRST pin) */
}

void rstc_ddr_rst_deassert(void)
{
	unsigned int grstr = rstc_read(RSTC_GRSTR);

	grstr |= AT91C_GRSTR_DDR_RST;
	rstc_write(RSTC_GRSTR, grstr);
}

void rstc_ddr_phy_rst_deassert(void)
{
	unsigned int grstr = rstc_read(RSTC_GRSTR);

	grstr |= AT91C_GRSTR_DDR_PHY_RST;
	rstc_write(RSTC_GRSTR, grstr);
}

void rstc_ddr_assert(void)
{
	unsigned int grstr = rstc_read(RSTC_GRSTR);

	grstr &= ~(AT91C_GRSTR_DDR_RST | AT91C_GRSTR_DDR_PHY_RST);
	rstc_write(RSTC_GRSTR, grstr);
}

#else
void rstc_external_reset(void)
{
}

void cpu_reset(void)
{
}
#endif
