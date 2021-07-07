// Copyright (C) 2008 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "spi_flash.h"
#include "qspi_flash.h"

int load_dataflash(struct image_info *image)
{
	int ret = 0;

#ifdef CONFIG_SPI
	ret = spi_flash_loadimage(image);
#endif

#ifdef CONFIG_QSPI
	ret = qspi_loadimage(image);
#endif

	if (ret)
		return -1;

	return 0;
}
