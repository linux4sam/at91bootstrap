// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "debug.h"
#include "board.h"
#include "flexcom.h"

#ifndef AT91C_NUM_FLEXCOM
#error "Must define AT91C_NUM_FLEXCOM by board definitions"
#endif

struct at91_flexcom *flexcoms;

/* Must be called by board init routine
 * Board must enable the clocks for all flexcoms and configure the PIO
 * accordingly.
 */
void flexcoms_init(struct at91_flexcom *board_specific_flexcoms)
{
	flexcoms = board_specific_flexcoms;
}

unsigned int flexcom_get_base(unsigned int flexcom_num)
{
	if (flexcom_num >= AT91C_NUM_FLEXCOM)
		return 0;

	return flexcoms[flexcom_num].addr;
}

unsigned int flexcom_get_regmap(unsigned int flexcom_num)
{
	if (flexcom_num >= AT91C_NUM_FLEXCOM)
		return 0;

	return flexcoms[flexcom_num].regmap;
}

int flexcom_set_mode(unsigned int flexcom_num, unsigned int mode)
{
	unsigned int base_addr = flexcom_get_base(flexcom_num);

	if (base_addr) {
		writel(mode, base_addr);
		flexcoms[flexcom_num].mode = mode;
		return 0;
	}

	/* failed */
	return -1;
}

int flexcom_init(unsigned int flexcom_num)
{
	int ret;

	ret = flexcom_set_mode(flexcom_num, flexcoms[flexcom_num].mode);
	if (ret)
		return ret;

	switch (flexcoms[flexcom_num].mode) {
	case FLEXCOM_USART:
		flexcoms[flexcom_num].regmap = flexcoms[flexcom_num].addr +
						AT91C_OFFSET_FLEXCOM_USART;
		break;
	case FLEXCOM_TWI:
		flexcoms[flexcom_num].regmap = flexcoms[flexcom_num].addr +
						AT91C_OFFSET_FLEXCOM_TWI;
		break;
	case FLEXCOM_SPI:
		flexcoms[flexcom_num].regmap = flexcoms[flexcom_num].addr +
						AT91C_OFFSET_FLEXCOM_SPI;
		break;
	}

	return 0;
}
