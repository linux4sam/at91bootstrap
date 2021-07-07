/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#include <mon_macros.h>

.section monitor
	.text
	.align

	.global monitor_smc_handler

monitor_smc_handler:
	/* Save some workable registers */
	stmdb	sp!, {r0-r3}

	/*
	 * Depending on from which world the SMC is called from the code
	 * switches to appropriate world by properly setting the SCR
	 *  register.
	 */
	mrc	p15, 0, r0, c1, c1, 0	/* read SCR */
	ands	r1, r0, #NS_BIT
	/*
	 * If NS bit is set then it is a call from NWd
	 * Otherwise it is a return from SWd
	 */
	beq	swd_to_nwd

nwd_to_swd:
	bic	r0, r0, #NS_BIT
	mcr	p15, 0, r0, c1, c1, 0
	/* ~~~ We are in SWd from now on ~~~ */

	/* - Implement the NWd --> SWd sequence as described in mon_macro.h */
	/*   - Save NWd registers */
	ldr	r0, =MON_DATA_BASE
	/*     - monitor lr is NWd pc */
	str	lr,  [r0, #NWD_PC_OFF]
	/*     - monitor spsr is NWd cpsr */
	mrs	r1, spsr
	str	r1,  [r0, #NWD_CPSR_OFF]
	/*     - r8-r11 */
	str	r8,  [r0, #NWD_R8_OFF]
	str	r9,  [r0, #NWD_R9_OFF]
	str	r10, [r0, #NWD_R10_OFF]
	str	r11, [r0, #NWD_R11_OFF]
	/*     - sp & lr */
	cps	#Mode_SVC
	str	sp, [r0, #NWD_SVC_SP_OFF]
	str	lr, [r0, #NWD_SVC_LR_OFF]
	/*   - Restore SWd registers */
	/*     - sp */
	ldr	sp, [r0, #SWD_SVC_SP_OFF]
	cps	#Mode_MON

	/*     - lr pointer */
	add	lr, r0, #SWD_PC_OFF

	/* Restore corrupted registers */
	ldmia	sp!, {r0-r3}

	/*
	 * As ARM ARM is saying: On a context switch, software must
	 * take care of clearing the local Exclusive Monitor
	 */
	clrex

	/* Call service manager (svc_mgr_*) that further executes service function */
	/* (take cpsr from database as well) */
	rfe	lr

swd_to_nwd:
	/* - Implement the SWd -->NWd sequence as described in mon_macro.h */
	ldr	r0, =MON_DATA_BASE

	/*   - Save SWd sp registers */
	cps	#Mode_SVC
	str	sp,  [r0, #SWD_SVC_SP_OFF]

	/*   - Restrore SVC sp & lr */
	ldr	sp, [r0, #NWD_SVC_SP_OFF]
	ldr	lr, [r0, #NWD_SVC_LR_OFF]
	cps	#Mode_MON

	/* Switch to NWd */
	mrc	p15, 0, r1, c1, c1, 0
	orr	r1, r1, #NS_BIT
	mcr	p15, 0, r1, c1, c1, 0
	/* ~~~ We are in NWd from now on ~~~ */

	/*
	 * Restore NWd cpsr in monitor spsr such that
	 * it returns to NWd by restoring spsr to NWd
	 */
	ldr	r1, [r0, #NWD_CPSR_OFF]
	msr	spsr_cxsf, r1

	/*     - lr pointer */
	add	lr, r0, #NWD_PC_OFF

	/*     - r8-r11*/
	ldr	r8, [r0, #NWD_R8_OFF]
	ldr	r9, [r0, #NWD_R9_OFF]
	ldr	r10, [r0, #NWD_R10_OFF]
	ldr	r11, [r0, #NWD_R11_OFF]

	/* Only to adjust the stack pointer */
	ldmia	sp!, {r0-r3}

	/* Restore r0-r2 from DB for kernel loading */
	ldr	r3, =MON_DATA_BASE
	mov	r4, #DB_R012_VALID
	ldr	r5, [r3, #NWD_R012_VALID_OFF]
	cmp	r4, r5
	bne	not_valid

	mov	r4, #0x00
	str	r4, [r3, #NWD_R012_VALID_OFF]

	ldr	r0, [r3, #NWD_R0_OFF]
	ldr	r1, [r3, #NWD_R1_OFF]
	ldr	r2, [r3, #NWD_R2_OFF]
	b	zero_regs

not_valid:
	/* Zero out r1-r7 and r12 registers */
	mov	r1, #0
	mov	r2, #0

zero_regs:
	mov	r3, #0
	mov	r4, #0
	mov	r5, #0
	mov	r6, #0
	mov	r7, #0
	mov	r12, #0

	/*
	 * As ARM ARM is saying: On a context switch, software must
	 * take care of clearing the local Exclusive Monitor
	 */
	clrex

	/* Restore mon_lr to NWd return point */
	/* (take cpsr from database as well) */
	rfe	lr

	.end
