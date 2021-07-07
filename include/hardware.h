/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#ifdef CONFIG_SAM9X60
#include "arch/sam9x60.h"
#endif

#ifdef CONFIG_SAMA5D3X
#include "arch/sama5d3x.h"
#endif

#ifdef CONFIG_SAMA5D4
#include "arch/sama5d4.h"
#endif

#ifdef CONFIG_SAMA5D2
#include "arch/sama5d2.h"
#endif

#ifdef CONFIG_SAMA7G5
#include "arch/sama7g5.h"
#endif

/* I/O Function Macro */
#define writel(value, addr) \
	(*(volatile unsigned int *)(addr)) = (value)
#define readl(addr) \
	(*(volatile unsigned int *)(addr))

#define writew(value, addr) \
	 (*(volatile unsigned short *)(addr) = (value))
#define readw(addr) \
	(*(volatile unsigned short *)(addr))

#define writeb(value, addr) \
	 (*(volatile unsigned char *)(addr) = (value))
#define readb(addr) \
	(*(volatile unsigned char *)(addr))

#endif /* #ifndef __HARDWARE_H__ */
