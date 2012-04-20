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
#include "common.h"
#include "hardware.h"
#include "at91sam9n12ek.h"
#include "arch/at91_matrix.h"
#include "arch/at91_wdt.h"
#include "arch/at91_rstc.h"
#include "arch/at91_pmc.h"
#include "arch/at91_slowclk.h"
#include "arch/at91_smc.h"
#include "arch/at91_pio.h"
#include "gpio.h"
#include "pmc.h"
#include "dbgu.h"
#include "debug.h"
#include "ddramc.h"

#ifdef CONFIG_NANDFLASH
#include "nandflash.h"
#endif

#include "onewire_info.h"

extern int get_cp15(void);
extern void set_cp15(unsigned int value);

#ifdef CONFIG_SCLK
static void slow_clk_enable(void)
{
	writel(readl(AT91C_SYS_SLCKSEL) | AT91C_SLCKSEL_OSC32EN, AT91C_SYS_SLCKSEL);
	/* must wait for slow clock startup time ~ 1000ms
	 * (~6 core cycles per iteration, core is at 400MHz: 66666000 min loops) */
	delay(66700000);

	writel(readl(AT91C_SYS_SLCKSEL) | AT91C_SLCKSEL_OSCSEL, AT91C_SYS_SLCKSEL);
	/* must wait 5 slow clock cycles = ~153 us
	 * (~6 core cycles per iteration, core is at 400MHz: min 10200 loops) */
	delay(10200);

	/* now disable the internal RC oscillator */
	writel(readl(AT91C_SYS_SLCKSEL) & ~AT91C_SLCKSEL_RCEN, AT91C_SYS_SLCKSEL);
}
#endif /* CONFIG_SCLK */

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	unsigned int cp15;

	/* Configure DBGU pin */
	const struct pio_desc dbgu_pins[] = {
#ifdef CONFIG_DEBUG
		{"RXD", AT91C_PIN_PA(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PA(10), 0, PIO_DEFAULT, PIO_PERIPH_A},
#endif
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

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
	/*  Configure the dbgu pins */
	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(dbgu_pins);

#ifdef CONFIG_DEBUG
	/* Initialize dbgu */
	dbgu_init(BAUDRATE(MASTER_CLOCK, 115200));
#endif

#ifdef CONFIG_DDR2
	/* Initialize DDRAM Controller */
	ddramc_init();
#endif
}
#endif /* CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure PIN for SPI0 */
	const struct pio_desc spi0_pins[] = {
		{"MISO",  AT91C_PIN_PA(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MOSI",  AT91C_PIN_PA(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPCK",  AT91C_PIN_PA(13), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"NPCS0", AT91C_PIN_PA(14), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(spi0_pins);

	/* Enable the clock */
	writel((1 << AT91C_ID_SPI0), (PMC_PCER + AT91C_BASE_PMC));
}

void spi_cs_activate(int cs)
{
	switch (cs) {
	case 0:
		pio_set_value(AT91C_PIN_PA(14), 0);
		break;
	case 1:
		pio_set_value(AT91C_PIN_PA(7), 0);
		break;
	}
}

void spi_cs_deactivate(int cs)
{
	switch (cs) {
	case 0:
		pio_set_value(AT91C_PIN_PA(14), 1);
		break;
	case 1:
		pio_set_value(AT91C_PIN_PA(7), 1);
		break;
	}
}
#endif /* CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
void at91_mci_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PA(17), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PA(16), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA0", AT91C_PIN_PA(15), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PA(18), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PA(19), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PA(20), 0, PIO_PULLUP, PIO_PERIPH_A},

	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(mci_pins);

	/* Enable the clock */
	writel((1 << CONFIG_SYS_ID_MCI), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	unsigned int reg;

	/* Configure nand pins */
	const struct pio_desc nand_pins_lo[] = {
		{"NANDOE", AT91C_PIN_PD(0), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDWE", AT91C_PIN_PD(1), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDALE", AT91C_PIN_PD(2), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE", AT91C_PIN_PD(3), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCS", AT91C_PIN_PD(4), 0, PIO_PULLUP, PIO_OUTPUT},
		{"RDY_BSY", AT91C_PIN_PD(5), 0, PIO_PULLUP, PIO_INPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	reg = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	reg |= AT91C_EBI_CS3A_SM;

	reg &= ~AT91C_EBI_NFD0_ON_D16;	/* nandflash connect to D0~D15 */

	reg |= AT91C_EBI_DRV;	/* according to IAR verification package */
	writel(reg, AT91C_BASE_CCFG + CCFG_EBICSA);

	/* Configure SMC CS3 */
	writel((AT91C_SMC_NWESETUP_(1)
		| AT91C_SMC_NCS_WRSETUP_(0)
		| AT91C_SMC_NRDSETUP_(2) 
		| AT91C_SMC_NCS_RDSETUP_(0)), 
		AT91C_BASE_SMC + SMC_SETUP3);

	writel((AT91C_SMC_NWEPULSE_(3)
		| AT91C_SMC_NCS_WRPULSE_(5) 
		| AT91C_SMC_NRDPULSE_(4) 
		| AT91C_SMC_NCS_RDPULSE_(6)), 
		AT91C_BASE_SMC + SMC_PULSE3);

	writel((AT91C_SMC_NWECYCLE_(5)
		|  AT91C_SMC_NRDCYCLE_(7)),
		AT91C_BASE_SMC + SMC_CYCLE3);

	writel((AT91C_SMC_READMODE 
		| AT91C_SMC_WRITEMODE 
		| AT91C_SMC_NWAITM_NWAIT_DISABLE 
		| AT91C_SMC_DBW_WIDTH_BITS_8
		| AT91_SMC_TDF_(1)), 
		AT91C_BASE_SMC + SMC_CTRL3);

	/* Configure the nand controller pins*/
	writel((1 << AT91C_ID_PIOC_D), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(nand_pins_lo);
}

void nandflash_config_buswidth(unsigned char busw)
{
	unsigned long csa;

	csa = readl(AT91C_BASE_SMC + SMC_CTRL3);

	if (busw == 0)
		csa |= AT91C_SMC_DBW_WIDTH_BITS_8;
	else
		csa |= AT91C_SMC_DBW_WIDTH_BITS_16;

	writel(csa, AT91C_BASE_SMC + SMC_CTRL3);
}

#endif /* #ifdef CONFIG_NANDFLASH */

