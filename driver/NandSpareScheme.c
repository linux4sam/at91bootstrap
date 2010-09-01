/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "NandSpareScheme.h"

#ifdef CONFIG_NANDFLASH
//------------------------------------------------------------------------------
//         Exported variables
//------------------------------------------------------------------------------
/// Spare area placement scheme for 256 byte pages.
struct NandSpareScheme Spare_256 = {

    // Bad block marker is at position #5
    5,
    // 3 ecc bytes
    3,
    // Ecc bytes positions
    {0, 1, 2},
    // 4 extra bytes
    4,
    // Extra bytes positions
    {3, 4, 6, 7}
};

/// Spare area placement scheme for 512 byte pages.
struct NandSpareScheme Spare_512 = {

    // Bad block marker is at position #5
    5,
    // 6 ecc bytes
    6,
    // Ecc bytes positions
    {0, 1, 2, 3, 6, 7},
    // 8 extra bytes
    8,
    // Extra bytes positions
    {8, 9, 10, 11, 12, 13, 14, 15}
};

/// Spare area placement scheme for 2048 byte pages.
struct NandSpareScheme Spare_2048 = {

    // Bad block marker is at position #0
    0,
    // 24 ecc bytes
    24,
    // Ecc bytes positions
    {40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
     58, 59, 60, 61, 62, 63},
    // 38 extra bytes
    38,
    // Extra bytes positions
    {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39}
};
#endif

/// Spare area placement scheme for 4096 byte pages.
#if 0
const struct NandSpareScheme Spare_4096 = {

    // Bad block marker is at position #0
    0,
    // 48 ecc bytes
    48,
    // Ecc bytes positions
    {80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94,
     95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
     110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124,
     125, 126, 127},
    // 78 extra bytes
    78,
    // Extra bytes positions
    {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
     21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
     40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
     59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
     78, 79}
};
#endif

#ifdef CONFIG_NANDFLASH
//------------------------------------------------------------------------------
/// Reads ECC information from a spare area using the provided scheme.
/// \param scheme  Pointer to a NandSpareScheme instance.
/// \param spare  Spare area buffer.
/// \param ecc  ECC buffer.
//------------------------------------------------------------------------------
void NandSpareScheme_ReadEcc(struct NandSpareScheme *scheme,
                             unsigned char *spare, unsigned char *ecc)
{
    unsigned int i;

    for (i = 0; i < scheme->numEccBytes; i++) {

        ecc[i] = spare[scheme->eccBytesPositions[i]];
    }
}

#endif
