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

/*
 *	Chip ID list
 *
 *	Name. ID code, pagesize, chipsize in MegaByte, eraseblock size,
 *	options
 *
 *	Pagesize; 0, 256, 512
 *	0	get this information from the extended chip ID
 *	256	256 Byte page size
 *	512	512 Byte page size
 */
const struct nandflash_dev nandflash_ids[] = {
	{"NAND 16MiB 1,8V 8-bit",	0x33, 512, 16, 0x4000, 0},
	{"NAND 16MiB 3,3V 8-bit",	0x73, 512, 16, 0x4000, 0},
	{"NAND 16MiB 1,8V 16-bit",	0x43, 512, 16, 0x4000, NAND_BUSWIDTH_16},
	{"NAND 16MiB 3,3V 16-bit",	0x53, 512, 16, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 32MiB 1,8V 8-bit",	0x35, 512, 32, 0x4000, 0},
	{"NAND 32MiB 3,3V 8-bit",	0x75, 512, 32, 0x4000, 0},
	{"NAND 32MiB 1,8V 16-bit",	0x45, 512, 32, 0x4000, NAND_BUSWIDTH_16},
	{"NAND 32MiB 3,3V 16-bit",	0x55, 512, 32, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 64MiB 1,8V 8-bit",	0x36, 512, 64, 0x4000, 0},
	{"NAND 64MiB 3,3V 8-bit",	0x76, 512, 64, 0x4000, 0},
	{"NAND 64MiB 1,8V 16-bit",	0x46, 512, 64, 0x4000, NAND_BUSWIDTH_16},
	{"NAND 64MiB 3,3V 16-bit",	0x56, 512, 64, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 128MiB 1,8V 8-bit",	0x78, 512, 128, 0x4000, 0},
	{"NAND 128MiB 1,8V 8-bit",	0x39, 512, 128, 0x4000, 0},
	{"NAND 128MiB 3,3V 8-bit",	0x79, 512, 128, 0x4000, 0},
	{"NAND 128MiB 1,8V 16-bit",	0x72, 512, 128, 0x4000, NAND_BUSWIDTH_16},
	{"NAND 128MiB 1,8V 16-bit",	0x49, 512, 128, 0x4000, NAND_BUSWIDTH_16},
	{"NAND 128MiB 3,3V 16-bit",	0x74, 512, 128, 0x4000, NAND_BUSWIDTH_16},
	{"NAND 128MiB 3,3V 16-bit",	0x59, 512, 128, 0x4000, NAND_BUSWIDTH_16},

	{"NAND 256MiB 3,3V 8-bit",	0x71, 512, 256, 0x4000, 0},

	/*
	 * These are the new chips with large page size. The pagesize and the
	 * erasesize is determined from the extended id bytes
	 */
	/*512 Megabit */
	{"NAND 64MiB 1,8V 8-bit",	0xA2, 0,  64, 0, 0},
	{"NAND 64MiB 3,3V 8-bit",	0xF2, 0,  64, 0, 0},
	{"NAND 64MiB 1,8V 16-bit",	0xB2, 0,  64, 0, NAND_BUSWIDTH_16},
	{"NAND 64MiB 3,3V 16-bit",	0xC2, 0,  64, 0, NAND_BUSWIDTH_16},

	/* 1 Gigabit */
	{"NAND 128MiB 1,8V 8-bit",	0xA1, 0, 128, 0, 0},
	{"NAND 128MiB 3,3V 8-bit",	0xF1, 0, 128, 0, 0},
	{"NAND 128MiB 3,3V 8-bit",	0xD1, 0, 128, 0, 0},
	{"NAND 128MiB 1,8V 16-bit",	0xB1, 0, 128, 0, NAND_BUSWIDTH_16},
	{"NAND 128MiB 3,3V 16-bit",	0xC1, 0, 128, 0, NAND_BUSWIDTH_16},

	/* 2 Gigabit */
	{"NAND 256MiB 1,8V 8-bit",	0xAA, 0, 256, 0, 0},
	{"NAND 256MiB 3,3V 8-bit",	0xDA, 0, 256, 0, 0},
	{"NAND 256MiB 1,8V 16-bit",	0xBA, 0, 256, 0, NAND_BUSWIDTH_16},
	{"NAND 256MiB 3,3V 16-bit",	0xCA, 0, 256, 0, NAND_BUSWIDTH_16},

	/* 4 Gigabit */
	{"NAND 512MiB 1,8V 8-bit",	0xAC, 0, 512, 0, 0},
	{"NAND 512MiB 3,3V 8-bit",	0xDC, 0, 512, 0, 0},
	{"NAND 512MiB 1,8V 16-bit",	0xBC, 0, 512, 0, NAND_BUSWIDTH_16},
	{"NAND 512MiB 3,3V 16-bit",	0xCC, 0, 512, 0, NAND_BUSWIDTH_16},

	/* 8 Gigabit */
	{"NAND 1GiB 1,8V 8-bit",	0xA3, 0, 1024, 0, 0},
	{"NAND 1GiB 3,3V 8-bit",	0xD3, 0, 1024, 0, 0},
	{"NAND 1GiB 1,8V 8-bit",	0x38, 0, 1024, 0, 0},
	{"NAND 1GiB 1,8V 16-bit",	0xB3, 0, 1024, 0, NAND_BUSWIDTH_16},
	{"NAND 1GiB 3,3V 16-bit",	0xC3, 0, 1024, 0, NAND_BUSWIDTH_16},

	/* 16 Gigabit */
	{"NAND 2GiB 1,8V 8-bit",	0xA5, 0, 2048, 0, 0},
	{"NAND 2GiB 3,3V 8-bit",	0xD5, 0, 2048, 0, 0},
	{"NAND 2GiB 1,8V 16-bit",	0xB5, 0, 2048, 0, NAND_BUSWIDTH_16},
	{"NAND 2GiB 3,3V 16-bit",	0xC5, 0, 2048, 0, NAND_BUSWIDTH_16},

	/*
	 * Renesas AND 1 Gigabit. Those chips do not support extended id and
	 * have a strange page/block layout !  The chosen minimum erasesize is
	 * 4 * 2 * 2048 = 16384 Byte, as those chips have an array of 4 page
	 * planes 1 block = 2 pages, but due to plane arrangement the blocks
	 * 0-3 consists of page 0 + 4,1 + 5, 2 + 6, 3 + 7 Anyway JFFS2 would
	 * increase the eraseblock size so we chose a combined one which can be
	 * erased in one go There are more speed improvements for reads and
	 * writes possible, but not implemented now
	 */
	{NULL,}
};

