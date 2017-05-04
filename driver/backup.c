/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
#include "backup.h"
#include "debug.h"
#include "hardware.h"
#include "rstc.h"
#include "arch/at91_sfrbu.h"

static struct at91_pm_bu {
	int suspended;
	unsigned long *reserved;
	unsigned long *canary;
	unsigned long resume;
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

	resuming = 0;

	ret = readl(AT91C_BASE_SFRBU + SFRBU_DDRBUMCR);
	if (ret == 0)
		return;

	do {
		ret = readl(AT91C_BASE_SECUMOD + 0x14);
	} while (ret == 0);

	pm_bu = (struct at91_pm_bu *)AT91C_BASE_SECURAM;
	if (!pm_bu->suspended)
		return;

	resuming = 1;
	return;
}

int backup_resume(void)
{
	if (resuming == -1)
		backup_mode();

	return resuming;
}

unsigned long backup_mode_resume(void)
{
	if (!backup_resume())
		return 0;

	writel(0, AT91C_BASE_SFRBU + SFRBU_DDRBUMCR);

	if (*pm_bu->canary != 0xa5a5a5a5) {
		cpu_reset();
		return 0;
	}

	return pm_bu->resume;
}
