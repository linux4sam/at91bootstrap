/* ----------------------------------------------------------------------------
 *         Microchip Microprocessor (MPU) Software Team
 * ----------------------------------------------------------------------------
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Microchip's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "board.h"
#include "clk-common.h"
#include "arch/at91_pmc/pmc.h"

void pmc_cfg_mck(unsigned int pmc_mckr)
{
	unsigned int tmp;

	/*
	 * Program the PRES field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~(0x1 << 13));
#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(SAMA5D3X) \
	|| defined(SAMA5D4) || defined(SAMA5D2)
	tmp &= (~AT91C_PMC_ALT_PRES);
	tmp |= (pmc_mckr & AT91C_PMC_ALT_PRES);
#else
	tmp &= (~AT91C_PMC_PRES);
	tmp |= (pmc_mckr & AT91C_PMC_PRES);
#endif
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the MDIV field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_MDIV);
	tmp |= (pmc_mckr & AT91C_PMC_MDIV);
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the PLLADIV2 field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_PLLADIV2);
	tmp |= (pmc_mckr & AT91C_PMC_PLLADIV2);
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the H32MXDIV field in the PMC_MCKR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_H32MXDIV);
	tmp |= (pmc_mckr & AT91C_PMC_H32MXDIV);
	write_pmc(PMC_MCKR, tmp);

	/*
	 * Program the CSS field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_CSS);
	tmp |= (pmc_mckr & AT91C_PMC_CSS);
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;
}

int pmc_check_mck_h32mxdiv(void)
{
#ifdef CPU_HAS_H32MXDIV
	return read_pmc(PMC_MCKR) & AT91C_PMC_H32MXDIV;
#else
	return 0;
#endif
}

