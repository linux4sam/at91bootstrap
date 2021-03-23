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

#if defined(CONFIG_LED_R_ON_PIOA)
	#define LED_R_PIO AT91C_PIN_PA(CONFIG_LED_R_PIN)
#elif defined(CONFIG_LED_R_ON_PIOB)
	#define LED_R_PIO AT91C_PIN_PB(CONFIG_LED_R_PIN)
#elif defined(CONFIG_LED_R_ON_PIOC)
	#define LED_R_PIO AT91C_PIN_PC(CONFIG_LED_R_PIN)
#elif defined(CONFIG_LED_R_ON_PIOD)
	#define LED_R_PIO AT91C_PIN_PD(CONFIG_LED_R_PIN)
#elif defined(CONFIG_LED_R_ON_PIOE)
	#define LED_R_PIO AT91C_PIN_PE(CONFIG_LED_R_PIN)
#endif

#if defined(CONFIG_LED_G_ON_PIOA)
	#define LED_G_PIO AT91C_PIN_PA(CONFIG_LED_G_PIN)
#elif defined(CONFIG_LED_G_ON_PIOB)
	#define LED_G_PIO AT91C_PIN_PB(CONFIG_LED_G_PIN)
#elif defined(CONFIG_LED_G_ON_PIOC)
	#define LED_G_PIO AT91C_PIN_PC(CONFIG_LED_G_PIN)
#elif defined(CONFIG_LED_G_ON_PIOD)
	#define LED_G_PIO AT91C_PIN_PD(CONFIG_LED_G_PIN)
#elif defined(CONFIG_LED_G_ON_PIOE)
	#define LED_G_PIO AT91C_PIN_PE(CONFIG_LED_G_PIN)
#endif

#if defined(CONFIG_LED_B_ON_PIOA)
	#define LED_B_PIO AT91C_PIN_PA(CONFIG_LED_B_PIN)
#elif defined(CONFIG_LED_B_ON_PIOB)
	#define LED_B_PIO AT91C_PIN_PB(CONFIG_LED_B_PIN)
#elif defined(CONFIG_LED_B_ON_PIOC)
	#define LED_B_PIO AT91C_PIN_PC(CONFIG_LED_B_PIN)
#elif defined(CONFIG_LED_B_ON_PIOD)
	#define LED_B_PIO AT91C_PIN_PD(CONFIG_LED_B_PIN)
#elif defined(CONFIG_LED_B_ON_PIOE)
	#define LED_B_PIO AT91C_PIN_PE(CONFIG_LED_B_PIN)
#endif

void at91_leds_init(void)
{
#ifndef LED_R_NONE
	pio_set_gpio_output(LED_R_PIO, CONFIG_LED_R_VALUE);
#endif
#ifndef LED_G_NONE
	pio_set_gpio_output(LED_G_PIO, CONFIG_LED_G_VALUE);
#endif
#ifndef LED_B_NONE
	pio_set_gpio_output(LED_B_PIO, CONFIG_LED_B_VALUE);
#endif
}
