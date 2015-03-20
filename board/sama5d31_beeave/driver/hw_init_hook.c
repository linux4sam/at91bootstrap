/* ----------------------------------------------------------------------------
 *         BEEAVE module support
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
#include "sama5d31_beeave.h"

#if defined(CONFIG_BEEAVE_WITH_DEBUG_LEDS)
//! This function will initialize the DEBUG LEDS of the BeeAve module : set them GREEN:RED:GREEN to see Bootstrap running.
void debug_leds_init(void)
{
#ifdef CONFIG_BEEAVE_DEBUG_LEDS_ON
  const struct pio_desc debug_led_pio[] =
    {
      { "GREEN_LED_1", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_OUTPUT },
      { "RED_LED_1", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_INPUT },
      { "GREEN_LED_2", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_OUTPUT },
      { "RED_LED_2", AT91C_PIN_PD(22), 0, PIO_DEFAULT, PIO_OUTPUT },
      { "GREEN_LED_3", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_OUTPUT },
      { "RED_LED_3", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_INPUT },
      PIO_DESCRIPTION_END };
#endif /*CONFIG_BEEAVE_DEBUG_LEDS_ON*/

#ifdef CONFIG_BEEAVE_DEBUG_LEDS_OFF
#warning DEBUG LED OFF.
const struct pio_desc debug_led_pio[] =
    {
      { "GREEN_LED_1", AT91C_PIN_PD(17), 0, PIO_DEFAULT, PIO_INPUT },
      { "RED_LED_1", AT91C_PIN_PD(18), 0, PIO_DEFAULT, PIO_INPUT },
      { "GREEN_LED_2", AT91C_PIN_PD(21), 0, PIO_DEFAULT, PIO_INPUT },
      { "RED_LED_2", AT91C_PIN_PD(22), 0, PIO_DEFAULT, PIO_INPUT },
      { "GREEN_LED_3", AT91C_PIN_PD(19), 0, PIO_DEFAULT, PIO_INPUT },
      { "RED_LED_3", AT91C_PIN_PD(20), 0, PIO_DEFAULT, PIO_INPUT },
      PIO_DESCRIPTION_END };
#endif /*CONFIG_BEEAVE_DEBUG_LEDS_OFF*/

  pmc_enable_periph_clock(AT91C_ID_PIOD);
  pio_configure(debug_led_pio);
}
#endif/*CONFIG_BEEAVE_WITH_DEBUG_LEDS*/

//*********************************************************
//! This function will init the LIGHTING LED (WHITE) of the BeeAve module : leave it OFF.
void lighting_led_init(void)
{
  const struct pio_desc lighting_led_pio[] =
    {
      { "SAMA5D3_LED_CMD", AT91C_PIN_PD(5), 0, PIO_DEFAULT, PIO_OUTPUT },
      { "ISI_SFIN", AT91C_PIN_PD(4), 0, PIO_DEFAULT, PIO_INPUT },
      { "LED_SYNC_SEL", AT91C_PIN_PD(8), 0, PIO_DEFAULT, PIO_OUTPUT },
      PIO_DESCRIPTION_END };

  pmc_enable_periph_clock(AT91C_ID_PIOD);
  pio_configure(lighting_led_pio);
}
//*********************************************************
//!This function activates the ISI_MCK output (PCK2 clock) @ 20MHz when MCK@166MHz.
void test_activate_isi_mck(void)
{
  const struct pio_desc isi_mck_io[] =
    {
      { "ISI_MCK", AT91C_PIN_PC(15), 0, PIO_DEFAULT, PIO_PERIPH_B },
        PIO_DESCRIPTION_END 
    };
    pio_configure(isi_mck_io);
    pmc_disable_system_clock(AT91C_PMC_PCK2);
    //pmc_cfg_pck(2, AT91C_PMC_CSS_SYS_CLK , AT91C_PMC_PRES_CLK_8);
    pmc_cfg_pck(2, AT91C_PMC_CSS_SYS_CLK, AT91C_PMC_PRES_CLK);
}
//*********************************************************
void hw_init_hook(void)
{
  //FOR tests
  test_activate_isi_mck();
  
  lighting_led_init();
#if defined(CONFIG_BEEAVE_WITH_DEBUG_LEDS)
  debug_leds_init();
#endif /*CONFIG_BEEAVE_WITH_DEBUG_LEDS*/
}
//**********************************************************