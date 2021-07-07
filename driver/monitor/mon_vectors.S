/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

.section monitor
	 .text
	 .align 8

	.extern monitor_smc_handler
	.global monitor_vectors

/*
 *-----------------------------------------------------------------------------
 * Monitor exception vector table
 *      Most of these exceptions does not do anything other than branching to
 *      itself except smc vector. The SMC vector jumps to smc handler which
 *      takes care of proper switching from NWd to SWd and from SWd to NWd.
 * -----------------------------------------------------------------------------
 */
monitor_vectors:
	b	.			/* Reset: not used by Monitor */
	b	.			/* Undef: not used by Monitor */
	ldr	pc, =monitor_smc_handler
	b	.			/* Prefetch: can be used by Monitor */
	b	.			/* Data abort: can be used by Monitor */
	b	.			/* RESERVED */
	b	.			/* IRQ: can be used by Monitor */
	b	.			/* FIQ: can be used by Monitor */

	.end
