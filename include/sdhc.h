/*
 * Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SDHC_H__
#define	__SDHC_H__

int sdcard_register_sdhc(struct sd_card *sdcard);

struct adma_desc {
	unsigned short cmd;
	unsigned short len;
	unsigned int addr;
} __attribute__ ((packed, aligned(4)));

#endif
