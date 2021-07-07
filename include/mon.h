/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __MON_H__
#define __MON_H__

extern void monitor_init(void);

extern void init_loadkernel_args(unsigned int r0,
				unsigned int r1,
				unsigned int r2,
				unsigned int r3);

#endif
