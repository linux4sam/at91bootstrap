// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "hardware.h"
#include "board.h"
#include "string.h"
#include "debug.h"
#include "fdt.h"

#include "debug.h"

#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)

static int update_image_length(unsigned int offset,
			       unsigned char *dest,
			       unsigned char flag)
{
	unsigned int length = 512;
	int ret;

	dbg_info("FLASH: update image length from image\n");

	memcpy(dest, (const char *)offset, length);

	if (flag == KERNEL_IMAGE)
		return kernel_size(dest);
#ifdef CONFIG_OF_LIBFDT
	else {
		ret = check_dt_blob_valid((void *)dest);
		if (!ret)
			return of_get_dt_total_size((void *)dest);
	}
#endif
	return -1;
}
#endif

int load_norflash(struct image_info *image)
{
	int length = 0;

	norflash_hw_init();

#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
	length = update_image_length(image->offset, image->dest, KERNEL_IMAGE);
	if (length == -1)
		return -1;

	image->length = length;
#endif

	dbg_info("FLASH: copy %x bytes from %x to %x\n",
		 image->length, image->offset, image->dest);

	memcpy(image->dest, (const char *)image->offset, image->length);

#ifdef CONFIG_OF_LIBFDT
	length = update_image_length(image->of_offset,
				     image->of_dest, DT_BLOB);
	if (length == -1)
		return -1;

	image->of_length = length;

	dbg_info("FLASH: dt blob: Copy %x bytes from %x to %x\n",
		image->of_length, image->of_offset, image->of_dest);

	memcpy(image->of_dest,
	       (const char *)image->of_offset, image->of_length);
#endif
	return 0;
}
