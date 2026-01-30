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

#define FAST_BOOT_SDCARD	0
#define FAST_BOOT_QSPI		1
#define FAST_BOOT_NAND		2

#define FAST_BOOT_KERNEL_6_12	0
#define FAST_BOOT_KERNEL_6_11	1

struct fast_boot {
	unsigned int bootmedia;
	unsigned int secure;
	unsigned int kernel_version;
	unsigned int ddr_base;
	unsigned int snapshot_offset;
	unsigned int mapnr;
	unsigned int page_stru;
	unsigned int of_pagetype;
	unsigned int of_priate;
	unsigned int ss_cipher_key[4];
	unsigned int ss_iv[4];
	unsigned long mem_map_addr;
};

struct rw_ops {
	int (*read)(unsigned int from, unsigned int len, void *buf);
	int (*write)(unsigned int to, unsigned int len, const void *buf);
};

struct ss_restore {
	unsigned long mem_map;
	unsigned long magic_code;
	unsigned long resume_addr;
	unsigned int max_mapnr;
	unsigned int mem_base;
	const struct rw_ops *ops;
};

extern void init_fast_boot(void);
extern void fast_boot_init_params(struct fast_boot *fb);
extern void fast_boot_init_snapshot(int partition_addr);
extern void fast_boot_init_aes(void);
extern unsigned int flash_restore(struct image_info *image);

#ifdef CONFIG_SDCARD
extern int fastboot_get_partition(void);
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

extern const struct rw_ops ss_rw_ops;
#endif	/* #ifndef __FAST_BOOT_H__ */
