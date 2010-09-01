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
 * File Name           : sdramc.c
 * Object              :
 * Creation            :
 *-----------------------------------------------------------------------------
 */
#include "../include/sddrc.h"
#include "../include/part.h"
#include "../include/main.h"

#ifdef CONFIG_SDDRC

/* Write SDDRC register */
static inline void write_sddrc(unsigned int offset, const unsigned int value)
{
    writel(value, offset + AT91C_BASE_SDDRC);
}

/* Read SDDRC registers */
static inline unsigned int read_sddrc(unsigned int offset)
{
    return readl(offset + AT91C_BASE_SDDRC);
}

//*----------------------------------------------------------------------------
//* \fn    sdram_init
//* \brief Initialize the SDDRC Controller
//*----------------------------------------------------------------------------
int sddrc_init(unsigned int sdramc_cr, unsigned int sdramc_tr)
{
    volatile unsigned int i;

    /*
     * Performs the hardware initialization 
     */
    sddrc_hw_init();

    /*
     * 32 bit mode, SDRAM type 
     */
    write_sddrc(SDDRC_MDR, 0x00000000);

    /*
     * CFG Control Register 
     */
    write_sddrc(SDDRC_CR, sdramc_cr);

    /*
     * inhibit low power 
     */
    write_sddrc(SDDRC_LPR, 0x00000000);

    /*
     * sleep 
     */
    for (i = 0; i < 1000; i++) ;

    /*
     * nop 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_NOP_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * nop 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_NOP_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * nop 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_NOP_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * precharge all banks 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_PRCGALL_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * sleep 
     */
    for (i = 0; i < 1000; i++) ;

    /*
     * auto refresh 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_RFSH_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * sleep 
     */
    for (i = 0; i < 1000; i++) ;

    /*
     * auto refresh 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_RFSH_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * sleep 
     */
    for (i = 0; i < 1000; i++) ;

    /*
     * lmr 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_LMR_CMD);
    writel(0x5a5a5b5b, AT91C_SDRAM + 20);

    /*
     * auto refresh 
     */
    write_sddrc(SDDRC_MR, AT91C_MODE_NORMAL_CMD);
    writel(0x00000000, AT91C_SDRAM);

    /*
     * refresh timer 
     */
    write_sddrc(SDDRC_RTR, sdramc_tr);

    /*
     * disable high speed 
     */
    write_sddrc(SDDRC_HS, 0x00000000);

    /*
     * sleep 
     */
    for (i = 0; i < 1000; i++) ;

    return 0;
}

#endif                          /* CFG_SDDRC */
