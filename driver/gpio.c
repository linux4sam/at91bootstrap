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
 * File Name           : gpio.c
 * Object              :
 * Creation            : ODi Apr 19th 2006
 *-----------------------------------------------------------------------------
 */
#include "part.h"
#include "main.h"
#include "gpio.h"
#include "debug.h"

#define EINVAL 1                /* Error code returned when the PIN is unknown */

/* Write PIO register */
static inline void write_pio(unsigned int offset, const unsigned int value)
{
    writel(value, offset + AT91C_BASE_PIOA);
}

/* Read PIO registers */
static inline unsigned int read_pio(volatile unsigned int offset)
{
    return readl(offset + AT91C_BASE_PIOA);
}

/* Convert Pin Number into PIO controller index */
static inline unsigned pin_to_controller(unsigned pin)
{
    return (pin) / PIO_NB_IO;
}

/* Convert Pin Number into I/O line index */
static inline unsigned pin_to_mask(unsigned pin)
{
    return 1 << ((pin) % PIO_NB_IO);
}

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_A_periph							*/
/* \brief the pin to the "A" internal peripheral role.				*/
/*------------------------------------------------------------------------------*/
static int pio_set_A_periph(unsigned pin, int use_pullup)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

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

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_B_periph							*/
/* \brief mux the pin to the "B" internal peripheral role.			*/
/*------------------------------------------------------------------------------*/
static int pio_set_B_periph(unsigned pin, int use_pullup)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

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

#if 0
#ifdef CONFIG_HAS_PIO3
/*------------------------------------------------------------------------------*/
/* \fn    pio_set_C_periph							*/
/* \brief mux the pin to the "C" internal peripheral role.			*/
/*------------------------------------------------------------------------------*/
static int pio_set_C_periph(unsigned pin, int use_pullup)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

    write_pio(PIO_IDR(pio), mask);
    write_pio((use_pullup ? PIO_PPUER(pio) : PIO_PPUDR(pio)), mask);

    write_pio(PIO_SP1(pio), read_pio(PIO_SP1(pio)) & ~mask);
    write_pio(PIO_SP2(pio), read_pio(PIO_SP2(pio)) | mask);

    write_pio(PIO_PDR(pio), mask);
    return 0;
}

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_D_periph							*/
/* \brief mux the pin to the "D" internal peripheral role.			*/
/*------------------------------------------------------------------------------*/
static int pio_set_D_periph(unsigned pin, int use_pullup)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

    write_pio(PIO_IDR(pio), mask);
    write_pio((use_pullup ? PIO_PPUER(pio) : PIO_PPUDR(pio)), mask);

    write_pio(PIO_SP1(pio), read_pio(PIO_SP1(pio)) | mask);
    write_pio(PIO_SP2(pio), read_pio(PIO_SP2(pio)) | mask);

    write_pio(PIO_PDR(pio), mask);
    return 0;
}
#endif                          /* CONFIG_HAS_PIO3 */
#endif /* #if 0 */

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_gpio_input							*/
/* \brief mux the pin to the gpio controller (instead of "A" or "B" peripheral),*/
/*        and configure it for an input.					*/
/*------------------------------------------------------------------------------*/
int pio_set_gpio_input(unsigned pin, int use_pullup)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

    write_pio(PIO_IDR(pio), mask);
    write_pio((use_pullup ? PIO_PPUER(pio) : PIO_PPUDR(pio)), mask);
    write_pio(PIO_ODR(pio), mask);
    write_pio(PIO_PER(pio), mask);
    return 0;
}

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_gpio_output													*/
/* \brief mux the pin to the gpio controller (instead of "A" or "B" peripheral),*/
/*        and configure it for an output.										*/
/*------------------------------------------------------------------------------*/
int pio_set_gpio_output(unsigned pin, int value)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

    write_pio(PIO_IDR(pio), mask);
    write_pio(PIO_PPUDR(pio), mask);
    write_pio((value ? PIO_SODR(pio) : PIO_CODR(pio)), mask);
    write_pio(PIO_OER(pio), mask);
    write_pio(PIO_PER(pio), mask);
    return 0;
}

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_deglitch							*/
/* \brief enable/disable the glitch filter; mostly used with IRQ handling.	*/
/*------------------------------------------------------------------------------*/
static int pio_set_deglitch(unsigned pin, int is_on)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;
    write_pio((is_on ? PIO_IFER(pio) : PIO_IFDR(pio)), mask);
    return 0;
}

/*------------------------------------------------------------------------------*/
/* \fn    pio_set_multi_drive							*/
/* \brief enable/disable the multi-driver; This is only valid for output and	*/
/*        allows the output pin to run as an open collector output.		*/
/*------------------------------------------------------------------------------*/
static int pio_set_multi_drive(unsigned pin, int is_on)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;

    write_pio((is_on ? PIO_MDER(pio) : PIO_MDDR(pio)), mask);
    return 0;
}

#if !defined(at91sam9g10)
/*------------------------------------------------------------------------------*/
/* \fn    pio_set_value								*/
/* \brief assuming the pin is muxed as a gpio output, set its value.		*/
/*------------------------------------------------------------------------------*/
int pio_set_value(unsigned pin, int value)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;
    write_pio((value ? PIO_SODR(pio) : PIO_CODR(pio)), mask);
    return 0;
}
#endif

/*------------------------------------------------------------------------------*/
/* \fn    pio_get_value								*/
/* \brief read the pin's value (works even if it's not muxed as a gpio).	*/
/*        !!! PIO Clock must be enabled in the PMC !!!				*/
/*------------------------------------------------------------------------------*/
int pio_get_value(unsigned pin)
{
    unsigned pio = pin_to_controller(pin);

    unsigned mask = pin_to_mask(pin);

    unsigned int pdsr;

    if (pio >= AT91C_NR_PIO)
        return -EINVAL;
    pdsr = read_pio(PIO_PDSR(pio));
    return (pdsr & mask) != 0;
}

/*------------------------------------------------------------------------------*/
/* \fn    pio_device_pio_setup							*/
/* \brief Configure PIO in periph mode according to the platform informations	*/
/*------------------------------------------------------------------------------*/
int pio_setup(const struct pio_desc *pio_desc)
{
    unsigned pio, pin = 0;

    if (!pio_desc) {
        return 0;
    }

    /*
     * Sets all the pio muxing of the corresponding device as defined in its platform_data struct 
     */
    while (pio_desc->pin_name) {
        pio = pin_to_controller(pio_desc->pin_num);
        if (pio >= AT91C_NR_PIO)
            return 0;
        else if (pio_desc->type == PIO_PERIPH_A)
            pio_set_A_periph(pio_desc->pin_num,
                             (pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
#if !(defined(at91sam9g10)&&defined(CONFIG_SDCARD))
        else if (pio_desc->type == PIO_PERIPH_B)
            pio_set_B_periph(pio_desc->pin_num,
                             (pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
        else if (pio_desc->type == PIO_INPUT) {
            pio_set_deglitch(pio_desc->pin_num,
                             (pio_desc->attribute & PIO_DEGLITCH) ? 1 : 0);
            pio_set_gpio_input(pio_desc->pin_num,
                               (pio_desc->attribute & PIO_PULLUP) ? 1 : 0);
        } else if (pio_desc->type == PIO_OUTPUT) {
            pio_set_multi_drive(pio_desc->pin_num,
                                (pio_desc->attribute & PIO_OPENDRAIN) ? 1 : 0);
            pio_set_gpio_output(pio_desc->pin_num, pio_desc->dft_value);
        }
#endif
        else
            return 0;
        ++pin;
        ++pio_desc;
    }
    return pin;
}
