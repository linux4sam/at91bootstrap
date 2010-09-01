/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation

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
 * File Name           : at91sam9g45ekes.h
 * Object              :
 * Creation            : PVz June 2009
 *-----------------------------------------------------------------------------
 */
#ifndef _AT91SAM9G45EKES_H
#define _AT91SAM9G45EKES_H

/* ******************************************************************* */
/* PMC Settings                                                        */
/*                                                                     */
/* The main oscillator is enabled as soon as possible in the c_startup */
/* and MCK is switched on the main oscillator.                         */
/* PLL initialization is done later in the hw_init() function          */
/* ******************************************************************* */
#define MASTER_CLOCK		(132096000)
#define PLL_LOCK_TIMEOUT	1000000

#define BOARD_MAINOSC           12000000
#define BOARD_MCK               ((unsigned long)((BOARD_MAINOSC / 3 / 2 / 3) * 200 ))   // 133MHz
#define BOARD_OSCOUNT           (AT91C_CKGR_OSCOUNT & (64 << 8))
#define BOARD_CKGR_PLLA         (AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT         (0x3F << 8)
#define BOARD_MULA              (AT91C_CKGR_MULA & (199 << 16))
#define BOARD_DIVA              (AT91C_CKGR_DIVA & 3)
#define BOARD_PRESCALER         (0x00001301)

#define PLLA_SETTINGS           ( BOARD_CKGR_PLLA \
                                | BOARD_PLLACOUNT \
                                | BOARD_MULA \
                                | BOARD_DIVA)

//#define PLLA_SETTINGS 0x202A3F01
#define PLLUTMI
#define PLLUTMI_SETTINGS	0x10193F05

/* Switch MCK on PLLA output PCK = PLLA/2 = 3 * MCK */
//#define MCKR_SETTINGS         0x1300
#define MCKR_CSS_SETTINGS	0x1302
//(AT91C_PMC_CSS_PLLA_CLK | MCKR_SETTINGS)

/* ******************************************************************* */
/* DataFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_BASE_SPI	AT91C_BASE_SPI0
#define AT91C_ID_SPI	AT91C_ID_SPI0

/* AC characteristics */
/* DLYBS = tCSS= 250ns min and DLYBCT = tCSH = 250ns */
#define DATAFLASH_TCSS		(0x22 << 16)
#define DATAFLASH_TCHS		(0x1 << 24)

#define DF_CS_SETTINGS 		(AT91C_SPI_NCPHA | (AT91C_SPI_DLYBS & DATAFLASH_TCSS) | (AT91C_SPI_DLYBCT & DATAFLASH_TCHS) | ((MASTER_CLOCK / AT91C_SPI_CLK) << 8))

/* ******************************************************************* */
/* NandFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_SMARTMEDIA_BASE	0x40000000

#define AT91_SMART_MEDIA_ALE    (1 << 21)       /* our ALE is AD21 */
#define AT91_SMART_MEDIA_CLE    (1 << 22)       /* our CLE is AD22 */

#define NAND_DISABLE_CE() do { *(volatile unsigned int *)AT91C_PIOC_SODR = AT91C_PIO_PC14;} while(0)
#define NAND_ENABLE_CE() do { *(volatile unsigned int *)AT91C_PIOC_CODR = AT91C_PIO_PC14;} while(0)

#define NAND_WAIT_READY() while (!(*(volatile unsigned int *)AT91C_PIOC_PDSR & AT91C_PIO_PC8))

/* ******************************************************************** */
/* SMC Chip Select 3 Timings for NandFlash for MASTER_CLOCK = 133000000.*/
/* Please refer to SMC section in AT91SAM9 datasheet to learn how 	*/
/* to generate these values. 						*/
/* ******************************************************************** */
#define AT91C_SM_NWE_SETUP	(2 << 0)
#define AT91C_SM_NCS_WR_SETUP	(0 << 8)
#define AT91C_SM_NRD_SETUP	(2 << 16)
#define AT91C_SM_NCS_RD_SETUP	(0 << 24)

#define AT91C_SM_NWE_PULSE 	(4 << 0)
#define AT91C_SM_NCS_WR_PULSE	(4 << 8)
#define AT91C_SM_NRD_PULSE	(4 << 16)
#define AT91C_SM_NCS_RD_PULSE	(4 << 24)

#define AT91C_SM_NWE_CYCLE 	(7 << 0)
#define AT91C_SM_NRD_CYCLE	(7 << 16)

#define AT91C_SM_TDF	        (3 << 16)

#define	DEBUG

#define BOARD_SD_PIN_CD \
    {AT91C_PIO_PD10, AT91C_BASE_PIOD, AT91C_ID_PIOD_E, PIO_INPUT, PIO_PULLUP}

#define BOARD_SD_PINS \
    {(0x3E <<  0), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x1 <<  0), AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

#endif                          /* _AT91SAM9G45EKES_H */
