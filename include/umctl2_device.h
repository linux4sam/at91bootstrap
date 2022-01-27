/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __UMCTL2_DEVICE_H__
#define __UMCTL2_DEVICE_H__

#if defined(CONFIG_DDR_SET_BY_DEVICE)
#if defined(CONFIG_DDR_MT41K256M16TW_107) || defined (CONFIG_DDR_MT41K512M16HA_125)
#define _tRFC		350UL		/* Refresh to Refresh, ns */
#define _tREFI		7800UL		/* Refresh Intervals, ns */
#define _tWR		15UL		/* Write Recovery, ns */
#define _tRP		14UL		/* Row Precharge command, ns */
#define _tRP_ps		13125UL		/* Row Precharge command, ps */
#define _tRCD		14UL		/* Row to Column delay, ns */
#define _tRCD_ps	13125UL		/* Row to Column delay, ps */
#define _tCCD		4UL		/* Column to Column delay, ns */
#define _tRAS		38UL		/* Row Active Strobe, ns */
#define _tRASMAX	70000UL		/* RAS max, ns */
#define _tRC_ps		50625UL		/* Row Cycle, ps */
#define _tFAW		50UL		/* Four Activation Window, ns */
#define _tPRECKE	500000UL
#define _tPOSTCKE	0UL		/* Unused with DDR3 */
#define _CL		7UL		/* CAS Latency, Clock cycles */
#define _CWL		6UL		/* CAS Write Latency, Clock cycles */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _TZQOPER	256UL		/* TZQ Long Calibration, Clock cycles */
#define _TZQCS		64UL		/* TZQ Short Calibration, Clock cycles */
#define _MRD		4UL		/* Mode Register Delay, Clock cycles */
#endif

#if defined(CONFIG_DDR_AS4C256M16D3LC_12BCNTR)
#define _tRFC		260UL		/* Refresh to Refresh, ns */
#define _tREFI		7800UL		/* Refresh Intervals, ns */
#define _tWR		15UL		/* Write Recovery, ns */
#define _tRP		14UL		/* Row Precharge command, ns */
#define _tRP_ps		13750UL		/* Row Precharge command, ps */
#define _tRCD		14UL		/* Row to Column delay, ns */
#define _tRCD_ps	13750UL		/* Row to Column delay, ps */
#define _tCCD		4UL		/* Column to Column delay, ns */
#define _tRAS		35UL		/* Row Active Strobe, ns */
#define _tRASMAX	70200UL		/* RAS max, ns */
#define _tRC_ps		48750UL		/* Row Cycle, ps */
#define _tFAW		40UL		/* Four Activation Window, ns */
#define _tPRECKE	500000UL
#define _tPOSTCKE	0UL		/* Unused with DDR3 */
#define _CL		7UL		/* CAS Latency, Clock cycles */
#define _CWL		6UL		/* CAS Write Latency, Clock cycles */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _TZQOPER	256UL		/* TZQ Long Calibration, Clock cycles */
#define _TZQCS		64UL		/* TZQ Short Calibration, Clock cycles */
#define _MRD		4UL		/* Mode Register Delay, Clock cycles */
#endif

#ifdef CONFIG_DDR_MT47H128M16RT_25E_C
#define _tRFC		195UL		/* Refresh to Refresh, ns */
#define _tREFI		7800UL		/* Refresh Intervals, ns */
#define _tWR		15UL		/* Write Recovery, ns */
#define _tRP		13UL		/* Row Precharge command, ns */
#define _tRP_ps		12500UL		/* Row Precharge command, ps */
#define _tRCD		13UL		/* Row to Column delay, ns */
#define _tRCD_ps	12500UL		/* Row to Column delay, ps */
#define _tCCD		2UL		/* Column to Column delay, ns */
#define _tRAS		40UL		/* Row Active Strobe, ns */
#define _tRASMAX	70000UL		/* RAS max, ns */
#define _tRC_ps		55000UL		/* Row Cycle, ps */
#define _tFAW		50UL		/* Four Activation Window, ns */
#define _tPRECKE	200000UL
#define _tPOSTCKE	400UL
#define _CL		5UL		/* CAS Latency, Clock cycles */
#define _CWL		4UL		/* CAS Write Latency, Clock cycles */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _MRD		2UL		/* Mode Register Delay, Clock cycles */
#endif

#ifdef CONFIG_DDR_IS43LD16128B_25BLI
#define _tRFC		130UL		/* Refresh to Refresh, ns */
#define _tREFI		3900UL		/* Refresh Intervals, ns */
#define _tWR		15UL		/* Write Recovery, ns */
#define _tRP		21UL		/* Row Precharge command, ns */
#define _tRP_ps		21000UL		/* Row Precharge command, ps */
#define _tRCD		18UL		/* Row to Column delay, ns */
#define _tRCD_ps	18000UL		/* Row to Column delay, ps */
#define _tCCD		2UL		/* Column to Column delay, ns */
#define _tRAS		42UL		/* Row Active Strobe, ns */
#define _tRASMAX	70000UL		/* RAS max, ns */
#define _tRC_ps		((_tRAS + _tRP)*1000)		/* Row Cycle, ps */
#define _tFAW		50UL		/* Four Activation Window, ns */
#define _tPOSTCKE	200000UL	/* Post CKE, ns */
#define _CL		0UL		/* CAS Latency, Clock cycles, unused in LPDDR2 */
#define _CWL		0UL		/* CAS Write Latency, Clock cycles, unused in LPDDR2 */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _RL		6UL		/* For LPDDR2, Read Latency, Clock cycles */
#define _WL		3UL		/* For LPDDR2, Write Latency, Clock cycles */
#define _TZQOPER	NS_TO_CYCLES_UP(360UL)		/* TZQ Long Calibration, Clock cycles */
#define _TZQCS		NS_TO_CYCLES_UP(90UL)		/* TZQ Short Calibration, Clock cycles */
#define _MRD		0UL		/* Mode Register Delay, Clock cycles , unused in LPDDR2*/
#define _tDQSCK_MIN	2500UL
#define _tDQSCK_MAX	5500UL
#define _tTSI_ms	16UL		/* Temperature Sensor interval, ms */
#endif

#ifdef CONFIG_DDR_MT52L256M32D1PF_107
#define _tRFC		210UL		/* Refresh to Refresh, ns */
#define _tREFI		3900UL		/* Refresh Intervals, ns */
#define _tWR		MAX(15UL, 3 * CYCLE_IN_NS)		/* Write Recovery, ns */
#define _tRP		MAX(21UL, 3 * CYCLE_IN_NS)		/* Row Precharge command, ns */
#define _tRP_ps		MAX(21000UL, 3 * CYCLE_IN_PS)		/* Row Precharge command, ps */
#define _tRCD		MAX(18UL, 3 * CYCLE_IN_NS)		/* Row to Column delay, ns */
#define _tRCD_ps	MAX(18000UL, 3 * CYCLE_IN_PS)		/* Row to Column delay, ps */
#define _tCCD		4UL		/* Column to Column delay, ns */
#define _tRAS		MAX(42UL, 3 * CYCLE_IN_NS)		/* Row Active Strobe, ns */
#define _tRASMAX	70200UL		/* RAS max, ns */
#define _tRC_ps		((_tRAS + _tRP) * 1000)		/* Row Cycle, ps */
#define _tFAW		MAX(50UL, 8 * CYCLE_IN_NS)		/* Four Activation Window, ns */
#define _tPOSTCKE	200000UL	/* Post CKE, ns */
#define _CL		0UL		/* CAS Latency, Clock cycles, unused in LPDDR2 */
#define _CWL		0UL		/* CAS Write Latency, Clock cycles, unused in LPDDR2 */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _RL		8UL		/* For LPDDR3, Read Latency, Clock cycles */
#define _WL		4UL		/* For LPDDR3, Write Latency, Clock cycles */
#define _TZQOPER	NS_TO_CYCLES_UP(360UL)		/* TZQ Long Calibration, Clock cycles */
#define _TZQCS		NS_TO_CYCLES_UP(90UL)		/* TZQ Short Calibration, Clock cycles */
#define _MRD		MAX(NS_TO_CYCLES_UP(14UL), 10UL)		/* Mode Register Delay, Clock cycles */
#define _tDQSCK_MIN	2500UL
#define _tDQSCK_MAX	5500UL
#define _tTSI_ms	32UL		/* Temperature Sensor interval, ms */
#endif

#ifdef CONFIG_DDR_EDB5432BEBH_1DAAT_F_D
#define _tRFC		90UL		/* Refresh to Refresh, ns */
#define _tREFI		7800UL		/* Refresh Intervals, ns */
#define _tWR		15UL		/* Write Recovery, ns */
#define _tRP		21UL		/* Row Precharge command, ns */
#define _tRP_ps		21000UL		/* Row Precharge command, ps */
#define _tRCD		18UL		/* Row to Column delay, ns */
#define _tRCD_ps	18000UL		/* Row to Column delay, ps */
#define _tCCD		2UL		/* Column to Column delay, ns */
#define _tRAS		42UL		/* Row Active Strobe, ns */
#define _tRASMAX	70000UL		/* RAS max, ns */
#define _tRC_ps		((_tRAS + _tRP)*1000)		/* Row Cycle, ps */
#define _tFAW		50UL		/* Four Activation Window, ns */
#define _tPOSTCKE	200000UL	/* Post CKE, ns */
#define _CL		0UL		/* CAS Latency, Clock cycles, unused in LPDDR2 */
#define _CWL		0UL		/* CAS Write Latency, Clock cycles, unused in LPDDR2 */
#define _AL		0UL		/* Additive Latency, Clock cycles */
#define _RL		8UL		/* For LPDDR2, Read Latency, Clock cycles */
#define _WL		4UL		/* For LPDDR2, Write Latency, Clock cycles */
#define _TZQOPER	NS_TO_CYCLES_UP(360UL)		/* TZQ Long Calibration, Clock cycles */
#define _TZQCS		NS_TO_CYCLES_UP(90UL)		/* TZQ Short Calibration, Clock cycles */
#define _MRD		0UL		/* Mode Register Delay, Clock cycles , unused in LPDDR2*/
#define _tDQSCK_MIN	2500UL
#define _tDQSCK_MAX	5620UL
#define _tTSI_ms	32UL		/* Temperature Sensor interval, ms */
#endif

#endif
#endif
