// Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "clk-common.h"
#include "common.h"
#include "debug.h"
#include "div.h"
#include "hardware.h"
#include "pmc.h"
#include "timer.h"
#include "arch/at91_pmc/pmc.h"

#ifdef CONFIG_PMC_V1
static const unsigned int css_idx_to_reg[] = {
	[GCK_CSS_SLOW_CLK]	= AT91C_PMC_GCKCSS_SLOW_CLK,
	[GCK_CSS_MAIN_CLK]	= AT91C_PMC_GCKCSS_MAIN_CLK,
	[GCK_CSS_MCK_CLK]	= AT91C_PMC_GCKCSS_MCK_CLK,
	[GCK_CSS_PLLA_CLK]	= AT91C_PMC_GCKCSS_PLLA_CLK,
	[GCK_CSS_UPLL_CLK]	= AT91C_PMC_GCKCSS_UPLL_CLK,
	[GCK_CSS_AUDIO_CLK]	= AT91C_PMC_GCKCSS_AUDIO_CLK,
};
#define GCK_STATUS_REG(_p)	(PMC_SR)
#define GCK_READY(_s, _p)	((_s) & AT91C_PMC_GCKRDY)

#elif CONFIG_PMC_V2
static const unsigned int gcsr[] = { PMC_GCSR0, PMC_GCSR1, PMC_GCSR2 };
static const unsigned int css_idx_to_reg[] = {
	[GCK_CSS_SLOW_CLK]	= AT91C_PMC_GCKCSS_SLOW_CLK,
	[GCK_CSS_MAIN_CLK]	= AT91C_PMC_GCKCSS_MAIN_CLK,
	[GCK_CSS_MCK_CLK]	= AT91C_PMC_GCKCSS_MCK_CLK,
	[GCK_CSS_PLLA_CLK]	= AT91C_PMC_GCKCSS_PLLA_CLK,
	[GCK_CSS_UPLL_CLK]	= AT91C_PMC_GCKCSS_UPLL_CLK,
	[GCK_CSS_PLLADIV2_CLK]	= AT91C_PMC_GCKCSS_PLLADIV2_CLK,
};
#define GCK_STATUS_REG(_p)	gcsr[(_p) / 32]
#define GCK_READY(_s, _p)	((_s) & (1 << ((_p) % 32)))

#elif CONFIG_PMC_V3
static const unsigned int gcsr[] = { PMC_GCSR0, PMC_GCSR1, PMC_GCSR2 };
static const unsigned int css_idx_to_reg[] = {
	[GCK_CSS_SLOW_CLK]	= AT91C_PMC_GCKCSS_SLOW_CLK,
	[GCK_CSS_MAIN_CLK]	= AT91C_PMC_GCKCSS_MAIN_CLK,
	[GCK_CSS_MCK_CLK]	= AT91C_PMC_GCKCSS_MCK_CLK,
	[GCK_CSS_SYSPLL_CLK]	= AT91C_PMC_GCKCSS_SYSPLL_CLK,
	[GCK_CSS_DDRPLL_CLK]	= AT91C_PMC_GCKCSS_DDRPLL_CLK,
	[GCK_CSS_IMGPLL_CLK]	= AT91C_PMC_GCKCSS_IMGPLL_CLK,
	[GCK_CSS_BAUDPLL_CLK]	= AT91C_PMC_GCKCSS_BAUDPLL_CLK,
	[GCK_CSS_AUDIO_CLK]	= AT91C_PMC_GCKCSS_AUDIOPLL_CLK,
	[GCK_CSS_ETHPLL_CLK]	= AT91C_PMC_GCKCSS_ETHPLL_CLK,
};
#define GCK_STATUS_REG(_p)	gcsr[(_p) / 32]
#define GCK_READY(_s, _p)	((_s) & (1 << ((_p) % 32)))

#endif

#define CSS_IDX_TO_REGVAL(idx)	(css_idx_to_reg[idx])

int pmc_enable_generic_clock(unsigned int periph_id, unsigned int clk_source,
			     unsigned int div)
{
	unsigned int regval, status;
	unsigned int timeout = 1000;

	if (periph_id > 0x7f)
		return -1;

#ifndef CONFIG_PMC_V1
	if (periph_id / 32 > ARRAY_SIZE(gcsr)) {
		dbg_info("GCK: invalid peripheral id!\n");
		return -1;
	}
#endif

	if (clk_source > ARRAY_SIZE(css_idx_to_reg)) {
		dbg_info("Error GCK clock source selection!\n");
		return -1;
	}

	if (div > 0xff)
		return -1;

#ifdef CONFIG_PMC_UTMI_CLK
	if (!(read_pmc(PMC_SR) & AT91C_PMC_LOCKU))
		pmc_uckr_clk(1);
#endif

	write_pmc(PMC_PCR, periph_id);
	regval = read_pmc(PMC_PCR);
	regval &= ~AT91C_PMC_GCKCSS;
	regval &= ~AT91C_PMC_GCKDIV;

	regval |= CSS_IDX_TO_REGVAL(clk_source) |
		  AT91C_PMC_CMD |
		  AT91C_PMC_GCKDIV_(div) |
		  AT91C_PMC_GCKEN;

	write_pmc(PMC_PCR, regval);

	do {
		udelay(1);
		status = read_pmc(GCK_STATUS_REG(periph_id));
	} while ((!!(--timeout)) && (!GCK_READY(status, periph_id)));

	if (!timeout)
		dbg_info("Timeout waiting for GCK ready!\n");

	return 0;
}

unsigned int pmc_get_generic_clock(unsigned int periph_id)
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
#if defined(CONFIG_PMC_PLL_CLK) || defined(CONFIG_PMC_PLL_CLK_SAM9X60)
#if defined(CONFIG_PMC_V3)
	case AT91C_PMC_GCKCSS_SYSPLL_CLK:
	case AT91C_PMC_GCKCSS_DDRPLL_CLK:
	case AT91C_PMC_GCKCSS_IMGPLL_CLK:
	case AT91C_PMC_GCKCSS_BAUDPLL_CLK:
	case AT91C_PMC_GCKCSS_AUDIOPLL_CLK:
	case AT91C_PMC_GCKCSS_ETHPLL_CLK:
		tmp = ((clock_source - AT91C_PMC_GCKCSS_SYSPLL_CLK) >> 8) + 1;
		freq = pmc_get_pll_freq(tmp);
		break;
#else
	case AT91C_PMC_GCKCSS_PLLA_CLK:
	case AT91C_PMC_GCKCSS_UPLL_CLK:
#if defined(CONFIG_PMC_V2)
	case AT91C_PMC_GCKCSS_PLLADIV2_CLK:
#endif
		tmp = (clock_source - AT91C_PMC_GCKCSS_PLLA_CLK) >> 8;
		freq = pmc_get_pll_freq(tmp);
		break;
#endif
#endif
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

