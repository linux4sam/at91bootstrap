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
#include "arch/tz_matrix.h"
#include "sama5d4ek.h"
#include "tz_utils.h"
#include "matrix.h"

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

#if defined(CONFIG_MATRIX)
static int matrix_configure_slave(void)
{
	unsigned int ddr_port;
	unsigned int ssr_setting, sasplit_setting, srtop_setting;

	/*
	 * Matrix 0 (H64MX)
	 */

	/* 0: Bridge from H64MX to AXIMX */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					H64MX_SLAVE_BRIDGE_TO_AXIMX,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 1: H64MX Peripheral Bridge: Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					H64MX_SLAVE_PERI_BRIDGE,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 2: Video Decoder 128K: Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					H64MX_SLAVE_VIDEO_DECODER,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 4 ~ 10 DDR2 Port1 ~ 7: Non-Secure */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_128M);
	sasplit_setting = (MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_128M)
				| MATRIX_SASPLIT(1, MATRIX_SASPLIT_VALUE_128M)
				| MATRIX_SASPLIT(2, MATRIX_SASPLIT_VALUE_128M)
				| MATRIX_SASPLIT(3, MATRIX_SASPLIT_VALUE_128M));
	ssr_setting = (MATRIX_LANSECH_NS(0)
			| MATRIX_LANSECH_NS(1)
			| MATRIX_LANSECH_NS(2)
			| MATRIX_LANSECH_NS(3)
			| MATRIX_RDNSECH_NS(0)
			| MATRIX_RDNSECH_NS(1)
			| MATRIX_RDNSECH_NS(2)
			| MATRIX_RDNSECH_NS(3)
			| MATRIX_WRNSECH_NS(0)
			| MATRIX_WRNSECH_NS(1)
			| MATRIX_WRNSECH_NS(2)
			| MATRIX_WRNSECH_NS(3));
	/* DDR port 0 not used from NWd */
	for (ddr_port = 1; ddr_port < 8; ddr_port++) {
		matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					(H64MX_SLAVE_DDR2_PORT_0 + ddr_port),
					srtop_setting,
					sasplit_setting,
					ssr_setting);
	}

	/* 11: Internal SRAM 128K
	 * TOP0 is set to 128K
	 * SPLIT0 is set to 64K
	 * LANSECH0 is set to 0, the low area of region 0 is the Securable one
	 * RDNSECH0 is set to 0, region 0 Securable area is secured for reads.
	 * WRNSECH0 is set to 0, region 0 Securable area is secured for writes
	 */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_128K);
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_64K);
	ssr_setting = (MATRIX_LANSECH_S(0)
			| MATRIX_RDNSECH_S(0)
			| MATRIX_WRNSECH_S(0));
	matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					H64MX_SLAVE_INTERNAL_SRAM,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 12:  Bridge from H64MX to H32MX: Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					H64MX_SLAVE_BRIDGE_TO_H32MX,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/*
	 * Matrix 1 (H32MX)
	 */

	/* 0: Bridge from H32MX to H64MX */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_BRIDGE_TO_H64MX,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 1: H32MX Peripheral Bridge 0 */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_PERI_BRIDGE_0,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 2: H32MX Peripheral Bridge 1 */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_PERI_BRIDGE_1,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 3: External Bus Interface: Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_EXTERNAL_EBI,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 4: NFC SRAM (4K): Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_NFC_SRAM,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 5: DPHS RAM(1M), UHP OHCI (1M), UHP EHCI (1M): Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_USB,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 6: Soft Modem (1M): Non-Secure */
	srtop_setting = 0xffffffff;
	sasplit_setting = 0xffffffff;
	ssr_setting = 0xffffffff;
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_SMD,
					srtop_setting,
					sasplit_setting,
					ssr_setting);
	return 0;
}

static unsigned int security_ps_peri_id[] = {
	AT91C_ID_VDEC,
	AT91C_ID_PIOA,
	AT91C_ID_PIOB,
	AT91C_ID_PIOC,
	AT91C_ID_PIOE,
	AT91C_ID_USART2,
	AT91C_ID_USART3,
	AT91C_ID_USART4,
	AT91C_ID_TWI0,
	AT91C_ID_TWI2,
	AT91C_ID_HSMCI0,
	AT91C_ID_HSMCI1,
	AT91C_ID_TC0,
	AT91C_ID_TC1,
	AT91C_ID_UHPHS,
	AT91C_ID_UDPHS,
	AT91C_ID_LCDC,
	AT91C_ID_GMAC,
	AT91C_ID_SPI0,
	AT91C_ID_SPI1,
	AT91C_ID_SMD,
};

static int matrix_config_periheral(void)
{
	unsigned int *peri_id = security_ps_peri_id;
	unsigned int array_size = sizeof(security_ps_peri_id) / sizeof(unsigned int);
	int ret;

	ret = matrix_configure_peri_security(peri_id, array_size);
	if (ret)
		return -1;

	return 0;
}

static int matrix_init(void)
{
	int ret;

	matrix_write_disable(AT91C_BASE_MATRIX64);
	matrix_write_disable(AT91C_BASE_MATRIX32);

	ret = matrix_configure_slave();
	if (ret)
		return -1;

	ret = matrix_config_periheral();
	if (ret)
		return -1;

	return 0;
}
#endif	/* #if defined(CONFIG_MATRIX) */

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

#if defined(CONFIG_ENTER_NWD)
	cpacr_init();

	/* Program the DACR to allow client access to *all* domains */
	dacr_swd_init();
#endif

#if defined(CONFIG_MATRIX)
	/* Initialize the matrix */
	matrix_init();
#endif

	/* initialize the dbgu */
	initialize_dbgu();

#if defined(CONFIG_MATRIX)
	matrix_read_slave_security();
	matrix_read_periperal_security();
#endif

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
	const struct pio_desc spi0_pins[] = {
		{"SPI0_MISO",	AT91C_PIN_PC(0), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_MOSI",	AT91C_PIN_PC(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_SPCK",	AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	pio_configure(spi0_pins);

	pmc_enable_periph_clock(AT91C_ID_PIOC);
	pmc_enable_periph_clock(AT91C_ID_SPI0);
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
