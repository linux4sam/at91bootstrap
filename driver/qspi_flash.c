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
#include "common.h"
#include "board.h"
#include "qspi.h"
#include "string.h"
#include "debug.h"
#include "fdt.h"

/*
 * QSPI Manufacturer IDs
 */
#define QSPI_MFR_SPANSION	0x01
#define QSPI_MFR_MICRON		0x20
#define QSPI_MFR_MACRONIX	0xc2
#define QSPI_MFR_WINBOND	0xef

/*
 * Generic commands
 */
#define	CMD_READ_ID				0x9f

#define	CMD_READ				0x03
#define	CMD_FAST_READ				0x0b
#define	CMD_FAST_READ_1_1_2			0x3b
#define	CMD_FAST_READ_1_1_4			0x6b
#define	CMD_FAST_READ_1_2_2			0xbb
#define	CMD_FAST_READ_1_4_4			0xeb

#define	CMD_PAGE_PROGRAM			0x02
#define	CMD_QUAD_PAGE_PROGRAM			0x32
#define	CMD_SECTOR_ERASE			0xd8

#define	CMD_WRITE_ENABLE			0x06
#define	CMD_WRITE_DISABLE			0x04

#define	CMD_READ_STATUS_REG			0x05
#define	CMD_WRITE_STATUS_REG			0x01

/*
 * 4byte address commands:
 * MUST be named as the associated 3byte address command with the _4B suffix.
 */
#define	CMD_READ_4B				0x13
#define	CMD_FAST_READ_4B			0x0c
#define	CMD_FAST_READ_1_1_2_4B			0x3c
#define	CMD_FAST_READ_1_1_4_4B			0x6c
#define	CMD_FAST_READ_1_2_2_4B			0xbc
#define	CMD_FAST_READ_1_4_4_4B			0xec

#define	CMD_PAGE_PROGRAM_4B			0x12
#define	CMD_QUAD_PAGE_PROGRAM_4B		0x34
#define	CMD_SECTOR_ERASE_4B			0xdc


/* Status Register Bit Definitions */
#define	STATUS_WRITE_READY		(0x0 << 0)
#define	STATUS_WRITE_BUSY		(0x1 << 0)
#define	STATUS_WRITE_ENABLE_CLEAR	(0x0 << 1)
#define	STATUS_WRITE_ENABLE_SET		(0x1 << 1)


/*
 * Micron & Macronix commands
 */
#define	CMD_MIO_READ_ID				0xaf


/*
 * Micron only
 */
#define	CMD_READ_VCR				0x85
#define	CMD_WRITE_VCR				0x81
#define	CMD_READ_EVCR				0x65
#define	CMD_WRITE_EVCR				0x61

/* Enhanced Volatile Configuration Register Bit Definitions */
#define	EVCR_DUAL_ENABLE		(0x1 << 6)
#define	EVCR_QUAD_ENABLE		(0x1 << 7)


/*
 * Macronix only
 */
#define	CMD_READ_CONFIG_REG_MX			0x15

#define	SR_QUAD_EN_MX			(0x1 << 6)

#define	CMD_QUAD_PAGE_PROGRAM_MX		0x38
#define	CMD_QUAD_PAGE_PROGRAM_MX_4B		0x3e



static int qspi_flash_read_reg(qspi_flash_t *flash, unsigned char opcode,
			       void *buf, unsigned int buf_len)
{
	qspi_command_t cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.data = 1;
	cmd.instruction = opcode;
	cmd.rx_buf = buf;
	cmd.buf_len = buf_len;
	cmd.protocol = flash->reg_proto;
	cmd.transfer_type = QSPI_TFRTYPE_READ;
	return qspi_send_command(&cmd);
}

static int qspi_flash_write_reg(qspi_flash_t *flash, unsigned char opcode,
				const void *buf, unsigned int buf_len)
{
	qspi_command_t cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.data = (buf && buf_len);
	cmd.instruction = opcode;
	cmd.tx_buf = buf;
	cmd.buf_len = buf_len;
	cmd.protocol = flash->reg_proto;
	cmd.transfer_type = QSPI_TFRTYPE_WRITE;
	return qspi_send_command(&cmd);
}
#if 0
static int qspi_flash_program(qspi_flash_t *flash, unsigned int to,
			      const void *buf, unsigned int buf_len)
{
	qspi_command_t cmd;

	if (!buf_len)
		return 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.address = flash->addr_width;
	cmd.enable.bits.data = 1;
	cmd.instruction = flash->program_opcode;
	cmd.address = to;
	cmd.tx_buf = buf;
	cmd.buf_len = buf_len;
	cmd.protocol = flash->program_proto;
	cmd.transfer_type = QSPI_TFRTYPE_WRITE_MEMORY;
	return qspi_send_command(&cmd);
}

static int qspi_flash_erase(qspi_flash_t *flash, unsigned int address)
{
	qspi_command_t cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.address = flash->addr_width;
	cmd.instruction = flash->erase_opcode;
	cmd.address = address;
	cmd.protocol = flash->erase_proto;
	cmd.transfer_type = QSPI_TFRTYPE_WRITE;
	return qspi_send_command(&cmd);
}
#endif
static int qspi_flash_read(qspi_flash_t *flash, unsigned int from,
			   void *buf, unsigned int buf_len)
{
	qspi_command_t cmd;

	if (buf && !buf_len)
		return 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.enable.bits.instruction = 1;
	cmd.enable.bits.address = flash->addr_width;
	cmd.enable.bits.mode = (flash->num_mode_cycles > 0);
	cmd.enable.bits.dummy = (flash->num_dummy_cycles > 0);
	cmd.enable.bits.data = 1;
	cmd.instruction = flash->read_opcode;
	cmd.address = from;
	cmd.mode = (buf) ? flash->normal_mode : flash->continuous_read_mode;
	cmd.num_mode_cycles = flash->num_mode_cycles;
	cmd.num_dummy_cycles = flash->num_dummy_cycles;
	cmd.rx_buf = buf;
	cmd.buf_len = buf_len;
	cmd.protocol = flash->read_proto;
	cmd.transfer_type = QSPI_TFRTYPE_READ_MEMORY;
	return qspi_send_command(&cmd);
}

static inline int qspi_flash_read_status_reg(qspi_flash_t *flash)
{
	unsigned char val;
	int ret;

	ret = qspi_flash_read_reg(flash, CMD_READ_STATUS_REG, &val, 1);
	return (ret < 0) ? ret : val;
}

static inline int qspi_flash_write_status_reg(qspi_flash_t *flash,
					      unsigned char val)
{
	return qspi_flash_write_reg(flash, CMD_WRITE_STATUS_REG, &val, 1);
}

static inline int qspi_flash_read_macronix_config_reg(qspi_flash_t *flash)
{
	unsigned char val;
	int ret;

	ret = qspi_flash_read_reg(flash, CMD_READ_CONFIG_REG_MX, &val, 1);
	return (ret < 0) ? ret : val;
}

static inline int qspi_flash_write_status_and_config_regs(qspi_flash_t *flash,
							  unsigned char sr_cr[2])
{
	return qspi_flash_write_reg(flash, CMD_WRITE_STATUS_REG, sr_cr, 2);
}

static inline int qspi_flash_write_enable(qspi_flash_t *flash)
{
	return qspi_flash_write_reg(flash, CMD_WRITE_ENABLE, NULL, 0);
}

static inline int qspi_flash_write_disable(qspi_flash_t *flash)
{
	return qspi_flash_write_reg(flash, CMD_WRITE_DISABLE, NULL, 0);
}

static inline int qspi_flash_ready(qspi_flash_t *flash)
{
	int sr = qspi_flash_read_status_reg(flash);
	if (sr < 0)
		return sr;
	else
		return !(sr & STATUS_WRITE_BUSY);
}

static int qspi_flash_wait_ready(qspi_flash_t *flash)
{
	int ret;

	for (;;) {
		ret = qspi_flash_ready(flash);
		if (ret < 0)
			return ret;
		if (ret)
			return 0;
	}

	return -1;
}

/*
 * Spansion
 */

static int qspi_flash_init_spansion(qspi_flash_t *flash)
{
	// TODO:
	return 0;
}


/*
 * Micron
 */

static int micron_set_protocol(qspi_flash_t *flash,
			       unsigned char mask, unsigned char val,
			       qspi_protocol_t proto)
{
	unsigned char evcr;
	int ret;

	/* Read the Enhanced Volatile Configuration Register (EVCR). */
	ret = qspi_flash_read_reg(flash, CMD_READ_EVCR, &evcr, 1);
	if (ret < 0) {
		dbg_info("QSPI Flash: error while reading EVCR register\n");
		return ret;
	}

	/* Check whether we need to update the protocol bits. */
	if ((evcr & mask) == val)
		return 0;

	/* Set EVCR protocol bits. */
	qspi_flash_write_enable(flash);
	evcr = (evcr & ~mask) | val;
	ret = qspi_flash_write_reg(flash, CMD_WRITE_EVCR, &evcr, 1);
	if (ret < 0) {
		dbg_info("QSPI Flash: error while writing EVCR register\n");
		return ret;
	}

	/* Switch reg protocol now before accessing any other registers. */
	flash->reg_proto = proto;

	ret = qspi_flash_wait_ready(flash);
	if (ret)
		return ret;

	/* Read EVCR and check it. */
	ret = qspi_flash_read_reg(flash, CMD_READ_EVCR, &evcr, 1);
	if (ret < 0 || (evcr & mask) != val) {
		dbg_info("QSPI Flash: Micron EVCR protocol bits not updated\n");
		return -1;
	}

	return 0;
}

static int micron_set_quad_spi_protocol(qspi_flash_t *flash)
{
	int ret;

	/* Set Quad/Dual bits to 0_ to select the Quad SPI mode. */
	ret = micron_set_protocol(flash,
				  EVCR_QUAD_ENABLE,
				  0,
				  QSPI_PROTO_4_4_4);
	if (ret) {
		dbg_info("QSPI Flash: Failed to enter Micron Quad SPI mode\n");
		return ret;
	}

	flash->read_proto = QSPI_PROTO_4_4_4;
	flash->program_proto = QSPI_PROTO_4_4_4;
	flash->erase_proto = QSPI_PROTO_4_4_4;
	return 0;
}
#if 0
static int micron_set_dual_spi_protocol(qspi_flash_t *flash)
{
	int ret;

	/* Set Quad/Dual bits to 10 to select the Dual SPI mode. */
	ret = micron_set_protocol(flash,
				  EVCR_DUAL_ENABLE | EVCR_QUAD_ENABLE,
				  EVCR_QUAD_ENABLE,
				  QSPI_PROTO_2_2_2);
	if (ret) {
		dbg_info("QSPI Flash: Failed to enter Micron Dual SPI mode\n");
		return ret;
	}

	flash->read_proto = QSPI_PROTO_2_2_2;
	flash->program_proto = QSPI_PROTO_2_2_2;
	flash->erase_proto = QSPI_PROTO_2_2_2;
	return 0;
}

static int micron_set_extended_spi_protocol(qspi_flash_t *flash)
{
	int ret;

	/* Set Quad/Dual bits to 11 to select the Extended SPI mode. */
	ret = micron_set_protocol(flash,
				  EVCR_DUAL_ENABLE | EVCR_QUAD_ENABLE,
				  EVCR_DUAL_ENABLE | EVCR_QUAD_ENABLE,
				  QSPI_PROTO_1_1_1);
	if (ret) {
		dbg_info("QSPI Flash: Failed to enter Micron Extended SPI mode\n");
		return ret;
	}

	flash->program_proto = QSPI_PROTO_1_1_1;
	flash->erase_proto = QSPI_PROTO_1_1_1;
	return 0;
}
#endif
static int micron_set_dummy_cycles(qspi_flash_t *flash,
				   unsigned char num_dummy_cycles)
{
	unsigned char vcr, val, mask;
	int ret;

	/* Clear bit3 (XIP) to enable the Continuoues Read mode. */
	mask = 0xf8;
	val = (num_dummy_cycles << 4) & mask;

	/* Read the Volatile Configuration Register (VCR). */
	ret = qspi_flash_read_reg(flash, CMD_READ_VCR, &vcr, 1);
	if (ret < 0) {
		dbg_info("QSPI Flash: error while reading VCR register\n");
		return ret;
	}

	/* Check whether we need to update the number of dummy cycles. */
	if ((vcr & mask) == val)
		goto updated;

	/* Update the number of dummy into the VCR. */
	qspi_flash_write_enable(flash);
	vcr = (vcr & ~mask) | val;
	ret = qspi_flash_write_reg(flash, CMD_WRITE_VCR, &vcr, 1);
	if (ret < 0) {
		dbg_info("QSPI Flash: error while writing VCR register\n");
		return ret;
	}

	ret = qspi_flash_wait_ready(flash);
	if (ret < 0)
		return ret;

	/* Read VCR and check it. */
	ret = qspi_flash_read_reg(flash, CMD_READ_VCR, &vcr, 1);
	if (ret < 0 || (vcr & mask) != val) {
		dbg_info("QSPI Flash: Micron VCR dummy cycles not updated\n");
		return -1;
	}

updated:
	/* Save the number of mode/dummy cycles to use with Fast Read commands. */
	if (num_dummy_cycles) {
		flash->num_mode_cycles = 1;
		flash->num_dummy_cycles = num_dummy_cycles - 1;
	} else {
		flash->num_mode_cycles = 0;
		flash->num_dummy_cycles = 0;
	}

	/* mode cycle - bit[0] = 0x0: continuous read, normal read otherwise */
	flash->normal_mode = 0x01;
	flash->continuous_read_mode = 0x00;

	return 0;
}

static int qspi_flash_init_micron(qspi_flash_t *flash)
{
	int ret;

	ret = micron_set_quad_spi_protocol(flash);
	if (ret)
		return ret;

	ret = micron_set_dummy_cycles(flash, 8);
	if (ret)
		return ret;

	flash->read_opcode = CMD_FAST_READ_1_4_4;
	return 0;
}


/*
 * Macronix
 */

static int macronix_quad_enable(qspi_flash_t *flash)
{
	int ret, val;

	val = qspi_flash_read_status_reg(flash);
	if (val < 0)
		return val;

	if (val & SR_QUAD_EN_MX)
		return 0;
	dbg_info("QSPI Flash: Macronix Quad mode disabled, enable it\n");

	ret = qspi_flash_write_enable(flash);
	if (ret)
		return ret;

	ret = qspi_flash_write_status_reg(flash, val | SR_QUAD_EN_MX);
	if (ret)
		return ret;

	ret = qspi_flash_wait_ready(flash);
	if (ret)
		return ret;

	ret = qspi_flash_read_status_reg(flash);
	if (!(ret > 0 && (ret & SR_QUAD_EN_MX))) {
		dbg_info("QSPI Flash: Macronix Quad bit not set\n");
		return -1;
	}

	return 0;
}

static inline int macronix_dummy2code(unsigned char read_opcode,
				      unsigned char num_dummy_cycles,
				      unsigned char *dc)
{
	switch (read_opcode) {
	case CMD_READ:
		*dc = 0;
		break;

	case CMD_FAST_READ:
	case CMD_FAST_READ_1_1_4:
		switch (num_dummy_cycles) {
		case 6:
			*dc = 1;
			break;
		case 8:
			*dc = 0;
			break;
		case 10:
			*dc = 3;
			break;
		default:
			return -1;
		}
		break;

	case CMD_FAST_READ_1_4_4:
		switch (num_dummy_cycles) {
		case 4:
			*dc = 1;
			break;
		case 6:
			*dc = 0;
			break;
		case 8:
			*dc = 2;
			break;
		case 10:
			*dc = 3;
		default:
			return -1;
		}
		break;

	default:
		return -1;
	}

	return 0;
}

static int macronix_set_dummy_cycles(qspi_flash_t *flash,
				     unsigned char num_dummy_cycles)
{
	int ret, sr, cr, mask, val;
	unsigned char dc, sr_cr[2];

	/* Convert the numver of dummy cycles into Macronix DC volatile bits. */
	ret = macronix_dummy2code(flash->read_opcode, num_dummy_cycles, &dc);
	if (ret)
		return ret;

	mask = 0xc0;
	val = (dc << 6) & mask;

	cr = qspi_flash_read_macronix_config_reg(flash);
	if (cr < 0) {
		dbg_info("QSPI Flash: error while reading CR register\n");
		return cr;
	}

	if ((cr & mask) == val)
		goto updated;

	sr = qspi_flash_read_status_reg(flash);
	if (sr < 0) {
		dbg_info("QSPI Flash: error while reading SR register\n");
		return sr;
	}

	ret = qspi_flash_write_enable(flash);
	if (ret)
		return ret;

	cr = (cr & ~mask) | val;
	sr_cr[0] = sr & 0xff;
	sr_cr[1] = cr & 0xff;
	ret = qspi_flash_write_status_and_config_regs(flash, sr_cr);
	if (ret) {
		dbg_info("QSPI Flash: error while writing SR and CR registers\n");
		return ret;
	}

	ret = qspi_flash_wait_ready(flash);
	if (ret)
		return ret;

	cr = qspi_flash_read_macronix_config_reg(flash);
	if (cr < 0 || (cr & mask) != val) {
		dbg_info("QSPI Flash: Macronix Dummy Cycle bits not updated\n");
		return -1;
	}

updated:
	if (num_dummy_cycles) {
		flash->num_mode_cycles = 2;
		flash->num_dummy_cycles = num_dummy_cycles - 2;
	} else {
		flash->num_mode_cycles = 0;
		flash->num_dummy_cycles = 0;
	}

	/* mode cycles: bit[0:3] = ~bit[4:7]: continuous read, normal read otherwise */
	flash->normal_mode = 0x00;
	flash->continuous_read_mode = 0xf0;

	return 0;
}

static int qspi_flash_init_macronix(qspi_flash_t *flash)
{
	int ret;

	/*
	 * In QPI mode, only the Fast Read 1-4-4 (0xeb) op code is supported.
	 * In SPI mode, both the Fast Read 1-1-4 (0x6b) and Fast Read 1-4-4
	 * (0xeb) op codes are supported but we'd rather use the Fast Read 1-4-4
	 * command as it is the only one which allows us to enter/leave the
	 * peformance enhance (continuous read) mode required by XIP operations.
	 */
	flash->read_opcode = CMD_FAST_READ_1_4_4;

	/*
	 * Check whether the QPI mode is enabled: if it is then we know that
	 * the Quad Enabled (QE) non-volatile bit is already set. Otherwise,
	 * we MUST set the QE bit before using any Quad SPI command.
	 */
	if (flash->read_proto != QSPI_PROTO_4_4_4) {
		ret = macronix_quad_enable(flash);
		if (ret)
			return ret;

		flash->read_proto = QSPI_PROTO_1_4_4;
	}

	return macronix_set_dummy_cycles(flash, 8);
}


/*
 * Winbond
 */

static int qspi_flash_init_winbond(qspi_flash_t *flash)
{
	// TODO:
	return 0;
}


typedef struct read_id_config {
	qspi_protocol_t		proto;
	unsigned char		opcode;
} read_id_config_t;

static const read_id_config_t configs[] = {
	/* Regular protocol and command */
	{QSPI_PROTO_1_1_1, CMD_READ_ID},

	/* Winbond QPI mode */
	{QSPI_PROTO_4_4_4, CMD_READ_ID},

	/* Micron Quad mode & Macronix QPI mode */
	{QSPI_PROTO_4_4_4, CMD_MIO_READ_ID},

	/* Micron Dual mode */
	{QSPI_PROTO_2_2_2, CMD_MIO_READ_ID},
};


typedef struct flash_id {
	unsigned char		manufacturer_id;
	int			(*init)(qspi_flash_t *);
} flash_id_t;

static const flash_id_t flash_ids[] = {
	{ QSPI_MFR_SPANSION,	qspi_flash_init_spansion },
	{ QSPI_MFR_MICRON,	qspi_flash_init_micron },
	{ QSPI_MFR_MACRONIX,	qspi_flash_init_macronix },
	{ QSPI_MFR_WINBOND,	qspi_flash_init_winbond },
};

#ifdef CONFIG_QSPI_4B_OPCODES
struct address_entry {
	unsigned char	src_opcode;
	unsigned char	dst_opcode;
};

static unsigned char
qspi_flash_convert_opcode(unsigned char opcode,
			  const struct address_entry *entries,
			  int num_entries)
{
	int b, e;

	b = 0;
	e = num_entries - 1;
	while (b <= e) {
		int m = (b + e) >> 1;
		const struct address_entry *entry = &entries[m];

		if (opcode == entry->src_opcode)
			return entry->dst_opcode;

		if (opcode < entry->src_opcode)
			e = m - 1;
		else
			b = m + 1;
	}

	/* No convertion found */
	return opcode;
}

static unsigned char qspi_flash_3to4_opcode(unsigned char opcode)
{
	/* MUST be sorted by 3byte opcode */
#define ENTRY_3TO4(_opcode)	{ _opcode, _opcode##_4B }
	static const struct address_entry qspi_flash_3to4_table[] = {
		ENTRY_3TO4(CMD_PAGE_PROGRAM),		/* 0x02 */
		ENTRY_3TO4(CMD_READ),			/* 0x03 */
		ENTRY_3TO4(CMD_FAST_READ),		/* 0x0b */
		ENTRY_3TO4(CMD_QUAD_PAGE_PROGRAM),	/* 0x32 */
		ENTRY_3TO4(CMD_QUAD_PAGE_PROGRAM_MX),	/* 0x38 */
		ENTRY_3TO4(CMD_FAST_READ_1_1_2),	/* 0x3b */
		ENTRY_3TO4(CMD_FAST_READ_1_1_4),	/* 0x6b */
		ENTRY_3TO4(CMD_FAST_READ_1_2_2),	/* 0xbb */
		ENTRY_3TO4(CMD_SECTOR_ERASE),		/* 0xd8 */
		ENTRY_3TO4(CMD_FAST_READ_1_4_4),	/* 0xeb */
	};
#undef ENTRY_3TO4

	return qspi_flash_convert_opcode(opcode,
					 qspi_flash_3to4_table,
					 ARRAY_SIZE(qspi_flash_3to4_table));
}
#endif /* CONFIG_QSPI_4B_OPCODES */

static int qspi_flash_probe(qspi_flash_t *flash)
{
	const read_id_config_t *config;
	const flash_id_t *info;
	unsigned char id[3]; /* Manufacturer and Device ID */
	char id_str[12], *p;
	int i, ret;

	for (config = configs;
	     (config - configs) < ARRAY_SIZE(configs);
	     ++config) {

		flash->reg_proto	= config->proto;
		flash->read_proto	= config->proto;
		flash->program_proto	= config->proto;
		flash->erase_proto	= config->proto;

		memset(id, 0xff, sizeof(id));
		ret = qspi_flash_read_reg(flash, config->opcode,
					  id, sizeof(id));
		if (ret < 0)
			continue;

		for (info = flash_ids;
		     info - flash_ids < ARRAY_SIZE(flash_ids);
		     ++info)
			if (id[0] == info->manufacturer_id)
				goto found;
	}

	return -1;

found:
	p = id_str;
	for (i = 0; i < sizeof(id); ++i) {
		unsigned char lo = (id[i] & 0x0f) >> 0;
		unsigned char hi = (id[i] & 0xf0) >> 4;

		*p++ = (hi < 10) ? ('0' + hi) : ('a' + hi - 10);
		*p++ = (lo < 10) ? ('0' + lo) : ('a' + lo - 10);
	}
	*p = '\0';
	dbg_info("QSPI Flash: Manufacturer and Device ID: %s\n", id_str);

	/* Set default settings */
	flash->read_opcode = CMD_FAST_READ;
	flash->program_opcode = CMD_PAGE_PROGRAM;
	flash->erase_opcode = CMD_SECTOR_ERASE;

	flash->addr_width = 3;
	flash->sector_size = 0x10000; /* FIXME: depends on the JEDEC ID */

	flash->num_mode_cycles = 0;
	flash->num_dummy_cycles = 8;

	/* Init memory settings */
	ret = (info->init) ? info->init(flash) : 0;

	/* Convert opcodes to their 4byte address version for >16MiB memories */
#ifdef CONFIG_QSPI_4B_OPCODES
	flash->addr_width = 4;
	flash->read_opcode = qspi_flash_3to4_opcode(flash->read_opcode);
	flash->program_opcode = qspi_flash_3to4_opcode(flash->program_opcode);
	flash->erase_opcode = qspi_flash_3to4_opcode(flash->program_opcode);
#endif
	return ret;
}

#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
static int update_image_length(qspi_flash_t *flash,
			       unsigned int offset,
			       unsigned char *dest,
			       unsigned char flag)
{
	unsigned int length = 512;
	int ret;

	ret = qspi_flash_read(flash, offset, dest, length);
	if (ret)
		return -1;

	if (flag == KERNEL_IMAGE)
		return kernel_size(dest);
#ifdef CONFIG_OF_LIBFDT
	else
		return of_get_dt_total_size((void *)dest);
#else
	return -1;
#endif
}
#endif

int qspi_flash_loadimage(struct image_info *image)
{
	qspi_flash_t flash;
	int ret;
#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
	int length;
#endif

	at91_qspi_hw_init();

	qspi_init(AT91C_QSPI_CLK, SPI_MODE0);

	ret = qspi_flash_probe(&flash);
	if (ret)
		return -1;

#if defined(CONFIG_OF_LIBFDT)
	length = update_image_length(&flash,
				     image->of_offset,
				     image->of_dest,
				     DT_BLOB);
	if (length == -1)
		return -1;

	image->of_length = length;

	dbg_info("QSPI Flash: dt blob: Copy %d bytes from %d to %d\n",
		 image->of_length, image->of_offset, image->of_dest);
	ret = qspi_flash_read(&flash,
			      image->of_offset,
			      image->of_dest,
			      image->of_length);
	if (ret)
		return -1;
#endif /* CONFIG_OF_LIBFDT */

#if defined(CONFIG_QSPI_XIP)
	image->dest = qspi_memory_base() + image->offset;
	qspi_flash_read(&flash, 0, NULL, 0);
#else

#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
	length = update_image_length(&flash,
				     image->offset,
				     image->dest,
				     KERNEL_IMAGE);
	if (length == -1)
		return -1;

	image->length = length;
#endif

	dbg_info("QSPI Flash: Copy %d bytes from %d to %d\n",
		 image->length, image->offset, image->dest);
	ret = qspi_flash_read(&flash,
			      image->offset,
			      image->dest,
			      image->length);
	if (ret)
		return -1;
#endif /* !CONFIG_QSPI_XIP */

	return 0;
}
