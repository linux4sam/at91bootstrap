/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

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
#include "hardware.h"
#include "board.h"

#include "arch/at91_pit.h"
#include "arch/at91_pmc.h"

#define TIMER_LOAD_VAL  0xfffff

static inline int pit_readl(unsigned int reg)
{
	return(readl(AT91C_BASE_PITC + reg));
}

static inline void pit_writel(unsigned int value, unsigned reg)
{
	writel(value, (AT91C_BASE_PITC + reg));
}

/*
 * Use the PITC in full 32 bit incrementing mode
 * If MASTER_CLOCK = 132M, the maximum delay is about 520.6 second(8.6767 min).
 * it is long enough for our use.
 */
int timer_init(void)
{
	pit_writel((TIMER_LOAD_VAL | AT91C_PIT_PITEN), PIT_MR);

	/* Enable PITC Clock */
#ifdef AT91C_ID_PIT
	writel((1 << AT91C_ID_PIT), (PMC_PCER + AT91C_BASE_PMC));
#else
	writel((1 << AT91C_ID_SYS), (PMC_PCER + AT91C_BASE_PMC));
#endif
	return 0;
}

/* If MASTER_CLOCK = 132M, usec <= 21537 us (0xffffffff / 132000) */
static unsigned int usec_to_tick(unsigned int usec)
{
	unsigned int tick;

	tick = ((MASTER_CLOCK / 1000) * usec) / (16 * 1000);

	return tick;
}

static unsigned int msec_to_tick(unsigned int msec)
{
	unsigned int tick;

	tick = ((MASTER_CLOCK / 1000) * msec) / 16;

	return tick;
}

static unsigned int get_ticks(void)
{
	return(pit_readl(PIT_PIIR));
}


void udelay(unsigned int usec)
{
	unsigned int start = get_ticks();
	unsigned int tmo = usec_to_tick(usec);

	while ((get_ticks() - start) < tmo);
}

/* Init a special timer for slow clock switch function */
static int timer1_base;

int start_interval_timer(void)
{
	timer1_base = get_ticks();

	return 0;
}

int wait_interval_timer(unsigned int msec)
{
	unsigned int tmo = msec_to_tick(msec);

	while ((get_ticks() - timer1_base) < tmo);

	return 0;
}
