/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation

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
#include "sama5d3_xplained.h"
#include "macb.h"
#include "twi.h"
#include "act8865.h"

static void at91_dbgu_hw_init(void)
{
	/* Configure DBGU pin */
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/*  Configure the dbgu pins */
	pmc_enable_periph_clock(AT91C_ID_PIOB);
	pio_configure(dbgu_pins);

	/* Enable clock */
	pmc_enable_periph_clock(AT91C_ID_DBGU);
}

static void initialize_dbgu(void)
{
	at91_dbgu_hw_init();
	usart_init(BAUDRATE(MASTER_CLOCK, 115200));
}

#ifdef CONFIG_DDR2
static void ddramc_reg_config(struct ddramc_register *ddramc_config)
{
	ddramc_config->mdr = (AT91C_DDRC2_DBW_32_BITS
				| AT91C_DDRC2_MD_DDR2_SDRAM);

	ddramc_config->cr = (AT91C_DDRC2_NC_DDR10_SDR9
				| AT91C_DDRC2_NR_13
				| AT91C_DDRC2_CAS_3
				| AT91C_DDRC2_DLL_RESET_DISABLED
				| AT91C_DDRC2_DIS_DLL_DISABLED
				| AT91C_DDRC2_ENRDM_ENABLE
				| AT91C_DDRC2_NB_BANKS_8
				| AT91C_DDRC2_NDQS_DISABLED
				| AT91C_DDRC2_DECOD_INTERLEAVED
				| AT91C_DDRC2_UNAL_SUPPORTED);

#if defined(CONFIG_BUS_SPEED_133MHZ)
	/*
	 * The DDR2-SDRAM device requires a refresh every 15.625 us or 7.81 us.
	 * With a 133 MHz frequency, the refresh timer count register must to be
	 * set with (15.625 x 133 MHz) ~ 2084 i.e. 0x824
	 * or (7.81 x 133 MHz) ~ 1039 i.e. 0x40F.
	 */
	ddramc_config->rtr = 0x40F;     /* Refresh timer: 7.812us */

	/* One clock cycle @ 133 MHz = 7.5 ns */
	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_(6)	/* 6 * 7.5 = 45 ns */
			| AT91C_DDRC2_TRCD_(2)		/* 2 * 7.5 = 22.5 ns */
			| AT91C_DDRC2_TWR_(2)		/* 2 * 7.5 = 15   ns */
			| AT91C_DDRC2_TRC_(8)		/* 8 * 7.5 = 75   ns */
			| AT91C_DDRC2_TRP_(2)		/* 2 * 7.5 = 15   ns */
			| AT91C_DDRC2_TRRD_(2)		/* 2 * 7.5 = 15   ns */
			| AT91C_DDRC2_TWTR_(2)		/* 2 clock cycles min */
			| AT91C_DDRC2_TMRD_(2));	/* 2 clock cycles */

	ddramc_config->t1pr = (AT91C_DDRC2_TXP_(2)	/* 2 clock cycles */
			| AT91C_DDRC2_TXSRD_(200)	/* 200 clock cycles */
			| AT91C_DDRC2_TXSNR_(19)	/* 19 * 7.5 = 142.5 ns */
			| AT91C_DDRC2_TRFC_(17));	/* 17 * 7.5 = 127.5 ns */

	ddramc_config->t2pr = (AT91C_DDRC2_TFAW_(6)	/* 6 * 7.5 = 45 ns */
			| AT91C_DDRC2_TRTP_(2)		/* 2 clock cycles min */
			| AT91C_DDRC2_TRPA_(2)		/* 2 * 7.5 = 15 ns */
			| AT91C_DDRC2_TXARDS_(8)	/* = TXARD */
			| AT91C_DDRC2_TXARD_(8));	/* MR12 = 1 */

#elif defined(CONFIG_BUS_SPEED_166MHZ)
	/*
	 * The DDR2-SDRAM device requires a refresh of all rows every 64ms.
	 * ((64ms) / 8192) * 166MHz = 1296 i.e. 0x510
	 */
	ddramc_config->rtr = 0x510;

	/* One clock cycle @ 166 MHz = 6.0 ns */
	ddramc_config->t0pr = (AT91C_DDRC2_TRAS_(8)	/* 8 * 6 = 48 ns */
			| AT91C_DDRC2_TRCD_(3)		/* 3 * 6 = 18 ns */
			| AT91C_DDRC2_TWR_(3)		/* 3 * 6 = 18 ns */
			| AT91C_DDRC2_TRC_(10)		/* 10 * 6 = 60 ns */
			| AT91C_DDRC2_TRP_(3)		/* 3 * 6 = 18 ns */
			| AT91C_DDRC2_TRRD_(2)		/* 2 * 6 = 12 ns */
			| AT91C_DDRC2_TWTR_(2)		/* 2 clock cycles */
			| AT91C_DDRC2_TMRD_(2));	/* 2 clock cycles */

	ddramc_config->t1pr = (AT91C_DDRC2_TXP_(2)	/* 2 * 6 = 12ns */
			| AT91C_DDRC2_TXSRD_(200)	/* 200 clock cycles */
			| AT91C_DDRC2_TXSNR_(23)	/* 23 * 6 = 138 ns */
			| AT91C_DDRC2_TRFC_(22));	/* 22 * 6 = 132 ns */

	ddramc_config->t2pr = (AT91C_DDRC2_TFAW_(8)	/* 45 ns */
			| AT91C_DDRC2_TRTP_(2)		/* 2 * 6 = 15ns */
			| AT91C_DDRC2_TRPA_(3)		/* 15 ns */
			| AT91C_DDRC2_TXARDS_(8)	/* = TXARD */
			| AT91C_DDRC2_TXARD_(8));	/* 8 clock cycles */

#else
#error "No bus clock provided!"
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

	/* Init the special register for sama5d3x */
	/* MPDDRC DLL Slave Offset Register: DDR2 configuration */
	reg = AT91C_MPDDRC_S0OFF_1
		| AT91C_MPDDRC_S2OFF_1
		| AT91C_MPDDRC_S3OFF_1;
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_DLL_SOR));

	/* MPDDRC DLL Master Offset Register */
	/* write master + clk90 offset */
	reg = AT91C_MPDDRC_MOFF_7
		| AT91C_MPDDRC_CLK90OFF_31
		| AT91C_MPDDRC_SELOFF_ENABLED | AT91C_MPDDRC_KEY;
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_DLL_MOR));

	/* MPDDRC I/O Calibration Register */
	/* DDR2 RZQ = 50 Ohm */
	/* TZQIO = 4 */
	reg = AT91C_MPDDRC_RDIV_DDR2_RZQ_50
		| AT91C_MPDDRC_TZQIO_4;
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR));

	/* DDRAM2 Controller initialize */
	ddram_initialize(AT91C_BASE_MPDDRC, AT91C_BASE_DDRCS, &ddramc_reg);
}
#endif /* #ifdef CONFIG_DDR2 */

#ifdef CONFIG_USER_HW_INIT
/*
 * Special setting for PM.
 * Since for the chips with no EMAC or GMAC, No actions is done to make
 * its phy to enter the power save mode when linux system enter suspend
 * to memory or standby.
 * And it causes the VDDCORE current is higher than our expection.
 * So set GMAC clock related pins GTXCK(PB8), GRXCK(PB11), GMDCK(PB16),
 * G125CK(PB18) and EMAC clock related pins EREFCK(PC7), EMDC(PC8)
 * to Pullup and Pulldown disabled, and output low.
 */

#define GMAC_PINS	((0x01 << 8) | (0x01 << 11) \
				| (0x01 << 16) | (0x01 << 18))

#define EMAC_PINS	((0x01 << 7) | (0x01 << 8))

static void at91_special_pio_output_low(void)
{
	unsigned int base;
	unsigned int value;

	base = AT91C_BASE_PIOB;
	value = GMAC_PINS;

	writel((1 << AT91C_ID_PIOB), (PMC_PCER + AT91C_BASE_PMC));

	writel(value, base + PIO_REG_PPUDR);	/* PIO_PPUDR */
	writel(value, base + PIO_REG_PPDDR);	/* PIO_PPDDR */
	writel(value, base + PIO_REG_PER);	/* PIO_PER */
	writel(value, base + PIO_REG_OER);	/* PIO_OER */
	writel(value, base + PIO_REG_CODR);	/* PIO_CODR */

	base = AT91C_BASE_PIOC;
	value = EMAC_PINS;

	writel((1 << AT91C_ID_PIOC), (PMC_PCER + AT91C_BASE_PMC));

	writel(value, base + PIO_REG_PPUDR);	/* PIO_PPUDR */
	writel(value, base + PIO_REG_PPDDR);	/* PIO_PPDDR */
	writel(value, base + PIO_REG_PER);	/* PIO_PER */
	writel(value, base + PIO_REG_OER);	/* PIO_OER */
	writel(value, base + PIO_REG_CODR);	/* PIO_CODR */
}
#endif

#if defined(CONFIG_PM_EXTERNAL_DEVICES)
#if defined(CONFIG_MACB)
static void gmac_hw_init(void)
{
	const struct pio_desc macb_pins[] = {
		{"GMDC",	AT91C_PIN_PB(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"GMDIO",	AT91C_PIN_PB(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(macb_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOB);
}

static void emac_hw_init(void)
{
	const struct pio_desc macb_pins[] = {
		{"EMDC",	AT91C_PIN_PC(8), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"EMDIO",	AT91C_PIN_PC(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(macb_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOC);
}

static int phys_enter_power_down(void)
{
	struct mii_bus macb_mii_bus;

	gmac_hw_init();
	emac_hw_init();

	pmc_enable_periph_clock(AT91C_ID_GMAC);

	macb_mii_bus.name = "GMAC KSZ9011RNI";
	macb_mii_bus.reg_base = (void *)AT91C_BASE_GMAC;
	macb_mii_bus.phy_addr = 1;

	if (phy_power_down_mode(&macb_mii_bus)) {
		dbg_info("%s: Failed to enter power down mode\n",
						macb_mii_bus.name);
	}

	pmc_disable_periph_clock(AT91C_ID_GMAC);

	macb_mii_bus.name = "EMAC KSZ8081RNB";
	macb_mii_bus.reg_base = (void *)AT91C_BASE_EMAC;
	macb_mii_bus.phy_addr = 1;

	pmc_enable_periph_clock(AT91C_ID_EMAC);

	if (phy_power_down_mode(&macb_mii_bus)) {
		dbg_info("%s: Failed to enter power down mode\n",
						macb_mii_bus.name);
	}

	pmc_disable_periph_clock(AT91C_ID_EMAC);

	return 0;
}
#endif	/* #if defined(CONFIG_MACB) */
#endif	/* #if defined(CONFIG_PM_EXTERNAL_DEVICES) */

#ifdef CONFIG_TWI

#define TWI_CLOCK	400000

static void at91_twi1_hw_init(void)
{
	const struct pio_desc twi0_pins[] = {
		{"TWD", AT91C_PIN_PC(26), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"TWCK", AT91C_PIN_PC(27), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(twi0_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOC);

	pmc_enable_periph_clock(AT91C_ID_TWI1);
}

static void twi_init(void)
{
	unsigned int bus_clock = MASTER_CLOCK;

	at91_twi_base = AT91C_BASE_TWI1;

	at91_twi1_hw_init();

	twi_configure_master_mode(bus_clock, TWI_CLOCK);
}
#endif /* #ifdef CONFIG_TWI */

#ifdef CONFIG_ACT8865
static int sama5d4ek_act8865_set_reg_voltage(void)
{
	unsigned char reg, value;
	int ret;

	/* Check ACT8865 I2C interface */
	if (act8865_check_i2c_disabled())
		return 0;

	/* Enable REG5 output 3.3V */
	reg = REG5_0;
	value = ACT8865_3V3;
	ret = act8865_set_reg_voltage(reg, value);
	if (ret) {
		dbg_info("ACT8865: Failed to make REG5 output 3300mV\n");
		return -1;
	}

	dbg_info("ACT8865: The REG5 output 3300mV\n");

	return 0;
}
#endif

static void at91_disable_smd_clock(void)
{
	/*
	 * set pin DIBP to pull-up and DIBN to pull-down
	 * to save power on VDDIOP0
	 */
	pmc_enable_system_clock(AT91C_PMC_SMDCK);
	pmc_set_smd_clock_divider(AT91C_PMC_SMDDIV);
	pmc_enable_periph_clock(AT91C_ID_SMD);
	writel(0xF, (0x0C + AT91C_BASE_SMD));
	pmc_disable_periph_clock(AT91C_ID_SMD);
	pmc_disable_system_clock(AT91C_PMC_SMDCK);
}

#ifdef CONFIG_HW_INIT
void hw_init(void)
{
	/* Disable watchdog */
	at91_disable_wdt();

	/*
	 * At this stage the main oscillator
	 * is supposed to be enabled PCK = MCK = MOSC
	 */

	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

	/* Initialize PLLA charge pump */
	pmc_init_pll(AT91C_PMC_IPLLA_3);

	/* Switch PCK/MCK on Main clock output */
	pmc_cfg_mck(BOARD_PRESCALER_MAIN_CLOCK, PLL_LOCK_TIMEOUT);

	/* Switch PCK/MCK on PLLA output */
	pmc_cfg_mck(BOARD_PRESCALER_PLLA, PLL_LOCK_TIMEOUT);

#ifdef CONFIG_USER_HW_INIT
	/* Set GMAC & EMAC pins to output low */
	at91_special_pio_output_low();
#endif

	/* Disable the software modem clock */
	at91_disable_smd_clock();

	/* Init timer */
	timer_init();

#ifdef CONFIG_SCLK
	slowclk_enable_osc32();
#endif

	/* initialize the dbgu */
	initialize_dbgu();

#ifdef CONFIG_DDR2
	/* Initialize MPDDR Controller */
	ddramc_init();
#endif

#ifdef CONFIG_TWI
	twi_init();
#endif

#ifdef CONFIG_ACT8865
	/* Set ACT8865 REG power saving mode */
	act8865_set_power_saving_mode();

	/* Set ACT8865 output voltage */
	sama5d4ek_act8865_set_reg_voltage();

	/* Dsiable ACT8865 I2C interface */
	if (act8865_workaround_disable_i2c())
		while (1)
			;
#endif

#ifdef CONFIG_PM_EXTERNAL_DEVICES
#ifdef CONFIG_MACB
	/* Make PHYs to power down mode */
	phys_enter_power_down();
#endif
#endif	/* #ifdef CONFIG_PM_EXTERNAL_DEVICES */
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
	pmc_enable_periph_clock(AT91C_ID_PIOD);
	pio_configure(spi0_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SPI0);
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
static void sdcard_set_of_name_board(char *of_name)
{
	strcat(of_name, "at91-sama5d3_xplained.dtb");
}

void at91_mci0_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PD(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PD(0), 0, PIO_DEFAULT, PIO_PERIPH_A},

		{"MCDA0", AT91C_PIN_PD(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA4", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA5", AT91C_PIN_PD(6), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA6", AT91C_PIN_PD(7), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA7", AT91C_PIN_PD(8), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	pmc_enable_periph_clock(AT91C_ID_HSMCI0);
	pio_configure(mci_pins);

	/* Enable the clock */
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
		{"NANDALE", AT91C_PIN_PE(21), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"NANDCLE", AT91C_PIN_PE(22), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the nand controller pins*/
	pmc_enable_periph_clock(AT91C_ID_PIOE);
	pio_configure(nand_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SMC);

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
#endif /* #ifdef CONFIG_NANDFLASH */
