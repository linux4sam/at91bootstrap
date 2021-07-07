/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

.section svc_mgr
	.text
	.align

	.extern svc_mgr_main
	.global svc_mgr_veneer

svc_mgr_veneer:
	/* Push registers onto the stack */
	stmdb	sp!, {r0-r7}
	/* r0 should point to the argument structure */
	mov	r0, sp

	/* Call the C code SMC handler */
	bl	svc_mgr_main

	/* Restore the stack pointer to reset value */
	add	sp, sp, #(8*4)

	/* Return to Normal World */
	smc	#0

	bx	lr

	.end
