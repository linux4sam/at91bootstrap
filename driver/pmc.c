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
#include "hardware.h"
#include "timer.h"
#include "arch/at91_pmc.h"
#include "rstc.h"

static inline void write_pmc(unsigned int offset, const unsigned int value)
{
	writel(value, offset + AT91C_BASE_PMC);
}

static inline unsigned int read_pmc(unsigned int offset)
{
	return readl(offset + AT91C_BASE_PMC);
}

void lowlevel_clock_init()
{
	unsigned long tmp;

#if defined(CONFIG_SAMA5D3X_CMP)
	/*
	 * On the sama5d3x_cmp board, a phy is not in the proper reset state
	 * after power-up, additional reset
	 */
	rstc_external_reset();
#endif

#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(SAMA5D3X) || defined(SAMA5D4)
	/*
	 * Enable the 12MHz oscillator
	 * tST_max = 2ms
	 * Startup Time: 32768 * 2ms / 8 = 8
	 */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCXTST);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_MOSCXTEN;
	tmp |= AT91_CKGR_MOSCXTST_SET(8);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS))
		;

	/* Switch from internal 12MHz RC to the 12MHz oscillator */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCXTBY);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);

	tmp = read_pmc(PMC_MOR);
	tmp |= AT91C_CKGR_MOSCSEL;
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCSELS))
		;

#if !defined(SAMA5D4)
	/* Disable the 12MHz RC oscillator */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCRCEN);
	tmp &= (~AT91C_CKGR_KEY);
	tmp |= AT91C_CKGR_PASSWD;
	write_pmc(PMC_MOR, tmp);
#endif

#else
	/*
	 * Enable the 12MHz oscillator
	 * tST_max = 2ms
	 * Startup Time: 32768 * 2ms / 8 = 8
	 */
	tmp = read_pmc(PMC_MOR);
	tmp &= (~AT91C_CKGR_MOSCXTST);
	tmp |= AT91C_CKGR_MOSCXTEN;
	tmp |= AT91_CKGR_MOSCXTST_SET(8);
	write_pmc(PMC_MOR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MOSCXTS))
		;
#endif

	/* After stablization, switch to Main Oscillator */
	if ((read_pmc(PMC_MCKR) & AT91C_PMC_CSS) == AT91C_PMC_CSS_SLOW_CLK) {
		tmp = read_pmc(PMC_MCKR);
		tmp &= ~AT91C_PMC_CSS;
		tmp |= AT91C_PMC_CSS_MAIN_CLK;
		write_pmc(PMC_MCKR, tmp);

		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
			;

		tmp &= ~AT91C_PMC_PRES;
		tmp |= AT91C_PMC_PRES_CLK;
		write_pmc(PMC_MCKR, tmp);

		while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
			;
	}

	return;
}

void pmc_init_pll(unsigned int pmc_pllicpr)
{
	write_pmc(PMC_PLLICPR, pmc_pllicpr);
}

int pmc_cfg_plla(unsigned int pmc_pllar)
{
	write_pmc((unsigned int)PMC_PLLAR, pmc_pllar);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_LOCKA))
		;

	return 0;
}

int pmc_cfg_mck(unsigned int pmc_mckr)
{
	unsigned int tmp;

	/*
	 * Program the PRES field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(SAMA5D3X) || defined(SAMA5D4)
	tmp &= (~AT91C_PMC_ALT_PRES);
	tmp |= (pmc_mckr & AT91C_PMC_ALT_PRES);
#else
	tmp &= (~AT91C_PMC_PRES);
	tmp |= (pmc_mckr & AT91C_PMC_PRES);
#endif
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

	/*
	 * Program the MDIV field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_MDIV);
	tmp |= (pmc_mckr & AT91C_PMC_MDIV);
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

	/*
	 * Program the PLLADIV2 field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_PLLADIV2);
	tmp |= (pmc_mckr & AT91C_PMC_PLLADIV2);
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

	/*
	 * Program the H32MXDIV field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_H32MXDIV);
	tmp |= (pmc_mckr & AT91C_PMC_H32MXDIV);
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

	/*
	 * Program the CSS field in the PMC_MCKR register,
	 * wait for MCKRDY bit to be set in the PMC_SR register
	 */
	tmp = read_pmc(PMC_MCKR);
	tmp &= (~AT91C_PMC_CSS);
	tmp |= (pmc_mckr & AT91C_PMC_CSS);
	write_pmc(PMC_MCKR, tmp);

	while (!(read_pmc(PMC_SR) & AT91C_PMC_MCKRDY))
		;

	return 0;
}

int pmc_cfg_pck(unsigned char x, unsigned int clk_sel, unsigned int prescaler)
{
	write_pmc(PMC_PCKR + x * 4, clk_sel | prescaler);
	write_pmc(PMC_SCER, 1 << (x + 8));
	while (!(read_pmc(PMC_SR) & (1 << (x + 8)))) ;

	return 0;
}

int pmc_enable_periph_clock(unsigned int periph_id)
{
	unsigned int mask = 0x01 << (periph_id % 32);

	if ((periph_id / 32) == 1)
		write_pmc(PMC_PCER1, mask);
	else if ((periph_id / 32) == 0)
		write_pmc(PMC_PCER, mask);
	else
		return -1;

	return 0;
}

int pmc_disable_periph_clock(unsigned int periph_id)
{
	unsigned int mask = 0x01 << (periph_id % 32);

	if ((periph_id / 32) == 1)
		write_pmc(PMC_PCDR1, mask);
	else if ((periph_id / 32) == 0)
		write_pmc(PMC_PCDR, mask);
	else
		return -1;

	return 0;
}

int pmc_periph_clock_enabled(unsigned int periph_id)
{
	unsigned int mask = 0x01 << (periph_id % 32);
	int enabled = 0;

	if ((periph_id / 32) == 1)
		enabled = !!(read_pmc(PMC_PCSR1) & mask);
	else if ((periph_id / 32) == 0)
		enabled = !!(read_pmc(PMC_PCSR) & mask);

	return enabled;
}

void pmc_enable_system_clock(unsigned int clock_id)
{
	 write_pmc(PMC_SCER, clock_id);
}

void pmc_disable_system_clock(unsigned int clock_id)
{
	 write_pmc(PMC_SCDR, clock_id);
};

void pmc_set_smd_clock_divider(unsigned int divider)
{
	unsigned int tmp = read_pmc(PMC_SMD);

	tmp &= ~AT91C_PMC_SMDDIV;
	tmp |= AT91C_PMC_SMDDIV_(divider);

	write_pmc(PMC_SMD, tmp);
}

#if defined(CONFIG_ENTER_NWD)
unsigned int pmc_read_reg(unsigned int reg_offset)
{
	if (reg_offset <= PMC_OCR)
		return read_pmc(reg_offset);
	else
		return 0xffffffff;
}

void pmc_enable_clock(unsigned int per_id)
{
	unsigned long regval;

	regval = AT91C_PMC_CMD | AT91C_PMC_EN;
	regval |= (per_id & AT91C_PMC_PID);

	/* No need to use Peripheral Divisor value
	 * peripherals are supposed to work @ 90MHz
	 */
	write_pmc(PMC_PCR, regval);
}

void pmc_disable_clock(unsigned int per_id)
{
	unsigned long regval;

	regval = AT91C_PMC_CMD;
	regval |= (per_id & AT91C_PMC_PID);
	write_pmc(PMC_PCR, regval);
}

int pmc_periph_clk(unsigned int periph_id, unsigned int is_on)
{
	if ((periph_id > AT91C_ID_FIQ) && (periph_id < AT91C_ID_COUNTS)) {
		if (is_on)
			pmc_enable_clock(periph_id);
		else
			pmc_disable_clock(periph_id);
		return 0;
	} else {
		return -1;
	}
}

unsigned int sys_mask_to_per_id(unsigned int sys_mask)
{
	switch (sys_mask) {
	case AT91C_PMC_LCDCK:
		return AT91C_ID_LCDC;
	case AT91C_PMC_SMDCK:
		return AT91C_ID_SMD;
	case AT91C_PMC_UHP:
		return AT91C_ID_UHPHS;
	case AT91C_PMC_UDP:
		return AT91C_ID_UDPHS;
	}

	return 0xffffffff;
}

int pmc_sys_clk(unsigned int sys_clock_mask, unsigned int is_on)
{
	if (sys_clock_mask & AVAILABLE_SYS_CLK) {
		if (is_on)
			write_pmc(PMC_SCER, sys_clock_mask);
		else
			write_pmc(PMC_SCDR, sys_clock_mask);
		return 0;
	} else {
		return -1;
	}
}

void pmc_pck_setup(unsigned int reg_offset, unsigned int reg_value)
{
	write_pmc(reg_offset, reg_value);
}

int pmc_uckr_clk(unsigned int is_on)
{
	unsigned int uckr = read_pmc(PMC_UCKR);
	unsigned int sr;

	if (is_on) {
		uckr |= (AT91C_CKGR_UPLLCOUNT_DEFAULT | AT91C_CKGR_UPLLEN_ENABLED);
		sr = AT91C_PMC_LOCKU;
	} else {
		uckr &= ~AT91C_CKGR_UPLLEN_ENABLED;
		sr = 0;
	}

	write_pmc(PMC_UCKR, uckr);

	do {
		udelay(1);
	} while ((read_pmc(PMC_SR) & AT91C_PMC_LOCKU) != sr);

	return 0;
}

unsigned int pmc_usb_setup(void)
{
	unsigned int usbr = AT91C_PMC_USBS_USB_UPLL;

	/* Setup divider by 10 to reach 48 MHz */
	usbr |= ((10 - 1) << 8) & AT91C_PMC_USBDIV;

	write_pmc(PMC_USB, usbr);

	return usbr;
}

void pmc_smd_setup(unsigned int val)
{
	val &= (AT91C_PMC_SMDS | AT91C_PMC_SMDDIV);

	write_pmc(PMC_SMD, val);
}
#endif	/* #if defined(CONFIG_ENTER_NWD) */
