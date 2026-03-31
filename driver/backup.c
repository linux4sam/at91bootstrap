// Copyright (C) 2016 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "backup.h"
#include "debug.h"
#include "hardware.h"
#include "rstc.h"
#include "arch/at91_sfrbu.h"
#include "usart.h"

#ifdef CONFIG_FAST_BOOT
#include "fast_boot.h"
#endif

#undef DEBUG_BKP_SR_INIT
#if defined(DEBUG_BKP_SR_INIT)
#define dbg_bkp_sf(fmt_str)	usart_puts("BKP: " fmt_str)
#else
#define dbg_bkp_sf(fmt_str)	do {} while (0)
#endif

#define BACKUP_DDR_PHY_CALIBRATION	(9)

/**
 * struct at91_pm_bu - PM data saved by Linux
 * @suspended: true if returning from backup mode
 * @reserved: reserved
 * @canary: pointer to data saved by Linux for self-refresh checking
 * @resume: physical address with resuming code that AT91Bootstrap should
 * jump to
 * @ddr_phy_calibration: DDR PHY calibration data saved before suspending
 */
static struct at91_pm_bu {
	int suspended;
#define SUS_NONE    0
#define SUS_BACKUP  1
#define SUS_RESTORE 2
	unsigned long reserved;
	unsigned long *canary;
	unsigned long resume;
	unsigned long ddr_phy_calibration[BACKUP_DDR_PHY_CALIBRATION];
	unsigned long mem_map;
	unsigned long max_mapnr;
	unsigned long struct_size;
	unsigned long page_shift;
	unsigned long page_type;
	unsigned long page_off;
	unsigned long order_off;
	unsigned long linux_ver;
} *pm_bu;

/*
 * resuming: static variable to reflect the state of resuming from
 * Backup+Self-Refresh mode.
 *
 * -1: state at AT91Boostrap startup, just after SoC power-up or reset. As such
 *     it also applies when the system comes back from Backup+Self-Refresh mode
 *  0: transient state while the resume process is being evaluated:
 *     - whether the DDR Backup mode is disabled: boot process can continue
 *       normally
 *     - or the DDR Backup mode is programmed but the PM status stored in
 *       backup SRAM is not consistent => error condition: boot process will
 *       continue as if the SoC have just experienced a cold boot
 *  1: state where AT91Bootstrap is resuming from Backup+Self-Refresh mode
 *
 * This variable is modified and checked both in external ram initialization sequence
 * in driver/ddramc.c and while actually starting the next level image in main.c
 * (actually restarting Linux in the case of Backup+Self-Refresh mode).
 * */
static int resuming = -1;

static void backup_mode(void)
{
	int ret;

	dbg_bkp_sf("enter backup_mode resuming = -1\n");
	resuming = SUS_NONE;

	if (sfrbu_ddr_is_powered())
		return;

	do {
		ret = readl(AT91C_BASE_SECUMOD + 0x14);
	} while (ret == 0);

	pm_bu = (struct at91_pm_bu *)AT91C_BASE_SECURAM;
	if (pm_bu->suspended == SUS_NONE)
		return;

	resuming = pm_bu->suspended;
	return;
}

int backup_resume(void)
{
	dbg_bkp_sf("enter backup_resume\n");
	if (resuming == -1)
		backup_mode();

	if ((resuming == SUS_BACKUP) || (resuming == SUS_RESTORE)) {
		dbg_bkp_sf("backup_resume return 1\n");
		return 1;
	}

	return 0;
}

int is_backup(void)
{
	dbg_bkp_sf("enter is_backup\n");
	if (resuming == -1)
		backup_mode();

	if (resuming == SUS_BACKUP) {
		dbg_bkp_sf("is_backup resuming = SUS_BACKUP\n");
		return 1;
	}

	return 0;
}

int is_restore(void)
{
	dbg_bkp_sf("enter is_restore\n");
	if (resuming == -1)
		backup_mode();

	if (resuming == SUS_RESTORE) {
		dbg_bkp_sf("is_restore resuming = SUS_RESTORE\n");
		return 1;
	}

	return 0;
}

unsigned long backup_mode_resume(void)
{
	dbg_loud("BKP: backup_mode_resume, resuming = %d\n", resuming);

	if (!is_backup())
		return 0;

	if (*pm_bu->canary != 0xa5a5a5a5) {
		dbg_info("BKP: Failed to find the canary! Rebooting\n");
		dbg_info("BKP: @%x: %x @%x:%x -> resume @%x\n"
				, (unsigned long)pm_bu
				, (unsigned long)(pm_bu->suspended)
				, (unsigned long)(pm_bu->canary)
				, (unsigned long)(*pm_bu->canary)
				, (unsigned long)(pm_bu->resume)
				);
#if defined(DEBUG_BKP_SR_INIT)
		dbg_hexdump((unsigned char *)pm_bu, 16, DUMP_WIDTH_BIT_32);
		while (1) {};
#endif
		cpu_reset();
		return 0;
	}

	return pm_bu->resume;
}

#ifdef CONFIG_PUBL
void backup_get_calibration_data(unsigned int *data, unsigned int len)
{
	int i;

	for (i = 0; i < len && i < BACKUP_DDR_PHY_CALIBRATION; i++)
		data[i] = pm_bu->ddr_phy_calibration[i];
}
#endif

#ifdef CONFIG_FAST_BOOT
void backup_fast_config(struct fast_config *conf)
{
	if ((resuming == SUS_BACKUP) ||
	    (resuming == SUS_RESTORE)) {
		conf->canary = (unsigned int)pm_bu->canary;
		conf->resume = pm_bu->resume;
	}

	if (resuming == SUS_RESTORE) {
		conf->mem_map = pm_bu->mem_map;
		conf->max_mapnr = pm_bu->max_mapnr;
		conf->struct_size = pm_bu->struct_size;
		conf->page_shift = pm_bu->page_shift;
		conf->page_type = pm_bu->page_type;
		conf->page_off = pm_bu->page_off;
		conf->order_off = pm_bu->order_off;
		conf->linux_ver = pm_bu->linux_ver;
	}
}
#endif
