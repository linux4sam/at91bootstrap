/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
 * File Name           : at91sam9261ek.h
 * Object              :
 * Creation            : NLe Jul 12th 2006
 *-----------------------------------------------------------------------------
 */
#ifndef _AT91SAM9RLEK_H
#define _AT91SAM9RLEK_H

/* ******************************************************************* */
/* PMC Settings                                                        */
/*                                                                     */
/* The main oscillator is enabled as soon as possible in the c_startup */
/* and MCK is switched on the main oscillator.                         */
/* PLL initialization is done later in the hw_init() function          */
/* ******************************************************************* */

#ifdef CONFIG_CPU_CLK_200MHZ

#define MCK_100

#define MASTER_CLOCK		(100000000)
#define	TOP_OF_MEMORY		0x310000
#define PLL_LOCK_TIMEOUT	1000000

#define PLL_SETTINGS		0x2031BF03

/* AC characteristics */
/* DLYBS = tCSS= 250ns min and DLYBCT = tCSH = 250ns */
#define DATAFLASH_TCSS		(0x1a << 16)    /* 250ns min (tCSS) <=> 12/48000000 = 250ns */
#define DATAFLASH_TCHS		(0x1 << 24)     /* 250ns min (tCSH) <=> (64*1+SCBR)/(2*48000000) */

#endif

#ifdef CONFIG_CPU_CLK_266MHZ

#define MCK_133

/* 133 MHz Bus clock */
#define MASTER_CLOCK		(133000000)
#define PLL_LOCK_TIMEOUT	1000000

#define PLL_SETTINGS		0x2109BF0C

#define DATAFLASH_TCSS		(0x1f << 16)    /* 250ns min (tCSS) <=> 12/48000000 = 250ns */
#define DATAFLASH_TCHS		(0x2 << 24)     /* 250ns min (tCSH) <=> (64*1+SCBR)/(2*48000000) */

#endif

/* Switch MCK on PLLA output PCK = PLLA = 2 * MCK */
#define MCKR_SETTINGS		(AT91C_PMC_PRES_CLK | AT91C_PMC_MDIV_2)
#define MCKR_CSS_SETTINGS	(AT91C_PMC_CSS_PLLA_CLK | MCKR_SETTINGS)

/* ******************************************************************* */
/* DataFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_BASE_SPI	AT91C_BASE_SPI0
#define AT91C_ID_SPI	AT91C_ID_SPI0

#define DF_CS_SETTINGS 		(AT91C_SPI_NCPHA | (AT91C_SPI_DLYBS & DATAFLASH_TCSS) | (AT91C_SPI_DLYBCT & DATAFLASH_TCHS) | ((MASTER_CLOCK / AT91C_SPI_CLK) << 8))

/* ******************************************************************* */
/* NandFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_SMARTMEDIA_BASE	0x40000000

#define AT91_SMART_MEDIA_ALE    (1 << 21)       /* our ALE is AD21 */
#define AT91_SMART_MEDIA_CLE    (1 << 22)       /* our CLE is AD22 */

#define NAND_DISABLE_CE() do { *(volatile unsigned int *)AT91C_PIOB_SODR = AT91C_PIO_PB6;} while(0)
#define NAND_ENABLE_CE() do { *(volatile unsigned int *)AT91C_PIOB_CODR = AT91C_PIO_PB6;} while(0)

#define NAND_WAIT_READY() while (!(*(volatile unsigned int *)AT91C_PIOD_PDSR & AT91C_PIO_PD17))

/* ******************************************************************** */
/* SMC Chip Select 3 Timings for NandFlash for MASTER_CLOCK = 100000000.*/
/* Please refer to SMC section in AT91SAM9RL datasheet to learn how 	*/
/* to generate these values. 						*/
/* ******************************************************************** */
#define AT91C_SM_NWE_SETUP	(1 << 0)
#define AT91C_SM_NCS_WR_SETUP	(0 << 8)
#define AT91C_SM_NRD_SETUP	(1 << 16)
#define AT91C_SM_NCS_RD_SETUP	(0 << 24)

#define AT91C_SM_NWE_PULSE 	(3 << 0)
#define AT91C_SM_NCS_WR_PULSE	(3 << 8)
#define AT91C_SM_NRD_PULSE	(3 << 16)
#define AT91C_SM_NCS_RD_PULSE	(3 << 24)

#define AT91C_SM_NWE_CYCLE 	(5 << 0)
#define AT91C_SM_NRD_CYCLE	(5 << 16)

#define AT91C_SM_TDF	        (2 << 16)

#define OP_BOOTSTRAP_MCI_on
#define BOARD_SD_PIN_CD \
    {1 << 15, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_INPUT, PIO_PULLUP}

#define BOARD_SD_PINS \
    {0x0000003B, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}, \
    {1 << 2, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

#define at91sam9rl
#endif                          /* _AT91SAM9RLEK_H */
