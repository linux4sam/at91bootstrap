/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2007, Stelian Pop <stelian.pop@leadtechdesign.com>
 * Copyright (c) 2007 Lead Tech Design <www.leadtechdesign.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
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
 * File Name           : at91cap9adk.c
 * Object              :
 * Creation            :
 *-----------------------------------------------------------------------------
 */
#include "part.h"
#include "gpio.h"
#include "pmc.h"
#include "rstc.h"
#include "debug.h"
#include "memory.h"
#include "main.h"

#ifndef CONFIG_THUMB
static inline unsigned int get_cp15(void)
{
    unsigned int value;

 __asm__("mrc p15, 0, %0, c1, c0, 0":"=r"(value));
    return value;
}

static inline void set_cp15(unsigned int value)
{
 __asm__("mcr p15, 0, %0, c1, c0, 0": :"r"(value));
}
#else
int get_cp15(void);

void set_cp15(unsigned int value);
#endif

#ifdef CONFIG_HW_INIT
/*---------------------------------------------------------------------------- */
/* \fn    hw_init							       */
/* \brief This function performs very low level HW initialization	       */
/* This function is invoked as soon as possible during the c_startup	       */
/* The bss segment must be initialized					       */
/*---------------------------------------------------------------------------- */
void hw_init(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc hw_pio[] = {
#ifdef CONFIG_VERBOSE
        {"RXD", AT91C_PIN_PC(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"TXD", AT91C_PIN_PC(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
#endif
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Disable watchdog 
     */
    writel(AT91C_WDTC_WDDIS, AT91C_BASE_WDTC + WDTC_WDMR);

    /*
     * Ensure RTT interrupts are disabled, or
     * * Linux won't know how to handle them 
     */
    writel(readl(AT91C_BASE_RTTC + RTTC_RTMR) & 0xFFFCFFFF,
           AT91C_BASE_RTTC + RTTC_RTMR);

    /*
     * At this stage the main oscillator is supposed to be enabled
     * * PCK = MCK = MOSC 
     */

    /*
     * Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA 
     */
    pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * PCK = PLLA = 2 * MCK 
     */
    pmc_cfg_mck(MCKR_SETTINGS, PLL_LOCK_TIMEOUT);
    /*
     * Switch MCK on PLLA output 
     */
    pmc_cfg_mck(MCKR_CSS_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * Configure PLLB 
     */
    pmc_cfg_pllb(PLLB_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * Enable External Reset 
     */
    writel(AT91C_RSTC_KEY_UNLOCK
           || AT91C_RSTC_URSTEN, AT91C_BASE_RSTC + RSTC_RMR);

    /*
     * Configure the PIO controller to output PCK0 
     */
    pio_setup(hw_pio);

#ifdef CONFIG_VERBOSE
    /*
     * Enable Debug messages on the DBGU 
     */
    dbg_init(BAUDRATE(MASTER_CLOCK, 115200));
    header();
#endif                          /* CONFIG_VERBOSE */

#ifdef CONFIG_SDDRC
    /*
     * Initialize the matrix 
     */
    /*
     * VDDIOMSEL = 1 -> Memories are 3.3V powered 
     */
    writel(readl(AT91C_BASE_CCFG + CCFG_EBICSA) | AT91C_EBI_SUP_3V3,
           AT91C_BASE_CCFG + CCFG_EBICSA);

    /*
     * Configure SDRAM Controller 
     */
    sddrc_init(0x00000039, 781);
#endif                          /* CONFIG_SDDRC */
}
#endif                          /* CONFIG_HW_INIT */

#ifdef CONFIG_SDDRC
//*----------------------------------------------------------------------------
//* \fn    sdddrc_hw_init
//* \brief This function performs SDDRC HW initialization
//*----------------------------------------------------------------------------*/
void sddrc_hw_init(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc sddrc_pio[] = {
        {"D16", AT91C_PIN_PD(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D17", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D18", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D19", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D20", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D21", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D22", AT91C_PIN_PD(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D23", AT91C_PIN_PD(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D24", AT91C_PIN_PD(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D25", AT91C_PIN_PD(25), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D26", AT91C_PIN_PD(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D27", AT91C_PIN_PD(27), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D28", AT91C_PIN_PD(28), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D29", AT91C_PIN_PD(29), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D30", AT91C_PIN_PD(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D31", AT91C_PIN_PD(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Configure the SDDRC PIO controller 
     */
    pio_setup(sddrc_pio);
}
#endif

#ifdef CONFIG_DATAFLASH
/*------------------------------------------------------------------------------*/
/* \fn    df_hw_init								*/
/* \brief This function performs DataFlash HW initialization			*/
/*------------------------------------------------------------------------------*/
void df_hw_init(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc df_pio[] = {
        {"MISO", AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_B},
        {"MOSI", AT91C_PIN_PA(1), 0, PIO_DEFAULT, PIO_PERIPH_B},
        {"SPCK", AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_B},
        {"NPCS0", AT91C_PIN_PA(5), 0, PIO_DEFAULT, PIO_PERIPH_B},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Configure the PIO controller 
     */
    pio_setup(df_pio);
}
#endif                          /* CONFIG_DATAFLASH */

#ifdef CONFIG_FLASH
void norflash_hw_init(void)
{
    /*
     * Configure CS0 
     */
    writel(AT91C_FLASH_NWE_SETUP |
           AT91C_FLASH_NCS_WR_SETUP |
           AT91C_FLASH_NRD_SETUP |
           AT91C_FLASH_NCS_RD_SETUP, AT91C_BASE_SMC + SMC_SETUP0);
    writel(AT91C_FLASH_NWE_PULSE |
           AT91C_FLASH_NCS_WR_PULSE |
           AT91C_FLASH_NRD_PULSE |
           AT91C_FLASH_NCS_RD_PULSE, AT91C_BASE_SMC + SMC_PULSE0);
    writel(AT91C_FLASH_NWE_CYCLE |
           AT91C_FLASH_NRD_CYCLE, AT91C_BASE_SMC + SMC_CYCLE0);
    writel(AT91C_SMC_READMODE |
           AT91C_SMC_WRITEMODE |
           AT91C_SMC_NWAITM_NWAIT_DISABLE |
           AT91C_SMC_BAT_BYTE_WRITE |
           AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS |
           (AT91C_SMC_TDF & (1 << 16)), AT91C_BASE_SMC + SMC_CTRL0);
}
#endif
