// Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "clk-common.h"
#include "pmc.h"
#include "arch/at91_pmc/pmc.h"

int pmc_enable_periph_clock(unsigned int periph_id, int divider)
{
	unsigned int val;

	if (divider == PMC_PERIPH_CLK_DIVIDER_NA)
		divider = 0;

	write_pmc(PMC_PCR, ((periph_id & AT91C_PMC_PID)));
	val = read_pmc(PMC_PCR);
	val &= ~AT91C_PMC_DIV;
	val |= AT91C_PMC_DIV_(divider) | AT91C_PMC_CMD | AT91C_PMC_EN;
	write_pmc(PMC_PCR, val);

	return 0;
}

int pmc_disable_periph_clock(unsigned int periph_id)
{
	unsigned int val;

	write_pmc(PMC_PCR, (periph_id & AT91C_PMC_PID));
	val = read_pmc(PMC_PCR);
	val &= ~AT91C_PMC_EN;
	val |= AT91C_PMC_CMD;
	write_pmc(PMC_PCR, val);

	return 0;
}

unsigned int pmc_periph_clock_get_rate(unsigned int periph_id)
{
#ifdef CONFIG_SAMA7G5
	unsigned int val, mck_rate, mckid, div;

	write_pmc(PMC_PCR, (periph_id & AT91C_PMC_PID));
	val = read_pmc(PMC_PCR);
	mckid = (val & AT91C_PMC_MCKID) >> 16;
	div = (val & AT91C_PMC_DIV) >> 14;

	mck_rate = pmc_mck_get_rate(mckid);

	return mck_rate / (1 << div);
#else
	return at91_get_ahb_clock();
#endif
}
