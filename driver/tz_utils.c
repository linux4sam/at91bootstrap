// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "mon_macros.h"
#include "mon.h"
#include "debug.h"

void dacr_swd_init(void)
{
	asm volatile (
		"mcr	p15, 0, %0, c3, c0, 0\n\t"
		"isb"
		:
		: "r" (0x55555555));
}

/* Enable access to CP 10 & 11 */
void cpacr_init(void)
{
	asm volatile (
		"mrc	p15, 0, r0, c1, c0, 2\n\t"
		"orr	r0, r0, %0\n\t"
		"mcr	p15, 0, r0, c1, c0, 2\n\t"
		"isb"
		:
		: "r" (0xf << 20)
		: "r0");
}

void enter_normal_world(void)
{
	asm volatile ("smc #0");
}

void switch_normal_world(void)
{
	monitor_init();

	dbg_info("Enter Normal World, Run at %x\n", NWD_BOOT_ADDR);

	enter_normal_world();
}
