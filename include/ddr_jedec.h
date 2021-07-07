/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DDR_JEDET_H__
#define __DDR_JEDET_H__

#include "hardware.h"
#include "arch/at91_ddrsdrc.h"
#include "ddramc.h"

#if defined(CONFIG_DDR_SET_BY_JEDEC)
/* Convert nanoseconds to clock cycles for given master clock in MHz */
#define NS2CYCLES(ns, clk) ((((ns) * (clk)) + 999) / 1000)

#if defined(CONFIG_LPDDR1)
static const struct ddram_timings ddr_ddram_timings = {
/* Reference to JESD209B Low Power Double Data Rate (LPDDR) SDRAM Standard */
#if defined(CONFIG_DDR_SPEED_200)
	.tras = 50,
	.trcd = 30,
	.trp = 30,
	.trc = 80,
	.trrd = 15,
	.twtr = 1,
#elif defined(CONFIG_DDR_SPEED_266)
	.tras = 45,
	.trcd = 22,
	.trp = 22,
	.trc = 67,
	.trrd = 15,
	.twtr = 1,
#elif defined(CONFIG_DDR_SPEED_333)
	.tras = 42,
	.trcd = 18,
	.trp = 18,
	.trc = 60,
	.trrd = 12,
	.twtr = 2,
#elif defined(CONFIG_DDR_SPEED_370)
	.tras = 42,
	.trcd = 16,
	.trp = 16,
	.trc = 58,
	.trrd = 11,
	.twtr = 2,
#elif defined(CONFIG_DDR_SPEED_400)
	.tras = 40,
	.trcd = 15,
	.trp = 15,
	.trc = 55,
	.trrd = 10,
	.twtr = 2,
#endif /* Endif of CONFIG_DDR_SPEED_200 */
	.twr = 15,
	.tmrd = 2,
	
#if defined(CONFIG_DDR_1_GBIT) || defined(CONFIG_DDR_2_GBIT)
/* 1GB/2GB */
	.trfc = 140,
#elif defined(CONFIG_DDR_512_MBIT)
/* 512MB */
	.trfc = 110,
#else
	.trfc = 80,
#endif /* Endif of CONFIG_DDR_1_GBIT */
/* In case of low-power DDR-SDRAM, this field is equivalent to tXSR timing. */
	.txsnr = 200,
	.txsrd = 0,
	.tfaw = 0,
	.txard = 0,
	.txards = 0,
	.txp = 25,
	.trtp = 2,
	.trpa = 0,
};

#elif defined(CONFIG_DDR2)
/* Reference to JEDEC STANDARD JESD79-2F DDR2 SDRAM SPECIFICATION (Revision of JESD79-2E)*/
static const struct ddram_timings ddr_ddram_timings = {
#if defined(CONFIG_DDR_SPEED_400)
	.tras = 40,
	.trcd = 15,
	.trp = 15,
	.trc = 55,
	.twtr = 10,
	.txard = 2,
	.txards = 6,
	.trpa = 15,
#elif defined(CONFIG_DDR_SPEED_533)
	.tras = 45,
	.trcd = 12,
	.trp = 12,
	.trc = 57,
	.twtr = 8,
	.txard = 2,
	.txards = 6,
	.trpa = 12,
#elif defined(CONFIG_DDR_SPEED_667)
	.tras = 45,
	.trcd = 15,
	.trp = 15,
	.trc = 60,
	.twtr = 8,
	.txard = 2,
	.txards = 7,
	.trpa = 12,
#elif defined(CONFIG_DDR_SPEED_800)
	.tras = 45,
	.trcd = 13,
	.trp = 13,
	.trc = 58,
	.twtr = 8,
	.txard = 2,
	.txards = 8,
	.trpa = 10,
#endif /* Endif of CONFIG_DDR_SPEED_400 */

#if defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_1_GBIT) || defined(CONFIG_DDR_512_MBIT)
	.trrd = 10,
#else
	.trrd = 8,
#endif /* Endif of CONFIG_DDR_2_GBIT */

	.twr = 15,
	.tmrd = 2,
	
#if defined(CONFIG_DDR_2_GBIT)
/* 2Gb addressing only support for A0 - A13 */
	.trfc = 198,
	.txsnr = 208,
#elif defined(CONFIG_DDR_1_GBIT)
/* 1GB */
	.trfc = 128,
	.txsnr = 138,
#elif defined(CONFIG_DDR_512_MBIT)
/* 512MB */
	.trfc = 105,
	.txsnr = 115,
#else
	.trfc = 75,
	.txsnr = 85,
#endif /* Endif of CONFIG_DDR_2_GBIT */
	.txsrd = 200,
	.txp = 2,
	.trtp = 8,

#if defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_1_GBIT) || defined(CONFIG_DDR_512_MBIT)
/* For page size is 2K , page size = 2 ^ COLBITS x ORG !O 8 */
	#if defined(CONFIG_DDR_SPEED_800)
		.tfaw = 45,
	#else
		.tfaw = 50,
	#endif /* Endif of CONFIG_DDR_SPEED_800 */
/* For page size = 1KB , page size = 2 ^ COLBITS x ORG !O 8*/
#else
	#if defined(CONFIG_DDR_SPEED_800)
		.tfaw = 35,
	#else
		.tfaw = 38,
	#endif /* Endif of CONFIG_DDR_SPEED_800 */
#endif
};

#elif defined(CONFIG_LPDDR2)
/* Reference to JEDEC STANDARD JESD209-2F Low Power Double Data Rate 2 (LPDDR2)(Revision of JESD79-2E)*/
static const struct ddram_timings ddr_ddram_timings = {
	.tras = 42,
	.trcd = 15,
	.trp = 3,
#if defined(CONFIG_BANK_4)
	.trc = 57,
#else
	.trc = 60,
#endif
	.twtr = 10,
	.trrd = 10,
	.twr = 15,
	/* For low-power DDR2-SDRAM and low-power DDR3-SDRAM, this field is equivalent to TMRW timing.*/
	.tmrd = 5,
	
#if defined(CONFIG_DDR_1_GBIT) || defined(CONFIG_DDR_2_GBIT) 
/* 1Gb | 2Gb */
	.trfc = 130,
	.txsnr = 140,
#else
	.trfc = 90,
	.txsnr = 100,
#endif
#if defined(CONFIG_LPDDR2_S2)
	.trpa = 15,
#else
	.trpa = 21,
#endif
	.txsrd = 0,
	.txp = 2,
	.trtp = 8,
	.tfaw = 60,
	.txard = 0,
	.txards = 0,
};

#elif defined(CONFIG_DDR3)
/* Reference to JEDEC STANDARD JESD79-3E DDR3 SDRAM Specification(Revision of JESD79-3D, August 2009)*/
static const struct ddram_timings ddr_ddram_timings = {
#if defined(CONFIG_DDR_SPEED_800)
	.tras = 38,
	.trcd = 13,
	.trp = 13,
	.trc = 50,
	.twtr = 8,
	.trrd = 10,
	.twr = 15,
	.tmrd = 4,
#elif defined(CONFIG_DDR_SPEED_1066)
	.tras = 37,
	.trcd = 12,
	.trp = 12,
	.trc = 49,
	.twtr = 8,
	.trrd = 10,
	.twr = 15,
	.tmrd = 4,
#elif defined(CONFIG_DDR_SPEED_1333)
	.tras = 36,
	.trcd = 11,
	.trp = 11,
	.trc = 47,
	.twtr = 8,
	.trrd = 8,
	.twr = 15,
	.tmrd = 4,
#else
#error "No CLK setting defined"
#endif
#if defined(CONFIG_DDR_2_GBIT) 
/* For 2GB */
	.trfc = 160,
	/* In case of DDR3-SDRAM, this field is equivalent to tXS timing */
	.txsnr = 170,
#elif defined(CONFIG_DDR_1_GBIT)
/* For 1GB */
	.trfc = 110,
	.txsnr = 120,
#else
	.trfc = 90,
	.txsnr = 100,
#endif
	.txsrd = 0,
	.txp = 8,
	.trtp = 8,
	.trpa = 0,
	.tfaw = 50,
	.txard = 0,
	.txards = 0,
};
#endif /* Endif of LPDDR1 */
#endif /* Endif of CONFIG_DDR_SET_JEDEC */
#endif /* Endif __DDR_JEDET_H__ */
