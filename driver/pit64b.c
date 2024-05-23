// Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "board.h"
#include "debug.h"
#include "div.h"
#include "pmc.h"
#include "types.h"

#include "arch/at91_pmc/pmc.h"

#define MCHP_PIT64B_CR			0x00	/* Control Register */
#define		MCHP_PIT64B_CR_START	(1UL << 0)
#define 	MCHP_PIT64B_CR_SWRST	(1UL << 8)
#define MCHP_PIT64B_MR			0x04	/* Mode Register */
#define		MCHP_PIT64B_MR_CONT	(1UL << 0)
#define MCHP_PIT64B_LSB_PR		0x08	/* LSB Period Register */
#define MCHP_PIT64B_MSB_PR		0x0C	/* MSB Period Register */
#define MCHP_PIT64B_TLSBR		0x20	/* Timer LSB Register */
#define MCHP_PIT64B_TMSBR		0x24	/* Timer MSB Register */

#define MAX_PIT64B	(~0UL)

static u32 clk_rate = 0;

static inline unsigned int pit64b_readl(unsigned int reg)
{
	return readl(AT91C_BASE_PIT64BC + reg);
}

static inline void pit64b_writel(unsigned int value, unsigned reg)
{
	writel(value, (AT91C_BASE_PIT64BC + reg));
}

/**
 * timer_init() - initialize timer to be used for {u, m}delay() operations
 *
 * Notice: call this after clocks feeding PIT64B peripheral clock were
 * 	   initialized
 */
int timer_init(void)
{
	pmc_enable_periph_clock(AT91C_ID_PIT64B, PMC_PERIPH_CLK_DIVIDER_NA);
	clk_rate = pmc_periph_clock_get_rate(AT91C_ID_PIT64B);
	/*
	 * Set it at maximum value. It is enough even for a peripheral
	 * clock running at 1GHz.
	 */
	pit64b_writel(MCHP_PIT64B_CR_SWRST, MCHP_PIT64B_CR);
	pit64b_writel(MCHP_PIT64B_MR_CONT, MCHP_PIT64B_MR);
	pit64b_writel(MAX_PIT64B, MCHP_PIT64B_MSB_PR);
	pit64b_writel(MAX_PIT64B, MCHP_PIT64B_LSB_PR);
	pit64b_writel(MCHP_PIT64B_CR_START, MCHP_PIT64B_CR);

	return 0;
}

static u64 pit64b_read_value(void)
{
	u32 low, high;

	low = pit64b_readl(MCHP_PIT64B_TLSBR);
	high = pit64b_readl(MCHP_PIT64B_TMSBR);

	return (((u64)high << 32) | low);
}

void udelay(unsigned int usec)
{
	u64 base = pit64b_read_value();
	u64 end = base + (clk_rate / 1000000) * usec;
	u64 current;

	do {
		current = pit64b_read_value();
	} while (current < end);
}

void mdelay(unsigned int msec)
{
	u64 base = pit64b_read_value();
	u64 end = base + (clk_rate / 1000) * msec;
	u64 current;

	do {
		current = pit64b_read_value();
	} while (current < end);
}

/* Init a special timer for slow clock switch function */
static u64 timer1_base;

int start_interval_timer(void)
{
	timer1_base = pit64b_read_value();

	return 0;
}

int wait_interval_timer(unsigned int msec)
{
	u64 end = timer1_base + (clk_rate / 1000) * msec;
	u64 current;

	do {
		current = pit64b_read_value();
	} while (current < end);

	return 0;
}
