/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef	__AT91_QSPI_SAM9X60_H__
#define	__AT91_QSPI_SAM9X60_H__

#define	QSPI_WICR	0x34	/* Write Instruction Code Register */
#define	QSPI_RICR	0x3c	/* Read Instruction Code Register */

#define QSPI_MR_TAMPCLR		(0x1 << 7)	/* Tamper Clear Enable */
#define QSPI_MR_QICMEN		(0x1 << 13)	/* QSPI Inter-chip Mode Enable */

#define QSPI_IFR_TFRTYP		(0x1 << 12)
#define QSPI_IFR_DDREN		(0x1 << 15)
#define QSPI_IFR_APBTFRTYP	(0x1 << 24)
#define QSPI_IFR_DDRCMDEN	(0x1 << 26)

#define QSPI_SMR_SCRKL		(0x1 << 3)

#define QSPI_WPMR_WPITEN	(0x1 << 1)
#define QSPI_WPMR_WPCREN	(0x1 << 2)

#endif
