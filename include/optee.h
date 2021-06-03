/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __OPTEE_H__
#define __OPTEE_H__

void optee_load(void);
void optee_init_nw_params(void *nw_addr, unsigned int r0,
			  unsigned int r1, unsigned int r2);

#endif
