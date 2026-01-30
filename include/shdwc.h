/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SHDWC_H__
#define __SHDWC_H__

extern void shdwc_disable_lpm(void);
extern unsigned int shdwc_read_status(void);
extern void shdwc_shutdown(void);

#endif	/* #ifndef __SHDWC_H__ */
