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

/* MUST be in the very same order as QSPI_IFR_TFRTYPE_* */
typedef enum qspi_transfer_type {
	QSPI_TFRTYPE_READ = 0,
	QSPI_TFRTYPE_READ_MEMORY = 1,
	QSPI_TFRTYPE_WRITE = 2,
	QSPI_TFRTYPE_WRITE_MEMORY = 3,
} qspi_transfer_type_t;

/* MUST be in the very same order as QSPI_IFR_WIDTH_* */
typedef enum qspi_protocol {
	QSPI_PROTO_1_1_1,	/* SINGLE BIT SPI */
	QSPI_PROTO_1_1_2,	/* DUAL OUTPUT */
	QSPI_PROTO_1_1_4,	/* QUAD OUTPUT */
	QSPI_PROTO_1_2_2,	/* DUAL IO */
	QSPI_PROTO_1_4_4,	/* QUAD IO */
	QSPI_PROTO_2_2_2,	/* DUAL CMD */
	QSPI_PROTO_4_4_4,	/* QUAD CMD */
} qspi_protocol_t;

typedef struct qspi_command {
	union {
		struct {
			unsigned int	instruction:1;
			unsigned int	address:3;
			unsigned int	mode:1;
			unsigned int	dummy:1;
			unsigned int	data:1;
			unsigned int	reserved:25;
		}		bits;
		unsigned int	word;
	}			enable;
	unsigned char		instruction;
	unsigned char		mode;
	unsigned char		num_mode_cycles;
	unsigned char		num_dummy_cycles;
	unsigned int		address;

	unsigned int		buf_len;
	const void		*tx_buf;
	void			*rx_buf;

	qspi_protocol_t		protocol;
	qspi_transfer_type_t	transfer_type;
} qspi_command_t;

typedef struct qspi_flash {
	unsigned int		addr_width;
	unsigned int		sector_size;

	qspi_protocol_t		reg_proto;
	qspi_protocol_t		read_proto;
	qspi_protocol_t		program_proto;
	qspi_protocol_t		erase_proto;

	unsigned char		read_opcode;
	unsigned char		program_opcode;
	unsigned char		erase_opcode;

	unsigned char		normal_mode;
	unsigned char		continuous_read_mode;
	unsigned char		num_mode_cycles;
	unsigned char		num_dummy_cycles;
} qspi_flash_t;

int qspi_init(unsigned int clock, unsigned int mode);
int qspi_send_command(const qspi_command_t *cmd);
unsigned char *qspi_memory_base(void);

#endif
