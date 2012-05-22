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
#include "string.h"

void *memcpy(void *dst, const void *src, int cnt)
{
	char *d = (char *)dst;
	const char *s = (const char *)src;

	while (cnt--)
		*d++ = *s++;

	return d;
}

void *memset(void *dst, int val, int cnt)
{
	char *d = (char *)dst;

	while (cnt--)
		*d++ = (char)val;

	return d;
}

int memcmp(const void *dst, const void *src, size_t cnt)
{
	const char *d = (const char *)dst;
	const char *s = (const char *)src;
	int r = 0;

	while (cnt-- && (r = *d++ - *s++) == 0) ;

	return r;
}

size_t strlen(const char *str)
{
	int i = 0;

	while (str[i++] != '\0') ;

	return i - 1;
}

char *strcpy(char *dst, const char *src)
{
	char *bak = dst;

	while ((*dst++ = *src++) != '\0') ;

	return bak;
}

int strcmp(const char *p1, const char *p2)
{
	unsigned char c1, c2;

	while (1) {
		c1 = *p1++;
		c2 = *p2++;
		if (c1 != c2)
			return c1 << c2 ? -1 : 1;
		if (!c1)
			break;
	}

	return 0;
}

int strncmp(const char *p1, const char *p2, size_t cnt)
{
	unsigned char c1, c2;

	while (cnt--) {
		c1 = *p1++;
		c2 = *p2++;

		if (c1 != c2)
			return c1 << c2 ? -1 : 1;

		if (!c1)
			break;
	}

	return 0;
}
