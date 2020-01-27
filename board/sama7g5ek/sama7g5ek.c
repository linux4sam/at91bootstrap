/* ----------------------------------------------------------------------------
 *         Microchip Technology AT91Bootstrap project
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip Technology Inc. and its subsidiaries
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Microchip's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "flexcom.h"
#include "usart.h"
#include "hardware.h"
#include "arch/at91_pio.h"
#include "string.h"
#include "tzc400-interface.h"
#include "debug.h"
#include "umctl2.h"
#include "gpio.h"
#include "pmc.h"
#include "sama7g5ek.h"

static void ca7_enable_smp()
{
	/* asm code to enable ACTLR.SMP . this is needed for SCU for L2 cache */
	asm  volatile (
		"MRC p15, 0, R1, c1, c0, 1;"
		"ORR R1, R1, #64;"
		"MCR p15, 0, R1, c1, c0, 1;"
	);
}

static void initialize_serial(void)
{
	unsigned int baudrate = 115200;

	usart_init(BAUDRATE(200000000, baudrate));
}

#if defined CONFIG_FLEXCOM
static struct at91_flexcom flexcoms[] = {
	{AT91C_ID_FLEXCOM0, FLEXCOM_USART, AT91C_BASE_FLEXCOM0}, /* BT serial */
	{AT91C_ID_FLEXCOM1, FLEXCOM_SPI, AT91C_BASE_FLEXCOM1}, /* Mikrobus SPI */
	{AT91C_ID_FLEXCOM2, FLEXCOM_USART, AT91C_BASE_FLEXCOM2}, /* Unused */
	{AT91C_ID_FLEXCOM3, FLEXCOM_USART, AT91C_BASE_FLEXCOM3}, /* DBGU */
};

void board_flexcoms_init()
{
	flexcoms_init(flexcoms);
}
#endif

#if defined(CONFIG_FLEXCOM)
unsigned int at91_flexcom3_init(void)
{
	const struct pio_desc flx_pins[] = {
		{"FLX_IO0", CONFIG_SYS_DBGU_TXD_PIN, 0, PIO_DEFAULT, PIO_PERIPH_F},
		{"FLX_IO1", CONFIG_SYS_DBGU_RXD_PIN, 0, PIO_DEFAULT, PIO_PERIPH_F},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_F},
	};

	pio_configure(flx_pins);
	pmc_enable_periph_clock(AT91C_ID_FLEXCOM3, PMC_PERIPH_CLK_DIVIDER_NA);

	flexcom_init(3);

	return flexcom_get_regmap(3);
}
#endif

void hw_init(void)
{
	board_flexcoms_init();
	at91_flexcom3_init();

	initialize_serial();

	usart_puts("hardware init CA7\n");

	ca7_enable_smp();
}
