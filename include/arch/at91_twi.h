/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_TWI_H__
#define __AT91_TWI_H__

/**** Register offset in AT91_TWI structure ***/
#define TWI_CR		0x00	/* Control Register */
#define TWI_MMR		0x04	/* Master Mode Register */
#define TWI_SMR		0x08	/* Slave Mode Register */
#define TWI_IADR	0x0C	/* Internal Address Register */
#define TWI_CWGR	0x10	/* Clock Waveform Generator Register */
/* 0x14 - 0x1C Reserved */
#define TWI_SR		0x20	/* Status Register */
#define TWI_IER		0x24	/* Interrupt Enable Register */
#define TWI_IDR		0x28	/* Interrupt Disable Register */
#define TWI_IMR		0x2C	/* Interrupt Mask Register */
#define TWI_RHR		0x30	/* Receive Holding Register */
#define TWI_THR		0x34	/* Transmit Holding Register */

#define TWI_WPROT_MODE		0xE4	/* Protection Mode Register */
#define TWI_WPROT_STATUS	0xE8	/* Protection Status Register */
#define TWI_VERSION		0xFC

/*-------- TWI_CR : (Offset: 0x00) Control Register --------*/
#define TWI_CR_START		(0x1UL << 0)	/* Send a START condition */
#define TWI_CR_STOP		(0x1UL << 1)	/* Send a STOP condition */
#define TWI_CR_MSEN		(0x1UL << 2)	/* TWI Master Mode Enabled */
#define TWI_CR_MSDIS		(0x1UL << 3)	/* TWI Master Mode Disabled */
#define TWI_CR_SVEN		(0x1UL << 4)	/* TWI Slave Mode Enabled */
#define TWI_CR_SVDIS		(0x1UL << 5)	/* TWI Slave Mode Disabled */
#define TWI_CR_QUICK		(0x1UL << 6)	/* SMBUS Quick Command */
#define TWI_CR_SWRST		(0x1UL << 7)	/* Software Reset */

/*-------- TWI_MMR : (Offset: 0x04) Control Register --------*/
#define TWI_MMR_IADRSZ(isize)	(isize << 8)
#define TWI_MMR_MREAD		(0x01UL << 12)
#define		TWI_MMR_MREAD_WR	(0x00UL << 12)
#define		TWI_MMR_MREAD_RD	(0x01UL << 12)
#define	TWI_MMR_DADR(addr)	(addr << 16)

/*-------- TWI_CWGR : (Offset: 0x10) Clock Waveform Generator Register --*/
#define TWI_CWGR_HOLD		(0x01 << 24)
#define		TWI_CWGR_HOLD_(x)	((x) << 24)

/*-------- TWI_SR : (Offset: 0x20) Status Register --------*/
#define TWI_SR_TXCOMP		(0x01UL	<< 0)
#define TWI_SR_RXRDY		(0x01UL	<< 1)
#define TWI_SR_TXRDY		(0x01UL	<< 2)
#define TWI_SR_SVREAD		(0x01UL	<< 3)
#define TWI_SR_SVACC		(0x01UL	<< 4)
#define TWI_SR_GACC		(0x01UL	<< 5)
#define TWI_SR_OVRE		(0x01UL	<< 6)
#define TWI_SR_NACK		(0x01UL	<< 8)
#define TWI_SR_ARBLST		(0x01UL	<< 9)
#define TWI_SR_SCLWS		(0x01UL	<< 10)
#define TWI_SR_EOSACC		(0x01UL	<< 11)

#endif /* #ifndef __AT91_TWI_H__ */
