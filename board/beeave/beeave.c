/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

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
#include "onewire_info.h"

#include "arch/at91_pmc.h"
#include "arch/at91_rstc.h"
#include "arch/sama5_smc.h"
#include "arch/at91_pio.h"
#include "arch/at91_ddrsdrc.h"
#include "beeave.h"

#if defined(CONFIG_WITH_MMU)
#include "CP15.h"
#include "mmu.h"
#endif

#ifdef CONFIG_USER_HW_INIT
extern void hw_init_hook(void);
#endif


//*************** MEMORY functions initialization prototypes ******

#ifdef CONFIG_LPDDR1
  /* Initialize MPDDR Controller for LPDDR1*/
void  ddramc_init(void);
#elif !defined (CONFIG_ONLY_INTERNAL_RAM)
#error BeeAve module only support LP-DDR1 RAM.
#endif

static void
at91_dbgu_hw_init(void)
{
  /* Configure DBGU pin */
  const struct pio_desc dbgu_pins[] =
    {
      { "RXD", AT91C_PIN_PB(30), 0, PIO_DEFAULT, PIO_PERIPH_A },
      { "TXD", AT91C_PIN_PB(31), 0, PIO_DEFAULT, PIO_PERIPH_A },
      { (char *) 0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A }, };

  /*  Configure the dbgu pins */
	pmc_enable_periph_clock(AT91C_ID_PIOB);
  pio_configure(dbgu_pins);

  /* Enable clock */
	pmc_enable_periph_clock(AT91C_ID_DBGU);
}

static void
initialize_dbgu(void)
{
  at91_dbgu_hw_init();
	usart_init(BAUDRATE(MASTER_CLOCK, 115200));
}


#ifdef CONFIG_HW_INIT
void
hw_init(void)
{
#if defined(CONFIG_WITH_MMU)
  struct ExtMemDescriptor memDescriptor =
    {
      CONFIG_EBI_0_SIZE,
      CONFIG_EBI_1_SIZE,
      CONFIG_EBI_2_SIZE,
      CONFIG_EBI_3_SIZE,
      CONFIG_RAM_SIZE};
#endif

  /* Disable watchdog */
  at91_disable_wdt();

	/*
	 * At this stage the main oscillator
	 * is supposed to be enabled PCK = MCK = MOSC
	 */

  /* Configure PLLA = MOSC * (PLL_MULA + 1) / PLL_DIVA */
  pmc_cfg_plla(PLLA_SETTINGS, PLL_LOCK_TIMEOUT);

  /* Initialize PLLA charge pump */
  pmc_init_pll(AT91C_PMC_IPLLA_3);

	/* Switch PCK/MCK on Main clock output */
  pmc_cfg_mck(BOARD_PRESCALER_MAIN_CLOCK, PLL_LOCK_TIMEOUT);

	/* Switch PCK/MCK on PLLA output */
  pmc_cfg_mck(BOARD_PRESCALER_PLLA, PLL_LOCK_TIMEOUT);

  
  /* Init timer */
  timer_init();

#ifdef CONFIG_SCLK
  slowclk_enable_osc32();
#endif

  /* initialize the dbgu */
  initialize_dbgu();
  usart_puts("... BOOTING ...\n");

#ifdef CONFIG_LPDDR1
  /* Initialize MPDDR Controller for LPDDR1*/
  ddramc_init();
#endif


#ifdef CONFIG_USER_HW_INIT
  hw_init_hook();
#endif

#if defined(CONFIG_WITH_MMU)
#warning MMU activated
  MMU_TB_Initialize(&memDescriptor, &MEMORY_TRANSLATION_TABLE_BASE);
  MMU_Set(&MEMORY_TRANSLATION_TABLE_BASE);
  CP15_EnableMMU();
#if defined(CONFIG_WITH_CACHE)
#warning CACHE activated
  CP15_EnableDcache();
  CP15_EnableIcache();
#endif /*CONFIG_CACHE_ENABLED*/
#endif

#if defined(CONFIG_WITH_MMU)
//Check MMU & Cache status
  if (CP15_IsMMUEnabled())
    usart_puts("MMU ENabled\n");
  else
    usart_puts("MMU DISabled\n");

  if (CP15_IsDcacheEnabled())
    usart_puts("D Cache ENabled\n");
  else
    usart_puts("D Cache DISabled\n");

  if (CP15_IsIcacheEnabled())
    usart_puts("I Cache ENabled\n");
  else
    usart_puts("I Cache DISabled\n");
#endif

}
#endif /* #ifdef CONFIG_HW_INIT */

#ifdef CONFIG_DATAFLASH
void
at91_spi0_hw_init(void)
{
  /* Configure PIN for SPI0 */
  const struct pio_desc spi0_pins[] =
    {
      { "MISO", AT91C_PIN_PD(10), 0, PIO_DEFAULT, PIO_PERIPH_A },
      { "MOSI", AT91C_PIN_PD(11), 0, PIO_DEFAULT, PIO_PERIPH_A },
      { "SPCK", AT91C_PIN_PD(12), 0, PIO_DEFAULT, PIO_PERIPH_A },
      { "NPCS", CONFIG_SYS_SPI_PCS, 1, PIO_DEFAULT, PIO_OUTPUT },
      { (char *) 0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A }, };

  /* Configure the PIO controller */
	pmc_enable_periph_clock(AT91C_ID_PIOD);
  pio_configure(spi0_pins);

  /* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SPI0);
}
#endif /* #ifdef CONFIG_DATAFLASH */

#ifdef CONFIG_SDCARD
static void sdcard_set_of_name_board(char *of_name)
  {
    /* CPU TYPE*/
    switch (get_cm_sn())
      {
        case BOARD_ID_SAMA5D31_CM:
        strcpy(of_name, "sama5d31ek");
        break;

        case BOARD_ID_SAMA5D33_CM:
        strcpy(of_name, "sama5d33ek");
        break;

        case BOARD_ID_SAMA5D34_CM:
        strcpy(of_name, "sama5d34ek");
        break;

        case BOARD_ID_SAMA5D35_CM:
        strcpy(of_name, "sama5d35ek");
        break;

        case BOARD_ID_SAMA5D36_CM:
        strcpy(of_name, "sama5d36ek");
        break;

        default:
		dbg_info("WARNING: Not correct CPU board ID\n");
        break;
      }

    if (get_dm_sn() == BOARD_ID_PDA_DM)
    strcat(of_name, "_pda");

    strcat(of_name, ".dtb");
  }

void at91_mci0_hw_init(void)
  {
    const struct pio_desc mci_pins[] =
      {
          { "MCCK", AT91C_PIN_PD(9), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCCDA", AT91C_PIN_PD(0), 0, PIO_DEFAULT, PIO_PERIPH_A},

          { "MCDA0", AT91C_PIN_PD(1), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA1", AT91C_PIN_PD(2), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA2", AT91C_PIN_PD(3), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA3", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA4", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA5", AT91C_PIN_PD(6), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA6", AT91C_PIN_PD(7), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { "MCDA7", AT91C_PIN_PD(8), 0, PIO_DEFAULT, PIO_PERIPH_A},
          { (char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
      };

    /* Configure the PIO controller */
	pmc_enable_periph_clock(AT91C_ID_HSMCI0);
    pio_configure(mci_pins);

    /* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_HSMCI0);

    /* Set of name function pointer */
    sdcard_set_of_name = &sdcard_set_of_name_board;
  }
#endif /* #ifdef CONFIG_SDCARD */

#ifdef CONFIG_NANDFLASH
void nandflash_hw_init(void)
  {
    /* Configure nand pins */
    const struct pio_desc nand_pins[] =
      {
          { "NANDALE", AT91C_PIN_PE(21), 0, PIO_PULLUP, PIO_PERIPH_A},
          { "NANDCLE", AT91C_PIN_PE(22), 0, PIO_PULLUP, PIO_PERIPH_A},
          { (char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
      };

    /* Configure the nand controller pins*/
	pmc_enable_periph_clock(AT91C_ID_PIOE);
    pio_configure(nand_pins);

    /* Enable the clock */
	pmc_enable_periph_clock(AT91C_ID_SMC);

    /* Configure SMC CS3 for NAND/SmartMedia */
    writel(AT91C_SMC_SETUP_NWE(1)
        | AT91C_SMC_SETUP_NCS_WR(1)
        | AT91C_SMC_SETUP_NRD(2)
        | AT91C_SMC_SETUP_NCS_RD(1),
        (ATMEL_BASE_SMC + SMC_SETUP3));

    writel(AT91C_SMC_PULSE_NWE(5)
        | AT91C_SMC_PULSE_NCS_WR(7)
        | AT91C_SMC_PULSE_NRD(5)
        | AT91C_SMC_PULSE_NCS_RD(7),
        (ATMEL_BASE_SMC + SMC_PULSE3));

    writel(AT91C_SMC_CYCLE_NWE(8)
        | AT91C_SMC_CYCLE_NRD(9),
        (ATMEL_BASE_SMC + SMC_CYCLE3));

    writel(AT91C_SMC_TIMINGS_TCLR(3)
        | AT91C_SMC_TIMINGS_TADL(10)
        | AT91C_SMC_TIMINGS_TAR(3)
        | AT91C_SMC_TIMINGS_TRR(4)
        | AT91C_SMC_TIMINGS_TWB(5)
        | AT91C_SMC_TIMINGS_RBNSEL(3)
        | AT91C_SMC_TIMINGS_NFSEL,
        (ATMEL_BASE_SMC + SMC_TIMINGS3));

    writel(AT91C_SMC_MODE_READMODE_NRD_CTRL
        | AT91C_SMC_MODE_WRITEMODE_NWE_CTRL
        | AT91C_SMC_MODE_EXNWMODE_DISABLED
        | AT91C_SMC_MODE_DBW_8
        | AT91C_SMC_MODE_TDF_CYCLES(1),
        (ATMEL_BASE_SMC + SMC_MODE3));
  }

void nandflash_config_buswidth(unsigned char buswidth)
  {
    unsigned int mode;

    mode = readl(ATMEL_BASE_SMC + SMC_MODE3);

    mode &= ~AT91C_SMC_MODE_DBW;
    if (buswidth == 0) /* 8 bits bus */
    mode |= AT91C_SMC_MODE_DBW_8;
    else
    mode |= AT91C_SMC_MODE_DBW_16;

    writel(mode, (ATMEL_BASE_SMC + SMC_MODE3));
  }
#endif /* #ifdef CONFIG_NANDFLASH */

