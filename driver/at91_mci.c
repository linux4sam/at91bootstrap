/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
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
#include "board.h"
#include "arch/at91_mci.h"

#include "debug.h"

inline unsigned int mci_readl(unsigned int reg)
{
	return readl((void *)CONFIG_SYS_BASE_MCI + reg);
}

inline void mci_writel(unsigned int reg, unsigned int value)
{
	writel((value), (void *)CONFIG_SYS_BASE_MCI + reg);
}

static int at91_mci_set_clock_blklen(unsigned int clock,
					unsigned int blklen)
{
	unsigned int clkdiv;
	unsigned int reg;

	clkdiv = (MASTER_CLOCK + clock) / clock;

	blklen &= 0xfffc;

	reg = mci_readl(MCI_BLKR);
	reg &= ~(((0x1 << 16) - 1) << 16);
	reg |= (blklen << 16);
	mci_writel(MCI_BLKR, reg);

#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(AT91SAMA5D3X)
	clkdiv -= 2;
	reg = mci_readl(MCI_MR);
	reg &= ~((0x01 << 8) - 1);
	reg |= (clkdiv >> 1);
	reg |= (clkdiv & 1) ? AT91C_MCI_CLKODD : 0;

	mci_writel(MCI_MR, reg);
#else
	clkdiv = clkdiv / 2 - 1;
	if (clkdiv > 0xff)
		clkdiv = 0xff;

	reg = mci_readl(MCI_MR);
	reg &= ~((0x01 << 8) - 1);
	reg &= ~(((0x1 << 16) - 1) << 16);
	reg |= AT91C_MCI_MRBLKLEN(blklen);
	reg |= AT91C_MCI_CLKDIV(clkdiv);

	mci_writel(MCI_MR, reg);
#endif

	return 0;
}

int at91_mci_init(unsigned int clock, unsigned int blklen)
{
	int ret;

	/* software reset */
	mci_writel(MCI_CR, AT91C_MCI_SWRST);

	/* disable mci and disable power save mode */
	mci_writel(MCI_CR, AT91C_MCI_PWSDIS | AT91C_MCI_MCIDIS);

	/* enable Read Proof and Write Proof   */
	mci_writel(MCI_MR, AT91C_MCI_RDPROOF_ENABLE | AT91C_MCI_WRPROOF_ENABLE);

	/* select Slot A and set bus width 1 bit*/
	mci_writel(MCI_SDCR, AT91C_MCI_SCDSEL_SLOTA
				| AT91C_MCI_SCDBUS_1BIT);

	/* set the Data Timeout Register */
	mci_writel(MCI_DTOR, 0x7f);

	/* disable Interrupt */
	mci_writel(MCI_IDR, ~0L);

	/* set mci clock and blocklen */
	ret = at91_mci_set_clock_blklen(clock, blklen);
	if (ret)
		return ret;

	/* enable mci */
	mci_writel(MCI_CR, AT91C_MCI_MCIEN);

	return 0;
}

int at91_mci_set_clock(unsigned int clock)
{
	unsigned int blklen;
	int ret;

	blklen = (mci_readl(MCI_BLKR) >> 16) & 0xffff;

	ret = at91_mci_set_clock_blklen(clock, blklen);
	if (ret)
		return ret;

	return 0;
}

void at91_mci_set_blkr(unsigned int blkcnt, unsigned int blklen)
{
	mci_writel(MCI_BLKR, (blklen << 16) | blkcnt);
}

int at91_mci_set_bus_width(unsigned int buswidth)
{
	unsigned int reg;

	reg = mci_readl(MCI_SDCR);
	reg &= ~(AT91C_MCI_SCDBUS);

	switch (buswidth) {
	case 8:
		reg |=  AT91C_MCI_SCDBUS_8BIT;
		break;

	case 4:
		reg |= AT91C_MCI_SCDBUS_4BIT;
		break;

	case 1:
		reg |= AT91C_MCI_SCDBUS_1BIT;
		break;

	default:
		return -1;
	}

	mci_writel(MCI_SDCR, reg);

	return 0;
}

/*
 * Refer to the at91sam9g20 datasheet:
 * Figure 35-10. Read Function Flow Diagram
 */
static int at91_mci_read_data(unsigned int *data)
{
	unsigned int status;
	unsigned int error_check = (AT91C_MCI_DCRCE
					| AT91C_MCI_DTOE
					| AT91C_MCI_OVRE);
	/*
	 * Read status register MCI_SR
	 * Wait for RXRDY or error bits
	 */
	do {
		status = mci_readl(MCI_SR);
	} while ((!(status & AT91C_MCI_RXRDY))
			&& (!(status & error_check))); 

	if (status & error_check) {
		dbg_log(1, "Error to read data, sr: %d\n\r", status);
		return -1;
	}

	if (status & AT91C_MCI_RXRDY)
		*data = mci_readl(MCI_RDR);

	return 0;
}

int at91_mci_read_block_data(unsigned int *data,
			unsigned int bytes_to_read,
			unsigned int block_len)
{
	unsigned int count;
	unsigned int words_to_read = bytes_to_read >> 2;
	unsigned int words_of_block = block_len >> 2;
	unsigned int tmp;
	int timeout = 10000;
	int ret;

	/* Read the valid data of the block */
	for (count = 0; count < words_to_read; count++, data++) {
		ret = at91_mci_read_data(data);
		if (ret)
			return ret;
	}

	/* Read the no useful data the block */
	for (; count < words_of_block; count++) {
		ret = at91_mci_read_data(&tmp);
		if (ret)
			return ret;
	}

	while ((mci_readl(MCI_SR) & AT91C_MCI_DTIP) && (--timeout))
		;

	if (!timeout) {
		dbg_log(1, "Data Transfer in Progress.\n\r");
		return -1;
	}

	return 0;
}

int at91_mci_read_blocks(unsigned int *data,
			unsigned int blocks,
			unsigned int block_len)
{
	unsigned int block;
	unsigned int count;
	unsigned int words_of_block = block_len >> 2;
	int timeout = 10000;
	int ret;

	for (block = 0; block < blocks; block++) {
		for (count = 0; count < words_of_block; count++, data++) {
			ret = at91_mci_read_data(data);
			if (ret)
				return ret;
		}
	}

	while ((mci_readl(MCI_SR) & AT91C_MCI_DTIP) && (--timeout))
		;

	if (!timeout) {
		dbg_log(1, "Data Transfer in Progress.\n\r");
		return -1;
	}

	return 0;
}

static int at91_mci_write_data(unsigned int *data)
{
	unsigned int status;

	/*
	 * Read status register MCI_SR
	 * Wait for TXRDY or error bits
	 */
	do {
		status = mci_readl(MCI_SR);
	} while (!(status & AT91C_MCI_TXRDY));

	mci_writel(MCI_TDR, *data);

	return 0;
}

int at91_mci_write_block_data(unsigned int *data,
			unsigned int bytes_to_write,
			unsigned int block_len)
{
	unsigned int count;
	unsigned int words_to_write = bytes_to_write >> 2;
	unsigned int words_of_block = block_len >> 2;
	unsigned int tmp = 0;
	int timeout = 10000;
	int ret;

	/* write the valid data of the block */
	for (count = 0; count < words_to_write; count++, data++) {
		ret = at91_mci_write_data(data);
		if (ret)
			return ret;
	}

	/* write the no useful data the block */
	for (; count < words_of_block; count++) {
		ret = at91_mci_write_data(&tmp);
		if (ret)
			return ret;
	}

	while ((mci_readl(MCI_SR) & AT91C_MCI_DTIP) && (--timeout))
		;

	if (!timeout) {
		dbg_log(1, "Data Transfer in Progress.\n\r");
		return -1;
	}

	return 0;
}
