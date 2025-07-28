/* ----------------------------------------------------------------------------
 *         Printarescu Labs
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Microchip Technology Inc. and its subsidiaries
 * Copyright (c) 2025, Printarescu Labs
 *
 * Based on at91sam9g10ek (AT91SAM9G10-EK) board support code.
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
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY WHATCLOUD "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL WHATCLOUD BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __GLASNOST_M9G10_H__
#define __GLASNOST_M9G10_H__

#if defined(CONFIG_CPU_CLK_266MHZ)  /* 133 MHz */

#define	MCK_133

#define MASTER_CLOCK		(266000000/2)

#define PLLA_SETTINGS		0x22DF3F33

#endif /* #if defined(CONFIG_CPU_CLK_266MHZ) */

/* Switch MCK on PLLA output PCK = PLLA = 2 * MCK */
#define MCKR_SETTINGS		((0x0 << 2) | AT91C_PMC_MDIV_2)
#define MCKR_CSS_SETTINGS	(AT91C_PMC_CSS_PLLA_CLK | MCKR_SETTINGS)

/*
 * MCI Settings
 */
#define CONFIG_SYS_BASE_MCI	AT91C_BASE_MCI

/*
 * Recovery Button
 */
#define CONFIG_SYS_RECOVERY_BUTTON_PIN	AT91C_PIN_PB(25)
#define RECOVERY_BUTTON_NAME	"USR1"

#endif /* #ifndef __GLASNOST_M9G10_H__*/
