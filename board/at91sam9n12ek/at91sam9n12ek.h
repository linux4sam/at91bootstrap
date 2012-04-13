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
 * File Name           : at91sam9n12ek.h
 * Object              :
 * Creation            : HXu Aug. 2011
 *-----------------------------------------------------------------------------
 */
#ifndef _AT91SAM9N12EK_H_
#define _AT91SAM9N12EK_H_

/* 
 * PMC Settings
 *
 * The main oscillator is enabled as soon as possible in the lowlevel_clock_init
 * and MCK is switched on the main oscillator.                                  
 * PLL initialization is done later in the hw_init() function
 */
#define MASTER_CLOCK		(132096000)
#define PLL_LOCK_TIMEOUT	10000

#define BOARD_MAINOSC		16000000
#define BOARD_MCK		133000000
#define BOARD_OSCOUNT		(AT91C_CKGR_OSCOUNT & (64 << 8))
#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
//#define BOARD_MULA		(AT91C_CKGR_MULA & (199 << 16))
#define BOARD_MULA		(AT91C_CKGR_MULA & (149 << 16))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 3)

#define BOARD_PRESCALER_MAIN_CLOCK	(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_MAIN_CLK)

#define BOARD_PRESCALER_PLLA		(AT91C_PMC_PLLADIV2_2 \
					| AT91C_PMC_MDIV_3 \
					| AT91C_PMC_CSS_PLLA_CLK)

#define PLLA_SETTINGS	(BOARD_CKGR_PLLA \
			| BOARD_PLLACOUNT \
			| BOARD_MULA \
			| BOARD_DIVA)
/*
#define PLLUTMI
#define PLLUTMI_SETTINGS	0x10193F05
*/

/*
* DataFlash Settings
*/
#define CONFIG_SPI_CLOCK	AT91C_SPI_CLK
#define CONFIG_SPI_BUS		0
#define CONFIG_SPI_CS		0
//#define CONFIG_SPI_MAX_H	1000000
#define CONFIG_SPI_MODE		SPI_MODE_3

/*
 * NandFlash Settings
 */
#define AT91C_SMARTMEDIA_BASE	0x40000000

#define AT91_SMART_MEDIA_ALE    (1 << 21)       /* our ALE is AD21 */
#define AT91_SMART_MEDIA_CLE    (1 << 22)       /* our CLE is AD22 */

#define CONFIG_SYS_NAND_ENABLE_PIN	AT91C_PIN_PD(4)
#define CONFIG_SYS_NAND_READY_PIN	AT91C_PIN_PD(5)

/*
 * MCI Settings
 */
#define BOARD_SD_PINS \
    {(0x01 << 16), AT91C_BASE_PIOA, AT91C_ID_PIOA_B, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x39 << 15), AT91C_BASE_PIOA, AT91C_ID_PIOA_B, PIO_PERIPH_A, PIO_PULLUP}, \
    {(0x01 << 17), AT91C_BASE_PIOA, AT91C_ID_PIOA_B, PIO_PERIPH_A, PIO_DEFAULT}

/* function */
extern void hw_init(void);

extern void nandflash_hw_init(void);
extern void nandflash_config_buswidth(unsigned char busw);

extern void at91_spi0_hw_init(void);
extern void spi_cs_activate(int cs);
extern void spi_cs_deactivate(int cs);

#endif /* #ifndef _AT91SAM9N12EK_H_ */
