/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SLOWCLK_H__
#define __SLOWCLK_H__

extern int slowclk_enable_osc32(void);
extern int slowclk_switch_rc32(void);
extern int slowclk_switch_osc32(void);
extern int slowclk_switch_osc32_bypass(void);

#endif /* #ifndef __SLOWCLK_H__ */
