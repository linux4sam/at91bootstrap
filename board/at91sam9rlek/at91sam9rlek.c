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
 * File Name           : at91sam9rl.c
 * Object              :
 * Creation            : ODi Apr 11th 2007
 *-----------------------------------------------------------------------------
 */
#if defined(WINCE) && !defined(CONFIG_AT91SAM9RLEK)

#else

#include "part.h"
#include "main.h"
#include "gpio.h"
#include "dbgu.h"
#include "pmc.h"
#include "rstc.h"
#include "debug.h"
#include "memory.h"

int get_cp15(void);

void set_cp15(unsigned int value);

int get_cpsr(void);

void set_cpsr(unsigned int value);

#ifdef CONFIG_HW_INIT
/*------------------------------------------------------------------------------*/
/* \fn    hw_init								*/
/* \brief This function performs very low level HW initialization		*/
/* This function is invoked as soon as possible during the c_startup	       	*/
/* The bss segment must be initialized					       	*/
/*------------------------------------------------------------------------------*/
void hw_init(void)
{
    unsigned int cp15;

    /*
     * Configure PIOs 
     */
    const struct pio_desc hw_pio[] = {
#ifdef CONFIG_DEBUG
        {"RXD", AT91C_PIN_PA(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"TXD", AT91C_PIN_PA(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
#endif
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Disable watchdog 
     */
    writel(AT91C_WDTC_WDDIS, AT91C_BASE_WDTC + WDTC_WDMR);

    /*
     * At this stage the main oscillator is supposed to be enabled
     * * PCK = MCK = MOSC 
     */

    /*
     * Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA 
     */
    pmc_cfg_plla(PLL_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * PCK = PLL = 2 * MCK 
     */
    pmc_cfg_mck(MCKR_SETTINGS, PLL_LOCK_TIMEOUT);
    /*
     * Switch MCK on PLLA output 
     */
    pmc_cfg_mck(MCKR_CSS_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * Enable External Reset 
     */
    writel(AT91C_RSTC_KEY_UNLOCK
           || AT91C_RSTC_URSTEN, AT91C_BASE_RSTC + RSTC_RMR);

    /*
     * Configure CP15 
     */
    cp15 = get_cp15();
    //cp15 |= I_CACHE;
    set_cp15(cp15);

    /*
     * Configure the PIO controller to output PCK0 
     */
    pio_setup(hw_pio);

#ifdef CONFIG_DEBUG
    /*
     * Enable Debug messages on the DBGU 
     */
    dbgu_init(BAUDRATE(MASTER_CLOCK, 115200));
    dbgu_print("Start AT91Bootstrap...\n\r");
#endif                          /* CONFIG_VERBOSE */

    /*
     * Configure the EBI Slave Slot Cycle to 64 
     */
    writel((readl((AT91C_MATRIX_SCFG4)) & ~0xFF) | 0x40, AT91C_MATRIX_SCFG4);

    /*
     * Initialize the matrix Slave 0 & Slave 4 (SRAM & EBI)
     */
    writel(readl(AT91C_MATRIX_SCFG0) | AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR |
           AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D, AT91C_MATRIX_SCFG0);
    writel(readl(AT91C_MATRIX_SCFG4) | AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR |
           AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D, AT91C_MATRIX_SCFG4);

#ifdef CONFIG_SDRAM
    /*
     * Initialize the matrix 
     */
    writel(readl(AT91C_CCFG_EBICSA) | AT91C_EBI_CS1A_SDRAMC, AT91C_CCFG_EBICSA);

#ifdef MCK_100
    /*
     * Configure SDRAM Controller 
     */
    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_7 | AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2 | AT91C_SDRAMC_TRAS_5 | AT91C_SDRAMC_TXSR_8,       /* Control Register */
               (MASTER_CLOCK * 7) / 1000000,    /* Refresh Timer Register */
               AT91C_SDRAMC_MD_SDRAM);  /* SDRAM (no low power)   */
#else                           /* 133 MHz */
    /*
     * Configure SDRAM Controller 
     */
    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_3 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_9 | AT91C_SDRAMC_TRP_3 | AT91C_SDRAMC_TRCD_3 | AT91C_SDRAMC_TRAS_6 | AT91C_SDRAMC_TXSR_10,      /* Control Register */
               (MASTER_CLOCK * 7) / 1000000,    /* Refresh Timer Register */
               AT91C_SDRAMC_MD_SDRAM);  /* SDRAM (no low power)   */
#endif

#endif
}
#endif                          /* CONFIG_HW_INIT */

#ifdef CONFIG_SDRAM
/*------------------------------------------------------------------------------*/
/* \fn    sdramc_hw_init							*/
/* \brief This function performs SDRAMC HW initialization			*/
/*------------------------------------------------------------------------------*/
void sdramc_hw_init(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc sdramc_pio[] = {
        {"D16", AT91C_PIN_PB(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D17", AT91C_PIN_PB(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D18", AT91C_PIN_PB(18), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D19", AT91C_PIN_PB(19), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D20", AT91C_PIN_PB(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D21", AT91C_PIN_PB(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D22", AT91C_PIN_PB(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D23", AT91C_PIN_PB(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D24", AT91C_PIN_PB(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D25", AT91C_PIN_PB(25), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D26", AT91C_PIN_PB(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D27", AT91C_PIN_PB(27), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D28", AT91C_PIN_PB(28), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D29", AT91C_PIN_PB(29), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D30", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"D31", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Configure the SDRAMC PIO controller to output PCK0 
     */
    pio_setup(sdramc_pio);
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
        {"MISO", AT91C_PIN_PA(25), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"MOSI", AT91C_PIN_PA(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"SPCK", AT91C_PIN_PA(27), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"NPCS0", AT91C_PIN_PA(28), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Configure the PIO controller 
     */
    pio_setup(df_pio);
}
#endif                          /* CONFIG_DATAFLASH */

#ifdef CONFIG_NANDFLASH
/*------------------------------------------------------------------------------*/
/* \fn    nandflash_hw_init							*/
/* \brief NandFlash HW init							*/
/*------------------------------------------------------------------------------*/
void nandflash_hw_init(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc nand_pio[] = {
        {"NANDALE", AT91C_PIN_PB(2), 0, PIO_PULLUP, PIO_PERIPH_A},
        {"NANDCLE", AT91C_PIN_PB(3), 0, PIO_PULLUP, PIO_PERIPH_A},
        {"NANDOE", AT91C_PIN_PB(4), 0, PIO_PULLUP, PIO_PERIPH_A},
        {"NANDWE", AT91C_PIN_PB(5), 0, PIO_PULLUP, PIO_PERIPH_A},
        {"NANDCS", AT91C_PIN_PB(6), 0, PIO_PULLUP, PIO_OUTPUT},
        {"RDY_BSY", AT91C_PIN_PD(17), 0, PIO_PULLUP, PIO_INPUT},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Setup Smart Media, first enable the address range of CS3 in HMATRIX user interface 
     */
    writel(readl(AT91C_CCFG_EBICSA) | AT91C_EBI_CS3A_SM, AT91C_CCFG_EBICSA);

    /*
     * Configure SMC CS3 
     */
    writel((AT91C_SM_NWE_SETUP | AT91C_SM_NCS_WR_SETUP | AT91C_SM_NRD_SETUP |
            AT91C_SM_NCS_RD_SETUP), AT91C_BASE_SMC + SMC_SETUP3);
    writel((AT91C_SM_NWE_PULSE | AT91C_SM_NCS_WR_PULSE | AT91C_SM_NRD_PULSE |
            AT91C_SM_NCS_RD_PULSE), AT91C_BASE_SMC + SMC_PULSE3);
    writel((AT91C_SM_NWE_CYCLE | AT91C_SM_NRD_CYCLE),
           AT91C_BASE_SMC + SMC_CYCLE3);
    writel((AT91C_SMC_READMODE | AT91C_SMC_WRITEMODE |
            AT91C_SMC_NWAITM_NWAIT_DISABLE | AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS |
            AT91C_SM_TDF), AT91C_BASE_SMC + SMC_CTRL3);

    /*
     * Configure the PIO controller 
     */
    writel((1 << AT91C_ID_PIOD), PMC_PCER + AT91C_BASE_PMC);
    pio_setup(nand_pio);
}

void nandflash_cfg_16bits_dbw_init(void)
{
    writel(readl(AT91C_BASE_SMC + SMC_CTRL3) | AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS,
           AT91C_BASE_SMC + SMC_CTRL3);
}

/*------------------------------------------------------------------------------*/
/* \fn    nandflash_cfg_8bits_dbw_init						*/
/* \brief Configure SMC in 8 bits mode						*/
/*------------------------------------------------------------------------------*/
void nandflash_cfg_8bits_dbw_init(void)
{
    writel((readl(AT91C_BASE_SMC + SMC_CTRL3) & ~(AT91C_SMC_DBW)) |
           AT91C_SMC_DBW_WIDTH_EIGTH_BITS, AT91C_BASE_SMC + SMC_CTRL3);
}

#endif                          /* #ifdef CONFIG_NANDFLASH */

#ifdef CONFIG_SCLK
void sclk_enable(void)
{
    volatile int i;

    unsigned int dwRegSave;

    (*(volatile unsigned int *)AT91C_SYS_SLCKSEL) =
        AT91C_SLCKSEL_OSC32EN | AT91C_SLCKSEL_RCEN;
    for (i = 0; i < 0x100000; i++) ;    //wait for a slow clock  startup time

    (*(volatile unsigned int *)AT91C_SYS_SLCKSEL) =
        AT91C_SLCKSEL_OSC32EN | AT91C_SLCKSEL_RCEN | AT91C_SLCKSEL_OSCSEL;
    for (i = 0; i < 0x1000; i++) ;

    dwRegSave = (*(volatile unsigned int *)AT91C_PMC_MCKR);
    (*(volatile unsigned int *)AT91C_PMC_MCKR) = AT91C_PMC_MDIV_2;

    while (((*(volatile unsigned int *)AT91C_PMC_SR) & AT91C_PMC_MCKRDY) == 0) ;

    (*(volatile unsigned int *)AT91C_PMC_MOR) &= ~AT91C_CKGR_MOSCEN;
    (*(volatile unsigned int *)AT91C_PMC_MOR) |= AT91C_CKGR_MOSCEN;

    while (((*(volatile unsigned int *)AT91C_PMC_SR) & AT91C_PMC_MOSCS) == 0) ;

    (*(volatile unsigned int *)AT91C_PMC_MCKR) = dwRegSave;
    while (((*(volatile unsigned int *)AT91C_PMC_SR) & AT91C_PMC_MCKRDY) == 0) ;

}
#endif

#endif                          /* CONFIG_AT91SAM9RLEK */
