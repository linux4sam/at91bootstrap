/*
 * Interface to SPI flash
 *
 * Copyright (C) 2008 Atmel Corporation
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_

#include "spi.h"

struct spi_flash_params {
	unsigned char	idcode1;
	/* Log2 of page size in power-of-two mode */
	unsigned char	l2_page_size;
	unsigned char	pages_per_block;
	unsigned char	blocks_per_sector;
	unsigned char	nr_sectors;
	const char	*name;
};

struct spi_flash {
	struct spi_slave *spi;
	struct spi_flash_params *params;
	unsigned int	size;
	unsigned int 	sector_size;

	int		(*read)(struct spi_flash *flash, 
				unsigned int offset,
				unsigned int  len, 
				void *buf);
};

struct spi_flash *spi_flash_probe(unsigned int bus, 
				unsigned int cs, 
				unsigned int max_hz, 
				unsigned int spi_mode);


static inline int spi_flash_read(struct spi_flash *flash, 
				unsigned int offset,
				unsigned int len, 
				void *buf)
{
	return flash->read(flash, offset, len, buf);
}

#endif /* #ifndef _SPI_FLASH_H_  */
