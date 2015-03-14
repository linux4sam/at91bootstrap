/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
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
#ifndef __COMMON_H__
#define __COMMON_H__

#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))

#define ALIGN(size, align)	(((size) + (align) - 1) & (~((align) - 1)))
#define OF_ALIGN(size)		ALIGN(size, 4)

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#ifndef NULL
#define	NULL	0
#endif

#define FILENAME_BUF_LEN	33

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
#ifdef CONFIG_UBI
	const char *volname;
#ifdef CONFIG_UBI_SPARE
	const char *spare_volname;
#endif
#endif
#endif
#ifdef CONFIG_SDCARD
	char *filename;
#endif
	unsigned char *dest;

#ifdef CONFIG_OF_LIBFDT
#if defined(CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH) || defined(CONFIG_FLASH)
	unsigned int of_offset;
	unsigned int of_length;
#ifdef CONFIG_UBI
	const char *of_volname;
#ifdef CONFIG_UBI_SPARE
	const char *of_spare_volname;
#endif
#endif
#endif
#ifdef CONFIG_SDCARD
	char *of_filename;
#endif
	unsigned char *of_dest;
#endif
};

#ifdef CONFIG_SDCARD
extern void (*sdcard_set_of_name)(char *);
#endif

#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
extern int kernel_size(unsigned char *addr);
#endif

static inline unsigned int swap_uint32(unsigned int data)
{
	volatile unsigned int a, b, c, d;

	a = ((data) & 0xff000000) >> 24;
	b = ((data) & 0x00ff0000) >> 8;
	c = ((data) & 0x0000ff00) << 8;
	d = ((data) & 0x000000ff) << 24;

	return a | b | c | d;
}

static inline unsigned long long int swap_uint64(unsigned long long int data)
{
	volatile unsigned long long int a, b, c, d, e, f, g, h;

	a = ((data) & 0xff00000000000000) >> 56;
	b = ((data) & 0x00ff000000000000) >> 40;
	c = ((data) & 0x0000ff0000000000) >> 24;
	d = ((data) & 0x000000ff00000000) >> 8;
	e = ((data) & 0x00000000ff000000) << 8;
	f = ((data) & 0x0000000000ff0000) << 24;
	g = ((data) & 0x000000000000ff00) << 40;
	h = ((data) & 0x00000000000000ff) << 56;

	return a | b | c | d | e | f | g | h;
}

#endif /* #ifdef __COMMON_H__ */
