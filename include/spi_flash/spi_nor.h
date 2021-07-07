/*
 * Copyright (C) 2017 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SPI_NOR_H__
#define __SPI_NOR_H__

#include "spi_flash/spi_flash.h"
#include "spi_flash/sfdp.h"

struct spi_nor_info {
	const char		*name;

	u8			id[SFLASH_MAX_ID_LEN];
	u8			id_len;

	u32			sector_size;
	u16			n_sectors;
	u16			page_size;
	u16			addr_len;
	u16			flags;
#define SNOR_SECT_4K		(0x1UL << 0)
#define SNOR_NO_FR		(0x1UL << 1)
#define SNOR_HAS_FSR		(0x1UL << 2)
#define SNOR_NO_4BAIS		(0x1UL << 3)
#define SNOR_SKIP_SFDP		(0x1UL << 4)
#define SNOR_SECT_4K_ONLY	(0x1UL << 5)
#define SNOR_SST_ULBPR		(0x1UL << 6)

	const struct spi_flash_parameters	*params;
};

extern const struct spi_nor_info spi_nor_ids[];

int spansion_new_quad_enable(struct spi_flash *flash);
int spansion_quad_enable(struct spi_flash *flash);
int macronix_quad_enable(struct spi_flash *flash);
int sr2_bit7_quad_enable(struct spi_flash *flash);
int micron_enable_0_4_4(struct spi_flash *flash, bool enable);

int spi_nor_probe(struct spi_flash *flash,
		  const struct spi_flash_hwcaps *hwcaps);

#endif /* __SPI_NOR_H__ */
