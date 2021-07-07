/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __PMC_H__
#define __PMC_H__

#define CONFIG_SYS_AT91_SLOW_CLOCK	32768
#define PMC_PERIPH_CLK_DIVIDER_NA	(-1)

/* Generated clock source selection */
enum gck_css_clk {
	GCK_CSS_SLOW_CLK,
	GCK_CSS_MAIN_CLK,
	GCK_CSS_PLLA_CLK,
	GCK_CSS_UPLL_CLK,
	GCK_CSS_MCK_CLK,
	GCK_CSS_AUDIO_CLK,
	GCK_CSS_SYSPLL_CLK,
	GCK_CSS_DDRPLL_CLK,
	GCK_CSS_IMGPLL_CLK,
	GCK_CSS_BAUDPLL_CLK,
	GCK_CSS_ETHPLL_CLK,
};

enum pll_ids {
	PLL_ID_PLLA,
	PLL_ID_UPLL,
	#if defined(CONFIG_SAMA5D2)
	PLL_ID_AUDIO,
	#elif  defined(CONFIG_SAMA7G5)
	PLL_ID_CPUPLL = 0,
	PLL_ID_SYSPLL,
	PLL_ID_DDRPLL,
	PLL_ID_IMGPLL,
	PLL_ID_BAUDPLL,
	PLL_ID_AUDIOPLL,
	PLL_ID_ETHPLL,
	#endif
	PLL_ID_MAX,
};

struct pmc_pll_cfg {
	unsigned int mul;	/* PLL MUL value */
	unsigned int div;	/* PLL DIV value */
	unsigned int divio;	/* PLL DIVIO value */
	unsigned int count;	/* PLL COUNT value */
	unsigned int fracr;
	unsigned int acr;
};

extern void pmc_init_pll(unsigned int pmc_pllicpr);
extern int pmc_cfg_plla(unsigned int pmc_pllar);
extern void pmc_sam9x60_cfg_pll(unsigned int pll_id, struct pmc_pll_cfg *cfg);
extern unsigned int pmc_get_pll_freq(unsigned int pll_id);

extern void pmc_mck_cfg_set(unsigned int mckid, unsigned int bits,
			    unsigned int mask);
extern int pmc_mck_check_h32mxdiv(void);
extern unsigned int pmc_mck_get_rate(unsigned int mckid);
extern int pmc_cfg_pck(unsigned char x,
			unsigned int clk_sel,
			unsigned int prescaler);

extern int pmc_enable_periph_clock(unsigned int periph_id, int divider);
extern int pmc_disable_periph_clock(unsigned int periph_id);
extern int pmc_periph_clock_enabled(unsigned int periph_id);
unsigned int pmc_periph_clock_get_rate(unsigned int periph_id);
extern void pmc_enable_system_clock(unsigned int clock_id);
extern void pmc_disable_system_clock(unsigned int clock_id);
extern void pmc_set_smd_clock_divider(unsigned int divider);

extern int pmc_enable_generic_clock(unsigned int periph_id,
				    unsigned int clk_source,
				    unsigned int div);
extern unsigned int pmc_get_generic_clock(unsigned int periph_id);

extern unsigned int pmc_read_reg(unsigned int reg_offset);
extern int pmc_periph_clk(unsigned int periph_id, unsigned int is_on);
extern unsigned int sys_mask_to_per_id(unsigned int sys_mask);
extern int pmc_sys_clk(unsigned int sys_clock_mask, unsigned int is_on);
extern int pmc_uckr_clk(unsigned int is_on);
extern unsigned int pmc_usb_setup(void);
extern void pmc_smd_setup(unsigned int val);
extern void pmc_pck_setup(unsigned int reg_offset, unsigned int reg_value);

extern unsigned int at91_get_ahb_clock(void);
extern unsigned int pmc_mainck_get_rate(void);

#endif	/* #ifndef __PMC_H__ */
