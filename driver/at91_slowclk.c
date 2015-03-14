/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "hardware.h"
#include "arch/at91_slowclk.h"
#include "timer.h"

int slowclk_enable_osc32(void)
{
	unsigned int reg;

	/*
	 * Enable the 32768 Hz oscillator by setting the bit OSC32EN to 1
	 */
	reg = readl(AT91C_BASE_SCKCR);
	reg |= AT91C_SLCKSEL_OSC32EN;
	writel(reg, AT91C_BASE_SCKCR);

	/* start a internal timer */
	start_interval_timer();

	return 0;
}

#if !defined(SAMA5D4)
static void slowclk_wait_osc32_stable(void)
{
	/*
	 * Wait 32768 Hz Startup Time for clock stabilization (software loop)
	 * wait about 1s (1300ms)
	 */
	wait_interval_timer(1300);
}

static void slowclk_disable_rc32(void)
{
	unsigned int reg;

	/*
	 * Disable the 32kHz RC oscillator by setting the bit RCEN to 0
	 */
	reg = readl(AT91C_BASE_SCKCR);
	reg &= ~AT91C_SLCKSEL_RCEN;
	writel(reg, AT91C_BASE_SCKCR);
}

#if defined(CONFIG_SCLK_BYPASS)
static void slowclk_bypass_osc32(void)
{
	unsigned int reg;

	/*
	 * Bypass the 32kHz oscillator by using an external clock
	 */
	reg = readl(AT91C_BASE_SCKCR);
	reg |= AT91C_SLCKSEL_OSC32BYP;
	writel(reg, AT91C_BASE_SCKCR);

	reg = readl(AT91C_BASE_SCKCR);
	reg &= ~AT91C_SLCKSEL_OSC32EN;
	writel(reg, AT91C_BASE_SCKCR);
}
#endif /* #if defined(CONFIG_SCLK_BYPASS) */
#endif /* #if !defined(SAMA5D4) */

static int slowclk_select_osc32(void)
{
	unsigned int reg;

	/*
	 * Switching from internal 32kHz RC oscillator to 32768 Hz oscillator
	 * by setting the bit OSCSEL to 1
	 */
	reg = readl(AT91C_BASE_SCKCR);
	reg |= AT91C_SLCKSEL_OSCSEL;
	writel(reg, AT91C_BASE_SCKCR);

	/*
	 * Waiting 5 slow clock cycles for internal resynchronization
	 * 5 slow clock cycles = ~153 us (5 / 32768)
	 */
	udelay(153);

	return 0;
}

int slowclk_switch_osc32(void)
{
#if defined(SAMA5D4)
	slowclk_select_osc32();
#else
	slowclk_wait_osc32_stable();

	slowclk_select_osc32();

	slowclk_disable_rc32();

#if defined(CONFIG_SCLK_BYPASS)
	slowclk_bypass_osc32();
#endif
#endif

	return 0;
}
