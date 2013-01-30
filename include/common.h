/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

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

#ifndef NULL
#define	NULL	0
#endif

/* structure definition */
struct image_info
{
	unsigned int offset;
	unsigned int length;
	char *filename;
	unsigned char *dest;

	unsigned char of;
	unsigned int of_offset;
	unsigned int of_length;
	char *of_filename;
	unsigned char *of_dest;
};

static inline unsigned int swap_uint32(unsigned int data)
{
	return ((data & 0x000000ff) << 24) | ((data & 0x0000ff00) << 8)
		| ((data & 0xff000000) >> 24) | ((data & 0x00ff0000) >> 8);
}

#endif /* #ifdef __COMMON_H__ */
