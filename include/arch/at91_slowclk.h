/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_SLOWCLK_H__
#define __AT91_SLOWCLK_H__

#define AT91C_SLCKSEL_RCEN	(0x1UL << 0)
#define AT91C_SLCKSEL_OSC32EN	(0x1UL << 1)
#define AT91C_SLCKSEL_OSC32BYP	(0x1UL << 2)

#if defined(CONFIG_SAM9X60) || defined(CONFIG_SAM9X7) || \
	defined(CONFIG_SAMA7G5) || defined(CONFIG_SAMA7D65)
#define AT91C_SLCKSEL_OSCSEL	(0x1UL << 24)
#else
#define AT91C_SLCKSEL_OSCSEL	(0x1UL << 3)
#endif

#endif /* #ifndef __AT91_SLOWCLK_H__ */
