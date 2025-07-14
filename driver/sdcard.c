// Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "autoconf.h"
#include "common.h"
#include "hardware.h"
#include "board.h"

#include "string.h"

#include "ff.h"

#include "debug.h"

#ifdef CONFIG_FAST_BOOT
#include "fast_boot.h"
#include "media.h"
#endif

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
		dbg_info("*** FATFS: f_open, filename: [%s]: error\n", filename);
		ret = -1;
		goto open_fail;
	}

	do {
		byte_read = 0;
		fret = f_read(&file, (void *)(dest), byte_to_read, &byte_read);
		dest += byte_to_read;
	} while (byte_read >= byte_to_read);

	if (fret != FR_OK) {
		dbg_info("*** FATFS: f_read: error\n");
		 ret = -1;
		goto read_fail;
	}
	ret = 0;

read_fail:
	fret = f_close(&file);

open_fail:
	return ret;

}

#ifdef CONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE
static int sdcard_read_cmd(char *cmdline_file, char *cmdline_args)
{
	FIL 	file;
	UINT	byte_to_read = CMDLINE_BUF_LEN;
        UINT    byte_read;
	FRESULT	fret;
        int 	ret;

	fret = f_open(&file, cmdline_file, FA_OPEN_EXISTING | FA_READ);
	if (fret != FR_OK) {
		dbg_info("*** FATFS: f_open, filename: [%s]: error %d\n",
			  cmdline_file, fret);
                ret = -1;
		goto open_fail;
	}

	do {
		byte_read = 0;
		fret = f_read(&file, (char *)(cmdline_args), byte_to_read,
                                                                    &byte_read);
	} while (0);

        dbg_info("SD/MMC: kernel arg string: %s\n", cmdline_args);

	if (fret != FR_OK) {
		dbg_info("*** FATFS: cmdline f_read: error\n");
		ret = -1;
		goto read_fail;
	}
        
        ret = 0;

read_fail:
	fret = f_close(&file);

open_fail:
	return ret;

}
#endif

int load_sdcard(struct image_info *image)
{
	FATFS	fs;
	FRESULT	fret;
	int	ret;
	static bool initialized = false;

	if (!initialized) {
#ifdef CONFIG_AT91_MCI
#if defined(CONFIG_AT91_MCI0)
		at91_mci0_hw_init();
#elif defined(CONFIG_AT91_MCI1)
		at91_mci1_hw_init();
#elif defined(CONFIG_AT91_MCI2)
		at91_mci2_hw_init();
#endif
#endif

#ifdef CONFIG_SDHC
		at91_sdhc_hw_init();
#endif
		initialized = true;
	}
#ifdef CONFIG_FAST_BOOT
	if (sdcard_initialize()) {
		dbg_info("Sdcard initialization failed!\n");
		return 0;
	}
	if (sdcard_fast_boot(image))
		return 0;
#endif

	/* mount fs */
	fret = f_mount(0, &fs);
	if (fret != FR_OK) {
		dbg_info("*** FATFS: f_mount mount error **\n");
		return -1;
	}

	dbg_info("SD/MMC: Image: Read file %s to %x\n",
					image->filename, image->dest);

	ret = sdcard_loadimage(image->filename, image->dest);
	if (ret) {
		(void)f_mount(0, NULL);
		return ret;
	}

#ifdef CONFIG_OF_LIBFDT
	if (image->of_dest) {
		at91_board_set_dtb_name(image->of_filename);

		if (strcmp(CONFIG_OF_OVERRIDE_DTB_NAME, "")) {
			strcpy(image->of_filename, CONFIG_OF_OVERRIDE_DTB_NAME);
		}

		dbg_info("SD/MMC: dt blob: Read file %s to %x\n",
				image->of_filename, image->of_dest);

		ret = sdcard_loadimage(image->of_filename, image->of_dest);
		if (ret) {
			(void)f_mount(0, NULL);
			return ret;
		}
	}

#endif

#ifdef CONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE
	if (image->cmdline_args) {
		dbg_info("SD/MMC: kernel arg string: Read file %s\n",
				image->cmdline_file);

		ret = sdcard_read_cmd(image->cmdline_file, image->cmdline_args);
		if (ret) {
			(void)f_mount(0, NULL);
			return ret;
		}
	}

#endif

	/* umount fs */
	fret = f_mount(0, NULL);
	if (fret != FR_OK) {
		dbg_info("*** FATFS: f_mount umount error **\n");
		return -1;
	}

	return 0;
}
