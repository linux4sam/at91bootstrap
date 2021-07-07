// Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "twi.h"
#include "timer.h"
#include "debug.h"

/*
 * SiI9022 Slave Device Address
 */
#define SiI9022_ADDR	(0x39)

/*
 * SiI9022 Global Register Map
 */
#define TPI_DEVICE_POWER_STATE_CTRL_REG	(0x1E)
#define TPI_DEVICE_ID			(0x1B)
#define TMDS_CONT_REG			(0x82)
#define TPI_INTERRUPT_ENABLE_REG	(0x3C)
#define TPI_INTERRUPT_STATUS_REG	(0x3D)
#define TPI_ENABLE			(0xC7)

/*
 * Field Definitions.
 */
#define HOT_PLUG_EVENT			(0x01)

#define TX_POWER_STATE_MASK		(0x03)
#define TX_POWER_STATE_D0		(0x00)
#define TX_POWER_STATE_D1		(0x01)
#define TX_POWER_STATE_D2		(0x02)
#define TX_POWER_STATE_D3		(0x03)

#define SiI9022_DEVICE_ID		(0xB0)

static unsigned int SiI9022_get_twi_bus(void)
{
	return CONFIG_HDMI_ON_TWI;
}

static int SiI9022_read(unsigned char reg_addr, unsigned char *data)
{
	unsigned int bus;
	int ret;

	bus = SiI9022_get_twi_bus();

	ret = twi_read(bus, SiI9022_ADDR,
				reg_addr, 1, (unsigned char *)data, 1);
	if (ret) {
		dbg_loud("SiI9022: Failed to read on TWI bus: %d\n", bus);
		return -1;
	}

	return 0;
}

static int SiI9022_write(unsigned char reg_addr, unsigned char data)
{
	unsigned int bus;
	int ret;

	bus = SiI9022_get_twi_bus();

	ret = twi_write(bus, SiI9022_ADDR, reg_addr, 1, &data, 1);
	if (ret) {
		dbg_loud("SiI9022: Failed to write on TWI bus: %d\n", bus);
		return -1;
	}

	return 0;
}

static int SiI9022_TxHW_Reset(void)
{
	int ret;

	/* Set terminations to default. */
	ret = SiI9022_write(TMDS_CONT_REG, 0x25);
	if (ret)
		return -1;

	/* HW debounce to 64ms (0x14) */
	ret = SiI9022_write(0x7C, 0x14);
	if (ret)
		return -1;

	return 0;
}

int SiI9022_enter_power_state_D3_Cold(void)
{
	unsigned char power_state = 0;
	unsigned char device_id = 0;
	unsigned int timeout = 10;
	int ret;

	/*
	 * D3 cold Note:It is necessary to unplug the HDMI connector,
	 * otherwise would not go to D3 cold.
	 */

	/* 1. Clear any pending interrupts via TPI 0x3D */
	ret = SiI9022_write(TPI_INTERRUPT_STATUS_REG, 0xFF);
	if (ret) {
		dbg_loud("SiI9022: Failed to clear any pending interrupts\n");
		return -1;
	}
	/* 2. Reset SiI9022A Tx via HW */
	ret = SiI9022_TxHW_Reset();
	if (ret) {
		dbg_loud("SiI9022: Failed to reset\n");
		return -1;
	}

	do {
		/* 3. Write device register 0xC7 = 0x00 to enter TPI mode */
		ret = SiI9022_write(TPI_ENABLE, 0x00);
		if (ret)
			dbg_loud("SiI9022: Failed to enter TPI mode\n");

		mdelay(100);

		power_state = TX_POWER_STATE_D0;
		ret = SiI9022_write(TPI_DEVICE_POWER_STATE_CTRL_REG,
								power_state);
		if (ret) {
			dbg_loud("SiI9022: Failed to write TPI 0x1E\n");
			return -1;
		}

		ret = SiI9022_read(TPI_DEVICE_ID, &device_id);
		if (ret)
			dbg_loud("SiI9022: Failed to 0x1b\n");
	} while ((--timeout) && (device_id == 0x0));

	if (device_id != SiI9022_DEVICE_ID) {
		dbg_loud("SiI9022: Not found\n");
		return -1;
	}

	/* 4. Set INT# source to Hotplug via TPI 0x3C[0] = 1b */
	ret = SiI9022_write(TPI_INTERRUPT_ENABLE_REG, HOT_PLUG_EVENT | 0x08);
	if (ret) {
		dbg_loud("SiI9022: Failed to Set INT# source to Hotplug\n");
		return -1;
	}

	/* 5. Clear any pending interrupts via TPI 0x3D*/
	ret = SiI9022_write(TPI_INTERRUPT_STATUS_REG, 0xFF);
	if (ret) {
		dbg_loud("SiI9022: Failed to clear any pending interrupts\n");
		return -1;
	}

	/* 6. Enter D3 Cold mode via TPI 0x1E[1:0] = 11b */
	power_state = 0x04;
	ret = SiI9022_write(TPI_DEVICE_POWER_STATE_CTRL_REG, power_state);
	if (ret) {
		dbg_loud("SiI9022: Failed to write TPI 0x1E\n");
		return -1;
	}

	power_state &= ~TX_POWER_STATE_MASK;
	power_state |= TX_POWER_STATE_D3;
	ret = SiI9022_write(TPI_DEVICE_POWER_STATE_CTRL_REG, power_state);
	if (ret) {
		dbg_loud("SiI9022: Failed to write TPI 0x1E\n");
		return -1;
	}

	dbg_info("HDMI SiI9022: Enter D3 Cold mode\n");

	return 0;
}
