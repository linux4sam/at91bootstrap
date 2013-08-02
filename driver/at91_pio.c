/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
#include "hardware.h"
#include "arch/at91_pio.h"
#include "gpio.h"
#include "debug.h"

static inline int pio_base_addr(unsigned int pio)
{
	if (pio > AT91C_NUM_PIO)
		return -1;

	if (pio == 0)
		return AT91C_BASE_PIOA;
	else if (pio == 1)
		return AT91C_BASE_PIOB;
	else if (pio == 2)
		return AT91C_BASE_PIOC;
	else if (pio == 3)
#ifdef AT91C_BASE_PIOD
		return AT91C_BASE_PIOD;
#else
		return -1;
#endif
	else if (pio == 4)
#ifdef AT91C_BASE_PIOE
		return AT91C_BASE_PIOE;
#else
		return -1;
#endif
	else
		return -1;
}

static inline void write_pio(unsigned int pio,
			unsigned int offset,
			const unsigned int value)
{
	int base = pio_base_addr(pio);

	if (base == -1)
		return;

	writel(value, offset + base);
}

static inline unsigned int read_pio(unsigned int pio, unsigned int offset)
{
	int base = pio_base_addr(pio);

	if (base == -1)
		return 0;

	return readl(offset + base);
}

static inline unsigned pin_to_controller(unsigned pin)
{
	return (pin) / PIO_NUM_IO;
}

static inline unsigned pin_to_mask(unsigned pin)
{
	return 1 << ((pin) % PIO_NUM_IO);
}

static int pio_set_a_periph(unsigned pin, int use_pullup)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, PIO_IDR, mask);
	write_pio(pio, use_pullup ? PIO_PPUER : PIO_PPUDR, mask);
#ifndef CONFIG_HAS_PIO3
	write_pio(pio, PIO_ASR, mask);
#else
	write_pio(pio, PIO_SP1, read_pio(pio, PIO_SP1) & ~mask);
	write_pio(pio, PIO_SP2, read_pio(pio, PIO_SP2) & ~mask);
#endif
	write_pio(pio, PIO_PDR, mask);

	return 0;
}

static int pio_set_b_periph(unsigned pin, int use_pullup)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, PIO_IDR, mask);
	write_pio(pio, (use_pullup ? PIO_PPUER : PIO_PPUDR), mask);
#ifndef CONFIG_HAS_PIO3
	write_pio(pio, PIO_BSR, mask);
#else
	write_pio(pio, PIO_SP1, read_pio(pio, PIO_SP1) | mask);
	write_pio(pio, PIO_SP2, read_pio(pio, PIO_SP2) & ~mask);
#endif
	write_pio(pio, PIO_PDR, mask);

	return 0;
}

int pio_set_gpio_input(unsigned pin, int use_pullup)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, PIO_IDR, mask);
	write_pio(pio, (use_pullup ? PIO_PPUER : PIO_PPUDR), mask);
	write_pio(pio, PIO_ODR, mask);
	write_pio(pio, PIO_PER, mask);

	return 0;
}

int pio_set_gpio_output(unsigned pin, int value)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, PIO_IDR, mask);
	write_pio(pio, PIO_PPUDR, mask);
	write_pio(pio, (value ? PIO_SODR : PIO_CODR), mask);
	write_pio(pio, PIO_OER, mask);
	write_pio(pio, PIO_PER, mask);

	return 0;
}

static int pio_set_deglitch(unsigned pin, int is_on)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, (is_on ? PIO_IFER : PIO_IFDR), mask);

	return 0;
}

static int pio_set_multi_drive(unsigned pin, int is_on)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, (is_on ? PIO_MDER : PIO_MDDR), mask);

	return 0;
}

int pio_set_value(unsigned pin, int value)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(pio, (value ? PIO_SODR : PIO_CODR), mask);

	return 0;
}

int pio_get_value(unsigned pin)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);
	unsigned int pdsr;

	if (pio >= AT91C_NUM_PIO)
		return -1;

	pdsr = read_pio(pio, PIO_PDSR);

	return ((pdsr & mask) != 0);
}

int pio_configure(const struct pio_desc *pio_desc)
{
	unsigned pio, pin = 0;

	if (pio_desc == 0) return 0;

	/*
	 * Sets all the pio muxing of the corresponding device as defined
	 * in its platform_data struct
	 */
	while (pio_desc->pin_name) {
		pio = pin_to_controller(pio_desc->pin_num);
		if (pio >= AT91C_NUM_PIO) {
			return 0;
		} else if (pio_desc->type == PIO_PERIPH_A) {
			pio_set_a_periph(pio_desc->pin_num,
			 	(pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
		} else if (pio_desc->type == PIO_PERIPH_B) {
			pio_set_b_periph(pio_desc->pin_num,
				(pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
		} else if (pio_desc->type == PIO_INPUT) {
			pio_set_deglitch(pio_desc->pin_num,
				(pio_desc->attribute & PIO_DEGLITCH) ? 1 : 0);
			pio_set_gpio_input(pio_desc->pin_num,
				(pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
		} else if (pio_desc->type == PIO_OUTPUT) {
			pio_set_multi_drive(pio_desc->pin_num,
				(pio_desc->attribute & PIO_OPENDRAIN) ? 1 : 0);
			pio_set_gpio_output(pio_desc->pin_num,
				pio_desc->default_value);
		} else {
			return 0;
		}
		
		++pin;
		++pio_desc;
	}

	return pin;
}
