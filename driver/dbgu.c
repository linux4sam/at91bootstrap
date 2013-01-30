/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation

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
#include "arch/at91_dbgu.h"

static inline void write_dbgu(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_DBGU);
}

static inline unsigned int read_dbgu(unsigned int offset)
{
	return readl(offset + AT91C_BASE_DBGU);
}

void dbgu_init(unsigned int baudrate)
{
	/* Disable interrupts */
	write_dbgu(DBGU_IDR, -1);

	/* Reset the receiver and transmitter */
	write_dbgu(DBGU_CR, AT91C_DBGU_RSTRX | AT91C_DBGU_RSTTX | AT91C_DBGU_RXDIS | AT91C_DBGU_TXDIS);

	/* Configure the baudrate */
	write_dbgu(DBGU_BRGR, baudrate);

	/* Configure USART in Asynchronous mode */
	write_dbgu(DBGU_MR, AT91C_DBGU_PAR);

	/* Enable RX and Tx */
	write_dbgu(DBGU_CR, AT91C_DBGU_RXEN | AT91C_DBGU_TXEN);
}

void dbgu_print(const char *ptr)
{
	int i = 0;

	while (ptr[i] != '\0') {
		while (!(read_dbgu(DBGU_CSR) & AT91C_DBGU_TXRDY)) ;
		write_dbgu(DBGU_THR, ptr[i]);
		i++;
	}
}

char dbgu_getc(void)
{
	while (!(read_dbgu(DBGU_CSR) & AT91C_DBGU_RXRDY)) ;
	return (char)read_dbgu(DBGU_RHR);
}
