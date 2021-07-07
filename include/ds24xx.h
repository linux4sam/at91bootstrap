/*
 * Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DS24XX_H__
#define __DS24XX_H__

extern unsigned int enumerate_all_rom(void);
extern int ds24xx_read_memory(int chip_index, unsigned char addrh,
				unsigned char addrl, int len, unsigned char *p);
extern void one_wire_hw_init(void);

#endif
