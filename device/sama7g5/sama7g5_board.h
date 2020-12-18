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
				AT91C_PMC_CSS_CPUPLL_CLK)

#define BOARD_PRESCALER_MCK1	(AT91C_MCR_MASTER_DIV2 | \
				AT91C_MCR_CSS_SYSPLL_CLK | \
				AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK1_CLEAN	(AT91C_MCR_MASTER_DIV4 | \
					AT91C_MCR_CSS_MCK0_CLK | \
					AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK2	(AT91C_MCR_MASTER_DIV1 | \
				AT91C_MCR_CSS_DDRPLL_CLK | \
				AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK3	(AT91C_MCR_MASTER_DIV1 | \
				AT91C_MCR_CSS_IMGPLL_CLK | \
				AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK4	(AT91C_MCR_MASTER_DIV1 | \
				AT91C_MCR_CSS_SYSPLL_CLK | \
				AT91C_MCR_EN)

#define BOARD_PRESCALER_MCK4_CLEAN	(AT91C_MCR_MASTER_DIV4 | \
					AT91C_MCR_CSS_MCK0_CLK | \
					AT91C_MCR_EN)

#define MASTER_CLOCK			200000000
#define BOARD_MAINOSC			24000000

#define CONFIG_SYS_BASE_TZC400		AT91C_BASE_TZC400
#define TZC400_BASE			CONFIG_SYS_BASE_TZC400

#define CONFIG_SYS_BASE_PUBL		AT91C_BASE_PUBL
#define CONFIG_SYS_BASE_UMCTL2		AT91C_BASE_UMCTL2
#define CONFIG_SYS_BASE_UMCTL2_MP	AT91C_BASE_UMCTL2_MP

#if defined(CONFIG_SDHC0)
#define CONFIG_SYS_BASE_SDHC		AT91C_BASE_SDMMC0
#define	CONFIG_SYS_ID_SDHC		AT91C_ID_SDMMC0
#elif defined(CONFIG_SDHC1)
#define CONFIG_SYS_BASE_SDHC		AT91C_BASE_SDMMC1
#define	CONFIG_SYS_ID_SDHC		AT91C_ID_SDMMC1
#endif

#endif
