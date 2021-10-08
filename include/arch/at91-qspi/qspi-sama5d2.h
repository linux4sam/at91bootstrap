/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef	__AT91_QSPI_SAMA5D2_H__
#define	__AT91_QSPI_SAMA5D2_H__

/*
 * Register Definitions
 */
#define	QSPI_SR		0x10	/* Status Register */
#define	QSPI_ICR	0x34	/* Instruction Code Register */

#define	QSPI_MR_LLB		(0x1 << 1)	/* Local Localback Enable */
#define	QSPI_MR_SMRM		(0x1 << 3)	/* Serial Memory Register Mode */

#define	QSPI_SR_RDRF		(0x1 << 0)	/* Receive Data Register Full */
#define	QSPI_SR_TDRE		(0x1 << 1)	/* Transmit Data Register Empty */
#define	QSPI_SR_TXEMPTY		(0x1 << 2)	/* Transmission Registers Empty */
#define	QSPI_SR_OVRES		(0x1 << 3)	/* Overrun Error Status */
#define	QSPI_SR_CSR		(0x1 << 8)	/* Chip Select Rise */
#define	QSPI_SR_CSS		(0x1 << 9)	/* Chip Select Status */
#define	QSPI_SR_INSTRE		(0x1 << 10)	/* Instruction End Status */
#define	QSPI_SR_QSPIENS		(0x1 << 24)	/* QSPI Enable Status */

#define	QSPI_SCR_SCBR		(0xff << 8)
#define	QSPI_SCR_SCBR_(x)	(((x) << 8) & QSPI_SCR_SCBR)	/* Serial Clock Baud Rate */

#define	QSPI_IFR_ADDRL		(0x1 << 10)	/* Address Length */
#define		QSPI_IFR_ADDRL_24_BIT		(0x0 << 10)
#define		QSPI_IFR_ADDRL_32_BIT		(0x1 << 10)
#define	QSPI_IFR_TFRTYPE_WRITE	(0x1 << 13)

#endif
