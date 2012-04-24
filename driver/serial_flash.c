/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation

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
#include "spi.h"

#include "debug.h"

/* Common commands */
#define CMD_READ_ID			0x9f

#define CMD_READ_ARRAY_SLOW		0x03
#define CMD_READ_ARRAY_FAST		0x0b
#define CMD_READ_ARRAY_LEGACY		0xe8

/* AT45-specific commands */
#define CMD_AT45_READ_STATUS		0xd7

/* AT45 status register bits */
#define AT45_STATUS_P2_PAGE_SIZE	(1 << 0)
#define AT45_STATUS_READY		(1 << 7)

/* DataFlash family IDs, as obtained from the second idcode byte */
#define DF_FAMILY_AT26F			0x00
#define DF_FAMILY_AT45			0x01
#define DF_FAMILY_AT26DF		0x02	/* AT25DF and AT26DF */

/* struct definiton */
struct serial_flash_params {
	unsigned char	idcode1;
	/* Log2 of page size in power-of-two mode */
	unsigned char	l2_page_size;
	unsigned char	pages_per_block;
	unsigned char	blocks_per_sector;
	unsigned char	nr_sectors;
	const char	*name;
};

typedef int (*serial_flash_read)(unsigned int offset, unsigned int len, void *buf);

static serial_flash_read	sf_read;

static struct serial_flash_params 	atmel_sf_params;

static const struct serial_flash_params atmel_flash_table[] = {
	{
		.idcode1		= 0x22,
		.l2_page_size		= 8,
		.pages_per_block	= 8,
		.blocks_per_sector	= 16,
		.nr_sectors		= 4,
		.name			= "AT45DB011D",
	},
	{
		.idcode1		= 0x23,
		.l2_page_size		= 8,
		.pages_per_block	= 8,
		.blocks_per_sector	= 16,
		.nr_sectors		= 8,
		.name			= "AT45DB021D",
	},
	{
		.idcode1		= 0x24,
		.l2_page_size		= 8,
		.pages_per_block	= 8,
		.blocks_per_sector	= 32,
		.nr_sectors		= 8,
		.name			= "AT45DB041D",
	},
	{
		.idcode1		= 0x25,
		.l2_page_size		= 8,
		.pages_per_block	= 8,
		.blocks_per_sector	= 32,
		.nr_sectors		= 16,
		.name			= "AT45DB081D",
	},
	{
		.idcode1		= 0x26,
		.l2_page_size		= 9,
		.pages_per_block	= 8,
		.blocks_per_sector	= 32,
		.nr_sectors		= 16,
		.name			= "AT45DB161D",
	},
	{
		.idcode1		= 0x27,
		.l2_page_size		= 9,
		.pages_per_block	= 8,
		.blocks_per_sector	= 64,
		.nr_sectors		= 64,
		.name			= "AT45DB321D",
	},
	{
		.idcode1		= 0x28,
		.l2_page_size		= 10,
		.pages_per_block	= 8,
		.blocks_per_sector	= 32,
		.nr_sectors		= 32,
		.name			= "AT45DB642D",
	},
	{
		.idcode1		= 0x47,
		.l2_page_size		= 8,	/* 256 bytes per page */
		.pages_per_block	= 16,	/* 4k bytes per block */
		.blocks_per_sector	= 16,	/* 64k bytes per sector*/
		.nr_sectors		= 64,	/* 64 sectors */
		.name			= "AT25DF321",
	},
};

static int sf_read_write(const unsigned char *cmd, 
			unsigned int cmd_len,
			const unsigned char *data_out, 
			unsigned char *data_in,
			unsigned int data_len)
{
	unsigned long flags = SPI_XFER_BEGIN;
	int ret;

	if (data_len == 0)
		flags |= SPI_XFER_END;

	/* command */
	ret = spi_xfer(cmd_len, cmd, NULL, flags);
	if (ret) 
		dbg_log(1, "SF: Failed to send command (%zu bytes): %d\n\r", cmd_len, ret);
	else if (data_len != 0) { /* data */
		ret = spi_xfer(data_len, data_out, data_in, SPI_XFER_END);
		if (ret)
			dbg_log(1, "SF: Failed to transfer %zu bytes of data: %d\n\r", data_len, ret);
	}

	return ret;
}

static int sf_cmd(unsigned char cmd, void *response, unsigned int len)
{
	return sf_read_write(&cmd, 1, NULL, response, len);
}

static int sf_cmd_read(const unsigned char *cmd, unsigned int cmd_len,
			void *data, unsigned int data_len)
{
	int ret;

	at91_spi_enable();
	ret = sf_read_write(cmd, cmd_len, NULL, data, data_len);
	at91_spi_disable();

	return ret;
}

static int sf_cmd_read_fast(unsigned int offset, unsigned int len, void *buf)
{
	unsigned char cmd[5];

	cmd[0] = CMD_READ_ARRAY_FAST;
	cmd[1] = offset >> 16;
	cmd[2] = offset >> 8;
	cmd[3] = offset >> 0;
	cmd[4] = 0x00;

	return sf_cmd_read(cmd, sizeof(cmd), buf, len);
}

/*
 * Assemble the address part of a command for AT45 devices in
 * non-power-of-two page size mode.
 */
static void at45_build_address(	unsigned char *cmd, unsigned int offset)
{
	const struct serial_flash_params *sf_params = &atmel_sf_params;
	unsigned long page_addr;
	unsigned long byte_addr;
	unsigned long page_size;
	unsigned int page_shift;

	/*
	 * The "extra" space per page is the power-of-two page size
	 * divided by 32.
	 */
	page_shift = sf_params->l2_page_size;
	page_size = (1 << page_shift) + (1 << (page_shift - 5));
	page_shift++;
	page_addr = offset / page_size;
	byte_addr = offset % page_size;

	cmd[0] = page_addr >> (16 - page_shift);
	cmd[1] = page_addr << (page_shift - 8) | (byte_addr >> 8);
	cmd[2] = byte_addr;
}

static int dataflash_read_fast_at45(unsigned int offset, 
				unsigned int len, void *buf)
{
	unsigned char cmd[5];

	cmd[0] = CMD_READ_ARRAY_FAST;
	at45_build_address(cmd + 1, offset);
	cmd[4] = 0x00;

	return sf_cmd_read(cmd, sizeof(cmd), buf, len);
}

static int sf_cmd_read_id(unsigned char *idcode, unsigned int idcode_len)
{
	int ret;
	unsigned int i;

	/* Read the ID codes */
	ret = sf_cmd(CMD_READ_ID, idcode, idcode_len);
	if (ret)
		return -1;
	
	unsigned char *p = idcode;

	dbg_log(1, "SF: Got idcodes:");
	for (i = 0; i < idcode_len; i++)
		dbg_log(1, "%d ", *p++);
	dbg_log(1, "\n\r");

	return 0;
}

static int sf_cmd_read_status_at45(unsigned char *page_256)
{
	unsigned char status;
	int ret;

	ret = sf_cmd(CMD_AT45_READ_STATUS, &status, 1);
	if (ret)
		return -1;

	dbg_log(1, "SF: AT45 status register: %02x\n", status);

	if ((status & AT45_STATUS_P2_PAGE_SIZE))
		*page_256 = 1;
	else
		*page_256 = 0;
	
	return 0;
}

#define IDCODE_LEN	5
#define MANU_ID_ATMEL	0x1F

static int atmel_sf_probe(unsigned int clock, unsigned int spi_mode)
{
	const struct serial_flash_params *sf_params = &atmel_sf_params;
	const struct serial_flash_params *params;
	unsigned char idcode[IDCODE_LEN];
	unsigned char manu_id;
	unsigned int family;
	unsigned int i;
	int ret;
	unsigned char page_256;

	ret = at91_spi_init(clock, spi_mode);
	if (ret) {
		dbg_log(1, "SF: Failed to init SPI bus\n\r");
		return -1;
	}

	ret = at91_spi_enable();
	if (ret) {
		dbg_log(1, "SF: Failed to enable SPI bus\n\r");
		return -1;
	}

	/* Read the ID codes */
	ret = sf_cmd_read_id(idcode, sizeof(idcode));
	if (ret)
		goto err;
	
	manu_id = idcode[0];
	if (manu_id == MANU_ID_ATMEL){ /* Manufacturer ID:0x1F = Atmel */
		for (i = 0; i < ARRAY_SIZE(atmel_flash_table); i++) {
			params = &atmel_flash_table[i];
			if (params->idcode1 == idcode[1])	/* Device ID */
				break;
		}

		if (i == ARRAY_SIZE(atmel_flash_table)) {
			dbg_log(1, "SF: Unsupported SerialFlash ID %02x\n", idcode[1]);
			goto err;
		}

		sf_params = (struct serial_flash_params *)params;

		family = idcode[1] >> 5;	/* Family Code */

		switch (family) {
		case DF_FAMILY_AT45:
			/*
			 * AT45 chips have configurable page size. The status
		 	 * register indicates which configuration is active.
		 	 */
			ret = sf_cmd_read_status_at45(&page_256);
			if (ret)
				goto err;

			if (page_256 == 0)
				sf_read = dataflash_read_fast_at45;
			else
				sf_read = sf_cmd_read_fast;
			break;

		case DF_FAMILY_AT26F:
		case DF_FAMILY_AT26DF:
			sf_read = sf_cmd_read_fast;
			break;

		default:
			dbg_log(1, "SF: Unsupported SerialFlash family %d\n\r", family);
			goto err;
		}

	} else {
		dbg_log(1, "SF: Unsupported SerialFlash Manufacturer ID %d\n\r", manu_id);
		goto err;
	}

	dbg_log(1, "SF: Detected flash %s\n\r", sf_params->name);

	at91_spi_disable();

	return 0;

err:
	at91_spi_disable();

	return -1;
}

int load_dataflash(unsigned int offset, unsigned int size, unsigned char *dest)
{
	int ret;

	at91_spi0_hw_init();

	ret = atmel_sf_probe(CONFIG_SYS_SPI_CLOCK, CONFIG_SYS_SPI_MODE);
	if (ret) {
		dbg_log(1, "SF: Fail to probe atmel serial flash\n\r");
		return -1;
	}

	dbg_log(1, "SF: Copy %d bytes from %d to %d\n\r", size, offset, dest);

	ret = (*sf_read)(offset, size, dest);
	if (ret) {
		dbg_log(1, "** SF: Serial flash read error**\n\r");
		return -1;
	}

	return 0;
}
