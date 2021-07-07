/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_WDT_H__
#define __AT91_WDT_H__

/**** Register offset in AT91S_WDTC structure ***/
#define WDTC_CR		0x00	/* Watchdog Control Register */
#define WDTC_MR		0x04	/* Watchdog Mode Register */
#define WDTC_SR		0x08	/* Watchdog Status Register */

/*-------- WDTC_CR : (WDTC Offset: 0x0) Periodic Interval Image Register --------*/
#define AT91C_WDTC_WDRSTT	(0x1UL << 0)
#define AT91C_WDTC_KEY		(0xA5 << 24)

/*-------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register --------*/
#define AT91C_WDTC_WDV		(0xFFFUL << 0)
#define AT91C_WDTC_WDFIEN	(0x1UL << 12)
#define AT91C_WDTC_WDRSTEN	(0x1UL << 13)
#define AT91C_WDTC_WDRPROC	(0x1UL << 14)
#define AT91C_WDTC_WDDIS	(0x1UL << 15)
#define AT91C_WDTC_WDD		(0xFFFUL << 16)
#define AT91C_WDTC_WDDBGHLT	(0x1UL << 28)
#define AT91C_WDTC_WDIDLEHLT	(0x1UL << 29)

/*-------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------*/
#define AT91C_WDTC_WDUNF	(0x1UL << 0)
#define AT91C_WDTC_WDERR	(0x1UL << 1)

#endif /* #ifndef __AT91_WDT_H__ */
