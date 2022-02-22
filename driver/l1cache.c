// Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

/*
 * L1 Cache functions implementation for ARMv5-TE and ARMv7-A
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "barriers.h"
#include "cp15.h"
#include "l1cache.h"

#if defined(CONFIG_SAMA5D2) || defined(CONFIG_SAMA5D3X) || defined(CONFIG_SAMA5D4) || defined(CONFIG_SAM9X60)
/** L1 data cache line size in bytes */
#define L1_CACHE_BYTES (32u)

/** Number of ways of L1 data cache */
#define L1_CACHE_WAYS (4)

/** Number of sets of L1 data cache */
#if defined(CONFIG_SAM9X60)
#define L1_CACHE_SETS (128)
#else
#define L1_CACHE_SETS (256)
#endif

/** Build a set/way parameter for cache operations */
#define L1_CACHE_SETWAY(set, way) (((set) << 5) | ((way) << 30))
#endif

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

void icache_invalidate(void)
{
	cp15_icache_invalidate();
	isb();
}

void icache_enable(void)
{
	unsigned int sctlr = cp15_read_sctlr();
	if ((sctlr & CP15_SCTLR_I) == 0) {
		icache_invalidate();
		cp15_write_sctlr(sctlr | CP15_SCTLR_I);
	}
}

void icache_disable(void)
{
	unsigned int sctlr = cp15_read_sctlr();
	if (sctlr & CP15_SCTLR_I) {
		cp15_write_sctlr(sctlr & ~CP15_SCTLR_I);
		icache_invalidate();
	}
}

void dcache_enable(void)
{
	unsigned int sctlr = cp15_read_sctlr();
	if ((sctlr & CP15_SCTLR_C) == 0) {
		dcache_invalidate();
		cp15_write_sctlr(sctlr | CP15_SCTLR_C);
	}
}

void dcache_disable(void)
{
	unsigned int sctlr = cp15_read_sctlr();
	if (sctlr & CP15_SCTLR_C) {
		dcache_clean();
		cp15_write_sctlr(sctlr & ~CP15_SCTLR_C);
		dcache_invalidate();
	}
}

void dcache_invalidate(void)
{
	unsigned int set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			cp15_dcache_invalidate_setway(L1_CACHE_SETWAY(set, way));

	dsb();
}

void dcache_clean(void)
{
	unsigned int set, way;

	for (way = 0; way < L1_CACHE_WAYS; way++)
		for (set = 0; set < L1_CACHE_SETS; set++)
			cp15_dcache_clean_setway(L1_CACHE_SETWAY(set, way));

	dsb();
}

