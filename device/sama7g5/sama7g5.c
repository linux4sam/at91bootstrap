// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "backup.h"
#include "common.h"
#include "flexcom.h"
#include "twi.h"
#include "usart.h"
#include "hardware.h"
#include "arch/at91_pio.h"
#include "string.h"
#include "tzc400-interface.h"
#include "debug.h"
#include "umctl2.h"
#include "gpio.h"
#include "pmc.h"
#include "arch/at91_pmc/pmc.h"
#include "arch/at91_sfrbu.h"
#include "publ.h"
#include "shdwc.h"
#include "umctl2.h"
#include "watchdog.h"
#include "timer.h"
#include "sdhc_cal.h"
#include "led.h"
#include "arch/tz_matrix.h"
#include "matrix.h"
#include "arch/at91_sfr.h"
#include "arch/sama5_smc.h"
#include "nand.h"

#include "board.h"

__attribute__((weak)) void at91_can_stdby_dis(void);

static void ca7_enable_smp()
{
	/* asm code to enable ACTLR.SMP . this is needed for SCU for L2 cache */
	asm  volatile (
		"MRC p15, 0, R1, c1, c0, 1;"
		"ORR R1, R1, #64;"
		"MCR p15, 0, R1, c1, c0, 1;"
	);
}

static void axi2ahb_config_outstanding()
{
	/*
	 * AXI2AHB bridge must be limited to 1 outstanding per ID.
	 * More outstanding can lead to corrupted data transfer.
	 * Source: sama7g5 Errata
	 *
	 */
	writel(0x3, AT91C_BASE_NICGPV + 0x2008 + (0x1000 * 6));
	writel(0x3, AT91C_BASE_NICGPV + 0x2008 + (0x1000 * 13));
};

#if CONFIG_CONSOLE_INDEX <= 3
	#define FLEXCOM_USART_INDEX 0
#elif CONFIG_CONSOLE_INDEX <= 7
	#define FLEXCOM_USART_INDEX 1
#elif CONFIG_CONSOLE_INDEX <= 12
	#define FLEXCOM_USART_INDEX 2
#elif CONFIG_CONSOLE_INDEX <= 17
	#define FLEXCOM_USART_INDEX 3
#elif CONFIG_CONSOLE_INDEX <= 22
	#define FLEXCOM_USART_INDEX 4
#elif CONFIG_CONSOLE_INDEX <= 27
	#define FLEXCOM_USART_INDEX 5
#elif CONFIG_CONSOLE_INDEX <= 32
	#define FLEXCOM_USART_INDEX 6
#elif CONFIG_CONSOLE_INDEX <= 37
	#define FLEXCOM_USART_INDEX 7
#elif CONFIG_CONSOLE_INDEX <= 42
	#define FLEXCOM_USART_INDEX 8
#elif CONFIG_CONSOLE_INDEX <= 47
	#define FLEXCOM_USART_INDEX 9
#elif CONFIG_CONSOLE_INDEX <= 52
	#define FLEXCOM_USART_INDEX 10
#elif CONFIG_CONSOLE_INDEX <= 57
	#define FLEXCOM_USART_INDEX 11
#else
#error "Invalid CONSOLE_INDEX was chosen"
#endif

static struct at91_flexcom flexcoms[] = {
	{AT91C_ID_FLEXCOM0, FLEXCOM_TWI, AT91C_BASE_FLEXCOM0},
	{AT91C_ID_FLEXCOM1, FLEXCOM_TWI, AT91C_BASE_FLEXCOM1},
	{AT91C_ID_FLEXCOM2, FLEXCOM_TWI, AT91C_BASE_FLEXCOM2},
	{AT91C_ID_FLEXCOM3, FLEXCOM_TWI, AT91C_BASE_FLEXCOM3},
	{AT91C_ID_FLEXCOM4, FLEXCOM_TWI, AT91C_BASE_FLEXCOM4},
	{AT91C_ID_FLEXCOM5, FLEXCOM_TWI, AT91C_BASE_FLEXCOM5},
	{AT91C_ID_FLEXCOM6, FLEXCOM_TWI, AT91C_BASE_FLEXCOM6},
	{AT91C_ID_FLEXCOM7, FLEXCOM_TWI, AT91C_BASE_FLEXCOM7},
	{AT91C_ID_FLEXCOM8, FLEXCOM_TWI, AT91C_BASE_FLEXCOM8},
	{AT91C_ID_FLEXCOM9, FLEXCOM_TWI, AT91C_BASE_FLEXCOM9},
	{AT91C_ID_FLEXCOM10, FLEXCOM_TWI, AT91C_BASE_FLEXCOM10},
	{AT91C_ID_FLEXCOM11, FLEXCOM_TWI, AT91C_BASE_FLEXCOM11},
};

const unsigned int usart_base =
#if CONFIG_CONSOLE_INDEX <= 3
	(AT91C_BASE_FLEXCOM0 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 7
	(AT91C_BASE_FLEXCOM1 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 12
	(AT91C_BASE_FLEXCOM2 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 17
	(AT91C_BASE_FLEXCOM3 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 22
	(AT91C_BASE_FLEXCOM4 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 27
	(AT91C_BASE_FLEXCOM5 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 32
	(AT91C_BASE_FLEXCOM6 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 37
	(AT91C_BASE_FLEXCOM7 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 42
	(AT91C_BASE_FLEXCOM8 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 47
	(AT91C_BASE_FLEXCOM9 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 52
	(AT91C_BASE_FLEXCOM10 + AT91C_OFFSET_FLEXCOM_USART);
#elif CONFIG_CONSOLE_INDEX <= 57
	(AT91C_BASE_FLEXCOM11 + AT91C_OFFSET_FLEXCOM_USART);
#else
#error "Invalid CONSOLE_INDEX was chosen"
#endif

static const unsigned int usart_periph_id =
#if CONFIG_CONSOLE_INDEX <= 3
	AT91C_ID_FLEXCOM0;
#elif CONFIG_CONSOLE_INDEX <= 7
	AT91C_ID_FLEXCOM1;
#elif CONFIG_CONSOLE_INDEX <= 12
	AT91C_ID_FLEXCOM2;
#elif CONFIG_CONSOLE_INDEX <= 17
	AT91C_ID_FLEXCOM3;
#elif CONFIG_CONSOLE_INDEX <= 22
	AT91C_ID_FLEXCOM4;
#elif CONFIG_CONSOLE_INDEX <= 27
	AT91C_ID_FLEXCOM5;
#elif CONFIG_CONSOLE_INDEX <= 32
	AT91C_ID_FLEXCOM6;
#elif CONFIG_CONSOLE_INDEX <= 37
	AT91C_ID_FLEXCOM7;
#elif CONFIG_CONSOLE_INDEX <= 42
	AT91C_ID_FLEXCOM8;
#elif CONFIG_CONSOLE_INDEX <= 47
	AT91C_ID_FLEXCOM9;
#elif CONFIG_CONSOLE_INDEX <= 52
	AT91C_ID_FLEXCOM10;
#elif CONFIG_CONSOLE_INDEX <= 57
	AT91C_ID_FLEXCOM11;
#else
#error "Invalid CONSOLE_INDEX was chosen"
#endif

static void at91_dbgu_hw_init(void)
{
	const struct pio_desc dbgu_pins[] = {
	#if CONFIG_CONSOLE_INDEX == 0
		/* FLEXCOM0 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PA(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 1
		/* FLEXCOM0 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 2
		/* FLEXCOM0 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(10), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(11), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 3
		/* FLEXCOM0 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PE(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PE(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 4
		/* FLEXCOM1 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PA(6), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 5
		/* FLEXCOM1 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(12), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PD(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 6
		/* FLEXCOM1 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(3), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 7
		/* FLEXCOM1 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(9), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(10), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 8
		/* FLEXCOM2 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(7), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PA(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 9
		/* FLEXCOM2 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 10
		/* FLEXCOM2 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(4), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 11
		/* FLEXCOM2 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(11), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(12), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 12
		/* FLEXCOM2 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(14), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(15), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 13
		/* FLEXCOM3 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PA(16), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 14
		/* FLEXCOM3 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 15
		/* FLEXCOM3 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(6), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(7), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 16
		/* FLEXCOM3 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(13), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(14), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 17
		/* FLEXCOM3 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(16), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 18
		/* FLEXCOM4 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(20), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PA(21), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 19
		/* FLEXCOM4 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PC(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 20
		/* FLEXCOM4 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(8), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(9), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 21
		/* FLEXCOM4 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(15), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(16), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 22
		/* FLEXCOM4 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 23
		/* FLEXCOM5 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PA(29), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 24
		/* FLEXCOM5 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(25), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PD(26), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 25
		/* FLEXCOM5 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(10), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(11), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 26
		/* FLEXCOM5 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(17), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(18), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 27
		/* FLEXCOM5 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 28
		/* FLEXCOM6 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(2), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 29
		/* FLEXCOM6 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(30), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PD(31), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 30
		/* FLEXCOM6 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(12), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(13), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 31
		/* FLEXCOM6 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(19), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(20), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 32
		/* FLEXCOM6 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(21), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(22), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 33
		/* FLEXCOM7 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(23), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(24), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 34
		/* FLEXCOM7 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(7), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PC(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 35
		/* FLEXCOM7 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(25), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(26), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 36
		/* FLEXCOM7 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(28), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PB(29), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 37
		/* FLEXCOM7 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(23), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(24), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 38
		/* FLEXCOM8 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(9), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 39
		/* FLEXCOM8 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(14), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PC(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 40
		/* FLEXCOM8 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(27), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 41
		/* FLEXCOM8 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 42
		/* FLEXCOM8 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 43
		/* FLEXCOM9 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(14), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 44
		/* FLEXCOM9 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PC(19), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 45
		/* FLEXCOM9 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(29), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PA(30), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 46
		/* FLEXCOM9 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(0), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(1), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 47
		/* FLEXCOM9 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 48
		/* FLEXCOM10 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(19), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 49
		/* FLEXCOM10 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(30), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PC(31), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 50
		/* FLEXCOM10 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PA(31), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PB(0), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 51
		/* FLEXCOM10 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(3), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 52
		/* FLEXCOM10 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(6), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(7), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 53
		/* FLEXCOM11 IOSET 1 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PB(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 54
		/* FLEXCOM11 IOSET 2 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
		{"FLX_IO1", AT91C_PIN_PD(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
	#elif CONFIG_CONSOLE_INDEX == 55
		/* FLEXCOM11 IOSET 3 USART pins */
		{"FLX_IO0", AT91C_PIN_PB(1), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PB(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 56
		/* FLEXCOM11 IOSET 4 USART pins */
		{"FLX_IO0", AT91C_PIN_PC(4), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PC(5), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#elif CONFIG_CONSOLE_INDEX == 57
		/* FLEXCOM11 IOSET 5 USART pins */
		{"FLX_IO0", AT91C_PIN_PD(8), 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", AT91C_PIN_PD(9), 0, PIO_DEFAULT, PIO_PERIPH_F},
	#else
	#error "Invalid CONSOLE_INDEX was chosen"
	#endif
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A}, 
	};

	pio_configure(dbgu_pins);
	pmc_enable_periph_clock(usart_periph_id, PMC_PERIPH_CLK_DIVIDER_NA);

	flexcoms[FLEXCOM_USART_INDEX].id = usart_periph_id;
	flexcoms[FLEXCOM_USART_INDEX].mode = FLEXCOM_USART;
	flexcoms[FLEXCOM_USART_INDEX].addr = usart_base - AT91C_OFFSET_FLEXCOM_USART;
	flexcom_init(FLEXCOM_USART_INDEX);
}

#if defined(CONFIG_MATRIX)
static void matrix_configure_slave(void)
{
	unsigned int ssr_setting, sasplit_setting, srtop_setting;

	/* 0: QSPI0 */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_128M) |
			MATRIX_SRTOP(1, MATRIX_SRTOP_VALUE_128M);
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_128M) |
			  MATRIX_SASPLIT(1, MATRIX_SASPLIT_VALUE_128M);
	ssr_setting = MATRIX_LANSECH_NS(0) | MATRIX_LANSECH_NS(1);

	matrix_configure_slave_security(AT91C_BASE_MATRIX, MATRIX_SLAVE_QSPI0,
					srtop_setting, sasplit_setting,
					ssr_setting);
	/* 1: QSPI1 */
	matrix_configure_slave_security(AT91C_BASE_MATRIX, MATRIX_SLAVE_QSPI1,
					srtop_setting, sasplit_setting,
					ssr_setting);
	/* SMC EBI CS3 */
	srtop_setting = MATRIX_SRTOP(3, MATRIX_SRTOP_VALUE_128M);
	sasplit_setting = MATRIX_SASPLIT(3, MATRIX_SASPLIT_VALUE_128M);
	ssr_setting = MATRIX_LANSECH_NS(3);
	matrix_configure_slave_security(AT91C_BASE_MATRIX, MATRIX_SLAVE_EBI,
					srtop_setting, sasplit_setting,
					ssr_setting);
	/* NFC RAM */
	srtop_setting = MATRIX_SRTOP(0, MATRIX_SRTOP_VALUE_16K);
	sasplit_setting = MATRIX_SASPLIT(0, MATRIX_SASPLIT_VALUE_16K);
	ssr_setting = MATRIX_LANSECH_NS(0);
	matrix_configure_slave_security(AT91C_BASE_MATRIX, MATRIX_SLAVE_NFCRAM,
					srtop_setting, sasplit_setting,
					ssr_setting);
}

static void matrix_init(void)
{
	matrix_write_protect_disable(AT91C_BASE_MATRIX);

	matrix_configure_slave();
}
#endif

static void initialize_serial(void)
{
	unsigned int baudrate = 115200;

	at91_dbgu_hw_init();
	usart_init(BAUDRATE(MASTER_CLOCK, baudrate));
}

static struct umctl2_config_state umctl2_config;

static void umctl2_config_state_init()
{
	/* enable 5 AXI ports */
	umctl2_config.axi_port_bitmap = MP_AXI_PORT_ENABLE(0) |
					MP_AXI_PORT_ENABLE(1) |
					MP_AXI_PORT_ENABLE(2) |
					MP_AXI_PORT_ENABLE(3) |
					MP_AXI_PORT_ENABLE(4);

	/* port 0 configuration : CPU port */
		/* region 0 is ArQOS 0x0 to 0x8; */
		/* region 1 is ArQOS 0x9 to 0xF; */
	umctl2_config.port_x_read_region0_last[0] = 0x3;
		/* region 2 doesn't exist (single queue port) */
	umctl2_config.port_x_read_region1_last[0] = 0xE;
		/* region 0 is AwQOS 0x0 to 0xF; */
	umctl2_config.port_x_write_region0_last[0] = 0x3;
	umctl2_config.port_x_write_region1_last[0] = 0xE;

	/* port 1 configuration : AHB port */
		/* region 0 is ArQOS 0x0 to 0x8; */
		/* region 1 is ArQOS 0x9 to 0xF; */
	umctl2_config.port_x_read_region0_last[1] = 0x3;
		/* region 2 doesn't exist (single queue port) */
	umctl2_config.port_x_read_region1_last[1] = 0xE;
		/* region 0 is AwQOS 0x0 to 0xF; */
	umctl2_config.port_x_write_region0_last[1] = 0x3;
	umctl2_config.port_x_write_region1_last[1] = 0xE;

	/* port 2 configuration : PSS port XDMAC0,1+... */
		/* region 0 is ArQOS 0x0 to 0x3; */
		/* region 1 is ArQOS 0x3 to 0x8; */
	umctl2_config.port_x_read_region0_last[2] = 0x3;
		/* region 2 is ArQOS 0x8 to 0xF */
	umctl2_config.port_x_read_region1_last[2] = 0x8;
		/* region 0 is AwQOS 0x0 to 0xF; */
	umctl2_config.port_x_write_region0_last[2] = 0x3;
	umctl2_config.port_x_write_region1_last[2] = 0xE;

	/* port 3 configuration : ISS port XISC */
		/* region 0 is ArQOS 0x0 to 0x8; */
		/* region 1 is ArQOS 0x9 to 0xF; */
	umctl2_config.port_x_read_region0_last[3] = 0x3;
		/* region 2 doesn't exist (single queue port) */
	umctl2_config.port_x_read_region1_last[3] = 0xE;
		/* region 0 is AwQOS 0x0 to 0xF; */
	umctl2_config.port_x_write_region0_last[3] = 0x3;
	umctl2_config.port_x_write_region1_last[3] = 0xE;

	umctl2_config.port_x_rdwr_ordered_en = 0x0;

	/* port 4 configuration : MSS port SD+GMAC+... */
		/* region 0 is ArQOS 0x0 to 0x8; */
		/* region 1 is ArQOS 0x9 to 0xF; */
	umctl2_config.port_x_read_region0_last[4] = 0x3;
		/* region 2 doesn't exist (single queue port) */
	umctl2_config.port_x_read_region1_last[4] = 0xE;
		/* region 0 is AwQOS 0x0 to 0xF; */
	umctl2_config.port_x_write_region0_last[4] = 0x3;
	umctl2_config.port_x_write_region1_last[4] = 0xE;

	/* configure 16 entries from 32 as low priority. other 16 will be high */
	/* MEMC_NO_OF_ENTRY is total number. synthesised as 32 */
	umctl2_config.lpr_num_entries = 16;

	/* configure time queues can be unserved until going critical; DFI clocks */
	umctl2_config.lpr_max_starve = 0x1FF;
	umctl2_config.hpr_max_starve = 0x1F;
	umctl2_config.w_max_starve = 0x7F;

	/* configure how long queues should run after going critical; number of transactions */
	umctl2_config.lpr_xact_run_length = 0xF;
	umctl2_config.hpr_xact_run_length = 0xF;
	umctl2_config.w_xact_run_length = 0xF;

	/* wait 3 cycles and then go to alternate store if it's non empty */
	/* for now go immediately to alternate store */
	umctl2_config.rdwr_idle_gap = 0;

	/* prefer the read transaction store. */
	umctl2_config.prefer_write = 0;

	/* enable pageclose mechanism */
	umctl2_config.pageclose = 0;
	umctl2_config.pageclose_timer = 0x27;

	/* disable auto-precharge for flushed command in collision case */
	umctl2_config.dis_collision_page_opt = 0;

	/* do not disable write combine */
	umctl2_config.dis_wc = 0;

	/* Use PUBL as PHY */
	umctl2_config.phy_init = &publ_init;
	umctl2_config.phy_idone = &publ_idone;
	umctl2_config.phy_start = &publ_start;
	umctl2_config.phy_train = &publ_train;
#ifdef CONFIG_BACKUP_MODE
	umctl2_config.phy_bypass_zq_calibration = &publ_bypass_zq_calibration;
	umctl2_config.phy_override_zq_calibration = &publ_override_zq_calibration;
	umctl2_config.phy_prepare_train_corrupted_data_restore = &publ_prepare_train_corrupted_data_restore;
	umctl2_config.phy_zq_recalibrate = &publ_zq_recalibrate;
	umctl2_config.phy_train_corrupted_data_restore = &publ_train_corrupted_data_restore;
#endif
}

#ifdef CONFIG_DATAFLASH
#if defined(CONFIG_QSPI)
void at91_qspi_hw_init(void)
{
#if CONFIG_QSPI_BUS == 1
	const struct pio_desc qspi_pins[] = {
		{"QSPI1_IO0", AT91C_PIN_PB(25), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI1_IO1", AT91C_PIN_PB(24), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI1_IO2", AT91C_PIN_PB(23), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI1_IO3", AT91C_PIN_PB(22), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI1_CS", AT91C_PIN_PB(26), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI1_SCK", AT91C_PIN_PB(27), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#else
	const struct pio_desc qspi_pins[] = {
		{"QSPI0_IO0", AT91C_PIN_PB(12), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO1", AT91C_PIN_PB(11), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO2", AT91C_PIN_PB(10), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO3", AT91C_PIN_PB(9), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO4", AT91C_PIN_PB(16), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO5", AT91C_PIN_PB(17), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO6", AT91C_PIN_PB(18), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_IO7", AT91C_PIN_PB(19), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_CS", AT91C_PIN_PB(13), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_SCK", AT91C_PIN_PB(14), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_SCKN", AT91C_PIN_PB(15), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_DQS", AT91C_PIN_PB(20), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{"QSPI0_INT", AT91C_PIN_PB(21), 0, PIO_DRVSTR_HI, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#endif
	pio_configure(qspi_pins);
}

#endif
#endif /* CONFIG_DATAFLASH */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
{
	const struct pio_desc nand_pins[] = {
		{"NANDOE", CONFIG_SYS_NAND_OE_PIN, 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"NANDWE", CONFIG_SYS_NAND_WE_PIN, 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"NANDALE", CONFIG_SYS_NAND_ALE_PIN, 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"NANDCLE", CONFIG_SYS_NAND_CLE_PIN, 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"NANDCS", CONFIG_SYS_NAND_ENABLE_PIN, 1, PIO_DEFAULT, PIO_OUTPUT},
		{"D0", AT91C_PIN_PD(9), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D1", AT91C_PIN_PD(10), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D2", AT91C_PIN_PD(11), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D3", AT91C_PIN_PC(21), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D4", AT91C_PIN_PC(22), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D5", AT91C_PIN_PC(23), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D6", AT91C_PIN_PC(24), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{"D7", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_D},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(nand_pins);
	pmc_enable_periph_clock(AT91C_ID_HSMC, PMC_PERIPH_CLK_DIVIDER_NA);

	nandflash_set_smc_timing(TIMING_MODE_0);
}

void nandflash_set_smc_timing(unsigned int timing_mode)
{
#ifdef CONFIG_NAND_TIMING_MODE
 	if (timing_mode == TIMING_MODE_3) {
		/* Configure SMC CS3 for NAND */
		writel(AT91C_SMC_SETUP_NWE(2), ATMEL_BASE_SMC + SMC_SETUP3);

		writel(AT91C_SMC_PULSE_NWE(3) | AT91C_SMC_PULSE_NCS_WR(7) |
		       AT91C_SMC_PULSE_NRD(4) | AT91C_SMC_PULSE_NCS_RD(6),
		       ATMEL_BASE_SMC + SMC_PULSE3);

		writel(AT91C_SMC_CYCLE_NWE(7) | AT91C_SMC_CYCLE_NRD(7),
		      (ATMEL_BASE_SMC + SMC_CYCLE3));

		writel(AT91C_SMC_TIMINGS_TCLR(2) |
		       AT91C_SMC_TIMINGS_TADL(15) |
		       AT91C_SMC_TIMINGS_TAR(2) |
		       AT91C_SMC_TIMINGS_TRR(4) |
		       AT91C_SMC_TIMINGS_TWB(8) | AT91C_SMC_TIMINGS_NFSEL,
		       ATMEL_BASE_SMC + SMC_TIMINGS3);

		writel(AT91C_SMC_MODE_READMODE_NRD_CTRL |
		       AT91C_SMC_MODE_WRITEMODE_NWE_CTRL |
		       AT91C_SMC_MODE_TDF_MODE |
		       AT91C_SMC_MODE_TDF_CYCLES(15),
		       ATMEL_BASE_SMC + SMC_MODE3);
	} else {   
		/* Configure SMC CS3 for NAND */
		writel(AT91C_SMC_SETUP_NWE(4), ATMEL_BASE_SMC + SMC_SETUP3);

		writel(AT91C_SMC_PULSE_NWE(10) | AT91C_SMC_PULSE_NCS_WR(20) |
		       AT91C_SMC_PULSE_NRD(10) | AT91C_SMC_PULSE_NCS_RD(20),
		       ATMEL_BASE_SMC + SMC_PULSE3);

		writel(AT91C_SMC_CYCLE_NWE(20) | AT91C_SMC_CYCLE_NRD(20),
		      (ATMEL_BASE_SMC + SMC_CYCLE3));

		writel(AT91C_SMC_TIMINGS_TCLR(4) |
		       AT91C_SMC_TIMINGS_TADL(15) |
		       AT91C_SMC_TIMINGS_TAR(5) |
		       AT91C_SMC_TIMINGS_TRR(8) |
		       AT91C_SMC_TIMINGS_TWB(8) |
		       AT91C_SMC_TIMINGS_NFSEL,
		       ATMEL_BASE_SMC + SMC_TIMINGS3);

		writel(AT91C_SMC_MODE_READMODE_NRD_CTRL |
		       AT91C_SMC_MODE_WRITEMODE_NWE_CTRL |
		       AT91C_SMC_MODE_TDF_MODE |
		       AT91C_SMC_MODE_TDF_CYCLES(15),
		       ATMEL_BASE_SMC + SMC_MODE3);
	}
#else
	/* Configure SMC CS3 for NAND */
	writel(AT91C_SMC_SETUP_NWE(4), ATMEL_BASE_SMC + SMC_SETUP3);

	writel(AT91C_SMC_PULSE_NWE(10) | AT91C_SMC_PULSE_NCS_WR(20) |
	       AT91C_SMC_PULSE_NRD(10) | AT91C_SMC_PULSE_NCS_RD(20),
	       ATMEL_BASE_SMC + SMC_PULSE3);

	writel(AT91C_SMC_CYCLE_NWE(20) | AT91C_SMC_CYCLE_NRD(20),
	      (ATMEL_BASE_SMC + SMC_CYCLE3));

	writel(AT91C_SMC_TIMINGS_TCLR(4) | AT91C_SMC_TIMINGS_TADL(15) |
	       AT91C_SMC_TIMINGS_TAR(5) | AT91C_SMC_TIMINGS_TRR(8) |
	       AT91C_SMC_TIMINGS_TWB(8) | AT91C_SMC_TIMINGS_NFSEL,
	       ATMEL_BASE_SMC + SMC_TIMINGS3);

	writel(AT91C_SMC_MODE_READMODE_NRD_CTRL |
	       AT91C_SMC_MODE_WRITEMODE_NWE_CTRL | AT91C_SMC_MODE_TDF_MODE |
	       AT91C_SMC_MODE_TDF_CYCLES(15), ATMEL_BASE_SMC + SMC_MODE3);
#endif /* #ifdef CONFIG_NAND_TIMING_MODE */
}
#endif /* CONFIG_NANDFLASH */

#if defined(CONFIG_SDCARD)
#if defined(CONFIG_OF_LIBFDT)
void at91_board_set_dtb_name(char *of_name)
{
	strcpy(of_name, CONFIG_DEVICENAME ".dtb");
}
#endif

#define ATMEL_SDHC_GCKDIV_VALUE		1

void at91_sdhc_hw_init(void)
{
	u32 reg;
#if defined(CONFIG_SDHC1)
	const struct pio_desc sdmmc_pins[] = {
		{"SDMMC1_CK",   AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC1_CMD",  AT91C_PIN_PB(29), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_DAT0", AT91C_PIN_PB(31), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_DAT1", AT91C_PIN_PC(0), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_DAT2", AT91C_PIN_PC(1), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_DAT3", AT91C_PIN_PC(2), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_VDDSEL", AT91C_PIN_PC(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC1_WP",   AT91C_PIN_PC(3), 1, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_CD",   AT91C_PIN_PC(4), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC1_RST",  AT91C_PIN_PB(28), 0, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
	const struct pio_desc sdmmc_pins_reset[] = {
		{"SDMMC1_RST",  AT91C_PIN_PB(28), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#endif
#if defined(CONFIG_SDHC0)
	const struct pio_desc sdmmc_pins[] = {
		{"SDMMC0_CK",   AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_CMD",  AT91C_PIN_PA(1), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_RST",  AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"SDMMC0_DAT0", AT91C_PIN_PA(3), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT1", AT91C_PIN_PA(4), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT2", AT91C_PIN_PA(5), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT3", AT91C_PIN_PA(6), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT4", AT91C_PIN_PA(7), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT5", AT91C_PIN_PA(8), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT6", AT91C_PIN_PA(9), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_DAT7", AT91C_PIN_PA(10), 0, PIO_PULLUP, PIO_PERIPH_A},
		{"SDMMC0_CD",  AT91C_PIN_PA(14), 0, PIO_PULLUP, PIO_PERIPH_A},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
#endif

	pio_configure(sdmmc_pins);
#if defined(CONFIG_SDHC1)
	mdelay(500);
	pio_configure(sdmmc_pins_reset);
#endif

	pmc_enable_periph_clock(CONFIG_SYS_ID_SDHC, PMC_PERIPH_CLK_DIVIDER_NA);
	pmc_enable_generic_clock(CONFIG_SYS_ID_SDHC,
				 GCK_CSS_SYSPLL_CLK,
				 ATMEL_SDHC_GCKDIV_VALUE);

	/* Launch calibration and wait till it's completed */
	reg = readl(CONFIG_SYS_BASE_SDHC + SDMMC_CALCR);
	reg |= SDMMC_CALCR_CLKDIV(7) | SDMMC_CALCR_ALWYSON;
	writel(reg, CONFIG_SYS_BASE_SDHC + SDMMC_CALCR);
	reg |= SDMMC_CALCR_EN;
	writel(reg, CONFIG_SYS_BASE_SDHC + SDMMC_CALCR);
	while (readl(CONFIG_SYS_BASE_SDHC + SDMMC_CALCR) & SDMMC_CALCR_EN)
		;
}
#endif

/**
 * The MSBs [bits 31:16] of the CAN Message RAM for CAN0, CAN1 and CAN2 controllers
 * are configured in First half of internal SRAM, and CAN3, CAN4, CAN5 controllers are
 * configured in Second half of internal SRAM.
 */
#define CAN_MESSAGE_RAM_SEL	0x38

void at91_init_can_message_ram(void)
{
	writel(CAN_MESSAGE_RAM_SEL,
	       (AT91C_BASE_SFR + SFR_CAN_SRAM));
}

#define EHCIOHCI_PHYCLK_UTMI0	1

void usb_utmi_clk_fix(void)
{
	writel(EHCIOHCI_PHYCLK_UTMI0,
	       (AT91C_BASE_SFR + SFR_EHCIOCHI));
}

#ifdef CONFIG_TWI

#if defined(CONFIG_FLEXCOM0) || defined(CONFIG_FLEXCOM1) || defined(CONFIG_FLEXCOM2) || \
	defined(CONFIG_FLEXCOM3) || defined(CONFIG_FLEXCOM4) || defined(CONFIG_FLEXCOM5) || \
	defined(CONFIG_FLEXCOM6) || defined(CONFIG_FLEXCOM7) || defined(CONFIG_FLEXCOM8) || \
	defined(CONFIG_FLEXCOM9) || defined(CONFIG_FLEXCOM10) || defined(CONFIG_FLEXCOM11)
static unsigned int at91_flexcom_twi_hw_init(unsigned int index)
{
	const struct pio_desc flx_pins[][3] = {
		{ // FLEXCOM0
#if CONFIG_FLEXCOM0_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PA(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM0_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM0_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PD(10), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(11), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM0_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PE(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PE(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif defined(CONFIG_FLEXCOM0)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM1
#if CONFIG_FLEXCOM1_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PA(6), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM1_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(12), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PD(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM1_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(3), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM1_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(9), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(10), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM1)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM2
#if CONFIG_FLEXCOM2_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(7), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PA(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM2_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM2_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(4), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM2_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(11), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(12), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM2_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(14), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(15), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM2)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM3
#if CONFIG_FLEXCOM3_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(15), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PA(16), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM3_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM3_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(6), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(7), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM3_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(13), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(14), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM3_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(16), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM3)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM4
#if CONFIG_FLEXCOM4_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(20), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PA(21), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM4_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM4_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(8), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(9), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM4_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(15), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(16), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM4_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM4)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM5
#if CONFIG_FLEXCOM5_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PA(29), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM5_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(25), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PD(26), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM5_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(10), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(11), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM5_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(17), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(18), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM5_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM5)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM6
#if CONFIG_FLEXCOM6_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(2), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM6_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(30), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PD(31), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM6_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(12), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(13), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM6_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(19), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(20), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM6_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PC(21), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(22), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM6)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM7
#if CONFIG_FLEXCOM7_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(23), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(24), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM7_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(7), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM7_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(25), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(26), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM7_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PB(28), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PB(29), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM7_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PC(23), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(24), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM7)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM8
#if CONFIG_FLEXCOM8_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(8), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(9), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM8_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(14), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM8_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(27), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM8_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM8_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM8)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM9
#if CONFIG_FLEXCOM9_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(13), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(14), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM9_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(19), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM9_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(29), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PA(30), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM9_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(0), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(1), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM9_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM9)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM10
#if CONFIG_FLEXCOM10_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(18), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(19), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM10_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PC(30), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PC(31), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM10_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PA(31), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PB(0), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM10_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(3), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM10_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(6), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(7), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM10)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
		{ // FLEXCOM11
#if CONFIG_FLEXCOM11_IOSET == 1
			{"FLX_IO0", AT91C_PIN_PB(3), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PB(4), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM11_IOSET == 2
			{"FLX_IO0", AT91C_PIN_PD(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
			{"FLX_IO1", AT91C_PIN_PD(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
#elif CONFIG_FLEXCOM11_IOSET == 3
			{"FLX_IO0", AT91C_PIN_PB(1), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PB(2), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM11_IOSET == 4
			{"FLX_IO0", AT91C_PIN_PC(4), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PC(5), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif CONFIG_FLEXCOM11_IOSET == 5
			{"FLX_IO0", AT91C_PIN_PD(8), 0, PIO_DEFAULT, PIO_PERIPH_F},
			{"FLX_IO1", AT91C_PIN_PD(9), 0, PIO_DEFAULT, PIO_PERIPH_F},
#elif defined(CONFIG_FLEXCOM11)
#error "Invalid FLEXCOM IOSET was chosen"
#endif
			{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
		},
	};

	if (usart_periph_id == flexcoms[index].id) {
		dbg_very_loud("\nFLEXCOM %d is used in UART mode, config to TWI mode ignored!\n\n", index);
		return 0;
	}

	pio_configure(flx_pins[index]);

	pmc_enable_periph_clock(flexcoms[index].id, PMC_PERIPH_CLK_DIVIDER_NA);

	flexcom_init(index);

	return flexcom_get_regmap(index);
}
#endif

void twi_init()
{
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
#if defined(CONFIG_FLEXCOM5)
	twi_bus_init(at91_flexcom_twi_hw_init, 5);
#endif
#if defined(CONFIG_FLEXCOM6)
	twi_bus_init(at91_flexcom_twi_hw_init, 6);
#endif
#if defined(CONFIG_FLEXCOM7)
	twi_bus_init(at91_flexcom_twi_hw_init, 7);
#endif
#if defined(CONFIG_FLEXCOM8)
	twi_bus_init(at91_flexcom_twi_hw_init, 8);
#endif
#if defined(CONFIG_FLEXCOM9)
	twi_bus_init(at91_flexcom_twi_hw_init, 9);
#endif
#if defined(CONFIG_FLEXCOM10)
	twi_bus_init(at91_flexcom_twi_hw_init, 10);
#endif
#if defined(CONFIG_FLEXCOM11)
	twi_bus_init(at91_flexcom_twi_hw_init, 11);
#endif
}
#endif /* CONFIG_TWI */

void hw_preinit(void)
{
	/*
	 * We don't call here backup_resume() as this is using BSS data which is
	 * not initialized at the moment hw_preinit() is called. The functionality
	 * will not be affected if executing this code all the time at both boot
	 * and BSR exit.
	 */
	shdwc_disable_lpm();

	/*
	 * Out of Romcode, MCK1 & MCK4 are already configured with SYSPLL
	 * at unwanted frequencies.
	 * We cannot reconfigure SYSPLL without first reconfiguring
	 * MCK1 & MCK4 to different clock source.
	 * After we complete configuration for SYSPLL,
	 * we can configure MCK1 & MCK4 accordingly
	 */
	pmc_mck_cfg_set(4, BOARD_PRESCALER_MCK4_CLEAN,
			AT91C_MCR_DIV | AT91C_MCR_CSS | AT91C_MCR_EN);

	pmc_mck_cfg_set(1, BOARD_PRESCALER_MCK1_CLEAN,
			AT91C_MCR_DIV | AT91C_MCR_CSS | AT91C_MCR_EN);

	/*
	 * We are done here cleaning up MCK1 & MCK4, so we can configure
	 * SYSPLL at cruise speed
	 */
}

void hw_init(void)
{
	struct pmc_pll_cfg plla_config;
	struct pmc_pll_cfg ddrpll_config;
	struct pmc_pll_cfg syspll_config;
	struct pmc_pll_cfg imgpll_config;
	unsigned int mck0_prescaler;

	/* Switch backup area to VDDIN33. */
#ifdef CONFIG_BACKUP_VDDIN33
	sfrbu_select_ba_power_source(true);
#else
	sfrbu_auto_ba_power_source();
#endif

	/* Watchdog might be enabled out of reset. Let's make sure it's off */
	at91_disable_wdt();
#ifdef CONFIG_WDTS
	at91_disable_wdts();
#endif
	/* SMP is needed for L2 cache in cortex A7 */
	ca7_enable_smp();

	axi2ahb_config_outstanding();
#if defined(CONFIG_MATRIX)
	matrix_configure_default_qos();
#endif

	/* Configure & Enable CPU PLL at a safe speed of 600 Mhz*/
	plla_config.mul = 24; /* 25 * 24 = 600 */
	plla_config.div = 0;
	plla_config.count = 0x3f;
	plla_config.fracr = 0;
	plla_config.acr = 0x00070010;

	mck0_prescaler = BOARD_PRESCALER_CPUPLL | AT91C_PMC_MDIV_3;

	pmc_sam9x60_cfg_pll(PLL_ID_CPUPLL, &plla_config);

	pmc_mck_cfg_set(0, mck0_prescaler,
			AT91C_PMC_PRES | AT91C_PMC_MDIV | AT91C_PMC_CSS);

	/* Configure & Enable SYS PLL */
	syspll_config.mul = 49; /* (49 + 1) * 24 = 1200 */
	syspll_config.div = 2; /* Feed to PMC 1200/3 = 400 Mhz */
	syspll_config.count = 0x3f;
	syspll_config.fracr = 0;
	syspll_config.acr = 0x00070010;
	/* SYSPLL @ 1200 MHz */
	pmc_sam9x60_cfg_pll(PLL_ID_SYSPLL, &syspll_config);

	/* MCK4 @ 400 Mhz (== SYSPLL) */
	pmc_mck_cfg_set(4, BOARD_PRESCALER_MCK4,
			AT91C_MCR_DIV | AT91C_MCR_CSS | AT91C_MCR_EN);

	/* MCK1 @ 200 Mhz (== SYSPLL/2) */
	pmc_mck_cfg_set(1, BOARD_PRESCALER_MCK1,
			AT91C_MCR_DIV | AT91C_MCR_CSS | AT91C_MCR_EN);

	flexcoms_init(flexcoms);
#ifdef CONFIG_LED_ON_BOARD
	at91_leds_init();
#endif

#if defined(CONFIG_MATRIX)
	matrix_init();
#endif

	initialize_serial();

	/* We need timers in the following steps */
	timer_init();

#ifdef CONFIG_TWI
	twi_init();
#endif
#if defined(CONFIG_MATRIX)
	matrix_read_slave_security(AT91C_BASE_MATRIX, MATRIX_SLAVE_MAX);
#endif

	dbg_very_loud("CA7 early uart\n");

	/* Configure & Enable DDR PLL */
#if CONFIG_MEM_CLOCK == 533
	ddrpll_config.mul = 43; /* (43 + 1) * 24 = 1056 */
	ddrpll_config.div = 1;
	ddrpll_config.divio = 100;
	ddrpll_config.count = 0x3f;
	ddrpll_config.fracr = 0x1aaaab; /* (10/24) * 2^22 to get extra 10 MHz */
	ddrpll_config.acr = 0x00070010;
	/* DDRPLL @ 1066 MHz */
#endif
#if CONFIG_MEM_CLOCK == 400
	ddrpll_config.mul = 49; /* (49 + 1) * 24 =  1200 MHz */
	ddrpll_config.div = 2;  /* 1200 / 3 = 400 MHz */
	ddrpll_config.divio = 100;
	ddrpll_config.count = 0x3f;
	ddrpll_config.fracr = 0;
	ddrpll_config.acr = 0x00070010;
	/* DDRPLL @ 1200 MHz */
#endif
	pmc_sam9x60_cfg_pll(PLL_ID_DDRPLL, &ddrpll_config);

	/* MCK2 @ DDRPLL/2 MHz */
	pmc_mck_cfg_set(2, BOARD_PRESCALER_MCK2,
			AT91C_MCR_DIV | AT91C_MCR_CSS | AT91C_MCR_EN);

	/* Configure & Enable IMG PLL */
	imgpll_config.mul = 43; /* (43 + 1) * 24 = 1056 */
	imgpll_config.div = 3;
	imgpll_config.divio = 3;
	imgpll_config.count = 0x3f;
	imgpll_config.fracr = 0x155555; /* (8/24) * 2^22 to get extra 8 MHz */
	imgpll_config.acr = 0x00070010;
	/* IMGPLL @ 1064 MHz */
	pmc_sam9x60_cfg_pll(PLL_ID_IMGPLL, &imgpll_config);

	/* MCK3 @ 266 MHz */
	pmc_mck_cfg_set(3, BOARD_PRESCALER_MCK3,
			AT91C_MCR_DIV | AT91C_MCR_CSS | AT91C_MCR_EN);

	if (!backup_resume())
		dbg_printf("MCK: mck domains initialization complete.\n");

	tzc400_init();

	/* All MCK MUST be started before UMCTL2. Otherwise UMCTL2 will
	 * have the AXI ports blocked.
	 */
	umctl2_config_state_init();
	if (umctl2_init(&umctl2_config)) {
		console_printf("UMCTL2: Error initializing.\n");
	} else if (!backup_resume()) {
		console_printf("UMCTL2: Initialization complete.\n");
	}

	at91_init_can_message_ram();

#ifdef CONFIG_BOARD_QUIRK_SAMA7G5_EK
	at91_can_stdby_dis();
#endif

	usb_utmi_clk_fix();
}

void hw_postinit(void)
{
	struct pmc_pll_cfg plla_config;
	unsigned int mck0_prescaler;

	/*  In order to run at 1000MHz CPU clock the board's PMIC
	 *  must be able to raise the VDDCPU voltage to 1250mV
	 *  as it is recommended in the datasheet.
	 */

#ifdef CONFIG_CPU_CLK_800MHZ
	plla_config.mul = 32; /* 33 * 24 = 792 */
	plla_config.div = 0;
	plla_config.count = 0x3f;
	plla_config.fracr = 0x155555; /* 2^22 / 3 */
	plla_config.acr = 0x00070010;

	mck0_prescaler = BOARD_PRESCALER_CPUPLL | AT91C_PMC_MDIV_4;
#endif
#ifdef CONFIG_CPU_CLK_1000MHZ
	plla_config.mul = 40; /* 41 * 24 = 984 */
	plla_config.div = 0;
	plla_config.count = 0x3f;
	plla_config.fracr = 0x2AAAAB; /* 2^22  * 2 / 3 */
	plla_config.acr = 0x00070010;

	mck0_prescaler = BOARD_PRESCALER_CPUPLL | AT91C_PMC_MDIV_5;
#endif

#ifndef CONFIG_CPU_CLK_600MHZ
	pmc_sam9x60_cfg_pll(PLL_ID_CPUPLL, &plla_config);

	pmc_mck_cfg_set(0, mck0_prescaler,
			AT91C_PMC_PRES | AT91C_PMC_MDIV | AT91C_PMC_CSS);
#endif
}
