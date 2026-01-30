/*
 * Copyright (C) 2017 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
#ifndef _SIZE_T
typedef unsigned long size_t;
typedef signed long ssize_t;
#endif
#ifndef _STDBOOL_H
typedef unsigned char bool;
#define false	0U
#define true	1U
#endif

#endif /* TYPES_H_ */
