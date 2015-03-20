/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, HAGER Security.

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
 */

#include "common.h"
#include "hardware.h"
#include "pmc.h"
#include "usart.h"
#include "debug.h"
#include "ddramc.h"
#include "spi.h"
#include "gpio.h"
#include "slowclk.h"
#include "timer.h"
#include "watchdog.h"
#include "string.h"

#include "arch/at91_pmc.h"
#include "arch/at91_rstc.h"
#include "arch/sama5_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"

//*************** MEMORY CHIP functions initialization prototypes  ******
//  (implemented on dedicated memory support file)
extern void ddram_chip_config(struct ddramc_register *ddramc_config);
extern unsigned int ddram_chip_get_ba_offset (struct ddramc_register const* ddramc_config);

//*****************************************************************
//! This function aims at LPDDR1 initialization.
void ddramc_init(void)
{
  struct ddramc_register ddramc_reg;
  unsigned int reg;

  ddram_chip_config(&ddramc_reg);

  /* enable DDR clock */
  pmc_enable_periph_clock(AT91C_ID_MPDDRC);
  pmc_enable_system_clock(AT91C_PMC_DDR);

#if 0
 /* NOT USED in LP-DDR1 */
  /* Same as for the DDR2 */
  reg = AT91C_MPDDRC_S0OFF_1 | AT91C_MPDDRC_S2OFF_1 | AT91C_MPDDRC_S3OFF_1;
  writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_DLL_SOR));

  /* MPDDRC DLL Master Offset Register (keep the same as for the DDR2) ! 4 fields writtent but only 3 in the register !*/
  /* write master + clk90 offset */
  reg = AT91C_MPDDRC_MOFF_7 | AT91C_MPDDRC_CLK90OFF_31
      | AT91C_MPDDRC_SELOFF_ENABLED | AT91C_MPDDRC_KEY;
  writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_DLL_MOR));
#endif
  /* MPDDRC I/O Calibration Register (RZQ for 50 Ohms, TZQIO keep the value)*/
  /* LP-DDR1 RZQ = 50 Ohm */
  /* TZQIO = 4 */
  reg = AT91C_MPDDRC_RDIV_DDR2_RZQ_50 | AT91C_MPDDRC_TZQIO_4;
  writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR));

  /* LP-DDRAM1 Controller initialize */
  ddram_initialize(AT91C_BASE_MPDDRC, AT91C_BASE_DDRCS, ddram_chip_get_ba_offset(&ddramc_reg), &ddramc_reg);
}
