// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "board.h"
#include "pmc.h"
#include "string.h"
#include "spi_flash/spi_nor.h"
#include "debug.h"

#include "qspi-common.h"

#ifndef CONFIG_SYS_BASE_QSPI
#error "CONFIG_SYS_BASE_QSPI is not set"
#endif

#ifndef CONFIG_SYS_BASE_QSPI_MEM
#error "CONFIG_SYS_BASE_QSPI_MEM is not set"
#endif

unsigned int qspi_readl(struct qspi_priv *qspi, u32 reg)
{
	return readl(qspi->reg_base + reg);
}

void qspi_writel(struct qspi_priv *qspi, u32 reg, u32 value)
{
	writel(value, qspi->reg_base + reg);
}

int qspi_loadimage(struct image_info *image)
{
	const struct spi_flash_hwcaps hwcaps = {
		.mask = (SFLASH_HWCAPS_READ_MASK |
			 SFLASH_HWCAPS_PP_MASK),
	};
	struct spi_flash flash;
	struct qspi_priv qspi;
	int ret;

	memset(&qspi, 0, sizeof(qspi));
	qspi.reg_base = CONFIG_SYS_BASE_QSPI;
	qspi.mem = (void *)CONFIG_SYS_BASE_QSPI_MEM;

	memset(&flash, 0, sizeof(flash));
	flash.ops = &qspi_ops;
	spi_flash_set_priv(&flash, &qspi);

	/* Init the SPI controller. */
	ret = spi_flash_init(&flash);
	if (ret) {
		dbg_info("SF: Fail to initialize spi\n");
		return -1;
	}

	/* Probe the SPI flash memory. */
	ret = spi_nor_probe(&flash, &hwcaps);
	if (ret) {
		dbg_info("SF: Fail to probe SPI flash\n");
		spi_flash_cleanup(&flash);
		return -1;
	}

	return spi_flash_loadimage(&flash, image);
}

int qspi_xip(struct spi_flash *flash, void **mem)
{
	struct qspi_priv *qspi = spi_flash_get_priv(flash);
	int ret;

	if (flash->enable_0_4_4) {
		ret = flash->enable_0_4_4(flash, true);
		if (ret)
			return ret;
	}

	*mem = qspi->mem;
	return spi_flash_read(flash, 0, 1, NULL);
}
