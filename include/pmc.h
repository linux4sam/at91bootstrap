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
#ifndef __PMC_H__
#define __PMC_H__

extern void pmc_init_pll(unsigned int pmc_pllicpr);
extern int pmc_cfg_plla(unsigned int pmc_pllar);
extern int pmc_cfg_mck(unsigned int pmc_mckr);
extern int pmc_cfg_pck(unsigned char x,
			unsigned int clk_sel,
			unsigned int prescaler);

extern int pmc_enable_periph_clock(unsigned int periph_id);
extern int pmc_disable_periph_clock(unsigned int periph_id);
extern int pmc_periph_clock_enabled(unsigned int periph_id);
extern void pmc_enable_system_clock(unsigned int clock_id);
extern void pmc_disable_system_clock(unsigned int clock_id);
extern void pmc_set_smd_clock_divider(unsigned int divider);

extern unsigned int pmc_read_reg(unsigned int reg_offset);
extern int pmc_periph_clk(unsigned int periph_id, unsigned int is_on);
extern unsigned int sys_mask_to_per_id(unsigned int sys_mask);
extern int pmc_sys_clk(unsigned int sys_clock_mask, unsigned int is_on);
extern int pmc_uckr_clk(unsigned int is_on);
extern unsigned int pmc_usb_setup(void);
extern void pmc_smd_setup(unsigned int val);
extern void pmc_pck_setup(unsigned int reg_offset, unsigned int reg_value);

#endif	/* #ifndef __PMC_H__ */
