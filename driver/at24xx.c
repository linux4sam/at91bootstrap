// Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "twi.h"
#include "board_hw_info.h"
#include "debug.h"

#define EK_INFO_OFFSET (CONFIG_EEPROM_SIZE - HW_INFO_TOTAL_SIZE)

static unsigned int at24_get_twi_bus(void)
{
	return CONFIG_EEPROM_ON_TWI;
}
static int at24_read(unsigned char device_addr, unsigned char internal_addr,
			unsigned char *buff, unsigned int length)
{
	unsigned char iaddr_size = 1;
	unsigned int bus;
	int ret = 0;

	bus = at24_get_twi_bus();

	ret = twi_read(bus, device_addr, internal_addr, iaddr_size, buff, length);
	if (ret)
		dbg_loud("EEPROM: Failed to read\n");

	return ret;
}

int load_ek_at24xx(unsigned char *buff, unsigned int length)
{
	unsigned char dev_addr = CONFIG_EEPROM_ADDR;
	unsigned char offset = EK_INFO_OFFSET;
	int ret = 0;

	if (!twi_init_done)
		twi_init();

	ret = at24_read(dev_addr, offset, buff, length);

	if (!ret) {
		dbg_loud("EEPROM Buff:\n");
#if (BOOTSTRAP_DEBUG_LEVEL >= DEBUG_LOUD)
		dbg_hexdump(buff, length, DUMP_WIDTH_BIT_8);
#endif
	}

	return ret;
}
