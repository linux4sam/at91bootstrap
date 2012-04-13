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
 * ----------------------------------------------------------------------------
 * File Name           :at91_pio.h
 * Object              :
 * Creation            : 
 *-----------------------------------------------------------------------------
 */

#ifndef AT91_PIO_H
#define AT91_PIO_H

/* Register offset in AT91S_PIO structure */
#define PIO_PER(p)		( 0 + (p) * 0x200)	/* PIO Enable Register */
#define PIO_PDR(p)		( 4 + (p) * 0x200)	/* PIO Disable Register */
#define PIO_PSR(p)		( 8 + (p) * 0x200)	/* PIO Status Register */
#define PIO_OER(p)		(16 + (p) * 0x200)	/* Output Enable Register */
#define PIO_ODR(p)		(20 + (p) * 0x200)	/* Output Disable Registerr */
#define PIO_OSR(p)		(24 + (p) * 0x200)	/* Output Status Register */
#define PIO_IFER(p)		(32 + (p) * 0x200)	/* Input Filter Enable Register */
#define PIO_IFDR(p)		(36 + (p) * 0x200)	/* Input Filter Disable Register */
#define PIO_IFSR(p)		(40 + (p) * 0x200)	/* Input Filter Status Register */
#define PIO_SODR(p)		(48 + (p) * 0x200)	/* Set Output Data Register */
#define PIO_CODR(p)		(52 + (p) * 0x200)	/* Clear Output Data Register */
#define PIO_ODSR(p)		(56 + (p) * 0x200)	/* Output Data Status Register */
#define PIO_PDSR(p)		(60 + (p) * 0x200)	/* Pin Data Status Register */
#define PIO_IER(p)		(64 + (p) * 0x200)	/* Interrupt Enable Register */
#define PIO_IDR(p)		(68 + (p) * 0x200)	/* Interrupt Disable Register */
#define PIO_IMR(p)		(72 + (p) * 0x200)	/* Interrupt Mask Register */
#define PIO_ISR(p)		(76 + (p) * 0x200)	/* Interrupt Status Register */
#define PIO_MDER(p)		(80 + (p) * 0x200)	/* Multi-driver Enable Register */
#define PIO_MDDR(p)		(84 + (p) * 0x200)	/* Multi-driver Disable Register */
#define PIO_MDSR(p)		(88 + (p) * 0x200)	/* Multi-driver Status Register */
#define PIO_PPUDR(p)		(96 + (p) * 0x200)	/* Pull-up Disable Register */
#define PIO_PPUER(p)		(100 + (p) * 0x200)	/* Pull-up Enable Register */
#define PIO_PPUSR(p)		(104 + (p) * 0x200)	/* Pull-up Status Register */
#define PIO_SP1(p)		(112 + (p) * 0x200)	/* Select Peripheral 1 Register */
#define PIO_SP2(p)		(116 + (p) * 0x200)	/* Select Peripheral 2 Register */
#define PIO_ABSR(p)		(120 + (p) * 0x200)	/* AB Select Status Register */
#define PIO_PPDDR(p)		(144 + (p) * 0x200)	/* Pull-down Disable Register */
#define PIO_PPDER(p)		(148 + (p) * 0x200)	/* Pull-down Enable Register */
#define PIO_PPDSR(p)		(152 + (p) * 0x200)	/* Pull-down Status Register */
#define PIO_OWER(p)		(160 + (p) * 0x200)	/* Output Write Enable Register */
#define PIO_OWDR(p)		(164 + (p) * 0x200)	/* Output Write Disable Register */
#define PIO_OWSR(p)		(168 + (p) * 0x200)	/* Output Write Status Register */
#define PIO_ADDRSIZE(p)		(236 + (p) * 0x200)	/* PIO ADDRSIZE REGISTER */
#define PIO_IPNAME1(p)		(240 + (p) * 0x200)	/* PIO IPNAME1  REGISTER */
#define PIO_IPNAME2(p)		(244 + (p) * 0x200)	/* PIO IPNAME2  REGISTER */
#define PIO_FEATURES(p)		(248 + (p) * 0x200)	/* PIO FEATURES REGISTER */
#define PIO_VER(p)		(252 + (p) * 0x200)	/* PIO VERSION  REGISTER */
#define PIO_SCHMITT(p)		(256 + (p) * 0x200)	/* PIO SCHMITT Register */
#define PIO_DELAY1(p)		(272 + (p) * 0x200)	/* PIO DELAY1  Register */
#define PIO_DRIVE1(p)		(276 + (p) * 0x200)	/* PIO DRIVE1  Register */
#define PIO_DRIVE2(p)		(280 + (p) * 0x200)	/* PIO DRIVE2  Register */
#define PIO_SENMR(p)		(336 + (p) * 0x200)	/* Sensor Mode Register */
#define PIO_SENIER(p)		(340 + (p) * 0x200)	/* Sensor Interrupt Enable Register */
#define PIO_SENIDR(p)		(344 + (p) * 0x200)	/* Sensor Interrupt Disable Register */
#define PIO_SENIMR(p)		(348 + (p) * 0x200)	/* Sensor Interrupt Mask Register */
#define PIO_SENISR(p)		(352 + (p) * 0x200)	/* Sensor Interrupt Status Register */
#define PIO_SENDATA(p)		(356 + (p) * 0x200)	/* Sensor Data Register */

#define AT91C_NUM_PIO		(32 * 4)

/* Number of IO handled by one PIO controller */
#define PIO_NUM_IO		32

#define	AT91C_PIN_PA(io)	(0 * PIO_NUM_IO + io)
#define	AT91C_PIN_PB(io)	(1 * PIO_NUM_IO + io)
#define	AT91C_PIN_PC(io)	(2 * PIO_NUM_IO + io)
#define	AT91C_PIN_PD(io)	(3 * PIO_NUM_IO + io)
#define	AT91C_PIN_PE(io)	(4 * PIO_NUM_IO + io)

#endif /* #ifndef AT91_PIO_H */
