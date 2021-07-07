/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __GPIO_H__
#define __GPIO_H__

/* I/O type */
enum pio_type {
	PIO_PERIPH_A,
	PIO_PERIPH_B,
	PIO_PERIPH_C,
	PIO_PERIPH_D,
	PIO_PERIPH_E,
	PIO_PERIPH_F,
	PIO_PERIPH_G,
	PIO_INPUT,
	PIO_OUTPUT
};

/* I/O attributes */
#define PIO_DEFAULT	(0 << 0)
#define PIO_PULLUP	(1 << 0)
#define PIO_DEGLITCH	(1 << 1)
#define PIO_OPENDRAIN	(1 << 2)
#define PIO_PULLDOWN	(1 << 3)
#define PIO_DRVSTR_LO	(1 << 4)
#define PIO_DRVSTR_ME	(1 << 5)
#define PIO_DRVSTR_HI	(1 << 6)
#define PIO_SLEWR_CTRL	(1 << 7)

struct pio_desc {
	const char	*pin_name;	/* Pin Name */
	unsigned int	pin_num;	/* Pin number */
	unsigned int	default_value;	/* Default value for outputs */
	unsigned char	attribute;
	enum pio_type	type;
};

extern int pio_set_value(unsigned pin, int value);
extern int pio_get_value(unsigned pin);

/* pio_device_pio_setup: Configure PIO in periph mode according to the platform informations */
extern int pio_configure(const struct pio_desc *pio_desc);

extern int pio_set_gpio_input(unsigned pin, int config);
extern int pio_set_gpio_output(unsigned pin, int value);

#endif /* #ifndef __GPIO_H__ */
