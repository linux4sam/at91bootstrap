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
#include "nand_ids.h"

#define ECC_CORRECT_ERROR  0xfe

#undef CONFIG_USE_PMECC
#if defined(CPU_HAS_PMECC) && !defined(CONFIG_ENABLE_SW_ECC)
#define CONFIG_USE_PMECC
#endif

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

/* ECC detection/coreection */
typedef int (*PMECC_CorrectionAlgo_Rom_Func) (unsigned long pPMECC,
			unsigned long pPMERRLOC,
			struct _PMECC_paramDesc_struct *PMECC_desc,
			unsigned int PMECC_status,
			void *pageBuffer);

PMECC_CorrectionAlgo_Rom_Func pmecc_correction_algo;

static int pmecc_readl(unsigned int reg)
{
	return(readl(AT91C_BASE_PMECC + reg));
}

static void pmecc_writel(unsigned int value, unsigned reg)
{
	writel(value, (AT91C_BASE_PMECC + reg));
}
#endif /* #ifdef CONFIG_USE_PMECC */

/* ooblayout */
static struct nand_ooblayout nand_oob_layout;

static struct nand_chip nand_chip_default;

static struct nand_onfi_params onfi_params;

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
	return(readb((unsigned long)IO_ADDR_R));
}

static void write_byte(unsigned char data)
{
	writeb(data, (unsigned long)IO_ADDR_W);
}

/* 16 bits devices */
static void nand_command16(unsigned short cmd)
{
	writew(cmd, (unsigned long)IO_ADDR_W | CONFIG_SYS_NAND_MASK_CLE);
}

static void nand_address16(unsigned short addr)
{
	writew(addr, (unsigned long)IO_ADDR_W | CONFIG_SYS_NAND_MASK_ALE);
}

static unsigned short read_word(void)
{
	return(readw((unsigned long)IO_ADDR_R));
}

static void nand_wait_ready(void)
{
	unsigned int timeout = 10000;

	nand_command(CMD_STATUS);
	while((!(read_byte() & STATUS_READY)) && timeout--);
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
		layout->eccbytes = 16;
#else
		layout->eccbytes = 24;
#endif
		layout->oobavail_offset = 1;
		break;

	case 4096:
		layout->badblockpos = 0;
#ifdef CONFIG_USE_PMECC
		layout->eccbytes = 32;
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

	layout->oobavailbytes = oobsize - layout->eccbytes - layout->oobavail_offset;
}

static int nand_disable_internal_ecc(unsigned char manfid,
				unsigned char devicemodel,
				unsigned char ecc_bits)
{
	if (((manfid & 0x2c) == 0x2c)	/* Micron */
		&& (ecc_bits == 0x04)
		&& ((devicemodel == '1') 	/* 1G */
		|| (devicemodel == '2')		/* 2G*/
		|| (devicemodel == '4'))) {	/* 4G */

		nand_cs_enable();
		nand_command(CMD_SET_FEATURE);
		nand_address(0x90);

		write_byte(0x00);
		write_byte(0x00);
		write_byte(0x00);
		write_byte(0x00);
		nand_cs_disable();
	}
	return 0;

}

static unsigned short onfi_crc16(unsigned short crc, unsigned char const *p, unsigned int len)
{
	int i;

	while (len--) {
		crc ^= *p++ << 8;
		for (i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
	}

	return crc;
}

/* Check if the NAND chip is ONFI compliant, returns 0 if it is, -1 otherwise */
static int nandflash_detect_onfi(struct nand_chip *chip)
{
	struct nand_onfi_params *p = &onfi_params;
	unsigned char onfi_ind[4];
	int i, j;
	unsigned int onfi_version;
	unsigned char *param;

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
		dbg_log(1, "Nand: ONFI not supported\n\r");
		return -1;
	}

	dbg_log(1, "ONFI flash detected\n\r");

	nand_cs_enable();

	/* read the nand ONFI parameter */
	nand_command(CMD_READ_ONFI);
	nand_address(0x00);
	
	nand_wait_ready();
	nand_command(CMD_READ_1);
	
	for (i = 0; i < 3; i++) {
		param = (unsigned char *)p;
		/* Read the parameter table */
		for (j = 0; j < sizeof(onfi_params); j++)
			*param++ = read_byte();

		if (onfi_crc16(ONFI_CRC_BASE, (unsigned char *)p, 254) == p->crc) {
			dbg_log(1, "ONFI param page %d valid\n\r", i);
			break;
		}
	}

	nand_cs_disable();

	if (i == 3) {
		dbg_log(1, "ONFI para CRC error!\n\r");
		return -1;
	}

	/* check version */
	if (p->revision & (1 << 5))
		onfi_version = 23;
	else if (p->revision & (1 << 4))
		onfi_version = 22;
	else if (p->revision & (1 << 3))
		onfi_version = 21;
	else if (p->revision & (1 << 2))
		onfi_version = 20;
	else if (p->revision & (1 << 1))
		onfi_version = 10;
	else
		onfi_version = 0;

	if (!onfi_version) {
		dbg_log(1, "%s: unsupported ONFI version: %d\n\r", __func__, p->revision);
		return -1;
	}

	chip->numblocks = p->blocks_per_lun;
	chip->pagesize 	= p->byte_per_page;
	chip->blocksize = p->pages_per_block * chip->pagesize;
	chip->oobsize 	= p->spare_bytes_per_page;
	chip->buswidth	= p->features & 0x01;

	nand_disable_internal_ecc(p->jedec_id, p->model[5], p->ecc_bits);
	return 0;
}

static int nandflash_detect_non_onfi(struct nand_chip *chip)
{
	int manf_id, dev_id, cellinfo, extid, tmp_manf, tmp_dev;
	struct nandflash_dev *type;

	nand_cs_enable();

	/* Send the command for reading device ID */
	nand_command(CMD_READID);
	nand_address(0x00);

	/* Read manufacturer and device IDs */
	manf_id  = read_byte();
	dev_id   = read_byte();
	cellinfo = read_byte();
	extid    = read_byte();

	/*
	 * Try again to make sure, as some systems the bus-hold or other
	 * interface concerns can cause random data which looks like a
	 * possibly credible NAND flash to appear. If the two results do
	 * not match, ignore the device completely.
	 */

	nand_command(CMD_READID);
	nand_address(0x00);

	/* Read manufacturer and device IDs */
	tmp_manf = read_byte();
	tmp_dev  = read_byte();

	nand_cs_disable();

	if (tmp_manf != manf_id || tmp_dev != dev_id) {
		dbg_log(1, "%s: second ID read did not match "
		       "%d, %d against %d, %d\n\r", __func__,
		       manf_id, dev_id, tmp_manf, tmp_dev);
		return -1;
	}

	cellinfo = cellinfo;

	type = (struct nandflash_dev *)&nandflash_ids[0];
	
	for (; type->name != NULL; type++)
		if (dev_id == type->id)
			break;
	
	if (type->name == NULL){
		if (manf_id != 0x00 && manf_id != 0xff 
			&& dev_id != 0x00 && dev_id != 0xff)
			dbg_log(1, "unknown NAND device: Manufacturer ID: %d, Chip ID: 0x%d\n\r",
						manf_id, dev_id);
		return -1;
	}
	
	dbg_log(1, "NAND device: %s, Manufacturer ID: %d Chip ID: %d\n\r",
			type->name, manf_id, dev_id);

	/* Newer devices have all the information in additional id bytes */
	if (type->pagesize == 0){
		/* Calc pagesize */
		chip->pagesize = 1024 << (extid & 0x3);
		extid >>= 2;
		/* Calc oobsize */
		chip->oobsize = (8 << (extid & 0x01)) * (chip->pagesize >> 9);
		extid >>= 2;
		/* Calc blocksize. Blocksize is multiples of 64KiB */
		chip->blocksize = (64 * 1024) << (extid & 0x03);
		extid >>= 2;
		/* Get buswidth information */
		chip->buswidth = (extid & 0x01) ? 1 : 0;
	} else {
		/* Old devices have chip data hardcoded in the device id table */
		chip->pagesize 	= type->pagesize;
		chip->blocksize = type->erasesize;
		chip->oobsize 	= chip->pagesize / 32;
		chip->buswidth 	= (((type->options & NAND_BUSWIDTH_16) 
						== NAND_BUSWIDTH_16) ? 1: 0); 
	}

	chip->numblocks = (type->chipsize << 20) / chip->blocksize;

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
	nand->pages_block = nand->blocksize / nand->pagesize;
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
			dbg_log(1, "Not Find Support NAND Device!\n\r");
			return -1;
		}
	}

	nand_info_init(nand, chip);
	
	if (nand->buswidth == 0)
		nandflash_config_buswidth(0);
	else
		nandflash_config_buswidth(1);

	return 0;
}

#ifdef CONFIG_USE_PMECC
static int init_pmecc_descripter(struct _PMECC_paramDesc_struct *pmecc_params, struct nand_info *nand)
{
	if ((nand->pagesize == 2048) || (nand->pagesize == 4096)) {
		pmecc_params->errBitNbrCapability = AT91C_PMECC_BCH_ERR2; 	/* Error Correct Capability */
		pmecc_params->sectorSize = AT91C_PMECC_SECTORSZ_512;		/* Sector Size */
		pmecc_params->nandWR = AT91C_PMECC_NANDWR_0;			/* NAND read access */
		pmecc_params->spareEna = AT91C_PMECC_SPAREENA_DIS;		/* for NAND read access,the spare area is skipped  */
		pmecc_params->modeAuto = AT91C_PMECC_AUTO_DIS;			/* the spare area is not protected */

		pmecc_params->spareSize = nand->oobsize;			/* Spare Area Size */
		pmecc_params->eccSizeByte = nand->ecclayout->eccbytes;		/* ECC size */
		pmecc_params->eccStartAddress = nand->ecclayout->eccpos[0];	/* ECC Area Start Address */
		pmecc_params->eccEndAddress = nand->ecclayout->eccpos[nand->ecclayout->eccbytes - 1];	/* ECC Area End Address */

		pmecc_params->clkCtrl = 2;	/* At 133Mhz, this field must be programmed with 2 */

		pmecc_params->interrupt = 0;
		pmecc_params->tt = 2;
		pmecc_params->mm = 13;
		pmecc_params->nn = (1 << pmecc_params->mm) - 1;
		pmecc_params->alpha_to = (short *)(AT91C_BASE_ROM + CONFIG_LOOKUP_TABLE_ALPHA_OFFSET);
		pmecc_params->index_of = (short *)(AT91C_BASE_ROM + CONFIG_LOOKUP_TABLE_INDEX_OFFSET);

		/* Number of Sectors in the Page */
		if (nand->pagesize == 2048)
			pmecc_params->pageSize = AT91C_PMECC_PAGESIZE_4SEC;
		else
			pmecc_params->pageSize = AT91C_PMECC_PAGESIZE_8SEC;

		return 0;
	} else {
		dbg_log(1, "PMECC: Not supported page size: %d\n\r", nand->pagesize);
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
	pmecc_correction_algo = (PMECC_CorrectionAlgo_Rom_Func)
			(*(unsigned int *)(AT91C_BASE_ROM + CONFIG_PMECC_ALGO_FUNC_OFFSET));

	if (init_pmecc_descripter(&PMECC_paramDesc, nand) != 0)
		return -1;

	init_pmecc_core(&PMECC_paramDesc);

	return 0;
}
#endif /* #ifdef CONFIG_USE_PMECC */

static void write_column_address(struct nand_info *nand, unsigned int column_address)
{
	unsigned int page_size = nand->pagesize;

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

static void write_row_address(struct nand_info *nand, unsigned int row_address)
{
	unsigned int num_pages = nand->pages_device;

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
static int check_pmecc_ecc_data(struct nand_info *nand, unsigned char *buffer)
{
	unsigned int i;
	unsigned char *ecc_data = buffer + nand->pagesize + nand->ecclayout->eccpos[0];

	for (i = 0; i < nand->ecclayout->eccbytes; i++)
		if (*ecc_data++ != 0xff)
			break;

	if (i >= nand->ecclayout->eccbytes)
		return -1;
	else
		return 0;
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
			//dbg_log(1, "PMECC: reading All-0xFF page\n\r");
			return 0;
		}

		dbg_log(1, "PMECC: sector bits %d corrupted, Now correcting...\n\r", erris);
		result = (*pmecc_correction_algo)(AT91C_BASE_PMECC,
			AT91C_BASE_PMERRLOC,
			&PMECC_paramDesc,
			erris,
			buffer);

		if (result != 0) {
			dbg_log(1, "PMECC: failed to correct corrupted bits!\n\r");
			ret =  ECC_CORRECT_ERROR;
		}
	}

	return ret;
}
#endif /* #ifdef CONFIG_USE_PMECC */

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

	nand_wait_ready();
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
		pmecc_writel((pmecc_readl(PMECC_CFG) | AT91C_PMECC_AUTO_ENA), PMECC_CFG);
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

	nand_wait_ready();
	if (nand->buswidth)
		nand_command16(CMD_READ_1);
	else
		nand_command(CMD_READ_1);

#ifdef CONFIG_USE_PMECC
	if (usepmecc == 1) {
		pmecc_writel(AT91C_PMECC_RST, PMECC_CTRL);
		pmecc_writel(AT91C_PMECC_ENABLE | AT91C_PMECC_DATA , PMECC_CTRL);
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

	/* Read the first page and second page oob zone to detect if block is bad */
	for (page = 0; page < 2; page++) {
		nand_read_sector(nand, row_address + page, buffer, ZONE_INFO);
		if (*(buffer + nand->pagesize + nand->ecclayout->badblockpos) != 0xff)
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

	retval = nand_read_sector(nand, row_address, buffer,ZONE_DATA | ZONE_INFO);
	if (retval)
		return -1;

	nand_read_ecc(nand->ecclayout, buffer + nand->pagesize, hamming);

	error = Hamming_Verify256x(buffer, nand->pagesize, hamming);
	if (error && (error != Hamming_ERROR_SINGLEBIT)) {
		dbg_log(1, "Hamming ECC error!\n\r");
		return ECC_CORRECT_ERROR;
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
	int ret;

	nand_cs_enable();

	nand_command(CMD_ERASE_1);
	write_row_address(nand, row_address);
	nand_command(CMD_ERASE_2);

	nand_command(CMD_STATUS);
	do {
		status = read_byte();
		if (status & STATUS_ERROR){
			ret = -1;
			goto err;
		}
		if (status & STATUS_READY) {
			ret = 0;
			break;
		}
	} while (timeout--);

	if (timeout == 0)
		ret = -2;

	nand_cs_disable();
	return ret;

err:
	nand_cs_disable();
	return ret;
}

static int nandflash_recovery(struct nand_info *nand)
{
	/*
	 * If Recovery Button is pressed during boot sequence,
	 * erase nandflash block0
	*/
	if ((pio_get_value(CONFIG_SYS_RECOVERY_BUTTON_PIN)) == 0) {
		dbg_log(1, "Nand: The recovery button (%s) has been pressed\n\r", RECOVERY_BUTTON_NAME);
		dbg_log(1, "Nand: The block 0 is erasing ...\n\r");

		nand_erase_block0(nand);

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

	unsigned int length, readsize;
	unsigned int block;
	unsigned int page, start_page, end_page, numpages;
	int ret;
	
	nandflash_hw_init();

#ifdef CONFIG_NANDFLASH_RECOVERY
	if (nandflash_recovery(&nand) == 0)
		return -2;
#endif

	if (nandflash_get_type(&nand))
		return -1;

#ifdef CONFIG_USE_PMECC
	if (init_pmecc(&nand))
		return -1;
#endif

	dbg_log(1, "Nand: Copy %d bytes from %d to %d\r\n", size, offset, buffer);

	block = offset / nand.blocksize;
	start_page = (offset % nand.blocksize) / nand.pagesize;

	length = size;
	while (length > 0) {
		/* read a buffer corresponding to a block */
		if (length < nand.blocksize) 
			readsize = length;
		else
			readsize = nand.blocksize;

		/* adjust the number of pages to read */
		numpages = readsize / nand.pagesize;
		if (readsize % nand.pagesize)
			numpages++;

		end_page = start_page + numpages;

		/* check the bad block */
		while (1) {
			if (nand_check_badblock(&nand, block, buffer) != 0) {
				block++; /* skip this block */
				dbg_log(1, "Bad block: #%d\n\r", block);
			} else
				break;
		}

		/* read pages of a block */
		for (page = start_page; page < end_page; page++) {
			ret = nand_read_page(&nand, block, page, ZONE_DATA, buffer);
			if (ret == ECC_CORRECT_ERROR)
				return -1;
			else
				buffer += nand.pagesize;
		}
		length -= readsize;

		block++;
		start_page = 0;
	}

	return 0;
}
