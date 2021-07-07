/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_CCFG_H__
#define __AT91_CCFG_H__

#define CCFG_ROM		0x04	/* Slave 1 (ROM) Wait-State Configuration Register */
#define CCFG_EBICSA		0x08	/* EBI Chip Select Assignement Register */
#define CCFG_UDPHS		0x0C	/* USB Device HS configuration Register */
#define CCFG_EBI0CSA		0x10	/* EBI0 Chip Select Assignement Register */
#define CCFG_EBI1CSA		0x14	/* EBI1 Chip Select Assignement Register */
#define CCFG_MATRIXVERSION	0xEC	/* Version Register */

/* -------- CCFG_ROM : (CCFG Offset: 0x4) AHB Slave 1 (ROM) Configuration --------*/ 
#define AT91C_ROM_WS_CFG	(0x1UL << 0)
#define 	AT91C_ROM_WS_CFG_NO_WAIT		(0x0UL)
#define 	AT91C_ROM_WS_CFG_SINGLE_WAIT		(0x1UL)

/* -------- CCFG_UDPHS : (CCFG Offset: 0xc) USB Device HS configuration --------*/ 
#define AT91C_CCFG_DONT_USE_UTMI_LOCK	(0x1UL << 0)
#define 	AT91C_CCFG_DONT_USE_UTMI_LOCK_DONT_USE_LOCK	(0x0UL)

/* -------- CCFG_EBICSA : (CCFG Offset: 0x10) EBI Chip Select Assignement Register --------*/ 
#define AT91C_EBI_CS1A		(0x1UL << 1)
#define 	AT91C_EBI_CS1A_SMC		(0x0UL << 1)
#define 	AT91C_EBI_CS1A_SDRAMC		(0x1UL << 1)
#define AT91C_EBI_CS3A		(0x1UL << 3)
#define 	AT91C_EBI_CS3A_SMC		(0x0UL << 3)
#define 	AT91C_EBI_CS3A_SM		(0x1UL << 3)
#define AT91C_EBI_DBPUC		(0x1UL << 8)
#define AT91C_EBI_DBPDC		(0x1UL << 9)
#define AT91C_VDDIOM_SEL	(0x1UL << 16)
#define 	AT91C_VDDIOM_SEL_18V		(0x0UL << 16)
#define 	AT91C_VDDIOM_SEL_33V		(0x1UL << 16)
#define AT91C_EBI_DRV		(0x1UL << 17)
#define 	AT91C_EBI_DRV_LD		(0x0UL << 17)
#define 	AT91C_EBI_DRV_HD		(0x1UL << 17)
#define AT91C_EBI_NFD0_ON_D16	(0x1UL << 24)
#define AT91C_EBI_DDR_MP_EN	(0x1UL << 25)

#endif /* #ifndef __AT91_CCFG_H__ */
