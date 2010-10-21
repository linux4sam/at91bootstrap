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

//*----------------------------------------------------------------------------
//* \fn    sdram_init
//* \brief Initialize the SDDRC Controller
//*----------------------------------------------------------------------------
int ddram_init(unsigned int ddram_controller_address,
               unsigned int ddram_address, struct SDdramConfig *ddram_config)
{
    unsigned int cr = 0;

    // Step 1: Program the memory device type
    // Configure the DDR controller
    write_ddramc(ddram_controller_address, HDDRSDRC2_MDR,
                 ddram_config->ddramc_mdr);

    // Program the DDR Controller
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 ddram_config->ddramc_cr);

    // assume timings for 7.5ns min clock period
    write_ddramc(ddram_controller_address, HDDRSDRC2_T0PR,
                 ddram_config->ddramc_t0pr);

    // pSDDRC->HDDRSDRC2_T1PR 
    write_ddramc(ddram_controller_address, HDDRSDRC2_T1PR,
                 ddram_config->ddramc_t1pr);

    // pSDDRC->HDDRSDRC2_T2PR 
    write_ddramc(ddram_controller_address, HDDRSDRC2_T2PR,
                 ddram_config->ddramc_t2pr);

    // Initialization Step 3: NOP command -> allow to enable clk
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_NOP_CMD);
    *((unsigned volatile int *)ddram_address) = 0;

    // Initialization Step 3 (must wait 200 us) (6 core cycles per iteration, core is at 396MHz: min 13200 loops)
    Wait(13300);

    // Step 4:  An NOP command is issued to the DDR2-SDRAM 
    // NOP command -> allow to enable cke
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_NOP_CMD);
    *((unsigned volatile int *)ddram_address) = 0;

    // wait 400 ns min
    Wait(100);

    // Initialization Step 5: Set All Bank Precharge
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_PRCGALL_CMD);
    *((unsigned volatile int *)ddram_address) = 0;

    // wait 400 ns min
    Wait(100);

    // Initialization Step 6: Set EMR operation (EMRS2)
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + 0x2000000)) = 0;

    // wait 2 cycles min
    Wait(100);

    // Initialization Step 7: Set EMR operation (EMRS3)
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + 0x3000000)) = 0;

    // wait 2 cycles min
    Wait(100);

    // Initialization Step 8: Set EMR operation (EMRS1)
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *((unsigned int *)(ddram_address + 0x1000000)) = 0;

    // wait 200 cycles min
    Wait(10000);

    // Initialization Step 9: enable DLL reset
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr | AT91C_DDRC2_DLL_RESET_ENABLED);

    // Initialization Step 10: reset DLL
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait 2 cycles min
    Wait(100);

    // Initialization Step 11: Set All Bank Precharge
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_PRCGALL_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait 400 ns min
    Wait(100);

    // Initialization Step 12: Two auto-refresh (CBR) cycles are provided. Program the auto refresh command (CBR) into the Mode Register.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_RFSH_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait 10 cycles min
    Wait(100);

    // Set 2nd CBR
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_RFSH_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // wait 10 cycles min
    Wait(100);

    // Initialization Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset).
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr & (~AT91C_DDRC2_DLL_RESET_ENABLED));

    // Initialization Step 14: A Mode Register set (MRS) cycle is issued to program the parameters of the DDR2-SDRAM devices.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_LMR_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // Step 15: Program OCD field into the Configuration Register to high (OCD calibration default).
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr | AT91C_DDRC2_OCD_DEFAULT);

    // Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *(((unsigned int *)(ddram_address + 0x1000000))) = 0;

    // wait 2 cycles min
    Wait(100);

    // Step 17: Program OCD field into the Configuration Register to low (OCD calibration mode exit).
    cr = read_ddramc(ddram_controller_address, HDDRSDRC2_CR);
    write_ddramc(ddram_controller_address, HDDRSDRC2_CR,
                 cr & (~AT91C_DDRC2_OCD_EXIT));

    // Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_EXT_LMR_CMD);
    *(((unsigned int *)(ddram_address + 0x1000000))) = 0;

    // wait 2 cycles min
    Wait(100);

    // Step 19,20: A mode Normal command is provided. Program the Normal mode into Mode Register.
    write_ddramc(ddram_controller_address, HDDRSDRC2_MR,
                 AT91C_DDRC2_MODE_NORMAL_CMD);
    *(((unsigned volatile int *)ddram_address)) = 0;

    // Step 21: Write the refresh rate into the count field in the Refresh Timer register. The DDR2-SDRAM device requires a
    // refresh every 15.625 ¦Is or 7.81 ¦Ìs. With a 100MHz frequency, the refresh timer count register must to be set with
    // (15.625 /100 MHz) = 1562 i.e. 0x061A or (7.81 /100MHz) = 781 i.e. 0x030d.

    // Set Refresh timer
    write_ddramc(ddram_controller_address, HDDRSDRC2_RTR,
                 ddram_config->ddramc_rtr);

    // OK now we are ready to work on the DDRSDR

    // wait for end of calibration
    Wait(500);

    return 0;
}

#endif                          /* CONFIG_DDR2 */
