// Copyright (C) 2010 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "board.h"
#include "arch/at91_dbgu.h"

#ifdef CONFIG_USART

#ifdef CONFIG_CONSOLE_INDEX
extern const unsigned int usart_base;
#define USART_BASE usart_base
#else
#define USART_BASE	AT91C_BASE_DBGU
#endif

static inline void write_usart(unsigned int offset, const unsigned int value)
{
	writel(value, offset + USART_BASE);
}

static inline unsigned int read_usart(unsigned int offset)
{
	return readl(offset + USART_BASE);
}

void usart_init(unsigned int baudrate)
{
	/* Disable interrupts */
	write_usart(DBGU_IDR, -1);

	/* Reset the receiver and transmitter */
	write_usart(DBGU_CR, AT91C_DBGU_RSTRX
				| AT91C_DBGU_RSTTX
				| AT91C_DBGU_RXDIS
				| AT91C_DBGU_TXDIS);

	/* Configure the baudrate */
	write_usart(DBGU_BRGR, baudrate);

	/* Configure USART in Asynchronous mode */
	write_usart(DBGU_MR, AT91C_DBGU_PAR_NONE
				| AT91C_DBGU_CHMODE_NORMAL
				| AT91C_DBGU_CHRL_8BIT
				| AT91C_DBGU_NBSTOP_1BIT);

	/* Enable RX and Tx */
	write_usart(DBGU_CR, AT91C_DBGU_RXEN | AT91C_DBGU_TXEN);
}

static void usart_putc(const char c)
{
	while (!(read_usart(DBGU_CSR) & AT91C_DBGU_TXRDY))
		;

	write_usart(DBGU_THR, c);
}

void usart_puts(const char *ptr)
{
	int i = 0;

	while (ptr[i] != '\0') {
		if (ptr[i] == '\n')
			usart_putc('\r');
		usart_putc(ptr[i]);
		i++;
	}
}

char usart_getc(void)
{
	while (!(read_usart(DBGU_CSR) & AT91C_DBGU_RXRDY))
		;

	return (char)read_usart(DBGU_RHR);
}

#else

void usart_puts(const char *ptr)
{

}

#endif
