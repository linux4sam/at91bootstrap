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

struct spi_slave atmel_spi;

/* Register access macros */
#define spi_readl(as, reg)			\
	readl(as->base + reg)
#define spi_writel(as, reg, value)		\
	writel(value, as->base + reg)

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
			unsigned int clock, unsigned int mode)
{
	struct spi_slave  *slave = &atmel_spi;
	unsigned int	scbr;
	unsigned int 	csrx;
	void		*regs;
	unsigned int	tmp;

	switch (bus) {
	case 0:
		regs = (void *)AT91C_BASE_SPI0;
		break;
#ifdef AT91C_BASE_SPI1 
	case 1:
		regs = (void *)AT91C_BASE_SPI1;
		break;
#endif
	default:
		return NULL;
	}


	scbr = MASTER_CLOCK/ clock;
	csrx = AT91C_SPI_SCBR(scbr);
	csrx |= AT91C_SPI_BITS_8;
	if (!(mode & SPI_CPHA))
		csrx |= AT91C_SPI_NCPHA;
	if (mode & SPI_CPOL)
		csrx |= AT91C_SPI_CPOL;

	slave->bus = bus;
	slave->cs = cs;
	slave->base = regs;

	tmp = ~(1 << cs) & 0xf;
	slave->mr = AT91C_SPI_MSTR | AT91C_SPI_MODFDIS | AT91C_SPI_PCS(tmp);
	//		| AT91C_SPI_PCS(~(0x01UL << cs) & 0xf);

	spi_writel(slave, SPI_CSR(cs), csrx);
	
	return slave;
}

int spi_claim_bus(struct spi_slave *slave)
{
	/* Enable the SPI hardware */
	spi_writel(slave, SPI_CR, AT91C_SPI_SPIEN);

	/*
	 * Select the slave. This should set SCK to the correct
	 * initial state, etc.
	 */
	spi_writel(slave, SPI_MR, slave->mr);

	return 0;
}

void spi_release_bus(struct spi_slave *slave)
{
	/* Disable the SPI hardware */
	spi_writel(slave, SPI_CR, AT91C_SPI_SPIDIS);
}

int spi_xfer(struct spi_slave *slave, unsigned int bitlen,
		const void *dout, void *din, unsigned long flags)
{
	unsigned int	len_tx;
	unsigned int	len_rx;
	unsigned int	len;
	int		ret;
	unsigned int 	status;
	const unsigned char	*txp = dout;
	unsigned char		*rxp = din;
	unsigned char	value;

	ret = 0;
	if (bitlen == 0)
		/* Finish any previously submitted transfers */
		goto out;

	/*
	 * TODO: The controller can do non-multiple-of-8 bit
	 * transfers, but this driver currently doesn't support it.
	 *
	 * It's also not clear how such transfers are supposed to be
	 * represented as a stream of bytes...this is a limitation of
	 * the current SPI interface.
	 */
	if (bitlen % 8) {
		/* Errors always terminate an ongoing transfer */
		flags |= SPI_XFER_END;
		goto out;
	}

	len = bitlen / 8;

	/*
	 * The controller can do automatic CS control, but it is
	 * somewhat quirky, and it doesn't really buy us much anyway
	 * in the context of U-Boot.
	 */
	if (flags & SPI_XFER_BEGIN) {
		spi_cs_activate(slave->cs);
		/*
		 * sometimes the RDR is not empty when we get here,
		 * in theory that should not happen, but it DOES happen.
		 * Read it here to be on the safe side.
		 * That also clears the OVRES flag. Required if the
		 * following loop exits due to OVRES!
		 */
		spi_readl(slave, SPI_RDR);
		spi_readl(slave, SPI_SR);
	}

	for (len_tx = 0, len_rx = 0; len_rx < len; ) {
		if (len_tx < len) {
			do {
				status = spi_readl(slave, SPI_SR);
			} while ((status & AT91C_SPI_TDRE) == 0);

			if (txp)
				value = *txp++;
			else
				value = 0;

			spi_writel(slave, SPI_TDR, value);
			len_tx++;
		}

		do {
			status = spi_readl(slave, SPI_SR);
			if (status & AT91C_SPI_OVRES) {
				spi_cs_deactivate(slave->cs);
				return -1;
			}
		} while ((status & AT91C_SPI_RDRF) == 0);

		value = spi_readl(slave, SPI_RDR);
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
			status = spi_readl(slave, SPI_SR);
		} while (!(status & AT91C_SPI_TXEMPTY));

		spi_cs_deactivate(slave->cs);
	}

	return 0;
}
