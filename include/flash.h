/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __NORFLASH_H__
#define __NORFLASH_H__

#define AT91_NORFLASH_BASE	AT91C_EBI_CS0

/* SMC Chip select 0 timings */
#define AT91C_FLASH_NWE_SETUP           (4 << 0)
#define AT91C_FLASH_NCS_WR_SETUP        (2 << 8)
#define AT91C_FLASH_NRD_SETUP           (4 << 16)
#define AT91C_FLASH_NCS_RD_SETUP        (2 << 24)

#define AT91C_FLASH_NWE_PULSE           (8 << 0)
#define AT91C_FLASH_NCS_WR_PULSE        (10 << 8)
#define AT91C_FLASH_NRD_PULSE           (8 << 16)
#define AT91C_FLASH_NCS_RD_PULSE        (10 << 24)

#define AT91C_FLASH_NWE_CYCLE           (16 << 0)
#define AT91C_FLASH_NRD_CYCLE           (16 << 16)

int load_norflash(struct image_info *image);

#endif	/* #ifndef __NORFLASH_H__ */
