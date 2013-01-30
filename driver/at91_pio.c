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

static inline void write_pio(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_PIOA);
}

static inline unsigned int read_pio(volatile unsigned int offset)
{
	return readl(offset + AT91C_BASE_PIOA);
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

	write_pio(PIO_IDR(pio), mask);
	write_pio(use_pullup ? PIO_PPUER(pio) : PIO_PPUDR(pio), mask);
#ifndef CONFIG_HAS_PIO3
	write_pio(PIO_ASR(pio), mask);
#else
	write_pio(PIO_SP1(pio), read_pio(PIO_SP1(pio)) & ~mask);
	write_pio(PIO_SP2(pio), read_pio(PIO_SP2(pio)) & ~mask);
#endif
	write_pio(PIO_PDR(pio), mask);
	return 0;
}

static int pio_set_b_periph(unsigned pin, int use_pullup)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(PIO_IDR(pio), mask);
	write_pio((use_pullup ? PIO_PPUER(pio) : PIO_PPUDR(pio)), mask);
#ifndef CONFIG_HAS_PIO3
	write_pio(PIO_BSR(pio), mask);
#else
	write_pio(PIO_SP1(pio), read_pio(PIO_SP1(pio)) | mask);
	write_pio(PIO_SP2(pio), read_pio(PIO_SP2(pio)) & ~mask);
#endif
	write_pio(PIO_PDR(pio), mask);
	return 0;
}

int pio_set_gpio_input(unsigned pin, int use_pullup)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(PIO_IDR(pio), mask);
	write_pio((use_pullup ? PIO_PPUER(pio) : PIO_PPUDR(pio)), mask);
	write_pio(PIO_ODR(pio), mask);
	write_pio(PIO_PER(pio), mask);
	return 0;
}

int pio_set_gpio_output(unsigned pin, int value)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio(PIO_IDR(pio), mask);
	write_pio(PIO_PPUDR(pio), mask);
	write_pio((value ? PIO_SODR(pio) : PIO_CODR(pio)), mask);
	write_pio(PIO_OER(pio), mask);
	write_pio(PIO_PER(pio), mask);
	return 0;
}

static int pio_set_deglitch(unsigned pin, int is_on)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio((is_on ? PIO_IFER(pio) : PIO_IFDR(pio)), mask);
	return 0;
}

static int pio_set_multi_drive(unsigned pin, int is_on)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio((is_on ? PIO_MDER(pio) : PIO_MDDR(pio)), mask);
	return 0;
}

#if !defined(at91sam9g10)
int pio_set_value(unsigned pin, int value)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);

	if (pio >= AT91C_NUM_PIO)
		return -1;

	write_pio((value ? PIO_SODR(pio) : PIO_CODR(pio)), mask);
	return 0;
}
#endif

int pio_get_value(unsigned pin)
{
	unsigned pio = pin_to_controller(pin);
	unsigned mask = pin_to_mask(pin);
	unsigned int pdsr;

	if (pio >= AT91C_NUM_PIO)
		return -1;

	pdsr = read_pio(PIO_PDSR(pio));
	return ((pdsr & mask) != 0);
}

int pio_configure(const struct pio_desc *pio_desc)
{
	unsigned pio, pin = 0;

	if (pio_desc == 0) return 0;

	/*
	 * Sets all the pio muxing of the corresponding device as defined in its platform_data struct 
	 */
	while (pio_desc->pin_name) {
		pio = pin_to_controller(pio_desc->pin_num);
		if (pio >= AT91C_NUM_PIO)
			return 0;
		else if (pio_desc->type == PIO_PERIPH_A)
			pio_set_a_periph(pio_desc->pin_num,
			 	(pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
#if !(defined(at91sam9g10)&&defined(CONFIG_SDCARD))
		else if (pio_desc->type == PIO_PERIPH_B)
			pio_set_b_periph(pio_desc->pin_num,
				(pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
		else if (pio_desc->type == PIO_INPUT) {
			pio_set_deglitch(pio_desc->pin_num,
				(pio_desc->attribute & PIO_DEGLITCH) ? 1 : 0);
			pio_set_gpio_input(pio_desc->pin_num,
				(pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
		} else if (pio_desc->type == PIO_OUTPUT) {
			pio_set_multi_drive(pio_desc->pin_num,
				(pio_desc->attribute & PIO_OPENDRAIN) ? 1 : 0);
			pio_set_gpio_output(pio_desc->pin_num,
				pio_desc->default_value);
		}
#endif
		else
			return 0;
		
		++pin;
		++pio_desc;
	}
	return pin;
}
