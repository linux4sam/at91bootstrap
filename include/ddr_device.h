/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2020, Atmel Corporation
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
 */
#ifndef __DDR_DEVICE_H__
#define __DDR_DEVICE_H__

#include "hardware.h"
#include "arch/at91_ddrsdrc.h"
#include "ddramc.h"

#if defined(CONFIG_DDR_SET_BY_DEVICE)
static const struct ddram_timings ddr_ddram_timings = {
#if defined(CONFIG_DDR_MT41K128M16_D2)
/* Two DDR3L(MT41H128M16JT-125-K = 16 Mbit x 16 x 8 banks), total 4Gbit on SAMA5D2 Xplained Ultra Evaluation Kit*/
#if defined(CONFIG_BUS_SPEED_116MHZ)
	.tras = 5,
	.trcd = 2,
	.twr = 4,
	.trc = 6,
	.trp = 2,
	.trrd = 4,
	.twtr = 4,
	.tmrd = 4,
	.trfc = 19,
	.txsnr = 21,
	.txsrd = 0,
	.txp = 10,
	.txard = 0,
	.txards = 0,
	.trpa = 0,
	.trtp = 4,
	.tfaw = 5,
#elif defined(CONFIG_BUS_SPEED_166MHZ)
	.tras = 6,
	.trcd = 3,
	.twr = 4,
	.trc = 9,
	.trp = 3,
	.trrd = 4,
	.twtr = 4,
	.tmrd = 4,
	.trfc = 27,
	.txsnr = 29,
	.txsrd = 0,
	.txp = 3,
	.txard = 0,
	.txards = 0,
	.trpa = 0,
	.trtp = 4,
	.tfaw = 7,
#else
#error "No CLK setting defined"
#endif /* Endif of CONFIG_BUS_SPEED_116MHZ */
#elif defined(CONFIG_DDR_W972GG6KB_D2)
/* Two DDR2 (W972GG6KB-25-2 Gbits = 16 Mbits x 16 x 8 banks), total 4 Gbits on the SAMA5D2-PTC-EK */
/* all timings in nCK */
	.tras = 8,
	.trcd = 3,
	.twr = 3,
	.trc = 10,
	.trp = 3,
	.trrd = 4,
	.twtr = 4,
	.tmrd = 2,
	.trfc = 33,
	.txsnr = 35,
	.txsrd = 200,
	.txp = 3,
	.txard = 2,
	.txards = 8,
	.trpa = 4,
	.trtp = 2,
	.tfaw = 8,
#elif defined(CONFIG_DDR_W972GG6KB_9X60)
/* DDR2 (W972GG6KB-25-2 Gbits = 16 Mbits x 16 x 8 banks), total 2 Gbits on the SAM9X60-EK */
/* all timings in nCK */
	.tras = 8,
	.trcd = 3,
	.twr = 3,
	.trc = 11,
	.trp = 3,
	.trrd = 2,
	.twtr = 2,
	.tmrd = 2,
	.trfc = 26,
	.txsnr = 28,
	.txsrd = 200,
	.txp = 2,
	.txard = 8,
	.txards = 2,
	.trpa = 3,
	.trtp = 2,
	.tfaw = 7,

#elif defined(CONFIG_DDR_W971GG6SB_9X60)
/* DDR2 (W971GG6SB = 8 Mwords x 8 Banks x 16 bits), total 1 Gbit in SiP on the SAM9X60_DDR2_SIP_EB */
/* all timings in nCK */
	.tras = 8,
	.trcd = 3,
	.twr = 3,
	.trc = 11,
	.trp = 3,
	.trrd = 2,
	.twtr = 2,
	.tmrd = 2,
	.trfc = 26,
	.txsnr = 28,
	.txsrd = 200,
	.txp = 2,
	.txard = 2,
	.txards = 7,
	.trpa = 4,
	.trtp = 2,
	.tfaw = 10,
#elif defined(CONFIG_DDR_W971GG6SB_D2)
/* DDR2 (W971GG6SB = 8 Mwords x 8 Banks x 16 bits), total 1 Gbit in SiP on the SAMA5D2-SOM-EK */
/* all timings in nCK */
	.tras = 7,
	.trcd = 3,
	.twr = 3,
	.trc = 9,
	.trp = 3,
	.trrd = 2,
	.twtr = 2,
	.tmrd = 2,
	.trfc = 22,
	.txsnr = 23,
	.txsrd = 200,
	.txp = 2,
	.txard = 2,
	.txards = 8,
	.trpa = 4,
	.trtp = 2,
	.tfaw = 8,
#elif defined(CONFIG_DDR_AD220032D)
/* LPDDR2 (AD220032D = 8 Mwords x 8 Banks x 32 bits), total 2 Gbit in SiP on SAMA5D27-WLSOM-EK */
	.tras = 7,
	.trcd = 3,
	.twr = 4,
	.trc = 11,
	.trp = 4,
	.trrd = 2,
	.twtr = 2,
	.tmrd = 5,
	.trfc = 21,
	.txsnr = 0,
	.txsrd = 23,
	.txp = 2,
	.txard = 0,
	.txards = 0,
	.trpa = 4,
	.trtp = 2,
	.tfaw = 10,
#else
#error "DDR-SDRAM device is not supported!"
#endif /* Endif of  CONFIG_DDR_MT41K128M16_D2 */
};
#endif /* Endif of CONFIG_DDR_SET_BY_DEVICE */
#endif /* Endif __DDR_DEVICE_H__ */