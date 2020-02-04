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
#include "board.h"
#include "clk-common.h"
#include "pmc.h"
#include "types.h"
#include "arch/at91_pmc/pmc.h"

static unsigned long pmc_mck_css_to_freq(unsigned int css)
{
	unsigned long freq = 0;

	switch (css) {
	case AT91C_PMC_CSS_SLOW_CLK:
		freq = 32768;
		break;
	case AT91C_PMC_CSS_MAIN_CLK:
		freq = pmc_mainck_get_rate();
		break;
	case AT91C_PMC_CSS_CPUPLL_CLK:
	case AT91C_PMC_CSS_SYSPLL_CLK:
		freq = pmc_get_pll_freq(css - AT91C_PMC_CSS_CPUPLL_CLK);
		break;
	default:
		break;
	}

	return freq;
}

static void pmc_mck_mck0_set(unsigned int updates, unsigned int bits,
			     bool css_first)
{
	unsigned int tmp;

	/* Update CSS/MDIV. */
	if (css_first) {
		if (updates & AT91C_PMC_CSS) {
			tmp = read_pmc(PMC_MCKR);
			tmp &= ~AT91C_PMC_CSS;
			tmp |= (bits & AT91C_PMC_CSS);
			write_pmc(PMC_MCKR, tmp);
			while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
		}
	} else {
		if (updates & AT91C_PMC_MDIV) {
			tmp = read_pmc(PMC_MCKR);
			tmp &= ~AT91C_PMC_MDIV;
			tmp |= (bits & AT91C_PMC_MDIV);
			write_pmc(PMC_MCKR, tmp);
			while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
		}
	}

	/* Update PRES. */
	if (updates & AT91C_PMC_PRES) {
		tmp = read_pmc(PMC_MCKR);
		tmp &= ~AT91C_PMC_PRES;
		tmp |= (bits & AT91C_PMC_PRES);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}

	/* Update MDIV/CSS. */
	if (css_first) {
		if (updates & AT91C_PMC_MDIV) {
			tmp = read_pmc(PMC_MCKR);
			tmp &= ~AT91C_PMC_MDIV;
			tmp |= (bits & AT91C_PMC_MDIV);
			write_pmc(PMC_MCKR, tmp);
			while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
		}
	} else {
		if (updates & AT91C_PMC_CSS) {
			tmp = read_pmc(PMC_MCKR);
			tmp &= ~AT91C_PMC_CSS;
			tmp |= (bits & AT91C_PMC_CSS);
			write_pmc(PMC_MCKR, tmp);
			while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
		}
	}
}

void pmc_mck_cfg_set(unsigned int mckid, unsigned int bits, unsigned int mask)
{
	unsigned int updates, tmp;
	unsigned long cur_freq = 0, new_freq = 0;

	/* MCK0 is programmed via PMC_MCKR. */
	if (!mckid) {
		tmp = read_pmc(PMC_MCKR);
		updates = (tmp & mask) ^ bits;

		if (updates & AT91C_PMC_CSS) {
			/*
			 * We have different progamming order b/w CSS, PRES,
			 * MDIV based on selected clock source.
			 */
			cur_freq = pmc_mck_css_to_freq(tmp & AT91C_PMC_CSS);
			new_freq = pmc_mck_css_to_freq(bits & AT91C_PMC_CSS);
		}

		pmc_mck_mck0_set(updates, bits, cur_freq < new_freq);

		return;
	}

	/* Read current config. */
	write_pmc(PMC_MCR, mckid);
	tmp = read_pmc(PMC_MCR);
	updates = (tmp & mask) ^ bits;

	/* Prepare new config. */
	if (updates & AT91C_MCR_DIV) {
		tmp &= ~AT91C_MCR_DIV;
		tmp |= (bits & AT91C_MCR_DIV);
	}
	if (updates & AT91C_MCR_CSS) {
		tmp &= ~AT91C_MCR_CSS;
		tmp |= (bits & AT91C_MCR_CSS);
	}
	if (updates & AT91C_MCR_EN) {
		tmp &= ~AT91C_MCR_EN;
		tmp |= (bits & AT91C_MCR_EN);
	}

	/* Update it. */
	write_pmc(PMC_MCR, AT91C_MCR_CMD | mckid | tmp);

	while ((updates & AT91C_MCR_CSS) &&
	       !(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
}

int pmc_mck_check_h32mxdiv(void)
{
	return 0;
}
