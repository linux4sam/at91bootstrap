/*
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef _AT91_WDT2_H_
#define _AT91_WDT2_H_

#define WDTC_CR			0x00	/* Control Register */
#define WDTC_MR			0x04	/* Mode Register */
#define WDTC_VR			0x08	/* Value Register */

/*-------- WDTC_MR : (WDTC Offset: 0x4) Watchdog Mode Register --------*/
#define AT91C_WDTC_WDDIS	(0x1UL << 12)

#endif
