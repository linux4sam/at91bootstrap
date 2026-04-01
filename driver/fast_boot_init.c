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
#include "aes.h"
#include "fast_boot.h"
#include "autoconf.h"

void fast_boot_init_config(struct fast_config *conf)
{
#if defined(CONFIG_FASTBOOT_AUTO_MODE) || defined(CONFIG_FASTBOOT_MANUAL_MODE)
	backup_fast_config(conf);
#endif

#ifdef CONFIG_FASTBOOT_AUTO_MODE
	conf->flags |= F_AUTO_MODE;
#endif

#ifdef CONFIG_FASTBOOT_MANUAL_MODE
#if defined(CONFIG_FASTBOOT_LINUX_5_15_68)
	conf->linux_ver = ID_0_VER_5_15_68;
#elif defined(CONFIG_FASTBOOT_LINUX_6_6_23)
	conf->linux_ver = ID_1_VER_6_6_23;
#elif defined(CONFIG_FASTBOOT_LINUX_6_6_51)
	conf->linux_ver = ID_2_VER_6_6_51;
#elif defined(CONFIG_FASTBOOT_LINUX_6_10_14)
	conf->linux_ver = ID_3_VER_6_10_14;
#elif defined(CONFIG_FASTBOOT_LINUX_6_12_22)
	conf->linux_ver = ID_4_VER_6_12_22;
#elif defined (CONFIG_FASTBOOT_LINUX_6_12_48)
	conf->linux_ver = ID_5_VER_6_12_48;
#else
#error "Fastboot incorrect linux version"
#endif

#if defined(CONFIG_FASTBOOT_LINUX_PAGE_4K)
	conf->page_shift = PAGE_SHIFT_4K;
#elif defined(CONFIG_FASTBOOT_LINUX_PAGE_16K)
	conf->page_shift = PAGE_SHIFT_16K;
#else
#error "Fastboot incorrect page shift"
#endif

	conf->mem_map = CONFIG_FASTBOOT_MEM_MAP_ADDRESS;
	conf->max_mapnr = CONFIG_FASTBOOT_MAX_NB_MEM_MAP;
	conf->struct_size = CONFIG_FASTBOOT_SIZEOF_PAGE_STRUCT;
	conf->page_off = CONFIG_FASTBOOT_OFFSET_OF_PAGETYPE;
	conf->order_off = CONFIG_FASTBOOT_OFFSET_OF_PRIVATE;
#endif

#ifdef CONFIG_FASTBOOT_SECURE
	conf->flags |= F_SECURE;
	conf->ss_key[0] = CONFIG_AES_CIPHER_KEY_WORD0;
	conf->ss_key[1] = CONFIG_AES_CIPHER_KEY_WORD1;
	conf->ss_key[2] = CONFIG_AES_CIPHER_KEY_WORD2;
	conf->ss_key[3] = CONFIG_AES_CIPHER_KEY_WORD3;
	conf->ss_iv[0] = CONFIG_AES_IV_WORD0;
	conf->ss_iv[1] = CONFIG_AES_IV_WORD1;
	conf->ss_iv[2] = CONFIG_AES_IV_WORD2;
	conf->ss_iv[3] = CONFIG_AES_IV_WORD3;
#if defined(CONFIG_AES_KEY_SIZE_128)
	conf->ss_key_size = AT91_AES_KEY_SIZE_128;
#elif defined(CONFIG_AES_KEY_SIZE_192)
	conf->ss_key_size = AT91_AES_KEY_SIZE_192;
	conf->ss_key[4] = CONFIG_AES_CIPHER_KEY_WORD4;
	conf->ss_key[5] = CONFIG_AES_CIPHER_KEY_WORD5;
#elif defined(CONFIG_AES_KEY_SIZE_256)
	conf->ss_key_size = AT91_AES_KEY_SIZE_256;
	conf->ss_key[4] = CONFIG_AES_CIPHER_KEY_WORD4;
	conf->ss_key[5] = CONFIG_AES_CIPHER_KEY_WORD5;
	conf->ss_key[6] = CONFIG_AES_CIPHER_KEY_WORD6;
	conf->ss_key[7] = CONFIG_AES_CIPHER_KEY_WORD7;
#else
#error "Fastboot bad AES key size"
#endif
#endif

#ifdef CONFIG_FASTBOOT_ZERO_PAGE
	conf->flags |= F_ZERO_PAGE;
#endif
#ifdef CONFIG_FASTBOOT_DUMP
	conf->flags |= F_DUMP;
#endif
#ifdef CONFIG_FASTBOOT_CRC
	conf->flags |= F_CRC;
#endif

	conf->ddr_base = AT91C_BASE_DDRCS;
#if defined(CONFIG_SDCARD)
	conf->snap_addr = CONFIG_FASTBOOT_SD_PARTITION;
#else
	conf->snap_addr = CONFIG_FASTBOOT_IMG_ADDRESS;
	conf->snap_size = CONFIG_FASTBOOT_IMG_SIZE;
#endif
}
