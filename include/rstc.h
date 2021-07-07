/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __RSTC_H__
#define __RSTC_H__

extern void cpu_reset(void);

extern void rstc_external_reset(void);

extern void rstc_ddr_phy_rst_deassert(void);
extern void rstc_ddr_rst_deassert(void);
extern void rstc_ddr_assert(void);

#endif	/* #ifndef __RSTC_H__ */
