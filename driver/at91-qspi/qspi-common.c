// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "board.h"
#include "pmc.h"
#include "string.h"
#include "arch/at91-qspi/qspi.h"
#include "spi_flash/spi_nor.h"
#include "debug.h"

#include "qspi-common.h"

#ifndef CONFIG_SYS_BASE_QSPI
#error "CONFIG_SYS_BASE_QSPI is not set"
#endif

#ifndef CONFIG_SYS_BASE_QSPI_MEM
#error "CONFIG_SYS_BASE_QSPI_MEM is not set"
#endif

#ifdef CONFIG_DEBUG_VERY_LOUD
static const char *qspi_reg_name(u32 reg)
{
	switch (reg) {
	case QSPI_CR:
		return "CR";
	case QSPI_MR:
		return "MR";
	case QSPI_RDR:
		return "RDR";
	case QSPI_TDR:
		return "TDR";
	case QSPI_SR:
		return "SR";
	case QSPI_IER:
		return "IER";
	case QSPI_IDR:
		return "IDR";
	case QSPI_IMR:
		return "IMR";
	case QSPI_SCR:
		return "SCR";
	case QSPI_IAR:
		return "IAR";
#if defined(CONFIG_SAMA5D2)
	case QSPI_ICR:
		return "ICR";
#endif /* CONFIG_SAMA5D2 */
	case QSPI_IFR:
		return "IFR";
#if defined(CONFIG_SAM9X60) || defined(CONFIG_SAMA7G5)
	case QSPI_WICR:
		return "WICR";
	case QSPI_RICR:
		return "RICR";
#endif /* CONFIG_SAM9X60 || CONFIG_SAMA7G5 */
	case QSPI_SMR:
		return "SMR";
	case QSPI_SKR:
		return "SKR";
#if defined(CONFIG_SAMA7G5)
	case QSPI_ISR:
		return "ISR";
	case QSPI_REFRESH:
		return "REFRESH";
	case QSPI_WRACNT:
		return "WRACNT";
	case QSPI_DLLCFG:
		return "DLLCFG";
	case QSPI_PCALCFG:
		return "PCALCFG";
	case QSPI_PCALBP:
		return "PCALBP";
	case QSPI_TOUT:
		return "TOUT";
#endif /* CONFIG_SAMA7G5 */
	case QSPI_WPMR:
		return "WPMR";
	case QSPI_WPSR:
		return "WPSR";
	default:
		return "UNKNOWN";
	}
}
#endif /* CONFIG_DEBUG_VERY_LOUD */

unsigned int qspi_readl(struct qspi_priv *qspi, u32 reg)
{
	u32 value = readl(qspi->reg_base + reg);
#ifdef CONFIG_DEBUG_VERY_LOUD
	dbg_very_loud("read %x from %s\n", value, qspi_reg_name(reg));
#endif
	return value;
}

void qspi_writel(u32 value, struct qspi_priv *qspi, u32 reg)
{
#ifdef CONFIG_DEBUG_VERY_LOUD
	dbg_very_loud("write %x into %s\n", value, qspi_reg_name(reg));
#endif
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
	qspi.mmap_size = CONFIG_SYS_QSPI_MEM_SIZE;

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
