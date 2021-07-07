/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SVC_MGR_H__
#define __SVC_MGR_H__

/* A structure which can hold the contents of the registers r0-r7 */
struct smc_args_t {
	unsigned int	r0;
	unsigned int	r1;
	unsigned int	r2;
	unsigned int	r3;
	unsigned int	r4;
	unsigned int	r5;
	unsigned int	r6;
	unsigned int	r7;
};

#endif
