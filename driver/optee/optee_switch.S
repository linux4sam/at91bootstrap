/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#include <hardware.h>

	.text
	.align
	.thumb_func
/*
 * OP-TEE expect the following boot arguments
 * r0: pagestore
 * r1: (ARMv7 standard bootarg #1)
 * r2: device tree address, (ARMv7 standard bootarg #2)
 * r3: return address
 */
.global optee_start
optee_start:
	mov	lr, r3
	ldr	r4, =CONFIG_OPTEE_JUMP_ADDR
	bx	r4
	b	.

.end
