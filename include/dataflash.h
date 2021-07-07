/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DATAFLASH_H__
#define __DATAFLASH_H__

extern int load_dataflash(struct image_info *image);

extern int dataflash_page0_erase(void);

#endif

