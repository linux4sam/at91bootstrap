/*
 * SPI flash interface
 *
 * Copyright (C) 2008 Atmel Corporation
 * Copyright (C) 2010 Reinhard Meyer, EMK Elektronik
 *
 * Licensed under the GPL-2 or later.
 */

#include "common.h"
#include "spi.h"
#include "spi_flash.h"

#include "debug.h"
/*
#define SPI_FLASH_PROG_TIMEOUT		(2 * CONFIG_SYS_HZ)
#define SPI_FLASH_PAGE_ERASE_TIMEOUT	(5 * CONFIG_SYS_HZ)
#define SPI_FLASH_SECTOR_ERASE_TIMEOUT	(10 * CONFIG_SYS_HZ)
*/
/* Common commands */
#define CMD_READ_ID			0x9f

#define CMD_READ_ARRAY_SLOW		0x03
#define CMD_READ_ARRAY_FAST		0x0b
#define CMD_READ_ARRAY_LEGACY		0xe8

#define CMD_READ_STATUS			0x05
#define CMD_WRITE_ENABLE		0x06

/* Common status */
#define STATUS_WIP			0x01

static void spi_flash_addr(unsigned int addr, unsigned char *cmd)
{
	/* cmd[0] is actual command */
	cmd[1] = addr >> 16;
	cmd[2] = addr >> 8;
	cmd[3] = addr >> 0;
}

static int spi_flash_read_write(struct spi_slave *spi,
				const unsigned char *cmd, 
				unsigned int cmd_len,
				const unsigned char *data_out, 
				unsigned char *data_in,
				unsigned int data_len)
{
	unsigned long flags = SPI_XFER_BEGIN;
	int ret;

	if (data_len == 0)
		flags |= SPI_XFER_END;
	
	ret = spi_xfer(spi, cmd_len * 8, cmd, NULL, flags);
	if (ret) {
		dbg_log(1, "SF: Failed to send command (%zu bytes): %d\n\r", cmd_len, ret);
	} else if (data_len != 0) {
		ret = spi_xfer(spi, data_len * 8, data_out, data_in, SPI_XFER_END);
		if (ret)
			dbg_log(1, "SF: Failed to transfer %zu bytes of data: %d\n", data_len, ret);
	}

	return ret;
}

static int spi_flash_cmd_read(struct spi_slave *spi, const unsigned char *cmd,
		unsigned int cmd_len, void *data, unsigned int data_len)
{
	return spi_flash_read_write(spi, cmd, cmd_len, NULL, data, data_len);
}

static int spi_flash_cmd(struct spi_slave *spi, unsigned char cmd, 
			void *response, unsigned int len)
{
	return spi_flash_cmd_read(spi, &cmd, 1, response, len);
}

static int spi_flash_read_common(struct spi_flash *flash, const unsigned char *cmd,
		unsigned int cmd_len, void *data, unsigned int data_len)
{
	struct spi_slave *spi = flash->spi;
	int ret;

	spi_claim_bus(spi);
	ret = spi_flash_cmd_read(spi, cmd, cmd_len, data, data_len);
	spi_release_bus(spi);

	return ret;
}

static int spi_flash_cmd_read_fast(struct spi_flash *flash, unsigned int offset,
		unsigned int len, void *data)
{
	unsigned char cmd[5];

	cmd[0] = CMD_READ_ARRAY_FAST;
	spi_flash_addr(offset, cmd);
	cmd[4] = 0x00;

	return spi_flash_read_common(flash, cmd, sizeof(cmd), data, len);
}

/*
 * The following table holds all device probe functions
 *
 * shift:  number of continuation bytes before the ID
 * idcode: the expected IDCODE or 0xff for non JEDEC devices
 * probe:  the function to call
 *
 * Non JEDEC devices should be ordered in the table such that
 * the probe functions with best detection algorithms come first.
 *
 * Several matching entries are permitted, they will be tried
 * in sequence until a probe function returns non NULL.
 *
 * IDCODE_CONT_LEN may be redefined if a device needs to declare a
 * larger "shift" value.  IDCODE_PART_LEN generally shouldn't be
 * changed.  This is the max number of bytes probe functions may
 * examine when looking up part-specific identification info.
 *
 * Probe functions will be given the idcode buffer starting at their
 * manu id byte (the "idcode" in the table below).  In other words,
 * all of the continuation bytes will be skipped (the "shift" below).
 */

/* AT45-specific commands */
#define CMD_AT45_READ_STATUS		0xd7
#define CMD_AT45_ERASE_PAGE		0x81
#define CMD_AT45_LOAD_PROG_BUF1		0x82
#define CMD_AT45_LOAD_BUF1		0x84
#define CMD_AT45_LOAD_PROG_BUF2		0x85
#define CMD_AT45_LOAD_BUF2		0x87
#define CMD_AT45_PROG_BUF1		0x88
#define CMD_AT45_PROG_BUF2		0x89

/* AT45 status register bits */
#define AT45_STATUS_P2_PAGE_SIZE	(1 << 0)
#define AT45_STATUS_READY		(1 << 7)

/* AT25-specific commands */
#define CMD_AT25_READ_STATUS		0x05
#define CMD_AT25_WRITE_STATUS		0x01

#define CMD_AT25_BYTE_PAGE_PROGRAM	0x02
#define CMD_AT25_ERASE_BLOCK_4K		0x20
#define CMD_AT25_ERASE_BLOCK_32K	0x52
#define CMD_AT25_ERASE_BLOCK_64K	0xD8

#define CMD_AT25_WRITE_ENABLE	0x06
#define CMD_AT25_WRITE_DISABLE	0x04

/* AT25 status register bits */
#define AT25_STATUS_READYBUSY		(1 << 0)
#define AT25_STATUS_READYBUSY_READY	(0 << 0)
#define AT25_STATUS_READYBUSY_BUSY	(1 << 0)
#define AT25_ERASE_PROGRAM_ERROR	(1 << 5)
#define AT25_STATUS_SWP			(3 << 2)
#define AT25_STATUS_SWP_PROTECTALL	(3 << 2)
#define AT25_STATUS_SWP_PROTECTSOME	(1 << 2)
#define AT25_STATUS_SWP_PROTECTNONE	(0 << 2)
#define AT25_STATUS_SPRL		(1 << 7)
#define AT25_STATUS_SPRL_UNLOCKED	(0 << 7)
#define AT25_STATUS_SPRL_LOCKED		(1 << 7)

#define BLOCK_SIZE_4K		(4 * 1024)

/* DataFlash family IDs, as obtained from the second idcode byte */
#define DF_FAMILY_AT26F			0x00
#define DF_FAMILY_AT45			0x01
#define DF_FAMILY_AT26DF		0x02	/* AT25DF and AT26DF */

static const struct spi_flash_params atmel_spi_flash_table[] = {
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

/* atmel spi flash device */
static struct spi_flash  atmel_flash;

/*
 * Assemble the address part of a command for AT45 devices in
 * non-power-of-two page size mode.
 */
static void at45_build_address(struct spi_flash *flash, 
				unsigned char *cmd, 
				unsigned int offset)
{
	unsigned long page_addr;
	unsigned long byte_addr;
	unsigned long page_size;
	unsigned int page_shift;

	/*
	 * The "extra" space per page is the power-of-two page size
	 * divided by 32.
	 */
	page_shift = flash->params->l2_page_size;
	page_size = (1 << page_shift) + (1 << (page_shift - 5));
	page_shift++;
	page_addr = offset / page_size;
	byte_addr = offset % page_size;

	cmd[0] = page_addr >> (16 - page_shift);
	cmd[1] = page_addr << (page_shift - 8) | (byte_addr >> 8);
	cmd[2] = byte_addr;
}

static int dataflash_read_fast_at45(struct spi_flash *flash,
				unsigned int offset, 
				unsigned int len, void *buf)
{
	unsigned char cmd[5];

	cmd[0] = CMD_READ_ARRAY_FAST;
	at45_build_address(flash, cmd + 1, offset);
	cmd[4] = 0x00;

	return spi_flash_read_common(flash, cmd, sizeof(cmd), buf, len);
}

static struct spi_flash *spi_flash_probe_atmel(struct spi_slave *spi, 
			unsigned char *idcode)
{
	const struct spi_flash_params *params;
	unsigned long page_size;
	unsigned int family;
	struct spi_flash *flash = &atmel_flash;
	unsigned int i;
	int ret;
	unsigned char status;

	for (i = 0; i < ARRAY_SIZE(atmel_spi_flash_table); i++) {
		params = &atmel_spi_flash_table[i];
		if (params->idcode1 == idcode[1])
			break;
	}

	if (i == ARRAY_SIZE(atmel_spi_flash_table)) {
		dbg_log(1, "SF: Unsupported DataFlash ID %02x\n", idcode[1]);
		return NULL;
	}

	flash->params = (struct spi_flash_params *)params;
	flash->spi = spi;
	/* Assuming power-of-two page size initially. */
	page_size = 1 << params->l2_page_size; /* "power of 2" 256 bytes */

	family = idcode[1] >> 5;

	switch (family) {
	case DF_FAMILY_AT45:
		/*
		 * AT45 chips have configurable page size. The status
		 * register indicates which configuration is active.
		 */
		ret = spi_flash_cmd(spi, CMD_AT45_READ_STATUS, &status, 1);
		if (ret)
			goto err;

		dbg_log(1, "SF: AT45 status register: %02x\n", status);

		if (!(status & AT45_STATUS_P2_PAGE_SIZE)) {
			flash->read = dataflash_read_fast_at45;
			page_size += 1 << (params->l2_page_size - 5); /* 264 bytes */
		} else {
			flash->read = spi_flash_cmd_read_fast;
		}
		flash->sector_size = page_size;
		break;

	case DF_FAMILY_AT26F:
	case DF_FAMILY_AT26DF:
		flash->read = spi_flash_cmd_read_fast;
		flash->sector_size = page_size * params->pages_per_block
					* params->blocks_per_sector;
		break;

	default:
		dbg_log(1, "SF: Unsupported DataFlash family %u\n", family);
		goto err;
	}

	flash->size = page_size * params->pages_per_block
				* params->blocks_per_sector
				* params->nr_sectors;

	return flash;

err:
	return NULL;
}

#define IDCODE_LEN	5

struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
		unsigned int clock, unsigned int spi_mode)
{
	struct spi_slave *spi;
	struct spi_flash *flash = NULL;
	int ret, i;
	unsigned char  idcode[IDCODE_LEN];

	spi = spi_setup_slave(bus, cs, clock, spi_mode);
	if (!spi) {
		dbg_log(1, "SF: Failed to set up slave\n\r");
		return NULL;
	}

	ret = spi_claim_bus(spi);
	if (ret) {
		dbg_log(1, "SF: Failed to claim SPI bus: %d\n\r", ret);
		goto err_claim_bus;
	}

	/* Read the ID codes */
	ret = spi_flash_cmd(spi, CMD_READ_ID, idcode, sizeof(idcode));
	if (ret)
		goto err_read_id;

	dbg_log(1, "SF: Got idcodes:");
	for (i = 0; i < IDCODE_LEN; i++)
		dbg_log(1, "0x%x ", idcode[i]);
	dbg_log(1, "\n\r");

	if (idcode[0] == 0x1f) 
		flash = spi_flash_probe_atmel(spi, &idcode[0]);

	if (!flash) {
		dbg_log(1, "SF: Not Atmel spi flash support\n\r");
		goto err_manufacturer_probe;
	}

	dbg_log(1, "SF: Detected %s with sector_size:%d, device size:%d\n\r", 
		flash->params->name, flash->sector_size, flash->size);

	spi_release_bus(spi);

	return flash;

err_manufacturer_probe:
err_read_id:
	spi_release_bus(spi);
err_claim_bus:
	return NULL;
}

