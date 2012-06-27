/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
#ifndef __AT91SAM9M10G45EK_H__
#define __AT91SAM9M10G45EK_H__

/*
 * PMC Settings
 *
 * The main oscillator is enabled as soon as possible in the c_startup
 * and MCK is switched on the main oscillator.
 * PLL initialization is done later in the hw_init() function
 */
#define MASTER_CLOCK		(132096000)
#define PLL_LOCK_TIMEOUT	1000000

#define BOARD_MAINOSC		12000000
#define BOARD_MCK		((unsigned long)((BOARD_MAINOSC / 3 / 2 / 3) * 200))
#define BOARD_OSCOUNT		(AT91C_CKGR_OSCOUNT & (64 << 8))
#define BOARD_CKGR_PLLA		(AT91C_CKGR_SRCA | AT91C_CKGR_OUTA_0)
#define BOARD_PLLACOUNT		(0x3F << 8)
#define BOARD_MULA		(AT91C_CKGR_MULA & (199 << 16))
#define BOARD_DIVA		(AT91C_CKGR_DIVA & 3)
#define BOARD_PRESCALER		(0x00001301)

#define PLLA_SETTINGS		(BOARD_CKGR_PLLA \
				| BOARD_PLLACOUNT \
				| BOARD_MULA \
				| BOARD_DIVA)

/* #define PLLA_SETTINGS 0x202A3F01 */
#define PLLUTMI
#define PLLUTMI_SETTINGS	0x10193F05

/* Switch MCK on PLLA output PCK = PLLA/2 = 3 * MCK */
#define MCKR_CSS_SETTINGS	0x1302

/* DDRAM Controller */
#define AT91C_BASE_DDRSDRC	AT91C_BASE_DDRSDRC0
#define AT91C_DDRAM_BASE_ADDR	AT91C_BASE_CS6
/*
 * DataFlash Settings
 */
#define CONFIG_SYS_SPI_CLOCK    AT91C_SPI_CLK
#define CONFIG_SYS_SPI_BUS      0
#define CONFIG_SYS_SPI_MODE     SPI_MODE3

#if CONFIG_SYS_SPI_BUS == 0
#define CONFIG_SYS_BASE_SPI     AT91C_BASE_SPI0
#elif CONFIG_SYS_SPI_BUS == 1
#define CONFIG_SYS_BASE_SPI     AT91C_BASE_SPI1
#endif

#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS0_DATAFLASH)
#define CONFIG_SYS_SPI_CS	0
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PB(3)
#elif (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS1_DATAFLASH)
#define CONFIG_SYS_SPI_CS	1
#define CONFIG_SYS_SPI_PCS	AT91C_PIN_PB(18)
#endif

#define CONFIG_SYS_NAND_BASE		AT91C_BASE_CS3
#define CONFIG_SYS_NAND_MASK_ALE	(1 << 21)
#define CONFIG_SYS_NAND_MASK_CLE	(1 << 22)

#define CONFIG_SYS_NAND_ENABLE_PIN	AT91C_PIN_PC(14)

/*
 * MCI Settings
 */
#define CONFIG_SYS_BASE_MCI     AT91C_BASE_MCI0

/*
 * Recovery
 */
#define CONFIG_SYS_RECOVERY_BUTTON_PIN	AT91C_PIN_PB(7)
#define RECOVERY_BUTTON_NAME	"BP4"

/* function */
extern void hw_init(void);

extern void nandflash_hw_init(void);
extern void nandflash_config_buswidth(unsigned char busw);
extern unsigned int nandflash_get_ready_pin(void);

extern void at91_spi0_hw_init(void);

extern void at91_mci0_hw_init(void);

#endif /* __AT91SAM9M10G45EK_H__ */
