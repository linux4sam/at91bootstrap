/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
 * ----------------------------------------------------------------------------
 * File Name           : main.c
 * Object              :
 * Creation            : ODi Apr 19th 2006
 *-----------------------------------------------------------------------------
 */
#include "hardware.h"
#include "board.h"
#include "debug.h"
#include "dataflash.h"
#include "nandflash.h"
#include "flash.h"

#ifdef CONFIG_USER_HW_INIT
void user_hw_init(void);
#endif

extern unsigned int load_SDCard(void *dst);

extern void LoadLinux();

const char version_string[] =
	AT91BOOTSTRAP_VERSION" ( "__DATE__" - "__TIME__" )";

static int display_banner (void)
{
	dbg_log(1, "\n\nAT91Bootstrap %s\n\n\r", version_string);
	return 0;
}

int main(void)
{
#ifdef CONFIG_HW_INIT
	hw_init();
#endif

#ifdef CONFIG_USER_HW_INIT
	user_hw_init();
#endif

#if defined(CONFIG_AT91SAM9X5EK)
	extern void load_1wire_info();
	load_1wire_info();
#endif
	display_banner();

	dbg_log(1, "Downloading image...\n\r");

#if defined(CONFIG_LOAD_LINUX)
	LoadLinux();
#else
/* Booting stand-alone application, e.g. U-Boot */
#if defined (CONFIG_DATAFLASH)
	load_df(AT91C_SPI_PCS_DATAFLASH, IMG_ADDRESS, IMG_SIZE, JUMP_ADDR);
#elif defined(CONFIG_NANDFLASH)
	load_nandflash((unsigned int)IMG_ADDRESS, (unsigned int)IMG_SIZE, (unsigned char *)JUMP_ADDR);
#elif defined(CONFIG_SDCARD)
	load_SDCard((void *)JUMP_ADDR);
#else
#error "No booting media specified!"
#endif
#endif

	dbg_log(1, "Done!\n\r");

	return JUMP_ADDR;
}
