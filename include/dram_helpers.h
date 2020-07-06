/* ----------------------------------------------------------------------------
 *         Microchip Technology AT91Bootstrap project
 * ----------------------------------------------------------------------------
 * Copyright (c) 2020, Microchip Technology Inc. and its subsidiaries
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Microchip's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
	unsigned long	tRAS;		/* Row Active Strobe, ns */
	unsigned long	tRASMAX;	/* Row Active Strobe Max value, ns */
	unsigned long	tRC_ps;		/* Row Cycle, ps */
	unsigned long	tFAW;		/* Four Activation Window, ns */
	unsigned long	tPRECKE;
	unsigned long	CL;		/* CAS Latency, Clock cycles */
	unsigned long	CWL;		/* CAS Write Latency, Clock cycles */
	unsigned long	AL;		/* Additive Latency, Clock cycles */
	unsigned long	TZQOPER;	/* Calibration time, Clock cycles */
	unsigned long	TZQCS;		/* Calibration time short, Clock cycles */

#define TRTP		MAX(4, PS_TO_CYCLES_UP(7500UL))		/* Read to Precharge, Clock Cycles */
#define TWTR		MAX(4, PS_TO_CYCLES_UP(7500UL))		/* Write to Read, Clock Cycles */
#define TRP		PS_TO_CYCLES_UP(tRP_ps)			/* Row Precharge delay, Clock Cycles */
#define TRCD		PS_TO_CYCLES_UP(tRCD_ps)		/* Row to Column delay, Clock Cycles */
#define TRAS		NS_TO_CYCLES_UP(tRAS)			/* Row Active Strobe, Clock Cycles */
#define TRRD		MAX(4, NS_TO_CYCLES_UP(10UL))		/* Row to Row Delay, Clock Cycles */
#define TRC		PS_TO_CYCLES_UP(tRC_ps)			/* Row Cycle, Clock Cycles */
#define TFAW		NS_TO_CYCLES_UP(tFAW)			/* Four Activation Window, Clock Cycles */
#define TMRD		4UL					/* Mode Register Delay, Clock Cycles */
#define TCCD		4UL					/* Column to Column Delay, Clock Cycles */
#define TMOD		MAX(12, NS_TO_CYCLES_UP(15UL))		/* Mode Update Delay, Clock Cycles */
#define TRFC		NS_TO_CYCLES_UP(tRFC)			/* Mode Update Delay, Clock Cycles */
#define TXS		MAX(5, NS_TO_CYCLES_UP(tRFC + 10UL))	/* Self-refresh Exit Delay, Clock Cycles */
#define TXSDLL		512UL
#define TXP		MAX(3, PS_TO_CYCLES_UP(7500UL))		/* Power down exit Delay, Clock Cycles */
#define TXPDLL		MAX(10, NS_TO_CYCLES_UP(24UL))
#define TXPR		MAX(5, NS_TO_CYCLES_UP(tRFC + 10))	/* Reset Clock exit time, Clock Cycles */
#define TCKE		MAX(3, NS_TO_CYCLES_UP(5UL))		/* CKE minimum width, Clock Cycles */
#define TCKESR		(TCKE + 1)
#define TCKSRX		MAX(5, NS_TO_CYCLES_UP(10UL))
#define TCKSRE		MAX(5, NS_TO_CYCLES_UP(10UL))
#define TDLLK		512UL					/* DLL Lock time, Clock Cycles */
#define BL		8UL					/* Burst Length */
#define RL		(CL + AL)				/* Read Latency */
#define WL		(CWL + AL)				/* Write Latency */
#define WR		NS_TO_CYCLES_UP(tWR)			/* Write Recovery */
};

#define OFFSETOF(TYPE, ELEMENT) ((unsigned int)&(((TYPE *)0)->ELEMENT))

#endif
