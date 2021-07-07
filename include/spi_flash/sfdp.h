/*
 * Copyright (C) 2017 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SFDP_H__
#define __SFDP_H__

#include "spi_flash/spi_flash.h"

struct spi_flash_read_command {
	u8			num_mode_cycles;
	u8			num_wait_states;
	u8			inst;
	enum spi_flash_protocol	proto;
};

struct spi_flash_pp_command {
	u8			inst;
	enum spi_flash_protocol	proto;
};

enum spi_flash_read_command_index {
	SFLASH_CMD_READ,
	SFLASH_CMD_READ_FAST,

	/* Dual SPI */
	SFLASH_CMD_READ_1_1_2,
	SFLASH_CMD_READ_1_2_2,
	SFLASH_CMD_READ_2_2_2,

	/* Quad SPI */
	SFLASH_CMD_READ_1_1_4,
	SFLASH_CMD_READ_1_4_4,
	SFLASH_CMD_READ_4_4_4,

	SFLASH_CMD_READ_MAX
};

enum spi_flash_pp_command_index {
	SFLASH_CMD_PP,

	/* Quad SPI */
	SFLASH_CMD_PP_1_1_4,
	SFLASH_CMD_PP_1_4_4,
	SFLASH_CMD_PP_4_4_4,

	SFLASH_CMD_PP_MAX
};

struct spi_flash_parameters {
	u32				size;
	u32				page_size;

	struct spi_flash_hwcaps		hwcaps;
	struct spi_flash_read_command	reads[SFLASH_CMD_READ_MAX];
	struct spi_flash_pp_command	page_programs[SFLASH_CMD_PP_MAX];

	int (*quad_enable)(struct spi_flash *flash);
};

static inline void
spi_flash_set_read_settings(struct spi_flash_read_command *read,
			    u8 num_mode_cycles,
			    u8 num_wait_states,
			    u8 inst,
			    enum spi_flash_protocol proto)
{
	read->num_mode_cycles = num_mode_cycles;
	read->num_wait_states = num_wait_states;
	read->inst = inst;
	read->proto = proto;
}

static inline void
spi_flash_set_pp_settings(struct spi_flash_pp_command *pp,
			  u8 inst,
			  enum spi_flash_protocol proto)
{
	pp->inst = inst;
	pp->proto = proto;
}

int spi_flash_parse_sfdp(struct spi_flash *flash,
			 struct spi_flash_parameters *params);

#endif /* __SFDP_H__ */
