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
 * this list of conditions and the disclaiimer below.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the disclaimer below in the documentation and/or
 * other materials provided with the distribution.
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
 * File Name           : at91sam9260ek.h
 * Object              :
 * Creation            : NLe Jul 13th 2006
 *-----------------------------------------------------------------------------
 */
#ifndef _AFEB9260_H
#define _AFEB9260_H
#include	"spi.h"
#include 	"pll.h"

/* ******************************************************************* */
/* DataFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_BASE_SPI	AT91C_BASE_SPI0
#define AT91C_ID_SPI	AT91C_ID_SPI0

/* SPI CLOCK */
#define AT91C_SPI_CLK 		 5000000
/* AC characteristics */
/* DLYBS = tCSS= 250ns min and DLYBCT = tCSH = 250ns */
#define DATAFLASH_TCSS		(0x1a << 16)    /* 250ns min (tCSS) <=> 12/48000000 = 250ns */
#define DATAFLASH_TCHS		(0x1 << 24)     /* 250ns min (tCSH) <=> (64*1+SCBR)/(2*48000000) */

#define DF_CS_SETTINGS 		((SPI_MODE) | (AT91C_SPI_DLYBS & DATAFLASH_TCSS) | (AT91C_SPI_DLYBCT & DATAFLASH_TCHS) | ((MASTER_CLOCK / AT91C_SPI_CLK) << 8))

/* ******************************************************************* */
/* BootStrap Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define MACH_TYPE       	0x44B   /* AT91SAM9260-EK */

#define IMG_ADDRESS 		0x8400  /* Image Address in DataFlash */

#if	defined(IMG_SIZE)
#warning			"IMG_SIZE redefined"
#else
#define	IMG_SIZE		0x39000 /* Image Size in DataFlash    */
#endif

#if	defined(JUMP_ADDR)
#warning			"JUMP_ADDR redefined"
#else
#define JUMP_ADDR		0x21F00000      /* Final Jump Address         */
#endif

/* ******************************************************************* */
/* NandFlash Settings                                                  */
/*                                                                     */
/* ******************************************************************* */
#define AT91C_SMARTMEDIA_BASE	0x40000000

#define AT91_SMART_MEDIA_ALE    (1 << 21)       /* our ALE is AD21 */
#define AT91_SMART_MEDIA_CLE    (1 << 22)       /* our CLE is AD22 */

#define NAND_DISABLE_CE() do { *(volatile unsigned int *)AT91C_PIOC_SODR = AT91C_PIO_PC14;} while(0)
#define NAND_ENABLE_CE() do { *(volatile unsigned int *)AT91C_PIOC_CODR = AT91C_PIO_PC14;} while(0)

#define NAND_WAIT_READY() while (!(*(volatile unsigned int *)AT91C_PIOC_PDSR & AT91C_PIO_PC13))

/* ******************************************************************** */
/* SMC Chip Select 3 Timings for NandFlash for MASTER_CLOCK = 100000000.*/
/* Micron 16bits 256Mb for MASTER_CLOCK = 100000000.			*/
/* Please refer to SMC section in AT91SAM9261 datasheet to learn how 	*/
/* to generate these values. 						*/
/* ******************************************************************** */

#define AT91C_SM_NWE_SETUP	(2 << 0)
#define AT91C_SM_NCS_WR_SETUP	(2 << 8)
#define AT91C_SM_NRD_SETUP	(2 << 16)
#define AT91C_SM_NCS_RD_SETUP	(2 << 24)

#define AT91C_SM_NWE_PULSE 	(4 << 0)
#define AT91C_SM_NCS_WR_PULSE	(4 << 8)
#define AT91C_SM_NRD_PULSE	(4 << 16)
#define AT91C_SM_NCS_RD_PULSE	(4 << 24)

#define AT91C_SM_NWE_CYCLE 	(8 << 0)
#define AT91C_SM_NRD_CYCLE	(8 << 16)

#define AT91C_SM_TDF	        (2 << 16)

/* ******************************************************************* */
/* Application Settings                                                */
/* ******************************************************************* */
#define CFG_DEBUG
#define CFG_DATAFLASH
#define	CFG_SDRAM
#define	CFG_HW_INIT

#endif                          /* _AT91SAM9260EK_H */
