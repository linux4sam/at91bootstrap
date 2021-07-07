/*
 * Copyright (C) 2017 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BITOPS_H_
#define BITOPS_H_

#define IS_POWER_OF_TWO(n)	((n) && !((n) & ((n) - 1)))

static inline int fls(int value)
{
	int i;

	for (i = 31; i >= 0; i--)
		if (value & (1 << i))
			return i + 1;

	return 0;
}

#endif /* BITOPS_H_ */
