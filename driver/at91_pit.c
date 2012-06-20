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
#include "arch/at91_pit.h"
#include "board.h"

static inline int pit_readl(unsigned int reg)
{
	return(readl(AT91C_BASE_PITC + reg));
}

static inline void pit_writel(unsigned int value, unsigned reg)
{
	writel(value, (AT91C_BASE_PITC + reg));
}

/* time unit: ms */
int start_intervl_timer(unsigned int time)
{
	unsigned int interval_val;
	unsigned int reg;

	interval_val = (MASTER_CLOCK / 16 / 1000) * time;
	if (interval_val > 0xFFFFF)
		return -1;

	reg = interval_val | AT91C_PIT_PITEN;
	pit_writel(reg, PIT_MR);

	return 0;
}

/* wait_timer unit: ms */
/* timer unit: ms */
unsigned int wait_interval_timer(unsigned int wait_time, unsigned int timer)
{
	unsigned int check_counter = wait_time / timer;
	unsigned int counter;

	if (check_counter > 0xFFF)
		return -1;

	do {
		counter = pit_readl(PIT_PIIR) >> 20;
	} while (counter < check_counter);

	pit_writel(0x00, PIT_MR);

	return 0;
}

/* time unit: us */
int wait_timer(unsigned int time)
{
	unsigned int reg;
	unsigned int interval_val;

	interval_val = ((MASTER_CLOCK / 1000) * time) / 16 / 1000;
	if (interval_val > 0xFFFFF)
		return -1;

	/* enable PIT */
	reg = interval_val | AT91C_PIT_PITEN;
	pit_writel(reg, PIT_MR);

	/* clear bit PITS in PIT_SR */
	pit_readl(PIT_PIVR);

	while((pit_readl(PIT_SR) & AT91C_PIT_PITS) == 0);

	pit_writel(0x00, PIT_MR);

	return 0;
}
