/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
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
#include "at91sama5d3xek.h"
#include "pmc.h"
#include "dbgu.h"
#include "debug.h"
#include "ddramc.h"
#include "mpddrsdramc.h"
#include "spi.h"
#include "gpio.h"

#include "arch/at91_pmc.h"
#include "arch/at91_wdt.h"
#include "arch/at91_rstc.h"
#include "arch/at91sama5_smc.h"
#include "arch/at91_slowclk.h"
#include "arch/at91_pio.h"

extern int get_cp15(void);
extern void set_cp15(unsigned int value);

#ifdef CONFIG_DEBUG
static void initialize_dbgu(void);
#endif

static void initialize_ddr2(void);

#ifdef CONFIG_SCLK
static void slow_clk_enable(void)
{
	writel(readl(AT91C_SYS_SCKCR) | AT91C_SLCKSEL_OSC32EN, AT91C_SYS_SCKCR);
	/* must wait for slow clock startup time ~ 1000ms
	 * (~6 core cycles per iteration, core is at 400MHz: 66666000 min loops) */
	delay(66700000);

	writel(readl(AT91C_SYS_SCKCR) | AT91C_SLCKSEL_OSCSEL, AT91C_SYS_SCKCR);
	/* must wait 5 slow clock cycles = ~153 us
	 * (~6 core cycles per iteration, core is at 400MHz: min 10200 loops) */
	delay(10200);

	/* now disable the internal RC oscillator */
	writel(readl(AT91C_SYS_SCKCR) & ~AT91C_SLCKSEL_RCEN, AT91C_SYS_SCKCR);
}
#endif /* #ifdef CONFIG_SCLK */

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	unsigned int cp15;

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

	/* Configure CP15 */
	cp15 = get_cp15();
	cp15 |= I_CACHE;
	set_cp15(cp15);

#ifdef CONFIG_SCLK
	slow_clk_enable();
#endif

#ifdef CONFIG_DEBUG
	/* initialize the dbgu */
	initialize_dbgu();
#endif

#ifdef CONFIG_DDR2
	/* Initialize MPDDR Controller */
	initialize_ddr2();
#endif

#ifdef CONFIG_USER_HW_INIT
	hw_init_hook();
#endif
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DEBUG
static void at91_dbgu_hw_init(void)
{
	/* Configure DBGU pin */
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(dbgu_pins);

	/*  Configure the dbgu pins */
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
static void initialize_ddr2(void)
{
	writel(1 << (AT91C_ID_MPDDRC - 32),  (PMC_PCER1 + AT91C_BASE_PMC));
	writel(AT91C_PMC_DDR, (PMC_SCER + AT91C_BASE_PMC));

	init_mpddr_sdramc();

}
#endif /* #ifdef CONFIG_DDR2 */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure PIN for SPI0 */
	const struct pio_desc spi0_pins[] = {
		{"MISO",  AT91C_PIN_PD(10), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MOSI",  AT91C_PIN_PD(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPCK",  AT91C_PIN_PD(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"NPCS0", AT91C_PIN_PD(13), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOD), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(spi0_pins);

	/* Enable the clock */
	writel((1 << AT91C_ID_SPI0), (PMC_PCER + AT91C_BASE_PMC));
}

void spi_cs_activate(int cs)
{
	switch (cs) {
	case 0:
		pio_set_value(AT91C_PIN_PD(13), 0);
		break;
	case 1:
		pio_set_value(AT91C_PIN_PD(14), 0);
		break;
	}
}

void spi_cs_deactivate(int cs)
{
	switch (cs) {
	case 0:
		pio_set_value(AT91C_PIN_PD(13), 1);
		break;
	case 1:
		pio_set_value(AT91C_PIN_PD(14), 1);
		break;
	}
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
void at91_mci_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PD(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PD(0), 0, PIO_PULLUP, PIO_PERIPH_A},

		{"MCDA0", AT91C_PIN_PD(1), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PD(2), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PD(3), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PD(4), 0, PIO_PULLUP, PIO_PERIPH_A},

	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOD), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(mci_pins);

	/* Enable the clock */
	writel((1 << CONFIG_SYS_ID_MCI), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
static unsigned int mode ;

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
		ATMEL_BASE_SMC + SMC_SETUP3);

	writel(AT91C_SMC_PULSE_NWE(5)
		| AT91C_SMC_PULSE_NCS_WR(7)
		| AT91C_SMC_PULSE_NRD(5)
		| AT91C_SMC_PULSE_NCS_RD(7), 
	 	ATMEL_BASE_SMC + SMC_PULSE3);

	writel(AT91C_SMC_CYCLE_NWE(8)
		| AT91C_SMC_CYCLE_NRD(9), 
		ATMEL_BASE_SMC + SMC_CYCLE3);

	writel(AT91C_SMC_TIMINGS_TCLR(3)
		| AT91C_SMC_TIMINGS_TADL(10)
		| AT91C_SMC_TIMINGS_TAR(3)
		| AT91C_SMC_TIMINGS_TRR(4)
		| AT91C_SMC_TIMINGS_TWB(5)
		| AT91C_SMC_TIMINGS_RBNSEL(3)
		| AT91C_SMC_TIMINGS_NFSEL,
		ATMEL_BASE_SMC + SMC_TIMINGS3);

	mode = AT91C_SMC_MODE_READMODE_NRD_CTRL
		| AT91C_SMC_MODE_WRITEMODE_NWE_CTRL
		| AT91C_SMC_MODE_EXNWMODE_DISABLED
		| AT91C_SMC_MODE_DBW_8
		| AT91C_SMC_MODE_TDF_CYCLES(1);

	writel(mode, (ATMEL_BASE_SMC + SMC_MODE3));
}

void nandflash_config_buswidth(unsigned char buswidth)
{
	mode &= ~AT91C_SMC_MODE_DBW;
	if (buswidth == 0)	/* 8 bits bus */
		mode |= AT91C_SMC_MODE_DBW_8;	
	else 
		mode |= AT91C_SMC_MODE_DBW_16;

	writel(mode, ATMEL_BASE_SMC + SMC_MODE3);
}
#endif /* #ifdef CONFIG_NANDFLASH */

