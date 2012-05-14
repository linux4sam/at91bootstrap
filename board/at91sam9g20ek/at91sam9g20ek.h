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
 */
#ifndef __AT91SAM9G20EK_H__
#define __AT91SAM9G20EK_H__

/* ******************************************************************* */
/* PMC Settings                                                        */
/*                                                                     */
/* The main oscillator is enabled as soon as possible in the c_startup */
/* and MCK is switched on the main oscillator.                         */
/* PLL initialization is done later in the hw_init() function          */
/* ******************************************************************* */
#define MASTER_CLOCK		(132096000)
#define	TOP_OF_MEMORY		0x304000
#define PLL_LOCK_TIMEOUT	1000000

#define PLLA_SETTINGS	0x202A3F01
#define PLLB_SETTINGS	0x10193F05

/* Switch MCK on PLLA output PCK = PLLA/2 = 3 * MCK */
#define MCKR_SETTINGS		0x1300
#define MCKR_CSS_SETTINGS	(AT91C_PMC_CSS_PLLA_CLK | MCKR_SETTINGS)

/*
* DataFlash Settings
*/
#define CONFIG_SYS_SPI_CLOCK	AT91C_SPI_CLK
#define CONFIG_SYS_SPI_BUS	0
#define CONFIG_SYS_SPI_MODE	SPI_MODE3

#if CONFIG_SYS_SPI_BUS == 0
#define CONFIG_SYS_BASE_SPI	AT91C_BASE_SPI0
#elif CONFIG_SYS_SPI_BUS == 1
#define CONFIG_SYS_BASE_SPI	AT91C_BASE_SPI1
#endif

#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS0_DATAFLASH)
#define CONFIG_SYS_SPI_CS	0
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PA(3)
#elif (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS1_DATAFLASH)
#define CONFIG_SYS_SPI_CS	1
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PC(11)
#endif

/*
 * NandFlash Settings
 */
#define CONFIG_SYS_NAND_BASE		AT91C_BASE_CS3
#define CONFIG_SYS_NAND_MASK_ALE	(1 << 21)
#define CONFIG_SYS_NAND_MASK_CLE	(1 << 22)

#define CONFIG_SYS_NAND_ENABLE_PIN	AT91C_PIN_PC(14)
#define CONFIG_SYS_NAND_READY_PIN	AT91C_PIN_PC(13)



#define OP_BOOTSTRAP_MCI_on
#define BOARD_SD_PIN_CD \
    {1 << 9, AT91C_BASE_PIOC, AT91C_ID_PIOC, PIO_INPUT, PIO_PULLUP}

#define BOARD_SD_PINS \
    {0x0000003B, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_B, PIO_PULLUP}, \
    {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}

/// List of second MCI slot pins definitions.
#define BOARD_SD_MCI1_PINS  \
    {0xec0, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_PULLUP}, \
    {1 << 8, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT}


/* function */
extern void hw_init(void);

extern void nandflash_hw_init(void);
extern void nandflash_config_buswidth(unsigned char busw);

extern void at91_spi0_hw_init(void);
extern void spi_cs_activate(void);
extern void spi_cs_deactivate(void);

extern void at91_mci_hw_init(void);

#endif	/* #ifndef __AT91SAM9G20EK_H__ */
