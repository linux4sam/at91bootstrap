/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation
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
#include "board.h"
#include "timer.h"
#include "arch/at91_pmc.h"
#include "arch/at91_sfr.h"
#include "rstc.h"
#include "debug.h"
#include "div.h"
#include "pmc.h"

static inline void write_pmc(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_PMC);
}

static inline unsigned int read_pmc(unsigned int offset)
{
	return readl(offset + AT91C_BASE_PMC);
}

void lowlevel_clock_init()
{
	unsigned long tmp;

	/*
	 * Switch the master clock to the slow clock without modifying other
	 * parameters. It is assumed that ROM code set H32MXDIV, PLLADIV2,
	 * PCK_DIV3.
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_CSS);
	tmp |= AT91C_PMC_CSS_SLOW_CLK;
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

#if defined(CONFIG_SAMA5D3X_CMP)
	/*
	 * On the sama5d3x_cmp board, a phy is not in the proper reset state
	 * after power-up, additional reset
	 */
	rstc_external_reset();
#endif

#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(SAMA5D3X) \
	|| defined(SAMA5D4) || defined(SAMA5D2) || defined(AT91SAM9X60)
	/*
	 * Enable the Main Crystal Oscillator
	 * tST_max = 2ms
	 * Startup Time: 32768 * 2ms / 8 = 8
	 */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCXTST);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_MOSCXTEN;
	tmp |= AT91_CKGR_MOSCXTST_SET(18);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS))
		;

#if defined(SAMA5D2)
	/* Enable a measurement of the Main Cristal Oscillator */
	tmp = read_pmc(PMC_MCFR);
	tmp |= AT91C_CKGR_CCSS_XTAL_OSC;
	tmp |= AT91C_CKGR_RCMEAS;
	write_pmc(PMC_MCFR, tmp);

	while (!(read_pmc(PMC_MCFR) & AT91C_CKGR_MAINRDY))
		;
#endif

	/* Switch from internal 12MHz RC to the Main Cristal Oscillator */
#if !defined(AT91SAM9X60)
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCXTBY);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);
#endif

	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	tmp |= AT91C_CKGR_MOSCSEL;
	write_pmc(PMC_MOR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCSELS))
		;

#if !defined(SAMA5D4) && !defined(SAMA5D2)
	/* Disable the 12MHz RC Oscillator */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCRCEN);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);
#endif

#else
	/*
	 * Enable the Main Crystal Oscillator
	 * tST_max = 2ms
	 * Startup Time: 32768 * 2ms / 8 = 8
	 */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCXTST);
	tmp |= AT91C_CKGR_MOSCXTEN;
	tmp |= AT91_CKGR_MOSCXTST_SET(8);
	write_pmc(PMC_MOR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS))
		;
#endif

	/* After stablization, switch to Main Clock */
#if !defined(AT91SAM9X60)
	if ((read_pmc(PMC_MCKR) & AT91C_PMC_CSS) == AT91C_PMC_CSS_SLOW_CLK) {
#endif
		tmp = read_pmc(PMC_MCKR);
		tmp &= ~AT91C_PMC_ALT_PRES;
		tmp &= ~AT91C_PMC_CSS;
		tmp |= AT91C_PMC_PRES_ALT_CLK;
		tmp |= AT91C_PMC_CSS_MAIN_CLK;
		write_pmc(PMC_MCKR, tmp);

		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
			;
#if !defined(AT91SAM9X60)
	}
#endif

	return;
}

void pmc_init_pll(unsigned int pmc_pllicpr)
{
	write_pmc(PMC_PLLICPR, pmc_pllicpr);
}

void pmc_switch_mck_to_slck(void)
{
	unsigned long tmp;

	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_CSS);
	tmp |= AT91C_PMC_CSS_SLOW_CLK;
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;
}

void pmc_switch_mck_to_pll(void)
{
	unsigned long tmp;

	/* Select PLL as input clock for PCK and MCK */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_CSS);
	tmp |= AT91C_PMC_CSS_PLLA_CLK;
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;
}

void pmc_disable_internal_osc(void)
{
	unsigned long tmp;

	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCRCEN);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);
}


void pmc_enable_internal_osc(void)
{
	unsigned long tmp;

	if ((read_pmc(PMC_MOR) & AT91C_CKGR_MOSCRCEN)
			!= AT91C_CKGR_MOSCRCEN) {
		tmp = read_pmc(PMC_MOR);
		tmp &= (~AT91C_CKGR_KEY);
		tmp |= (AT91C_CKGR_MOSCRCEN | AT91C_CKGR_PASSWD);
		write_pmc(PMC_MOR, tmp);

		while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCRCS))
			;
	}
}

int pmc_enable_external_osc(unsigned int bypass)
{
	unsigned int cgmor = read_pmc(PMC_MOR);
	unsigned int mask = AT91C_CKGR_MOSCXTEN;

	/* Enable Crystal Oscillator if needed */
	if ((cgmor & mask) != mask) {
		cgmor &= (~AT91C_CKGR_KEY);
		cgmor |= AT91C_CKGR_PASSWD;

		/* Set Oscillator Startup Time */
		cgmor &= (~AT91C_CKGR_MOSCXTST);
		cgmor |= AT91_CKGR_MOSCXTST_SET(18);
		write_pmc(PMC_MOR, cgmor);

		/* Enable Crystal Oscillator */
		cgmor |=  AT91C_CKGR_MOSCXTEN;
		write_pmc(PMC_MOR, cgmor);

		/* Wait Main Oscillator ready */
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS))
			;
	} else {
		/* Crystal Oscillator already selected,
		 * just check if ready
		 */
		if (read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS)
			return 0;
		else
			return -1;
	}
	return 0;
}

void pmc_set_mck_prescaler(unsigned int prescaler)
{
	unsigned int reg;
	/* Change MCK Prescaler divider in PMC_MCKR register */
	reg = read_pmc(PMC_MCKR);
	reg &= (~AT91C_PMC_ALT_PRES);
	reg |= prescaler;
	write_pmc(PMC_MCKR, reg);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;
}

void pmc_set_mck_divider(unsigned int divider)
{
	unsigned int reg;
	/* change MCK Prescaler divider in PMC_MCKR register */
	reg = read_pmc(PMC_MCKR);
	reg &= (~AT91C_PMC_MDIV);
	reg |= divider;
	write_pmc(PMC_MCKR, reg);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;
}

int pmc_select_external_osc(unsigned int bypass)
{
	int err;
	unsigned int mask, reg;

	/* Return if external oscillator had been selected */
	if ((read_pmc(PMC_MOR) & AT91C_CKGR_MOSCSEL)
			== AT91C_CKGR_MOSCSEL) {
		mask = AT91C_CKGR_MOSCXTEN;
		if ((read_pmc(PMC_MOR) & mask) == mask)
			return 0;
	}
	/* When switching the source of the main clock between
	 * the RC oscillator and the crystal oscillator, both
	 * oscillators must be enabled. After completion of the
	 * switch, the unused oscillator can be disabled.
	 */
	pmc_enable_internal_osc();
	err = pmc_enable_external_osc(bypass);
	if (err < 0)
		return err;

	/* switch MAIN clock to external oscillator */
	reg = read_pmc(PMC_MOR);
	reg &= (~AT91C_CKGR_KEY);
	reg |= (AT91C_CKGR_MOSCSEL | AT91C_CKGR_PASSWD);
	write_pmc(PMC_MOR, reg);

	/* wait for the command to be taken into account */
	while ((read_pmc(PMC_MOR) & AT91C_CKGR_MOSCSEL) != AT91C_CKGR_MOSCSEL)
		;

	/* wait MAIN clock status change for external
	 * oscillator selection
	 */
	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCSELS))
		;

	/* in case where MCK is running on MAIN CLK */
	if ((read_pmc(PMC_MCKR) &  AT91C_PMC_CSS_PLLA_CLK) ||
			(read_pmc(PMC_MCKR) & AT91C_PMC_CSS_MAIN_CLK))
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
			;

	/* disable internal 12MHz RC to save power */
	pmc_disable_internal_osc();
	return 0;
}

void pmc_sam9x60_disable_pll(unsigned int pll_id)
{
	unsigned int reg;

	/* To power-down a PLL, the following sequence must be applied:
	 * 1. If the PLL drives a section of the system that is active,
	 * modify the source clock of the system.
	 */

	/* 2. Define the ID (ID=n) of the PLL to be switched off in
	 * PMC_UPDT. The bit UPDATE in this register
	 * must be set at 0 in this step.
	 */
	reg = read_pmc(PMC_PLL_UPDT);
	reg &= ~(AT91C_PLL_UPDT_UPDATE | AT91C_PLL_UPDT_ID);
	reg |= AT91C_PLL_UPDT_ID_(pll_id);
	write_pmc(PMC_PLL_UPDT, reg);

	/* 3. In PMC_PLL_CTRL0, set ENPLLCK to 0 and leave ENPLL at '1'.*/
	reg = read_pmc(PMC_PLL_CTRL0);
	reg &= (~AT91C_PLL_CTRL0_ENPLLCK);
	reg |= AT91C_PLL_CTRL0_ENPLL;
	write_pmc(PMC_PLL_CTRL0, reg);

	/* 4. Set PMC_PLL_UPDT.UPDATE to '1'. PMC_PLL_UPDT.ID must equal
	 * the one written during step 2, else the update is cancelled.
	 */
	reg = read_pmc(PMC_PLL_UPDT);
	reg |= AT91C_PLL_UPDT_UPDATE;
	write_pmc(PMC_PLL_UPDT, reg);

	/* 5. Write a '0' to PMC_PLL_CTRL0.ENPLL. */
	reg = read_pmc(PMC_PLL_CTRL0);
	reg &= (~AT91C_PLL_CTRL0_ENPLL);
	write_pmc(PMC_PLL_CTRL0, reg);

	/* 6. In case a UPLL is being powered down, write a '0' to
	 * PMC_PLL_ACR.UTMIBG and PMC_PLL_ACR.UTMIVR.
	 */
	if (pll_id == PLL_ID_UPLL) {
		reg = read_pmc(PMC_PLL_ACR);
		reg &= ~(AT91C_PLL_ACR_UTMIBG | AT91C_PLL_ACR_UTMIVR);
		write_pmc(PMC_PLL_ACR, reg);
	}
}

void pmc_sam9x60_cfg_pll(unsigned int pll_id, const struct _pmc_plla_cfg *plla)
{

	unsigned int reg;

	if (pll_id == PLL_ID_UPLL) {
		if (plla->div != 1)
			return;
	}

	reg = read_pmc(PMC_PLL_UPDT);
	reg &= ~(AT91C_PLL_UPDT_STUPTIM
			| AT91C_PLL_UPDT_UPDATE
			| AT91C_PLL_UPDT_ID);
	reg |= (AT91C_PLL_UPDT_STUPTIM_(plla->count)
		| AT91C_PLL_UPDT_ID_(pll_id));
	write_pmc(PMC_PLL_UPDT, reg);

	reg = read_pmc(PMC_PLL_ACR);
	reg &= ~AT91C_PLL_ACR_LOOP_FILTER;
	reg |= AT91C_PLL_ACR_LOOP_FILTER_(plla->loop_filter);
	write_pmc(PMC_PLL_ACR, reg);
	write_pmc(PMC_PLL_CTRL1, AT91C_PLL_CTRL1_MUL_(plla->mul)
			| AT91C_PLL_CTRL1_FRACR_(plla->fracr));

	if (pll_id == PLL_ID_UPLL) {
		reg = read_pmc(PMC_PLL_ACR);
		reg |= AT91C_PLL_ACR_UTMIBG;
		write_pmc(PMC_PLL_ACR, reg);
		udelay(10);
		reg = read_pmc(PMC_PLL_ACR);
		reg |= AT91C_PLL_ACR_UTMIVR;
		write_pmc(PMC_PLL_ACR, reg);
		udelay(10);
	}

	reg = read_pmc(PMC_PLL_UPDT);
	reg |= AT91C_PLL_UPDT_UPDATE;
	write_pmc(PMC_PLL_UPDT, reg);
	reg = read_pmc(PMC_PLL_CTRL0);
	reg &= (~AT91C_PLL_CTRL0_DIVPMC);
	reg |= (AT91C_PLL_CTRL0_ENLOCK
		| AT91C_PLL_CTRL0_ENPLL
		| AT91C_PLL_CTRL0_DIVPMC_(plla->div)
		| AT91C_PLL_CTRL0_ENPLLCK);
	write_pmc(PMC_PLL_CTRL0, reg);

	reg = read_pmc(PMC_PLL_UPDT);
	reg |= AT91C_PLL_UPDT_UPDATE;
	write_pmc(PMC_PLL_UPDT, reg);

	while ((read_pmc(PMC_PLL_ISR0) & (AT91C_PLL_ISR0_LOCK0 << pll_id))
			!= (AT91C_PLL_ISR0_LOCK0 << pll_id))
		;
}

int pmc_cfg_plla(unsigned int pmc_pllar)
{
	/* Always disable PLL before configuring it */
	write_pmc((unsigned int)PMC_PLLAR, 0 | AT91C_CKGR_SRCA);
	write_pmc((unsigned int)PMC_PLLAR, pmc_pllar);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_LOCKA))
		;

	return 0;
}

int pmc_cfg_mck(unsigned int pmc_mckr)
{
	unsigned int tmp;

	/*
	 * Program the PRES field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~(0x1 << 13));
#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(SAMA5D3X) \
	|| defined(SAMA5D4) || defined(SAMA5D2) ||  defined(AT91SAM9X60)
	tmp &= (~AT91C_PMC_ALT_PRES);
	tmp |= (pmc_mckr & AT91C_PMC_ALT_PRES);
#else
	tmp &= (~AT91C_PMC_PRES);
	tmp |= (pmc_mckr & AT91C_PMC_PRES);
#endif
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the MDIV field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_MDIV);
	tmp |= (pmc_mckr & AT91C_PMC_MDIV);
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the PLLADIV2 field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_PLLADIV2);
	tmp |= (pmc_mckr & AT91C_PMC_PLLADIV2);
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the H32MXDIV field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_H32MXDIV);
	tmp |= (pmc_mckr & AT91C_PMC_H32MXDIV);
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the CSS field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_CSS);
	tmp |= (pmc_mckr & AT91C_PMC_CSS);
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

	return 0;
}

int pmc_cfg_pck(unsigned char x, unsigned int clk_sel, unsigned int prescaler)
{
	write_pmc(PMC_PCKR + x * 4, clk_sel | prescaler);
	write_pmc(PMC_SCER, 1 << (x + 8));
	while (!(read_pmc(PMC_SR) & (1 << (x + 8)))) ;

	return 0;
}

int pmc_enable_periph_clock(unsigned int periph_id)
{
	unsigned int mask = 0x01 << (periph_id % 32);

	if ((periph_id / 32) == 1)
		write_pmc(PMC_PCER1, mask);
	else if ((periph_id / 32) == 0)
		write_pmc(PMC_PCER, mask);
	else
		return -1;

	return 0;
}

int pmc_disable_periph_clock(unsigned int periph_id)
{
	unsigned int mask = 0x01 << (periph_id % 32);

	if ((periph_id / 32) == 1)
		write_pmc(PMC_PCDR1, mask);
	else if ((periph_id / 32) == 0)
		write_pmc(PMC_PCDR, mask);
	else
		return -1;

	return 0;
}

int pmc_periph_clock_enabled(unsigned int periph_id)
{
	unsigned int mask = 0x01 << (periph_id % 32);
	int enabled = 0;

	if ((periph_id / 32) == 1)
		enabled = !!(read_pmc(PMC_PCSR1) & mask);
	else if ((periph_id / 32) == 0)
		enabled = !!(read_pmc(PMC_PCSR) & mask);

	return enabled;
}

void pmc_enable_system_clock(unsigned int clock_id)
{
	 write_pmc(PMC_SCER, clock_id);
}

void pmc_disable_system_clock(unsigned int clock_id)
{
	 write_pmc(PMC_SCDR, clock_id);
};

int pmc_sam9x5_enable_periph_clk(unsigned int periph_id)
{
	unsigned int div_value;

	write_pmc(PMC_PCR, periph_id);
	div_value = read_pmc(PMC_PCR) & AT91C_PMC_DIV;

	write_pmc(PMC_PCR, (periph_id | div_value
				| AT91C_PMC_CMD
				| AT91C_PMC_EN));

	return 0;
}

#if defined(AT91C_BASE_SFR) && !defined(SAMA5D4)
static unsigned long pmc_get_main_clock(void)
{
	unsigned long main_clock;

#ifdef BOARD_MAINOSC
	main_clock = BOARD_MAINOSC;
#else
	unsigned int tmp;

	do {
		tmp = read_pmc(PMC_MCFR);
	} while (!(tmp & AT91C_CKGR_MAINRDY));

	tmp &= AT91C_CKGR_MAINF;
	main_clock = tmp * (CONFIG_SYS_AT91_SLOW_CLOCK / 16);
#endif
	return main_clock;
}

static int clock_freq_in_range(unsigned long freq,
			     unsigned long norm, unsigned int delta)
{
	if (delta > norm)
		return 0;

	if ((freq >= (norm - delta)) && (freq <= (norm + delta)))
		return 1;
	else
		return 0;
}

static int pmc_configure_utmi_ref_clk(void)
{
	unsigned long main_clock;
	unsigned int utmi_ref_clk_freq, tmp;
	unsigned long delta = 50000;

	/*
	 * If mainck rate is different from 12 MHz, we have to configure
	 * the FREQ field of the SFR_UTMICKTRIM register to generate properly
	 * the utmi clock.
	 */
	main_clock = pmc_get_main_clock();
	if (clock_freq_in_range(main_clock, 12000000, delta)) {
		utmi_ref_clk_freq = 0;
	} else if (clock_freq_in_range(main_clock, 16000000, delta)) {
		utmi_ref_clk_freq = 1;
	} else if (clock_freq_in_range(main_clock, 24000000, delta)) {
		utmi_ref_clk_freq = 2;
	/*
	 * Not supported on SAMA5D2 but it's not an issue since MAINCK
	 * maximum value is 24 MHz.
	 */
	} else if (clock_freq_in_range(main_clock, 48000000, delta)) {
		utmi_ref_clk_freq = 3;
	} else {
		dbg_info("The MAINCK frequency: %d\n", main_clock);
		return -1;
	}

	tmp = readl(SFR_UTMICKTRIM + AT91C_BASE_SFR);
	tmp &= ~AT91C_UTMICKTRIM_FREQ;
	tmp |= utmi_ref_clk_freq;
	writel(tmp, SFR_UTMICKTRIM + AT91C_BASE_SFR);

	return 0;
}
#else
static int pmc_configure_utmi_ref_clk(void)
{
	return 0;
}
#endif

int pmc_uckr_clk(unsigned int is_on)
{
	unsigned int uckr = read_pmc(PMC_UCKR);
	unsigned int sr;
	int ret;

	if (is_on) {
		ret = pmc_configure_utmi_ref_clk();
		if (ret)
			return ret;

		uckr |= (AT91C_CKGR_UPLLCOUNT_DEFAULT |
			 AT91C_CKGR_UPLLEN | AT91C_CKGR_BIASEN);
		sr = AT91C_PMC_LOCKU;
	} else {
		uckr &= ~(AT91C_CKGR_UPLLEN | AT91C_CKGR_BIASEN);
		sr = 0;
	}

	write_pmc(PMC_UCKR, uckr);

	do {
		udelay(1);
	} while ((read_pmc(PMC_SR) & AT91C_PMC_LOCKU) != sr);

	return 0;
}

int pmc_enable_periph_generated_clk(unsigned int periph_id,
				    unsigned int clk_source,
				    unsigned int div)
{
	unsigned int regval, status;
	unsigned int timeout = 1000;

	if (periph_id > 0x7f)
		return -1;

	if (div > 0xff)
		return -1;

#if !defined(AT91SAM9X60)
	if (!(read_pmc(PMC_SR) & AT91C_PMC_LOCKU))
		pmc_uckr_clk(1);
#endif

	write_pmc(PMC_PCR, periph_id);
	regval = read_pmc(PMC_PCR);
	regval &= ~AT91C_PMC_GCKCSS;
	regval &= ~AT91C_PMC_GCKDIV;

	switch (clk_source) {
	case GCK_CSS_SLOW_CLK:
		regval |= AT91C_PMC_GCKCSS_SLOW_CLK;
		break;
	case GCK_CSS_MAIN_CLK:
		regval |= AT91C_PMC_GCKCSS_MAIN_CLK;
		break;
	case GCK_CSS_PLLA_CLK:
		regval |= AT91C_PMC_GCKCSS_PLLA_CLK;
		break;
	case GCK_CSS_UPLL_CLK:
		regval |= AT91C_PMC_GCKCSS_UPLL_CLK;
		break;
	case GCK_CSS_MCK_CLK:
		regval |= AT91C_PMC_GCKCSS_MCK_CLK;
		break;
#if !defined(AT91SAM9X60)
	case GCK_CSS_AUDIO_CLK:
		regval |= AT91C_PMC_GCKCSS_AUDIO_CLK;
		break;
#endif
	default:
		dbg_info("Error GCK clock source selection!\n");
		return -1;
	}

#if defined(AT91SAM9X60)
	div = 5; /* 6 as a divider */
#endif

	regval |= AT91C_PMC_CMD |
		  AT91C_PMC_GCKDIV_(div) |
		  AT91C_PMC_GCKEN;

	write_pmc(PMC_PCR, regval);

#if defined(AT91SAM9X60)
	/* TODO adapt to PMC and periph ID */
	do {
		udelay(1);
		status = read_pmc(PMC_GCSR0);
	} while ((!!(--timeout)) && (!(status & (1 << (periph_id % 32)))));
#else
	do {
		udelay(1);
		status = read_pmc(PMC_SR);
	} while ((!!(--timeout)) && (!(status & AT91C_PMC_GCKRDY)));
#endif

	if (!timeout)
		dbg_info("Timeout waiting for GCK ready!\n");

	return 0;
}

void pmc_sam9x5_disable_periph_clk(unsigned int periph_id)
{
	write_pmc(PMC_PCR, ((periph_id & AT91C_PMC_PID) | AT91C_PMC_CMD));
}

void pmc_set_smd_clock_divider(unsigned int divider)
{
	unsigned int tmp = read_pmc(PMC_SMD);

	tmp &= ~AT91C_PMC_SMDDIV;
	tmp |= AT91C_PMC_SMDDIV_(divider);

	write_pmc(PMC_SMD, tmp);
}

int pmc_check_mck_h32mxdiv(void)
{
#ifdef CPU_HAS_H32MXDIV
	return read_pmc(PMC_MCKR) & AT91C_PMC_H32MXDIV;
#else
	return 0;
#endif
}

unsigned int at91_get_ahb_clock(void)
{
	if (pmc_check_mck_h32mxdiv())
		return MASTER_CLOCK / 2;

	return MASTER_CLOCK;
}

/* TODO: to be updated for sam9x60 */
#if !defined(AT91SAM9X60)
static unsigned int pmc_get_plla_freq(void)
{
	unsigned int tmp;
	unsigned int divider, multiplier;
	unsigned int main_clock;
	unsigned int freq;

#ifdef BOARD_MAINOSC
	main_clock = BOARD_MAINOSC;
#else
	return 0;
#endif

	tmp = read_pmc(PMC_PLLAR);
	divider = tmp & AT91C_CKGR_DIVA_MSK;
	multiplier = (tmp >> AT91C_CKGR_ALT_MULA_OFFSET)
					& AT91C_CKGR_ALT_MULA_MSK;
	if (divider && multiplier) {
		freq = div(main_clock, divider);
		freq *= multiplier + 1;

		if (read_pmc(PMC_MCKR) & AT91C_PMC_PLLADIV2)
			freq /= 2;
	} else {
		freq = 0;
	}

	return freq;
}
#endif

unsigned int pmc_get_generated_clock(unsigned int periph_id)
{
	unsigned int tmp;
	unsigned int clock_source, divider;
	unsigned int freq = 0;

	write_pmc(PMC_PCR, periph_id);
	tmp = read_pmc(PMC_PCR);

	divider = (tmp >> AT91C_PMC_GCKDIV_OFFSET) & AT91C_PMC_GCKDIV_MSK;
	divider += 1;

	clock_source = tmp & AT91C_PMC_GCKCSS;
	switch (clock_source) {
	case AT91C_PMC_GCKCSS_MAIN_CLK:
#ifdef BOARD_MAINOSC
		freq = BOARD_MAINOSC;
#else
		freq = 0;
#endif
		break;
	case AT91C_PMC_GCKCSS_PLLA_CLK:
#if defined(AT91SAM9X60)
		freq = 600000000;
#else
		freq = pmc_get_plla_freq();
#endif
		break;
	case AT91C_PMC_GCKCSS_UPLL_CLK:
		freq = 480000000;
		break;
	case AT91C_PMC_GCKCSS_MCK_CLK:
		freq = MASTER_CLOCK;
		break;
	default:
		freq = 0;
		break;
	}

	freq = div(freq, divider);

	return freq;
}

#if defined(CONFIG_ENTER_NWD)
unsigned int pmc_read_reg(unsigned int reg_offset)
{
	if (reg_offset <= PMC_OCR)
		return read_pmc(reg_offset);
	else
		return 0xffffffff;
}

void pmc_enable_clock(unsigned int per_id)
{
	unsigned long regval;

	regval = AT91C_PMC_CMD | AT91C_PMC_EN;
	regval |= (per_id & AT91C_PMC_PID);

	/* No need to use Peripheral Divisor value
	 * peripherals are supposed to work @ 90MHz
	 */
	write_pmc(PMC_PCR, regval);
}

void pmc_disable_clock(unsigned int per_id)
{
	unsigned long regval;

	regval = AT91C_PMC_CMD;
	regval |= (per_id & AT91C_PMC_PID);
	write_pmc(PMC_PCR, regval);
}

int pmc_periph_clk(unsigned int periph_id, unsigned int is_on)
{
	if ((periph_id > AT91C_ID_FIQ) && (periph_id < AT91C_ID_COUNTS)) {
		if (is_on)
			pmc_enable_clock(periph_id);
		else
			pmc_disable_clock(periph_id);
		return 0;
	} else {
		return -1;
	}
}

unsigned int sys_mask_to_per_id(unsigned int sys_mask)
{
	switch (sys_mask) {
	case AT91C_PMC_LCDCK:
		return AT91C_ID_LCDC;
	case AT91C_PMC_SMDCK:
		return AT91C_ID_SMD;
	case AT91C_PMC_UHP:
		return AT91C_ID_UHPHS;
	case AT91C_PMC_UDP:
		return AT91C_ID_UDPHS;
	}

	return 0xffffffff;
}

int pmc_sys_clk(unsigned int sys_clock_mask, unsigned int is_on)
{
	if (sys_clock_mask & AVAILABLE_SYS_CLK) {
		if (is_on)
			write_pmc(PMC_SCER, sys_clock_mask);
		else
			write_pmc(PMC_SCDR, sys_clock_mask);
		return 0;
	} else {
		return -1;
	}
}

void pmc_pck_setup(unsigned int reg_offset, unsigned int reg_value)
{
	write_pmc(reg_offset, reg_value);
}

unsigned int pmc_usb_setup(void)
{
	unsigned int usbr = AT91C_PMC_USBS_USB_UPLL;

	/* Setup divider by 10 to reach 48 MHz */
	usbr |= ((10 - 1) << 8) & AT91C_PMC_USBDIV;

	write_pmc(PMC_USB, usbr);

	return usbr;
}

void pmc_smd_setup(unsigned int val)
{
	val &= (AT91C_PMC_SMDS | AT91C_PMC_SMDDIV);

	write_pmc(PMC_SMD, val);
}
#endif	/* #if defined(CONFIG_ENTER_NWD) */
