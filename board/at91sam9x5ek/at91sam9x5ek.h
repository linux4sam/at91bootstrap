/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
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
 * ----------------------------------------------------------------------------
 * File Name           : at91sam9x5ek.h
 * Object              :
 * Creation            : HXu Aug. 2010
 *-----------------------------------------------------------------------------
 */
#ifndef _AT91SAM9X5EK_H
#define _AT91SAM9X5EK_H

/* ***************************************************************************** */
/* PMC Settings                                                                  */
/*                                                                               */
/* The main oscillator is enabled as soon as possible in the lowlevel_clock_init */
/* and MCK is switched on the main oscillator.                                   */
/* PLL initialization is done later in the hw_init() function                    */
/* ***************************************************************************** */
#define MASTER_CLOCK		(132096000)
#define PLL_LOCK_TIMEOUT	10000

#define BOARD_MAINOSC               12000000
#define BOARD_MCK                   ((unsigned long)((BOARD_MAINOSC / 3 / 2 / 3) * 200 ))       // 133MHz
#define BOARD_OSCOUNT               (AT91C_CKGR_OSCOUNT & (64 << 8))
#define BOARD_CKGR_PLLA             (AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT             (0x3F << 8)
#define BOARD_MULA                  (AT91C_CKGR_MULA & (199 << 16))
#define BOARD_DIVA                  (AT91C_CKGR_DIVA & 3)

#define BOARD_PRESCALER_MAIN_CLOCK  (AT91C_PMC_PLLADIV2_2 | AT91C_PMC_MDIV_3 | AT91C_PMC_CSS_MAIN_CLK)
#define BOARD_PRESCALER_PLLA        (AT91C_PMC_PLLADIV2_2 | AT91C_PMC_MDIV_3 | AT91C_PMC_CSS_PLLA_CLK)

#define PLLA_SETTINGS           ( BOARD_CKGR_PLLA \
                                | BOARD_PLLACOUNT \
                                | BOARD_MULA \
                                | BOARD_DIVA)

#define PLLUTMI
#define PLLUTMI_SETTINGS	0x10193F05

/* ******************************************************************* */
/* DataFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_BASE_SPI	AT91C_BASE_SPI0
#define AT91C_ID_SPI	AT91C_ID_SPI0

#define DF_CS_SETTINGS	(AT91C_SPI_CPOL | ((MASTER_CLOCK / AT91C_SPI_CLK) << 8))

/* ******************************************************************* */
/* NandFlash Settings                                                  */
/* ******************************************************************* */
#define AT91C_SMARTMEDIA_BASE	0x40000000

#define AT91_SMART_MEDIA_ALE    (1 << 21)       /* our ALE is AD21 */
#define AT91_SMART_MEDIA_CLE    (1 << 22)       /* our CLE is AD22 */

#define NAND_DISABLE_CE() do { *(volatile unsigned int *)AT91C_PIOD_SODR = AT91C_PIO_PD4;} while(0)
#define NAND_ENABLE_CE() do { *(volatile unsigned int *)AT91C_PIOD_CODR = AT91C_PIO_PD4;} while(0)

/* ******************************************************************** */
/* SMC Chip Select 3 Timings for NandFlash for MASTER_CLOCK = 133000000 */
/* Please refer to SMC section in AT91SAM9 datasheet to learn how       */
/* to generate these values.                                            */
/* ******************************************************************** */
#define AT91C_SM_NWE_SETUP	(1 << 0)
#define AT91C_SM_NCS_WR_SETUP	(0 << 8)
#define AT91C_SM_NRD_SETUP	(1 << 16)
#define AT91C_SM_NCS_RD_SETUP	(0 << 24)

#define AT91C_SM_NWE_PULSE 	(3 << 0)
#define AT91C_SM_NCS_WR_PULSE	(5 << 8)
#define AT91C_SM_NRD_PULSE	(4 << 16)
#define AT91C_SM_NCS_RD_PULSE	(6 << 24)

#define AT91C_SM_NWE_CYCLE 	(5 << 0)
#define AT91C_SM_NRD_CYCLE	(6 << 16)

#define AT91C_SM_TDF	        (1 << 16)

#define BOARD_SD_PINS \
    {(0x1D << 16), AT91C_BASE_PIOA, AT91C_ID_PIOA_B, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x01 << 15), AT91C_BASE_PIOA, AT91C_ID_PIOA_B, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x01 << 17), AT91C_BASE_PIOA, AT91C_ID_PIOA_B, PIO_PERIPH_A, PIO_DEFAULT}

#endif                          /* _AT91SAM9X5EK_H */
