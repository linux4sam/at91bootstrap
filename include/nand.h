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
#ifndef __NAND_H__
#define __NAND_H__

#define MAX_ECC_BYTES		48 /* maximum bytes of ecc */

struct nand_ooblayout {
	unsigned char	badblockpos;
	unsigned char	eccbytes;
	unsigned char	eccpos[MAX_ECC_BYTES];
	unsigned char	oobavailbytes;
	unsigned char	oobavail_offset;
};

struct nand_chip {
	unsigned short	chip_id; /* Nand Chip ID */
	unsigned short	numblocks;
	unsigned int	blocksize;
	unsigned short	pagesize;
	unsigned char	oobsize;
	unsigned char	buswidth;
};

struct nand_info {
	unsigned int	blocksize;	/* size of a block */
	unsigned int	pagesize;	/* size of a page */
	unsigned int	oobsize;	/* size of a oob */
	unsigned int	sectorsize;	/* size of a sector */

	unsigned int	numblocks;	/* number of blocks in device */
	unsigned int	pages_device;	/* number of pages in device */
	unsigned int	pages_block;	/* number of pages in block */

	unsigned int	buswidth;	/* data bus width (8/16 bits) */

	struct nand_ooblayout	*ecclayout;
};


struct nand_onfi_params {
	/* rev info and features block */
	/* 'O' 'N' 'F' 'I'  */
	unsigned char sig[4];
	unsigned short revision;
	unsigned short features;
	unsigned short opt_cmd;
	unsigned char reserved[22];

	/* manufacturer information block */
	char manufacturer[12];
	char model[20];
	unsigned char jedec_id;
	unsigned short date_code;
	unsigned char reserved2[13];

	/* memory organization block */
	unsigned int byte_per_page;
	unsigned short spare_bytes_per_page;
	unsigned int data_bytes_per_ppage;
	unsigned short spare_bytes_per_ppage;
	unsigned int pages_per_block;
	unsigned int blocks_per_lun;
	unsigned char lun_count;
	unsigned char addr_cycles;
	unsigned char bits_per_cell;
	unsigned short bb_per_lun;
	unsigned short block_endurance;
	unsigned char guaranteed_good_blocks;
	unsigned short guaranteed_block_endurance;
	unsigned char programs_per_page;
	unsigned char ppage_attr;
	unsigned char ecc_bits;
	unsigned char interleaved_bits;
	unsigned char interleaved_ops;
	unsigned char reserved3[13];

	/* electrical parameter block */
	unsigned char io_pin_capacitance_max;
	unsigned short async_timing_mode;
	unsigned short program_cache_timing_mode;
	unsigned short t_prog;
	unsigned short t_bers;
	unsigned short t_r;
	unsigned short t_ccs;
	unsigned short src_sync_timing_mode;
	unsigned short src_ssync_features;
	unsigned short clk_pin_capacitance_typ;
	unsigned short io_pin_capacitance_typ;
	unsigned short input_pin_capacitance_typ;
	unsigned char input_pin_capacitance_max;
	unsigned char driver_strenght_support;
	unsigned short t_int_r;
	unsigned short t_ald;
	unsigned char reserved4[7];

	/* vendor */
	unsigned char reserved5[90];

	unsigned short crc;
} __attribute__((packed));

/*
 * struct nandflash_dev - NAND Flash Device ID Structure
 * @name:	Identify the device type
 * @id:		device ID code
 * @pagesize:	Pagesize in bytes. Either 256 or 512 or 0
 *		If the pagesize is 0, then the real pagesize
 *		and the eraseize are determined from the
 *		extended id bytes in the chip
 * @erasesize:	Size of an erase block in the flash device.
 * @chipsize:	Total chipsize in Mega Bytes
 * @options:	Bitfield to store chip relevant options
 */
struct nandflash_dev {
	char *name;
	int id;
	unsigned long pagesize;
	unsigned long chipsize;
	unsigned long erasesize;
	unsigned long options;
};

#define ZONE_DATA			0x01    /* Sector data zone */
#define ZONE_INFO			0x02    /* Sector info zone */

/* Nand flash chip status codes */
#define STATUS_READY			(0x01 << 6)   /* Status code for Ready */
#define STATUS_ERROR			(0x01 << 0)   /* Status code for Error */

/* Nand flash commands */
#define CMD_READ_1			0x00
#define CMD_READ_2			0x30

#define CMD_READID			0x90

#define CMD_WRITE_1			0x80
#define CMD_WRITE_2			0x10

#define CMD_ERASE_1			0x60
#define CMD_ERASE_2			0xD0

#define CMD_STATUS			0x70
#define CMD_RESET			0xFF

/* Nand flash commands (small blocks) */
#define CMD_READ_A0			0x00
#define CMD_READ_A1			0x01
#define CMD_READ_C			0x50

#define CMD_WRITE_A			0x00
#define CMD_WRITE_C			0x50

/* NandFlash ONFI */
#define CMD_READ_ONFI			0xEC

/* Feature Operations */
#define CMD_SET_FEATURE			0xEF
#define CMD_GET_FEATURE			0xEE

#define ONFI_CRC_BASE			0x4F4E

#define NAND_BUSWIDTH_16		0x00000002

#endif /* #ifndef __NAND_H__ */
