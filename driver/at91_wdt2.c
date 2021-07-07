// Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "arch/at91_wdt2.h"
#include "debug.h"

static inline void wdt_write(unsigned int offset, unsigned int value)
{
	writel(value, (AT91C_BASE_WDT + offset));
}

static inline int wdt_read(unsigned int offset)
{
	return(readl(AT91C_BASE_WDT + offset));
}

#ifdef CONFIG_WDTS
static inline void wdts_write(unsigned int offset, unsigned int value)
{
	writel(value, (AT91C_BASE_WDTS + offset));
}

static inline int wdts_read(unsigned int offset)
{
	return(readl(AT91C_BASE_WDTS + offset));
}
#endif

#ifdef CONFIG_DISABLE_WATCHDOG
void at91_disable_wdt(void)
{
	unsigned int reg;

	reg = wdt_read(WDTC_MR);
	reg |= AT91C_WDTC_WDDIS;
	wdt_write(WDTC_MR, reg);
}

#ifdef CONFIG_WDTS
void at91_disable_wdts(void)
{
	unsigned int reg;

	reg = wdts_read(WDTC_MR);
	reg |= AT91C_WDTC_WDDIS;
	wdts_write(WDTC_MR, reg);
}
#endif
#else
void at91_disable_wdt(void) {}
void at91_disable_wdts(void) {}
#endif
