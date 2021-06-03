/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
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
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"
#include "flash.h"
#include "string.h"
#include "usart.h"

load_function load_image;

#ifdef CONFIG_SDCARD
char filename[FILENAME_BUF_LEN];
#ifdef CONFIG_OF_LIBFDT
char of_filename[FILENAME_BUF_LEN];
#endif
#ifdef CONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE
char cmdline_file[FILENAME_BUF_LEN];
char cmdline_args[CMDLINE_BUF_LEN];
#endif
#endif

#if !defined(CONFIG_LOAD_NONE)

load_function get_image_load_func(void)
{
#if defined(CONFIG_DATAFLASH)
	return &load_dataflash;
#elif defined(CONFIG_FLASH)
	return &load_norflash;
#elif defined(CONFIG_NANDFLASH)
	return &load_nandflash;
#elif defined(CONFIG_SDCARD)
	return &load_sdcard;
#else
#error "No booting media_str specified!"
#endif
}

#if defined(CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH) || defined(CONFIG_FLASH)
unsigned int get_image_load_offset(unsigned int addr)
{
#ifdef CONFIG_FLASH
	return (addr | 0x10000000);
#endif

#if defined(CONFIG_NANDFLASH) || defined(CONFIG_DATAFLASH)
	return addr;
#endif
}
#endif

void init_load_image(struct image_info *image)
{
	memset(image,		0, sizeof(*image));
#ifdef CONFIG_SDCARD
	memset(filename,	0, FILENAME_BUF_LEN);
#ifdef CONFIG_OF_LIBFDT
	memset(of_filename,	0, FILENAME_BUF_LEN);
#endif
#endif

#if defined(CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH) || defined(CONFIG_FLASH)

#if !defined(CONFIG_LOAD_LINUX) && !defined(CONFIG_LOAD_ANDROID)
	image->length = IMG_SIZE;
#endif

	image->offset = get_image_load_offset(IMG_ADDRESS);
#ifdef CONFIG_OF_LIBFDT
	image->of_offset = get_image_load_offset(OF_OFFSET);
#endif

#endif

	image->dest = (unsigned char *)JUMP_ADDR;
#ifdef CONFIG_OF_LIBFDT
	image->of_dest = (unsigned char *)OF_ADDRESS;
#endif

#ifdef CONFIG_SDCARD
	image->filename = filename;
	strcpy(image->filename, IMAGE_NAME);
#ifdef CONFIG_OF_LIBFDT
	image->of_filename = of_filename;
#endif
#ifdef CONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE
	image->cmdline_file = cmdline_file;
	strcpy(image->cmdline_file, CMDLINE_FILE);
	image->cmdline_args = cmdline_args;
#endif
#endif

#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
	load_image = &load_kernel;
#else
	load_image = get_image_load_func();
#endif
}
#endif

void load_image_done(int retval)
{
	char *media;

#if defined(CONFIG_LOAD_NONE)
	media = "NONE: ";
#elif defined(CONFIG_FLASH)
	media = "FLASH: ";
#elif defined(CONFIG_NANDFLASH)
	media = "NAND: ";
#elif defined(CONFIG_DATAFLASH)
	media = "SF: ";
#elif defined(CONFIG_SDCARD)
	media = "SD/MMC: ";
#else
	media = NULL;
#endif

	if (media)
		usart_puts(media);

	if (retval == 0) {
#if defined(CONFIG_LOAD_NONE)
		usart_puts("AT91Bootstrap completed. Can load application via JTAG and jump.\n");
#else
		usart_puts("Done to load image\n");
#endif
	}
	if (retval == -1) {
		usart_puts("Failed to load image\n");
		while(1);
	}
	if (retval == -2) {
		usart_puts("Success to recovery\n");
		while (1);
	}
}
