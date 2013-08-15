/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation

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
#include "board.h"
#include "arch/at91_twi.h"
#include "div.h"
#include "debug.h"

unsigned int at91_twi_base;

static inline unsigned int twi_reg_read(unsigned int offset)
{
	return readl(at91_twi_base + offset);
}

static inline void twi_reg_write(unsigned int offset, unsigned int value)
{
	writel(value, at91_twi_base + offset);
}

int twi_configure_master_mode(unsigned int bus_clock, unsigned int twi_clock)
{
	unsigned int loop = 1;
	unsigned int clkdiv, ckdiv = 0;
	unsigned int clock =  bus_clock;

	twi_reg_write(TWI_CR, TWI_CR_SWRST);
	twi_reg_read(TWI_RHR);

	twi_reg_write(TWI_CR, TWI_CR_SVDIS);
	twi_reg_write(TWI_CR, TWI_CR_MSEN);

	while (loop) {
		clkdiv = div(clock, (2 * twi_clock)) - 4;
		clkdiv = div(clkdiv, (1 << ckdiv));
		if (clkdiv <= 255)
			loop = 0;
		else
			ckdiv++;
	}

	twi_reg_write(TWI_CWGR, ((ckdiv << 16) | (clkdiv << 8) | clkdiv));

	return 0;
}

static void twi_stop(void)
{
	twi_reg_write(TWI_CR, TWI_CR_STOP);
}

static unsigned char twi_readbyte(void)
{
	return twi_reg_read(TWI_RHR);
}

static void twi_writebyte(unsigned char byte)
{
	twi_reg_write(TWI_THR, byte);
}

static unsigned char twi_check_rxrdy(void)
{
	return ((twi_reg_read(TWI_SR) & TWI_SR_RXRDY) == TWI_SR_RXRDY);
}

static unsigned char twi_check_txrdy(void)
{
	return ((twi_reg_read(TWI_SR) & TWI_SR_TXRDY) == TWI_SR_TXRDY);
}

static unsigned char twi_check_txcompleted(void)
{
	return ((twi_reg_read(TWI_SR) & TWI_SR_TXCOMP) == TWI_SR_TXCOMP);
}

static void twi_startread(unsigned char device_addr,
			unsigned int internal_addr,
			unsigned char iaddr_size)
{
	twi_reg_write(TWI_MMR, TWI_MMR_IADRSZ(iaddr_size)
				| TWI_MMR_MREAD_RD
				| TWI_MMR_DADR(device_addr));

	twi_reg_write(TWI_IADR, internal_addr);

	twi_reg_write(TWI_CR, TWI_CR_START);
}

static void twi_startwrite(unsigned char device_addr,
			unsigned int internal_addr,
			unsigned char iaddr_size,
			unsigned char byte)
{
	twi_reg_write(TWI_MMR, TWI_MMR_IADRSZ(iaddr_size)
				| TWI_MMR_MREAD_WR
				| TWI_MMR_DADR(device_addr));

	twi_reg_write(TWI_IADR, internal_addr);

	twi_reg_write(TWI_THR, byte);
};

int twi_read(unsigned char device_addr,
		unsigned int internal_addr,
		unsigned char iaddr_size,
		unsigned char *data,
		unsigned int bytes)
{
	int timeout;

	twi_startread(device_addr, internal_addr, iaddr_size);

	while (bytes > 0) {
		if (bytes == 1)
			twi_stop();

		timeout = 10000;
		while (!twi_check_rxrdy() && (--timeout))
			;

		if (!timeout) {
			dbg_loud("twi read: timeout to wait RXRDY bit\n\r");
			return -1;
		}

		*data++ = twi_readbyte();
		bytes--;
	}

	timeout = 10000;
	while (!twi_check_txcompleted() && (--timeout))
		;
	if (!timeout) {
		dbg_loud("twi read: timeout to wait TXCOMP bit\n\r");
		return -1;
	}

	return 0;
}

int twi_write(unsigned char device_addr,
		unsigned int internal_addr,
		unsigned char iaddr_size,
		unsigned char *data,
		unsigned int bytes)
{
	int timeout;

	twi_startwrite(device_addr, internal_addr, iaddr_size, *data++);
	bytes--;

	while (bytes > 0) {
		timeout = 10000;
		while (!twi_check_txrdy() && (--timeout))
			;

		if (!timeout) {
			dbg_loud("twi write: timeout to wait TXRDY bit\n\r");
			return -1;
		}

		twi_writebyte(*data++);
		bytes--;
	}

	twi_stop();


	timeout = 10000;
	while (!twi_check_txcompleted() && (--timeout))
		;
	if (!timeout) {
		dbg_loud("twi write: timeout to wait TXCOMP bit\n\r");
		return -1;
	}

	return 0;
}
