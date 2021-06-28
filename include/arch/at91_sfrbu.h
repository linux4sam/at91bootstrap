/*
 * Copyright (C) 2016 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_SFRBU_H__
#define __AT91_SFRBU_H__

/*
 * Register Offset
 */
#define SFRBU_PSWBU	0x0	/* Power Switch BU Control Register */
#define SFRBU_DDRBUMCR	0x10	/* DDR BU Mode Control Register */

/*
 * Register Fields
 */
/*--- SFRBU_PSWBU: (offset: 0x0) Power Switch BU Control Register */
#define AT91C_PSWBU_PSWKEY	(0x4BD20C << 8)
#define AT9CC_PWSBU_CTRL	(1 << 0)
#define AT91C_PSWBU_SOFTSWITCH	(1 << 1)
#ifdef CONFIG_SAMA7G5
#define AT91C_BSWBU_SMCTRL	(0)
#define AT91C_PSWBU_STATE	(1 << 2)
#else
#define AT91C_PSWBU_SMCTRL	(1 << 2)
#define AT91C_PSWBU_STATE	(1 << 3)
#endif

/*--- SFRBU_DDRMCR: (offset: 0x10) DDR BU Mode Control Register ---*/
#define AT91C_DDRBUMCR_BUMEN	0x01	/* Force DDR_DQ Input Buffer Always On */

extern void sfrbu_select_ba_power_source(int vddin33);
extern void sfrbu_set_ddr_power_mode(int on);
extern int sfrbu_ddr_is_powered(void);

#endif /* #ifndef __AT91_SFRBU_H__ */
