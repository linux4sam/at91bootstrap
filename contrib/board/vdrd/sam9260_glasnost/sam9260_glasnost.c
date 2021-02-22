/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation
 * Copyright (c) 2021, Vadim Radu
 * 
 * Based on sama9260ek (AT91SAM9260 Evaluation Kit)
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
#include "common.h"
#include "hardware.h"
#include "arch/at91_ccfg.h"
#include "arch/at91_matrix.h"
#include "arch/at91_rstc.h"
#include "arch/at91_pmc/pmc.h"
#include "arch/at91_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_sdramc.h"
#include "spi.h"
#include "gpio.h"
#include "pmc.h"
#include "usart.h"
#include "debug.h"
#include "sdramc.h"
#include "timer.h"
#include "watchdog.h"
#include "sam9260_glasnost.h"

static void initialize_dbgu(void)
{
	/* Configure DBGU pin */
	/* {"RXD", AT91C_PIN_PB(14), 0, PIO_DEFAULT, PIO_PERIPH_A}, */
	/* {"TXD", AT91C_PIN_PB(15), 0, PIO_DEFAULT, PIO_PERIPH_A}, */
	writel(((0x01 << 14) | (0x01 << 15)), AT91C_BASE_PIOB + PIO_ASR);
	writel(((0x01 << 14) | (0x01 << 15)), AT91C_BASE_PIOB + PIO_PDR);

	pmc_enable_periph_clock(AT91C_ID_PIOB, PMC_PERIPH_CLK_DIVIDER_NA);

	usart_init(BAUDRATE(MASTER_CLOCK, 115200));
}

#ifdef CONFIG_SDRAM
static void sdramc_init(void)
{
	struct sdramc_register sdramc_config;

	sdramc_config.cr = AT91C_SDRAMC_NC_9
		| AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2
		| AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS
		| AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_4
		| AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2
		| AT91C_SDRAMC_TRAS_5 | AT91C_SDRAMC_TXSR_8;

	sdramc_config.tr = (MASTER_CLOCK * 7) / 1000000;
	sdramc_config.mdr = AT91C_SDRAMC_MD_SDRAM;

	/* configure sdramc pins */
	writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_ASR);
	writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_PDR);

	pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);

	/* Initialize the matrix (memory voltage = 3.3) */
	writel(readl(AT91C_BASE_CCFG + CCFG_EBICSA) | AT91C_EBI_CS1A_SDRAMC,
			AT91C_BASE_CCFG + CCFG_EBICSA);

	sdramc_initialize(&sdramc_config, AT91C_BASE_CS1);
}
#endif  /* #ifdef CONFIG_SDRAM */

static void at91_blue_led_on(void)
{
	pio_set_gpio_output(AT91C_PIN_PC(6), 1); /* Red Led */
	pio_set_gpio_output(AT91C_PIN_PC(7), 1); /* Green Led */
	pio_set_gpio_output(AT91C_PIN_PC(9), 0); /* Blue Led */
}

#if defined(CONFIG_DATAFLASH_RECOVERY)
static void recovery_buttons_hw_init(void)
{
	/* Configure recovery button PINs */
	/* {"RECOVERY_BUTTON", AT91C_PIN_PA(31), 0, PIO_PULLUP, PIO_INPUT} */
	writel((0x01 << 31), AT91C_BASE_PIOA + PIO_IDR);
	writel((0x01 << 31), AT91C_BASE_PIOA + PIO_PPUER);
	writel((0x01 << 31), AT91C_BASE_PIOA + PIO_ODR);
	writel((0x01 << 31), AT91C_BASE_PIOA + PIO_PER);

	pmc_enable_periph_clock(AT91C_ID_PIOA, PMC_PERIPH_CLK_DIVIDER_NA);
}
#endif /* #if defined(CONFIG_DATAFLASH_RECOVERY) */

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	at91_disable_wdt();

    /* Blue Led ON */
	at91_blue_led_on();

	/*
	 * At this stage the main oscillator is supposed to be enabled
	 * PCK = MCK = MOSC
	 */
	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS);

	/* PCK = PLLA = 2 * MCK */
	pmc_mck_cfg_set(0, MCKR_SETTINGS, AT91C_PMC_PRES | AT91C_PMC_MDIV);

	/* Switch MCK on PLLA output */
	pmc_mck_cfg_set(0, MCKR_CSS_SETTINGS,
			AT91C_PMC_PRES | AT91C_PMC_MDIV | AT91C_PMC_CSS);

	/* Enable External Reset */
	writel(AT91C_RSTC_KEY_UNLOCK | AT91C_RSTC_URSTEN, AT91C_BASE_RSTC + RSTC_RMR);

	/* Initialize matrix */
	writel((readl(AT91C_BASE_MATRIX + MATRIX_SCFG3) & (~AT91C_MATRIX_SLOT_CYCLE))
			| AT91C_MATRIX_SLOT_CYCLE_(0x40),
			AT91C_BASE_MATRIX + MATRIX_SCFG3);

	/* Init timer */
	timer_init();

	/* Initialize dbgu */
	initialize_dbgu();

#ifdef CONFIG_SDRAM
	/* Initlialize sdram controller */
	sdramc_init();
#endif

#if defined(CONFIG_DATAFLASH_RECOVERY)
	/* Init the recovery buttons pins */
	recovery_buttons_hw_init();
#endif
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure the spi0 pins */
	/* {"MISO",	AT91C_PIN_PA(0),	0, PIO_DEFAULT, PIO_PERIPH_A}
	   {"MOSI",	AT91C_PIN_PA(1),	0, PIO_DEFAULT, PIO_PERIPH_A}
	   {"SPCK",	AT91C_PIN_PA(2),	0, PIO_DEFAULT, PIO_PERIPH_A}*/
	writel(((0x01 << 0) | (0x01 << 1) | (0x01 << 2)),
					AT91C_BASE_PIOA + PIO_ASR);
	writel(((0x01 << 0) | (0x01 << 1) | (0x01 << 2)),
					AT91C_BASE_PIOA + PIO_PDR);

#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS0_DATAFLASH)
	/* {"NPCS",        AT91C_PIN_PA(3),     1, PIO_PULLUP, PIO_OUTPUT}, */
	writel((0x01 << 3), AT91C_BASE_PIOA + PIO_IDR);
	writel((0x01 << 3), AT91C_BASE_PIOA + PIO_PPUDR);
	writel((0x01 << 3), AT91C_BASE_PIOA + PIO_SODR);
	writel((0x01 << 3), AT91C_BASE_PIOA + PIO_OER);
	writel((0x01 << 3), AT91C_BASE_PIOA + PIO_PER);

	pmc_enable_periph_clock(AT91C_ID_PIOA, PMC_PERIPH_CLK_DIVIDER_NA);
#endif

	/* Enable the spi0 clock */
	pmc_enable_periph_clock(AT91C_ID_SPI0, PMC_PERIPH_CLK_DIVIDER_NA);
}
#endif /* #ifdef CONFIG_DATAFLASH */


