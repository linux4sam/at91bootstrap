/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

extern void matrix_write_protect_enable(unsigned int matrix_base);
extern void matrix_write_protect_disable(unsigned int matrix_base);
extern void matrix_configure_slave_security(unsigned int matrix_base,
				unsigned int slave,
				unsigned int srtop_setting,
				unsigned int srsplit_setting,
				unsigned int ssr_setting);
extern int matrix_configure_peri_security(unsigned int *peri_id,
					  unsigned int size);

extern int is_peripheral_secure(unsigned int periph_id);
extern int is_sys_clk_secure(unsigned int sys_mask);
extern int is_pck_clk_secure(unsigned int pck_mask);
extern int is_usb_hs_secure(void);
extern int is_usb_host_secure(void);
extern int is_switching_clock_forbiden(unsigned int periph_id, unsigned int is_on, unsigned int *silent);

extern void matrix_read_slave_security(unsigned int matrix_base,
				       unsigned int nslaves);
extern void matrix_read_peripheral_security(unsigned int matrix_base);

#ifdef CONFIG_SAMA7G5
extern void matrix_configure_default_qos();
#endif

#endif /* #ifndef __MATRIX_H__ */
