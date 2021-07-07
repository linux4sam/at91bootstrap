/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __UMCTL2_JEDET_H__
#define __UMCTL2_JEDET_H__

#if defined(CONFIG_DDR_SET_BY_JEDEC)
#if defined(CONFIG_DDR2)
	#if defined(CONFIG_DDR_256_MBIT)
		#define _tRFC		75UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_512_MBIT)
		#define _tRFC		105UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_1_GBIT)
		#define _tRFC		128UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_2_GBIT)
		#define _tRFC		198UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_4_GBIT)
		#define _tRFC		328UL		/* Refresh to Refresh, ns */
	#else
		#error "No DDR2 setting defined"
	#endif
	#define _tREFI		7800UL		/* Refresh Intervals, ns */
	#define _tWR		15UL		/* Write Recovery, ns */
	
	#if defined(CONFIG_DDR_SPEED_400)
		#if defined(CONFIG_CAS_3)
			#define _CL			3UL			/* CAS Latency, Clock cycles */
			#define _tRP		15UL		/* Row Precharge command, ns */
			#define _tRP_ps		15000UL		/* Row Precharge command, ps */
			#define _tRCD		15UL		/* Row to Column delay, ns */
			#define _tRCD_ps	15000UL		/* Row to Column delay, ps */
			#define _tRC_ps		55000UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_4)
			#define _CL			4UL			/* CAS Latency, Clock cycles */
			#define _tRP		20UL		/* Row Precharge command, ns */
			#define _tRP_ps		20000UL		/* Row Precharge command, ps */
			#define _tRCD		20UL		/* Row to Column delay, ns */
			#define _tRCD_ps	20000UL		/* Row to Column delay, ps */
			#define _tRC_ps		65000UL		/* Row Cycle, ps */
		#else
			#error "No DDR2 setting defined"
		#endif
	#elif defined(CONFIG_DDR_SPEED_533)
		#if defined(CONFIG_CAS_3)
			#define _CL			3UL			/* CAS Latency, Clock cycles */
			#define _tRP		12UL		/* Row Precharge command, ns */
			#define _tRP_ps		11250UL		/* Row Precharge command, ps */
			#define _tRCD		12UL		/* Row to Column delay, ns */
			#define _tRCD_ps	11250UL		/* Row to Column delay, ps */
			#define _tRC_ps		56250UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_4)
			#define _CL			4UL			/* CAS Latency, Clock cycles */
			#define _tRP		15UL		/* Row Precharge command, ns */
			#define _tRP_ps		15000UL		/* Row Precharge command, ps */
			#define _tRCD		15UL		/* Row to Column delay, ns */
			#define _tRCD_ps	15000UL		/* Row to Column delay, ps */
			#define _tRC_ps		60000UL		/* Row Cycle, ps */
		#else
			#error "No DDR2 setting defined"
		#endif
		#if defined(CONFIG_DDR_512_MBIT) || defined(CONFIG_DDR_1_GBIT) |\
			defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_4_GBIT)
			#define _tFAW		50UL		/* Four Activation Window, ns */
		#else
			#define _tFAW		38UL		/* Four Activation Window, ns */
		#endif
	#elif defined(CONFIG_DDR_SPEED_667)
		#if defined(CONFIG_CAS_4)
			#define _CL			4UL			/* CAS Latency, Clock cycles */
			#define _tRP		12UL		/* Row Precharge command, ns */
			#define _tRP_ps		12000UL		/* Row Precharge command, ps */
			#define _tRCD		12UL		/* Row to Column delay, ns */
			#define _tRCD_ps	12000UL		/* Row to Column delay, ps */
			#define _tRC_ps		57000UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_5)
			#define _CL			5UL			/* CAS Latency, Clock cycles */
			#define _tRP		15UL		/* Row Precharge command, ns */
			#define _tRP_ps		15000UL		/* Row Precharge command, ps */
			#define _tRCD		15UL		/* Row to Column delay, ns */
			#define _tRCD_ps	15000UL		/* Row to Column delay, ps */
			#define _tRC_ps		60000UL		/* Row Cycle, ps */
		#else
			#error "No DDR2 setting defined"
		#endif
		#if defined(CONFIG_DDR_512_MBIT) || defined(CONFIG_DDR_1_GBIT) ||\
			defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_4_GBIT)
			#define _tFAW		50UL		/* Four Activation Window, ns */
		#else
			#define _tFAW		38UL		/* Four Activation Window, ns */
		#endif
	#elif defined(CONFIG_DDR_SPEED_800)
		#if defined(CONFIG_CAS_4)
			#define _CL			4UL			/* CAS Latency, Clock cycles */
			#define _tRP		10UL		/* Row Precharge command, ns */
			#define _tRP_ps		10000UL		/* Row Precharge command, ps */
			#define _tRCD		10UL		/* Row to Column delay, ns */
			#define _tRCD_ps	10000UL		/* Row to Column delay, ps */
			#define _tRC_ps		55000UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_5)
			#define _CL			5UL			/* CAS Latency, Clock cycles */
			#define _tRP		13UL		/* Row Precharge command, ns */
			#define _tRP_ps		12500UL		/* Row Precharge command, ps */
			#define _tRCD		13UL		/* Row to Column delay, ns */
			#define _tRCD_ps	12500UL		/* Row to Column delay, ps */
			#define _tRC_ps		57500UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_6)
			#define _CL			6UL			/* CAS Latency, Clock cycles */
			#define _tRP		15UL		/* Row Precharge command, ns */
			#define _tRP_ps		15000UL		/* Row Precharge command, ps */
			#define _tRCD		15UL		/* Row to Column delay, ns */
			#define _tRCD_ps	15000UL		/* Row to Column delay, ps */
			#define _tRC_ps		60000UL		/* Row Cycle, ps */
		#else
			#error "No DDR2 setting defined"
		#endif
		#if defined(CONFIG_DDR_512_MBIT) || defined(CONFIG_DDR_1_GBIT) ||\
			defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_4_GBIT)
			#define _tFAW		45UL		/* Four Activation Window, ns */
		#else
			#define _tFAW		35UL		/* Four Activation Window, ns */
		#endif
	#else
		#error "No DDR2 speed defined"
	#endif
	
	#define _tCCD		2UL			/* CAS to CAS command delay, tCK */
	#define _tRAS		45UL		/* Row Active Strobe, ns */
	#define _tRASMAX	70000UL		/* RAS max, ns */
	#define _tPRECKE	200000UL
	#define _tPOSTCKE	400UL		/* DDR2 typically requires a 400 ns delay, */

	#define _MRD		2UL			/* Mode Register Delay, Clock cycles */
	#define _AL			0UL			/* Additive Latency, Clock cycles */
	#define _RL			(_CL + AL)	/* Read Latency , Clock cycles*/
	#define _CWL		(_CL - 1)	/* CAS Write Latency, Clock cycles */

#elif defined(CONFIG_DDR3)
	#if defined(CONFIG_DDR_512_MBIT)
		#define _tRFC		90UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_1_GBIT)
		#define _tRFC		110UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_2_GBIT)
		#define _tRFC		160UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_4_GBIT)
		#define _tRFC		300UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_8_GBIT)
		#define _tRFC		350UL		/* Refresh to Refresh, ns */
	#else
		#error "No DDR3 setting defined"
	#endif
	
	#define _tREFI		7800UL		/* Refresh Intervals, ns */
	#define _tWR		15UL		/* Write Recovery, ns */
	
	#if defined(CONFIG_DDR_SPEED_800)
		#if defined(CONFIG_CAS_5)
			#define _CL			5UL			/* CAS Latency, Clock cycles */
			#define _CWL		5UL			/* CAS Write Latency, Clock cycles */
			#define _tRP		13UL		/* Row Precharge command, ns */
			#define _tRP_ps		12500UL		/* Row Precharge command, ps */
			#define _tRCD		13UL		/* Row to Column delay, ns */
			#define _tRCD_ps	12500UL		/* Row to Column delay, ps */
			#define _tRC_ps		50000UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_6)
			#define _CL			6UL			/* CAS Latency, Clock cycles */
			#define _CWL		5UL			/* CAS Write Latency, Clock cycles */
			#define _tRP		15UL		/* Row Precharge command, ns */
			#define _tRP_ps		15000UL		/* Row Precharge command, ps */
			#define _tRCD		15UL		/* Row to Column delay, ns */
			#define _tRCD_ps	15000UL		/* Row to Column delay, ps */
			#define _tRC_ps		52500UL		/* Row Cycle, ps */
		#else
			#error "No DDR3 setting defined"
		#endif
	
	#elif defined(CONFIG_DDR_SPEED_1066)
		#if defined(CONFIG_CAS_6)
			#define _CL			6UL			/* CAS Latency, Clock cycles */
			#define _tRP		12UL		/* Row Precharge command, ns */
			#define _tRP_ps		11250UL		/* Row Precharge command, ps */
			#define _tRCD		12UL		/* Row to Column delay, ns */
			#define _tRCD_ps	11250UL		/* Row to Column delay, ps */
			#define _tRC_ps		48750UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_7)
			#define _CL			7UL			/* CAS Latency, Clock cycles */
			#define _tRP		14UL		/* Row Precharge command, ns */
			#define _tRP_ps		13125UL		/* Row Precharge command, ps */
			#define _tRCD		14UL		/* Row to Column delay, ns */
			#define _tRCD_ps	13125UL		/* Row to Column delay, ps */
			#define _tRC_ps		50625UL		/* Row Cycle, ps */
		#elif defined(CONFIG_CAS_8)
			#define _CL			8UL			/* CAS Latency, Clock cycles */
			#define _tRP		15UL		/* Row Precharge command, ns */
			#define _tRP_ps		15000UL		/* Row Precharge command, ps */
			#define _tRCD		15UL		/* Row to Column delay, ns */
			#define _tRCD_ps	15000UL		/* Row to Column delay, ps */
			#define _tRC_ps		52500UL		/* Row Cycle, ps */
		#else
			#error "No DDR2 setting defined"
		#endif
		#define _CWL		(_CL - 1)		/* CAS Write Latency, Clock cycles */
	#else
		#error "No DDR3 speed defined"
	#endif
	
	#define _tFAW		50UL		/* Four Activation Window, ns */
	#define _tCCD		4UL			/* CAS to CAS command delay, tCK */
	#define _tRAS		38UL		/* Row Active Strobe, ns */
	#define _tRASMAX	70000UL		/* RAS max, ns */
	
	#define _tPRECKE	500000UL
	#define _tPOSTCKE	0UL			/* Unused with DDR3 */
	
	#define _TZQOPER	256UL		/* TZQ Long Calibration, Clock cycles */
	#define _TZQCS		64UL		/* TZQ Short Calibration, Clock cycles */
	#define _MRD		4UL			/* Mode Register Delay, Clock cycles */
	#define _AL			0UL			/* Additive Latency, Clock cycles */

#elif defined(CONFIG_LPDDR2)
	#if defined(CONFIG_DDR_8_GBIT)
		#define _tRFC		210UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_1_GBIT) || defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_4_GBIT)
		#define _tRFC		130UL		/* Refresh to Refresh, ns */
	#else
		#define _tRFC		90UL		/* Refresh to Refresh, ns */
	#endif
	
	#if defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_4_GBIT) || defined(CONFIG_DDR_8_GBIT)
		#define _tREFI		3900UL		/* Refresh Intervals, ns */
	#else
		#define _tREFI		7800UL		/* Refresh Intervals, ns */
	#endif
	#define _tWR		15UL		/* Write Recovery, ns */
	#define _tRP		3UL			/* Row Precharge command, tCK */
	#define _tRP_ps		3000UL		/* Row Precharge command, tCK */
	#define _tRCD		15UL		/* Activate to Read/Write command period (min), ns */
	#define _tRCD_ps	15000UL		/* Activate to Read/Write command period (min), ps */
	#define _tCCD		2UL			/* Column to Column delay, ns */
	#define _tRAS		42UL		/* Row Active Strobe, ns */
	#define _tRASMAX	70000UL		/* RAS max, ns */
	#define _tRC_ps		((_tRAS + _tRP)*1000)		/* Row Cycle, ps */
	#define _tFAW		50UL		/* Four Activation Window, ns */
	
	#define _tPRECKE	100UL		/* LPDDR2 tINIT1 of 100 ns (min) */
	#define _tPOSTCKE	20000UL		/* LPDDR2 typically requires this to be programmed for a delay of 200 μs */
	
	#define _CL		0UL				/* CAS Latency, Clock cycles, unused in LPDDR2 */
	#define _CWL		0UL			/* CAS Write Latency, Clock cycles, unused in LPDDR2 */
	#define _AL		0UL				/* Additive Latency, Clock cycles */
	#if defined(CONFIG_DDR_SPEED_400)
		#define _RL		3UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		1UL				/* For LPDDR2, Write Latency, Clock cycles */
	#elif defined(CONFIG_DDR_SPEED_533)
		#define _RL		4UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		2UL				/* For LPDDR2, Write Latency, Clock cycles */
	#elif defined(CONFIG_DDR_SPEED_667)
		#define _RL		5UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		2UL				/* For LPDDR2, Write Latency, Clock cycles */
	#elif defined(CONFIG_DDR_SPEED_800)
		#define _RL		6UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		3UL				/* For LPDDR2, Write Latency, Clock cycles */
	#elif defined(CONFIG_DDR_SPEED_933)
		#define _RL		7UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		4UL				/* For LPDDR2, Write Latency, Clock cycles */
	#elif defined(CONFIG_DDR_SPEED_1066)
		#define _RL		8UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		4UL				/* For LPDDR2, Write Latency, Clock cycles */
	#else
		#error "No LPDDR2 speed defined"
	#endif
	#define _TZQOPER	360UL		/* TZQ Long Calibration, Clock cycles */
	#define _TZQCS		90UL		/* TZQ Short Calibration, Clock cycles */
	#define _MRD		0UL			/* unused in LPDDR2 */
	#define _tDQSCK_MIN	2500UL		/* DQS output access time from CK_t/CK_c min */
	#define _tDQSCK_MAX	5500UL		/* DQS output access time from CK_t/CK_c max */

#elif defined(CONFIG_LPDDR3)
	#if defined(CONFIG_DDR_4_GBIT) 
		#define _tRFC		130UL		/* Refresh to Refresh, ns */
	#elif defined(CONFIG_DDR_8_GBIT)
		#define _tRFC		210UL		/* Refresh to Refresh, ns */
	#endif
	#define _tREFI		3900UL			/* Refresh Intervals, ns */
	#define _tWR		15UL			/* Write Recovery, ns */
	#define _tRP		MAX(21UL, 3 * CYCLE_IN_NS)		/* Row Precharge command, tCK */
	#define _tRP_ps		MAX(21000UL, 3 * CYCLE_IN_PS)	/* Row Precharge command, ps */
	#define _tRCD		MAX(18UL, 3 * CYCLE_IN_NS)		/* Row to Column delay, ns */
	#define _tRCD_ps	MAX(18000UL, 3 * CYCLE_IN_PS)	/* Row to Column delay, ps */
	#define _tCCD		4UL								/* Column to Column delay, ns */
	#define _tRAS		MAX(42UL, 3 * CYCLE_IN_NS)		/* Row Active Strobe, ns */
	#define _tRASMAX	70000UL		/* RAS max, ns */
	#define _tRC_ps		((_tRAS + _tRP) * 1000)			/* Row Cycle, ps */
	#define _tFAW		MAX(50UL, 8 * CYCLE_IN_NS)		/* Four Activation Window, ns */
	#define _tPRECKE	100UL		/* LPDDR3 tINIT1 of 100 ns (min) */
	#define _tPOSTCKE	20000UL		/* LPDDR3 typically requires this to be programmed for a delay of 200 μs */
	#define _CL		0UL				/* CAS Latency, Clock cycles, unused in LPDD3 */
	#define _CWL		0UL			/* CAS Write Latency, Clock cycles, unused in LPDDR3 */
	#define _AL		0UL				/* Additive Latency, Clock cycles */
	#if defined(CONFIG_DDR_SPEED_800)
		#define _RL		6UL				/* For LPDDR3, Read Latency, Clock cycles */
		#define _WL		3UL				/* For LPDDR3, Write Latency, Clock cycles */
	#elif defined(CONFIG_DDR_SPEED_1066)
		#define _RL		8UL				/* For LPDDR2, Read Latency, Clock cycles */
		#define _WL		4UL				/* For LPDDR2, Write Latency, Clock cycles */
	#else
		#error "No LPDDR3 speed defined"
	#endif
	#define _TZQOPER	360UL		/* TZQ Long Calibration, Clock cycles */
	#define _TZQCS		90UL		/* TZQ Short Calibration, Clock cycles */
	#define _MRD		15UL		/* Mode register set command delay */
	#define _tDQSCK_MIN	2500UL		/* DQS output access time from CK_t/CK_c min */
	#define _tDQSCK_MAX	5500UL		/* DQS output access time from CK_t/CK_c max */
#endif
#endif /* Endif of CONFIG_DDR_SET_JEDEC */
#endif /* Endif __UMCTL2_JEDET_H__ */
