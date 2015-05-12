/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation
 *
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
#define PIO_PER		0x0000	/* PIO Enable Register */
#define PIO_PDR		0x0004	/* PIO Disable Register */
#define PIO_PSR		0x0008	/* PIO Status Register */
/* 0x000c */
#define PIO_OER		0x0010	/* Output Enable Register */
#define PIO_ODR		0x0014	/* Output Disable Registerr */
#define PIO_OSR		0x0018	/* Output Status Register */
/* 0x001c */
#define PIO_IFER	0x0020	/* Input Filter Enable Register */
#define PIO_IFDR	0x0024	/* Input Filter Disable Register */
#define PIO_IFSR	0x0028	/* Input Filter Status Register */
/* 0x002c */
#define PIO_SODR	0x0030	/* Set Output Data Register */
#define PIO_CODR	0x0034	/* Clear Output Data Register */
#define PIO_ODSR	0x0038	/* Output Data Status Register */
#define PIO_PDSR	0x003c	/* Pin Data Status Register */
#define PIO_IER		0x0040	/* Interrupt Enable Register */
#define PIO_IDR		0x0044	/* Interrupt Disable Register */
#define PIO_IMR		0x0048	/* Interrupt Mask Register */
#define PIO_ISR		0x004c	/* Interrupt Status Register */
#define PIO_MDER	0x0050	/* Multi-driver Enable Register */
#define PIO_MDDR	0x0054	/* Multi-driver Disable Register */
#define PIO_MDSR	0x0058	/* Multi-driver Status Register */
/* 0x005c */
#define PIO_PPUDR	0x0060	/* Pull-up Disable Register */
#define PIO_PPUER	0x0064	/* Pull-up Enable Register */
#define PIO_PPUSR	0x0068	/* Pull-up Status Register */
/* 0x006c */
#ifndef CONFIG_HAS_PIO3
#define PIO_ASR		0x0070	/* Peripheral Select Register 1 */
#define PIO_BSR		0x0074	/* Peripheral Select Register 2 */
#define PIO_ABSR	0x0078	/* AB Select Status Register */
/* 0x007c ~ 0x009c */
#else
#define PIO_SP1		0x0070	/* Select Peripheral 1 Register */
#define PIO_SP2		0x0074	/* Select Peripheral 2 Register */
#define PIO_ABSR	0x0078	/* AB Select Status Register */
/* 0x007c ~ 0x008c */
#define PIO_PPDDR	0x0090	/* Pull-down Disable Register */
#define PIO_PPDER	0x0094	/* Pull-down Enable Register */
#define PIO_PPDSR	0x0098	/* Pull-down Status Register */
/* 0x009c */
#endif	/* #ifndef CONFIG_HAS_PIO3 */
#define PIO_OWER	0x00a0	/* Output Write Enable Register */
#define PIO_OWDR	0x00a4	/* Output Write Disable Register */
#define PIO_OWSR	0x00a8	/* Output Write Status Register */
/* 0x00ac */

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
