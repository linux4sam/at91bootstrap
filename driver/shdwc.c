/* ----------------------------------------------------------------------------
 *         Microchip Microprocessor (MPU) Software Team
 * ----------------------------------------------------------------------------
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Microchip's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef CONFIG_SHDWC

#include "common.h"
#include "hardware.h"
#include "shdwc.h"

#define SHDWC_CR	(0x0)
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

void shdwc_disable_lpm(void)
{
	unsigned int val = shdwc_read(SHDWC_CR);

	val |= (SHDWC_CR_KEY | SHDWC_CR_LPMDIS);
	shdwc_write(SHDWC_CR, val);
}

#else

void shdwc_disable_lpm(void)
{
}

#endif
