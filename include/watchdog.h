/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

extern void at91_disable_wdt(void);
#ifdef CONFIG_WDTS
extern void at91_disable_wdts(void);
#endif

#if defined(CONFIG_ENTER_NWD)
extern unsigned int at91_wdt_set_counter(unsigned int count);
extern unsigned int at91_wdt_reload_counter(void);
#endif

#endif /* __WATCHDOG_H__ */
