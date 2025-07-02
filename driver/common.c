// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"
#include "flash.h"
#include "string.h"
#include "usart.h"

#ifdef CONFIG_LOAD_SW
load_function load_image;
#endif

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

#ifdef CONFIG_LOAD_SW

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
	image->jump_addr = JUMP_ADDR;
}
#endif /* CONFIG_LOAD_SW */

void load_image_done(int retval)
{
	char *media;

#ifndef CONFIG_LOAD_SW
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
#ifndef CONFIG_LOAD_SW
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
