// Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "arch/at91_wdt.h"
#include "debug.h"

static inline void wdt_write(unsigned int offset, unsigned int value)
{
	writel(value, (AT91C_BASE_WDT + offset));
}

static inline int wdt_read(unsigned int offset)
{
	return(readl(AT91C_BASE_WDT + offset));
}

#ifdef CONFIG_DISABLE_WATCHDOG
void at91_disable_wdt(void)
{
	unsigned int reg;

	reg = wdt_read(WDTC_MR);
	reg |= AT91C_WDTC_WDDIS;
	wdt_write(WDTC_MR, reg);
}
#else
void at91_disable_wdt(void) {}
#endif

#if defined(CONFIG_ENTER_NWD)
unsigned int at91_wdt_set_counter(unsigned int count)
{
	unsigned int reg;

	reg = wdt_read(WDTC_MR);
	if (reg & AT91C_WDTC_WDDIS) {
		dbg_info("at91_wdt: watchdog is disabled\n");
		return -1;
	}

	reg = AT91C_WDTC_WDRSTEN
		| AT91C_WDTC_WDDBGHLT
		| AT91C_WDTC_WDD
		| (count & AT91C_WDTC_WDV);
	wdt_write(WDTC_MR, reg);

	return 0;
}

unsigned int at91_wdt_reload_counter(void)
{
	wdt_write(WDTC_CR, (AT91C_WDTC_WDRSTT | AT91C_WDTC_KEY));

	return 0;
}
#endif
