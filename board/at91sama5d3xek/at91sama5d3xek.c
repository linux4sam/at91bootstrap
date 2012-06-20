/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

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
#include "pmc.h"
#include "dbgu.h"
#include "debug.h"
#include "ddramc.h"
#include "spi.h"
#include "gpio.h"
#include "slowclk.h"

#include "arch/at91_pmc.h"
#include "arch/at91_wdt.h"
#include "arch/at91_rstc.h"
#include "arch/at91sama5_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "at91sama5d3xek.h"

#ifdef CONFIG_USER_HW_INIT
extern void hw_init_hook(void);
#endif

#ifdef CONFIG_DEBUG
static void at91_dbgu_hw_init(void)
{
	/* Configure DBGU pin */
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/*  Configure the dbgu pins */
	pio_configure(dbgu_pins);
	writel((1 << AT91C_ID_PIOB), (PMC_PCER + AT91C_BASE_PMC));

	/* Enable clock */
	writel(1 << AT91C_ID_DBGU, (PMC_PCER + AT91C_BASE_PMC));
}

static void initialize_dbgu(void)
{
	at91_dbgu_hw_init();
	dbgu_init(BAUDRATE(MASTER_CLOCK, 115200));
}
#endif /* #ifdef CONFIG_DEBUG */

#ifdef CONFIG_DDR2
static void ddramc_reg_config(struct ddramc_register *ddramc_config)
{
	ddramc_config->mdr = (AT91C_DDRC2_DBW_32_BITS
				| AT91C_DDRC2_MD_DDR2_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9
				| AT91C_DDRC2_NR_13
				| AT91C_DDRC2_CAS_3
				| AT91C_DDRC2_NB_BANKS_8
				| AT91C_DDRC2_NDQS_DISABLED
				| AT91C_DDRC2_SUPPORTED);

	ddramc_config->rtr = 0x00300208;	/* Refresh Timer register : 520 for 133 MHz */

	/* One clock cycle @ 133 MHz = 7.5 ns */
	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_6
				| AT91C_DDRC2_TRCD_2
				| AT91C_DDRC2_TWR_2
				| AT91C_DDRC2_TRC_8
				| AT91C_DDRC2_TRP_2
				| AT91C_DDRC2_TRRD_2
				| AT91C_DDRC2_TWTR_2
				| AT91C_DDRC2_TMRD_2);

	ddramc_config->t1pr = 0x02C81311;

	ddramc_config->t2pr = (AT91C_DDRC2_TXARD_2
				| AT91C_DDRC2_TXARDS_7
				| AT91C_DDRC2_TRPA_3
				| AT91C_DDRC2_TRTP_2
				| AT91C_DDRC2_TFAW_7);
}

static void ddramc_init(void)
{
	struct ddramc_register ddramc_reg;

	ddramc_reg_config(&ddramc_reg);

	/* enable ddr2 clock */
	writel(1 << (AT91C_ID_MPDDRC - 32),  (PMC_PCER1 + AT91C_BASE_PMC));
	writel(AT91C_PMC_DDR, (PMC_SCER + AT91C_BASE_PMC));

	/* Init the special register for sama5d3x */
	/* MPDDRC DLL Slave Offset Register */
	writel((0x01 | (0x01 << 16) | (0x01 << 24)), (AT91C_BASE_MPDDRC + MPDDRC_DLL_SOR));
	/* MPDDRC DLL Master Offset Register */
	writel(0xC5011f07, (AT91C_BASE_MPDDRC + MPDDRC_DLL_MOR));
	/* MPDDRC I/O Calibration Register */
	writel(0x00850404, (AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR));

	/* DDRAM2 Controller initialize */
	ddram_initialize(AT91C_BASE_MPDDRC, AT91C_BASE_DDRCS, &ddramc_reg);
}
#endif /* #ifdef CONFIG_DDR2 */

#if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY)
static void recovery_buttons_hw_init(void)
{
	/* Configure recovery button PINs */
	const struct pio_desc recovery_button_pins[] = {
		{"RECOVERY_BUTTON", CONFIG_SYS_RECOVERY_BUTTON_PIN, 0, PIO_PULLUP, PIO_INPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	writel((1 << AT91C_ID_PIOE), PMC_PCER + AT91C_BASE_PMC);
	pio_configure(recovery_button_pins);
}
#endif /* #if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY) */

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	writel(AT91C_WDTC_WDDIS, AT91C_BASE_WDT + WDTC_MR);

	/* At this stage the main oscillator is supposed to be enabled PCK = MCK = MOSC */
	writel(0x00, AT91C_BASE_PMC + PMC_PLLICPR);

	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

	/* PCK = PLLA/2 = 3 * MCK */
	pmc_cfg_mck(BOARD_PRESCALER_MAIN_CLOCK, PLL_LOCK_TIMEOUT);

	/* Switch MCK on PLLA output */
	pmc_cfg_mck(BOARD_PRESCALER_PLLA, PLL_LOCK_TIMEOUT);

	/* Enable External Reset */
	writel(((0xA5 << 24) | AT91C_RSTC_URSTEN), AT91C_BASE_RSTC + RSTC_RMR);

#ifdef CONFIG_SCLK
	slowclk_enable_osc32();
#endif

#ifdef CONFIG_DEBUG
	/* initialize the dbgu */
	initialize_dbgu();
#endif

#ifdef CONFIG_DDR2
	/* Initialize MPDDR Controller */
	ddramc_init();
#endif

#ifdef CONFIG_USER_HW_INIT
	hw_init_hook();
#endif

#if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY)
	/* Init the recovery buttons pins */
	recovery_buttons_hw_init();
#endif
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure PIN for SPI0 */
	const struct pio_desc spi0_pins[] = {
		{"MISO",	AT91C_PIN_PD(10), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MOSI",	AT91C_PIN_PD(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPCK",	AT91C_PIN_PD(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOD), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(spi0_pins);

	/* Enable the clock */
	writel((1 << AT91C_ID_SPI0), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
void at91_mci0_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PD(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PD(0), 0, PIO_PULLUP, PIO_PERIPH_A},

		{"MCDA0", AT91C_PIN_PD(1), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PD(2), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PD(3), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PD(4), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOD), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(mci_pins);

	/* Enable the clock */
	writel((1 << AT91C_ID_HSMCI0), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	/* Configure nand pins */
	const struct pio_desc nand_pins[] = {
		{"NANDALE", AT91C_PIN_PE(21), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE", AT91C_PIN_PE(22), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the nand controller pins*/
	pio_configure(nand_pins);
	writel((1 << AT91C_ID_PIOE), (PMC_PCER + AT91C_BASE_PMC));

	/* Enable the clock */
	writel(1 << AT91C_ID_SMC, (PMC_PCER + AT91C_BASE_PMC));

	/* Configure SMC CS3 for NAND/SmartMedia */
	writel(AT91C_SMC_SETUP_NWE(1)
		| AT91C_SMC_SETUP_NCS_WR(1) 
		| AT91C_SMC_SETUP_NRD(2) 
		| AT91C_SMC_SETUP_NCS_RD(1), 
		(ATMEL_BASE_SMC + SMC_SETUP3));

	writel(AT91C_SMC_PULSE_NWE(5)
		| AT91C_SMC_PULSE_NCS_WR(7)
		| AT91C_SMC_PULSE_NRD(5)
		| AT91C_SMC_PULSE_NCS_RD(7), 
	 	(ATMEL_BASE_SMC + SMC_PULSE3));

	writel(AT91C_SMC_CYCLE_NWE(8)
		| AT91C_SMC_CYCLE_NRD(9), 
		(ATMEL_BASE_SMC + SMC_CYCLE3));

	writel(AT91C_SMC_TIMINGS_TCLR(3)
		| AT91C_SMC_TIMINGS_TADL(10)
		| AT91C_SMC_TIMINGS_TAR(3)
		| AT91C_SMC_TIMINGS_TRR(4)
		| AT91C_SMC_TIMINGS_TWB(5)
		| AT91C_SMC_TIMINGS_RBNSEL(3)
		| AT91C_SMC_TIMINGS_NFSEL,
		(ATMEL_BASE_SMC + SMC_TIMINGS3));

	writel(AT91C_SMC_MODE_READMODE_NRD_CTRL
		| AT91C_SMC_MODE_WRITEMODE_NWE_CTRL
		| AT91C_SMC_MODE_EXNWMODE_DISABLED
		| AT91C_SMC_MODE_DBW_8
		| AT91C_SMC_MODE_TDF_CYCLES(1),
		(ATMEL_BASE_SMC + SMC_MODE3));
}

void nandflash_config_buswidth(unsigned char buswidth)
{
	unsigned int mode; 

	mode = readl(ATMEL_BASE_SMC + SMC_MODE3);

	mode &= ~AT91C_SMC_MODE_DBW;
	if (buswidth == 0)	/* 8 bits bus */
		mode |= AT91C_SMC_MODE_DBW_8;	
	else 
		mode |= AT91C_SMC_MODE_DBW_16;

	writel(mode, (ATMEL_BASE_SMC + SMC_MODE3));
}
#endif /* #ifdef CONFIG_NANDFLASH */
