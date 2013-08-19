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
#include "arch/at91_nand_ecc.h"
#include "gpio.h"

#include "debug.h"

#include "nand.h"
#include "hamming.h"
#include "timer.h"
#include "div.h"

static struct nand_chip nand_ids[] = {
	/* Samsung K9F2G08U0M 256MB */
	{0xecda, 0x800, 0x20000, 0x800, 0x40, 0x0},
	/* Samsung K9F2G08U0A 256MB */
	{0xecaa, 0x800, 0x20000, 0x800, 0x40, 0x0},
	/* Micron MT29F2G16AAB 256MB */
	{0x2cca, 0x800, 0x20000, 0x800, 0x40, 0x1},
	/* Micron MT29F2G08AAC 256MB  */
	{0x2cda, 0x800, 0x20000, 0x800, 0x40, 0x0},
	/* Micron MT29F2G08ABD 256MB */
	{0x2caa, 0x800, 0x20000, 0x800, 0x40, 0x0},
	/* Hynix HY27UF082G2A 256MB */
	{0xadda, 0x800, 0x20000, 0x800, 0x40, 0x0},
	/* Hynix HY27UF162G2A 256MB */
	{0xadca, 0x800, 0x20000, 0x800, 0x40, 0x1},
	/* Mircon MT29H8G08ACAH1 1GB */
	{0x2c38, 0x800, 0x80000, 0x1000, 0xe0, 0x0},
	/* EON EN27LN1G08 128MB */
	{0x92f1, 0x400, 0x20000, 0x800, 0x40, 0x0},
	{0,}
};

#ifdef CONFIG_USE_PMECC

#define TT_MAX			25

/* The PMECC descripter structure */
struct _PMECC_paramDesc_struct {
	unsigned int pageSize;
	unsigned int spareSize;
	unsigned int sectorSize;	// 0 for 512, 1 for 1024 bytes, like in PMECCFG register
	unsigned int errBitNbrCapability;
	unsigned int eccSizeByte;
	unsigned int eccStartAddress;
	unsigned int eccEndAddress;

	unsigned int nandWR;
	unsigned int spareEna;
	unsigned int modeAuto;
	unsigned int clkCtrl;
	unsigned int interrupt;

	int tt;
	int mm;
	int nn;

	short *alpha_to;
	short *index_of;

	short partialSyn[100];
	short si[100];

	/* sigma table */
	short smu[TT_MAX + 2][2 * TT_MAX + 1];
	/* polynom order */
	short lmu[TT_MAX + 1];

} PMECC_paramDesc;

static int pmecc_readl(unsigned int reg)
{
	return(readl(AT91C_BASE_PMECC + reg));
}

static void pmecc_writel(unsigned int value, unsigned reg)
{
	writel(value, (AT91C_BASE_PMECC + reg));
}

static int pmecclor_readl(unsigned int reg)
{
	return readl(AT91C_BASE_PMERRLOC + reg);
}

static void pmecclor_writel(unsigned int value, unsigned reg)
{
	writel(value, (AT91C_BASE_PMERRLOC + reg));
}

/*
 * Return 1 means valid pmecc error bits & sector size. otherwise return 0;
 */
static int is_valid_pmecc_params()
{
	int ret = 1;
	switch (PMECC_ERROR_CORR_BITS) {
	case 2:
	case 4:
	case 8:
	case 12:
	case 24:
		break;
	default:
		dbg_log(DEBUG_INFO, "Invalid Pmecc error bits: %d. Should " \
			"be 2, 4, 8, 12 or 24.\r\n", PMECC_ERROR_CORR_BITS);
		ret = 0;
	}

	if (PMECC_SECTOR_SIZE != 512 && PMECC_SECTOR_SIZE != 1024) {
		dbg_log(DEBUG_INFO, "Invalid Pmecc sector size: %d. Should " \
				"be 512 or 1024.\r\n", PMECC_SECTOR_SIZE);
		ret = 0;
	}

	return ret;
}

/*
 * Return number of ecc bytes per sector according to sector size and
 * correction capability
 *
 * Following table shows what at91 PMECC supported:
 * Correction Capability	Sector_512_bytes	Sector_1024_bytes
 * =====================	================	=================
 *                2-bits                 4-bytes                  4-bytes
 *                4-bits                 7-bytes                  7-bytes
 *                8-bits                13-bytes                 14-bytes
 *               12-bits                20-bytes                 21-bytes
 *               24-bits                39-bytes                 42-bytes
 */
static int get_pmecc_bytes()
{
	int i;
	int error_corr_bits[] =		{2, 4, 8,  12, 24};
	int ecc_bytes_sec_512[] =	{4, 7, 13, 20, 39};
	int ecc_bytes_sec_1024[] =	{4, 7, 14, 21, 42};

	int ecc_bytes = 0;
	for (i = 0; i < 5; i++) {
		if (error_corr_bits[i] == PMECC_ERROR_CORR_BITS) {
			/* find out the index */
			ecc_bytes = (PMECC_SECTOR_SIZE == 512) ?
				ecc_bytes_sec_512[i] : ecc_bytes_sec_1024[i];
			break;
		}
	}

	return ecc_bytes;	/* 0 indicate not found */
}

#endif /* #ifdef CONFIG_USE_PMECC */

/* ooblayout */
static struct nand_ooblayout nand_oob_layout;

static struct nand_chip nand_chip_default;

/*
 * NAND Commands
 */

/* 8 bits devices */
static void nand_command(unsigned char cmd)
{
	volatile unsigned long ioaddr = (unsigned long)CONFIG_SYS_NAND_BASE
						| CONFIG_SYS_NAND_MASK_CLE;

	writeb(cmd, ioaddr);
}

static void nand_address(unsigned char addr)
{
	volatile unsigned long ioaddr = (unsigned long)CONFIG_SYS_NAND_BASE
						| CONFIG_SYS_NAND_MASK_ALE;

	writeb(addr, ioaddr);
}

static unsigned char read_byte(void)
{
	return(readb((unsigned long)CONFIG_SYS_NAND_BASE));
}

static void write_byte(unsigned char data)
{
	writeb(data, (unsigned long)CONFIG_SYS_NAND_BASE);
}

/* 16 bits devices */
static void nand_command16(unsigned short cmd)
{
	volatile unsigned long ioaddr = (unsigned long)CONFIG_SYS_NAND_BASE
						| CONFIG_SYS_NAND_MASK_CLE;

	writew(cmd, ioaddr);
}

static void nand_address16(unsigned short addr)
{
	volatile unsigned long ioaddr = (unsigned long)CONFIG_SYS_NAND_BASE
						| CONFIG_SYS_NAND_MASK_ALE;

	writew(addr, ioaddr);
}

static unsigned short read_word(void)
{
	return(readw((unsigned long)CONFIG_SYS_NAND_BASE));
}

static void nand_wait_ready(void)
{
	unsigned int timeout = 10000;

	nand_command(CMD_STATUS);
	while ((!(read_byte() & STATUS_READY)) && timeout--)
		;
}

static void nand_cs_enable(void)
{
#ifdef CONFIG_SYS_NAND_ENABLE_PIN
	pio_set_value(CONFIG_SYS_NAND_ENABLE_PIN, 0);
#endif
}

static void nand_cs_disable(void)
{
#ifdef CONFIG_SYS_NAND_ENABLE_PIN
	pio_set_value(CONFIG_SYS_NAND_ENABLE_PIN, 1);
#endif
}

static void config_nand_ooblayout(struct nand_ooblayout *layout, struct nand_chip *chip)
{
	unsigned int i;
	unsigned int oobsize = 0;

	switch (chip->pagesize) {
	case 256:
		layout->badblockpos = 5;
		layout->eccbytes = 3;
		layout->oobavail_offset = 6;
		oobsize = chip->oobsize;
		break;

	case 512:
		layout->badblockpos = 5;
		layout->eccbytes = 6;
		layout->oobavail_offset = 6;
		oobsize = chip->oobsize;
		break;

	case 2048:
		layout->badblockpos = 0;
		oobsize = chip->oobsize;
#ifdef CONFIG_USE_PMECC
		layout->eccbytes = chip->pagesize / PMECC_SECTOR_SIZE
			* get_pmecc_bytes();
#else
		layout->eccbytes = 24;
#endif
		layout->oobavail_offset = 1;
		break;

	case 4096:
		layout->badblockpos = 0;
#ifdef CONFIG_USE_PMECC
		layout->eccbytes = chip->pagesize / PMECC_SECTOR_SIZE
			* get_pmecc_bytes();
		oobsize = chip->oobsize;
#else
		layout->eccbytes = 48;
		oobsize = 128;
#endif
		layout->oobavail_offset = 1;
		break;

	default:
		break;
	}

	for (i = 0; i < layout->eccbytes; i++)
		layout->eccpos[i] = oobsize - layout->eccbytes + i;

	layout->oobavailbytes = oobsize - layout->eccbytes
					- layout->oobavail_offset;
}

static void nand_set_feature_on_die_ecc(unsigned char is_enable)
{
	unsigned char i;

	nand_cs_enable();

	nand_command(CMD_SET_FEATURE);
	nand_address(0x90);

	if (is_enable)
		write_byte(0x08);
	else
		write_byte(0x00);

	for (i = 0; i < 3; i++)
		write_byte(0x00);

	nand_cs_disable();
}

static unsigned char nand_get_feature_on_die_ecc(void)
{
	unsigned char buffer[4];
	unsigned char i;

	nand_cs_enable();

	nand_command(CMD_GET_FEATURE);
	nand_address(0x90);

	for (i = 0; i < 4; i++)
		buffer[i] = read_byte();

	nand_cs_disable();

	return buffer[0];
}

#define ENABLE_ECC	0x08

static int nand_set_on_die_ecc(unsigned char is_enable)
{
	unsigned char status;

	status = (nand_get_feature_on_die_ecc() & ENABLE_ECC) ? 1 : 0;
	if (is_enable == status)
		return 0;

	nand_set_feature_on_die_ecc(is_enable);
	status = (nand_get_feature_on_die_ecc() & ENABLE_ECC) ? 1 : 0;
	if (is_enable == status)
		return 0;

	return -1;
}

static int nand_init_on_die_ecc(void)
{
	unsigned char is_enable;

#ifdef CONFIG_ON_DIE_ECC
	is_enable = 1;
#else
	is_enable = 0;
#endif
	if (nand_set_on_die_ecc(is_enable)) {
		dbg_log(1, "WARNING: Fail to %s On-Die ECC\n\r",
				is_enable ? "enable" : "disable");

		return -1;
	} else {
		dbg_log(1, "NAND: %s On-Die ECC\n\r",
				is_enable ? "Enable" : "Disable");
		return 0;
	}
}

static unsigned short onfi_crc16(unsigned short crc,
				unsigned char const *p,
				unsigned int len)
{
	int i;

	while (len--) {
		crc ^= *p++ << 8;
		for (i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
	}

	return crc;
}

#define ONFI_PARAMS_SIZE		256

#define PARAMS_OFFSET_BUSWIDTH		6
#define PARAMS_OFFSET_MODEL		49
#define PARAMS_OFFSET_JEDEC_ID		64
#define PARAMS_OFFSET_PAGESIZE		80
#define PARAMS_OFFSET_OOBSIZE		84
#define PARAMS_OFFSET_BLOCKSIZE		92
#define PARAMS_OFFSET_NBBLOCKS		96
#define PARAMS_OFFSET_ECC_BITS		112
#define PARAMS_OFFSET_CRC		254

#define ONFI_CRC_BASE			0x4F4E

static int nandflash_detect_onfi(struct nand_chip *chip)
{
	unsigned char onfi_ind[4];
	unsigned char onfi_params[ONFI_PARAMS_SIZE];
	unsigned char *p = onfi_params;
	unsigned char *param;
	int i, j;
	unsigned short crc;
	unsigned char manf_id, dev_id;

	nand_cs_enable();
	nand_command(CMD_READID);
	nand_address(0x20);

	onfi_ind[0] = read_byte();
	onfi_ind[1] = read_byte();
	onfi_ind[2] = read_byte();
	onfi_ind[3] = read_byte();
	nand_cs_disable();

	if ((onfi_ind[0] != 'O')
		|| (onfi_ind[1] != 'N')
		|| (onfi_ind[2] != 'F')
		|| (onfi_ind[3] != 'I')) {
		dbg_log(1, "NAND: ONFI not supported\n\r");
		return -1;
	}

	dbg_log(1, "NAND: ONFI flash detected\n\r");

	nand_cs_enable();

	nand_command(CMD_READ_ONFI);
	nand_address(0x00);
	
	nand_wait_ready();
	nand_command(CMD_READ_1);
	
	for (i = 0; i < 3; i++) {
		param = onfi_params;
		/* Read the onfi parameter table */
		for (j = 0; j < ONFI_PARAMS_SIZE; j++)
			*param++ = read_byte();

		crc = *(unsigned short *)(p + PARAMS_OFFSET_CRC);
		if (onfi_crc16(ONFI_CRC_BASE, (unsigned char *)p, 254) == crc)
			break;
	}

	nand_cs_disable();

	if (i == 3) {
		dbg_log(1, "NAND: ONFI para CRC error!\n\r");
		return -1;
	}

	chip->numblocks = *(unsigned short *)(p + PARAMS_OFFSET_NBBLOCKS);
	chip->pagesize	= *(unsigned short *)(p + PARAMS_OFFSET_PAGESIZE);
	chip->blocksize = *(unsigned int  *)(p + PARAMS_OFFSET_BLOCKSIZE)
							* chip->pagesize;
	chip->oobsize	= *(unsigned char *)(p + PARAMS_OFFSET_OOBSIZE);
	chip->buswidth	= (*(unsigned char *)(p + PARAMS_OFFSET_BUSWIDTH))
								& 0x01;

	manf_id = *(unsigned char *)(p + PARAMS_OFFSET_JEDEC_ID);
	dev_id = *(unsigned char *)(p + PARAMS_OFFSET_MODEL);
	dbg_log(1, "NAND: Manufacturer ID: %d Chip ID: %d\n\r", manf_id, dev_id);

	return 0;
}

static int nandflash_detect_non_onfi(struct nand_chip *chip)
{
	int manf_id, dev_id;
	unsigned int chipid;
	unsigned int i;

	nand_cs_enable();

	/* Reading device ID */
	nand_command(CMD_READID);
	nand_address(0x00);

	manf_id  = read_byte();
	dev_id   = read_byte();

	chipid = (manf_id << 8) | dev_id;

	for (i = 0; i < ARRAY_SIZE(nand_ids); i++) {
		if (chipid == nand_ids[i].chip_id)
			break;
	}

	if (i == ARRAY_SIZE(nand_ids)) {
		dbg_log(1, "NAND: Not found Manufacturer ID: %d," \
			"Chip ID: 0x%d\n\r", manf_id, dev_id);

		return -1;
	}

	dbg_log(1, "NAND: Manufacturer ID: %d Chip ID: %d\n\r",
						manf_id, dev_id);

	chip->pagesize	= nand_ids[i].pagesize;
	chip->blocksize = nand_ids[i].blocksize;
	chip->oobsize	= nand_ids[i].oobsize;
	chip->buswidth	= nand_ids[i].buswidth;
	chip->numblocks = nand_ids[i].numblocks;

	return 0;
}

static void nand_info_init(struct nand_info *nand, struct nand_chip *chip)
{
	/* number of blocks in device */
	nand->numblocks = chip->numblocks;
	/* number of data bytes in a block */
	nand->blocksize = chip->blocksize;
	/* number of bytes in page area */
	nand->pagesize = chip->pagesize;
	/* number of pages in block */
	nand->pages_block = div(nand->blocksize, nand->pagesize);
	/* number of pages in device */
	nand->pages_device = nand->numblocks * nand->pages_block;
	/* number of bytes in oob area */
	nand->oobsize = chip->oobsize;
	/* Total number of bytes in a sector */
	nand->sectorsize = nand->pagesize + nand->oobsize;
	/* the layout of the spare area */
	config_nand_ooblayout(&nand_oob_layout, chip);
	nand->ecclayout = &nand_oob_layout;
	/* data bus width (8/16 bits) */
	nand->buswidth = chip->buswidth;
	if (nand->buswidth)
		nand->ecclayout->badblockpos *= 2;
}

static void nandflash_reset(void)
{
	nand_cs_enable();

	nand_command(CMD_RESET);

	nand_wait_ready();

	nand_cs_disable();
}

static int nandflash_get_type(struct nand_info *nand)
{
	struct nand_chip *chip = &nand_chip_default;
	int ret;

	nandflash_reset();

	/* Check if the Nandflash is ONFI compliant */
	ret = nandflash_detect_onfi(chip);
	if (ret == -1) {
		if (nandflash_detect_non_onfi(chip)) {
			dbg_log(1, "NAND: Not find support device!\n\r");
			return -1;
		}
	}

	if (nand_init_on_die_ecc())
		return -1;

	nand_info_init(nand, chip);
	
	if (nand->buswidth == 0)
		nandflash_config_buswidth(0);
	else
		nandflash_config_buswidth(1);

	return 0;
}

#ifdef CONFIG_USE_PMECC

static int init_pmecc_descripter(struct _PMECC_paramDesc_struct *pmecc_params,
				struct nand_info *nand)
{
	unsigned int sectors;

	if ((nand->pagesize == 2048) || (nand->pagesize == 4096)) {
		/* Sector Size */
		pmecc_params->sectorSize = (PMECC_SECTOR_SIZE == 512) ?
			AT91C_PMECC_SECTORSZ_512 : AT91C_PMECC_SECTORSZ_1024;

		pmecc_params->nandWR = AT91C_PMECC_NANDWR_0;
		pmecc_params->spareEna = AT91C_PMECC_SPAREENA_DIS;
		pmecc_params->modeAuto = AT91C_PMECC_AUTO_DIS;

		pmecc_params->spareSize = nand->oobsize;
		pmecc_params->eccSizeByte = nand->ecclayout->eccbytes;
		pmecc_params->eccStartAddress = nand->ecclayout->eccpos[0];
		pmecc_params->eccEndAddress
		= nand->ecclayout->eccpos[nand->ecclayout->eccbytes - 1];

		/* At 133Mhz, this field must be programmed with 2 */
		pmecc_params->clkCtrl = 2;

		pmecc_params->interrupt = 0;
		pmecc_params->tt = PMECC_ERROR_CORR_BITS;
		pmecc_params->mm = (PMECC_SECTOR_SIZE == 512) ? 13 : 14;
		pmecc_params->nn = (1 << pmecc_params->mm) - 1;

		if (PMECC_SECTOR_SIZE == 512) {
			pmecc_params->alpha_to = (short *)(AT91C_BASE_ROM
						+ CONFIG_LOOKUP_TABLE_ALPHA_OFFSET);
			pmecc_params->index_of = (short *)(AT91C_BASE_ROM
						+ CONFIG_LOOKUP_TABLE_INDEX_OFFSET);
		} else {
			pmecc_params->alpha_to = (short *)(AT91C_BASE_ROM
						+ CONFIG_LOOKUP_TABLE_ALPHA_OFFSET_1024);
			pmecc_params->index_of = (short *)(AT91C_BASE_ROM
						+ CONFIG_LOOKUP_TABLE_INDEX_OFFSET_1024);
		}

		/* Error Correct Capability */
		switch (PMECC_ERROR_CORR_BITS) {
		case 2:
			pmecc_params->errBitNbrCapability
						= AT91C_PMECC_BCH_ERR2;
			break;
		case 4:
			pmecc_params->errBitNbrCapability
						= AT91C_PMECC_BCH_ERR4;
			break;
		case 8:
			pmecc_params->errBitNbrCapability
						= AT91C_PMECC_BCH_ERR8;
			break;
		case 12:
			pmecc_params->errBitNbrCapability
						= AT91C_PMECC_BCH_ERR12;
			break;
		case 24:
			pmecc_params->errBitNbrCapability
						= AT91C_PMECC_BCH_ERR24;
			break;
		default:
			dbg_log(1, "PMECC: Invalid error correctable " \
				"bits: %d\n\r",	PMECC_ERROR_CORR_BITS);
			return -1;
		}

		/* Number of Sectors in the Page */
		sectors = div(nand->pagesize, PMECC_SECTOR_SIZE);
		if (sectors == 1) {
			pmecc_params->pageSize = AT91C_PMECC_PAGESIZE_1SEC;
		} else if (sectors == 2) {
			pmecc_params->pageSize = AT91C_PMECC_PAGESIZE_2SEC;
		} else if (sectors == 4) {
			pmecc_params->pageSize = AT91C_PMECC_PAGESIZE_4SEC;
		} else if (sectors == 8) {
			pmecc_params->pageSize = AT91C_PMECC_PAGESIZE_8SEC;
		} else {
			dbg_log(1, "PMECC: Not supported sector size: %d\n\r",
				sectors);
			return -1;
		}

		dbg_log(DEBUG_LOUD, "PMECC: page_size: %u, oob_size: %u, " \
					"pmecc_cap: %u, sector_size: %u\r\n",
			nand->pagesize, nand->oobsize, pmecc_params->tt,
			pmecc_params->sectorSize
				== AT91C_PMECC_SECTORSZ_512 ? 512 : 1024);

		return 0;
	} else {
		dbg_log(1, "PMECC: Not supported page size: %d\n\r",
							nand->pagesize);
		return -1;
	}
} 

static int init_pmecc_core(struct _PMECC_paramDesc_struct *pmecc_params)
{
	pmecc_writel(AT91C_PMECC_DISABLE, PMECC_CTRL);
	pmecc_writel(AT91C_PMECC_RST, PMECC_CTRL);

	pmecc_writel(pmecc_params->errBitNbrCapability |
		pmecc_params->sectorSize |
		pmecc_params->pageSize |
		pmecc_params->nandWR |
		pmecc_params->spareEna |
		pmecc_params->modeAuto, PMECC_CFG);
		
	pmecc_writel((pmecc_params->spareSize - 1), PMECC_SAREA);
	pmecc_writel(pmecc_params->eccStartAddress, PMECC_SADDR);
	pmecc_writel(pmecc_params->eccEndAddress, PMECC_EADDR);
	pmecc_writel(pmecc_params->clkCtrl, PMECC_CLK);
	pmecc_writel(0xff, PMECC_IDR);

	pmecc_writel(AT91C_PMECC_ENABLE, PMECC_CTRL);

	return 0;
}

static int init_pmecc(struct nand_info *nand)
{
	/* sanity check for the pmecc sector size and error bits */
	if (!is_valid_pmecc_params())
		return -1;

	if (init_pmecc_descripter(&PMECC_paramDesc, nand) != 0)
		return -1;

	dbg_log(1, "NAND: Initialize PMECC params, cap: %d, sector: %d\n\r",
			PMECC_ERROR_CORR_BITS, PMECC_SECTOR_SIZE);

	init_pmecc_core(&PMECC_paramDesc);

	return 0;
}
#endif /* #ifdef CONFIG_USE_PMECC */

static void write_column_address(struct nand_info *nand,
				unsigned int column_address)
{
	volatile unsigned int page_size = nand->pagesize;

	if (nand->buswidth)
		column_address >>= 1;

	while (page_size > 2) {
		if (nand->buswidth)
			nand_address16(column_address & 0xff);
		else
			nand_address(column_address & 0xff);

		page_size >>= 8;
		column_address >>= 8;
	}
}

static void write_row_address(struct nand_info *nand,
				unsigned int row_address)
{
	volatile unsigned int num_pages = nand->pages_device;

	while(num_pages) {
		if (nand->buswidth)
			nand_address16(row_address & 0xff);
		else
			nand_address(row_address & 0xff);

		num_pages >>= 8;
		row_address >>= 8;
	}
}

#ifdef CONFIG_USE_PMECC
static int check_pmecc_ecc_data(struct nand_info *nand,
				unsigned char *buffer)
{
	unsigned int i;
	unsigned char *ecc_data = buffer + nand->pagesize
				+ nand->ecclayout->eccpos[0];

	for (i = 0; i < nand->ecclayout->eccbytes; i++)
		if (*ecc_data++ != 0xff)
			break;

	if (i >= nand->ecclayout->eccbytes)
		return -1;
	else
		return 0;
}

/*
 * \brief Build the pseudo syndromes table
 * \param pPmeccDescriptor Pointer to a PMECC_paramDesc instance.
 * \param sector Targetted sector.
 */

static void GenSyn(unsigned long pPMECC,
		struct _PMECC_paramDesc_struct *pPmeccDescriptor,
		unsigned int sector)
{
	short *pRemainer;
	unsigned int index;

	pRemainer = (short *) (pPMECC + PMECC_REM + (sector * 0x40));

	for (index = 0; index < pPmeccDescriptor->tt; index++)
		/* Fill odd syndromes */
		pPmeccDescriptor->partialSyn[1 +  (2 * index)]
						= pRemainer[index];
}

/**
 * \brief The substitute function evaluates the polynomial remainder,
 * with different values of the field primitive elements.
 * \param pPmeccDescriptor Pointer to a PMECC_paramDesc instance.
 */
static int substitute(struct _PMECC_paramDesc_struct *pPmeccDescriptor)
{
	int i, j;
	short *si;
	short *pPartialSyn = pPmeccDescriptor->partialSyn;
	short *alpha_to = pPmeccDescriptor->alpha_to;
	short *index_of = pPmeccDescriptor->index_of;

	/*
	 * si[] is a table that holds the current syndrome value,
	 * an element of that table belongs to the field.
	 */
	si = pPmeccDescriptor->si;

	for (i = 1; i < 2 * TT_MAX; i++)
		si[i] = 0;

	/* Computation 2t syndromes based on S(x) */
	/* Odd syndromes */
	for (i = 1; i <= 2 * pPmeccDescriptor->tt - 1; i = i + 2) {
		si[i] = 0;
		for (j = 0; j < pPmeccDescriptor->mm; j++) {
			if (pPartialSyn[i] & ((unsigned short)0x1 << j))
				si[i] = alpha_to[(i * j)] ^ si[i];
		}
	}
	/* Even syndrome = (Odd syndrome) ** 2 */
	for (i = 2; i <= 2 * pPmeccDescriptor->tt; i = i + 2) {
		j = i / 2;
		if (si[j] == 0)
			si[i] = 0;
		else
			si[i] = alpha_to[mod((2 * index_of[si[j]]),
				(unsigned int)pPmeccDescriptor->nn)];
	}

	return 0;
}

/*
 * \brief The substitute function finding the value of the error
 * location polynomial.
 * \param pPmeccDescriptor Pointer to a PMECC_paramDesc instance.
 */
static unsigned int get_sigma(struct _PMECC_paramDesc_struct *pPmeccDescriptor)
{
	unsigned int dmu_0_count;
	int i, j, k;
	short *lmu = pPmeccDescriptor->lmu;
	short *si = pPmeccDescriptor->si;
	short tt = pPmeccDescriptor->tt;

	/* mu  */
	int mu[TT_MAX+1];

	/* discrepancy */
	int dmu[TT_MAX+1];

	/* delta order   */
	int delta[TT_MAX+1];

	/* index of largest delta */
	int ro;
	int largest;
	int diff;

	dmu_0_count = 0;

	/* First Row  */

	/* Mu */
	mu[0]  = -1;
	/* Actually -1/2 */
	/* Sigma(x) set to 1 */

	for (i = 0; i < (2 * TT_MAX + 1); i++)
		pPmeccDescriptor->smu[0][i] = 0;

	pPmeccDescriptor->smu[0][0] = 1;

	/* discrepancy set to 1 */
	dmu[0] = 1;

	/* polynom order set to 0 */
	lmu[0] = 0;

	/* delta set to -1 */
	delta[0]  = (mu[0] * 2 - lmu[0]) >> 1;

	/*                     */
	/*     Second Row      */
	/*                     */

	/* Mu */
	mu[1]  = 0;

	/* Sigma(x) set to 1 */
	for (i = 0; i < (2 * TT_MAX + 1); i++)
		pPmeccDescriptor->smu[1][i] = 0;

	pPmeccDescriptor->smu[1][0] = 1;

	/* discrepancy set to S1 */
	dmu[1] = si[1];

	/* polynom order set to 0 */
	lmu[1] = 0;

	/* delta set to 0 */
	delta[1]  = (mu[1] * 2 - lmu[1]) >> 1;

	/* Init the Sigma(x) last row */
	for (i = 0; i < (2 * TT_MAX + 1); i++)
		pPmeccDescriptor->smu[tt + 1][i] = 0;

	for (i = 1; i <= tt; i++) {
		mu[i+1] = i << 1;
		/* Compute Sigma (Mu+1)             */
		/* And L(mu)                        */
		/* check if discrepancy is set to 0 */
		if (dmu[i] == 0) {
			dmu_0_count++;
			if ((tt - (lmu[i] >> 1) - 1) & 0x1) {
				if (dmu_0_count
					== ((tt - (lmu[i] >> 1) - 1) / 2) + 2) {
					for (j = 0; j <= (lmu[i] >> 1) + 1; j++)
						pPmeccDescriptor->smu[tt+1][j]
						= pPmeccDescriptor->smu[i][j];

					lmu[tt + 1] = lmu[i];
					return 0;
				}
			} else {
				if (dmu_0_count
					== ((tt - (lmu[i] >> 1) - 1) / 2) + 1) {
					for (j = 0; j <= (lmu[i] >> 1) + 1; j++)
						pPmeccDescriptor->smu[tt + 1][j]
						= pPmeccDescriptor->smu[i][j];

					lmu[tt + 1] = lmu[i];
					return 0;
				}
			}

			/* copy polynom */
			for (j = 0; j <= lmu[i] >> 1; j++)
				pPmeccDescriptor->smu[i + 1][j]
						= pPmeccDescriptor->smu[i][j];

			/* copy previous polynom order to the next */
			lmu[i + 1] = lmu[i];
		} else {
			ro = 0;
			largest = -1;
			/* find largest delta with dmu != 0 */
			for (j = 0; j < i; j++) {
				if (dmu[j]) {
					if (delta[j] > largest) {
						largest = delta[j];
						ro = j;
					}
				}
			}

			/* compute difference */
			diff = (mu[i] - mu[ro]);

			/* Compute degree of the new smu polynomial */
			if ((lmu[i]>>1) > ((lmu[ro]>>1) + diff))
				lmu[i + 1] = lmu[i];
			else
				lmu[i + 1] = ((lmu[ro]>>1) + diff) * 2;

			/* Init smu[i+1] with 0 */
			for (k = 0; k < (2 * TT_MAX+1); k++)
				pPmeccDescriptor->smu[i+1][k] = 0;

			/* Compute smu[i+1] */
			for (k = 0; k <= lmu[ro]>>1; k++)
				if (pPmeccDescriptor->smu[ro][k] && dmu[i])
					pPmeccDescriptor->smu[i + 1][k + diff] = pPmeccDescriptor->alpha_to[mod((pPmeccDescriptor->index_of[dmu[i]]
						+ (pPmeccDescriptor->nn	- pPmeccDescriptor->index_of[dmu[ro]])
						+ pPmeccDescriptor->index_of[pPmeccDescriptor->smu[ro][k]]), (unsigned int)pPmeccDescriptor->nn)];

			for (k = 0; k <= lmu[i]>>1; k++)
				pPmeccDescriptor->smu[i+1][k] ^= pPmeccDescriptor->smu[i][k];
		}

		/*************************************************/
		/*                                               */
		/*      End Compute Sigma (Mu+1)                 */
		/*      And L(mu)                                */
		/*************************************************/
		/* In either case compute delta */
		delta[i + 1]  = (mu[i + 1] * 2 - lmu[i + 1]) >> 1;

		/* Do not compute discrepancy for the last iteration */
		if (i < tt) {
			for (k = 0 ; k <= (lmu[i + 1] >> 1); k++) {
				if (k == 0)
					dmu[i + 1] = si[2 * (i - 1) + 3];
				/*
				 * check if one operand of the multiplier
				 * is null, its index is -1
				 */
				else if (pPmeccDescriptor->smu[i+1][k] && si[2 * (i - 1) + 3 - k])
					dmu[i + 1] = pPmeccDescriptor->alpha_to[mod((pPmeccDescriptor->index_of[pPmeccDescriptor->smu[i + 1][k]]
							+ pPmeccDescriptor->index_of[si[2 * (i - 1) + 3 - k]]), (unsigned int)pPmeccDescriptor->nn)] ^ dmu[i + 1];
			}
		}
	}
	return 0;
}

/*
 * \brief Init the PMECC Error Location peripheral and start the error
 *        location processing
 * \param pPmeccDescriptor Pointer to a PMECC_paramDesc instance.
 * \param SectorSizeInBits Size of the sector in bits.
 * \return Number of errors
 */
static int ErrorLocation(unsigned long pPMERRLOC,
		struct _PMECC_paramDesc_struct *pPmeccDescriptor,
		unsigned int SectorSizeInBits)
{
	unsigned int alphax;
	unsigned int *pSigma;
	unsigned int errorNumber;
	unsigned int NbrOfRoots;

	/* Disable PMECC Error Location IP */
	pmecclor_writel(0xFFFFFFFF, PMERRLOC_ELDIS);

	errorNumber = 0;
	alphax = 0;

	pSigma = (unsigned int *) (pPMERRLOC + PMERRLOC_SIGMA0);

	for (alphax = 0;
		alphax <= pPmeccDescriptor->lmu[pPmeccDescriptor->tt + 1] >> 1;
		alphax++) {
		*pSigma++ = pPmeccDescriptor->smu[pPmeccDescriptor->tt + 1][alphax];
		errorNumber++;
	}

	pmecclor_writel(((errorNumber - 1) << 16)
			| pmecclor_readl(PMERRLOC_ELCFG), PMERRLOC_ELCFG);
	/* Enable error location process */
	pmecclor_writel(SectorSizeInBits, PMERRLOC_ELEN);

	while ((pmecclor_readl(PMERRLOC_ELISR) & PMERRLOC_ELISR_DONE) == 0);

	NbrOfRoots = (pmecclor_readl(PMERRLOC_ELISR)
				& PMERRLOC_ELISR_ERR_CNT) >> 8;
	/* Number of roots == degree of smu hence <= tt */
	if (NbrOfRoots == pPmeccDescriptor->lmu[pPmeccDescriptor->tt + 1] >> 1)
		return errorNumber - 1;

	/* Number of roots not match the degree of smu ==> unable to correct error */
	return -1;
}

/*
 * \brief Correct errors indicated in the PMECCEL error location registers.
 * \param sectorBaseAddress Base address of the sector.
 * \param ExtraBytes Number of extra bytes of the sector.
 * (encoded Spare Area, only for the last sector)
 * \param ErrorNbr Number of error to correct
 * \return Number of errors
 */
static unsigned int ErrorCorrection(unsigned long pPMERRLOC,
			struct _PMECC_paramDesc_struct *pPmeccDescriptor,
			unsigned int sectorBaseAddress,
			unsigned int eccBaseAddress,
			unsigned int ExtraBytes,
			unsigned int ErrorNbr)
{
	unsigned int *pErrPos;
	unsigned int bytePos;
	unsigned int bitPos;
	unsigned int sectorSize = PMECC_SECTOR_SIZE;

	pErrPos = (unsigned int *)(pPMERRLOC + PMERRLOC_EL0);

	while (ErrorNbr) {
		bytePos = (*pErrPos - 1) / 8;
		bitPos = (*pErrPos - 1) % 8;
		unsigned char *errByte;

		if (bytePos < sectorSize) {
			/* If error is located in the data area(not in ECC) */
			errByte = (unsigned char *)(sectorBaseAddress + bytePos);
			dbg_log(1, "Correct error bit @[#Byte %u,Bit# %u] " \
				"%u -> %u\n\r",
				(unsigned int)bytePos,
				(unsigned int)bitPos,
				*errByte,
				*errByte ^ (1 << bitPos));
			*errByte ^= (1 << bitPos);
		} else {
			/* error is located in oob area */
			errByte = (unsigned char *)(eccBaseAddress
					+ (bytePos - sectorSize));
			dbg_log(1, "Correct error bit in OOB @[#Byte %u,Bit# %u]" \
				" %u -> %u\n\r",
				(unsigned int)bytePos - sectorSize,
				(unsigned int)bitPos,
				(*errByte),
				*errByte ^ (1 << bitPos));
			*errByte ^= (1 << bitPos);
		}

		pErrPos++;
		ErrorNbr--;
	}
	return 0;
}

/**
 * \brief Launch error detection functions and correct corrupted bits.
 * \param pPmeccDescriptor Pointer to a PMECC_paramDesc instance.
 * \param pmeccStatus Value of the PMECC status register.
 * \param pageBuffer Base address of the buffer
 * 	containing the page to be corrected.
 * \param ErrorNbr Number of error to correct
 * \return 0 if all errors have been corrected, 1 if too many errors detected
 */
unsigned int PMECC_CorrectionAlgo(unsigned long pPMECC,
		unsigned long pPMERRLOC,
		struct _PMECC_paramDesc_struct *pPmeccDescriptor,
		unsigned int pmeccStatus,
		void *pageBuffer)
{
	unsigned int sectorNumber = 0;
	unsigned int sectorBaseAddress, eccBaseAddr;
	volatile int errorNbr;
	unsigned int sector_num_per_page, page_size_byte, ecc_byte_per_sector;

	/* Set the sector size (512 or 1024 bytes) */
	pmecclor_writel((pPmeccDescriptor->sectorSize >> 4), PMERRLOC_ELCFG);

	sector_num_per_page = div(pPmeccDescriptor->eccSizeByte,
					get_pmecc_bytes());
	page_size_byte = sector_num_per_page * PMECC_SECTOR_SIZE;
	ecc_byte_per_sector = get_pmecc_bytes();

	while (sectorNumber < sector_num_per_page) {

		errorNbr = 0;
		if (pmeccStatus & 0x1) {

			sectorBaseAddress = (unsigned int)pageBuffer
					+ (sectorNumber * PMECC_SECTOR_SIZE);
			eccBaseAddr = (unsigned int)pageBuffer
					+ page_size_byte
					+ pmecc_readl(PMECC_SADDR)
					+ (sectorNumber * ecc_byte_per_sector);

			GenSyn(pPMECC, pPmeccDescriptor, sectorNumber);

			substitute(pPmeccDescriptor);

			get_sigma(pPmeccDescriptor);
			errorNbr = ErrorLocation(pPMERRLOC,
					pPmeccDescriptor,
					(((pPmeccDescriptor->sectorSize >> 4) + 1) * 512 * 8)
					+ (pPmeccDescriptor->tt
						* (13 + (pPmeccDescriptor->sectorSize >> 4))));

			if (errorNbr == -1)
				return 1;	/* uncorrectable errors */
			else
				ErrorCorrection(pPMERRLOC,
						pPmeccDescriptor,
						sectorBaseAddress,
						eccBaseAddr,
						ecc_byte_per_sector,
						errorNbr);
		}
		sectorNumber++;
		pmeccStatus = pmeccStatus >> 1;
	}

	return 0;
}

void buf_dump(unsigned char *buf, int offset, int len)
{
	int i = 0;
	for (i = 0; i < len; i++) {
		if (i % 16 == 0)
			dbg_log(DEBUG_LOUD, "\r\n");
		dbg_log(DEBUG_LOUD, "%u ", buf[offset + i]);
	}
}

void page_dump(unsigned char *buf, int page_size, int oob_size)
{
	dbg_log(DEBUG_LOUD, "Dump Error Page: Data:\r\n");
	buf_dump(buf, 0, page_size);
	dbg_log(DEBUG_LOUD, "\r\nOOB:\r\n");
	buf_dump(buf, page_size, oob_size);
	dbg_log(DEBUG_LOUD, "\r\n");
}

static int pmecc_process(struct nand_info *nand, unsigned char *buffer)
{
	int ret = 0;
	int result;
	unsigned int erris;

	/* waiting for PMECC ready */
	while (pmecc_readl(PMECC_SR) & AT91C_PMECC_BUSY);

	/* read corrupted bit status */
	erris = pmecc_readl(PMECC_ISR);
	if (erris) {
		if (check_pmecc_ecc_data(nand, buffer) == -1){
			return 0;
		}

		/* erris means which sector has errors. for example:
		 * if erris is 0x9 (0b1001)
		 *                    ^  ^
		 * the bit 1 indicate the position of error sectors.
		 * If we have 4 sectors, then that means the first
		 * and last sector has errors.
		 */
		dbg_log(1, "PMECC: sector bits = %d, bit 1 means " \
			"corrupted sector, Now correcting...\n\r", erris);
		result = PMECC_CorrectionAlgo(AT91C_BASE_PMECC,
					AT91C_BASE_PMERRLOC,
					&PMECC_paramDesc,
					erris,
					buffer);

		if (result != 0) {
			dbg_log(1, "PMECC: failed to " \
					"correct corrupted bits!\n\r");
			ret =  -1;

			/* dump the whole page for test */
			page_dump(buffer, nand->pagesize, nand->oobsize);
		}
	}

	return ret;
}
#endif /* #ifdef CONFIG_USE_PMECC */

static int nand_read_status(void)
{
	unsigned int timeout = 1000;
	unsigned char status;

	do {
		nand_command(CMD_STATUS);
		status = read_byte();
		if (status & STATUS_READY)
			break;
	} while (--timeout);

	if (!timeout)
		return -1;

#ifdef CONFIG_ON_DIE_ECC
	if (status & STATUS_ERROR) {
		dbg_log(1, "WARNING: Read On-Die ECC error\n\r");
		return -1;
	}
#endif

	return 0;
}

#ifdef NANDFLASH_SMALL_BLOCKS
static int nand_read_sector(struct nand_info *nand, 
			unsigned int row_address,
			unsigned char *buffer,
			unsigned int zone_flag)
{
	unsigned int readbytes, i;
	unsigned char command;

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
	if (nand->buswidth)
		nand_command16(command);
	else
		nand_command(command);

	if (nand->buswidth) {
		nand_address16(0x00);
		nand_address16((row_address >> 0) & 0xff);
		nand_address16((row_address >> 8) & 0xff);
		nand_address16((row_address >> 16) & 0xff);
	} else {
		nand_address(0x00);
		nand_address((row_address >> 0) & 0xff);
		nand_address((row_address >> 8) & 0xff);
		nand_address((row_address >> 16) & 0xff);
	}

	if (nand_read_status())
		return -1;

	if (nand->buswidth)
		nand_command16(CMD_READ_A0);
	else
		nand_command(CMD_READ_A0);

	/* Read loop */
	if (nand->buswidth) {
		for (i = 0; i < readbytes / 2; i++) {
			*((short *)buffer) = read_word();
			buffer += 2;
		}
	} else {
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

			nand_command(CMD_READ_A1);
			nand_address(0x00);
			nand_address((row_address >> 0) & 0xff);
			nand_address((row_address >> 8) & 0xff);
			nand_address((row_address >> 16) & 0xff);

			nand_wait_ready();
			nand_command(CMD_READ_A0);

			for (i = 0; i < (readbytes / 2); i++) {
				*buffer = read_byte();
				buffer++;
			}
		}
	}

	nand_cs_disable();

	return 0;
}

#else /* large blocks */
static int nand_read_sector(struct nand_info *nand,
				unsigned int row_address,
				unsigned char *buffer, 
				unsigned int zone_flag)
{
	unsigned int readbytes, i;
	unsigned int column_address;
	int ret = 0;
	unsigned char *pbuf = buffer;

#ifdef CONFIG_USE_PMECC
	unsigned int usepmecc = 0;

	if ((zone_flag & ZONE_DATA) == ZONE_DATA) {
		usepmecc = 1;
		zone_flag = ZONE_DATA | ZONE_INFO;

		pmecc_writel(AT91C_PMECC_RST, PMECC_CTRL);
		pmecc_writel((pmecc_readl(PMECC_CFG) | AT91C_PMECC_AUTO_ENA),
				PMECC_CFG);
		pmecc_writel(AT91C_PMECC_ENABLE, PMECC_CTRL);
	}
#endif	/* #ifdef CONFIG_USE_PMECC */

	switch (zone_flag) {
	case ZONE_DATA:
		readbytes = nand->pagesize;
		column_address = 0x00;
		break;

	case ZONE_INFO:
		readbytes = nand->oobsize;
		pbuf += nand->pagesize;
		column_address = nand->pagesize;
		break;

	case ZONE_DATA | ZONE_INFO:
		readbytes = nand->sectorsize;
		column_address = 0x00;
		break;

	default:
		return -1;
	}

	nand_cs_enable();

	if (nand->buswidth)
		nand_command16(CMD_READ_1);
	else
		nand_command(CMD_READ_1);

	write_column_address(nand, column_address);
	write_row_address(nand, row_address);

	if (nand->buswidth)
		nand_command16(CMD_READ_2);
	else
		nand_command(CMD_READ_2);

	if (nand_read_status())
		return -1;

	if (nand->buswidth)
		nand_command16(CMD_READ_1);
	else
		nand_command(CMD_READ_1);

#ifdef CONFIG_USE_PMECC
	if (usepmecc == 1) {
		pmecc_writel(AT91C_PMECC_RST, PMECC_CTRL);
		pmecc_writel(AT91C_PMECC_ENABLE | AT91C_PMECC_DATA, PMECC_CTRL);
	}
#endif
	/* Read loop */
	if (nand->buswidth) {
		for (i = 0; i < readbytes / 2; i++) {
			*((short *)pbuf) = read_word();
			pbuf += 2;
		}
	} else {
		for (i = 0; i < readbytes; i++)
			*pbuf++ = read_byte();

#ifdef CONFIG_USE_PMECC
		if (usepmecc == 1)
			ret = pmecc_process(nand, buffer);
#endif
	}

	nand_cs_disable();

	return ret;
}
#endif /* #ifdef NANDFLASH_SMALL_BLOCKS */

static int nand_check_badblock(struct nand_info *nand,
				unsigned int block,
				unsigned char *buffer)
{
	unsigned int page;
	unsigned int row_address = block * nand->pages_block;

	/*
	 * Read the first page and second page oob zone
	 * to detect if block is bad
	 */
	for (page = 0; page < 2; page++) {
		nand_read_sector(nand, row_address + page, buffer, ZONE_INFO);
		if (*(buffer + nand->pagesize + nand->ecclayout->badblockpos)
			!= 0xff)
			return -1;
	}

	return 0;
}

#ifdef CONFIG_ENABLE_SW_ECC
static void nand_read_ecc(struct nand_ooblayout *ooblayout,
				unsigned char *buffer,
				unsigned char *ecc)
{
	unsigned int i;

	for (i = 0; i < ooblayout->eccbytes; i++)
		ecc[i] = buffer[ooblayout->eccpos[i]];
}
#endif

static int nand_read_page(struct nand_info *nand,
				unsigned int block,
				unsigned int page,
				unsigned int zone_flag,
				unsigned char *buffer)
{
	unsigned int row_address = block * nand->pages_block + page;

#ifndef CONFIG_ENABLE_SW_ECC
	return nand_read_sector(nand, row_address, buffer, ZONE_DATA);
#else

	int retval;
	unsigned char hamming[48], error;

	retval = nand_read_sector(nand, row_address, buffer,
				ZONE_DATA | ZONE_INFO);
	if (retval)
		return -1;

	nand_read_ecc(nand->ecclayout, buffer + nand->pagesize, hamming);

	error = Hamming_Verify256x(buffer, nand->pagesize, hamming);
	if (error && (error != Hamming_ERROR_SINGLEBIT)) {
		dbg_log(1, "NAND: Hamming ECC error!\n\r");
		return -1;
	}

	return 0;
#endif /* #ifndef CONFIG_ENABLE_SW_ECC */
}

#ifdef CONFIG_NANDFLASH_RECOVERY
static int nand_erase_block0(struct nand_info *nand)
{
	unsigned int row_address = 0;
	unsigned int timeout = 10000;
	unsigned int status;

	nand_cs_enable();

	nand_command(CMD_ERASE_1);
	write_row_address(nand, row_address);
	nand_command(CMD_ERASE_2);

	udelay(2000);

	nand_command(CMD_STATUS);
	while ((!((status = read_byte()) & STATUS_READY)) && --timeout)
		;

	nand_cs_disable();

	if (status & STATUS_ERROR)
		return -1;

	if (timeout == 0)
		return -2;

	return 0;
}

static int nandflash_recovery(struct nand_info *nand)
{
	int ret = -1;

	/*
	 * If Recovery Button is pressed during boot sequence,
	 * erase nandflash block0
	*/
	dbg_log(1, "NAND: Press the recovery button (%s) to recovery\n\r",
			RECOVERY_BUTTON_NAME);

	if ((pio_get_value(CONFIG_SYS_RECOVERY_BUTTON_PIN)) == 0) {
		dbg_log(1, "NAND: The recovery button (%s) has been "\
				"pressed\n\r", RECOVERY_BUTTON_NAME);
		dbg_log(1, "NAND: The block 0 is erasing ...\n\r");

		ret = nand_erase_block0(nand);
		if (ret)
			dbg_log(1, "NAND: The erasing failed\n\r");
		else
			dbg_log(1, "NAND: The erasing is done\n\r");
	}

	return ret;
}
#endif /* #ifdef CONFIG_NANDFLASH_RECOVERY */

static int nand_loadimage(struct nand_info *nand,
				unsigned int offset,
				unsigned int length,
				unsigned char *dest)
{
	unsigned char *buffer = dest;
	unsigned int readsize;
	unsigned int block = 0;
	unsigned int page;
	unsigned int start_page = 0;
	unsigned int end_page;
	unsigned int numpages = 0;
	unsigned int offsetpage = 0;
	int ret;

	division(offset, nand->blocksize, &block, &start_page);
	start_page = div(start_page, nand->pagesize);

	while (length > 0) {
		/* read a buffer corresponding to a block */
		if (length < nand->blocksize)
			readsize = length;
		else
			readsize = nand->blocksize;

		/* adjust the number of pages to read */
		division(readsize, nand->pagesize, &numpages, &offsetpage);
		if (offsetpage)
			numpages++;

		end_page = start_page + numpages;

		/* check the bad block */
		while (1) {
			if (nand_check_badblock(nand,
					block, buffer) != 0) {
				block++; /* skip this block */
				dbg_log(1, "NAND: Bad block:" \
					" #%d\n\r", block);
			} else
				break;
		}

		/* read pages of a block */
		for (page = start_page; page < end_page; page++) {
			ret = nand_read_page(nand, block, page,
						ZONE_DATA, buffer);
			if (ret)
				return -1;
			else
				buffer += nand->pagesize;
		}
		length -= readsize;

		block++;
		start_page = 0;
	}

	return 0;
}

int load_nandflash(struct image_info *image)
{
	struct nand_info nand;
	int ret;

	nandflash_hw_init();

	if (nandflash_get_type(&nand))
		return -1;

#ifdef CONFIG_NANDFLASH_RECOVERY
	if (nandflash_recovery(&nand) == 0)
		return -2;
#endif

#ifdef CONFIG_USE_PMECC
	if (init_pmecc(&nand))
		return -1;
#endif

#ifdef CONFIG_ENABLE_SW_ECC
	dbg_log(1, "NAND: Using Software ECC\n\r");
#endif

	dbg_log(1, "NAND: Image: Copy %d bytes from %d to %d\r\n",
			image->length, image->offset, image->dest);

	ret = nand_loadimage(&nand, image->offset, image->length, image->dest);
	if (ret)
		return ret;

	if (image->of) {
		dbg_log(1, "NAND: dt blob: Copy %d bytes from %d to %d\r\n",
			image->of_length, image->of_offset, image->of_dest);

		ret = nand_loadimage(&nand, image->of_offset,
					image->of_length, image->of_dest);
		if (ret)
			return ret;
	}

	return 0;
 }
