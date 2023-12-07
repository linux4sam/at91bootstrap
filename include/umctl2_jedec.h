/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __UMCTL2_JEDET_H__
#define __UMCTL2_JEDET_H__

#if defined(CONFIG_DDR2)
#if defined(CONFIG_DDR2_SPEED_BIN_400B) ||\
	defined(CONFIG_DDR2_SPEED_BIN_400C)
#define DDR2_SPEED_400
#elif defined(CONFIG_DDR2_SPEED_BIN_533B) ||\
	defined(CONFIG_DDR2_SPEED_BIN_533C)
#define DDR2_SPEED_533
#elif defined(CONFIG_DDR2_SPEED_BIN_667C) ||\
	defined(CONFIG_DDR2_SPEED_BIN_667D)
#define DDR2_SPEED_677
#elif defined(CONFIG_DDR2_SPEED_BIN_800C) ||\
	defined(CONFIG_DDR2_SPEED_BIN_800D) ||\
	defined(CONFIG_DDR2_SPEED_BIN_800E)
#define DDR2_SPEED_800
#elif defined(CONFIG_DDR2_SPEED_BIN_1066E) ||\
	defined(CONFIG_DDR2_SPEED_BIN_1066F)
#define DDR2_SPEED_1066
#endif

#if defined(CONFIG_DDR_128_MBIT)
	#define TRFC		75000
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	12
	#define NB_COL_BITS	9
	#define PAGE_SIZE	1
#elif defined(CONFIG_DDR_256_MBIT)
	#define TRFC		75000
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	9
	#define PAGE_SIZE	1
#elif defined(CONFIG_DDR_512_MBIT)
	#define TRFC		105000
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#elif defined(CONFIG_DDR_1_GBIT)
	#define TRFC		127500
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#elif defined(CONFIG_DDR_2_GBIT)
	#define TRFC		195000
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#elif defined(CONFIG_DDR_4_GBIT)
	#define TRFC		327500
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#endif

#if (PAGE_SIZE == 1)
	#define TRRD		7500
#else
	#define TRRD		10000
#endif
#if defined(DDR2_SPEED_400)
	#define TXARDS		6 - AL
	#define TWTR		10000
	#define TXP		2
	#define TXARD		2
#if(PAGE_SIZE == 1)
	#define TFAW		37500
#else
	#define TFAW		50000
#endif
#elif defined(DDR2_SPEED_533)
	#define TXARDS		6 - AL
	#define TWTR		7500
	#define TXP		2
	#define TXARD		2
#if (PAGE_SIZE == 1)
	#define TFAW		37500
#else
	#define TFAW		50000
#endif
#elif defined(DDR2_SPEED_667)
	#define TXARDS		7 - AL
	#define TWTR		7500
	#define TXP		2
	#define TXARD		2
#if (PAGE_SIZE == 1)
	#define TFAW		37500
#else
	#define TFAW		50000
#endif
#elif defined(DDR2_SPEED_800)
	#define TXARDS		8 - AL
	#define TWTR		7500
	#define TXP		2
	#define TXARD		2
#if (PAGE_SIZE == 1)
	#define TFAW		35000
#else
	#define TFAW		45000
#endif
#elif defined(DDR2_SPEED_1066)
	#define TXARDS		10 - AL
	#define TWTR		7500
	#define TXP		3
	#define TXARD		3
#if (PAGE_SIZE == 1)
	#define TFAW		35000
#else
	#define TFAW		45000
#endif
#endif

#if defined(CONFIG_DDR2_SPEED_BIN_400B)
	#define TRP		15000
	#define TRC		55000
	#define CL		3
#elif defined(CONFIG_DDR2_SPEED_BIN_400C)
	#define TRP		20000
	#define TRC		65000
	#define CL		4
#elif defined(CONFIG_DDR2_SPEED_BIN_533B)
	#define TRP		11250
	#define TRC		56250
	#define CL		3
#elif  defined(CONFIG_DDR2_SPEED_BIN_533C)
	#define TRP		15000
	#define TRC		60000
#if (DDR_CLOCK_PERIOD >= 5000)
	#define CL		3
#else
	#define CL		4
#endif
#elif defined(CONFIG_DDR2_SPEED_BIN_667C)
	#define TRP		12000
	#define TRC		57000
	#define CL		4
#elif defined(CONFIG_DDR2_SPEED_BIN_667D)
	#define TRP		15000
	#define TRC		60000
#if (DDR_CLOCK_PERIOD >= 3750)
	#define CL		4
#else
	#define CL		5
#endif
#elif defined(CONFIG_DDR2_SPEED_BIN_800C)
	#define TRP		10000
	#define TRC		55000
	#define CL		4
#elif defined(CONFIG_DDR2_SPEED_BIN_800D)
	#define TRP		12500
	#define TRC		57500
#if (DDR_CLOCK_PERIOD >= 3750)
	#define CL		4
#else
	#define CL		5
#endif
#elif defined(CONFIG_DDR2_SPEED_BIN_800E)
	#define TRP		15000
	#define TRC		60000
#if (DDR_CLOCK_PERIOD >= 3750)
	#define CL		4
#elif (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
#else
	#define CL		6
#endif
#elif defined(CONFIG_DDR2_SPEED_BIN_1066E)
	#define TRP		11250
	#define TRC		56250
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		4
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
#else
	#define CL		6
#endif
#elif defined(CONFIG_DDR2_SPEED_BIN_1066F)
	#define TRP		13125
	#define TRC		58125
#if (DDR_CLOCK_PERIOD >= 3750)
	#define CL		4
#elif (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
#else
	#define CL		7
#endif
#endif

#define TRCD			TRP

#define CWL			(CL - 1)
#define WL			(CWL + AL)
#define BL			8
#define AL			0
#define RL			(CL + AL)

#if defined(DDR2_SPEED_400) ||\
    defined(DDR2_SPEED_533) ||\
    defined(DDR2_SPEED_667)
#if ((CL + AL) < 4)
	#define ODT_NOT_SUPPORTED
	#define RD_ODT_DELAY	0
#else
	#define RD_ODT_DELAY	(CL + AL - 4)
#endif

#define RD_ODT_HOLD		((BL == 8) ? 6 : 4)
#if ((CWL + AL) < 3)
	#define ODT_NOT_SUPPORTED
	#define WR_ODT_DELAY	0
#else
	#define WR_ODT_DELAY	(CWL + AL - 3)
#endif

#define WR_ODT_HOLD		((BL == 8) ? 5 : 3)
#elif defined(DDR2_SPEED_800)
#if ((CL + AL) < 4)
	#define ODT_NOT_SUPPORTED
	#define RD_ODT_DELAY	0
#else
	#define RD_ODT_DELAY	((CL + AL) - 4)
#endif
	#define RD_ODT_HOLD	((BL == 8) ? 6 : 4)
#if ((CWL + AL) < 4)
	#define ODT_NOT_SUPPORTED
	#define WR_ODT_DELAY	0
#else
	#define WR_ODT_DELAY	((CWL + AL) - 4)
#endif

#define WR_ODT_HOLD		((BL == 8) ? 6 : 4)
#elif defined(DDR2_SPEED_1066)
#if ((CL + AL) < 5)
	#define ODT_NOT_SUPPORTED
	#define RD_ODT_DELAY	0
#else
	#define RD_ODT_DELAY	((CL + AL) -5)
#endif
	#define RD_ODT_HOLD	((BL == 8) ? 7 : 5)
#if ((CWL + AL) < 5)
	#define ODT_NOT_SUPPORTED
	#define WR_ODT_DELAY	0
#else
	#define WR_ODT_DELAY ((CWL + AL) - 5)
#endif
#define WR_ODT_HOLD		((BL == 8) ? 7 : 5)
#endif

#if (defined(ODT_ENABLE) && !defined(ODT_NOT_SUPPORTED))
	#define ODT_ENABLE_CHECK	1
#else
	#define ODT_ENABLE_CHECK	0
#endif

#elif defined(CONFIG_DDR3)

#if defined(CONFIG_DDR3_SPEED_BIN_800D) ||\
    defined(CONFIG_DDR3_SPEED_BIN_800E)
#define DDR3_SPEED_800
#endif
#if defined(CONFIG_DDR3_SPEED_BIN_1066E) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1066F)||\
    defined(CONFIG_DDR3_SPEED_BIN_1066G) 
#define DDR3_SPEED_1066
#endif
#if defined(CONFIG_DDR3_SPEED_BIN_1333F) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1333G) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1333H) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1333J)
#define DDR3_SPEED_1333
#endif
#if defined(CONFIG_DDR3_SPEED_BIN_1600G) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1600H) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1600J) ||\
    defined(CONFIG_DDR3_SPEED_BIN_1600K)
#define DDR3_SPEED_1600
#endif
#if defined(CONFIG_DDR3_SPEED_BIN_1866J) ||\
   defined(CONFIG_DDR3_SPEED_BIN_1866K) ||\
   defined(CONFIG_DDR3_SPEED_BIN_1866L) ||\
   defined(CONFIG_DDR3_SPEED_BIN_1866M)
#define DDR3_SPEED_1866
#endif
#if defined(CONFIG_DDR3_SPEED_BIN_2133K) ||\
    defined(CONFIG_DDR3_SPEED_BIN_2133L) ||\
    defined(CONFIG_DDR3_SPEED_BIN_2133M) ||\
    defined(CONFIG_DDR3_SPEED_BIN_2133N)
#define DDR3_SPEED_2133
#endif

#ifdef CONFIG_DDR_512_MBIT
	#define TRFC		90000
	#define NB_ROW_BITS	12
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#endif
#ifdef CONFIG_DDR_1_GBIT
	#define TRFC		110000
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#endif
#ifdef CONFIG_DDR_2_GBIT
	#define TRFC		160000
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#endif
#ifdef CONFIG_DDR_4_GBIT
	#define TRFC		300000
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#endif
#ifdef CONFIG_DDR_8_GBIT
	#define TRFC		350000
	#define NB_ROW_BITS	16
	#define NB_COL_BITS	10
	#define PAGE_SIZE	2
#endif

#define NB_BANK_BITS		3
#if defined(DDR3_SPEED_800)
	#define TCKE		MAX(3 * DDR_CLOCK_PERIOD, 7500)
	#if (PAGE_SIZE == 1)
		#define TFAW	40000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 10000)
	#else
		#define TFAW	50000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 10000)
	#endif
#elif defined(DDR3_SPEED_1066)
	#define TCKE		MAX(3 * DDR_CLOCK_PERIOD, 5625)
	#if (PAGE_SIZE == 1)
		#define TFAW	37500
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 7500)
	#else
		#define TFAW	50000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 10000)
	#endif
#elif defined(DDR3_SPEED_1333)
	#define TCKE		MAX(3 * DDR_CLOCK_PERIOD, 5625)
	#if (PAGE_SIZE == 1)
		#define TFAW	30000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 6000)
	#else
		#define TFAW	45000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 7500)
	#endif
#elif defined(DDR3_SPEED_1600)
	#define TCKE		MAX(3 * DDR_CLOCK_PERIOD, 5000)
	#if (PAGE_SIZE == 1)
		#define TFAW	30000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 6000)
	#else
		#define TFAW	40000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 7500)
	#endif
#elif defined(DDR3_SPEED_1866)
	#define TCKE		MAX(3 * DDR_CLOCK_PERIOD, 5000)
	#if (PAGE_SIZE == 1)
		#define TFAW 27000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 5000)
	#else
		#define TFAW	35000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 6000)
	#endif
#elif defined(DDR3_SPEED_2133)
	#define TCKE		MAX(3 * DDR_CLOCK_PERIOD, 5000)
	#if (PAGE_SIZE == 1)
		#define TFAW	25000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 5000)
	#else
		#define TFAW	35000
		#define TRRD	MAX(4 * DDR_CLOCK_PERIOD, 6000)
	#endif
#endif

#if defined(CONFIG_DDR3_SPEED_BIN_800D)
	#define TRC		50000
	#define TRP		12500
	#define TRASMIN		37500
	#define CL		5
	#define CWL		5
#elif defined(CONFIG_DDR3_SPEED_BIN_800E)
	#define TRC		52500
	#define TRP		15000
	#define TRASMIN		37500
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
	#define CWL		5
#else
	#define CL		6
	#define CWL		5
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1066E)
	#define TRC		48750
	#define TRP		11250
	#define TRASMIN		37500
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#else
	#define CL		6
	#define CWL		6
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1066F)
	#define TRC		50625
	#define TRP		13125
	#define TRASMIN		37500
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#else
	#define CL		7
	#define CWL		6
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1066G)
	#define TRC		52500
	#define TRP		15000
	#define TRASMIN		37500
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#else
	#define CL		8
	#define CWL		6
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1333F)
	#define TRC		46500
	#define TRP		10500
	#define TRASMIN		36000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		6
	#define CWL		6
#else
	#define CL		7
	#define CWL		7
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1333G)
	#define TRC		48000
	#define TRP		12000
	#define TRASMIN		36000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#else
	#define CL		8
	#define CWL		7
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1333H)
	#define TRC		49500
	#define TRP		13500
	#define TRASMIN		36000
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#else
	#define CL		9
	#define CWL		7
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1333J)
	#define TRC		51000
	#define TRP		15000
	#define TRASMIN		36000
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		8
	#define CWL		6
#else
	#define CL		10
	#define CWL		7
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1600G)
	#define TRC		45000
	#define TRP		10000
	#define TRASMIN		35000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		6
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		7
	#define CWL		7
#else
	#define CL		8
	#define CWL		8
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1600H)
	#define TRC		46250
	#define TRP		11250
	#define TRASMIN		35000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		6
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		8
	#define CWL		7
#else
	#define CL		9
	#define CWL		8
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1600J)
	#define TRC		47500
	#define TRP		12500
	#define TRASMIN		35000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		9
	#define CWL		7
#else
	#define CL		10
	#define CWL		8
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1600K)
	#define TRC		48750
	#define TRP		13750
	#define TRASMIN		35000
#if (DDR_CLOCK_PERIOD >= 3000)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		8
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		9
	#define CWL		7
#else
	#define CL		11
	#define CWL		8
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1866J)
	#define TRC		44700
	#define TRP		10700
	#define TRASMIN		34000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		6
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		8
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		9
	#define CWL		8
#else
	#define CL		11
	#define CWL		9
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1866K)
	#define TRC		45770
	#define TRP		11770
	#define TRASMIN		34000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		8
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		10
	#define CWL		8
#else
	#define CL		11
	#define CWL		9
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1866L)
	#define TRC		46840
	#define TRP		12840
	#define TRASMIN		34000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		9
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		11
	#define CWL		8
#else
	#define CL		12
	#define CWL		9
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_1866M)
	#define TRC		47910
	#define TRP		13910
	#define TRASMIN		34000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		8
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		10
	#define CWL		7
#else
	#define CL		13
	#define CWL		9
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_2133K)
	#define TRC		43285
	#define TRP		10285
	#define TRASMIN		34000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		6
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		7
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		9
	#define CWL		8
#elif (DDR_CLOCK_PERIOD >= 1070)
	#define CL		10
	#define CWL		9
#else
	#define CL		11
	#define CWL		10
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_2133L)
	#define TRC		44220
	#define TRP		11220
	#define TRASMIN		33000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		6
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		8
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		9
	#define CWL		8
#elif (DDR_CLOCK_PERIOD >= 1070)
	#define CL		11
	#define CWL		9
#else
	#define CL		12
	#define CWL		10
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_2133M)
	#define TRC		45155
	#define TRP		12155
	#define TRASMIN		33000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		5
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		9
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		10
	#define CWL		8
#elif (DDR_CLOCK_PERIOD >= 1070)
	#define CL		12
	#define CWL		9
#else
	#define CL		13
	#define CWL		10
#endif
#elif defined(CONFIG_DDR3_SPEED_BIN_2133N)
	#define TRC		46090
	#define TRP		13090
	#define TRASMIN		33000
#if (DDR_CLOCK_PERIOD >= 2500)
	#define CL		6
	#define CWL		5
#elif (DDR_CLOCK_PERIOD >= 1875)
	#define CL		7
	#define CWL		6
#elif (DDR_CLOCK_PERIOD >= 1500)
	#define CL		9
	#define CWL		7
#elif (DDR_CLOCK_PERIOD >= 1250)
	#define CL		11
	#define CWL		8
#elif (DDR_CLOCK_PERIOD >= 1070)
	#define CL		13
	#define CWL		9
#else
	#define CL		14
	#define CWL		10
#endif
#endif
#define BL			8
#define AL			0
#define RL			(CL + AL)
#define WL			(CWL + AL)
#define TRCD			TRP

#elif defined(CONFIG_LPDDR2)
#if defined(CONFIG_DDR_128_MBIT)
	#define TREFI		15600000
	#define TREFIpb		15600000
	#define TRFCab		90000
	#define TRFCpb		90000
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	12
	#define NB_COL_BITS	9
#elif defined(CONFIG_DDR_256_MBIT)
	#define TREFI		7800000
	#define TREFIpb		7800000
	#define TRFCab		90000
	#define TRFCpb		90000
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	9
#elif defined(CONFIG_DDR_512_MBIT)
	#define TREFI		7800000
	#define TREFIpb		7800000
	#define TRFCab		90000
	#define TRFCpb		90000
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	10
	#define NB_COL_BITS	9
#elif defined(CONFIG_DDR_1_GBIT)
	#define TREFI		7800000
	#define TREFIpb		7800000
	#define TRFCab		130000
	#define TRFCpb		130000
#if defined(CONFIG_LPDDR2_S2)
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	14
#elif defined(CONFIG_LPDDR2_S4)
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	13
#endif
	#define NB_COL_BITS	10
#elif defined(CONFIG_DDR_2_GBIT)
	#define TREFI		3900000
	#define TREFIpb		3900000
	#define TRFCab		130000
	#define TRFCpb		130000
#if defined(CONFIG_LPDDR2_S2)
	#define NB_BANK_BITS	2
	#define NB_ROW_BITS	15
#elif defined(CONFIG_LPDDR2_S4)
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	14
#endif
	#define NB_COL_BITS	10
#elif defined(CONFIG_DDR_4_GBIT)
	#define TREFI		3900000
	#define TREFIpb		487500
	#define TRFCab		130000
	#define TRFCpb		60000
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	11
#elif defined(CONFIG_DDR_8_GBIT)
	#define TREFI		3900000
	#define TREFIpb		487500
	#define TRFCab		210000
	#define TRFCpb		90000
	#define NB_BANK_BITS	3
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	11
#endif

#if defined(CONFIG_DDR_EXT_TEMP_RANGE)
#if defined(LPDDR2_SPEED_1066)
	#define TDQSCK_MAX	5620
#else
	#define TDQSCK_MAX	6000
#endif
#else
	#define TDQSCK_MAX	5500
#endif

#if defined(CONFIG_LPDDR2_SPEED_333)
	#define TWTR		MAX(10000, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(60000, 8 * DDR_CLOCK_PERIOD)
#elif defined(CONFIG_LPDDR2_SPEED_400)
	#define TWTR		MAX(10000, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(50000, 8 * DDR_CLOCK_PERIOD)
#elif defined(CONFIG_LPDDR2_SPEED_533)
	#define TWTR		MAX( 7500, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(50000, 8 * DDR_CLOCK_PERIOD)
#elif defined(CONFIG_LPDDR2_SPEED_667)
	#define TWTR		MAX( 7500, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(50000, 8 * DDR_CLOCK_PERIOD)
#elif defined(CONFIG_LPDDR2_SPEED_800)
	#define TWTR		MAX( 7500, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(50000, 8 * DDR_CLOCK_PERIOD)
#elif defined(CONFIG_LPDDR2_SPEED_933)
	#define TWTR		MAX( 7500, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(50000, 8 * DDR_CLOCK_PERIOD)
#elif defined(CONFIG_LPDDR2_SPEED_1066)
	#define TWTR		MAX( 7500, 2 * DDR_CLOCK_PERIOD)
	#define TFAW		MAX(50000, 8 * DDR_CLOCK_PERIOD)
#endif

#if (CONFIG_MEM_CLOCK <= 166)
	#define RL		3
	#define WL		1
#elif (CONFIG_MEM_CLOCK <= 200)
	#define RL		3
	#define WL		1
#elif (CONFIG_MEM_CLOCK <= 266)
	#define RL		4
	#define WL		2
#elif (CONFIG_MEM_CLOCK <= 333)
	#define RL		5
	#define WL		2
#elif (CONFIG_MEM_CLOCK <= 400)
	#define RL		6
	#define WL		3
#elif (CONFIG_MEM_CLOCK <= 466)
	#define RL		7
	#define WL		4
#else
	#define RL		8
	#define WL		4
#endif

#if defined(CONFIG_LPDDR2_S4)
	#define TCCD		2
#else
	#define TCCD		1
#endif

#elif defined(CONFIG_LPDDR3)
	#define NB_BANK_BITS	3
#if defined(CONFIG_DDR_1_GBIT)
	#define TREFI		7800000
	#define TREFIpb		975000
	#define TRFCab		130000
	#define TRFCpb		60000
#if defined(CONFIG_DBW_16)
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	10
#endif
#if defined(CONFIG_DBW_32)
	#define NB_ROW_BITS	13
	#define NB_COL_BITS	9
#endif
#elif defined(CONFIG_DDR_2_GBIT)
	#define TREFI		3900000
	#define TREFIpb		487500
	#define TRFCab		130000
	#define TRFCpb		60000
#if defined(CONFIG_DBW_16)
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	10
#endif
#if defined(CONFIG_DBW_32)
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	9
#endif

#elif defined(CONFIG_DDR_4_GBIT)
	#define TREFI		3900000
	#define TREFIpb		487500
	#define TRFCab		130000
	#define TRFCpb		60000
#if defined(CONFIG_DBW_16)
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	11
#endif
#if defined(CONFIG_DBW_32)
	#define NB_ROW_BITS	14
	#define NB_COL_BITS	10
#endif
#elif defined(CONFIG_DDR_6_GBIT)
	#define TREFI		3900000
	#define TREFIpb		487500
	#define TRFCab		210000
	#define TRFCpb		90000
#if defined(CONFIG_DBW_16)
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	11
#endif
#if defined(CONFIG_DBW_32)
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	11
#endif
#elif defined(CONFIG_DDR_8_GBIT)
	#define TREFI		3900000
	#define TREFIpb		487500
	#define TRFCab		210000
	#define TRFCpb		90000
#if defined(CONFIG_DBW_16)
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	11
#endif
#if defined(CONFIG_DBW_32)
	#define NB_ROW_BITS	15
	#define NB_COL_BITS	10
#endif
#endif

#define BL			8
#if (CONFIG_MEM_CLOCK <= 166)
#ifndef USE_QST_DDRX_VIP 
	#define RL		3
	#define WL		1
#else
	#define RL		6
	#define WL		3
#endif
#elif (CONFIG_MEM_CLOCK <= 400)
	#define RL		6
	#define WL		3
#else
	#define RL		8 
	#define WL		4
#endif
#endif
#endif /* Endif of CONFIG_DDR_SET_JEDEC */
