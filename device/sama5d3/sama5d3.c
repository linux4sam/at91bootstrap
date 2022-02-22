// Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "hardware.h"
#include "pmc.h"
#include "usart.h"
#include "debug.h"
#include "ddramc.h"
#include "spi.h"
#include "gpio.h"
#include "timer.h"
#include "watchdog.h"
#include "string.h"
#include "board_hw_info.h"
#include "led.h"
#include "arch/at91_pmc/pmc.h"
#include "arch/at91_rstc.h"
#include "arch/sama5_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "sama5d3_board.h"
#include "twi.h"

#ifdef CONFIG_MMU
#include "mmu_cp15.h"
#endif

__attribute__((weak)) void HDMI_Qt1070_workaround(void);

#ifdef CONFIG_LOAD_ONE_WIRE
#include "ds24xx.h"
#endif

static void at91_dbgu_hw_init(void)
{
	/* Configure DBGU pin */
	const struct pio_desc dbgu_pins[] = {
		{"RXD", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/*  Configure the dbgu pins */
	pmc_enable_periph_clock(AT91C_ID_PIOB, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(dbgu_pins);

	/* Enable clock */
	pmc_enable_periph_clock(AT91C_ID_DBGU, PMC_PERIPH_CLK_DIVIDER_NA);
}

static void initialize_dbgu(void)
{
	at91_dbgu_hw_init();
	usart_init(BAUDRATE(MASTER_CLOCK, 115200));
}

#if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY)
static void recovery_buttons_hw_init(void)
{
	/* Configure recovery button PINs */
	const struct pio_desc recovery_button_pins[] = {
		{"RECOVERY_BUTTON", CONFIG_SYS_RECOVERY_BUTTON_PIN, 0, PIO_PULLUP, PIO_INPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pmc_enable_periph_clock(AT91C_ID_PIOE, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(recovery_button_pins);
}
#endif /* #if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY) */

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

	pmc_enable_periph_clock(AT91C_ID_PIOB, PMC_PERIPH_CLK_DIVIDER_NA);

	writel(value, base + PIO_REG_PPUDR);	/* PIO_PPUDR */
	writel(value, base + PIO_REG_PPDDR);	/* PIO_PPDDR */
	writel(value, base + PIO_REG_PER);	/* PIO_PER */
	writel(value, base + PIO_REG_OER);	/* PIO_OER */
	writel(value, base + PIO_REG_CODR);	/* PIO_CODR */

	base = AT91C_BASE_PIOC;
	value = EMAC_PINS;

	pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);

	writel(value, base + PIO_REG_PPUDR);	/* PIO_PPUDR */
	writel(value, base + PIO_REG_PPDDR);	/* PIO_PPDDR */
	writel(value, base + PIO_REG_PER);	/* PIO_PER */
	writel(value, base + PIO_REG_OER);	/* PIO_OER */
	writel(value, base + PIO_REG_CODR);	/* PIO_CODR */
}

#if defined(CONFIG_MAC0_PHY)
unsigned int at91_eth0_hw_init(void)
{
	unsigned int base_addr = AT91C_BASE_GMAC;

	const struct pio_desc macb_pins[] = {
		{"GMDC",	AT91C_PIN_PB(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"GMDIO",	AT91C_PIN_PB(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(macb_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOB, PMC_PERIPH_CLK_DIVIDER_NA);

	pmc_enable_periph_clock(AT91C_ID_GMAC, PMC_PERIPH_CLK_DIVIDER_NA);

	return base_addr;
}
#endif

#if defined(CONFIG_MAC1_PHY)
unsigned int at91_eth1_hw_init(void)
{
	unsigned int base_addr = AT91C_BASE_EMAC;

	const struct pio_desc macb_pins[] = {
		{"EMDC",	AT91C_PIN_PC(8), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"EMDIO",	AT91C_PIN_PC(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(macb_pins);
	pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);

	pmc_enable_periph_clock(AT91C_ID_EMAC, PMC_PERIPH_CLK_DIVIDER_NA);

	return base_addr;
}
#endif

#if defined(CONFIG_MACB)
void at91_disable_mac_clock(void)
{
#if defined(CONFIG_MAC0_PHY)
	pmc_disable_periph_clock(AT91C_ID_GMAC);
#endif
#if defined(CONFIG_MAC1_PHY)
	pmc_disable_periph_clock(AT91C_ID_EMAC);
#endif
}
#endif

#ifdef CONFIG_TWI
#if defined(CONFIG_TWI0) || defined(CONFIG_TWI1) || defined(CONFIG_TWI2)
static unsigned int at91_twi_hw_init(unsigned int index)
{
	const unsigned int id[] = {AT91C_ID_TWI0, AT91C_ID_TWI1, AT91C_ID_TWI2};
	const unsigned int base_addr[] = {AT91C_BASE_TWI0, AT91C_BASE_TWI1, AT91C_BASE_TWI2};
	const struct pio_desc twi_pins[][3] = {
		{
			{"TWD0", AT91C_PIN_PA(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
			{"TWCK0", AT91C_PIN_PA(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
			{"TWD1", AT91C_PIN_PC(26), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"TWCK1", AT91C_PIN_PC(27), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
			{"TWD2", AT91C_PIN_PA(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"TWCK2", AT91C_PIN_PA(19), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
	};

	pio_configure(twi_pins[index]);

	pmc_enable_periph_clock(id[index], PMC_PERIPH_CLK_DIVIDER_NA);

	return base_addr[index];
}
#endif

void twi_init()
{
#if defined(CONFIG_TWI0)
	twi_bus_init(at91_twi_hw_init, 0);
#endif
#if defined(CONFIG_TWI1)
	twi_bus_init(at91_twi_hw_init, 1);
#endif
#if defined(CONFIG_TWI2)
	twi_bus_init(at91_twi_hw_init, 2);
#endif
}
#endif

#if defined(CONFIG_PM)
void at91_disable_smd_clock(void)
{
	/*
	 * set pin DIBP to pull-up and DIBN to pull-down
	 * to save power on VDDIOP0
	 */
	pmc_enable_system_clock(AT91C_PMC_SMDCK);
	pmc_set_smd_clock_divider(AT91C_PMC_SMDDIV);
	pmc_enable_periph_clock(AT91C_ID_SMD, PMC_PERIPH_CLK_DIVIDER_NA);
	writel(0xF, (0x0C + AT91C_BASE_SMD));
	pmc_disable_periph_clock(AT91C_ID_SMD);
	pmc_disable_system_clock(AT91C_PMC_SMDCK);
}
#endif

void hw_init(void)
{
	/* Disable watchdog */
	at91_disable_wdt();

#ifdef CONFIG_LED_ON_BOARD
	at91_leds_init();
#endif

	/*
	 * At this stage the main oscillator
	 * is supposed to be enabled PCK = MCK = MOSC
	 */

	/* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
	pmc_cfg_plla(PLLA_SETTINGS);

	/* Initialize PLLA charge pump */
	pmc_init_pll(AT91C_PMC_IPLLA_3);

	/* Switch PCK/MCK on Main clock output */
	pmc_mck_cfg_set(0, BOARD_PRESCALER_MAIN_CLOCK,
			AT91C_PMC_MDIV | AT91C_PMC_CSS);

	/* Switch PCK/MCK on PLLA output */
	pmc_mck_cfg_set(0, BOARD_PRESCALER_PLLA,
			AT91C_PMC_MDIV | AT91C_PMC_CSS);

	/* Set GMAC & EMAC pins to output low */
	at91_special_pio_output_low();

	/* Init timer */
	timer_init();

	/* initialize the dbgu */
	initialize_dbgu();

	ddram_init();

#ifdef CONFIG_LOAD_ONE_WIRE
	/* load one wire information */
	one_wire_hw_init();
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA5D3
	HDMI_Qt1070_workaround();
#endif

#if defined(CONFIG_NANDFLASH_RECOVERY) || defined(CONFIG_DATAFLASH_RECOVERY)
	/* Init the recovery buttons pins */
	recovery_buttons_hw_init();
#endif

#if defined(CONFIG_TWI)
	twi_init();
#endif
}

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
	pmc_enable_periph_clock(AT91C_ID_PIOD, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(spi0_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SPI0, PMC_PERIPH_CLK_DIVIDER_NA);
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
#ifdef CONFIG_OF_LIBFDT
void at91_board_set_dtb_name(char *of_name)
{
#ifdef CONFIG_LOAD_HW_INFO
	/* CPU TYPE*/
	switch (get_cm_sn()) {
	case BOARD_ID_SAMA5D31_CM:
		strcpy(of_name, "sama5d31ek");
		break;

	case BOARD_ID_SAMA5D33_CM:
		strcpy(of_name, "sama5d33ek");
		break;

	case BOARD_ID_SAMA5D34_CM:
		strcpy(of_name, "sama5d34ek");
		break;

	case BOARD_ID_SAMA5D35_CM:
		strcpy(of_name, "sama5d35ek");
		break;

	case BOARD_ID_SAMA5D36_CM:
		strcpy(of_name, "sama5d36ek");
		break;

	default:
		dbg_info("WARNING: Not correct CPU board ID\n");
		break;
	}

	if (get_dm_sn() == BOARD_ID_PDA_DM)
		strcat(of_name, "_pda4");
	else if (get_dm_sn() == BOARD_ID_PDA7_DM)
		strcat(of_name, "_pda7");

	strcat(of_name, ".dtb");
#else
	strcpy(of_name, CONFIG_DEVICENAME ".dtb");
#endif
}
#endif
#if defined(CONFIG_AT91_MCI0)
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
	pmc_enable_periph_clock(AT91C_ID_PIOD, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(mci_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_HSMCI0, PMC_PERIPH_CLK_DIVIDER_NA);
}
#elif defined(CONFIG_AT91_MCI1)
void at91_mci1_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PB(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PB(19), 0, PIO_DEFAULT, PIO_PERIPH_A},

		{"MCDA0", AT91C_PIN_PB(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PB(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PB(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PB(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	pmc_enable_periph_clock(AT91C_ID_PIOB, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(mci_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_HSMCI1, PMC_PERIPH_CLK_DIVIDER_NA);
}
#elif defined(CONFIG_AT91_MCI2)
void at91_mci2_hw_init(void)
{
	const struct pio_desc mci_pins[] = {
		{"MCCK", AT91C_PIN_PC(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCCDA", AT91C_PIN_PC(10), 0, PIO_DEFAULT, PIO_PERIPH_A},

		{"MCDA0", AT91C_PIN_PC(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA1", AT91C_PIN_PC(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA2", AT91C_PIN_PC(13), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"MCDA3", AT91C_PIN_PC(14), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Configure the PIO controller */
	pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(mci_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_HSMCI2, PMC_PERIPH_CLK_DIVIDER_NA);
}
#endif
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_FLASH
void norflash_hw_init(void)
{
	const struct pio_desc flash_pins[] = {
		{"FLASH_A1",  AT91C_PIN_PE(1),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A2",  AT91C_PIN_PE(2),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A3",  AT91C_PIN_PE(3),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A4",  AT91C_PIN_PE(4),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A5",  AT91C_PIN_PE(5),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A6",  AT91C_PIN_PE(6),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A7",  AT91C_PIN_PE(7),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A8",  AT91C_PIN_PE(8),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A9",  AT91C_PIN_PE(9),  0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A10", AT91C_PIN_PE(10), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A11", AT91C_PIN_PE(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A12", AT91C_PIN_PE(12), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A13", AT91C_PIN_PE(13), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A14", AT91C_PIN_PE(14), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A15", AT91C_PIN_PE(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A16", AT91C_PIN_PE(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A17", AT91C_PIN_PE(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A18", AT91C_PIN_PE(18), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A19", AT91C_PIN_PE(19), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A20", AT91C_PIN_PE(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A21", AT91C_PIN_PE(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A22", AT91C_PIN_PE(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_A23", AT91C_PIN_PE(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"FLASH_CS0", AT91C_PIN_PE(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SMC, PMC_PERIPH_CLK_DIVIDER_NA);

	/* Configure SMC CS0 for NOR flash */
	writel(AT91C_SMC_SETUP_NWE(1)
		| AT91C_SMC_SETUP_NCS_WR(0)
		| AT91C_SMC_SETUP_NRD(2)
		| AT91C_SMC_SETUP_NCS_RD(0),
		(ATMEL_BASE_SMC + SMC_SETUP0));

	writel(AT91C_SMC_PULSE_NWE(10)
		| AT91C_SMC_PULSE_NCS_WR(11)
		| AT91C_SMC_PULSE_NRD(10)
		| AT91C_SMC_PULSE_NCS_RD(11),
		(ATMEL_BASE_SMC + SMC_PULSE0));

	writel(AT91C_SMC_CYCLE_NWE(11)
		| AT91C_SMC_CYCLE_NRD(14),
		(ATMEL_BASE_SMC + SMC_CYCLE0));

	writel(AT91C_SMC_TIMINGS_TCLR(0)
		| AT91C_SMC_TIMINGS_TADL(0)
		| AT91C_SMC_TIMINGS_TAR(0)
		| AT91C_SMC_TIMINGS_TRR(0)
		| AT91C_SMC_TIMINGS_TWB(0)
		| AT91C_SMC_TIMINGS_RBNSEL(0)
		| AT91C_SMC_TIMINGS_NFSEL,
		(ATMEL_BASE_SMC + SMC_TIMINGS0));

	writel(AT91C_SMC_MODE_READMODE_NRD_CTRL
		| AT91C_SMC_MODE_WRITEMODE_NWE_CTRL
		| AT91C_SMC_MODE_EXNWMODE_DISABLED
		| AT91C_SMC_MODE_DBW_16
		| AT91C_SMC_MODE_TDF_CYCLES(1),
		(ATMEL_BASE_SMC + SMC_MODE0));

	/* Configure the PIO controller. */
	pio_configure(flash_pins);
}
#endif /* #ifdef CONFIG_FLASH */

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
	pmc_enable_periph_clock(AT91C_ID_PIOE, PMC_PERIPH_CLK_DIVIDER_NA);
	pio_configure(nand_pins);

	/* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SMC, PMC_PERIPH_CLK_DIVIDER_NA);

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

#ifdef CONFIG_MMU
void mmu_tlb_init(unsigned int *tlb)
{
	unsigned int addr;

	/* Reset table entries */
	for (addr = 0; addr < 4096; addr++)
		tlb[addr] = 0;

	/* 0x00000000: BOOT MEMORY */
	tlb[0x000] = TTB_SECT_ADDR(0x00000000)
	           | TTB_SECT_AP_READ_ONLY
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_TYPE_SECT;

	/* 0x00100000: ROM */
	tlb[0x001] = TTB_SECT_ADDR(0x00100000)
	           | TTB_SECT_AP_READ_ONLY
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_TYPE_SECT;

	/* 0x00200000: NFC SRAM */
	tlb[0x002] = TTB_SECT_ADDR(0x00200000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00300000: SRAM0 - SRAM1 */
	tlb[0x003] = TTB_SECT_ADDR(0x00300000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00800000: AXI Matrix */
	tlb[0x008] = TTB_SECT_ADDR(0x00800000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00900000: DAP */
	tlb[0x009] = TTB_SECT_ADDR(0x00900000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x10000000: EBI Chip Select 0 */
	for (addr = 0x100; addr < 0x200; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x20000000: DDR CS */
	for (addr = 0x200; addr < 0x400; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_CACHEABLE_WB
	                  | TTB_TYPE_SECT;

	/* 0x40000000: EBI Chip Select 1 */
	for (addr = 0x400; addr < 0x500; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x50000000: EBI Chip Select 2 */
	for (addr = 0x500; addr < 0x600; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x60000000: EBI Chip Select 3 */
	for (addr = 0x600; addr < 0x700; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x90000000: NFC Command Registers */
	for (addr = 0x700; addr < 0x800; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xf0000000: Internal Peripherals */
	tlb[0xf00] = TTB_SECT_ADDR(0xf0000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;

	/* 0xf8000000: Internal Peripherals */
	tlb[0xf80] = TTB_SECT_ADDR(0xf8000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;

	/* 0xfff00000: Internal Peripherals */
	tlb[0xfff] = TTB_SECT_ADDR(0xfff00000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;
}
#endif /* #ifdef CONFIG_MMU */
