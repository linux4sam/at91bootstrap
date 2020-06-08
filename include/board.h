/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef CONFIG_SAM9X60
#include "sam9x60_board.h"
#endif

#ifdef CONFIG_SAMA5D2
#include "sama5d2_board.h"
#endif

/*
 * Functions Prototype
 */
extern void hw_init(void);

extern void nandflash_hw_init(void);

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
