/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
 */
#include "common.h"
#include "hardware.h"
#include "board.h"
#include "debug.h"
#include "slowclk.h"
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"
#include "flash.h"

extern int load_kernel(struct image_info *img_info);

typedef int (*load_function)(struct image_info *img_info);

static load_function load_image;

static int init_loadfunction(void)
{
#if defined(CONFIG_LOAD_LINUX)
	load_image = &load_kernel;
#else
#if defined (CONFIG_DATAFLASH)
	load_image = &load_dataflash;
#elif defined(CONFIG_NANDFLASH)
	load_image = &load_nandflash;
#elif defined(CONFIG_SDCARD)
	load_image = &load_sdcard;
#else
#error "No booting media specified!"
#endif
#endif
	return 0;
}

static void display_banner (void)
{
	dbg_log(1, "\n\nAT91Bootstrap %s\n\n\r",
			AT91BOOTSTRAP_VERSION" ( "COMPILE_TIME" )");
}

int main(void)
{
	struct image_info image_info;
	int ret;

	image_info.dest = (unsigned char *)JUMP_ADDR;
#if defined (CONFIG_DATAFLASH) || defined(CONFIG_NANDFLASH)
	image_info.offset = IMG_ADDRESS;
	image_info.length = IMG_SIZE;
#endif
#if defined(CONFIG_SDCARD)
	image_info.filename = OS_IMAGE_NAME;
#endif

#ifdef CONFIG_HW_INIT
	hw_init();
#endif

	display_banner();

	init_loadfunction();

	dbg_log(1, "Downloading image...\n\r");

	ret = (*load_image)(&image_info);
	if (ret == 0){
		dbg_log(1, "Done!\n\r");
	}
	if (ret == -1) {
		dbg_log(1, "Failed to load image\n\r");
		while(1);
	}
	if (ret == -2) {
		dbg_log(1, "Success to recovery\n\r");
		while (1);
	}

#ifdef CONFIG_SCLK
	slowclk_switch_osc32();
#endif

	return JUMP_ADDR;
}
