/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_EEFC_H__
#define __AT91_EEFC_H__

#define EEFC_FMR		0x00	/* EEFC Flash Mode Register */
#define EEFC_FCR		0x04	/* EEFC Flash Command Register */
#define EEFC_FSR		0x08	/* EEFC Flash Status Register */
#define EEFC_FRR		0x0c	/* EEFC Flash Result Register */

/*-------- EEFC_FMR : (EEFC Offset: 0x0) EEFC Flash Mode Register --------*/ 
#define AT91C_EEFC_FRDY		(0x1 << 0)	/* Ready Interrupt Enable */
#define AT91C_EEFC_FWS		(0xF << 8)	/* Flash Wait State */
#define 	AT91C_EEFC_FWS_0WS		(0x0 << 8)
#define 	AT91C_EEFC_FWS_1WS		(0x1 << 8)
#define 	AT91C_EEFC_FWS_2WS		(0x2 << 8)
#define 	AT91C_EEFC_FWS_3WS		(0x3 << 8)
#define 	AT91C_EEFC_FWS_4WS		(0x4 << 8)
#define 	AT91C_EEFC_FWS_5WS		(0x5 << 8)
#define 	AT91C_EEFC_FWS_6WS		(0x6 << 8)

/*-------- EEFC_FCR : (EEFC Offset: 0x4) EEFC Flash Command Register --------*/ 
#define AT91C_EEFC_FCMD		(0xFF << 0)	/* Flash Command */
#define 	AT91C_EEFC_FCMD_GETD		(0x0)
#define 	AT91C_EEFC_FCMD_WP		(0x1)
#define 	AT91C_EEFC_FCMD_WPL		(0x2)
#define 	AT91C_EEFC_FCMD_EWP		(0x3)
#define 	AT91C_EEFC_FCMD_EWPL		(0x4)
#define 	AT91C_EEFC_FCMD_EA		(0x5)
#define 	AT91C_EEFC_FCMD_EPL		(0x6)
#define 	AT91C_EEFC_FCMD_EPA		(0x7)
#define 	AT91C_EEFC_FCMD_SLB		(0x8)
#define 	AT91C_EEFC_FCMD_CLB		(0x9)
#define 	AT91C_EEFC_FCMD_GLB		(0xA)
#define 	AT91C_EEFC_FCMD_SFB		(0xB)
#define 	AT91C_EEFC_FCMD_CFB		(0xC)
#define 	AT91C_EEFC_FCMD_GFB		(0xD)
#define AT91C_EEFC_FARG		(0xFFFF << 8)	/* Flash Command Argument */
#define AT91C_EEFC_FKEY		(0xFF << 24)	/* Flash Writing Protection Key */

/*-------- EEFC_FSR : (EEFC Offset: 0x8) EEFC Flash Status Register --------*/ 
#define AT91C_EEFC_FRDYS	(0x1 << 0)	/* Flash Ready Status */
#define AT91C_EEFC_FCMDE	(0x1 << 1)	/* Flash Command Error Status */
#define AT91C_EEFC_LOCKE	(0x1 << 2)	/* Flash Lock Error Status */

/*-------- EEFC_FRR : (EEFC Offset: 0xc) EEFC Flash Result Register --------*/ 
#define AT91C_EEFC_FVALUE	(0x0 << 0)	/* Flash Result Value */

#endif /* #ifndef __AT91_EEEFC_H__ */
