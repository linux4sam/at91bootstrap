/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 * All rights reserved.
 * PSRAM,16 bit SDRAM support courtesy of Epsilon Group
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
 * File Name           : at91sam9263ek.c
 * Object              :
 * Creation            : NLe Aug 8th 2006
 *-----------------------------------------------------------------------------
 */
#if defined(WINCE) && !defined(CONFIG_AT91SAM9263EK)

#else

#include "part.h"
#include "main.h"
#include "gpio.h"
#include "pmc.h"
#include "rstc.h"
#include "debug.h"
#include "dbgu.h"
#include "memory.h"
#include "psram.h"
#include "matrix.h"

int get_cp15(void);

void set_cp15(unsigned int value);

int get_cpsr(void);

void set_cpsr(unsigned int value);

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
#ifdef CONFIG_DEBUG
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

    /*
     * Configure TCMs (Tightly coupled memories) 
     */

    /*
     * Configure the EBI0 Slave Slot Cycle to 64 
     */
    // writel( (readl((AT91C_BASE_MATRIX + MATRIX_SCFG4)) & ~0xFF) | 0x40, (AT91C_BASE_MATRIX + MATRIX_SCFG4));

    writel(BURST_16WORD_BEAT, AHB_MATRIX_MASTER_OHCI);
    writel(BURST_8WORD_BEAT, AHB_MATRIX_MASTER_ISI);
    writel(BURST_8WORD_BEAT, AHB_MATRIX_MASTER_2D);
    writel(BURST_8WORD_BEAT, AHB_MATRIX_MASTER_DMAC);
    writel(BURST_4WORD_BEAT, AHB_MATRIX_MASTER_MACB);
    writel(BURST_16WORD_BEAT, AHB_MATRIX_MASTER_LCDC);
    writel(BURST_SINGLE_ACCESS, AHB_MATRIX_MASTER_PDC);
    writel(BURST_8WORD_BEAT, AHB_MATRIX_MASTER_DBUS);
    writel(BURST_4WORD_BEAT, AHB_MATRIX_MASTER_IBUS);

#if	0
    // ARBT
    AHB_MATRIX_FIXED_PRIORITY || AHB_MATRIX_ROUND_ROBIN ||
        // FIXED_DEFMSTR
        AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I ||
        AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D ||
        AT91C_MATRIX_FIXED_DEFMSTR0_PDC ||
        AT91C_MATRIX_FIXED_DEFMSTR0_LCDC ||
        AT91C_MATRIX_FIXED_DEFMSTR0_2DGC ||
        AT91C_MATRIX_FIXED_DEFMSTR0_ISI ||
        AT91C_MATRIX_FIXED_DEFMSTR0_DMA ||
        AT91C_MATRIX_FIXED_DEFMSTR0_EMAC || AT91C_MATRIX_FIXED_DEFMSTR0_USB ||
        // DEFMSTR_TYPE
        AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR ||
        AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR ||
        AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
        // SLOT_CYCLE
        SLOT_CYCLE(),
#endif
        writel(
                  // ARBT
                  AHB_MATRIX_FIXED_PRIORITY ||
                  // FIXED_DEFMSTR
                  AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I ||
                  // DEFMSTR_TYPE
                  AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR ||
                  // SLOT_CYCLE
                  SLOT_CYCLE(32), AHB_MATRIX_SLAVE_ROM);

    writel(
              // ARBT
              AHB_MATRIX_FIXED_PRIORITY ||
              // FIXED_DEFMSTR
              AT91C_MATRIX_FIXED_DEFMSTR0_EMAC ||
              // DEFMSTR_TYPE
              AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
              // SLOT_CYCLE
              SLOT_CYCLE(32), AHB_MATRIX_SLAVE_RAM80K);

    writel(
              // ARBT
              AHB_MATRIX_FIXED_PRIORITY ||
              // FIXED_DEFMSTR
              AT91C_MATRIX_FIXED_DEFMSTR0_USB ||
              // DEFMSTR_TYPE
              AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
              // SLOT_CYCLE
              SLOT_CYCLE(16), AHB_MATRIX_SLAVE_RAM16K);

    writel(
              // ARBT
              AHB_MATRIX_FIXED_PRIORITY ||
              // FIXED_DEFMSTR
              AT91C_MATRIX_FIXED_DEFMSTR0_PDC ||
              // DEFMSTR_TYPE
              AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
              // SLOT_CYCLE
              SLOT_CYCLE(4), AHB_MATRIX_SLAVE_PERIPHERALS);

    writel(
              // ARBT
              AHB_MATRIX_ROUND_ROBIN ||
              // FIXED_DEFMSTR
              AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I ||
              // DEFMSTR_TYPE
              AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
              // SLOT_CYCLE
              SLOT_CYCLE(32), AHB_MATRIX_SLAVE_EBI0);

    writel(
              // ARBT
              AHB_MATRIX_FIXED_PRIORITY ||
              // FIXED_DEFMSTR
              AT91C_MATRIX_FIXED_DEFMSTR0_LCDC ||
              // DEFMSTR_TYPE
              AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
              // SLOT_CYCLE
              SLOT_CYCLE(64), AHB_MATRIX_SLAVE_EBI1);

    writel(
              // ARBT
              AHB_MATRIX_FIXED_PRIORITY ||
              // FIXED_DEFMSTR
              AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D ||
              // DEFMSTR_TYPE
              AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR ||
              // SLOT_CYCLE
              SLOT_CYCLE(4), AHB_MATRIX_SLAVE_APB);

    AHB_PRIORITY9(ABH_PRIORITY_ROM, AHB_IBUS_ID, AHB_DBUS_ID,
                  // Rest should not access the ROM
                  AHB_PDC_ID,
                  AHB_DMAC_ID,
                  AHB_OHCI_ID, AHB_ISI_ID, AHB_2D_ID, AHB_MACB_ID, AHB_LCDC_ID);
    AHB_PRIORITY9(ABH_PRIORITY_RAM80K,
                  AHB_PDC_ID,
                  AHB_MACB_ID,
                  AHB_DMAC_ID, AHB_OHCI_ID, AHB_IBUS_ID, AHB_DBUS_ID,
                  // Rest should not access the large SRAM
                  AHB_ISI_ID, AHB_2D_ID, AHB_LCDC_ID);
    AHB_PRIORITY9(ABH_PRIORITY_RAM16K,
                  AHB_OHCI_ID,
                  AHB_PDC_ID, AHB_DMAC_ID, AHB_DBUS_ID, AHB_IBUS_ID,
                  // Rest should not access the small SRAM
                  AHB_ISI_ID, AHB_2D_ID, AHB_MACB_ID, AHB_LCDC_ID);
    AHB_PRIORITY9(ABH_PRIORITY_PERIPHERALS, AHB_DBUS_ID,
                  // Rest should not access & reconfigure peripherals
                  AHB_PDC_ID,
                  AHB_DMAC_ID,
                  AHB_OHCI_ID,
                  AHB_ISI_ID, AHB_2D_ID, AHB_MACB_ID, AHB_LCDC_ID, AHB_IBUS_ID);

#if	defined(CONFIG_PSRAM)
    // LCD on EBI1
    AHB_PRIORITY9(ABH_PRIORITY_EBI0,
                  AHB_PDC_ID,
                  AHB_MACB_ID,
                  AHB_OHCI_ID, AHB_DMAC_ID, AHB_IBUS_ID, AHB_DBUS_ID,
                  // Rest should not access EBI0
                  AHB_ISI_ID, AHB_LCDC_ID, AHB_2D_ID);
#else
    // LCD on EBI0
    AHB_PRIORITY9(ABH_PRIORITY_EBI0,
                  AHB_PDC_ID,
                  AHB_LCDC_ID,
                  AHB_MACB_ID,
                  AHB_OHCI_ID, AHB_DMAC_ID, AHB_2D_ID, AHB_IBUS_ID, AHB_DBUS_ID,
                  // Rest should not access EBI0
                  AHB_ISI_ID);
#endif

    AHB_PRIORITY9(ABH_PRIORITY_EBI1,
                  AHB_LCDC_ID, AHB_PDC_ID, AHB_DMAC_ID, AHB_2D_ID, AHB_DBUS_ID,
                  // Rest should not access ABI1
                  AHB_IBUS_ID, AHB_OHCI_ID, AHB_ISI_ID, AHB_MACB_ID);

    AHB_PRIORITY9(ABH_PRIORITY_APB, AHB_PDC_ID, AHB_DMAC_ID, AHB_DBUS_ID,
                  // Rest should not access APB
                  AHB_IBUS_ID,
                  AHB_OHCI_ID, AHB_ISI_ID, AHB_2D_ID, AHB_MACB_ID, AHB_LCDC_ID);

#ifdef CONFIG_DEBUG
    /*
     * Enable Debug messages on the DBGU 
     */
    dbgu_init(BAUDRATE(MASTER_CLOCK, 115200));
    dbgu_print("Start AT91Bootstrap...\n\r");
#endif

#ifdef CONFIG_SDRAM
    /*
     * Initialize the matrix 
     */
    /*
     * VDDIOMSEL = 1 -> Memories are 3.3V powered 
     */
    writel(readl(AT91C_BASE_CCFG + CCFG_EBI0CSA) | (1 << 16) |
           AT91C_EBI_CS1A_SDRAMC, AT91C_BASE_CCFG + CCFG_EBI0CSA);
    /*
     * Configure SDRAM Controller 
     */
#if	defined(CONFIG_SDRAM_16BIT)
    sdram_init(AT91C_SDRAMC_NC_10 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_16_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_7 | AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2 | AT91C_SDRAMC_TRAS_5 | AT91C_SDRAMC_TXSR_8,      /* Control Register       */
               (MASTER_CLOCK * 7) / 1000000,    /* Refresh Timer Register */
               AT91C_SDRAMC_MD_SDRAM);  /* SDRAM (no low power)   */
#else
    sdram_init(AT91C_SDRAMC_NC_9 | AT91C_SDRAMC_NR_13 | AT91C_SDRAMC_CAS_2 | AT91C_SDRAMC_NB_4_BANKS | AT91C_SDRAMC_DBW_32_BITS | AT91C_SDRAMC_TWR_2 | AT91C_SDRAMC_TRC_7 | AT91C_SDRAMC_TRP_2 | AT91C_SDRAMC_TRCD_2 | AT91C_SDRAMC_TRAS_5 | AT91C_SDRAMC_TXSR_8,       /* Control Register       */
               (MASTER_CLOCK * 7) / 1000000,    /* Refresh Timer Register */
               AT91C_SDRAMC_MD_SDRAM);  /* SDRAM (no low power)   */
#endif
#endif                          /* CONFIG_SDRAM */

#if	defined(CONFIG_PSRAM)
    psram_hw_init();
#endif                          /* CFG_PSRAM */
}
#endif                          /* CONFIG_HW_INIT */

#ifdef CONFIG_SDRAM
//*----------------------------------------------------------------------------
//* \fn    sdramc_hw_init
//* \brief This function performs SDRAMC HW initialization
//*----------------------------------------------------------------------------*/
void sdramc_hw_init(void)
{
    /*
     * Configure PIOs 
     */
    const struct pio_desc sdramc_pio[] = {
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
     * Configure the SDRAMC PIO controller 
     */
    pio_setup(sdramc_pio);
}
#endif

#ifdef CONFIG_PSRAM
void psram_hw_init(void)
{
    volatile unsigned short tmp;

    unsigned short *addressMax = (unsigned short *)MICRON_8MB_ADDRESS_MAX;

    /*
     * Configure PIOs 
     */
    const struct pio_desc psram_pio[] = {
        {"CRE", AT91C_PIN_PE(16), 0, PIO_DEFAULT, PIO_OUTPUT},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    writel((AT91C_PSRAM_NWE_SETUP |
            AT91C_PSRAM_NCS_WR_SETUP |
            AT91C_PSRAM_NRD_SETUP |
            AT91C_PSRAM_NCS_RD_SETUP), AT91C_BASE_SMC1 + SMC_SETUP0);
    writel((AT91C_PSRAM_NWE_PULSE |
            AT91C_PSRAM_NCS_WR_PULSE |
            AT91C_PSRAM_NRD_PULSE |
            AT91C_PSRAM_NCS_RD_PULSE), AT91C_BASE_SMC1 + SMC_PULSE0);
    writel((AT91C_PSRAM_NWE_CYCLE |
            AT91C_PSRAM_NRD_CYCLE), AT91C_BASE_SMC1 + SMC_CYCLE0);
    writel((AT91C_SMC_READMODE |
            AT91C_SMC_WRITEMODE |
            AT91C_SMC_BAT_BYTE_SELECT |
            AT91C_SMC_PMEN |
            AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS |
            AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES), AT91C_BASE_SMC1 + SMC_CTRL0);

    pio_setup(psram_pio);
    pio_set_value(AT91C_PIN_PE(16), 0); // Data access.

    //Enable page mode
    tmp = readl(addressMax);
    tmp = readl(addressMax);
    writel(MICRON_RCR, addressMax);
    writel(MICRON_PAGE_MODE_ENABLE, addressMax);
}
#endif                          /* CONFIG_PSRAM */

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
        {"RDY_BSY", AT91C_PIN_PA(22), 0, PIO_PULLUP, PIO_INPUT},
        {"NANDCS", AT91C_PIN_PD(15), 0, PIO_PULLUP, PIO_OUTPUT},
        {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
    };

    /*
     * Setup Smart Media, first enable the address range of CS3 in HMATRIX user interface 
     */
    writel(readl(AT91C_BASE_CCFG + CCFG_EBI0CSA) | AT91C_EBI_CS3A_SM,
           AT91C_BASE_CCFG + CCFG_EBI0CSA);

    /*
     * Configure SMC CS3 
     */
    writel((AT91C_SM_NWE_SETUP | AT91C_SM_NCS_WR_SETUP | AT91C_SM_NRD_SETUP |
            AT91C_SM_NCS_RD_SETUP), AT91C_BASE_SMC0 + SMC_SETUP3);
    writel((AT91C_SM_NWE_PULSE | AT91C_SM_NCS_WR_PULSE | AT91C_SM_NRD_PULSE |
            AT91C_SM_NCS_RD_PULSE), AT91C_BASE_SMC0 + SMC_PULSE3);
    writel((AT91C_SM_NWE_CYCLE | AT91C_SM_NRD_CYCLE),
           AT91C_BASE_SMC0 + SMC_CYCLE3);
    writel((AT91C_SMC_READMODE | AT91C_SMC_WRITEMODE |
            AT91C_SMC_NWAITM_NWAIT_DISABLE | AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS |
            AT91C_SM_TDF), AT91C_BASE_SMC0 + SMC_CTRL3);

    /*
     * Configure the PIO controller 
     */
    writel((1 << AT91C_ID_PIOA), PMC_PCER + AT91C_BASE_PMC);
    writel((1 << AT91C_ID_PIOCDE), PMC_PCER + AT91C_BASE_PMC);

    pio_setup(nand_pio);
}

/*------------------------------------------------------------------------------*/
/* \fn    nandflash_cfg_16bits_dbw_init						*/
/* \brief Configure SMC in 16 bits mode						*/
/*------------------------------------------------------------------------------*/
void nandflash_cfg_16bits_dbw_init(void)
{
    writel(readl(AT91C_BASE_SMC0 + SMC_CTRL3) |
           AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS, AT91C_BASE_SMC0 + SMC_CTRL3);
}

/*------------------------------------------------------------------------------*/
/* \fn    nandflash_cfg_8bits_dbw_init						*/
/* \brief Configure SMC in 8 bits mode						*/
/*------------------------------------------------------------------------------*/
void nandflash_cfg_8bits_dbw_init(void)
{
    writel((readl(AT91C_BASE_SMC0 + SMC_CTRL3) & ~(AT91C_SMC_DBW)) |
           AT91C_SMC_DBW_WIDTH_EIGTH_BITS, AT91C_BASE_SMC0 + SMC_CTRL3);
}

#endif                          /* #ifdef CONFIG_NANDFLASH */

#endif
