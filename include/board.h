/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef CONFIG_SAM9X60
#include "sam9x60_board.h"
#endif

#ifdef CONFIG_SAMA5D2
#include "sama5d2_board.h"
#endif

#ifdef CONFIG_SAMA5D3X
#include "sama5d3_board.h"
#endif

#ifdef CONFIG_SAMA5D4
#include "sama5d4_board.h"
#endif

#ifdef CONFIG_SAMA7G5
#include "sama7g5_board.h"
#endif

/*
 * Functions Prototype
 */
extern void hw_init(void);

/* Some platforms require a preinit very early in the boot process,
   or a postinit after the PMIC voltage selection.
*/

#ifdef CONFIG_SAMA7G5
extern void hw_preinit(void);
extern void hw_postinit(void);
#endif

extern void nandflash_hw_init(void);
extern void nandflash_set_smc_timing(unsigned int mode);

extern void at91_spi0_hw_init(void);

extern void at91_qspi_hw_init(void);

extern void at91_mci0_hw_init(void);
extern void at91_mci1_hw_init(void);
extern void at91_mci2_hw_init(void);

extern void at91_sdhc_hw_init(void);

extern void at91_board_set_dtb_name(char *of_name);

extern void norflash_hw_init(void);

extern char *board_override_cmd_line(void);

/* PM Support */
extern unsigned int at91_twi0_hw_init(void);
extern unsigned int at91_twi1_hw_init(void);
extern unsigned int at91_twi2_hw_init(void);
extern unsigned int at91_twi3_hw_init(void);
extern void at91_board_config_twi_bus(void);

extern unsigned int at91_eth0_hw_init(void);
extern unsigned int at91_eth1_hw_init(void);
extern void at91_disable_mac_clock(void);

extern void at91_disable_smd_clock(void);

extern int at91_board_act8865_set_reg_voltage(void);

#endif /* #ifndef __BOARD_H__ */
