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

#include "ff.h"

#include "debug.h"

#define CHUNK_SIZE	0x40000

static int sdcard_loadimage(char *filename, BYTE *dest)
{
	FIL 	file;
	UINT	byte_to_read = CHUNK_SIZE;
	UINT	byte_read;
	FRESULT	fret;
	int	ret;

	fret = f_open(&file, filename, FA_OPEN_EXISTING | FA_READ);
	if (fret != FR_OK) {
		dbg_log(1, "*** FATFS: f_open, filename: [%s]: error\n\r", filename);
		ret = -1;
		goto open_fail;
	}

	do {
		byte_read = 0;
		fret = f_read(&file, (void *)(dest), byte_to_read, &byte_read);
		dest += byte_to_read;
	} while (byte_read >= byte_to_read);

	if (fret != FR_OK) {
		dbg_log(1, "*** FATFS: f_read: error\n\r");
		 ret = -1;
		goto read_fail;
	}
	ret = 0;

read_fail:
	fret = f_close(&file);

open_fail:
	return ret;

}

int load_sdcard(struct image_info *image)
{
	FATFS	fs;
	FRESULT	fret;
	int	ret;

	at91_mci0_hw_init();

	fret = f_mount(0, &fs);
	if (fret != FR_OK) {
		dbg_log(1, "*** FATFS: f_mount error **\n\r");
		return -1;
	}

	dbg_log(1, "SD/MMC: Image: Read file %s to %d\n\r",
					image->filename, image->dest);

	ret = sdcard_loadimage(image->filename, image->dest);
	if (ret)
		return ret;

	if (image->of) {
		dbg_log(1, "SD/MMC: dt blob: Read file %s to %d\n\r",
				image->of_filename, image->of_dest);

		ret = sdcard_loadimage(image->of_filename, image->of_dest);
		if (ret)
			return ret;
	}

	return 0;
}
