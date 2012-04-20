/*
 * Copyright (C) 2007 Atmel Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include "common.h"
#include "hardware.h"
#include "board.h"
#include "spi.h"
#include "arch/at91_spi.h"
#include "debug.h"

/* Register access macros */
#define spi_readl(reg)			\
	readl(AT91_BASE_SPI + reg)

#define spi_writel(reg, value)		\
	writel(value, AT91_BASE_SPI + reg)

static unsigned int at91_spi_get_cs(void)
{
	unsigned int cs;

	cs = CONFIG_SPI_CS;
	return cs;
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
	unsigned int	cs = at91_spi_get_cs();

	if (len == 0)
		goto out;

	/*
	 * The controller can do automatic CS control, but it is
	 * somewhat quirky, and it doesn't really buy us much anyway
	 * in the context of U-Boot.
	 */
	if (flags & SPI_XFER_BEGIN) {
		spi_cs_activate(cs);
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
				spi_cs_deactivate(cs);
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

		spi_cs_deactivate(cs);
	}

	return 0;
}
