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
#include "arch/at91_ccfg.h"
#include "arch/at91_wdt.h"
#include "arch/at91_rstc.h"
#include "arch/at91_pmc.h"
#include "arch/at91_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "gpio.h"
#include "pmc.h"
#include "dbgu.h"
#include "debug.h"
#include "ddramc.h"
#include "slowclk.h"
#include "pit_timer.h"
#include "at91sam9m10g45ek.h"

#ifdef CONFIG_USER_HW_INIT
extern void hw_init_hook(void);
#endif

#ifdef CONFIG_DEBUG
static void at91_dbgu_hw_init(void)
{
	/* Configure DBGU pin */
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PB(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PB(13), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the dbgu pins */
	pio_configure(dbgu_pins);
	writel((1 << AT91C_ID_PIOB), (PMC_PCER + AT91C_BASE_PMC));
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
	ddramc_config->mdr = (AT91C_DDRC2_DBW_16_BITS
			| AT91C_DDRC2_MD_DDR2_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9	/* 10 column bits */
			| AT91C_DDRC2_NR_14		/* 14 row bits(8K)*/
			| AT91C_DDRC2_CAS_3		/* CAS Latency 3 */
			| AT91C_DDRC2_EBISHARE		/* DQM is shared with other controller */
			| AT91C_DDRC2_DLL_RESET_DISABLED);	/* DLL not reset*/

	ddramc_config->rtr = 0x24B;

	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_6	/* 6 * 7.5 = 45 ns */
			| AT91C_DDRC2_TRCD_2	/* 2 * 7.5 = 22.5 ns */
			| AT91C_DDRC2_TWR_2	/* 2 * 7.5 = 15 ns */
			| AT91C_DDRC2_TRC_8	/* 8 * 7.5 = 75 ns */
			| AT91C_DDRC2_TRP_2	/* 2 * 7.5 = 22.5 ns */
			| AT91C_DDRC2_TRRD_1	/* 1 * 7.5 = 7.5 ns */
			| AT91C_DDRC2_TWTR_1	/* 1 clock cycle */
			| AT91C_DDRC2_TMRD_2);	/* 2 clock cycles */

	ddramc_config->t1pr = (AT91C_DDRC2_TXP_2	/* 2 * 7.5 = 15 ns */
			| 200 << 16			/* 200 clock cycles */
			| 16 << 8			/* 16 * 7.5 = 120 ns */
			| AT91C_DDRC2_TRFC_14 << 0);	/* 14 * 7.5 = 142 ns */

	ddramc_config->t2pr = (AT91C_DDRC2_TRTP_1	/* 1 * 7.5 = 7.5 ns */
			| AT91C_DDRC2_TRPA_0		/* 0 * 7.5 = 0 ns */
			| AT91C_DDRC2_TXARDS_7		/* 7 clock cycles */
			| AT91C_DDRC2_TXARD_2);		/* 2 clock cycles */
}

static void ddramc_init(void)
{
	unsigned long csa;
	struct ddramc_register  ddramc_reg;

	ddramc_reg_config(&ddramc_reg);

	/* ENABLE DDR2 clock */ 
	writel(AT91C_PMC_DDR, AT91C_BASE_PMC + PMC_SCER);

	/* Chip select 1 is for DDR2/SDRAM */
	csa = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	csa |= AT91C_EBI_CS1A_SDRAMC;
	csa &= ~AT91C_VDDIOM_SEL_33V;
	writel(csa, AT91C_BASE_CCFG + CCFG_EBICSA);

	/* DDRAM2 Controller initialize */
	ddram_initialize(AT91C_BASE_DDRSDRC, AT91C_DDRAM_BASE_ADDR, &ddramc_reg);
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

	writel((1 << AT91C_ID_PIOB), PMC_PCER + AT91C_BASE_PMC);
	pio_configure(recovery_button_pins);
}
#endif /* #if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY) */

static int ek_special_hw_init(void)
{
	/*
	 * For on the sam9m10g45ek board, the chip wm9711 stay in the test mode,
	 * so it need do some action to exit mode.
	 */
	const struct pio_desc wm9711_pins[] = {
		{"AC97TX", AT91C_PIN_PD(7), 0, PIO_PULLUP, PIO_OUTPUT},
		{"AC97FS", AT91C_PIN_PD(8), 0, PIO_PULLUP, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(wm9711_pins);
	writel((1 << AT91C_ID_PIOD_E), PMC_PCER + AT91C_BASE_PMC);

	/*
	 * Disable pull-up on:
	 * RXDV(PA15) => PHY normal mode (not Test mode)
	 * ERX0(PA12) => PHY ADDR0
	 * ERX1(PA13) => PHY ADDR1 => PHYADDR = 0x0
	 *
	 * PHY has internal pull-down
	 */
	 writel((0x01 << 12) | (0x01 << 13) | (0x01 << 15),  AT91C_BASE_PIOA + PIO_PPUDR(0));

	 return 0;
}

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	writel(AT91C_WDTC_WDDIS, AT91C_BASE_WDTC + WDTC_MR);

	/* At this stage the main oscillator
	 * is supposed to be enabled PCK = MCK = MOSC */
	writel(0x00, AT91C_BASE_PMC + PMC_PLLICPR);

	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

	/* PCK = PLLA/2 = 3 * MCK */
	pmc_cfg_mck(BOARD_PRESCALER, PLL_LOCK_TIMEOUT);

	/* Switch MCK on PLLA output */
	pmc_cfg_mck(0x1302, PLL_LOCK_TIMEOUT);

	/* Enable External Reset */
	writel(((0xA5 << 24) | AT91C_RSTC_URSTEN), AT91C_BASE_RSTC + RSTC_RMR);

	/* Init timer */
	timer_init();

#ifdef CONFIG_SCLK
	slowclk_enable_osc32();
#endif

#ifdef CONFIG_DEBUG
	/* Initialize dbgu */
	initialize_dbgu();
#endif

#ifdef CONFIG_DDR2
	/* Initialize DDRAM Controller */
	ddramc_init();
#endif

#ifdef CONFIG_USER_HW_INIT
	hw_init_hook();
#endif

#if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY)
	/* Init the recovery buttons pins */
	recovery_buttons_hw_init();
#endif
	/* do some special init */
	ek_special_hw_init();
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure spi0 PINs */
	const struct pio_desc spi0_pins[] = {
		{"MISO", 	AT91C_PIN_PB(0),	0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MOSI", 	AT91C_PIN_PB(1),	0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPCK", 	AT91C_PIN_PB(2),	0, PIO_DEFAULT, PIO_PERIPH_A},
		{"NPCS",	CONFIG_SYS_SPI_PCS,	1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	writel((1 << AT91C_ID_PIOB), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(spi0_pins);

	writel((1 << AT91C_ID_SPI0), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
void at91_mci0_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", 	AT91C_PIN_PA(0), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCCDA",	AT91C_PIN_PA(1), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA0",	AT91C_PIN_PA(2), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA1",	AT91C_PIN_PA(3), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA2",	AT91C_PIN_PA(4), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA3",	AT91C_PIN_PA(5), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOA), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(mci_pins);

	/* Enable the clock */
	writel((1 << AT91C_ID_MCI0), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	unsigned int reg;

	/* Configure PIOs */
	const struct pio_desc nand_pins[] = {
		{"NANDCS",	CONFIG_SYS_NAND_ENABLE_PIN,	1, PIO_PULLUP, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Setup Smart Media, first enable the address range of CS3
	 * in HMATRIX user interface
	* EBI IO in 1.8V mode */
	reg = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	reg |= AT91C_EBI_CS3A_SM;
	reg &= ~AT91C_VDDIOM_SEL_33V;
	writel(reg, AT91C_BASE_CCFG + CCFG_EBICSA);

	/* Configure SMC CS3 */
	writel((AT91C_SMC_NWESETUP_(2)
		| AT91C_SMC_NCS_WRSETUP_(0)
		| AT91C_SMC_NRDSETUP_(2)
		| AT91C_SMC_NCS_RDSETUP_(0)),
		AT91C_BASE_SMC + SMC_SETUP3);

	writel((AT91C_SMC_NWEPULSE_(4)
		| AT91C_SMC_NCS_WRPULSE_(4)
		| AT91C_SMC_NRDPULSE_(4)
		| AT91C_SMC_NCS_RDPULSE_(4)),
		AT91C_BASE_SMC + SMC_PULSE3);

	writel((AT91C_SMC_NWECYCLE_(7)
		|  AT91C_SMC_NRDCYCLE_(7)),
		AT91C_BASE_SMC + SMC_CYCLE3);

	writel((AT91C_SMC_READMODE
		| AT91C_SMC_WRITEMODE
		| AT91C_SMC_NWAITM_NWAIT_DISABLE
		| AT91C_SMC_DBW_WIDTH_BITS_16
		| AT91_SMC_TDF_(3)),
		AT91C_BASE_SMC + SMC_CTRL3);

	/* Configure the PIO controll */
	writel((1 << AT91C_ID_PIOC), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(nand_pins);

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
