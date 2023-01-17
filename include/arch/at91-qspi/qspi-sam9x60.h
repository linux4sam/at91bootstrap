/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef	__AT91_QSPI_SAM9X60_H__
#define	__AT91_QSPI_SAM9X60_H__

#define	QSPI_SR		0x10	/* Status Register */
#define	QSPI_WICR	0x34	/* Write Instruction Code Register */
#define	QSPI_RICR	0x3c	/* Read Instruction Code Register */

#define	QSPI_MR_SMRM		(0x1 << 3)	/* Serial Memory Register Mode */
#define QSPI_MR_TAMPCLR		(0x1 << 7)	/* Tamper Clear Enable */
#define QSPI_MR_QICMEN		(0x1 << 13)	/* QSPI Inter-chip Mode Enable */

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
#define QSPI_IFR_TFRTYP		(0x1 << 12)
#define QSPI_IFR_DDREN		(0x1 << 15)
#define QSPI_IFR_APBTFRTYP	(0x1 << 24)
#define QSPI_IFR_DDRCMDEN	(0x1 << 26)

#define QSPI_SMR_SCRKL		(0x1 << 3)

#define QSPI_WPMR_WPITEN	(0x1 << 1)
#define QSPI_WPMR_WPCREN	(0x1 << 2)

#endif
