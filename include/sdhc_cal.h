/*
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SDHC_CAL_H__
#define	__SDHC_CAL_H__

#define	SDMMC_CALCR	0x240	/* Calibration Control Register */

/* SDMMC_CALCR */
#define	SDMMC_CALCR_EN		(0x1 << 0)	/* PADs Calibration Enable */
#define	SDMMC_CALCR_ALWYSON	(0x1 << 4)	/* Calibration Analog Always ON */
#define	SDMMC_CALCR_CLKDIV_MASK	(0x7)
#define	SDMMC_CALCR_CLKDIV(v)	(((v) & SDMMC_CALCR_CLKDIV_MASK) << 1) /* Calibration Clock Division */

#endif
