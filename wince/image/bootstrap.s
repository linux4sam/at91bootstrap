;
; Copyright (c) Microsoft Corporation.  All rights reserved.
;
;
; Use of this source code is subject to the terms of the Microsoft end-user
; license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
; If you did not accept the terms of the EULA, you are not authorized to use
; this source code. For a copy of the EULA, please see the LICENSE.RTF on your
; install media.
;

    INCLUDE kxarm.h
	
     
    IMPORT main



Mode_SVC	     EQU    0x00000013
NoIntsMask       EQU    0x000000C0

;Romimage.exe needs a pTOC else the file .NB0 is not created
	EXPORT pTOC

;------CPWAIT------------------------------------------------------------------
; Params: $Rd      : temporary read register
; 
; Returns: nothing
; 
; Effects: corrupts $Rd
; 
; This macro is used to wait for coprocessor operations to complete.
; 
; Ex:
;
;    CPWAIT r0
;------------------------------------------------------------------------------
    MACRO
    CPWAIT  $Rd
    
    mrc     p15, 0, $Rd, c2, c0, 0       ; arbitrary read of CP15
    mov     $Rd, $Rd                     ; wait for it (foward dependency)
    sub     pc, pc, #4                   ; branch to next instruction
    
    MEND


;------------------------------------------------------------------------------
;- Area Definition
;-----------------
;- Must be defined as function to put first in the code as it must be mapped
;- at offset 0 of the flash EBI_CSR0, ie. at address 0 before remap.
;------------------------------------------------------------------------------
                AREA        reset, CODE, READONLY


;------------------------------------------------------------------------------
;- Define the entry point
;------------------------

	EXPORT	__ENTRY
;__ENTRY

    STARTUPTEXT    
    LEAF_ENTRY __ENTRY

;------------------------------------------------------------------------------
;- Exception vectors ( before Remap )
;------------------------------------
;- These vectors are read at address 0.
;- They absolutely requires to be in relative addresssing mode in order to 
;- guarantee a valid jump. For the moment, all are just looping (what may be 
;- dangerous in a final system). If an exception occurs before remap, this 
;- would result in an infinite loop. 
;------------------------------------------------------------------------------
resetini
				B           InitReset       	; reset
undefvec
				B           InitReset			; Undefined Instruction
swivec
				B           InitReset          	; Software Interrupt
pabtvec
				B           pabtvec         	; Prefetch Abort
dabtvec 
				B           dabtvec         	; Data Abort
rsvdvec
				B           rsvdvec         	; reserved
irqvec
				B           irqvec				; IRQ : read the AIC
fiqvec
				B           fiqvec          	; FIQ


;
; This pointer on TOC structure must be declared after enter table
; else the first fourth byte are replace by this pointer
;
pTOC
	DCD 0

; Init reset
InitReset
	;ldr     r0, =0x00300000 - 4
	;add pc,pc,r0

; Put the CPU in Supervisor mode (SVC) and disable IRQ and FIQ interrupts.
    ldr     r0, =(Mode_SVC :OR: NoIntsMask)
    msr     cpsr_c, r0

; Disable the MMU, caches, and write-buffer and flush.
    ldr     r0, =0x2043             ; enable access to all coprocessors
    mcr     p15, 0, r0, c15, c1, 0  ;
    CPWAIT  r0                      ;

    ldr     r0, =0x00000078         ; get a zero to turn things off (must write bits[6:3] as 1s)
    mcr     p15, 0, r0, c1, c0, 0   ; turn off MMU, I&D caches, and write buffer 
    CPWAIT  r0                      ;

    mvn     r0, #0                  ; grant manager access to all domains
    mcr     p15, 0, r0, c3, c0, 0   ;

; Icache enable and asynchronous clocking mode
;	mrc     p15,0,r6,c1,c0,0
;	orr     r6,r6,#0xC0000000
;	orr     r6,r6,#0x1000
;	mcr     p15,0,r6,c1,c0,0

;  Set up a supervisor mode stack.
    ldr sp, =BOOTLOADER_STACK_BASE

C_MAIN
; Jump to the C entrypoint.
    bl      main                 ; Jump to main.c::main(), never to return...
    
STALL
    b      STALL
               
	EXPORT  Jump
Jump
	mov pc, r0

	EXPORT set_cp15
set_cp15
	mcr p15, 0, r0, c1, c0, 0
	bx lr

	EXPORT get_cp15
get_cp15
	mrc p15, 0, r0, c1, c0, 0
	bx lr

	END
