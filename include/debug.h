/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DEBUG_INFO        1
#define DEBUG_LOUD        2
#define DEBUG_VERY_LOUD   4

#define DUMP_WIDTH_BIT_8	1
#define DUMP_WIDTH_BIT_32	2

#ifdef CONFIG_DEBUG
extern int dbg_printf(const char *fmt_str, ...);
extern void dbg_hexdump(const unsigned char *buf,
			unsigned int size, unsigned int width);
#else
#define BOOTSTRAP_DEBUG_LEVEL 0

#include "usart.h"

static inline int dbg_printf(const char *fmt_str, ...)
{
	usart_puts(fmt_str);
	return 0;
}
static inline void dbg_hexdump(const unsigned char *buf,
			       unsigned int size, unsigned int width) { }
#endif

#define console_printf(fmt_str, args...) \
	dbg_printf(fmt_str , ## args)

#define dbg_log(level, fmt_str, args...) \
	({ \
		(level) <= BOOTSTRAP_DEBUG_LEVEL ? dbg_printf((fmt_str), ##args) : 0; \
	})

#define dbg_info(fmt_str, arg...)		\
	dbg_log(DEBUG_INFO, fmt_str , ## arg)
#define dbg_loud(fmt_str, arg...)		\
	dbg_log(DEBUG_LOUD, fmt_str , ## arg)
#define dbg_very_loud(fmt_str, arg...)		\
	dbg_log(DEBUG_VERY_LOUD, fmt_str , ## arg)

#endif /* #ifndef __DEBUG_H__ */
