// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "backup.h"
#include "debug.h"
#include "hardware.h"
#include "arch/tzc400.h"
#include "umctl2.h"

static void tzc400_info(int base)
{
	unsigned int build_config = read_tzc400(TZC400_BUILDCONFIG);

	dbg_very_loud("TZC400: controller @%x:", base);

	dbg_very_loud(" no_of_regions: ");
	dbg_very_loud("%u", (build_config & TZC_BUILD_CONFIG_REGIONS_MASK) + 1);

	dbg_very_loud(" addr_width: ");
	dbg_very_loud("%u bits",
		   ((build_config & TZC_BUILD_CONFIG_ADDRESS_WIDTH_MASK) >> 8) + 1);

	dbg_very_loud(" no_of_filters: ");
	dbg_very_loud("%u\n",
		   ((build_config & TZC_BUILD_CONFIG_NO_OF_FILTERS_MASK) >> 24) + 1);
}

static void tzc400_configure(int base)
{
#ifdef CONFIG_DEBUG
	tzc400_info(base);
#endif

	/* enable interrupts and error response on region permission failure */
	write_tzc400(TZC400_ACTION, TZC400_ACTION_REACTION_VALUE_INT_ERR);

#ifdef CONFIG_TZC400_SPECULATIVE_LOAD
	dbg_very_loud("TZC400: speculative load is enabled\n");
	/* default, but let's make it explicit */
	write_tzc400(TZC400_SPECULATION_CTRL, 0x0);
#else
	dbg_very_loud("TZC400: speculative load is disabled\n");
	write_tzc400(TZC400_SPECULATION_CTRL, TZC400_SPECULATION_CTRL_READ_DIS |
						TZC400_SPECULATION_CTRL_WRITE_DIS);
#endif

	/* Region 0 is the default and includes the whole memory map */
	/* Block secure access to Region 0 */
	write_tzc400(TZC400_REGION_ATTRIBUTES(0), 0x0);
	/* Block nonsecure access to Region 0 */
	write_tzc400(TZC400_REGION_ID_ACCESS(0), 0x0);

#ifdef CONFIG_TZC400_SIMPLE_PROFILE
	dbg_very_loud("TZC400: creating simple TZC400 Profile\n");
	dbg_very_loud("TZC400: 1 region comprising full DDR range %x:%x\n",
			AT91C_BASE_DDRCS, (unsigned int)AT91C_BASE_DDRCS + (unsigned int)get_ddram_size());

	/* Configuring region bounds */
	write_tzc400(TZC400_REGION_BASE_LOW(1), AT91C_BASE_DDRCS);
	write_tzc400(TZC400_REGION_BASE_HIGH(1), 0x0);
	write_tzc400(TZC400_REGION_TOP_LOW(1),
		((unsigned int)AT91C_BASE_DDRCS + (unsigned int)get_ddram_size()) | 0xFFF);
	write_tzc400(TZC400_REGION_TOP_HIGH(1), 0x0);

	/* Allow secure access */
	write_tzc400(TZC400_REGION_ATTRIBUTES(1),
			TZC400_REGION_ATTRIBUTES_S_RD_EN | TZC400_REGION_ATTRIBUTES_S_WR_EN |
	/* Associate all filters */
			TZC400_REGION_ATTRIBUTES_FILTER_EN_ALL);

	/* Allow nonsecure access */
	write_tzc400(TZC400_REGION_ID_ACCESS(1),
			TZC400_REGION_ID_ACCESS_NS_RD_EN | TZC400_REGION_ID_ACCESS_NS_WR_EN);
#endif
	/* Configure Gatekeeper to allow on all filters */
	write_tzc400(TZC400_GATE_KEEPER, TZC400_GATE_KEEPER_OPEN_ALL_FILTER);
}

void tzc400_init()
{
	/* There is one TZC controller at BASE, and another right next to it */
	tzc400_configure(TZC400_BASE);
	tzc400_configure(TZC400_BASE + 0x1000);

	if (!backup_resume())
		dbg_printf("TZC400: Initialization complete.\n");
}
