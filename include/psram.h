/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 * Courtesy of Epsilon Group
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
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
 * File Name           : sdramc.h
 * Object              :
 * Creation            : US Feb 9th 2009
 *-----------------------------------------------------------------------------
 */
#ifndef PSRAM_H_
#define PSRAM_H_

/* PSRAM Timings */
#define AT91C_PSRAM_NWE_SETUP    (0 << 0)
#define AT91C_PSRAM_NCS_WR_SETUP (0 << 8)
#define AT91C_PSRAM_NRD_SETUP    (0 << 16)
#define AT91C_PSRAM_NCS_RD_SETUP (0 << 24)

#define AT91C_PSRAM_NWE_PULSE    (4 << 0)
#define AT91C_PSRAM_NCS_WR_PULSE (5 << 8)
#define AT91C_PSRAM_NRD_PULSE    (2 << 16)
#define AT91C_PSRAM_NCS_RD_PULSE (5 << 24)

#define AT91C_PSRAM_NWE_CYCLE    (5 << 0)
#define AT91C_PSRAM_NRD_CYCLE    (7 << 16)

#define MICRON_RCR               0x0000
#define MICRON_BCR               0x0001
#define MICRON_PAGE_MODE_ENABLE  0x0090
#define MICRON_8MB_ADDRESS_MAX   0x707FFFFF

#if	defined(CONFIG_PSRAM)
extern void psram_hw_init(void);
#endif
#endif                          /* PSRAM_H_ */
