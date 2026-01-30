// Copyright (C) 2017 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "spi_flash/spi_nor.h"

#define ID5(_jedec_id, _ext_id)			\
	.id = {					\
		((_jedec_id) >> 16) & 0xff,	\
		((_jedec_id) >>  8) & 0xff,	\
		((_jedec_id) >>  0) & 0xff,	\
		((_ext_id) >> 8) & 0xff,	\
		((_ext_id) >> 0) & 0xff,	\
	},					\
	.id_len = ((_ext_id) ? 5 : 3)

#define SST26(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 4096U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K_ONLY | SNOR_SST_ULBPR

#define N25Q(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_HAS_FSR | SNOR_SECT_4K | SNOR_NO_4BAIS

#define MT25Q(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),			\
	.sector_size = 65536U,			\
	.n_sectors = (_n_sectors),		\
	.page_size = 256,			\
	.flags = SNOR_SECT_4K

#define MX25(_name, _jedec_id, _n_sectors)      \
        .name = _name,                          \
        ID5(_jedec_id, 0),                      \
        .sector_size = 65536U,                  \
        .n_sectors = (_n_sectors),              \
        .page_size = 256,                       \
        .flags = SNOR_SECT_4K

#define MX66(_name, _jedec_id, _n_sectors)      \
	.name = _name,                          \
	ID5(_jedec_id, 0),                      \
	.sector_size = 65536U,                  \
	.n_sectors = (_n_sectors),              \
	.page_size = 256,                       \
	.flags = SNOR_SECT_4K | SNOR_SKIP_SFDP

struct spi_flash_parameters mx66lm1g45g_params = {
	0x1000000,
	256,
	{
		SFLASH_HWCAPS_READ | SFLASH_HWCAPS_READ_FAST | SFLASH_HWCAPS_PP
	},
	{
		{ 0, 0, SFLASH_INST_READ, SFLASH_PROTO_1_1_1},
#ifdef CONFIG_QSPI_OCTAL_IO
#ifdef CONFIG_QSPI_DTR_ENABLE
		{ 0, 20, SFLASH_INST_FAST_READ_8D_8D_8D, SFLASH_PROTO_8D_8D_8D},
#else
		{ 0, 20, SFLASH_INST_FAST_READ_8_8_8, SFLASH_PROTO_8_8_8},
#endif
#else
		{ 0, 0, SFLASH_INST_READ, SFLASH_PROTO_1_1_1},
#endif
	},
	{
#ifdef CONFIG_QSPI_OCTAL_IO
#ifdef CONFIG_QSPI_DTR_ENABLE
		{ 0x12, SFLASH_PROTO_8D_8D_8D },
#else
		{ 0x12, SFLASH_PROTO_8_8_8 },
#endif
#else
		{ SFLASH_INST_PAGE_PROGRAM, SFLASH_PROTO_1_1_1},
#endif
	},
};

#define W25Q(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),                      \
	.sector_size = 65536U,                  \
	.n_sectors = (_n_sectors),              \
	.page_size = 256,                       \
	.flags = SNOR_SECT_4K

#define GD25_SKIP_SFDP(_name, _jedec_id, _n_sectors)	\
	.name = _name,				\
	ID5(_jedec_id, 0),                      \
	.sector_size = 65536U,                  \
	.n_sectors = (_n_sectors),              \
	.page_size = 256,                       \
	.flags = SNOR_SECT_4K | SNOR_SKIP_SFDP

struct spi_flash_parameters gd25f128f_params = {
	0x1000000,
	256,
	{
		SFLASH_HWCAPS_READ | SFLASH_HWCAPS_READ_FAST | SFLASH_HWCAPS_PP
	},
	{
		{ 0, 0, SFLASH_INST_READ, SFLASH_PROTO_1_1_1},
#ifdef CONFIG_QSPI_DTR_ENABLE
		{ 0, 8, SFLASH_INST_FAST_READ_1_4D_4D, SFLASH_PROTO_1_4D_4D},
#else
		{ 0, 6, SFLASH_INST_FAST_READ_1_4_4, SFLASH_PROTO_1_4_4},
#endif
	},
	{
		{ SFLASH_INST_PAGE_PROGRAM, SFLASH_PROTO_1_1_1 },
	},
};

const struct spi_nor_info spi_nor_ids[] = {
	/* Macronix */
	{ MX25("mx25l25635f", 0xc22019,  512), },
	{ MX66("mx66lm1g45g", 0xc2853b, 2048), &mx66lm1g45g_params},

	/* Micron */
	{ N25Q("n25q032ax1", 0x20bb16,   64), },
	{ N25Q("n25q032ax3", 0x20ba16,   64), },
	{ N25Q("n25q064ax1", 0x20bb17,  128), },
	{ N25Q("n25q064ax3", 0x20ba17,  128), },
	{ N25Q("n25q128ax1", 0x20bb18,  256), },
	{ N25Q("n25q128ax3", 0x20ba18,  256), },
	{ N25Q("n25q256ax1", 0x20bb19,  512), },
	{ N25Q("n25q256ax3", 0x20ba19,  512), },
	{ N25Q("n25q512ax1", 0x20bb20, 1024), },
	{ N25Q("n25q512ax3", 0x20ba20, 1024), },
	{ MT25Q("n25q00ax1", 0x20bb21, 2048), },
	{ MT25Q("n25q00ax3", 0x20ba21, 2048), },

	/* SST */
	{ SST26("sst26vf016b", 0xbf2641,  512), },
	{ SST26("sst26vf032b", 0xbf2642, 1024), },
	{ SST26("sst26vf064b", 0xbf2643, 2048), },
	{ SST26("sst26wf040b", 0xbf2654,  128), },
	{ SST26("sst26wf080b", 0xbf2658,  256), },

	{ W25Q("w25q256", 0xef4019, 512), },

	{ GD25_SKIP_SFDP("gd25f128f", 0xc84318, 256), &gd25f128f_params},

	{}	/* Sentinel */
};
