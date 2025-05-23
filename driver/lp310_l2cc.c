// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "arch/at91_sfr.h"
#include "arch/lp310_l2cc.h"

static inline void write_l2cc(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_L2CC);
}

static inline unsigned int read_l2cc(unsigned int offset)
{
	return readl(offset + AT91C_BASE_L2CC);
}

#ifdef CONFIG_SAMA5D2
static void l2cache_configure_ram(void)
{
	writel(0x1, SFR_L2CC_HRAMC + AT91C_BASE_SFR);
}
#else
static void l2cache_configure_ram(void) {}
#endif

void l2cache_prepare(void)
{
	unsigned int cfg;

	l2cache_configure_ram();

	/* disable cache if it hasn't been done yet */
	write_l2cc(L2CC_CR, 0x00);

	/* Auxiliary control register */
	/*
	 * Default values of Way size and Associativity are
	 * implementation defined (given by input pins).
	 * As a result, there should be no need to write them
	 * during this init sequence.
	 */
/*
	cfg = L2CC->L2CC_ACR;
	L2CC->L2CC_ACR = cfg;
*/
	/* L2CC global configuration */
	/* TAG, Data Latency Control: keep default */
/*
	cfg = L2CC->L2CC_TRCR;
	L2CC->L2CC_TRCR = cfg;
	cfg = L2CC->L2CC_DRCR;
	L2CC->L2CC_DRCR = cfg;
*/

	/* Prefetch Control */
	cfg = read_l2cc(L2CC_PCR);
	/* prefetch offset: TODO find proper values */
	cfg |= 0x1;
	cfg |= L2CC_PCR_PDEN;
	cfg |= L2CC_PCR_INSPEN;
	write_l2cc(L2CC_PCR, cfg);

	/* Power Control */
	cfg = read_l2cc(L2CC_POWCR);
	cfg |= L2CC_POWCR_STBYEN | L2CC_POWCR_DCKGATEN;
	write_l2cc(L2CC_POWCR, cfg);

	/* invalidate all entries */
	cfg = 0x0000ffff;
	write_l2cc(L2CC_IWR, cfg);
	/* check invalidate operation finished */
	while (read_l2cc(L2CC_IWR) != 0)
		;

	/* disable interrupts */
	write_l2cc(L2CC_IMR, 0);
	write_l2cc(L2CC_ICR, 0x01ff);

/*
	1.  Write to the Auxiliary, Tag RAM Latency, Data RAM Latency,
		Prefetch, and Power Control registers using a read-modify-write
			to set up global configurations:
	associativity, Way Size
	latencies for RAM accesses
	allocation policy
	prefetch and power capabilities.

	2. Secure write to the Invalidate by Way, offset 0x77C, to invalidate all entries in cache:
	   Write 0xFFFF to 0x77C
	   Poll cache maintenance register until invalidate operation is complete.
	3. Write to the Lockdown D and Lockdown I Register 9 if required.
	4. Write to interrupt clear register to clear any residual raw interrupts set.
	5. Write to the Interrupt Mask Register if you want to enable interrupts.
	6. Write to Control Register 1 with the LSB set to 1 to enable the cache.
*/
}

void l2cache_enable(void)
{
	/* enable cache, now! */
	write_l2cc(L2CC_CR, 1);
}
