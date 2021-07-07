// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "arch/at91_sfr.h"
#include "debug.h"

void redirect_interrupts_to_nsaic(void)
{
	unsigned int key32;

	if (!(readl(SFR_AICREDIR + AT91C_BASE_SFR) & 0x01)) {
		key32 = readl(SFR_SN1 + AT91C_BASE_SFR) ^ AICREDIR_KEY;
		writel(((key32 & ~0x01) | 0x1), SFR_AICREDIR + AT91C_BASE_SFR);
			/* bits[31:1] = key */
			/* bit[0] = 1 => all interrupts redirected to AIC */
			/* bit[0] = 0 => secure interrupts directed to SAIC,
						others to AIC (default) */

		if ((readl(SFR_AICREDIR + AT91C_BASE_SFR) & 0x01))
			dbg_loud("All interrupts redirected to AIC\n");
	}
}
