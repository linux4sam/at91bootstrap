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

#include "arch/at91_pio.h"
#include "gpio.h"
#include "timer.h"

#ifdef CONFIG_BOARD_QUIRK_SAMA5D3
void HDMI_Qt1070_workaround(void)
{
	/* For the HDMI and QT1070 shar the irq line
	 * if the HDMI does not initialize, the irq line is pulled down by HDMI,
	 * so, the irq line can not used by QT1070
	 */
	pio_set_gpio_output(AT91C_PIN_PC(31), 1);
	udelay(33000);
	pio_set_gpio_output(AT91C_PIN_PC(31), 0);
	udelay(33000);
	pio_set_gpio_output(AT91C_PIN_PC(31), 1);
}
#endif

#if defined(CONFIG_HDMI)
#if defined(CONFIG_BOARD_QUIRK_SAMA5D4)
void SiI9022_hw_reset(void)
{
	pio_set_gpio_output(AT91C_PIN_PB(15), 1);
	pio_set_gpio_output(AT91C_PIN_PB(15), 0);
	udelay(500);
	pio_set_gpio_output(AT91C_PIN_PB(15), 1);
}
#endif
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_ICP
/*
 * Must set PB25 to LOW to enable the can transceivers.
 * This needs to be replaced later with Linux control over this GPIO
 */
void at91_can_stdby_dis(void)
{
	const struct pio_desc can_pins[] = {
		{"CAN_STDBY", AT91C_PIN_PB(25), 0, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_B},
	};

	pio_configure(can_pins);
}

void peripherals_hw_reset(void)
{
	const struct pio_desc reset_peripherals[] = {
		{"LAN9252_RST",	AT91C_PIN_PB(16),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 200us */
		{"HSIC_RST",	AT91C_PIN_PC(2),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 1us */
		{"USB2534_RST",	AT91C_PIN_PC(17),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 5us */
		{"KSZ8563_RST",	AT91C_PIN_PD(4),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 100us */
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc wake_peripherals[] = {
		{"LAN9252_RST",	AT91C_PIN_PB(16),	1, PIO_DEFAULT, PIO_OUTPUT},
		{"HSIC_RST",	AT91C_PIN_PC(2),	1, PIO_DEFAULT, PIO_OUTPUT},
		{"USB2534_RST",	AT91C_PIN_PC(17),	1, PIO_DEFAULT, PIO_OUTPUT},
		{"KSZ8563_RST",	AT91C_PIN_PD(4),	1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(reset_peripherals);
	udelay(250);
	pio_configure(wake_peripherals);
}
#endif

#ifdef CONFIG_BOARD_QUIRK_SAM9X60
void wilc_pwrseq()
{
	const struct pio_desc wilc_down_pins[] = {
		{"WILC_RESETN", AT91C_PIN_PB(25), 0, PIO_DEFAULT, PIO_OUTPUT},
		{"WILC_EN", AT91C_PIN_PA(29), 0, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc wilc_powerup_pins[] = {
		{"WILC_EN", AT91C_PIN_PA(29), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc wilc_en_pins[] = {
		{"WILC_RESETN", AT91C_PIN_PB(25), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(wilc_down_pins);
	udelay(5000);
	pio_configure(wilc_powerup_pins);
	udelay(5000);
	pio_configure(wilc_en_pins);
}
#endif
