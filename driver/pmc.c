/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "hardware.h"
#include "arch/at91_pmc.h"

static inline void write_pmc(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_PMC);
}

static inline unsigned int read_pmc(unsigned int offset)
{
	return readl(offset + AT91C_BASE_PMC);
}

void die()
{
	for (;;) ;
}

void lowlevel_clock_init()
{
#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(AT91SAMA5D3X) 
	unsigned long tmp;

	/* Enable external crystal */
	tmp = read_pmc(PMC_MOR);
	if ((tmp & AT91C_CKGR_MOSCXTEN) == 0) {
		write_pmc(PMC_MOR,
			(0x37 << 16) 
			| AT91C_CKGR_MOSCXTEN 
			| (0x40 << 8) 
			| AT91C_CKGR_MOSCSEL);

		/* Wait until Main Oscillator is stable */
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS)) ;
	}

	/* Switch to external crystal if needed */
	tmp = read_pmc(PMC_MCKR);
	if ((tmp & AT91C_PMC_CSS) != AT91C_PMC_CSS_MAIN_CLK) {
		tmp &= ~AT91C_PMC_CSS;
		tmp |= AT91C_PMC_CSS_MAIN_CLK;
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}
#else
	if (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS)) {
		
		/* Enable Main Oscillator */
		write_pmc(PMC_MOR, AT91C_CKGR_MOSCXTEN | (0x40 << 8));

		/* Wait until Main Oscillator is stable */
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS)) ;
	}
	
	/* After stablization, switch to Main Oscillator */
	if ((read_pmc(PMC_MCKR) & AT91C_PMC_CSS) == AT91C_PMC_CSS_SLOW_CLK) {
		unsigned long tmp;

		tmp = read_pmc(PMC_MCKR);
		tmp &= ~AT91C_PMC_CSS;
		tmp |= AT91C_PMC_CSS_MAIN_CLK;
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;

		tmp &= ~AT91C_PMC_PRES;
		tmp |= AT91C_PMC_PRES_CLK;
		write_pmc(PMC_MCKR, tmp);
		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;
	}
#endif

	return;
}

int pmc_cfg_plla(unsigned int pmc_pllar, unsigned int timeout)
{
#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(AT91SAMA5D3X)
	write_pmc(PMC_PLLAR, 0);
	write_pmc(PMC_PLLAR, pmc_pllar);
	//while ((timeout--) && !(read_pmc(PMC_SR) & AT91C_PMC_LOCKA))
	while (!(read_pmc(PMC_SR) & AT91C_PMC_LOCKA)) ;
	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;

	return 0;
#else
	write_pmc((unsigned int)PMC_PLLAR, pmc_pllar);

	while ((timeout--) && !(read_pmc(PMC_SR) & AT91C_PMC_LOCKA)) ;
	return (timeout) ? 0 : (-1);
#endif
}

#ifndef PLLUTMI
int pmc_cfg_pllb(unsigned int pmc_pllbr, unsigned int timeout)
{
	write_pmc(PMC_PLLBR, pmc_pllbr);
	while ((timeout--) && !(read_pmc(PMC_SR) & AT91C_PMC_LOCKB)) ;

	return (timeout) ? 0 : (-1);
}
#else
int pmc_cfg_pllutmi(unsigned int pmc_pllutmi, unsigned int timeout)
{
	return 0;
}
#endif

int pmc_cfg_mck(unsigned int pmc_mckr, unsigned int timeout)
{
	write_pmc(PMC_MCKR, pmc_mckr);
	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY)) ;

	return (timeout) ? 0 : (-1);
}

int pmc_cfg_pck(unsigned char x, unsigned int clk_sel, unsigned int prescaler)
{
	write_pmc(PMC_PCKR + x * 4, clk_sel | prescaler);
	write_pmc(PMC_SCER, 1 << (x + 8));
	while (!(read_pmc(PMC_SR) & (1 << (x + 8)))) ;

	return 0;
}
