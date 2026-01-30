// Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifdef CONFIG_SHDWC

#include "common.h"
#include "hardware.h"
#include "shdwc.h"

#define SHDWC_CR	(0x0)
#define SHDWC_SR	(0x8)
#define SHDWC_CR_SHDW	(1 << 0)
#define SHDWC_CR_LPMDIS	(1 << 22)
#define SHDWC_CR_KEY	(0xa5 << 24)

static inline void shdwc_write(unsigned int offset, unsigned int value)
{
	writel(value, AT91C_BASE_SHDWC + offset);
}

static inline unsigned int shdwc_read(unsigned int offset)
{
	return readl(AT91C_BASE_SHDWC + offset);
}

void shdwc_shutdown(void)
{
	unsigned int val = (SHDWC_CR_KEY | SHDWC_CR_SHDW);

#ifdef CONFIG_SAMA7D65
	shdwc_read(SHDWC_SR);
#endif
	shdwc_write(SHDWC_CR, val);
}

void shdwc_disable_lpm(void)
{
	unsigned int val = shdwc_read(SHDWC_CR);

	val |= (SHDWC_CR_KEY | SHDWC_CR_LPMDIS);
	shdwc_write(SHDWC_CR, val);
}

unsigned int shdwc_read_status(void)
{
	return shdwc_read(SHDWC_SR);
}

#else

void shdwc_disable_lpm(void)
{
}

unsigned int shdwc_read_status(void)
{
	return 0;
}

void shdwc_shutdown(void)
{
}
#endif
