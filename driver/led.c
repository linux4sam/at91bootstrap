// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

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
#ifdef LED_R_PIO
	pio_set_gpio_output(LED_R_PIO, CONFIG_LED_R_VALUE);
#endif
#ifdef LED_G_PIO
	pio_set_gpio_output(LED_G_PIO, CONFIG_LED_G_VALUE);
#endif
#ifdef LED_B_PIO
	pio_set_gpio_output(LED_B_PIO, CONFIG_LED_B_VALUE);
#endif
}
