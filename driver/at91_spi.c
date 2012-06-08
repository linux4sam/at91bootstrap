/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
#include "common.h"
#include "hardware.h"
#include "spi.h"
#include "arch/at91_spi.h"
#include "arch/at91_pio.h"
#include "gpio.h"
#include "debug.h"
#include "board.h"

#define spi_readl(reg)			\
	readl(CONFIG_SYS_BASE_SPI + reg)

#define spi_writel(reg, value)		\
	writel(value, CONFIG_SYS_BASE_SPI + reg)

static unsigned int at91_spi_get_cs(void)
{
	unsigned int cs;

	cs = CONFIG_SYS_SPI_CS;
	return cs;
}

static void spi_cs_activate(void)
{
	pio_set_value(CONFIG_SYS_SPI_PCS, 0);
}

static void spi_cs_deactivate(void)
{
	pio_set_value(CONFIG_SYS_SPI_PCS, 1);
}

int at91_spi_init(unsigned int clock, unsigned int mode)
{
	unsigned int	scbr;
	unsigned int 	csrx;
	unsigned int	mr;
	unsigned int	cs = at91_spi_get_cs();

	scbr = MASTER_CLOCK/ clock;
	csrx = AT91C_SPI_SCBR(scbr);
	csrx |= AT91C_SPI_BITS_8;
	if (!(mode & SPI_CPHA))
		csrx |= AT91C_SPI_NCPHA;
	if (mode & SPI_CPOL)
		csrx |= AT91C_SPI_CPOL;

	mr = AT91C_SPI_MSTR 
			| AT91C_SPI_MODFDIS
			| AT91C_SPI_PCS((~(1 << cs) & 0xf));

	spi_writel(SPI_CSR(cs), csrx);
	spi_writel(SPI_MR, mr);

	return 0;
}

int at91_spi_enable(void)
{
	/* Enable the SPI hardware */
	spi_writel(SPI_CR, AT91C_SPI_SPIEN);

	return 0;
}

void at91_spi_disable(void)
{
	/* Disable the SPI hardware */
	spi_writel(SPI_CR, AT91C_SPI_SPIDIS);
}

int spi_xfer(unsigned int len, const void *dout, 
		void *din, unsigned long flags)
{
	unsigned int	len_tx;
	unsigned int	len_rx;
	const unsigned char	*txp = dout;
	unsigned char		*rxp = din;
	unsigned int 	status;
	unsigned char	value;

	if (len == 0)
		goto out;

	/*
	 * The controller can do automatic CS control, but it is
	 * somewhat quirky, and it doesn't really buy us much anyway
	 * in the context of U-Boot.
	 */
	if (flags & SPI_XFER_BEGIN) {
		spi_cs_activate();
		/*
		 * sometimes the RDR is not empty when we get here,
		 * in theory that should not happen, but it DOES happen.
		 * Read it here to be on the safe side.
		 * That also clears the OVRES flag. Required if the
		 * following loop exits due to OVRES!
		 */
		spi_readl(SPI_RDR);
		spi_readl(SPI_SR);
	}

	for (len_tx = 0, len_rx = 0; len_rx < len; ) {
		/* send data */
		if (len_tx < len) {
			do {
				status = spi_readl(SPI_SR);
			} while ((status & AT91C_SPI_TDRE) == 0);

			if (txp)
				value = *txp++;
			else
				value = 0;

			spi_writel(SPI_TDR, value);
			len_tx++;
		}

		/* recv data */
		do {
			status = spi_readl(SPI_SR);
			if (status & AT91C_SPI_OVRES) {
				spi_cs_deactivate();
				return -1;
			}
		} while ((status & AT91C_SPI_RDRF) == 0);

		value = spi_readl(SPI_RDR);
		if (rxp)
			*rxp++ = value;
		len_rx++;
	}

out:
	if (flags & SPI_XFER_END) {
		/*
		 * Wait until the transfer is completely done before
		 * we deactivate CS.
		 */
		do {
			status = spi_readl(SPI_SR);
		} while (!(status & AT91C_SPI_TXEMPTY));

		spi_cs_deactivate();
	}

	return 0;
}
