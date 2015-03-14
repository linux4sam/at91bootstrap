/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation
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
#include "usart.h"
#include "debug.h"
#include <stdarg.h>
#include <string.h>

#define ROW_SIZE	0x10
#define MAX_BUFFER	128

static char dbg_buf[MAX_BUFFER];

static inline short fill_char(char *buf, char val)
{
	*buf = val;

	return 1;
}

static inline short fill_string(char *buf, char *p)
{
	short num = 0;

	if (!p)
		p = "(null)";

	while (*p != 0) {
		*buf++ = *p++;
		num++;
	}

	return num;
}

static inline short fill_hex_int(char *buf, unsigned int data)
{
	short num = 0;

	if ((data >> 4) > 0) {
		num += fill_hex_int(buf, data >> 4);
		buf += num;
	}

	if ((data & 0xF) < 10)
		fill_char(buf, (data & 0xF) + '0');
	else
		fill_char(buf, (data & 0xF) - 10 + 'a');
	num++;

	return num;
}

int dbg_printf(const char *fmt_str, ...)
{
	va_list ap;

	char *p = dbg_buf;

	short num = 0;

	va_start(ap, fmt_str);
	while (*fmt_str != 0) {
		if (*fmt_str != '%')
			*p++ = *fmt_str++;
		else if (*(fmt_str + 1) == '%') {
			*p++ = '%';
			fmt_str += 2;
		} else {
			fmt_str++;	/* skip % */
			switch (*fmt_str) {
			case 'p':
			case 'd':
			case 'i':
			case 'u':
			case 'x':
				*p++ = '0';
				*p++ = 'x';
				num = fill_hex_int(p, va_arg(ap, unsigned int));

				break;
			case 's':
				num = fill_string(p, va_arg(ap, char *));

				break;
			case 'c':
				num =
				    fill_char(p, (char)va_arg(ap, signed long));

				break;
			default:
				va_end(ap);
				return -1;
			}

			fmt_str++;
			p += num;
		}
	}
	va_end(ap);

	/* Terminate the result string */
	*p = '\0';

	usart_puts(dbg_buf);

	return 0;
}

void dbg_hexdump_line(const unsigned char *buf, unsigned int size)
{
	unsigned int j;
	unsigned char b[ROW_SIZE];
	memcpy(b, buf, size);
	memset(&b[size], 0x00, (ROW_SIZE - size));

	for (j = 0; j < ROW_SIZE; j++) {
		dbg_printf(" %x", buf[j]);
	}

	dbg_printf("\t");

	for (j = 0; j < ROW_SIZE; j++) {
		if ((buf[j] < 0x20) || (buf[j] >= 0x7F))
			dbg_printf(".");
		else
			dbg_printf("%c", (char) buf[j]);
	}

	dbg_printf("\n");
}

void dbg_hexdump(unsigned int address,
		 const unsigned char *buf,
		 unsigned int size)
{
	unsigned int r, row;

	row = size / ROW_SIZE;
	if (size % ROW_SIZE)
		row++;

	dbg_printf("%s:", "@address");
	for (r = 0; r < ROW_SIZE; r ++)
		dbg_printf(" %x", r);
	dbg_printf("\n");

	for (r = 0; r < row; r++) {
		dbg_printf("%x:", address + (r * ROW_SIZE));
		dbg_hexdump_line(buf, ROW_SIZE);
		buf += ROW_SIZE;
	}
	dbg_printf("%x\n", address + size);
}
