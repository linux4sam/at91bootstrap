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
 * File Name           : sdramc.c
 * Object              :
 * Creation            : NLe Jul 11th 2006
 *-----------------------------------------------------------------------------
 */
#include "sdramc.h"
#include "part.h"
#include "main.h"

#ifdef CONFIG_SDRAM

/* Write SDRAMC register */
static inline void write_sdramc(unsigned int offset, const unsigned int value)
{
    writel(value, offset + AT91C_BASE_SDRAMC);
}

/* Read SDRAMC registers */
static inline unsigned int read_sdramc(unsigned int offset)
{
    return readl(offset + AT91C_BASE_SDRAMC);
}

//*----------------------------------------------------------------------------
//* \fn    sdram_init
//* \brief Initialize the SDRAM Controller
//*----------------------------------------------------------------------------
int sdram_init(unsigned int sdramc_cr, unsigned int sdramc_tr,
               unsigned char low_power)
{
    volatile unsigned int i;

    /*
     * Performs the hardware initialization 
     */
    sdramc_hw_init();

    /*
     * CFG Control Register 
     */
    write_sdramc(SDRAMC_CR, sdramc_cr);

    /*
     * Set MDR Register 
     */
    write_sdramc(SDRAMC_MDR, (low_power & 0x01));

    for (i = 0; i < 1000; i++) ;

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_NOP_CMD); // Set NOP 
    writel(0x00000000, AT91C_SDRAM);    // Perform NOP

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_PRCGALL_CMD);     // Set PRCHG AL
    writel(0x00000000, AT91C_SDRAM);    // Perform PRCHG

    for (i = 0; i < 10000; i++) ;

#if	0
    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 1st CBR
    writel(0x00000001, AT91C_SDRAM + 4);        // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 2 CBR
    writel(0x00000002, AT91C_SDRAM + 8);        // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 3 CBR
    writel(0x00000003, AT91C_SDRAM + 0xc);      // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 4 CBR
    writel(0x00000004, AT91C_SDRAM + 0x10);     // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 5 CBR
    writel(0x00000005, AT91C_SDRAM + 0x14);     // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 6 CBR
    writel(0x00000006, AT91C_SDRAM + 0x18);     // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 7 CBR
    writel(0x00000007, AT91C_SDRAM + 0x1C);     // Perform CBR

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);        // Set 8 CBR
    writel(0x00000008, AT91C_SDRAM + 0x20);     // Perform CBR
#else
    for (i = 0; i < 8; i++) {
        write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_RFSH_CMD);    // 8 x CBR
        writel(0x00000001 + i, AT91C_SDRAM + 4 + 4 * i);        // Perform CBR
    }
#endif

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_LMR_CMD); // Set LMR operation
    writel(0xcafedede, AT91C_SDRAM + 0x24);     // Perform LMR burst=1, lat=2

    write_sdramc(SDRAMC_TR, sdramc_tr); // Set Refresh Timer

    write_sdramc(SDRAMC_MR, AT91C_SDRAMC_MODE_NORMAL_CMD);      // Set Normal mode
    writel(0x00000000, AT91C_SDRAM);    // Perform Normal mode

    return 0;
}

#endif                          /* CONFIG_SDRAM */
