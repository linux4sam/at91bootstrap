 
/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, HAGER Security

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



#include "ddramc.h"
#include "arch/at91_ddrsdrc.h"


/**
 * This file contains the ddram_chip_config() and ddram_chip_get_ba_offset() functions definitions 
 * for the Winbond WD948D4 LP-DDR1 (4 bank (2 bits) X 4096 rows (12 bits) X 512 columns (9 bits) words of 32 bits) memory chip
 */

//! Define the BA offset in interleaved mode (@see ddram_chip_get_ba_offset() )
static const unsigned int BA_OFFSET_WHEN_INTERLEAVED = 11;
//! Define the BA offset in sequential mode
static const unsigned int BA_OFFSET_WHEN_SEQUENTIAL = 23;

/**
 * Initialze the DRAM ctrlr configuration strucure for this memory chip
 */
void ddram_chip_config(struct ddramc_register *ddramc_config)
{
  ddramc_config->mdr = (AT91C_DDRC2_DBW_32_BITS | AT91C_DDRC2_MD_LP_DDR_SDRAM);
  ddramc_config->cr = (AT91C_DDRC2_NC_DDR9_SDR8 | AT91C_DDRC2_NR_12
      | AT91C_DDRC2_CAS_3
      | AT91C_DDRC2_ENRDM_ENABLE /* Phase error correction is enabled */
      | AT91C_DDRC2_NB_BANKS_4 /* Only 4 banks*/
      | AT91C_DDRC2_DECOD_INTERLEAVED /* Interleaved decoding */
      | AT91C_DDRC2_UNAL_SUPPORTED); /* Unaligned access is supported */

#if defined(CONFIG_BUS_SPEED_133MHZ)
#error BeeAve board bus speed is  166MHz !
#elif defined(CONFIG_BUS_SPEED_166MHZ)
 /*
  * 
  * The LPDDR1-SDRAM device requires a refresh of all rows every 64ms.
  * ((64ms) / 4096) * 166MHz = 2594 i.e. 0xA22 (max value)
 */
  ddramc_config->rtr = 0xA12; /* less than maximum */

  /* One clock cycle @ 166 MHz = 6.0 ns */
  ddramc_config->t0pr = (AT91C_DDRC2_TRAS_8 /* 42ns =>  8 * 6 = 48 ns */
      | AT91C_DDRC2_TRCD_4    /* 18ns => 4 * 6 = 24 ns */
      | AT91C_DDRC2_TWR_3   /* 15ns => 3 * 6 = 18 ns */
      | AT91C_DDRC2_TRC_11    /* 62ns => 11 * 6 = 66 ns */
      | AT91C_DDRC2_TRP_4   /* 18ns => 4 * 6 = 24 ns */
      | AT91C_DDRC2_TRRD_3    /* 12ns => 3 * 6 = 18 ns */
      | AT91C_DDRC2_TWTR_2    /* 2 clock cycle*/
      | AT91C_DDRC2_TMRD_2);    /* 2 clock cycles at least (called tSSR)*/

  ddramc_config->t1pr = (AT91C_DDRC2_TXP_1  /* 1 * 6 = 6ns, 1 clock cycle */
      | AT91C_DDRC2_TXSR(20)    /* LP-DDR1 : use tXSR value  20 * 6 = 120 ns*/
      | AT91C_DDRC2_TRFC_12);   /* 72ns =>  12 * 6 = 72 ns */
      
   //Low power feature, NONE for the moment.
    ddramc_config->lpr = AT91C_MPDDRC_LPR_LPCB_NOLOWPOWER | AT91C_MPDDRC_LPR_PASR(0) | AT91C_MPDDRC_LPR_DS(0);
    //!@note Lowpower mode must be tested once the application is operationnal : Memory will be less used than when set under tests.
//ddramc_config->lpr = AT91C_MPDDRC_LPR_LPCB_SELFREFRESH | AT91C_MPDDRC_LPR_PASR(0) | AT91C_MPDDRC_LPR_DS(3);
      
#else
#error "No bus clock provided!"
#endif
}
//**********************************************
/**
 * This function returns an address value with BANK[1:0]= 0x2 accroding the given base address and the actual chip geometry.
 * The actual value depends on the chip geometry AND the access type (interleaved or sequential) as set above cr (configuration register)
 * See the ram chip data sheet for geometry and SAMA5D3x data sheet chap. 29.7. HERE see data sheet Table 29-16, but for 256 columns !
 * Addr : XXXX X:RRR RRRR RRRR R:BB:C CCCC CC:MM (28 bit)
 * @return The special address value with BANK[1:0] = 0x2
 */
unsigned int ddram_chip_get_ba_offset (struct ddramc_register const* ddramc_config)
{
  unsigned int ba_offset = ddramc_config->cr & AT91C_DDRC2_DECOD_INTERLEAVED ? BA_OFFSET_WHEN_INTERLEAVED : BA_OFFSET_WHEN_SEQUENTIAL;
  return ba_offset;
}
//**********************************************
