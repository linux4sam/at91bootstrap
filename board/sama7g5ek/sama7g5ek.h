/* ----------------------------------------------------------------------------
 *         Microchip Technology AT91Bootstrap project
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip Technology Inc. and its subsidiaries
 *
 * All rights reserved.
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

#ifndef __SAMA7G5EK_H__
#define __SAMA7G5EK_H__

#ifdef CONFIG_FLEXCOM
#include "flexcom.h"
#endif

#define BOARD_PRESCALER_CPUPLL	(AT91C_PMC_PRES_CLK | \
				AT91C_PMC_MDIV_4 | \
				AT91C_PMC_CSS_CPUPLL_CLK)

#define BOARD_PRESCALER_MCK1	(AT91C_MCR_MASTER_DIV2 | \
				AT91C_MCR_CSS_SYSPLL_CLK | \
				AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK2	(AT91C_MCR_MASTER_DIV1 | \
				AT91C_MCR_CSS_DDRPLL_CLK | \
				AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK4	(AT91C_MCR_MASTER_DIV1 | \
				AT91C_MCR_CSS_SYSPLL_CLK | \
				AT91C_MCR_EN)

#define MASTER_CLOCK			200000000
#define BOARD_MAINOSC			24000000

#define CONFIG_SYS_BASE_TZC400		AT91C_BASE_TZC400
#define TZC400_BASE			CONFIG_SYS_BASE_TZC400

#ifdef CONFIG_FLEXCOM
#define USART_BASE			(AT91C_BASE_FLEXCOM3 + AT91C_OFFSET_FLEXCOM_USART)
#endif

#define CONFIG_SYS_DBGU_RXD_PIN		AT91C_PIN_PD(17)
#define CONFIG_SYS_DBGU_TXD_PIN		AT91C_PIN_PD(16)

#define CONFIG_SYS_BASE_PUBL		AT91C_BASE_PUBL
#define CONFIG_SYS_BASE_UMCTL2		AT91C_BASE_UMCTL2
#define CONFIG_SYS_BASE_UMCTL2_MP	AT91C_BASE_UMCTL2_MP

#define CONFIG_SYS_BASE_SDHC		AT91C_BASE_SDMMC1
#define	CONFIG_SYS_ID_SDHC		AT91C_ID_SDMMC1

#define _tRFC		350UL		/* Refresh to Refresh, ns */
#define _tREFI		7800UL		/* Refresh Intervals, ns */
#define _tWR		15UL		/* Write Recovery, ns */
#define _tRP		14UL		/* Row Precharge command, ns */
#define _tRP_ps		13125UL		/* Row Precharge command, ps */
#define _tRCD		14UL		/* Row to Column delay, ns */
#define _tRCD_ps	13125UL		/* Row to Column delay, ps */
#define _tRAS		38UL		/* Row Active Strobe, ns */
#define _tRASMAX	70000UL		/* RAS max, ns */
#define _tRC_ps		50625UL		/* Row Cycle, ps */
#define _tFAW		50UL		/* Four Activation Window, ns */
#define _tPRECKE	500000UL
#define _CL		7UL		/* CAS Latency, Clock cycles */
#define _CWL		6UL		/* CAS Write Latency, Clock cycles */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _TZQOPER	256UL		/* TZQ Long Calibration, Clock cycles */
#define _TZQCS		64UL		/* TZQ Short Calibration, Clock cycles */
#endif
