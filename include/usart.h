/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __USART_H__
#define __USART_H__

#define BAUDRATE(mck, baud) \
	(((((mck) * 10) / ((baud) * 16)) % 10) >= 5) ? \
	(mck / (baud * 16) + 1) : ((mck) / (baud * 16))

extern void usart_init(unsigned int);
extern void usart_puts(const char *ptr);
extern char usart_getc(void);

#endif /* __USART_H__ */
