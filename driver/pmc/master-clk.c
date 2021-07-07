// Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "clk-common.h"
#include "arch/at91_pmc/pmc.h"

void pmc_mck_cfg_set(unsigned int mckid, unsigned int bits, unsigned int mask)
{
	unsigned int tmp = read_pmc(PMC_MCKR) & mask;
	unsigned int updates = tmp ^ bits;

	/*
	 * Program the PRES field in the PMC_MCKR register
	 */
#if defined(CONFIG_SAMA5D3X) || defined(CONFIG_SAMA5D4) \
	|| defined(CONFIG_SAMA5D2)
	if (updates & AT91C_PMC_ALT_PRES) {
		tmp &= (~(0x1 << 13));
		tmp &= (~AT91C_PMC_ALT_PRES);
		tmp |= (bits & AT91C_PMC_ALT_PRES);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}
#else
	if (updates & AT91C_PMC_PRES) {
		tmp &= (~(0x1 << 13));
		tmp &= (~AT91C_PMC_PRES);
		tmp |= (bits & AT91C_PMC_PRES);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}
#endif

	/*
	 * Program the MDIV field in the PMC_MCKR register
	 */
	if (updates & AT91C_PMC_MDIV) {
		tmp = read_pmc(PMC_MCKR);
		tmp &= (~AT91C_PMC_MDIV);
		tmp |= (bits & AT91C_PMC_MDIV);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}

	/*
	 * Program the PLLADIV2 field in the PMC_MCKR register
	 */
	if (updates & AT91C_PMC_PLLADIV2) {
		tmp = read_pmc(PMC_MCKR);
		tmp &= (~AT91C_PMC_PLLADIV2);
		tmp |= (bits & AT91C_PMC_PLLADIV2);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}

	/*
	 * Program the H32MXDIV field in the PMC_MCKR register
	 */
	if (updates & AT91C_PMC_H32MXDIV) {
		tmp = read_pmc(PMC_MCKR);
		tmp &= (~AT91C_PMC_H32MXDIV);
		tmp |= (bits & AT91C_PMC_H32MXDIV);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}

	/*
	 * Program the CSS field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	if (updates & AT91C_PMC_CSS) {
		tmp = read_pmc(PMC_MCKR);
		tmp &= (~AT91C_PMC_CSS);
		tmp |= (bits & AT91C_PMC_CSS);
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}
}

int pmc_mck_check_h32mxdiv(void)
{
#ifdef CONFIG_CPU_HAS_H32MXDIV
	return read_pmc(PMC_MCKR) & AT91C_PMC_H32MXDIV;
#else
	return 0;
#endif
}

unsigned int pmc_mck_get_rate(unsigned int mckid)
{
	return MASTER_CLOCK;
}
