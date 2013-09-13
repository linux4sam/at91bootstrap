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
#ifndef __AT91_PIO_H__
#define __AT91_PIO_H__

/* Register offset in AT91S_PIO structure */
#define PIO_PER(p)		(0x0000 + (p) * 0x200)	/* PIO Enable Register */
#define PIO_PDR(p)		(0x0004 + (p) * 0x200)	/* PIO Disable Register */
#define PIO_PSR(p)		(0x0008 + (p) * 0x200)	/* PIO Status Register */
/* 0x000c */
#define PIO_OER(p)		(0x0010 + (p) * 0x200)	/* Output Enable Register */
#define PIO_ODR(p)		(0x0014 + (p) * 0x200)	/* Output Disable Registerr */
#define PIO_OSR(p)		(0x0018 + (p) * 0x200)	/* Output Status Register */
/* 0x001c */
#define PIO_IFER(p)		(0x0020 + (p) * 0x200)	/* Input Filter Enable Register */
#define PIO_IFDR(p)		(0x0024 + (p) * 0x200)	/* Input Filter Disable Register */
#define PIO_IFSR(p)		(0x0028 + (p) * 0x200)	/* Input Filter Status Register */
/* 0x002c */
#define PIO_SODR(p)		(0x0030 + (p) * 0x200)	/* Set Output Data Register */
#define PIO_CODR(p)		(0x0034 + (p) * 0x200)	/* Clear Output Data Register */
#define PIO_ODSR(p)		(0x0038 + (p) * 0x200)	/* Output Data Status Register */
#define PIO_PDSR(p)		(0x003c + (p) * 0x200)	/* Pin Data Status Register */
#define PIO_IER(p)		(0x0040 + (p) * 0x200)	/* Interrupt Enable Register */
#define PIO_IDR(p)		(0x0044 + (p) * 0x200)	/* Interrupt Disable Register */
#define PIO_IMR(p)		(0x0048 + (p) * 0x200)	/* Interrupt Mask Register */
#define PIO_ISR(p)		(0x004c + (p) * 0x200)	/* Interrupt Status Register */
#define PIO_MDER(p)		(0x0050 + (p) * 0x200)	/* Multi-driver Enable Register */
#define PIO_MDDR(p)		(0x0054 + (p) * 0x200)	/* Multi-driver Disable Register */
#define PIO_MDSR(p)		(0x0058 + (p) * 0x200)	/* Multi-driver Status Register */
/* 0x005c */
#define PIO_PPUDR(p)		(0x0060 + (p) * 0x200)	/* Pull-up Disable Register */
#define PIO_PPUER(p)		(0x0064 + (p) * 0x200)	/* Pull-up Enable Register */
#define PIO_PPUSR(p)		(0x0068 + (p) * 0x200)	/* Pull-up Status Register */
/* 0x006c */
#ifndef CONFIG_HAS_PIO3
#define PIO_ASR(p)		(0x0070 + (p) * 0x200)  // Select A Register
#define PIO_BSR(p)		(0x007c + (p) * 0x200)  // Select B Register
#define PIO_ABSR(p)		(0x0078 + (p) * 0x200)  // AB Select Status Register
/* 0x007c ~ 0x009c */
#else
#define PIO_SP1(p)		(0x0070 + (p) * 0x200)  // Select Peripheral 1 Register
#define PIO_SP2(p)		(0x0074 + (p) * 0x200)  // Select Peripheral 2 Register
#define PIO_ABSR(p)		(0x0078 + (p) * 0x200)  // AB Select Status Register
/* 0x007c ~ 0x008c */
#define PIO_PPDDR(p)		(0x0090 + (p) * 0x200)  // Pull-down Disable Register
#define PIO_PPDER(p)		(0x0094 + (p) * 0x200)  // Pull-down Enable Register
#define PIO_PPDSR(p)		(0x0098 + (p) * 0x200)  // Pull-down Status Register
/* 0x009c */
#endif	/* #ifndef CONFIG_HAS_PIO3 */
#define PIO_OWER(p)		(0x00a0 + (p) * 0x200)	/* Output Write Enable Register */
#define PIO_OWDR(p)		(0x00a4 + (p) * 0x200)	/* Output Write Disable Register */
#define PIO_OWSR(p)		(0x00a8 + (p) * 0x200)	/* Output Write Status Register */
/* 0x00ac */

#define AT91C_NUM_PIO		5

/* Number of IO handled by one PIO controller */
#define PIO_NUM_IO		32

#define	AT91C_PIN_PA(io)	(0 * PIO_NUM_IO + io)
#define	AT91C_PIN_PB(io)	(1 * PIO_NUM_IO + io)
#define	AT91C_PIN_PC(io)	(2 * PIO_NUM_IO + io)
#define	AT91C_PIN_PD(io)	(3 * PIO_NUM_IO + io)
#define	AT91C_PIN_PE(io)	(4 * PIO_NUM_IO + io)

/* define the register */
#define PIO_REG_PER		0x00
#define PIO_REG_OER		0x10
#define PIO_REG_CODR		0x34
#define PIO_REG_PPUDR		0x60
#define	PIO_REG_PPDDR		0x90

#endif /* #ifndef __AT91_PIO_H__ */
