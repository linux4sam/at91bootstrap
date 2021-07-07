/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __PIT_TIMER_H__
#define __PIT_TIMER_H__

extern int timer_init(void);

extern void udelay(unsigned int usec);
extern void mdelay(unsigned int msec);

extern int start_interval_timer(void);
extern int wait_interval_timer(unsigned int usec);

#endif /* #ifndef __PIT_TIMER_H__ */
