/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SDRAMC_H__
#define __SDRAMC_H__

struct sdramc_register {
	unsigned int mr;
	unsigned int tr;
	unsigned int cr;
	unsigned int lpr;
	unsigned int mdr;
	unsigned int cfr1;
};

void sdramc_init(void);

int sdramc_initialize(struct sdramc_register *sdramc_config,
			unsigned int sdram_address);

unsigned int get_sdram_size(void);
#endif	/* #ifndef __SDRAMC_H__ */
