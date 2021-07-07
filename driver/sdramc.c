// Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "board.h"
#include "arch/at91_pmc/pmc.h"
#include "arch/at91_sfr.h"
#include "arch/at91_sdramc.h"
#include "pmc.h"
#include "sdramc.h"

static inline void sdramc_writel(unsigned int reg, const unsigned int value)
{
	writel(value, reg + AT91C_BASE_SDRAMC);
}

static inline unsigned int sdramc_readl(unsigned int reg)
{
	return readl(reg + AT91C_BASE_SDRAMC);
}

static void sdramc_reg_config(struct sdramc_register *sdramc_config)
{
	sdramc_config->cr = AT91C_SDRAMC_NC_8
					| AT91C_SDRAMC_NR_12
					| AT91C_SDRAMC_CAS_3
					| AT91C_SDRAMC_NB_4_BANKS
					| AT91C_SDRAMC_DBW_16_BITS
					| AT91C_SDRAMC_TWR_3
					| AT91C_SDRAMC_TRC_11
					| AT91C_SDRAMC_TRP_3
					| AT91C_SDRAMC_TRCD_3
					| AT91C_SDRAMC_TRAS_8
					| AT91C_SDRAMC_TXSR_12;

	sdramc_config->tr = (MASTER_CLOCK * 7) / 1000000;
	sdramc_config->mdr = AT91C_SDRAMC_MD_SDRAM
					| AT91C_SDRAMC_MD_SHIFT_SAMPLING_2_CYCLE;

	sdramc_config->cfr1 = AT91C_SDRAMC_CFR1_TMRD_2 | AT91C_SDRAMC_CFR1_UNAL
				| AT91C_SDRAMC_CFR1_ADD_DATA_MUX_UNSUPPORTED
				| AT91C_SDRAMC_CFR1_CMD_MUX_UNSUPPORTED;
}

void sdramc_init(void)
{
	struct sdramc_register sdramc_reg;
	unsigned int reg = 0;

	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	/*
	 * We need to also enable AT91C_EBI_NFD0_ON_D16 . Otherwise the DDR will
	 * not work if NAND lines have been previously used by RomCode
	 */
	reg |= (AT91C_EBI_CS1A | AT91C_EBI_NFD0_ON_D16);
	writel(reg, (AT91C_BASE_SFR + SFR_DDRCFG));

	pmc_enable_periph_clock(AT91C_ID_SDRAMC, PMC_PERIPH_CLK_DIVIDER_NA);
	pmc_enable_system_clock(AT91C_PMC_DDR);

	sdramc_reg_config(&sdramc_reg);

	sdramc_initialize(&sdramc_reg, AT91C_BASE_DDRCS);
}

unsigned int get_sdram_size(void)
{
	return 0x800000;
}

int sdramc_initialize(struct sdramc_register *sdramc_config,
			unsigned int sdram_address)
{
	unsigned int i;

	/* Step#1 SDRAM feature must be in the configuration register */
	sdramc_writel(SDRAMC_CR, sdramc_config->cr);

	/* Step#1 bis (SAM9X60 SDRAMC ) - initialize CFR1 register */

	if (sdramc_config->cfr1) /* avoid write for products where cfr1 is unavailable */
		sdramc_writel(SDRAMC_CFR1, sdramc_config->cfr1);

	/* Step#2 For mobile SDRAM, temperature-compensated self refresh(TCSR),... */

	/* Step#3 The SDRAM memory type must be set in the Memory Device Register */
	sdramc_writel(SDRAMC_MDR, sdramc_config->mdr);

	/* Step#4 The minimum pause of 200 us is provided to precede any single toggle */
	for (i = 0; i < 1000; i++) ;

	/* Step#5 A NOP command is issued to the SDRAM devices */
	sdramc_writel(SDRAMC_MR, AT91C_SDRAMC_MODE_NOP);
	writel(0x00000000, sdram_address);

	/* Step#6 An All Banks Precharge command is issued to the SDRAM devices  */
	sdramc_writel(SDRAMC_MR, AT91C_SDRAMC_MODE_PRECHARGE);
	writel(0x00000000, sdram_address);

	for (i = 0; i < 10000; i++) ;

	/* Step#7 Eight auto-refresh cycles are provided */
	for (i = 0; i < 8; i++) {
		sdramc_writel(SDRAMC_MR, AT91C_SDRAMC_MODE_AUTO_REFRESH);
		writel(0x00000001 + i, sdram_address + 4 + 4 * i);
	}

	/*  Pause cycles */
	for (i = 0; i < 1000; i++) ;

	/* Step#8 A Mode Register set (MRS) cyscle is issued to program the SDRAM parameters(TCSR, PASR, DS) */
	sdramc_writel(SDRAMC_MR, AT91C_SDRAMC_MODE_LOAD_MODE);
	writel(0xcafedede, sdram_address + 0x24);

	/*  Pause cycles */
	for (i = 0; i < 1000; i++) ;

	/* Step#9 For mobile SDRAM initialization, an Extended Mode Register set cycle is issued to ... */

	/* Step#10 The application must go into Normal Mode, setting Mode to 0 in the Mode Register
	   and perform a write access at any location in the SDRAM. */
	sdramc_writel(SDRAMC_MR, AT91C_SDRAMC_MODE_NORMAL);	// Set Normal mode
	writel(0x00000000, sdram_address);	// Perform Normal mode

	/* Step#11 Write the refresh rate into the count field in the SDRAMC Refresh Timer Rgister. */
	sdramc_writel(SDRAMC_TR, sdramc_config->tr);

	return 0;
}
