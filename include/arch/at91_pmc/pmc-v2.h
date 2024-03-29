/*
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_PMC_V2_H__
#define __AT91_PMC_V2_H__

#define PMC_PLL_CTRL0		0x0C		/* PLL Control Register 0 */
#define AT91C_PLL_CTRL0_DIVPMC	(0xFFUL << 0)
#define		AT91C_PLL_CTRL0_DIVPMC_(x)	((x) << 0)
#define AT91C_PLL_CTRL0_DIVIO	(0x0UL << 12)
#define		AT91C_PLL_CTRL0_DIVIO_(x)	((0) << 12)
#define AT91C_PLL_CTRL0_ENPLL	(0x1UL << 28)
#define AT91C_PLL_CTRL0_ENPLLCK	(0x1UL << 29)
#define AT91C_PLL_CTRL0_ENIOPLLCK (0x0UL << 30)
#define AT91C_PLL_CTRL0_ENLOCK	(0x1UL << 31)

#define PMC_PLL_CTRL1		0x10		/* PLL Control Register 1 */
#define AT91C_PLL_CTRL1_FRACR	(0x3FFFFFUL << 0)
#define		AT91C_PLL_CTRL1_FRACR_(x)	((x) << 0)
#define AT91C_PLL_CTRL1_MUL	(0xFFUL << 24)
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
#define AT91C_PLL_ACR_LOCK_THR	(0x7UL << 16)
#define		AT91C_PLL_ACR_LOCK_THR_(x)	((x) << 16)
#define AT91C_PLL_ACR_LOOP_FILTER (0x3FUL << 24)
#define		AT91C_PLL_ACR_LOOP_FILTER_(x)	((x) << 24)
#define AT91C_PLL_ACR_DEFAULT_UTMI	0x12020010UL
#define AT91C_PLL_ACR_DEFAULT_PLLA	0x20010UL

#define PMC_PLL_UPDT		0x1c		/* PLL Update Register */
#define AT91C_PLL_UPDT_ID	(0xFUL << 0)
#define		AT91C_PLL_UPDT_ID_(x)	((x) << 0)
#define AT91C_PLL_UPDT_UPDATE	(0x1UL << 8)
#define AT91C_PLL_UPDT_STUPTIM	(0x3FUL << 16)
#define AT91C_PLL_UPDT_STUPTIM_(x) ((x) << 16)

#define PMC_MCKR		0x28		/* Master Clock Register */
#define AT91C_PMC_CSS		(0x3UL <<  0)
#define 	AT91C_PMC_CSS_SLOW_CLK		(0x0UL)
#define 	AT91C_PMC_CSS_MAIN_CLK		(0x1UL)
#define 	AT91C_PMC_CSS_PLLA_CLK		(0x2UL)
#define 	AT91C_PMC_CSS_UPLL_CLK		(0x3UL)
#define	AT91C_PMC_PRES		(0x7UL << 4)
#define		AT91C_PMC_PRES_CLK		(0x0UL << 4)
#define		AT91C_PMC_PRES_CLK_2		(0x1UL << 4)
#define		AT91C_PMC_PRES_CLK_4		(0x2UL << 4)
#define		AT91C_PMC_PRES_CLK_8		(0x3UL << 4)
#define		AT91C_PMC_PRES_CLK_16		(0x4UL << 4)
#define		AT91C_PMC_PRES_CLK_32		(0x5UL << 4)
#define		AT91C_PMC_PRES_CLK_64		(0x6UL << 4)
#define		AT91C_PMC_PRES_CLK_3		(0x7UL << 4)
#define AT91C_PMC_MDIV		(0x3UL <<  8)
#define 	AT91C_PMC_MDIV_1		(0x0UL <<  8)
#define 	AT91C_PMC_MDIV_2		(0x1UL <<  8)
#define 	AT91C_PMC_MDIV_4		(0x2UL <<  8)
#define 	AT91C_PMC_MDIV_3		(0x3UL <<  8)
#define AT91C_PMC_PLLADIV2	(0x0)
#define AT91C_PMC_H32MXDIV	(0x0)

#define PMC_PCR			0x88		/* Peripheral Control Register */
#define	AT91C_PMC_PID		(0x7FUL << 0)
#define	AT91C_PMC_GCKCSS	(0x1FUL << 8)
#define		AT91C_PMC_GCKCSS_MD_SLOW_CLK	(0x0UL << 8)
#define		AT91C_PMC_GCKCSS_SLOW_CLK	(0x1UL << 8)
#define		AT91C_PMC_GCKCSS_MAIN_CLK	(0x2UL << 8)
#define		AT91C_PMC_GCKCSS_MCK_CLK	(0x3UL << 8)
#define		AT91C_PMC_GCKCSS_PLLA_CLK	(0x4UL << 8)
#define		AT91C_PMC_GCKCSS_UPLL_CLK	(0x5UL << 8)
#define		AT91C_PMC_GCKCSS_PLLADIV2_CLK	(0x8UL << 8)
#define	AT91C_PMC_DIV		(0)
#define		AT91C_PMC_DIV_(x)		(0)
#define	AT91C_PMC_GCKDIV	(0xFFUL << 20)
#define		AT91C_PMC_GCKDIV_MSK		0xFF
#define		AT91C_PMC_GCKDIV_OFFSET		20
#define		AT91C_PMC_GCKDIV_(x)		(((x) & AT91C_PMC_GCKDIV_MSK) << AT91C_PMC_GCKDIV_OFFSET)
#define	AT91C_PMC_EN		(0x1UL << 28)
#define	AT91C_PMC_GCKEN		(0x1UL << 29)
#define	AT91C_PMC_CMD		(0x1UL << 31)

#define PMC_GCSR0		0xC0		/* Generic Clock Status Register 0 */
#define PMC_GCSR1		0xC4		/* Generic Clock Status Register 1 */
#define PMC_GCSR2		0xC8		/* Generic Clock Status Register 2 */
#define PMC_GCSR3		0xCC		/* Generic Clock Status Register 3 */

#define PMC_PLL_ISR0		0xEC		/* PLL Interrupt Status Register 0 */
#define AT91C_PLL_ISR0_LOCKA	(0x1UL << 0)

#define PMC_PLL_ISR1		0xF0		/* PLL Interrupt Status Register 1 */

#endif

