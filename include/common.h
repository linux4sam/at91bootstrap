/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#define ALIGN(size, align)	(((size) + (align) - 1) & (~((align) - 1)))
#define OF_ALIGN(size)		ALIGN(size, 4)

#define min(a, b)	(((a) < (b)) ? (a) : (b))
#define max(a, b)	(((a) > (b)) ? (a) : (b))

#ifndef NULL
#define	NULL	0
#endif

#define FILENAME_BUF_LEN	32
#define CMDLINE_BUF_LEN		256

enum {
	KERNEL_IMAGE,
	DT_BLOB,
};

/* structure definition */
struct image_info
{
#if defined(CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH) || defined(CONFIG_FLASH)
	unsigned int offset;
	unsigned int length;
#endif
#ifdef CONFIG_SDCARD
	char *filename;
#ifdef CONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE
	char *cmdline_file;
	char *cmdline_args;
#endif
#endif
	unsigned char *dest;

#ifdef CONFIG_OF_LIBFDT
#if defined(CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH) || defined(CONFIG_FLASH)
	unsigned int of_offset;
	unsigned int of_length;
#endif
#ifdef CONFIG_SDCARD
	char *of_filename;
#endif
	unsigned char *of_dest;
#endif
	unsigned int jump_addr;
};

typedef int (*load_function)(struct image_info *image);

#ifdef CONFIG_LOAD_SW

load_function get_image_load_func(void);

#if defined(CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH) || defined(CONFIG_FLASH)
unsigned int get_image_load_offset(unsigned int addr);
#endif

extern load_function load_image;

extern void init_load_image(struct image_info *image);

extern int load_kernel(struct image_info *image);

extern int kernel_size(unsigned char *addr);
#endif

extern void load_image_done(int retval);


static inline unsigned short swap_uint16(unsigned short data)
{
	volatile unsigned int a, b;

	a = ((data) & 0xff00) >> 8;
	b = ((data) & 0x00ff) << 8;

	return a | b;
}

static inline unsigned int swap_uint32(unsigned int data)
{
	volatile unsigned int a, b, c, d;

	a = ((data) & 0xff000000) >> 24;
	b = ((data) & 0x00ff0000) >> 8;
	c = ((data) & 0x0000ff00) << 8;
	d = ((data) & 0x000000ff) << 24;

	return a | b | c | d;
}

#endif /* #ifdef __COMMON_H__ */
