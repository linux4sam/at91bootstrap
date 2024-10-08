// Copyright (C) 2017, Microchip Corporation
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "sama5d2_board.h"
#include "ddramc.h"
#include "debug.h"
#include "gpio.h"
#include "hardware.h"
#include "l2cc.h"
#include "matrix.h"
#include "pmc.h"
#include "string.h"
#include "timer.h"
#include "usart.h"
#include "watchdog.h"
#include "sdhc_cal.h"
#include "arch/at91_ddrsdrc.h"
#include "arch/at91_pio.h"
#include "arch/at91_pmc/pmc.h"
#include "arch/at91_rstc.h"
#include "arch/at91_sfr.h"
#include "arch/at91_sfrbu.h"
#include "arch/sama5_smc.h"
#if defined(CONFIG_TWI)
#include "flexcom.h"
#include "twi.h"
#endif
#include "arch/tz_matrix.h"
#include "led.h"

#ifdef CONFIG_MMU
#include "mmu_cp15.h"
#endif

__attribute__((weak)) void sdmmc_cal_setup(void);
__attribute__((weak)) void at91_can_stdby_dis(void);
__attribute__((weak)) void peripherals_hw_reset(void);

#if defined(CONFIG_TWI)
static struct at91_flexcom flexcoms[] = {
	{AT91C_ID_FLEXCOM0, FLEXCOM_TWI, AT91C_BASE_FLEXCOM0, 0},
	{AT91C_ID_FLEXCOM1, FLEXCOM_TWI, AT91C_BASE_FLEXCOM1, 0},
	{AT91C_ID_FLEXCOM2, FLEXCOM_TWI, AT91C_BASE_FLEXCOM2, 0},
	{AT91C_ID_FLEXCOM3, FLEXCOM_TWI, AT91C_BASE_FLEXCOM3, 0},
	{AT91C_ID_FLEXCOM4, FLEXCOM_TWI, AT91C_BASE_FLEXCOM4, 0},
};
#endif

const unsigned int usart_base =
#if CONFIG_CONSOLE_INDEX == 0
	AT91C_BASE_UART0;
#elif CONFIG_CONSOLE_INDEX <= 2
	AT91C_BASE_UART1;
#elif CONFIG_CONSOLE_INDEX <= 5
	AT91C_BASE_UART2;
#elif CONFIG_CONSOLE_INDEX <= 8
	AT91C_BASE_UART3;
#elif CONFIG_CONSOLE_INDEX <= 9
	AT91C_BASE_UART4;
#else
#error "Invalid CONSOLE_INDEX was chosen"
#endif

static void at91_dbgu_hw_init(void)
{
	const struct pio_desc dbgu_pins[3] = {
#if CONFIG_CONSOLE_INDEX == 0
		/* UART0 IO Set 1 */
		{"RXD0", AT91C_PIN_PB(26), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"TXD0", AT91C_PIN_PB(27), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif CONFIG_CONSOLE_INDEX == 1
		/* UART1 IO Set 1 */
		{"RXD1", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD1", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
#elif CONFIG_CONSOLE_INDEX == 2
		/* UART1 IO Set 2 */
		{"RXD1", AT91C_PIN_PC(7), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"TXD1", AT91C_PIN_PC(8), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif CONFIG_CONSOLE_INDEX == 3
		/* UART2 IO Set 1 */
		{"RXD2", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"TXD2", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_CONSOLE_INDEX == 4
		/* UART2 IO Set 2 */
		{"RXD2", AT91C_PIN_PD(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD2", AT91C_PIN_PD(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
#elif CONFIG_CONSOLE_INDEX == 5
		/* UART2 IO Set 3 */
		{"RXD2", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"TXD2", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif CONFIG_CONSOLE_INDEX == 6
		/* UART3 IO Set 1 */
		{"RXD3", AT91C_PIN_PC(12), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"TXD3", AT91C_PIN_PC(13), 0, PIO_DEFAULT, PIO_PERIPH_D},
#elif CONFIG_CONSOLE_INDEX == 7
		/* UART3 IO Set 2 */
		{"RXD3", AT91C_PIN_PC(31), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"TXD3", AT91C_PIN_PD(0), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif CONFIG_CONSOLE_INDEX == 8
		/* UART3 IO Set 3 */
		{"RXD3", AT91C_PIN_PB(11), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"TXD3", AT91C_PIN_PB(12), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif CONFIG_CONSOLE_INDEX == 9
		/* UART4 IO Set 1 */
		{"RXD4", AT91C_PIN_PB(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"TXD4", AT91C_PIN_PB(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
#else
#error "Invalid CONSOLE_INDEX was chosen"
#endif
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
	const unsigned int periph_id[] = {
		AT91C_ID_UART0, AT91C_ID_UART1, AT91C_ID_UART1, AT91C_ID_UART2,
		AT91C_ID_UART2, AT91C_ID_UART2, AT91C_ID_UART3, AT91C_ID_UART3,
		AT91C_ID_UART3, AT91C_ID_UART4 };

	pio_configure(dbgu_pins);
	pmc_enable_periph_clock(periph_id[CONFIG_CONSOLE_INDEX], PMC_PERIPH_CLK_DIVIDER_NA);
}

static void initialize_dbgu(void)
{
	unsigned int baudrate = 115200;

	at91_dbgu_hw_init();

	if (pmc_mck_check_h32mxdiv())
		usart_init(BAUDRATE(MASTER_CLOCK / 2, baudrate));
	else
		usart_init(BAUDRATE(MASTER_CLOCK, baudrate));
}

#if defined(CONFIG_MATRIX)
static void matrix_configure_slave(void)
{
	unsigned int ddr_port;
	unsigned int ssr_setting, sasplit_setting, srtop_setting;

	/*
	 * Matrix 0 (H64MX)
	 */

	/*
	 * 0: Bridge from H64MX to AXIMX
	 * (Internal ROM, Crypto Library, PKCC RAM): Always Secured
	 */

	/* 1: H64MX Peripheral Bridge */

	/* 2 ~ 9 DDR2 Port0 ~ 7: Non-Secure */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_128M);
#ifdef CONFIG_DDR_4_GBIT
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
#elif defined(CONFIG_DDR_2_GBIT)
	sasplit_setting = (MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_128M)
				| MATRIX_SASPLIT(1, MATRIX_SASPLIT_VALUE_128M));
	ssr_setting = (MATRIX_LANSECH_NS(0)
			| MATRIX_LANSECH_NS(1)
			| MATRIX_RDNSECH_NS(0)
			| MATRIX_RDNSECH_NS(1)
			| MATRIX_WRNSECH_NS(0)
			| MATRIX_WRNSECH_NS(1));
#else
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_128M);
	ssr_setting = MATRIX_LANSECH_NS(0) |
		      MATRIX_RDNSECH_NS(0) |
		      MATRIX_WRNSECH_NS(0);
#endif
	for (ddr_port = 0; ddr_port < 8; ddr_port++) {
		matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					(H64MX_SLAVE_DDR2_PORT_0 + ddr_port),
					srtop_setting,
					sasplit_setting,
					ssr_setting);
	}

	/*
	 * 10: Internal SRAM 128K
	 * TOP0 is set to 128K
	 * SPLIT0 is set to 64K
	 * LANSECH0 is set to 0, the low area of region 0 is the Securable one
	 * RDNSECH0 is set to 0, region 0 Securable area is secured for reads.
	 * WRNSECH0 is set to 0, region 0 Securable area is secured for writes
	 */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_128K);
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_64K);
	ssr_setting = MATRIX_LANSECH_S(0) |
		      MATRIX_RDNSECH_S(0) |
		      MATRIX_WRNSECH_S(0);
	matrix_configure_slave_security(AT91C_BASE_MATRIX64,
					H64MX_SLAVE_INTERNAL_SRAM,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 11:  Internal SRAM 128K (Cache L2) */
	/* 12:  QSPI0 */
	/* 13:  QSPI1 */
	/* 14:  AESB */

	/*
	 * Matrix 1 (H32MX)
	 */

	/* 0: Bridge from H32MX to H64MX: Not Secured */

	/* 1: H32MX Peripheral Bridge 0: Not Secured */

	/* 2: H32MX Peripheral Bridge 1: Not Secured */

	/*
	 * 3: External Bus Interface
	 * EBI CS0 Memory(256M) ----> Slave Region 0, 1
	 * EBI CS1 Memory(256M) ----> Slave Region 2, 3
	 * EBI CS2 Memory(256M) ----> Slave Region 4, 5
	 * EBI CS3 Memory(128M) ----> Slave Region 6
	 * NFC Command Registers(128M) -->Slave Region 7
	 *
	 * NANDFlash(EBI CS3) --> Slave Region 6: Non-Secure
	 */
	srtop_setting =	MATRIX_SRTOP(6, MATRIX_SRTOP_VALUE_128M) |
			MATRIX_SRTOP(7, MATRIX_SRTOP_VALUE_128M);
	sasplit_setting = MATRIX_SASPLIT(6, MATRIX_SASPLIT_VALUE_128M) |
			  MATRIX_SASPLIT(7, MATRIX_SASPLIT_VALUE_128M);
	ssr_setting = MATRIX_LANSECH_NS(6) |
		      MATRIX_RDNSECH_NS(6) |
		      MATRIX_WRNSECH_NS(6) |
		      MATRIX_LANSECH_NS(7) |
		      MATRIX_RDNSECH_NS(7) |
		      MATRIX_WRNSECH_NS(7);
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_EXTERNAL_EBI,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 4: NFC SRAM (4K): Non-Secure */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_8K);
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_8K);
	ssr_setting = MATRIX_LANSECH_NS(0) |
		      MATRIX_RDNSECH_NS(0) |
		      MATRIX_WRNSECH_NS(0);
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_NFC_SRAM,
					srtop_setting,
					sasplit_setting,
					ssr_setting);

	/* 5:
	 * USB Device High Speed Dual Port RAM (DPR): 1M
	 * USB Host OHCI registers: 1M
	 * USB Host EHCI registers: 1M
	 */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_1M) |
			MATRIX_SRTOP(1, MATRIX_SRTOP_VALUE_1M) |
			MATRIX_SRTOP(2, MATRIX_SRTOP_VALUE_1M);
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_1M) |
			  MATRIX_SASPLIT(1, MATRIX_SASPLIT_VALUE_1M) |
			  MATRIX_SASPLIT(2, MATRIX_SASPLIT_VALUE_1M);
	ssr_setting = MATRIX_LANSECH_NS(0) |
		      MATRIX_LANSECH_NS(1) |
		      MATRIX_LANSECH_NS(2) |
		      MATRIX_RDNSECH_NS(0) |
		      MATRIX_RDNSECH_NS(1) |
		      MATRIX_RDNSECH_NS(2) |
		      MATRIX_WRNSECH_NS(0) |
		      MATRIX_WRNSECH_NS(1) |
		      MATRIX_WRNSECH_NS(2);
	matrix_configure_slave_security(AT91C_BASE_MATRIX32,
					H32MX_USB,
					srtop_setting,
					sasplit_setting,
					ssr_setting);
}

static int matrix_init(void)
{
	matrix_write_protect_disable(AT91C_BASE_MATRIX64);
	matrix_write_protect_disable(AT91C_BASE_MATRIX32);

	matrix_configure_slave();

	return 0;
}
#endif

/**
 * The MSBs [bits 31:16] of the CAN Message RAM for CAN0 and CAN1
 * are configured in 0x210000, instead of the default configuration
 * 0x200000, to avoid conflict with SRAM map for PM.
 */
#define CAN_MESSAGE_RAM_MSB	0x21

void at91_init_can_message_ram(void)
{
	writel(AT91C_CAN0_MEM_ADDR_(CAN_MESSAGE_RAM_MSB) |
	       AT91C_CAN1_MEM_ADDR_(CAN_MESSAGE_RAM_MSB),
	       (AT91C_BASE_SFR + SFR_CAN));
}

#if defined(CONFIG_TWI)
#if defined(CONFIG_TWI0) || defined(CONFIG_TWI1)
static unsigned int at91_twi_hw_init(unsigned int index)
{
	const unsigned int id[] = {AT91C_ID_TWI0, AT91C_ID_TWI1};
	const unsigned int base_addr[] = {AT91C_BASE_TWI0, AT91C_BASE_TWI1};
	const struct pio_desc twi_pins[][3] = {
		{
#if CONFIG_TWI0_IOSET == 1
			{"TWD0", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_D},
			{"TWCK0", AT91C_PIN_PC(0), 0, PIO_DEFAULT, PIO_PERIPH_D},
#elif CONFIG_TWI0_IOSET == 2
			{"TWD0", AT91C_PIN_PC(27), 0, PIO_DEFAULT, PIO_PERIPH_E},
			{"TWCK0", AT91C_PIN_PC(28), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif CONFIG_TWI0_IOSET == 3
			{"TWD0", AT91C_PIN_PD(29), 0, PIO_DEFAULT, PIO_PERIPH_E},
			{"TWCK0", AT91C_PIN_PD(30), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif CONFIG_TWI0_IOSET == 4
			{"TWD0", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"TWCK0", AT91C_PIN_PD(22), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif defined(CONFIG_TWI0)
#error "Invalid TWI IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
#if CONFIG_TWI1_IOSET == 1
			{"TWD1", AT91C_PIN_PC(6), 0, PIO_DEFAULT, PIO_PERIPH_C},
			{"TWCK1", AT91C_PIN_PC(7), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif CONFIG_TWI1_IOSET == 2
			{"TWD1", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
			{"TWCK1", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
#elif CONFIG_TWI1_IOSET == 3
			{"TWD1", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"TWCK1", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif defined(CONFIG_TWI1)
#error "Invalid TWI IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
	};

	if (index == 0) {
#if CONFIG_TWI0_IOSET == 1
		pmc_enable_periph_clock(AT91C_ID_PIOB, PMC_PERIPH_CLK_DIVIDER_NA);
		pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);
#elif CONFIG_TWI0_IOSET == 2
		pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);
#else
		pmc_enable_periph_clock(AT91C_ID_PIOD, PMC_PERIPH_CLK_DIVIDER_NA);
#endif
	} else {
#if CONFIG_TWI1_IOSET == 1
		pmc_enable_periph_clock(AT91C_ID_PIOC, PMC_PERIPH_CLK_DIVIDER_NA);
#else
		pmc_enable_periph_clock(AT91C_ID_PIOD, PMC_PERIPH_CLK_DIVIDER_NA);
#endif
	}
	pio_configure(twi_pins[index]);

	pmc_enable_periph_clock(id[index], PMC_PERIPH_CLK_DIVIDER_NA);

	return base_addr[index];
}
#endif

#if defined(CONFIG_FLEXCOM0) || defined(CONFIG_FLEXCOM1) || defined(CONFIG_FLEXCOM2) || defined(CONFIG_FLEXCOM3) || defined(CONFIG_FLEXCOM4)
static unsigned int at91_flexcom_twi_hw_init(unsigned int index)
{
	const struct pio_desc flx_pins[][3] = {
		{
#if CONFIG_FLEXCOM0_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(28), 0, PIO_DEFAULT, PIO_PERIPH_C},
			{"FLX_IO1", AT91C_PIN_PB(29), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif defined(CONFIG_FLEXCOM0)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
#if CONFIG_FLEXCOM1_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
			{"FLX_IO1", AT91C_PIN_PA(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
#elif defined(CONFIG_FLEXCOM1)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
#if CONFIG_FLEXCOM2_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(6), 0, PIO_DEFAULT, PIO_PERIPH_E},
			{"FLX_IO1", AT91C_PIN_PA(7), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif CONFIG_FLEXCOM2_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(26), 0, PIO_DEFAULT, PIO_PERIPH_C},
			{"FLX_IO1", AT91C_PIN_PD(27), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif defined(CONFIG_FLEXCOM2)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
#if CONFIG_FLEXCOM3_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_E},
			{"FLX_IO1", AT91C_PIN_PA(13), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif CONFIG_FLEXCOM3_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(20), 0, PIO_DEFAULT, PIO_PERIPH_E},
			{"FLX_IO1", AT91C_PIN_PC(19), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif CONFIG_FLEXCOM3_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PB(23), 0, PIO_DEFAULT, PIO_PERIPH_E},
			{"FLX_IO1", AT91C_PIN_PB(22), 0, PIO_DEFAULT, PIO_PERIPH_E},
#elif defined(CONFIG_FLEXCOM3)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{
#if CONFIG_FLEXCOM4_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PC(28), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(29), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM4_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PB(12), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM4_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_PERIPH_C},
			{"FLX_IO1", AT91C_PIN_PD(22), 0, PIO_DEFAULT, PIO_PERIPH_C},
#elif defined(CONFIG_FLEXCOM4)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		}
	};

	pio_configure(flx_pins[index]);

	pmc_enable_periph_clock(flexcoms[index].id, PMC_PERIPH_CLK_DIVIDER_NA);

	flexcom_init(index);

	return flexcom_get_regmap(index);
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
#if defined(CONFIG_FLEXCOM0)
	twi_bus_init(at91_flexcom_twi_hw_init, 0);
#endif
#if defined(CONFIG_FLEXCOM1)
	twi_bus_init(at91_flexcom_twi_hw_init, 1);
#endif
#if defined(CONFIG_FLEXCOM2)
	twi_bus_init(at91_flexcom_twi_hw_init, 2);
#endif
#if defined(CONFIG_FLEXCOM3)
	twi_bus_init(at91_flexcom_twi_hw_init, 3);
#endif
#if defined(CONFIG_FLEXCOM4)
	twi_bus_init(at91_flexcom_twi_hw_init, 4);
#endif
}
#endif

void hw_init(void)
{
#ifdef CONFIG_BACKUP_VDDIN33
	/* Switch backup area to VDDIN33. */
	sfrbu_select_ba_power_source(true);
#else
	sfrbu_auto_ba_power_source();
#endif

	at91_disable_wdt();

#ifdef CONFIG_LED_ON_BOARD
	at91_leds_init();
#endif

	pmc_cfg_plla(PLLA_SETTINGS);

	/* Initialize PLLA charge pump */
	/*
	 * The field named ICP_PLLA[1:0] must be written to 0.
	 * Even if its default value is 0, it is wrongly re-written to 0x3
	 * by the ROMCode.
	 */
	pmc_init_pll(AT91C_PMC_ICPPLLA_0);

	pmc_mck_cfg_set(0, BOARD_PRESCALER_PLLA,
			AT91C_PMC_H32MXDIV | AT91C_PMC_PLLADIV2 |
			AT91C_PMC_MDIV | AT91C_PMC_CSS);

	writel(AT91C_RSTC_KEY_UNLOCK | AT91C_RSTC_URSTEN,
	       AT91C_BASE_RSTC + RSTC_RMR);

#ifdef CONFIG_MATRIX
	matrix_init();
#endif
	initialize_dbgu();

	timer_init();

#if defined(CONFIG_TWI)
	flexcoms_init(flexcoms);
	twi_init();
#endif

	ddram_init();

	l2cache_prepare();

	at91_init_can_message_ram();

#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_SIP
	/* SiP: Implement the VDDSDMMC power supply over-consumption errata */
	sdmmc_cal_setup();
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_ICP
	at91_can_stdby_dis();

	/* Reset peripherals*/
	peripherals_hw_reset();
#endif
}

#if defined(CONFIG_SPI)
void at91_spi0_hw_init(void)
{
#if CONFIG_SPI_BUS == 0
#if CONFIG_SPI_IOSET == 1
	const struct pio_desc spi_pins[] = {
		{"SPI0_SPCK",	AT91C_PIN_PA(14), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_MOSI",	AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_MISO",	AT91C_PIN_PA(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI0_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_SPI_IOSET == 2
	const struct pio_desc spi_pins[] = {
		{"SPI0_SPCK",	AT91C_PIN_PB(1), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"SPI0_MOSI",	AT91C_PIN_PB(0), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"SPI0_MISO",	AT91C_PIN_PA(31), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"SPI0_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#else
#error "Invalid SPI IOSET was chosen"
#endif
#elif CONFIG_SPI_BUS == 1
#if CONFIG_SPI_IOSET == 1
	const struct pio_desc spi_pins[] = {
		{"SPI1_SPCK",	AT91C_PIN_PC(1), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"SPI1_MOSI",	AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"SPI1_MISO",	AT91C_PIN_PC(3), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"SPI1_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_SPI_IOSET == 2
	const struct pio_desc spi_pins[] = {
		{"SPI1_SPCK",	AT91C_PIN_PA(22), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"SPI1_MOSI",	AT91C_PIN_PA(23), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"SPI1_MISO",	AT91C_PIN_PA(24), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"SPI1_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_SPI_IOSET == 3
	const struct pio_desc spi_pins[] = {
		{"SPI1_SPCK",	AT91C_PIN_PD(25), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI1_MOSI",	AT91C_PIN_PD(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI1_MISO",	AT91C_PIN_PD(27), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SPI1_NPCS",	CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#else
#error "Invalid SPI IOSET was chosen"
#endif
#else
#error "Invalid SPI BUS was chosen"
#endif

	pio_configure(spi_pins);

	pmc_enable_periph_clock(CONFIG_SYS_ID_SPI, PMC_PERIPH_CLK_DIVIDER_NA);
}
#endif

#ifdef CONFIG_QSPI
void at91_qspi_hw_init(void)
{
#if CONFIG_QSPI_BUS == 0
#if CONFIG_QSPI_IOSET == 1
	const struct pio_desc qspi_pins[] = {
		{"QSPI0_SCK",	AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI0_CS",	AT91C_PIN_PA(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI0_IO0",	AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI0_IO1",	AT91C_PIN_PA(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI0_IO2",	AT91C_PIN_PA(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI0_IO3",	AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_QSPI_IOSET == 2
	const struct pio_desc qspi_pins[] = {
		{"QSPI0_SCK",	AT91C_PIN_PA(14), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"QSPI0_CS",	AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"QSPI0_IO0",	AT91C_PIN_PA(16), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"QSPI0_IO1",	AT91C_PIN_PA(17), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"QSPI0_IO2",	AT91C_PIN_PA(18), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{"QSPI0_IO3",	AT91C_PIN_PA(19), 0, PIO_DEFAULT, PIO_PERIPH_C},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_QSPI_IOSET == 3
	const struct pio_desc qspi_pins[] = {
		{"QSPI0_SCK",	AT91C_PIN_PA(22), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"QSPI0_CS",	AT91C_PIN_PA(23), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"QSPI0_IO0",	AT91C_PIN_PA(24), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"QSPI0_IO1",	AT91C_PIN_PA(25), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"QSPI0_IO2",	AT91C_PIN_PA(26), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"QSPI0_IO3",	AT91C_PIN_PA(27), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#else
#error "Invalid QSPI IOSET was chosen"
#endif

#elif CONFIG_QSPI_BUS == 1

#if CONFIG_QSPI_IOSET == 1
	const struct pio_desc qspi_pins[] = {
		{"QSPI1_SCK",	AT91C_PIN_PA(6),  0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI1_CS",	AT91C_PIN_PA(11), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI1_IO0",	AT91C_PIN_PA(7),  0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI1_IO1",	AT91C_PIN_PA(8),  0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI1_IO2",	AT91C_PIN_PA(9),  0, PIO_DEFAULT, PIO_PERIPH_B},
		{"QSPI1_IO3",	AT91C_PIN_PA(10), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_QSPI_IOSET == 2
	const struct pio_desc qspi_pins[] = {
		{"QSPI1_SCK",	AT91C_PIN_PB(5),  0, PIO_DEFAULT, PIO_PERIPH_D},
		{"QSPI1_CS",	AT91C_PIN_PB(6),  0, PIO_DEFAULT, PIO_PERIPH_D},
		{"QSPI1_IO0",	AT91C_PIN_PB(7),  0, PIO_DEFAULT, PIO_PERIPH_D},
		{"QSPI1_IO1",	AT91C_PIN_PB(8),  0, PIO_DEFAULT, PIO_PERIPH_D},
		{"QSPI1_IO2",	AT91C_PIN_PB(9),  0, PIO_DEFAULT, PIO_PERIPH_D},
		{"QSPI1_IO3",	AT91C_PIN_PB(10), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#elif CONFIG_QSPI_IOSET == 3
	const struct pio_desc qspi_pins[] = {
		{"QSPI1_SCK",	AT91C_PIN_PB(14), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"QSPI1_CS",	AT91C_PIN_PB(15), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"QSPI1_IO0",	AT91C_PIN_PB(16), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"QSPI1_IO1",	AT91C_PIN_PB(17), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"QSPI1_IO2",	AT91C_PIN_PB(18), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"QSPI1_IO3",	AT91C_PIN_PB(19), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#else
#error "Invalid QSPI IOSET was chosen"
#endif
#else
#error "Invalid QSPI BUS was chosen"
#endif

	pio_configure(qspi_pins);
	pmc_enable_periph_clock(CONFIG_SYS_ID_QSPI, PMC_PERIPH_CLK_DIVIDER_NA);
}
#endif

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	const struct pio_desc nand_pins[] = {
#if defined(CONFIG_NANDFLASH_IOSET1)
		{"NANDOE", CONFIG_SYS_NAND_OE_PIN, 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NANDWE", CONFIG_SYS_NAND_WE_PIN, 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NANDALE", CONFIG_SYS_NAND_ALE_PIN, 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NANDCLE", CONFIG_SYS_NAND_CLE_PIN, 0, PIO_PULLUP, PIO_PERIPH_B},
		{"NANDCS", CONFIG_SYS_NAND_ENABLE_PIN, 1, PIO_DEFAULT, PIO_OUTPUT},
		{"D0", AT91C_PIN_PA(22), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D1", AT91C_PIN_PA(23), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D2", AT91C_PIN_PA(24), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D3", AT91C_PIN_PA(25), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D4", AT91C_PIN_PA(26), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D5", AT91C_PIN_PA(27), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D6", AT91C_PIN_PA(28), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
		{"D7", AT91C_PIN_PA(29), 0, PIO_DRVSTR_ME, PIO_PERIPH_B},
#elif defined(CONFIG_NANDFLASH_IOSET2)
		{"NANDOE", CONFIG_SYS_NAND_OE_PIN, 0, PIO_PULLUP, PIO_PERIPH_F},
		{"NANDWE", CONFIG_SYS_NAND_WE_PIN, 0, PIO_PULLUP, PIO_PERIPH_F},
		{"NANDALE", CONFIG_SYS_NAND_ALE_PIN, 0, PIO_PULLUP, PIO_PERIPH_F},
		{"NANDCLE", CONFIG_SYS_NAND_CLE_PIN, 0, PIO_PULLUP, PIO_PERIPH_F},
		{"NANDCS", CONFIG_SYS_NAND_ENABLE_PIN, 1, PIO_DEFAULT, PIO_OUTPUT},
		{"D0", AT91C_PIN_PA(0), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D1", AT91C_PIN_PA(1), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D2", AT91C_PIN_PA(2), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D3", AT91C_PIN_PA(3), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D4", AT91C_PIN_PA(4), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D5", AT91C_PIN_PA(5), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D6", AT91C_PIN_PA(6), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
		{"D7", AT91C_PIN_PA(7), 0, PIO_DRVSTR_ME, PIO_PERIPH_F},
#else
#error "No NAND Flash IOSETs defined"
#endif
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(nand_pins);
	pmc_enable_periph_clock(AT91C_ID_HSMC, PMC_PERIPH_CLK_DIVIDER_NA);

	/* EBI Configuration Register */
	writel((AT91C_EBICFG_DRIVE0_HIGH |
		AT91C_EBICFG_PULL0_NONE |
		AT91C_EBICFG_DRIVE1_HIGH |
		AT91C_EBICFG_PULL1_NONE), SFR_EBICFG + AT91C_BASE_SFR);

	/* Configure SMC CS3 for NAND/SmartMedia */
	writel(AT91C_SMC_SETUP_NWE(1) |
	       AT91C_SMC_SETUP_NCS_WR(1) |
	       AT91C_SMC_SETUP_NRD(1) |
	       AT91C_SMC_SETUP_NCS_RD(1), (ATMEL_BASE_SMC + SMC_SETUP3));

	writel(AT91C_SMC_PULSE_NWE(2) |
	       AT91C_SMC_PULSE_NCS_WR(3) |
	       AT91C_SMC_PULSE_NRD(2) |
	       AT91C_SMC_PULSE_NCS_RD(3), (ATMEL_BASE_SMC + SMC_PULSE3));

	writel(AT91C_SMC_CYCLE_NWE(5) |
	       AT91C_SMC_CYCLE_NRD(5), (ATMEL_BASE_SMC + SMC_CYCLE3));

	writel(AT91C_SMC_TIMINGS_TCLR(2) |
	       AT91C_SMC_TIMINGS_TADL(7) |
	       AT91C_SMC_TIMINGS_TAR(2) |
	       AT91C_SMC_TIMINGS_TRR(3) |
	       AT91C_SMC_TIMINGS_TWB(7) |
	       AT91C_SMC_TIMINGS_RBNSEL(2) |
	       AT91C_SMC_TIMINGS_NFSEL, (ATMEL_BASE_SMC + SMC_TIMINGS3));

	writel(AT91C_SMC_MODE_READMODE_NRD_CTRL |
	       AT91C_SMC_MODE_WRITEMODE_NWE_CTRL |
	       AT91C_SMC_MODE_DBW_8 |
	       AT91C_SMC_MODE_TDF_CYCLES(1), (ATMEL_BASE_SMC + SMC_MODE3));
}
#endif /* CONFIG_NANDFLASH */

#ifdef CONFIG_SDCARD
#ifdef CONFIG_OF_LIBFDT
void at91_board_set_dtb_name(char *of_name)
{
	strcpy(of_name, CONFIG_DEVICENAME ".dtb");
}
#endif

#define ATMEL_SDHC_GCKDIV_VALUE		1

void at91_sdhc_hw_init(void)
{
#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_SIP
	unsigned int reg;
#endif

#ifdef CONFIG_SDHC0
	const struct pio_desc sdmmc_pins[] = {
		{"SDMMC0_CK",   AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_CMD",  AT91C_PIN_PA(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT0", AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT1", AT91C_PIN_PA(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT2", AT91C_PIN_PA(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT3", AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
#ifdef CONFIG_SDHC_8BIT_SUPPORT
		{"SDMMC0_DAT4", AT91C_PIN_PA(6), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT5", AT91C_PIN_PA(7), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT6", AT91C_PIN_PA(8), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT7", AT91C_PIN_PA(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
#endif
		{"SDMMC0_RSTN", AT91C_PIN_PA(10), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_VDDSEL", AT91C_PIN_PA(11), 0, PIO_DEFAULT, PIO_PERIPH_A},
#ifndef CONFIG_BOARD_QUIRK_SAMA5D2_XULT
		{"SDMMC0_WP",   AT91C_PIN_PA(12), 1, PIO_DEFAULT, PIO_PERIPH_A},
#endif
		{"SDMMC0_CD",   AT91C_PIN_PA(13), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#endif

#ifdef CONFIG_SDHC1
	const struct pio_desc sdmmc_pins[] = {
		{"SDMMC1_DAT0",	AT91C_PIN_PA(18), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"SDMMC1_DAT1",	AT91C_PIN_PA(19), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"SDMMC1_DAT2",	AT91C_PIN_PA(20), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"SDMMC1_DAT3",	AT91C_PIN_PA(21), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"SDMMC1_CK",	AT91C_PIN_PA(22), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"SDMMC1_CMD",	AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{"SDMMC1_CD",	AT91C_PIN_PA(30), 0, PIO_DEFAULT, PIO_PERIPH_E},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_SIP
	/* First, print status of CAL for VDDSDMMC over-consumption errata */
	pmc_enable_periph_clock(AT91C_ID_SDMMC0, PMC_PERIPH_CLK_DIVIDER_NA);
	reg = readl(AT91C_BASE_SDHC0 + SDMMC_CALCR);
	pmc_disable_periph_clock(AT91C_ID_SDMMC0);

	if (reg & SDMMC_CALCR_ALWYSON)
		dbg_info("SDHC: fix in place for SAMA5D2 SiP VDDSDMMC over-consumption errata\n");
#endif

	/* Deal with usual SD/MCC peripheral init sequence */
	pio_configure(sdmmc_pins);

	pmc_enable_periph_clock(CONFIG_SYS_ID_SDHC, PMC_PERIPH_CLK_DIVIDER_NA);
	pmc_enable_generic_clock(CONFIG_SYS_ID_SDHC,
				 GCK_CSS_UPLL_CLK,
				 ATMEL_SDHC_GCKDIV_VALUE);
}
#endif

#ifdef CONFIG_MMU
void mmu_tlb_init(unsigned int *tlb)
{
	unsigned int addr;

	/* Reset table entries */
	for (addr = 0; addr < 4096; addr++)
		tlb[addr] = 0;

	/* 0x00000000: ROM */
	tlb[0x000] = TTB_SECT_ADDR(0x00000000)
	           | TTB_SECT_AP_READ_ONLY
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_CACHEABLE_WB
	           | TTB_TYPE_SECT;

	/* 0x00100000: NFC SRAM */
	tlb[0x001] = TTB_SECT_ADDR(0x00100000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00200000: SRAM */
	tlb[0x002] = TTB_SECT_ADDR(0x00200000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00600000: AXIMX */
	tlb[0x006] = TTB_SECT_ADDR(0x00600000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC_NEVER
	           | TTB_SECT_SHAREABLE_DEVICE
	           | TTB_TYPE_SECT;

	/* 0x00700000: DAP */
	tlb[0x007] = TTB_SECT_ADDR(0x00700000)
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

	/* 0x20000000: DDR Chip Select */
	for (addr = 0x200; addr < 0x400; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_CACHEABLE_WB
	                  | TTB_TYPE_SECT;

	/* 0x40000000: DDR AESB Chip Select */
	for (addr = 0x400; addr < 0x600; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC
	                  | TTB_SECT_CACHEABLE_WB
	                  | TTB_TYPE_SECT;

	/* 0x60000000: EBI Chip Select 1 */
	for (addr = 0x600; addr < 0x700; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x70000000: EBI Chip Select 2 */
	for (addr = 0x700; addr < 0x800; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0x80000000: EBI Chip Select 3 */
	for (addr = 0x800; addr < 0x900; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xd0000000: QSPI0/1 MEM */
	for (addr = 0xd00; addr < 0xe00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_STRONGLY_ORDERED
	                  | TTB_TYPE_SECT;

	/* 0xc0000000: NFC Command Register */
	for (addr = 0xc00; addr < 0xd00; addr++)
		tlb[addr] = TTB_SECT_ADDR(addr << 20)
	                  | TTB_SECT_AP_FULL_ACCESS
	                  | TTB_SECT_DOMAIN(0xf)
	                  | TTB_SECT_EXEC_NEVER
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

	/* 0xfc000000: Internal Peripherals */
	tlb[0xfc0] = TTB_SECT_ADDR(0xfc000000)
	           | TTB_SECT_AP_FULL_ACCESS
	           | TTB_SECT_DOMAIN(0xf)
	           | TTB_SECT_EXEC
	           | TTB_SECT_STRONGLY_ORDERED
	           | TTB_TYPE_SECT;
}
#endif /* #ifdef CONFIG_MMU */
