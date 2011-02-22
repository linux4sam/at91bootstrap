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
#include "dbgu.h"
#include "debug.h"
#include "../include/part.h"
#include "../include/main.h"
#include "../include/ddramc.h"

#ifdef CONFIG_DDR2

/* Write DDRC register */
static void write_ddramc(unsigned int address, unsigned int offset,
                         const unsigned int value)
{
    writel(value, (address + offset));
}

/* Read DDRC registers */
static unsigned int read_ddramc(unsigned int address, unsigned int offset)
{
    return readl((address + offset));
}

static BOOL ddram_decod_seq(unsigned int ddramc_cr)
{
#ifdef AT91SAM9X5
    if (ddramc_cr & AT91C_DDRC2_DECOD_INTERLEAVED)
	    return FALSE;
#endif
    return TRUE;
}

//*----------------------------------------------------------------------------
//* \fn    sdram_init
//* \brief Initialize the SDDRC Controller
//*----------------------------------------------------------------------------
int ddram_init(unsigned int ddram_controller_address,
               unsigned int ddram_address, struct SDdramConfig *ddram_config)
{
    unsigned int ba_offset;
    unsigned int cr = 0;

    /* compute BA[] offset according to CR configuration */
    ba_offset = (ddram_config->ddramc_cr & AT91C_DDRC2_NC) + 9;          // number of column bits for DDR
    if (ddram_decod_seq(ddram_config->ddramc_cr))
        ba_offset += ((ddram_config->ddramc_cr & AT91C_DDRC2_NR) >> 2) + 11; // number of row bits
    ba_offset += (ddram_config->ddramc_mdr & AT91C_DDRC2_DBW) ? 1 : 2;   // bus width

    dbg_log(3, " ba_offset = %x ... ", ba_offset);

    // Step 1: Program the memory device type
    write_ddramc(ddram_controller_address, HDDRSDRC2_MDR,
                 ddram_config->ddramc_mdr);

    // Step 2: Program the DDR features and timings
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 ddram_config->ddramc_cr);

    // assume timings for 7.5 ns min clock period
    write_ddramc(ddram_controller_address, HDDRSDRC2_T0PR,
                 ddram_config->ddramc_t0pr);

    write_ddramc(ddram_controller_address, HDDRSDRC2_T1PR,
                 ddram_config->ddramc_t1pr);

    write_ddramc(ddram_controller_address, HDDRSDRC2_T2PR,
                 ddram_config->ddramc_t2pr);

    // Step 3: NOP command -> allow to enable clk
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_NOP_CMD);
    *((unsigned volatile int *)ddram_address) = 0;

    // must wait 200 us (6 core cycles per iteration, core is at 396MHz: min 13340 loops)
    Wait(13340);

    // Step 4:  An NOP command is issued to the DDR2-SDRAM
    // NOP command -> allow to enable cke
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_NOP_CMD);
    *((unsigned volatile int *)ddram_address) = 0;

    // wait 400 ns min
    Wait(27);

    // Step 5: Set All Bank Precharge
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_PRCGALL_CMD);
    *((unsigned volatile int *)ddram_address) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 6: Set EMR operation (EMRS2)
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    /* Perform a write access to DDR address so that BA[1] is set to 1 and BA[0] is set to 0. */
    *((unsigned int *)(ddram_address + (0x2 << ba_offset))) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 7: Set EMR operation (EMRS3)
    /* Perform a write access to DDR address so that BA[1] is set to 1 and BA[0] is set to 1. */
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + (0x3 << ba_offset))) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 8: Set EMR operation (EMRS1)
    /* Perform a write access to DDR address so that BA[1] is set to 0 and BA[0] is set to 1. */
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + (0x1 << ba_offset))) = 0;

    // wait 200 cycles min (of tCK) = 1500 ns min
    Wait(100);

    // Step 9: enable DLL reset
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr | AT91C_DDRC2_DLL_RESET_ENABLED);

    // Step 10: reset DLL
    /* Perform a write access to DDR address so that BA[1] is set to 0 and BA[0] is set to 0. */
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_LMR_CMD);
    *((unsigned int *)(ddram_address + (0x0 << ba_offset))) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 11: Set All Bank Precharge
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_PRCGALL_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait 400 ns min (not needed on certain DDR2 devices)
    Wait(27);

    // Step 12: Two auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into the Mode Register.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_RFSH_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait TRFC cycles min (135 ns min) extended to 400 ns
    Wait(27);

    // Set 2nd CBR
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_RFSH_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait TRFC cycles min (135 ns min) extended to 400 ns
    Wait(27);

    // Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset).
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr & (~AT91C_DDRC2_DLL_RESET_ENABLED));

    // Step 14: A Mode Register set (MRS) cycle is issued to program the parameters of the DDR2-SDRAM devices.
    /* Perform a write access to DDR address so that BA[1] is set to 0 and BA[0] is set to 0. */
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_LMR_CMD);
    *((unsigned int *)(ddram_address + (0x0 << ba_offset))) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 15: Program OCD field into the Configuration Register to high (OCD calibration default).
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr | AT91C_DDRC2_OCD_DEFAULT);

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value.
    /* Perform a write access to DDR address so that BA[1] is set to 0 and BA[0] is set to 1. */
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + (0x1 << ba_offset))) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 17: Program OCD field into the Configuration Register to low (OCD calibration mode exit).
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr & (~AT91C_DDRC2_OCD_DEFAULT));

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.
    /* Perform a write access to DDR address so that BA[1] is set to 0 and BA[0] is set to 1. */
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + (0x1 << ba_offset))) = 0;

    // wait 2 cycles min (of tCK) = 15 ns min
    Wait(2);

    // Step 19: A mode Normal command is provided. Program the Normal mode into Mode Register.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_NORMAL_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // Step 20: Yes it is needed.
    /* Perform a write access to any DDR address */
    *(((unsigned volatile int *)ddram_address)) = 0;

    // Step 21: Write the refresh rate into the count field in the Refresh Timer register.
    // Set Refresh timer
    write_ddramc(ddram_controller_address, HDDRSDRC2_RTR,
                 ddram_config->ddramc_rtr);

    // OK now we are ready to work on the DDRSDR

    // wait for end of calibration
    Wait(500);

    return 0;
}

#endif                          /* CONFIG_DDR2 */
