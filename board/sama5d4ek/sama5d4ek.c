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
#include "usart.h"
#include "debug.h"
#include "ddramc.h"
#include "spi.h"
#include "gpio.h"
#include "slowclk.h"
#include "timer.h"
#include "watchdog.h"
#include "string.h"
#include "onewire_info.h"

#include "arch/at91_pmc.h"
#include "arch/at91_rstc.h"
#include "arch/sama5_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "arch/at91_sfr.h"
#include "sama5d4ek.h"

static void at91_dbgu_hw_init(void)
{
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PE(16), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"TXD", AT91C_PIN_PE(17), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(dbgu_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOE);
	pmc_enable_periph_clock(AT91C_ID_USART3);
}

static void initialize_dbgu(void)
{
	unsigned int baudrate = 115200;

	at91_dbgu_hw_init();
	usart_init(BAUDRATE(MASTER_CLOCK / 2, baudrate));
}

#ifdef CONFIG_DDR2
static void ddramc_reg_config(struct ddramc_register *ddramc_config)
{
#if defined(CONFIG_BUS_SPEED_133MHZ)

	ddramc_config->mdr = (AT91C_DDRC2_DBW_32_BITS
				| AT91C_DDRC2_MD_DDR2_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9
				| AT91C_DDRC2_NR_14
				| AT91C_DDRC2_CAS_3
				| AT91C_DDRC2_DLL_RESET_DISABLED
				| AT91C_DDRC2_DIS_DLL_DISABLED
				| AT91C_DDRC2_ENRDM_ENABLE
				| AT91C_DDRC2_NB_BANKS_8
				| AT91C_DDRC2_NDQS_DISABLED
				| AT91C_DDRC2_DECOD_INTERLEAVED
				| AT91C_DDRC2_UNAL_SUPPORTED);

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
			| AT91C_DDRC2_TXSNR_28          /* 195 + 10 = 205ns */
			| AT91C_DDRC2_TRFC_26);         /* 26 * 7.5 = 195 ns */

	ddramc_config->t2pr = (AT91C_DDRC2_TFAW_7       /* 7 * 7.5 = 52.5 ns */
			| AT91C_DDRC2_TRTP_2            /* 2 clock cycles min */
			| AT91C_DDRC2_TRPA_2            /* 2 * 7.5 = 15 ns */
			| AT91C_DDRC2_TXARDS_7          /* 7 clock cycles */
			| AT91C_DDRC2_TXARD_8);         /* MR12 = 1 */

#elif defined(CONFIG_BUS_SPEED_170MHZ)

	ddramc_config->mdr = (AT91C_DDRC2_DBW_32_BITS
				| AT91C_DDRC2_MD_DDR2_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9
				| AT91C_DDRC2_NR_14
				| AT91C_DDRC2_CAS_3
				| AT91C_DDRC2_DLL_RESET_DISABLED
				| AT91C_DDRC2_DIS_DLL_DISABLED
				| AT91C_DDRC2_NB_BANKS_8
				| AT91C_DDRC2_DECOD_INTERLEAVED
				| AT91C_DDRC2_UNAL_SUPPORTED);

	/*
	 * The DDR2-SDRAM device requires a refresh every 15.625 us or 7.81 us.
	 * With a 170 MHz frequency, the refresh timer count register must be
	 * (7.81 x 170 MHz) ~ 1328 i.e. 0x530.
	 */
	ddramc_config->rtr = 0x530;     /* Refresh timer: 7.8125us */

	/* One clock cycle @ 170 MHz = 5.9 ns */
	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_7       /* 7 * 5.9 = 41.3 ns */
			| AT91C_DDRC2_TRCD_3            /* 3 * 5.9 = 17.7 ns */
			| AT91C_DDRC2_TWR_3             /* 3 * 5.9 = 17.7 ns */
			| AT91C_DDRC2_TRC_10            /* 10 * 5.9 = 59  ns */
			| AT91C_DDRC2_TRP_3             /* 3 * 5.9 = 17.7 ns */
			| AT91C_DDRC2_TRRD_2            /* 2 * 5.9 = 11.8 ns */
			| AT91C_DDRC2_TWTR_2            /* 2 clock cycles min */
			| AT91C_DDRC2_TMRD_2);          /* 2 clock cycles */

	ddramc_config->t1pr = (AT91C_DDRC2_TXP_2        /*  2 clock cycles */
			| AT91C_DDRC2_TXSRD_200         /* 200 clock cycles */
			| AT91C_DDRC2_TXSNR_35          /* 195 + 10 = 205ns */
			| AT91C_DDRC2_TRFC_34);         /* 34 * 5.9 = 200.6ns */

	ddramc_config->t2pr = (AT91C_DDRC2_TFAW_8       /* 8 * 5.9 = 47.2 ns */
			| AT91C_DDRC2_TRTP_2            /* 2 clock cycles min */
			| AT91C_DDRC2_TRPA_3            /* 3 * 5.9 = 17.7 ns */
			| AT91C_DDRC2_TXARDS_8          /* MR12 = 1 */
			| AT91C_DDRC2_TXARD_2);         /* MR12 = 0 */

#else
#error "No CLK setting defined"
#endif
}

static void ddramc_init(void)
{
	struct ddramc_register ddramc_reg;
	unsigned int reg;

	ddramc_reg_config(&ddramc_reg);

	/* enable ddr2 clock */
	pmc_enable_periph_clock(AT91C_ID_MPDDRC);
	pmc_enable_system_clock(AT91C_PMC_DDR);

	/* configure Shift Sampling Point of Data */
#if defined(CONFIG_BUS_SPEED_133MHZ)
	reg = AT91C_MPDDRC_RD_DATA_PATH_NO_SHIFT;
#else
	reg = AT91C_MPDDRC_RD_DATA_PATH_ONE_CYCLES;
#endif
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_RD_DATA_PATH));

	/* MPDDRC I/O Calibration Register */
	reg = readl(AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR);
	reg &= ~AT91C_MPDDRC_RDIV;
	reg &= ~AT91C_MPDDRC_TZQIO;
	reg |= AT91C_MPDDRC_RDIV_DDR2_RZQ_50;
#if defined(CONFIG_BUS_SPEED_133MHZ)
	reg |= AT91C_MPDDRC_TZQIO_4;	/* @ 133 MHz */
#else
	reg |= AT91C_MPDDRC_TZQIO_5;	/* @ 170 MHz */
#endif
	reg |= AT91C_MPDDRC_EN_CALIB;
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR));

	/* DDRAM2 Controller initialize */
	ddram_initialize(AT91C_BASE_MPDDRC, AT91C_BASE_DDRCS, &ddramc_reg);
}
#endif /* #ifdef CONFIG_DDR2 */

static void one_wire_hw_init(void)
{
	const struct pio_desc one_wire_pio[] = {
		{"1-Wire", CONFIG_SYS_ONE_WIRE_PIN, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(one_wire_pio);
	pmc_enable_periph_clock(AT91C_ID_PIOE);
}

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	at91_disable_wdt();

	/* At this stage the main oscillator is supposed
	 * to be enabled PCK = MCK = MOSC
	 */

	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

	/* Initialize PLLA charge pump */
	/* not needed for SAMA5D4 */
	pmc_init_pll(0);

	/* Switch MCK on PLLA output */
	pmc_cfg_mck(BOARD_PRESCALER_PLLA, PLL_LOCK_TIMEOUT);

	/* Setup AHB 32-bit Matrix Divisor */
	pmc_cfg_h32mxdiv(BOARD_H32MX, PLL_LOCK_TIMEOUT);

	/* Enable External Reset */
	writel(AT91C_RSTC_KEY_UNLOCK | AT91C_RSTC_URSTEN,
					AT91C_BASE_RSTC + RSTC_RMR);

	/* initialize the dbgu */
	initialize_dbgu();

	/* Init timer */
	timer_init();

#ifdef CONFIG_SCLK
	slowclk_enable_osc32();
#endif

#ifdef CONFIG_DDR2
	/* Initialize MPDDR Controller */
	ddramc_init();
#endif
	/* load one wire information */
	one_wire_hw_init();

#ifdef CONFIG_USER_HW_INIT
	hw_init_hook();
#endif
}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void at91_spi0_hw_init(void)
{
	/* Configure PIN for SPI0 */
	const struct pio_desc spi1_pins[] = {
		{"SPI1_MISO",	AT91C_PIN_PB(18), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI1_MOSI",	AT91C_PIN_PB(19), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI1_SPCK",	AT91C_PIN_PB(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI1_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	pio_configure(spi1_pins);

	pmc_enable_periph_clock(AT91C_ID_PIOB);
	pmc_enable_periph_clock(AT91C_ID_SPI1);
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
static void sdcard_set_of_name_board(char *of_name)
{
	strcpy(of_name, "sama5d4ek.dtb");
}

void at91_mci0_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCI0_CK", AT91C_PIN_PC(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"MCI0_CDA", AT91C_PIN_PC(5), 0, PIO_DEFAULT, PIO_PERIPH_B},

		{"MCI0_DA0", AT91C_PIN_PC(6), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"MCI0_DA1", AT91C_PIN_PC(7), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"MCI0_DA2", AT91C_PIN_PC(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"MCI0_DA3", AT91C_PIN_PC(9), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	pio_configure(mci_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOC);
	pmc_enable_periph_clock(AT91C_ID_HSMCI0);

	/* Set of name function pointer */
	sdcard_set_of_name = &sdcard_set_of_name_board;
}
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	/* Configure nand pins */
	const struct pio_desc nand_pins[] = {
		{"NANDOE",	CONFIG_SYS_NAND_OE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDWE",	CONFIG_SYS_NAND_WE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDALE",	CONFIG_SYS_NAND_ALE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE",	CONFIG_SYS_NAND_CLE_PIN,
					0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCS",	CONFIG_SYS_NAND_ENABLE_PIN,
					1, PIO_DEFAULT, PIO_OUTPUT},
		{"D0",	AT91C_PIN_PC(5), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D1",	AT91C_PIN_PC(6), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D2",	AT91C_PIN_PC(7), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D3",	AT91C_PIN_PC(8), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D4",	AT91C_PIN_PC(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D5",	AT91C_PIN_PC(10), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D6",	AT91C_PIN_PC(11), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"D7",	AT91C_PIN_PC(12), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the nand controller pins*/
	pio_configure(nand_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOC);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_HSMC);

	/* EBI Configuration Register */
	writel((AT91C_EBICFG_DRIVE0_HIGH
		| AT91C_EBICFG_PULL0_NONE
		| AT91C_EBICFG_DRIVE1_HIGH
		| AT91C_EBICFG_PULL1_NONE), SFR_EBICFG + AT91C_BASE_SFR);

	/* Configure SMC CS3 for NAND/SmartMedia */
	writel(AT91C_SMC_SETUP_NWE(2)
		| AT91C_SMC_SETUP_NCS_WR(2)
		| AT91C_SMC_SETUP_NRD(2)
		| AT91C_SMC_SETUP_NCS_RD(2),
		(ATMEL_BASE_SMC + SMC_SETUP3));

	writel(AT91C_SMC_PULSE_NWE(7)
		| AT91C_SMC_PULSE_NCS_WR(7)
		| AT91C_SMC_PULSE_NRD(7)
		| AT91C_SMC_PULSE_NCS_RD(7),
		(ATMEL_BASE_SMC + SMC_PULSE3));

	writel(AT91C_SMC_CYCLE_NWE(13)
		| AT91C_SMC_CYCLE_NRD(13),
		(ATMEL_BASE_SMC + SMC_CYCLE3));

	writel(AT91C_SMC_TIMINGS_TCLR(3)
		| AT91C_SMC_TIMINGS_TADL(27)
		| AT91C_SMC_TIMINGS_TAR(3)
		| AT91C_SMC_TIMINGS_TRR(6)
		| AT91C_SMC_TIMINGS_TWB(5)
		| AT91C_SMC_TIMINGS_RBNSEL(3)
		| AT91C_SMC_TIMINGS_NFSEL,
		(ATMEL_BASE_SMC + SMC_TIMINGS3));

	writel(AT91C_SMC_MODE_READMODE_NRD_CTRL
		| AT91C_SMC_MODE_WRITEMODE_NWE_CTRL
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
