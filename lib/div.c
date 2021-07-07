// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

int division(unsigned int dividend,
		unsigned int divisor,
		unsigned int *quotient,
		unsigned int *remainder)
{
	unsigned int shift;
	unsigned int divisor_shift;
	unsigned int factor = 0;
	unsigned char end_flag = 0;

	if (!divisor)
		return 0xffffffff;

	if (dividend < divisor) {
		*quotient = 0;
		*remainder = dividend;
		return 0;
	}

	while (dividend >= divisor) {
		for (shift = 0, divisor_shift = divisor;
			dividend >= divisor_shift;
			divisor_shift <<= 1, shift++) {
			if (dividend - divisor_shift < divisor_shift) {
				factor += 1 << shift;
				dividend -= divisor_shift;
				end_flag = 1;
				break;
			}
		}

		if (end_flag)
			continue;

		factor += 1 << (shift - 1);
		dividend -= divisor_shift >> 1;
	}

	if (quotient)
		*quotient = factor;

	if (remainder)
		*remainder = dividend;

	return 0;
}

unsigned int div(unsigned int dividend, unsigned int divisor)
{
	unsigned int quotient = 0;
	unsigned int remainder = 0;
	int ret;

	ret = division(dividend, divisor, &quotient, &remainder);
	if (ret)
		return 0xffffffff;

	return quotient;
}

unsigned int mod(unsigned int dividend, unsigned int divisor)
{
	unsigned int quotient = 0;
	unsigned int remainder = 0;
	int ret;

	ret = division(dividend, divisor, &quotient, &remainder);
	if (ret)
		return 0xffffffff;

	return remainder;
}
