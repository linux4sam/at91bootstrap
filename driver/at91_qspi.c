/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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
#include "hardware.h"
#include "board.h"
#include "qspi.h"
#include "pmc.h"
#include "div.h"
#include "string.h"
#include "arch/at91_qspi.h"

#ifndef CONFIG_SYS_BASE_QSPI
#define CONFIG_SYS_BASE_QSPI		AT91C_BASE_QSPI0
#endif

#ifndef CONFIG_SYS_BASE_QSPI_MEM
#define	CONFIG_SYS_BASE_QSPI_MEM	AT91C_BASE_QSPI0_MEM
#endif

static unsigned int qspi_get_base(void)
{
	return CONFIG_SYS_BASE_QSPI;
}

static unsigned char *qspi_memory_base(void)
{
	return (unsigned char *)CONFIG_SYS_BASE_QSPI_MEM;
}

static unsigned int qspi_readl(unsigned int reg)
{
	return readl(qspi_get_base() + reg);
}

static void qspi_writel(unsigned int reg, unsigned int value)
{
	writel(value, qspi_get_base() + reg);
}

static int qspi_clock_init(unsigned int clock, unsigned int mode)
{
	unsigned int scbr;
	unsigned int reg;
	
	if (clock == 0)
		scbr = 1;
	else
		scbr = div(at91_get_ahb_clock(), clock);

	reg = QSPI_SCR_SCBR_(scbr);
	if (mode == SPI_MODE1)
		reg |= QSPI_SCR_CPHA;
	else if (mode == SPI_MODE2)
		reg |= QSPI_SCR_CPOL;
	else if (mode == SPI_MODE3)
		reg |= (QSPI_SCR_CPOL | QSPI_SCR_CPHA);

	qspi_writel(QSPI_SCR, reg);

	return 0;
}

int qspi_init(unsigned int clock, unsigned int mode)
{
	unsigned int config;

	qspi_writel(QSPI_CR, QSPI_CR_QSPIDIS);
	qspi_writel(QSPI_CR, QSPI_CR_SWRST);

	qspi_clock_init(clock, mode);

	config = QSPI_MR_SMM_MEMORY; 
	qspi_writel(QSPI_MR, config);

	qspi_writel(QSPI_CR, QSPI_CR_QSPIEN);

	return 0;
}

int qspi_send_command(qspi_frame_t *frame, qspi_data_t *data)
{
	unsigned int instruction = 0;
	unsigned int config = 0;
	unsigned char *membuff;

	if (frame->protocol == extended)
		config |= QSPI_IFR_WIDTH_SINGLE_BIT_SPI;
	else  if (frame->protocol == dual)
		config |= QSPI_IFR_WIDTH_DUAL_CMD;
	else  if (frame->protocol == quad)
		config |= QSPI_IFR_WIDTH_QUAD_CMD;

	if (frame->instruction) {
		config |= QSPI_IFR_INSTEN;
		instruction |= QSPI_ICR_INST_(frame->instruction);
	}

	if (frame->has_address) {
		config |= QSPI_IFR_ADDREN;
		if ((!data))
			qspi_writel(QSPI_IAR, frame->address);
	}

	if (data)
		config |= QSPI_IFR_DATAEN;

	if (frame->option) {
		config |= QSPI_IFR_OPTEN;
		instruction |= QSPI_ICR_OPT_(frame->option);
	}

	if (frame->option_len == 1)
		config |= QSPI_IFR_OPTL_1BIT;
	else if (frame->option_len == 2)
		config |= QSPI_IFR_OPTL_2BIT;
	else if (frame->option_len == 4)
		config |= QSPI_IFR_OPTL_4BIT;
	else if (frame->option_len == 8)
		config |= QSPI_IFR_OPTL_8BIT;

	if (frame->address_len)
		config |= QSPI_IFR_ADDRL_32_BIT;

	if (frame->tansfer_type == read)
		config |= QSPI_IFR_TFRTYPE_READ;
	else if (frame->tansfer_type == read_memory)
		config |= QSPI_IFR_TFRTYPE_READ_MEMORY;
	else if (frame->tansfer_type == write)
		config |= QSPI_IFR_TFRTYPE_WRITE;
	else if (frame->tansfer_type == write_memory)
		config |= QSPI_IFR_TFRTYPE_WRITE_MEMORY;

	if (frame->continue_read)
		config |= QSPI_IFR_CRM;

	config |= QSPI_IFR_NBDUM_(frame->dummy_cycles);

	qspi_writel(QSPI_ICR, instruction);
	qspi_writel(QSPI_IFR, config);

	qspi_readl(QSPI_IFR);	/* To synchronize system bus access */

	if (data) {
		membuff = qspi_memory_base() + frame->address;
		if (data->direction == DATA_DIR_READ)
			memcpy((unsigned char *)data->buffer, membuff, data->size);
		else if (data->direction == DATA_DIR_WRITE)
			memcpy(membuff, (unsigned char *)data->buffer, data->size);
	}

	qspi_writel(QSPI_CR, QSPI_CR_LASTXFER);

	while (!(qspi_readl(QSPI_SR) & QSPI_SR_INSTRE))
		;

	return 0;
}
