/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DRAM_HELPERS_H__
#define __DRAM_HELPERS_H__

#define WAIT_WHILE_COND(x, time)						\
{ 									\
	unsigned int timeout = (time);					\
	while ((x) && (timeout--));					\
									\
	if (timeout == 0xFFFFFFFF) {					\
		dbg_printf("Timed out while waiting for  " #x "\n");	\
		return -1;						\
	}								\
}

#define DIV_ROUND_UP(x, y)	((x) + (y) - 1)/(y)
#define DIV_ROUND_DOWN(x, y)	((x) / (y))

/*
 * ns * 10^-9 (ns to seconds)  * CLOCK * 10^6 (beats/sec in Mhz, to seconds)
 * / 1000 = clock cycles
 * ps * 10^-12 (ps to seconds) * CLOCK * 10^6 (beats/sec in Mhz, to seconds)
 * /10^6 = clock cycles
 */
#define NS_TO_CYCLES_UP(ns)	DIV_ROUND_UP(((ns) * CONFIG_MEM_CLOCK), 1000UL)
#define NS_TO_CYCLES_DOWN(ns)	DIV_ROUND_DOWN(((ns) * CONFIG_MEM_CLOCK), 1000UL)
#define PS_TO_CYCLES_UP(ps)	DIV_ROUND_UP(((ps) * CONFIG_MEM_CLOCK), 1000000UL)
#define PS_TO_CYCLES_DOWN(ps)	DIV_ROUND_DOWN(((ps) * CONFIG_MEM_CLOCK), 1000000UL)
/*
 * 1/ frequency = period.
 * CLOCK is in Mhz
 * 1/ (CLOCK * 10^6) = seconds. To obtain picoseconds, multiply by 10^12
 * 1 * 10 ^12 / (CLOCK * 10^6) = 10^6/ CLOCK (picoseconds)
 */
#define CYCLE_IN_PS		(1000000UL / CONFIG_MEM_CLOCK)
#define CYCLE_IN_NS		DIV_ROUND_UP(CYCLE_IN_PS, 1000UL)

#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define MIN(x, y)	((x) > (y) ? (y) : (x))

struct dram_timings
{
	unsigned long	tRFC;		/* Refresh to Refresh, ns */
	unsigned long	tREFI;		/* Refresh Intervals, ns */
	unsigned long	tWR;		/* Write Recovery, ns */
	unsigned long	tRP;		/* Row Precharge command, ns */
	unsigned long	tRP_ps;		/* Row Precharge command, ps */
	unsigned long	tRCD;		/* Row to Column delay, ns */
	unsigned long	tRCD_ps;	/* Row to Column delay, ps */
	unsigned long	tCCD;		/* Column to Column delay, ns */
	unsigned long	tRAS;		/* Row Active Strobe, ns */
	unsigned long	tRASMAX;	/* Row Active Strobe Max value, ns */
	unsigned long	tRC_ps;		/* Row Cycle, ps */
	unsigned long	tFAW;		/* Four Activation Window, ns */
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	unsigned long	tPRECKE;
#endif
	unsigned long	tPOSTCKE;
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	unsigned long	tDQSCK_MIN;
	unsigned long	tDQSCK_MAX;
	unsigned long	tTSI;		/* Temperature Sensor Interval, ms */
#endif
	unsigned long	CL;		/* CAS Latency, Clock cycles */
	unsigned long	CWL;		/* CAS Write Latency, Clock cycles */
	unsigned long	AL;		/* Additive Latency, Clock cycles */
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	unsigned long	RL;		/* Read Latency, Clock cycles, LPDDR2 */
	unsigned long	WL;		/* Write Latency, Clock cycles, LPDDR2 */
#endif
#if defined(CONFIG_DDR3) || defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	unsigned long	TZQOPER;	/* Calibration time, Clock cycles */
	unsigned long	TZQCS;		/* Calibration time short, Clock cycles */
#endif
	unsigned long	MRD;		/* Mode Register Delay, Clock cycles */

/* All timings below starting with a caps T should be in clock cycles */
#if defined(CONFIG_LPDDR3) || defined(CONFIG_DDR3)
#define TRTP		MAX(4, PS_TO_CYCLES_UP(7500UL))		/* Read to Precharge, Clock Cycles */
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_DDR2)
#define TRTP		MAX(2, PS_TO_CYCLES_UP(7500UL))		/* Read to Precharge, Clock Cycles */
#endif

#define TWTR		MAX(4, PS_TO_CYCLES_UP(7500UL))		/* Write to Read, Clock Cycles */
#define TRP			PS_TO_CYCLES_UP(tRP_ps)				/* Row Precharge delay, Clock Cycles */
#define TRCD		PS_TO_CYCLES_UP(tRCD_ps)			/* Row to Column delay, Clock Cycles */
#define TRAS		NS_TO_CYCLES_UP(tRAS)				/* Row Active Strobe, Clock Cycles */
#if defined(CONFIG_DDR2)
	#if defined(CONFIG_DDR_256_MBIT)
		#define TRRD		PS_TO_CYCLES_UP(7500UL)			/* Row to Row Delay, Clock Cycles */
	#elif defined(CONFIG_DDR_512_MBIT) || defined(CONFIG_DDR_1_GBIT) \
		|| defined(CONFIG_DDR_2_GBIT) || defined(CONFIG_DDR_4_GBIT)
		#define TRRD		NS_TO_CYCLES_UP(10UL)			/* Row to Row Delay, Clock Cycles */
	#endif
#elif defined(CONFIG_DDR3)
	#define TRRD		MAX(4, NS_TO_CYCLES_UP(10UL))		/* Row to Row Delay, Clock Cycles */
#elif defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	#define TRRD		MAX(2, NS_TO_CYCLES_UP(10UL))		/* Row to Row Delay, Clock Cycles */
#endif

#define TRC		PS_TO_CYCLES_UP(tRC_ps)			/* Row Cycle, Clock Cycles */
#define TFAW		NS_TO_CYCLES_UP(tFAW)			/* Four Activation Window, Clock Cycles */
#define TMRD		MRD					/* Mode Register Delay, Clock Cycles */
#if defined(CONFIG_LPDDR2)
#define TMRW		5UL					/* Mode Register Wait, Clock Cycles */
#endif
#if defined(CONFIG_LPDDR3)
#define TMRW		10UL					/* Mode Register Wait, Clock Cycles */
#endif
#define TCCD		NS_TO_CYCLES_UP(tCCD)			/* Column to Column Delay, Clock Cycles */
#if defined(CONFIG_DDR3)
#define TMOD		MAX(12, NS_TO_CYCLES_UP(15UL))	/* Mode Update Delay, Clock Cycles DDR3 only */
#endif
#define TRFC		NS_TO_CYCLES_UP(tRFC)			/* Refresh Counter, Clock Cycles */
#define TXS		MAX(5, NS_TO_CYCLES_UP(tRFC + 10UL))	/* Self-refresh Exit Delay, Clock Cycles */
#define TXSDLL		512UL
#define TXSR		NS_TO_CYCLES_UP(tRFC + 10UL)

#if defined(CONFIG_DDR2)
	#define TCKE		MAX(3, PS_TO_CYCLES_UP(7500UL))		/* CKE minimum width, Clock Cycles */
	#define TXP		2					/* Power down exit Delay, Clock Cycles */
	#define TCKSRX		1
	#define TCKSRE		1
	#define TCKESR		TCKE
#endif

#if defined(CONFIG_DDR3)
	#if defined (CONFIG_DDR_SET_BY_TIMING)
		#if defined (CONFIG_MEM_CLOCK_400)
			#define TCKE		MAX(3, PS_TO_CYCLES_UP(7500UL))
		#elif defined (CONFIG_MEM_CLOCK_533)
			#define TCKE		MAX(3, PS_TO_CYCLES_UP(5625UL))
		#endif
	#else
		#if defined(CONFIG_DDR_SPEED_800)
			#define TCKE		MAX(3, PS_TO_CYCLES_UP(7500UL))		/* CKE minimum width, Clock Cycles */
		#elif defined(CONFIG_DDR_SPEED_1066)
			#define TCKE		MAX(3, PS_TO_CYCLES_UP(5625UL))		/* CKE minimum width, Clock Cycles */
		#endif
	#endif
	#define TXPR		MAX(5, NS_TO_CYCLES_UP(tRFC + 10))	/* Reset Clock exit time, Clock Cycles */
	#define TXP		MAX(3, PS_TO_CYCLES_UP(7500UL))		/* Power down exit Delay, Clock Cycles */
	#define TXPDLL		MAX(10, NS_TO_CYCLES_UP(24UL))
	#define TCKSRX		MAX(5, NS_TO_CYCLES_UP(10UL))
	#define TCKSRE		MAX(5, NS_TO_CYCLES_UP(10UL))
	#define TCKESR		(TCKE + 1)
#endif

#if defined(CONFIG_LPDDR2)
	#define TCKE		MAX(3, NS_TO_CYCLES_UP(15UL))		/* CKE minimum width, Clock Cycles */
	#define TXP		MAX(2, PS_TO_CYCLES_UP(7500UL))		/* Power down exit Delay, Clock Cycles */
	#define TCKSRX		2
	#define TCKSRE		2
	#define TCKESR		MAX(3, PS_TO_CYCLES_UP(15000UL))	/* CKE minimum width, Clock Cycles */
	#define TCKCSX		(2 + TXP)
	#define TCKDPDX		2
	#define TCKDPDE		2
	#define TCKPDX		2
	#define TCKPDE		2
#endif

#if defined(CONFIG_LPDDR3)
	#define TCKE		MAX(3, PS_TO_CYCLES_UP(7500UL))		/* CKE minimum width, Clock Cycles */
	#define TXP		MAX(3, PS_TO_CYCLES_UP(7500UL))		/* Power down exit Delay, Clock Cycles */
	#define TCKSRX		2
	#define TCKSRE		2
	#define TCKESR		MAX(3, PS_TO_CYCLES_UP(15000UL))	/* CKE minimum width, Clock Cycles */
	#define TCKCSX		(2 + TXP)
	#define TCKDPDX		2
	#define TCKDPDE		2
	#define TCKPDX		2
	#define TCKPDE		2
#endif

#if defined(CONFIG_DDR2) || defined(CONFIG_DDR3)
	#define TDLLK		200UL					/* DLL Lock time, Clock Cycles */
#else
	#define TDLLK		0					/* DLL Lock time, Clock Cycles */
#endif

#define TAOND		2UL					/* ODT Turn-On Delay , Clock Cycles */
#define TDQSCK_MIN	PS_TO_CYCLES_DOWN(tDQSCK_MIN)		/* DQS Output access time */
#define TDQSCK_MAX	PS_TO_CYCLES_DOWN(tDQSCK_MAX)		/* DQS Output access time */
#define BL		8UL					/* Burst Length */
#if defined(CONFIG_DDR2) || defined(CONFIG_DDR3)
#define RL		(CL + AL)				/* Read Latency */
#define WL		(CWL + AL)				/* Write Latency */
#endif
#if defined(CONFIG_LPDDR3)
#define TWR		MAX(4, NS_TO_CYCLES_UP(tWR))		/* Write Recovery */
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_DDR2) || defined(CONFIG_DDR3)
#define TWR		NS_TO_CYCLES_UP(tWR)				/* Write Recovery */
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
#define TINIT1		NS_TO_CYCLES_UP(100UL)			/* Clock Cycles */
#define TINIT2		5UL					/* Clock Cycles */
#define TINIT4		NS_TO_CYCLES_UP(1000UL)			/* Clock Cycles */
#define TINIT5		NS_TO_CYCLES_UP(10000UL)		/* Clock Cycles */
#define TZQINIT		PS_TO_CYCLES_UP(1000000UL)		/* Clock Cycles */
#endif
#define TPOSTCKE	NS_TO_CYCLES_UP(tPOSTCKE)		/* Clock Cycles */
#define TZQRESET	MAX(3, NS_TO_CYCLES_UP(50UL))	/* Clock Cycles */
};

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

#endif

