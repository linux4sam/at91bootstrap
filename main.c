// Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "board.h"
#include "usart.h"
#include "slowclk.h"
#include "board_hw_info.h"
#include "tz_utils.h"
#include "pm.h"
#include "act8865.h"
#include "mcp16502.h"
#include "backup.h"
#include "secure.h"
#include "autoconf.h"
#include "optee.h"
#include "sfr_aicredir.h"

#ifdef CONFIG_CACHES
#include "l1cache.h"
#endif

#ifdef CONFIG_MMU
#include "mmu.h"
static unsigned int *tlb = (unsigned int *)MMU_TABLE_BASE_ADDR;
#endif

#ifdef CONFIG_HW_DISPLAY_BANNER
static void display_banner (void)
{
	usart_puts(BANNER);
}
#endif

int main(void)
{
#ifdef CONFIG_LOAD_SW
	struct image_info image;
#endif
	int ret = 0;

	hw_init();

#ifdef CONFIG_OCMS_STATIC
	ocms_init_keys();
	ocms_enable();
#endif

#if defined(CONFIG_SCLK)
#if !defined(CONFIG_SCLK_BYPASS)
	slowclk_enable_osc32();
#endif
#elif defined(CONFIG_SCLK_INTRC)
	slowclk_switch_rc32();
#endif

#ifdef CONFIG_BACKUP_MODE
	ret = backup_mode_resume();
	if (ret) {
		/* Backup+Self-Refresh mode detected... */
#ifdef CONFIG_REDIRECT_ALL_INTS_AIC
		redirect_interrupts_to_nsaic();
#endif
		slowclk_switch_osc32();

		/* ...jump to Linux here */
		return ret;
	}
	usart_puts("Backup mode enabled\n");
#endif

#ifdef CONFIG_HW_DISPLAY_BANNER
	display_banner();
#endif

#ifdef CONFIG_REDIRECT_ALL_INTS_AIC
	redirect_interrupts_to_nsaic();
#endif

#ifdef CONFIG_LOAD_HW_INFO
	load_board_hw_info();
#endif

#ifdef CONFIG_PM
	at91_board_pm();
#endif

#ifdef CONFIG_ACT8865
	act8865_workaround();

	act8945a_suspend_charger();
#endif

#ifdef CONFIG_MCP16502_SET_VOLTAGE
	mcp16502_voltage_select();
#endif

#ifdef CONFIG_SAMA7G5
	hw_postinit();
#endif

#ifdef CONFIG_LOAD_SW
	init_load_image(&image);

#if defined(CONFIG_SECURE)
	image.dest -= sizeof(at91_secure_header_t);
#endif

#ifdef CONFIG_MMU
	mmu_tlb_init(tlb);
	mmu_configure(tlb);
	mmu_enable();
#endif
#ifdef CONFIG_CACHES
	icache_enable();
	dcache_enable();
#endif
	ret = (*load_image)(&image);
#ifdef CONFIG_CACHES
	icache_disable();
	dcache_disable();
#endif
#ifdef CONFIG_MMU
	mmu_disable();
#endif

#if defined(CONFIG_SECURE)
	if (!ret)
		ret = secure_check(image.dest);
	image.dest += sizeof(at91_secure_header_t);
#endif

#endif
	load_image_done(ret);

#ifdef CONFIG_SCLK
#ifdef CONFIG_SCLK_BYPASS
	slowclk_switch_osc32_bypass();
#else
	slowclk_switch_osc32();
#endif
#endif

#if defined(CONFIG_LOAD_OPTEE)
	/* Will never return since we will jump to OP-TEE in secure mode */
	optee_load();
#endif

#if defined(CONFIG_ENTER_NWD)
	switch_normal_world();

	/* point never reached with TZ support */
#endif

#ifdef CONFIG_JUMP_TO_SW
	return JUMP_ADDR;
#else
	return 0;
#endif
}
