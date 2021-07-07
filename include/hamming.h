/*
 * Copyright (C) 2008 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __HAMMING_H__
#define __HAMMING_H__

/*
 *------------------------------------------------------------------------------
 *         Macro Defines
 *------------------------------------------------------------------------------
 */
/* A single bit was incorrect but has been recovered */
#define Hamming_ERROR_SINGLEBIT		1

/*  The original code has been corrupted */
#define Hamming_ERROR_ECC		2

/*  Multiple bits are incorrect in the data and they cannot be corrected */
#define Hamming_ERROR_MULTIPLEBITS	3

/*
 *------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------
 */

extern unsigned char Hamming_Verify256x(unsigned char *data,
					unsigned int size,
					const unsigned char *ecc_from_nand);

#endif /* #ifndef __HAMMING_H__ */
