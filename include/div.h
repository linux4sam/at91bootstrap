/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DIV_H__
#define __DIV_H__

extern unsigned int div(unsigned int dividend, unsigned int divisor);
extern unsigned int mod(unsigned int dividend, unsigned int divisor);
extern int division(unsigned int dividend,
		unsigned int divisor,
		unsigned int *quotient,
		unsigned int *remainder);
#endif
