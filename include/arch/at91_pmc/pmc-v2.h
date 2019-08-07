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
#ifndef __AT91_PMC_V2_H__
#define __AT91_PMC_V2_H__

#define PMC_PLL_CTRL0		0x0C		/* PLL Control Register 0 */
#define AT91C_PLL_CTRL0_DIVPMC	(0xFFUL << 0)
#define		AT91C_PLL_CTRL0_DIVPMC_(x)	((x) << 0)
#define AT91C_PLL_CTRL0_DIVIO	(0xFFUL << 12)
#define		AT91C_PLL_CTRL0_DIVIO_(x)	((x) << 12)
#define AT91C_PLL_CTRL0_ENPLL	(0x1UL << 28)
#define AT91C_PLL_CTRL0_ENPLLCK	(0x1UL << 29)
#define AT91C_PLL_CTRL0_ENLOCK	(0x1UL << 31)

#define PMC_PLL_CTRL1		0x10		/* PLL Control Register 1 */
#define AT91C_PLL_CTRL1_FRACR	(0x3FFFFFUL << 0)
#define		AT91C_PLL_CTRL1_FRACR_(x)	((x) << 0)
#define AT91C_PLL_CTRL1_MUL	(0x7FUL << 24)
#define		AT91C_PLL_CTRL1_MUL_(x)		((x) << 24)

#define PMC_PLL_SSR		0x14		/* PLL Spread Spectrum Register */
#define AT91C_PLL_SSR_STEP	(0xFFFFUL << 0)
#define		AT91C_PLL_SSR_STEP_(x)		((x) << 0)
#define AT91C_PLL_SSR_NSTEP	(0xFFUL << 16)
#define		AT91C_PLL_SSR_NSTEP_(x)		((x) << 16)
#define AT91C_PLL_SSR_ENSPREAD	(0x1UL << 28)

#define PMC_PLL_ACR		0x18		/* PLL Analog Control Register */
#define AT91C_PLL_ACR_CONTROL	(0xFFFUL << 0)
#define		AT91C_PLL_ACR_CONTROL_(x)	((x) << 0)
#define AT91C_PLL_ACR_UTMIVR	(0x1UL << 12)
#define AT91C_PLL_ACR_UTMIBG	(0x1UL << 13)
#define AT91C_PLL_ACR_LOCK_THR	(0xFFUL << 16)
#define		AT91C_PLL_ACR_LOCK_THR_(x)	((x) << 16)
#define AT91C_PLL_ACR_LOOP_FILTER (0xFFUL << 24)
#define		AT91C_PLL_ACR_LOOP_FILTER_(x)	((x) << 24)
#define AT91C_PLL_ACR_DEFAULT	0x1b040010UL

#define PMC_PLL_UPDT		0x1c		/* PLL Update Register */
#define AT91C_PLL_UPDT_ID	(0xFUL << 0)
#define		AT91C_PLL_UPDT_ID_(x)	((x) << 0)
#define AT91C_PLL_UPDT_UPDATE	(0x1UL << 8)
#define AT91C_PLL_UPDT_STUPTIM	(0xFFUL << 16)
#define AT91C_PLL_UPDT_STUPTIM_(x) ((x) << 16)

#endif

