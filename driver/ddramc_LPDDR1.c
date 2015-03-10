/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2007, Stelian Pop <stelian.pop@leadtechdesign.com>
 * Copyright (c) 2007 Lead Tech Design <www.leadtechdesign.com>
 * Copyright (c) 2014 HAGER Security <www.hager.fr>
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
 */
#include "hardware.h"
#include "arch/at91_ddrsdrc.h"
#include "debug.h"
#include "ddramc.h"
#include "timer.h"

//*****************************************************************
/* write DDRC register */
static void write_ddramc(unsigned int address,
			unsigned int offset,
			const unsigned int value)
{
	writel(value, (address + offset));
}
//*****************************************************************
/* read DDRC registers */
static unsigned int read_ddramc(unsigned int address, unsigned int offset)
{
	return readl(address + offset);
}

//*****************************************************************
#if defined (CONFIG_LPDDR1)
int ddram_initialize(unsigned int base_address,
			unsigned int ram_address,
      unsigned int bank_offset,
			struct ddramc_register *ddramc_config)
{

  unsigned int auto_refresh_loop = 0;
	/*
	 * Step 1: Program the memory device type into the Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/* 
	 * Step 2: Program the feature of LPDDR1-SDRAM device into 
	 * the Timing Register, and into the Configuration Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);
	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);

 /*
	* Step 3: Program the Low Power Register
	*/
  write_ddramc(base_address, HDDRSDRC2_LPR, ddramc_config->lpr);
  /*
   * Step 4 : note about the 200us of delay before any command.
   */
  udelay(200);
	/*
	 * Step 5: An NOP command is issued to the LPDDR1-SDRAM => activate the 
   * device's clocks
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	/* Now, clocks which drive the LPDDR1-SDRAM device are enabled */

	/* A minimum pause wait 200 us is provided to precede any signal toggle.
	(6 core cycles per iteration, core is at 396MHz: min 13340 loops) */
	udelay(200);

	/*
	 * Step 6:  An NOP command is issued to the LPDDR1-SDRAM => IO calibration request
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;
  /*Delay before next*/
	udelay(200);

	/*
	 * Step 7: An All Bank Precharge command is issued to the LPDDR1-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*((unsigned volatile int *)ram_address) = 0;
  /*Delay before next*/
	udelay(200);

	/*
	 * Step 8: TWO Auto Refresh command is issued to the LPDDR1-SDRAM.
	 */
  for (auto_refresh_loop = 0 ; auto_refresh_loop < 2 ; ++auto_refresh_loop)
  {
    write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
    //Two accesses to ack the command.
    *((unsigned volatile int *)ram_address) = 0;
    *((unsigned volatile int *)ram_address) = 0;
    /*Delay before next*/
    udelay(200);
  }

	/*
	 * Step 9: An Extended Mode Register set(EMRS) cycle is issued.
   * Activation with write to address with BA[1:0]=b10 BA position depends of the chip geometry and use.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x2 << bank_offset))) = 0;
   /* delay before next command*/
   udelay(200);
   
  /*
  * Step 10: Mode Register Set cycle : program DDR1 parameters.
  */
  write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
  *((unsigned volatile int *)(ram_address)) = 0;
   /* delay before next command*/
   udelay(200);
   
  /*
  * Step 11: Enter NORMAL mode
  */
   write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
  *((unsigned volatile int *)(ram_address)) = 0;
   /* delay before next command*/
   udelay(200);
	
	/*
	 * Step 12: Perform a write access to any LP-DDR1 address, not Base for this time.
	 */
	*((unsigned volatile int *)(ram_address + 4)) = 0;

	/*
	 * Step 13: Write the refresh rate into the count field in the Refresh Timer register.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	return 0;
}
#else
#error WRONG Memory type, here for LP-DDR1.
#endif
