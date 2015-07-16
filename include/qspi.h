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
#ifndef	__QSPI_H__
#define	__QSPI_H__

#include "spi.h"

typedef	enum {
	read = 0,
	read_memory,
	write,
	write_memory,
} tansfer_type_t;

typedef enum {
	extended = 0,
	dual,
	quad,
} spi_protocols_t;

typedef struct qspi_frame {
	unsigned int instruction;
	unsigned int option;
	unsigned int option_len;
	unsigned int has_address;
	unsigned int address;
	unsigned int address_len;
	unsigned int continue_read;
	unsigned int dummy_cycles;
	spi_protocols_t protocol;
	tansfer_type_t tansfer_type;
} qspi_frame_t;

#define	DATA_DIR_READ		0x11
#define	DATA_DIR_WRITE		0x22

typedef struct qspi_data {
	unsigned int *buffer;
	unsigned int size;
	unsigned int direction;
} qspi_data_t;

int qspi_init(unsigned int clock, unsigned int mode);
int qspi_send_command(qspi_frame_t *frame, qspi_data_t *data);

#endif
