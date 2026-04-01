/* SPDX-License-Identifier: MIT
 *
 * Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software
 * and any derivatives exclusively with Microchip products. It is your
 * responsibility to comply with third party license terms applicable to your
 * use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
 * ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 */

#ifndef __FAST_BOOT_H__
#define __FAST_BOOT_H__

#include "common.h"
#include "debug.h"
#include "aes.h"

#define F_AUTO_MODE 0x01
#define F_ZERO_PAGE 0x02
#define F_SECURE    0x04
#define F_DUMP      0x08
#define F_CRC       0x10

#define PAGE_SHIFT_4K  12
#define PAGE_SHIFT_16K 14

enum ver_id {
	ID_0_VER_5_15_68,
	ID_1_VER_6_6_23,
	ID_2_VER_6_6_51,
	ID_3_VER_6_10_14,
	ID_4_VER_6_12_22,
	ID_5_VER_6_12_48,
};

enum erase_flag {
	ERASE_ALL,
	ERASE_HEADER,
};

struct align_info {
	unsigned int shift;
	unsigned int size;
	unsigned int mask;
};

struct header_desc {
	unsigned int magic;		/* header[0] */
	unsigned int canary;		/* header[1] */
	unsigned int resume;		/* header[2] */
	unsigned int max_mapnr;		/* header[3] */
	unsigned int linux_ver;		/* header[4] */
	unsigned int page_shift;	/* header[5] */
	unsigned int data_base;		/* header[6] */
	unsigned int flags;		/* header[7] */
	unsigned int chunk_map[8];	/* header[8 ~ 15] */
	unsigned int crc_ddr;		/* header[16] */
};

struct block_dev {
	unsigned int start;
	unsigned int count;
	unsigned char *buffer;
	unsigned long offset;
	void *priv;
	struct align_info block;
	struct align_info align;

	int (*init)(struct block_dev *, unsigned int, unsigned int);
	int (*read)(struct block_dev *, unsigned int, void *, unsigned int);
	int (*write)(struct block_dev *, unsigned int, const void *,
		     unsigned int);
	int (*erase)(struct block_dev *, enum erase_flag);
	int (*seek)(struct block_dev *, unsigned long);
	int (*io_read)(struct block_dev *, void *, unsigned int);
	int (*io_write)(struct block_dev *, const void *, unsigned int);
};

struct fast_config {
	/* mem_map description */
	unsigned int canary;
	unsigned int resume;
	unsigned int mem_map;
	unsigned int max_mapnr;
	unsigned int struct_size;
	unsigned int page_shift;
	unsigned int page_type;
	unsigned int page_off;
	unsigned int order_off;
	unsigned int linux_ver;

	unsigned int ddr_base;
	unsigned int snap_addr;
	unsigned int snap_size;
	unsigned int flags;
#ifdef CONFIG_FASTBOOT_SECURE
	unsigned int ss_key_size;
	unsigned int ss_key[8];
	unsigned int ss_iv[4];
#endif
};

struct fast_boot {
	struct fast_config *conf;
	struct block_dev *dev;
	struct header_desc *header;
	struct align_info *page;
	struct at91_aes_params *ss_ctx;
	unsigned int map_base;
	unsigned int data_base;
	unsigned int map_shift;
	unsigned int pages_free;
	unsigned int pages_used;
	unsigned int pages_zero;
	unsigned int crc_ddr;
};

extern const char * const fb_name;

#define log_raw(fmt_str, arg...) \
	dbg_info(fmt_str , ##arg)
#define log_info(fmt_str, arg...) \
	dbg_info("%s: " fmt_str , fb_name, ##arg)
#define log_err(fmt_str, arg...) \
	dbg_info("%s: %s " fmt_str , fb_name, "Error", ##arg)
#define log_dbg(fmt_str, arg...) \
	dbg_loud("%s: " fmt_str , fb_name, ##arg)

extern int fast_boot(struct fast_config *conf, struct block_dev *dev,
		     struct image_info *image);
extern void fast_boot_init_config(struct fast_config *conf);

#ifdef CONFIG_BACKUP_MODE
extern void backup_fast_config(struct fast_config *conf);
#endif

#ifdef CONFIG_SDCARD
extern unsigned int sdcard_fast_boot(struct image_info *image);
#endif
#ifdef CONFIG_NANDFLASH
#include "nand.h"
unsigned int nandflash_fast_boot(struct nand_info *nandflash, struct image_info *image);
#endif
#ifdef CONFIG_QSPI
#include "spi_flash/spi_nor.h"
unsigned int qspi_fast_boot(struct spi_flash *flash, struct image_info *image);
#endif

#endif	/* #ifndef __FAST_BOOT_H__ */
