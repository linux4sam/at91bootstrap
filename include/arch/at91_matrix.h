
/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
#ifndef __AT91_MATRIX_H__
#define __AT91_MATRIX_H__

#define MATRIX_MCFG0	0x00	/*  Master Configuration Register 0 (ram96k) */
#define MATRIX_MCFG1	0x04	/*  Master Configuration Register 1 (rom) */
#define MATRIX_MCFG2	0x08	/*  Master Configuration Register 2 (hperiphs) */
#define MATRIX_MCFG3	0x0c	/*  Master Configuration Register 3 (ebi) */
#define MATRIX_MCFG4	0x10	/*  Master Configuration Register 4 (bridge) */
#define MATRIX_MCFG5	0x14	/*  Master Configuration Register 5 (mailbox) */
/* 0x18 ~ 0x3c reserved */
#define MATRIX_SCFG0	0x40	/*  Slave Configuration Register 0 (ram96k) */
#define MATRIX_SCFG1	0x44	/*  Slave Configuration Register 1 (rom) */
#define MATRIX_SCFG2	0x48	/*  Slave Configuration Register 2 (hperiphs) */
#define MATRIX_SCFG3	0x4c	/*  Slave Configuration Register 3 (ebi) */
#define MATRIX_SCFG4	0x50	/*  Slave Configuration Register 4 (bridge) */
/* 0x54 ~ 0x7c reserved */
#define MATRIX_PRAS0	0x80	/*  PRAS0 (ram0) */
/* 0x84 */
#define MATRIX_PRAS1	0x88	/*  PRAS1 (ram1) */
/* 0x8c */
#define MATRIX_PRAS2	0x90	/*  PRAS2 (ram2) */
/* 0x94 */
#define MATRIX_PRAS3	0x98	/*  PRAS3 (ebi) */
/* 0x9c */
#define MATRIX_PRAS4	0xa0	/*  PRAS4 (periph) */

/*-------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 ----*/
#define AT91C_MATRIX_SLOT_CYCLE   (0xFF << 0)	/* Maximum Number of Allowed Cycles for a Burst */
#define AT91C_MATRIX_DEFMSTR_TYPE (0x3 << 16)	/* Default Master Type */
#define 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           (0x0 << 16)
#define 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         (0x1 << 16)
#define 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        (0x2 << 16
#define AT91C_MATRIX_FIXED_DEFMSTR0 (0x7 << 18)	/* Fixed Index of Default Master */
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              (0x0 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              (0x1 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_HPDC3                (0x2 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_LCDC                 (0x3 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA                  (0x4 << 18)

/*-------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 ------*/
#define AT91C_MATRIX_FIXED_DEFMSTR1 (0x7 << 18)		/* Fixed Index of Default Master */
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              (0x0 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              (0x1 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_HPDC3                (0x2 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_LCDC                 (0x3 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA                  (0x4 << 18)

/*-------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 ------*/
#define AT91C_MATRIX_FIXED_DEFMSTR2 (0x1 << 18)		/* Fixed Index of Default Master */
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              (0x0 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              (0x1 << 18)

/*-------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 ------*/
#define AT91C_MATRIX_FIXED_DEFMSTR3 (0x7 << 18)		/* Fixed Index of Default Master */
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              (0x0 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              (0x1 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_HPDC3                (0x2 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_LCDC                 (0x3 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_DMA                  (0x4 << 18)

/*-------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 ------*/
#define AT91C_MATRIX_FIXED_DEFMSTR4 (0x3 << 18)		/* Fixed Index of Default Master */
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              (0x0 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              (0x1 << 18)
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_HPDC3                (0x2 << 18)

/*-------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register --------*/
#define AT91C_MATRIX_RCA926I      (0x1 <<  0)		/* Remap Command for ARM926EJ-S Instruction Master */
#define AT91C_MATRIX_RCA926D      (0x1 <<  1)		/* Remap Command for ARM926EJ-S Data Master */

#endif	/* #ifndef __AT91_MATRIX_H__ */
