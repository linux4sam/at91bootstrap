// Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "clk-common.h"
#include "common.h"
#include "div.h"
#include "pmc.h"
#include "arch/at91_pmc/pmc.h"

void pmc_init_pll(unsigned int pmc_pllicpr)
{
	write_pmc(PMC_PLLICPR, pmc_pllicpr);
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

unsigned int pmc_get_pll_freq(unsigned int pll_id)
{
	unsigned int tmp;
	unsigned int divider, multiplier;
	unsigned int parent_rate = 0;
	unsigned int freq;

	switch (pll_id) {
	case PLL_ID_PLLA:
		parent_rate = pmc_mainck_get_rate();
		break;
	case PLL_ID_UPLL:
#ifdef CONFIG_AT91SAM9N12
		parent_rate = pmc_mainck_get_rate();
#elif BOARD_MAINOSC
		parent_rate = BOARD_MAINOSC;
#endif
		break;
#if defined(CONFIG_SAMA5D2) && defined(BOARD_MAINOSC)
	case PLL_ID_AUDIO:
		parent_rate = BOARD_MAINOSC;
		break;
#endif
	default:
		break;
	}

	tmp = read_pmc(PMC_PLLAR);
	divider = tmp & AT91C_CKGR_DIVA_MSK;
	multiplier = (tmp >> AT91C_CKGR_ALT_MULA_OFFSET) &
		     AT91C_CKGR_ALT_MULA_MSK;
	if (divider && multiplier) {
		freq = div(parent_rate, divider);
		freq *= multiplier + 1;

		if (read_pmc(PMC_MCKR) & AT91C_PMC_PLLADIV2)
			freq /= 2;
	} else {
		freq = 0;
	}

	return freq;
}

