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
#include "at91sam9x5ek.h"

#include "onewire_info.h"

#ifdef CONFIG_USER_HW_INIT
extern void hw_init_hook(void);
#endif

#ifdef CONFIG_DEBUG
static void at91_dbgu_hw_init(void)
{
	/* Configure DBGU pins */
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PA(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PA(10), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(dbgu_pins);
	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
}

static void initialize_dbgu(void)
{
	at91_dbgu_hw_init();
	dbgu_init(BAUDRATE(MASTER_CLOCK, BAUD_RATE));
}
#endif /* #ifdef CONFIG_DEBUG */

#ifdef CONFIG_DDR2
/* Using the Micron MT47H64M16HR-3 */
static void ddramc_reg_config(struct ddramc_register *ddramc_config)
{
	ddramc_config->mdr = (AT91C_DDRC2_DBW_16_BITS
			| AT91C_DDRC2_MD_DDR2_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9 /* 10 column bits(1K) */
			| AT91C_DDRC2_NR_13              /* 13 row bits (8K) */
			| AT91C_DDRC2_CAS_3              /* CAS Latency 3 */
			| AT91C_DDRC2_NB_BANKS_8         /* 8 banks */
			| AT91C_DDRC2_DLL_RESET_DISABLED /* DLL not reset */
			| AT91C_DDRC2_DECOD_INTERLEAVED);/*Interleaved decode*/

	/*
	 * The DDR2-SDRAM device requires a refresh every 15.625 us or 7.81 us.
	 * With a 133 MHz frequency, the refresh timer count register must to be
	 * set with (15.625 x 133 MHz) ~ 2084 i.e. 0x824
	 * or (7.81 x 133 MHz) ~ 1040 i.e. 0x410.
	 */
	ddramc_config->rtr = 0x411;     /* Refresh timer: 7.8125us */

	/* One clock cycle @ 133 MHz = 7.5 ns */
	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_6       /* 6 * 7.5 = 45 ns */
			| AT91C_DDRC2_TRCD_2            /* 2 * 7.5 = 22.5 ns */
			| AT91C_DDRC2_TWR_2             /* 2 * 7.5 = 15   ns */
			| AT91C_DDRC2_TRC_8             /* 8 * 7.5 = 75   ns */
			| AT91C_DDRC2_TRP_2             /* 2 * 7.5 = 15   ns */
			| AT91C_DDRC2_TRRD_2            /* 2 * 7.5 = 15   ns */
			| AT91C_DDRC2_TWTR_2            /* 2 clock cycles min */
			| AT91C_DDRC2_TMRD_2);          /* 2 clock cycles */

	ddramc_config->t1pr = (AT91C_DDRC2_TXP_2        /*  2 clock cycles */
			| AT91C_DDRC2_TXSRD_200         /* 200 clock cycles */
			| AT91C_DDRC2_TXSNR_19          /* 19 * 7.5 = 142.5 ns*/
			| AT91C_DDRC2_TRFC_18);         /* 18 * 7.5 = 135 ns */

	ddramc_config->t2pr = (AT91C_DDRC2_TFAW_7       /* 7 * 7.5 = 52.5 ns */
			| AT91C_DDRC2_TRTP_2            /* 2 clock cycles min */
			| AT91C_DDRC2_TRPA_3            /* 3 * 7.5 = 22.5 ns */
			| AT91C_DDRC2_TXARDS_7          /* 7 clock cycles */
			| AT91C_DDRC2_TXARD_2);         /* 2 clock cycles */
}

static void ddramc_init(void)
{
	unsigned long csa;
	struct ddramc_register ddramc_reg;

	ddramc_reg_config(&ddramc_reg);

	/* ENABLE DDR2 clock */
	writel(AT91C_PMC_DDR, AT91C_BASE_PMC + PMC_SCER);

	/* Chip select 1 is for DDR2/SDRAM */
	csa = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	csa |= AT91C_EBI_CS1A_SDRAMC;
	csa &= ~AT91C_EBI_DBPUC;
	csa |= AT91C_EBI_DBPDC;
	csa |= AT91C_EBI_DRV_HD;

	writel(csa, AT91C_BASE_CCFG + CCFG_EBICSA);

	/* DDRAM2 Controller initialize */
	ddram_initialize(AT91C_BASE_DDRSDRC, AT91C_BASE_CS1, &ddramc_reg);
}
#endif	/* #ifdef CONFIG_DDR2 */

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	writel(AT91C_WDTC_WDDIS, AT91C_BASE_WDT + WDTC_MR);

	/* At this stage the main oscillator is
	 *supposed to be enabled PCK = MCK = MOSC
	 */
	writel(0x00, AT91C_BASE_PMC + PMC_PLLICPR);

	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

	/* PCK = PLLA/2 = 3 * MCK */
	pmc_cfg_mck(BOARD_PRESCALER_MAIN_CLOCK, PLL_LOCK_TIMEOUT);

	/* Switch MCK on PLLA output */
	pmc_cfg_mck(BOARD_PRESCALER_PLLA, PLL_LOCK_TIMEOUT);

	/*Enable External Reset */
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
	/* load one wire information */
	load_1wire_info();

#ifdef CONFIG_USER_HW_INIT
	hw_init_hook();
#endif
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure PINs for SPI0 */
	const struct pio_desc spi0_pins[] = {
		{"MISO",	AT91C_PIN_PA(11),	0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MOSI",	AT91C_PIN_PA(12),	0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPCK",	AT91C_PIN_PA(13),	0, PIO_DEFAULT, PIO_PERIPH_A},
		{"NPCS",	CONFIG_SYS_SPI_PCS,	1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0,	0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(spi0_pins);

	writel((1 << AT91C_ID_SPI0), (PMC_PCER + AT91C_BASE_PMC));
}
#endif	/* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
void at91_mci0_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PA(17), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PA(16), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA0", AT91C_PIN_PA(15), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PA(18), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PA(19), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PA(20), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0,	0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(mci_pins);

	/* Enable the clock */
	writel((1 << AT91C_ID_HSMCI0), (PMC_PCER + AT91C_BASE_PMC));
}
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	unsigned int reg;

	/* Configure Nand PINs */
	const struct pio_desc nand_pins_hi[] = {
		{"NANDOE",	CONFIG_SYS_NAND_OE_PIN,		0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDWE",	CONFIG_SYS_NAND_WE_PIN,		0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDALE",	CONFIG_SYS_NAND_ALE_PIN,	0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE",	CONFIG_SYS_NAND_CLE_PIN,	0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCS",	CONFIG_SYS_NAND_ENABLE_PIN,	1, PIO_PULLUP, PIO_OUTPUT},
		{"D0",	AT91C_PIN_PD(6), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D1",	AT91C_PIN_PD(7), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D2",	AT91C_PIN_PD(8), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D3",	AT91C_PIN_PD(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D4",	AT91C_PIN_PD(10), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D5",	AT91C_PIN_PD(11), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D6",	AT91C_PIN_PD(12), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D7",	AT91C_PIN_PD(13), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc nand_pins_lo[] = {
		{"NANDOE",	CONFIG_SYS_NAND_OE_PIN,		0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDWE",	CONFIG_SYS_NAND_WE_PIN,		0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDALE",	CONFIG_SYS_NAND_ALE_PIN,	0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE",	CONFIG_SYS_NAND_CLE_PIN,	0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCS", 	CONFIG_SYS_NAND_ENABLE_PIN,	1, PIO_PULLUP, PIO_OUTPUT},
		{(char *)0,	0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	reg = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
	reg |= AT91C_EBI_CS3A_SM;
	if ((get_cm_rev() == 'A') && (get_cm_vendor() == VENDOR_EMBEST))
		reg &= ~AT91C_EBI_NFD0_ON_D16;
	else
		reg |= (AT91C_EBI_DDR_MP_EN | AT91C_EBI_NFD0_ON_D16);

	reg &= ~AT91C_EBI_DRV;
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
		| AT91C_SMC_NRDCYCLE_(7)),
		AT91C_BASE_SMC + SMC_CYCLE3);

	writel((AT91C_SMC_READMODE
		| AT91C_SMC_WRITEMODE
		| AT91C_SMC_NWAITM_NWAIT_DISABLE
		| AT91C_SMC_DBW_WIDTH_BITS_8
		| AT91_SMC_TDF_(1)),
		AT91C_BASE_SMC + SMC_CTRL3);

	/* Configure the PIO controller */
	if ((get_cm_rev() == 'A') && (get_cm_vendor() == VENDOR_EMBEST))
		pio_configure(nand_pins_lo);
	else
		pio_configure(nand_pins_hi);

	writel((1 << AT91C_ID_PIOC_D), (PMC_PCER + AT91C_BASE_PMC));
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

void one_wire_hw_init(void)
{
	const struct pio_desc wire_pio[] = {
		{"1-Wire", AT91C_PIN_PB(18), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	writel((1 << AT91C_ID_PIOA_B), (PMC_PCER + AT91C_BASE_PMC));
	pio_configure(wire_pio);
}
