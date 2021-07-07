/*
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __PMC_COMMON_H__
#define __PMC_COMMON_H__

#include "hardware.h"

static inline void write_pmc(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_PMC);
}

static inline unsigned int read_pmc(unsigned int offset)
{
	return readl(offset + AT91C_BASE_PMC);
}

#endif
