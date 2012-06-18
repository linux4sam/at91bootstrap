/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
#include "arch/at91_pio.h"
#include "gpio.h"
#include "debug.h"
#include "nand.h"
#include "hamming.h"

#define ECC_CORRECT_ERROR  0xfe

/* ooblayout for 2048 byte pages */
struct nand_ooblayout ooblayout_2048 = {
	/* Bad block marker is at position */
	0,
	/* 24 ecc bytes */
	24,
	/* ecc byte positions */
	{40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
	52, 53, 54, 55, 56, 57,
	 58, 59, 60, 61, 62, 63},
	/* 38 extra bytes */
	38,
	/* extra byte positions */
	{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
	 34, 35, 36, 37, 38, 39}
};

static struct nand_chip nand_ids[] = {
	{0xecda, 0x800, 0x20000, 0x800, 0x40, 0x0, &ooblayout_2048},
	{0x2cca, 0x800, 0x20000, 0x800, 0x40, 0x1, &ooblayout_2048},
	{0x2cda, 0x800, 0x20000, 0x800, 0x40, 0x0, &ooblayout_2048},
	{0,}
};

/*
 * NAND Commands
 */
static unsigned char *IO_ADDR_R =
		(unsigned char *)(unsigned long)CONFIG_SYS_NAND_BASE;
static unsigned char *IO_ADDR_W =
		(unsigned char *)(unsigned long)CONFIG_SYS_NAND_BASE;

/* 8 bits devices */
static void nand_command(unsigned char cmd)
{
	writeb(cmd, ((unsigned long)IO_ADDR_W | CONFIG_SYS_NAND_MASK_CLE));
}

static void nand_address(unsigned char addr)
{
	writeb(addr, ((unsigned long)IO_ADDR_W | CONFIG_SYS_NAND_MASK_ALE));
}

static unsigned char read_byte(void)
{
	return readb((unsigned long)IO_ADDR_R);
}

#if 0
/* 16 bits devices */
static void nand_command16(unsigned short cmd)
{
	writew(cmd, (unsigned long)IO_ADDR_W | CONFIG_SYS_NAND_MASK_CLE);
}

static void nand_address16(unsigned short addr)
{
	writew(addr, (unsigned long)IO_ADDR_W | CONFIG_SYS_NAND_MASK_ALE);
}
#endif

static unsigned short read_word(void)
{
	return readw((unsigned long)IO_ADDR_R);
}

static void nand_wait_ready(void)
{
	/*while (pio_get_value(nandflash_get_ready_pin()) != 1);*/
	while (1) {
		if (pio_get_value(nandflash_get_ready_pin()) == 1)
			break;

	}
}

static void nand_cs_enable(void)
{
	pio_set_value(CONFIG_SYS_NAND_ENABLE_PIN, 0);
}

static void nand_cs_disable(void)
{
	pio_set_value(CONFIG_SYS_NAND_ENABLE_PIN, 1);
}

static void nand_info_init(struct nand_info *nand, struct nand_chip *chip)
{
	unsigned int pagesize, i = 0;

	/* number of blocks in device */
	nand->numblocks = chip->numblocks;
	/* number of data bytes in a block */
	nand->blocksize = chip->blocksize;
	/* number of bytes in page area */
	nand->pagesize = chip->pagesize;
	/* number of bytes in oob area */
	nand->oobsize = chip->oobsize;
	/* Total number of bytes in a sector */
	nand->sectorsize = nand->pagesize + nand->oobsize;
	nand->ecclayout = chip->ecclayout;
	nand->buswidth = chip->buswidth;	/* Data Bus Width */

	pagesize = nand->pagesize - 1;
	nand->page_shift = 0;
	while (pagesize >> i) {
		nand->page_shift++;
		i++;
	}

	if (nand->buswidth)
		nand->badblockpos = 2 * nand->ecclayout->badblockpos;
	else
		nand->badblockpos = nand->ecclayout->badblockpos;
}

static void nandflash_reset(void)
{
	unsigned int timeout = 200000;

	nand_cs_enable();
	nand_command(CMD_RESET);

	nand_wait_ready();

	nand_command(CMD_STATUS);
	nand_command(-1);
	/*while( (!(read_byte() & STATUS_READY)) && timeout--);*/
	while (1) {
		if ((read_byte() & STATUS_READY) || (!timeout--))
			break;
	}
	nand_cs_disable();
}

static struct nand_chip *nand_find_type(void)
{
	unsigned int chipid, i = 0;
	unsigned char manf_id, dev_id;
	struct nand_chip *chip = NULL;

	nand_cs_enable();
	nand_command(CMD_READID);
	nand_address(0x0);

	manf_id = read_byte();
	dev_id = read_byte();

	nand_cs_disable();

	chipid = (manf_id << 8) | dev_id;

	while (nand_ids[i].chip_id != 0) {
		if (nand_ids[i].chip_id == chipid) {
			chip = &nand_ids[i];
			break;
		}
		i++;
	}

	return chip;
}

static int nandflash_get_type(struct nand_info *nand)
{
	struct nand_chip *chip = 0;

	nandflash_reset();

	chip = nand_find_type();

	nand_info_init(nand, chip);

	if (nand->buswidth == 0)
		nandflash_config_buswidth(0);
	else
		nandflash_config_buswidth(1);

	return 0;
}

static void send_large_block_address(unsigned int addr)
{
	nand_address((addr >> 0) & 0xFF);
	nand_address((addr >> 8) & 0xFF);
}

static void send_sector_address(unsigned int addr)
{
	send_large_block_address(addr);
	nand_address((addr >> 16) & 0xFF);
}

#ifdef NANDFLASH_SMALL_BLOCKS
static int nand_read_sector(struct nand_info *nand,
				unsigned int sectoraddr,
				unsigned char *buffer,
				unsigned int zone_flag)
{
	unsigned int readbytes, i;
	unsigned char command;

	/*
	 * WARNING : During a read procedure you can't call
	 * the ReadStatus flash cmd. The ReadStatus fill the read register
	 *  with 0xC0 and then corrupt the read
	 */
	switch (zone_flag) {
	case ZONE_DATA:
		readbytes = nand->pagesize;
		command = CMD_READ_A0;
		break;
	case ZONE_INFO:
		readbytes = nand->oobsize;
		buffer += nand->pagesize;
		command = CMD_READ_C;
		break;
	case ZONE_DATA | ZONE_INFO:
		readbytes = nand->sectorsize;
		command = CMD_READ_A0;
		break;
	default:
		return -1;
	}

	nand_cs_enable();

	/* Write specific command, Read from start */
	if (nand->buswidth) /* 16 bits */
		nand_command16(command);
	else
		nand_command(command);

	sectoraddr >>= nand->page_shift;

	if (nand->buswidth) { /* 16 bits */
		nand_address16(0x00);
		nand_address16((sectoraddr >> 0) & 0xFF);
		nand_address16((sectoraddr >> 8) & 0xFF);
		nand_address16((sectoraddr >> 16) & 0xFF);
	} else {
		nand_address(0x00);
		nand_address((sectoraddr >> 0) & 0xFF);
		nand_address((sectoraddr >> 8) & 0xFF);
		nand_address((sectoraddr >> 16) & 0xFF);
	}

	/* Wait for flash to be ready */
	nand_wait_ready();

	/* Read loop */
	if (nand->buswidth) /* 16bits */
		for (i = 0; i < readbytes / 2; i++) {
			*((short *)buffer) = read_word();
			buffer += 2;
		}
	else /* 8 bits */
		if (command == CMD_READ_C)
			for (i = 0; i < readbytes; i++) {
				*buffer = read_byte();
				buffer++;
			}
		else {
			for (i = 0; i < readbytes / 2; i++) {
				*buffer = read_byte();
				buffer++;
			}

			command = CMD_READ_A1;
			nand_command(command);
			nand_address(0x00);
			nand_address((sectoraddr >> 0) & 0xFF);
			nand_address((sectoraddr >> 8) & 0xFF);
			nand_address((sectoraddr >> 16) & 0xFF);

			/* Need to be done twice, READY detected too early the first time? */
			nand_wait_ready();

			for (i = 0; i < (readbytes / 2); i++) {
				*buffer = read_byte();
				buffer++;
			}
		}
	}

	nand_cs_disable();

	return 0;
}

#else /* For large blocks */
static int nand_read_sector(struct nand_info *nand,
				unsigned int sectoraddr,
				unsigned char *buffer,
				unsigned int zone_flag)
{
	unsigned int readbytes, i;
	unsigned int address;
	int ret = 0;

	address = 0x00;
	switch (zone_flag) {
	case ZONE_DATA:
		readbytes = nand->pagesize;
		break;

	case ZONE_INFO:
		readbytes = nand->oobsize;
		buffer += nand->pagesize;
		address = nand->pagesize;
		if (nand->buswidth)		/* 16 bits */
			address = address / 2;
		break;

	case ZONE_DATA | ZONE_INFO:
		readbytes = nand->sectorsize;
		break;

	default:
		return -1;
	}
	/*
	 * WARNING : During a read procedure you can't call
	 * the ReadStatus flash cmd. The ReadStatus fill the read register
	 * with 0xC0 and then corrupt the read
	 */
	nand_cs_enable();

	nand_command(CMD_READ_1);

	send_large_block_address(address);
	sectoraddr >>= nand->page_shift;
	send_sector_address(sectoraddr);

	nand_command(CMD_READ_2);

	/* Wait for flash to be ready */
	nand_wait_ready();

	/* Read loop */
	if (nand->buswidth)
		for (i = 0; i < readbytes / 2; i++) {
			*((short *)buffer) = read_word();
			buffer += 2;
		}
	else
		for (i = 0; i < readbytes; i++)
			*buffer++ = read_byte();

	nand_cs_disable();

	return ret;
}
#endif /* #ifdef NANDFLASH_SMALL_BLOCKS */

static int nand_check_badblock(struct nand_info *nand,
				unsigned int block,
				unsigned char *buffer)
{
	unsigned int i = 0;
	unsigned int sectoraddr = block * nand->blocksize;

	/* Read the first page and second page oob zone to detect bad block */
	for (i = 0; i < 2; i++) {
		nand_read_sector(nand, sectoraddr + i * nand->pagesize,
		buffer, ZONE_INFO);
		if (*(buffer + nand->pagesize + nand->badblockpos) != 0xFF)
			return -1;
	}

	return 0;
}

static void nand_read_ecc(struct nand_ooblayout *ooblayout,
				unsigned char *buffer,
				unsigned char *ecc)
{
	unsigned int i;

	for (i = 0; i < ooblayout->eccbytes; i++)
		ecc[i] = buffer[ooblayout->eccpos[i]];
}

static int nand_read_page(struct nand_info *nand,
				unsigned int block,
				unsigned int page,
				unsigned int zone_flag,
				unsigned char *buffer)
{
	int retval;
	unsigned char hamming[48];
	unsigned char error;
	unsigned int sectoraddr = block * nand->blocksize + page * nand->pagesize;

	if (nand_check_badblock(nand, block, buffer)) {
		dbg_log(1, "Bad block: #%d\n\r", block);
		return -1;
	}

	retval = nand_read_sector(nand, sectoraddr, buffer,
			ZONE_DATA | ZONE_INFO);

	if (retval)
		return -1;

	nand_read_ecc(nand->ecclayout, buffer + nand->pagesize, hamming);

	error = Hamming_Verify256x(buffer, nand->pagesize, hamming);
	if (error && (error != Hamming_ERROR_SINGLEBIT)) {
		dbg_log(1, "Hamming ECC error!\n\r");
		return ECC_CORRECT_ERROR;
	}

	return 0;
}

#ifdef CONFIG_NANDFLASH_RECOVERY
static int nand_erase_block0(void)
{
	unsigned int block = 0;

	nand_cs_enable();

	nand_command(CMD_ERASE_1);
	send_sector_address(block);
	nand_command(CMD_ERASE_2);

	/* Wait for nand to be ready */
	nand_wait_ready();

	/* Check status bit for error notification */
	nand_command(CMD_STATUS);

	nand_wait_ready();
	if (read_byte() & STATUS_ERROR)
		return -1;

	nand_cs_disable();

	return 0;
}

static int nandflash_recovery(void)
{
	/*
	 * If Recovery Button is pressed during boot sequence,
	 * erase nandflash block0
	*/
	if ((pio_get_value(CONFIG_SYS_RECOVERY_BUTTON_PIN)) == 0) {
		dbg_log(1, "Nand: The recovery button (%s) is pressed\n\r",
		RECOVERY_BUTTON_NAME);
		dbg_log(1, "Nand: The block 0 is erasing ...\n\r");

		nand_erase_block0();

		dbg_log(1, "Nand: The erasing is done\n\r");
		return 0;
	}
	return 1;
}
#endif /* #ifdef CONFIG_NANDFLASH_RECOVERY */

int load_nandflash(struct image_info *img_info)
{
	struct nand_info nand;
	unsigned int offset = img_info->offset;
	unsigned int size = img_info->length;
	unsigned char *buffer = img_info->dest;

	unsigned int block, length, readsize, numpage, page;
	int ret;

	nandflash_hw_init();

	if (nandflash_get_type(&nand))
		return -1;

#ifdef CONFIG_NANDFLASH_RECOVERY
	if (nandflash_recovery() == 0)
		return -2;
#endif

	dbg_log(1, "Nand: Copy %d bytes from %d to %d\r\n",
		size, offset, buffer);

	block = offset / nand.blocksize;
	length = size;
	while (length > 0) {
		/* read a buffer corresponding to a block in the origin file */
		if (length < nand.blocksize)
			readsize = length;
		else
			readsize = nand.blocksize;

		/* Adjust the number of sectors to read */
		numpage = readsize / nand.pagesize;
		if (readsize % nand.pagesize)
			numpage++;

		/* Loop until a valid block has been read */
		while (1) {
			for (page = 0; page < numpage; page++) {
				ret = nand_read_page(&nand, block, page, ZONE_DATA, buffer);
				if (ret == ECC_CORRECT_ERROR)
					return -1;
				else if (ret == -1) /* skip this block */
					break;
				else
					buffer += nand.pagesize;
			}
			block++;

			if (page >= numpage)
				break;
		}
		length -= readsize;
	}

	return 0;
}
