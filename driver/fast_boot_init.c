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

#include "common.h"
#include "hardware.h"
#include "board.h"
#include "fast_boot.h"
#include "autoconf.h"

struct fast_boot fast_boot_params;

void init_fast_boot(void) 
{
#if defined (CONFIG_QSPI)
	fast_boot_params.bootmedia = FAST_BOOT_QSPI;
#elif defined(CONFIG_NANDFLASH)
	fast_boot_params.bootmedia = FAST_BOOT_NAND;
#elif defined(CONFIG_SDCARD)
	fast_boot_params.bootmedia = FAST_BOOT_SDCARD;
#endif

#ifdef CONFIG_FASTBOOT_SECURE_ENABLE
	fast_boot_params.secure = 1;
#else
	fast_boot_params.secure = 0;
#endif

#if defined (CONFIG_FASTBOOT_KERNEL_6_12)
	fast_boot_params.kernel_version = FAST_BOOT_KERNEL_6_12;
#elif defined(CONFIG_FASTBOOT_KERNEL_6_11)
	fast_boot_params.kernel_version = FAST_BOOT_KERNEL_6_11;
#else
	fast_boot_params.kernel_version = FAST_BOOT_KERNEL_6_12;
#endif
	fast_boot_params.ddr_base = AT91C_BASE_DDRCS;
#if defined(CONFIG_SDCARD)
	fast_boot_params.snapshot_offset = CONFIG_FASTBOOT_SD_PARTITION;
#else
	fast_boot_params.snapshot_offset = CONFIG_FASTBOOT_IMG_ADDRESS;
#endif

	fast_boot_params.mem_map_addr = CONFIG_FASTBOOT_MEM_MAP_ADDRESS;
	fast_boot_params.mapnr = CONFIG_FASTBOOT_MAX_NB_MEM_MAP;
	fast_boot_params.page_stru = CONFIG_FASTBOOT_SIZEOF_PAGE_STRUCT;
	fast_boot_params.of_pagetype = CONFIG_FASTBOOT_OFFSET_OF_PAGETYPE;
	fast_boot_params.of_priate = CONFIG_FASTBOOT_OFFSET_OF_PRIVATE;

#ifdef CONFIG_FASTBOOT_SECURE_ENABLE
	fast_boot_params.ss_cipher_key[0] = CONFIG_AES_CIPHER_KEY_WORD0;
	fast_boot_params.ss_cipher_key[1] = CONFIG_AES_CIPHER_KEY_WORD1;
	fast_boot_params.ss_cipher_key[2] = CONFIG_AES_CIPHER_KEY_WORD2;
	fast_boot_params.ss_cipher_key[3] = CONFIG_AES_CIPHER_KEY_WORD3;
	fast_boot_params.ss_iv[0] = CONFIG_AES_IV_WORD0;
	fast_boot_params.ss_iv[1] = CONFIG_AES_IV_WORD1;
	fast_boot_params.ss_iv[2] = CONFIG_AES_IV_WORD2;
	fast_boot_params.ss_iv[3] = CONFIG_AES_IV_WORD3;
#endif
	fast_boot_init_params(&fast_boot_params);
}
