/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation

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
 * File Name           : at91sam9g20ek.c
 * Object              :
 * Creation            : NFe Jan 2008
 *-----------------------------------------------------------------------------
 */
#if defined(WINCE) && !defined(CONFIG_AT91SAM9G20EK)

#else

#include "part.h"
#include "main.h"
#include "gpio.h"
#include "pmc.h"
#include "rstc.h"
#include "dbgu.h"
#include "debug.h"
#include "memory.h"

int get_cp15(void);

void set_cp15(unsigned int value);

int get_cpsr(void);

void set_cpsr(unsigned int value);

#ifdef CONFIG_HW_INIT
/*----------------------------------------------------------------------------*/
/* \fn    hw_init							      */
/* \brief This function performs very low level HW initialization	      */
/* This function is invoked as soon as possible during the c_startup	      */
/* The bss segment must be initialized					      */
/*----------------------------------------------------------------------------*/
void hw_init(void)
{
    unsigned int cp15;

    /*
     * Configure PIOs 
     */
    const struct pio_desc hw_pio[] = {
#ifdef CONFIG_DEBUG
        {"RXD", AT91C_PIN_PB(14), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"TXD", AT91C_PIN_PB(15), 0, PIO_DEFAULT, PIO_PERIPH_A},
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
    writel(0x00, AT91C_BASE_PMC + PMC_PLLICPR);

    /*
     * Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA 
     */
    pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

    /*
     * PCK = PLLA/2 = 3 * MCK 
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
     * Configure CP15 
     */
    cp15 = get_cp15();
    //cp15 |= I_CACHE;
    set_cp15(cp15);

    /*
     * Enable External Reset 
     */
    writel(AT91C_RSTC_KEY_UNLOCK
           || AT91C_RSTC_URSTEN, AT91C_BASE_RSTC + RSTC_RMR);
    /*
     * Configure the PIO controller 
     */
    pio_setup(hw_pio);

    /*
     * Configure the EBI Slave Slot Cycle to 64 
     */
    writel((readl((AT91C_BASE_MATRIX + MATRIX_SCFG3)) & ~0xFF) | 0x40,
           (AT91C_BASE_MATRIX + MATRIX_SCFG3));

#ifdef CONFIG_DEBUG
    /*
     * Enable Debug messages on the DBGU 
     */
    dbgu_init(BAUDRATE(MASTER_CLOCK, 115200));
    dbgu_print("Start AT91Bootstrap...\n\r");
#endif                          /* CONFIG_DEBUG */

#ifdef CONFIG_SDRAM
    /*
     * Initialize the matrix (memory voltage = 3.3) 
     */
    writel((readl(AT91C_BASE_CCFG + CCFG_EBICSA)) | AT91C_EBI_CS1A_SDRAMC |
           (1 << 16), AT91C_BASE_CCFG + CCFG_EBICSA);

    /*
     * Configure SDRAM Controller 
     */
    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_3 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_3 | AT91C_SDRAMC_TRC_9 | AT91C_SDRAMC_TRP_3 | AT91C_SDRAMC_TRCD_3 | AT91C_SDRAMC_TRAS_6 | AT91C_SDRAMC_TXSR_10,      /* Control Register */
               (MASTER_CLOCK * 7) / 1000000,    /* Refresh Timer Register */
               AT91C_SDRAMC_MD_SDRAM);  /* SDRAM (no low power)   */

#endif                          /* CONFIG_SDRAM */
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
/*	const struct pio_desc sdramc_pio[] = {
		{"D16", AT91C_PIN_PC(16), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D17", AT91C_PIN_PC(17), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D18", AT91C_PIN_PC(18), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D19", AT91C_PIN_PC(19), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D20", AT91C_PIN_PC(20), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D21", AT91C_PIN_PC(21), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D22", AT91C_PIN_PC(22), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D23", AT91C_PIN_PC(23), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D24", AT91C_PIN_PC(24), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D25", AT91C_PIN_PC(25), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D26", AT91C_PIN_PC(26), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D27", AT91C_PIN_PC(27), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D28", AT91C_PIN_PC(28), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D29", AT91C_PIN_PC(29), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D30", AT91C_PIN_PC(30), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{"D31", AT91C_PIN_PC(31), 0, PIO_DEFAULT, PIO_PERIPH_A},
		{(char *) 0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};
*/
    /*
     * Configure the SDRAMC PIO controller to output PCK0 
     */
/*	pio_setup(sdramc_pio); */

    writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_ASR(0));
    writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_PDR(0));

}
#endif                          /* CONFIG_SDRAM */

#ifdef CONFIG_DATAFLASH
#if	defined(CONFIG_DATAFLASH_RECOVERY)
/*------------------------------------------------------------------------------*/
/* \fn    df_recovery								*/
/* \brief This function erases DataFlash Page 0 if BP4 is pressed 		*/
/*        during boot sequence							*/
/*------------------------------------------------------------------------------*/
void df_recovery(AT91PS_DF pDf)
{
#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS1_DATAFLASH)
    /*
     * Configure PIOs 
     */
    const struct pio_desc bp4_pio[] = {
        {"BP4", AT91C_PIN_PA(31), 0, PIO_PULLUP, PIO_INPUT},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Configure the PIO controller 
     */
    writel((1 << AT91C_ID_PIOA), PMC_PCER + AT91C_BASE_PMC);
    pio_setup(bp4_pio);

    /*
     * If BP4 is pressed during Boot sequence 
     */
    /*
     * Erase NandFlash block 0
     */
    if (!pio_get_value(AT91C_PIN_PA(31)))
        df_page_erase(pDf, 0);
#endif
}
#endif

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
        {"MISO", AT91C_PIN_PA(0), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"MOSI", AT91C_PIN_PA(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
        {"SPCK", AT91C_PIN_PA(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS0_DATAFLASH)
        {"NPCS0", AT91C_PIN_PA(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
#endif
#if (AT91C_SPI_PCS_DATAFLASH == AT91C_SPI_PCS1_DATAFLASH)
        {"NPCS1", AT91C_PIN_PC(11), 0, PIO_DEFAULT, PIO_PERIPH_B},
#endif
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
/* \fn    nand_recovery						*/
/* \brief This function erases NandFlash Block 0 if BP4 is pressed 		*/
/*        during boot sequence							*/
/*------------------------------------------------------------------------------*/
static void nand_recovery(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc bp4_pio[] = {
        {"BP4", AT91C_PIN_PA(31), 0, PIO_PULLUP, PIO_INPUT},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Configure the PIO controller 
     */
    writel((1 << AT91C_ID_PIOA), PMC_PCER + AT91C_BASE_PMC);
    pio_setup(bp4_pio);

    /*
     * If BP4 is pressed during Boot sequence 
     */
    /*
     * Erase NandFlash block 0
     */
    if (!pio_get_value(AT91C_PIN_PA(31)))
        AT91F_NandEraseBlock0();
}

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
        {"RDY_BSY", AT91C_PIN_PC(13), 0, PIO_PULLUP, PIO_INPUT},
        {"NANDCS", AT91C_PIN_PC(14), 0, PIO_PULLUP, PIO_OUTPUT},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Setup Smart Media, first enable the address range of CS3 in HMATRIX user interface 
     */
    writel(readl(AT91C_BASE_CCFG + CCFG_EBICSA) | AT91C_EBI_CS3A_SM,
           AT91C_BASE_CCFG + CCFG_EBICSA);

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
    writel((1 << AT91C_ID_PIOC), PMC_PCER + AT91C_BASE_PMC);
    pio_setup(nand_pio);

    nand_recovery();
}

/*------------------------------------------------------------------------------*/
/* \fn    nandflash_cfg_16bits_dbw_init						*/
/* \brief Configure SMC in 16 bits mode						*/
/*------------------------------------------------------------------------------*/
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

#endif                          /* CONFIG_AT91SAM9G20EK */
