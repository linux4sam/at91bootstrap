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
#define	QSPI_ICR	0x34	/* Instruction Code Register */

#define	QSPI_MR_LLB		(0x1 << 1)	/* Local Localback Enable */

#define	QSPI_IFR_TFRTYPE_WRITE	(0x1 << 13)

#endif
