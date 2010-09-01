/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
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
 * ----------------------------------------------------------------------------
 * File Name           : gpio.h
 * Object              :
 * Creation            : ODi Apr 24th 2006
 *-----------------------------------------------------------------------------
 */
#ifndef GPIO_H_
#define GPIO_H_

/* I/O type */
enum pio_type {
    PIO_PERIPH_A,
    PIO_PERIPH_B,
    PIO_INPUT,
    PIO_OUTPUT
};

/* I/O attributes */
#define PIO_DEFAULT   (0 << 0)
#define PIO_PULLUP    (1 << 0)
#define PIO_DEGLITCH  (1 << 1)
#define PIO_OPENDRAIN (1 << 2)

struct pio_desc {
    const char *pin_name;       /* Pin Name */
    unsigned int pin_num;       /* Pin number */
    unsigned int dft_value;     /* Default value for outputs */
    unsigned char attribute;
    enum pio_type type;
};

/* pio_set_value: assuming the pin is muxed as a gpio output, set its value. */
extern int pio_set_value(unsigned pin, int value);

/* pio_get_value: read the pin's value (works even if it's not muxed as a gpio).
 * !!! PIO Clock must be enabled in the PMC !!! */
extern int pio_get_value(unsigned pin);

/* pio_device_pio_setup: Configure PIO in periph mode according to the platform informations */
extern int pio_setup(const struct pio_desc *pio_desc);

/* these pin numbers double as IRQ numbers, like AT91C_ID_* values */
#define PIO_NB_IO		32      /* Number of IO handled by one PIO controller */
#define	AT91C_PIN_PA(io)	(0 * PIO_NB_IO + io)
#define	AT91C_PIN_PB(io)	(1 * PIO_NB_IO + io)
#define	AT91C_PIN_PC(io)	(2 * PIO_NB_IO + io)
#define	AT91C_PIN_PD(io)	(3 * PIO_NB_IO + io)
#define	AT91C_PIN_PE(io)	(4 * PIO_NB_IO + io)

#endif                          /* GPIO_H_ */
