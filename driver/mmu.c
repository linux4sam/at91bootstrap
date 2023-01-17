// Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include "barriers.h"
#include "cp15.h"
#include "l1cache.h"
#include "mmu_cp15.h"

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

void mmu_configure(void *tlb)
{
	/* only configure MMU when it is not enabled */
	if ((cp15_read_sctlr() & CP15_SCTLR_M) != 0)
		return;

	/* Translation Table Base Register 0 */
	cp15_write_ttbr0((unsigned int)tlb);

	/* Domain Access Register */
	/* only domain 15: access are not checked */
	cp15_write_dacr(0xC0000000);

	dsb();
	isb();
}

void mmu_enable(void)
{
	unsigned int control;

	control = cp15_read_sctlr();
	if ((control & CP15_SCTLR_M) == 0)
		cp15_write_sctlr(control | CP15_SCTLR_M);
}

void mmu_disable(void)
{
	unsigned int control;

	control = cp15_read_sctlr();
	if (control & CP15_SCTLR_M)
		cp15_write_sctlr(control & (~CP15_SCTLR_M));
}
