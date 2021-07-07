/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_PIT_H__
#define __AT91_PIT_H__

/**** Register offset in AT91S_PITC structure ***/
#define PIT_MR		0x00	/* Period Interval Mode Register */
#define PIT_SR		0x04	/* Period Interval Status Register */
#define PIT_PIVR	0x08	/* Period Interval Value Register */
#define PIT_PIIR	0x0c	/* Period Interval Image Register */

/*-------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------*/
#define AT91C_PIT_PIV		(0xFFFFF << 0)	/* Periodic Interval Value */
#define AT91C_PIT_PITEN	(0x01 << 24)	/* Periodic Interval Timer Enabled */
#define AT91C_PIT_PITIEN	(0x01 << 25)	/* Periodic Interval Timer Interrupt Enable */
/*-------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register --------*/
#define AT91C_PIT_PITS		(0x01 << 0)	/* (PITC) Periodic Interval Timer Status */
/*-------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register --------*/
/*-------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register --------*/
#define AT91C_PIT_CPIV		(0xFFFFF << 0)	/* (PITC) Current Periodic Interval Value */
#define AT91C_PIT_PICNT	(0xFFF << 20)	/* (PITC) Periodic Interval Counter */

#endif /* #ifndef __AT91_PIT_H__ */
