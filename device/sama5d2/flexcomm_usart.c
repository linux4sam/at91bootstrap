#include "flexcomm_usart.h"

#include "component/flexcom.h"
#include "sama5d27cd1g.h"
#include "arch/at91_pio.h"
#include "gpio.h"
#include "pmc.h"
#include "usart.h"
#include "sama5d2_board.h"
#define SET_BAUD_RATE 921600
/* #define BAUD_RATE_CD 22 */
/* #define BAUD_RATE_CD_FRAC 2 */
#define BAUD_RATE_CD 11
#define BAUD_RATE_CD_FRAC 1

void flexcomm_usart_init()
{
    const struct pio_desc usart_pins[3] = {
        {"RX_USART0", AT91C_PIN_PB(29), 0, PIO_DEFAULT, PIO_PERIPH_C},
        {"TX_USART0", AT91C_PIN_PB(28), 0, PIO_DEFAULT, PIO_PERIPH_C},
        {NULL, 0, PIO_DEFAULT, PIO_PERIPH_A}
    };
    pio_configure(usart_pins);
    pmc_enable_periph_clock(ID_FLEXCOM0, PMC_PERIPH_CLK_DIVIDER_NA);
    // Set to USART mode
    FLEXCOM0_REGS->FLEX_MR = 1;
    // Disable TX and RX
    FLEXCOM0_REGS->FLEX_US_CR = FLEX_US_CR_RXDIS(1) | FLEX_US_CR_TXDIS(1);
    // Set to 8 bit and no parity
    FLEXCOM0_REGS->FLEX_US_MR = FLEX_US_MR_CHRL_8_BIT | FLEX_US_MR_PAR_NO | FLEX_US_MR_OVER(1);
    // Set baud rate
    if (pmc_mck_check_h32mxdiv())
    {
        // FLEXCOM0_REGS->FLEX_US_BRGR = BAUDRATE(MASTER_CLOCK / 2, SET_BAUD_RATE);
	    FLEXCOM0_REGS->FLEX_US_BRGR = BAUD_RATE_CD | (BAUD_RATE_CD_FRAC << 16);
    }
    else
    {
        FLEXCOM0_REGS->FLEX_US_BRGR = BAUDRATE(MASTER_CLOCK, SET_BAUD_RATE);
    }
    // Enable RX and TX
    FLEXCOM0_REGS->FLEX_US_CR =
        FLEX_US_CR_RXDIS(0) | FLEX_US_CR_TXDIS(0) | FLEX_US_CR_RXEN(1) | FLEX_US_CR_TXEN(1);
    // Clear RXRDY flag bc we just enabled RX
    (void)FLEXCOM0_REGS->FLEX_US_RHR;
}

bool flexcomm_usart_write(const uint8_t* const data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        // Wait for TX to be ready
        while (!(FLEXCOM0_REGS->FLEX_US_CSR & FLEX_US_CSR_TXRDY_Msk));
        // Write byte to the holding register
        FLEXCOM0_REGS->FLEX_US_THR = (unsigned int)data[i];
    }
    return true;
}

bool flexcomm_usart_read(uint8_t* const data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        // Wait for RX to be ready
        while (!(FLEXCOM0_REGS->FLEX_US_CSR & FLEX_US_CSR_RXRDY_Msk));
        // Read byte into buffer
        data[i] = (uint8_t)(FLEXCOM0_REGS->FLEX_US_RHR & 0xff);
    }
    return true;
}
