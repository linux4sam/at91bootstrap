# Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
#
# SPDX-License-Identifier: MIT

# Memory support

ifeq ($(CONFIG_PUBL),y)
CPPFLAGS += -DCONFIG_PUBL
endif

ifeq ($(CONFIG_MEM_CLOCK_533), y)
CPPFLAGS += -DCONFIG_MEM_CLOCK=533
endif

ifeq ($(CONFIG_MEM_CLOCK_400), y)
CPPFLAGS += -DCONFIG_MEM_CLOCK=400
endif

ifeq ($(CONFIG_DDR_EXT_TEMP_RANGE), y)
CPPFLAGS += -DCONFIG_DDR_EXT_TEMP_RANGE
endif

ifeq ($(CONFIG_DDR_SET_BY_DEVICE),y)
ifeq ($(CONFIG_DDR_MT41K128M16_D2),y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR_4_GBIT
endif
ifeq ($(CONFIG_DDR_MT41K128M16),y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR_2_GBIT
endif
ifeq ($(CONFIG_DDR_W632GU6NG),y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR_2_GBIT
endif
ifeq ($(CONFIG_DDR_W632GU6MB),y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR_4_GBIT
endif
ifeq ($(CONFIG_DDR_W972GG6KB_D2),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_4_GBIT
endif
ifeq ($(CONFIG_DDR_W972GG6KB_9X60),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_2_GBIT
endif
ifeq ($(CONFIG_DDR_W971GG6SB_D2),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_1_GBIT
endif
ifeq ($(CONFIG_DDR_W9751G6KB),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_512_MBIT
endif
ifeq ($(CONFIG_DDR_W971GG6SB),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_1_GBIT
endif
ifeq ($(CONFIG_DDR_W9712G6KB25I),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_128_MBIT
endif
ifeq ($(CONFIG_DDR_AD210032F),y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_DDR_1_GBIT
endif
ifeq ($(CONFIG_DDR_AD220032D),y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_DDR_2_GBIT
endif
ifeq ($(CONFIG_DDR_AS4C128M32MD2A),y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_DDR_4_GBIT
endif
ifeq ($(CONFIG_DDR_MT47H128M16),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_4_GBIT
endif
ifeq ($(CONFIG_DDR_EDB5432BEBH_1DAAT_F_D),y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_LPDDR2_S4 -DCONFIG_DDR_SPEED_1066 -DCONFIG_DDR_512_MBIT
endif
ifeq ($(CONFIG_DDR_MT47H64M16),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_2_GBIT
endif
ifeq ($(CONFIG_DDR_MT47H128M8),y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR_4_GBIT
endif
ifeq ($(CONFIG_DDR_MT47H128M16RT_25E_C), y)
CPPFLAGS += -DCONFIG_DDR2 -DCONFIG_DDR2_SPEED_BIN_800D -DCONFIG_DDR_2_GBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_MT41K256M16TW_107), y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1866K -DCONFIG_DDR_4_GBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_MT41K128M16JT_125),y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1600K -DCONFIG_DDR_2_GBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_AS4C256M16D3LC_12BCNTR), y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1600K -DCONFIG_DDR_4_GBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_AS4C512M16D3LA_10BIN), y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1600K -DCONFIG_DDR_8_GBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_W632GU6NB12I), y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1600K -DCONFIG_DDR_2_GBIT
endif
ifeq ($(CONFIG_DDR_MT41K512M16HA_125), y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1600K -DCONFIG_DDR_8_GBIT
endif
ifeq ($(CONFIG_DDR_W631GU6NB), y)
CPPFLAGS += -DCONFIG_DDR3 -DCONFIG_DDR3_SPEED_BIN_1600K -DCONFIG_DDR_1_GBIT
endif
ifeq ($(CONFIG_DDR_IS43LD16128B_25BLI), y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_LPDDR2_S4 -DCONFIG_LPDDR2_SPEED_800 -DCONFIG_DDR_2_GBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_MT52L256M32D1PF_107), y)
CPPFLAGS += -DCONFIG_LPDDR3 -DCONFIG_LPDDR3_SPEED_1333 -DCONFIG_DDR_8_GBIT -DCONFIG_DBW_32
endif
ifeq ($(CONFIG_DDR_EDB5432BEBH_1DAAT_F_D),y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_LPDDR2_S4 -DCONFIG_LPDDR2_SPEED_800 -DCONFIG_DDR_512_MBIT -DCONFIG_DBW_16
endif
ifeq ($(CONFIG_DDR_W97AH6NBVA1K), y)
CPPFLAGS += -DCONFIG_LPDDR2 -DCONFIG_LPDDR2_S4 -DCONFIG_LPDDR2_SPEED_1066 -DCONFIG_DDR_1_GBIT -DCONFIG_DBW_16
endif
endif

ifeq ($(CONFIG_REF_WIN_32),y)
CPPFLAGS += -DCONFIG_REF_WIN=32
endif
ifeq ($(CONFIG_REF_WIN_64),y)
CPPFLAGS += -DCONFIG_REF_WIN=64
endif
ifeq ($(CONFIG_REF_2048),y)
CPPFLAGS += -DCONFIG_REF_CYCLE=2048
endif
ifeq ($(CONFIG_REF_4096),y)
CPPFLAGS += -DCONFIG_REF_CYCLE=4096
endif
ifeq ($(CONFIG_REF_8192),y)
CPPFLAGS += -DCONFIG_REF_CYCLE=8192
endif

ifeq ($(CONFIG_DDR_SET_BY_JEDEC),y)
ifeq ($(CONFIG_REF_WIN_32),y)
CPPFLAGS += -DCONFIG_REF_WIN=32
endif
ifeq ($(CONFIG_REF_WIN_64),y)
CPPFLAGS += -DCONFIG_REF_WIN=64
endif

ifeq ($(CONFIG_REF_2048),y)
CPPFLAGS += -DCONFIG_REF_CYCLE=2048
endif
ifeq ($(CONFIG_REF_4096),y)
CPPFLAGS += -DCONFIG_REF_CYCLE=4096
endif
ifeq ($(CONFIG_REF_8192),y)
CPPFLAGS += -DCONFIG_REF_CYCLE=8192
endif
endif

# Dataflash support
ifeq ($(MEMORY),dataflash)
CPPFLAGS += -DAT91C_SPI_CLK=$(SPI_CLK)
CPPFLAGS += -DAT91C_SPI_PCS_DATAFLASH=$(SPI_BOOT) 
endif

ifeq ($(MEMORY),dataflashcard)
CPPFLAGS += -DAT91C_SPI_CLK=$(SPI_CLK)
CPPFLAGS += -DAT91C_SPI_PCS_DATAFLASH=$(SPI_BOOT) 
endif

# NAND flash support


ifeq ($(CONFIG_PMC_MCK_CLK),y)
CPPFLAGS += -DCONFIG_PMC_MCK_CLK
endif

ifeq ($(CONFIG_PMC_MCK_CLK_SAMA7G5),y)
CPPFLAGS += -DCONFIG_PMC_MCK_CLK
endif

ifeq ($(CONFIG_PMECC_CORRECT_BITS_2), y)
CPPFLAGS += -DPMECC_ERROR_CORR_BITS=2
endif

ifeq ($(CONFIG_PMECC_CORRECT_BITS_4), y)
CPPFLAGS += -DPMECC_ERROR_CORR_BITS=4
endif

ifeq ($(CONFIG_PMECC_CORRECT_BITS_8), y)
CPPFLAGS += -DPMECC_ERROR_CORR_BITS=8
endif

ifeq ($(CONFIG_PMECC_CORRECT_BITS_12), y)
CPPFLAGS += -DPMECC_ERROR_CORR_BITS=12
endif

ifeq ($(CONFIG_PMECC_CORRECT_BITS_24), y)
CPPFLAGS += -DPMECC_ERROR_CORR_BITS=24
endif

ifeq ($(CONFIG_PMECC_SECTOR_SIZE_512), y)
CPPFLAGS += -DPMECC_SECTOR_SIZE=512
endif

ifeq ($(CONFIG_PMECC_SECTOR_SIZE_1024), y)
CPPFLAGS += -DPMECC_SECTOR_SIZE=1024
endif

# Debug related stuff
ifeq ($(CONFIG_DEBUG_INFO),y)
CPPFLAGS += -DBOOTSTRAP_DEBUG_LEVEL=DEBUG_INFO
endif

ifeq ($(CONFIG_DEBUG_LOUD),y)
CPPFLAGS += -DBOOTSTRAP_DEBUG_LEVEL=DEBUG_LOUD
endif

ifeq ($(CONFIG_DEBUG_VERY_LOUD),y)
CPPFLAGS += -DBOOTSTRAP_DEBUG_LEVEL=DEBUG_VERY_LOUD
endif

ifeq ($(CONFIG_TZC400), y)
CPPFLAGS += -DCONFIG_TZC400
endif

ifeq ($(CONFIG_TZC400_SIMPLE_PROFILE), y)
CPPFLAGS += -DCONFIG_TZC400_SIMPLE_PROFILE
endif

ifeq ($(CONFIG_TZC400_SPECULATIVE_LOAD), y)
CPPFLAGS += -DCONFIG_TZC400_SPECULATIVE_LOAD
endif

ifeq ($(CONFIG_WDTS), y)
CPPFLAGS += -DCONFIG_WDTS
endif
