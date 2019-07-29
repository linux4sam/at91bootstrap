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
#ifndef __AT91_PMC_V1_H__
#define __AT91_PMC_V1_H__

#define PMC_PCR			0x10C		/* Peripheral Control Register */
#define	AT91C_PMC_PID		(0x3F << 0)
#define	AT91C_PMC_GCKCSS	(0x3 << 8)
#define		AT91C_PMC_GCKCSS_SLOW_CLK	(0x0 << 8)
#define		AT91C_PMC_GCKCSS_MAIN_CLK	(0x1 << 8)
#define		AT91C_PMC_GCKCSS_PLLA_CLK	(0x2 << 8)
#define		AT91C_PMC_GCKCSS_UPLL_CLK	(0x3 << 8)
#define		AT91C_PMC_GCKCSS_MCK_CLK	(0x4 << 8)
#define		AT91C_PMC_GCKCSS_AUDIO_CLK	(0x5 << 8)
#define	AT91C_PMC_CMD		(1 << 12)
#define	AT91C_PMC_DIV		(0x0)
#define	AT91C_PMC_GCKDIV	(0xff << 20)
#define		AT91C_PMC_GCKDIV_MSK		0xff
#define		AT91C_PMC_GCKDIV_OFFSET		20
#define		AT91C_PMC_GCKDIV_(x)		(((x) & AT91C_PMC_GCKDIV_MSK) << AT91C_PMC_GCKDIV_OFFSET)
#define	AT91C_PMC_EN		(0x1 << 28)
#define	AT91C_PMC_GCKEN		(0x1 << 29)

#endif
