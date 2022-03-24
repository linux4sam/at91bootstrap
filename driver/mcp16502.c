// Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "backup.h"
#include "common.h"
#include "debug.h"
#include "hardware.h"
#include "mcp16502.h"
#include "twi.h"
#include "div.h"

#define MCP16502_BASE(_i)		(((_i) + 1) << 4)
#define MCP16502_LOW_SEL		(0x0D)
#define MCP16502_VSEL			(0x3F)
#define MCP16502_EN			(1 << 7)

/**
 * struct mcp16502_priv - MCP16502 private data structure
 * @busid: TWI bus ID
 * @addr: TWI device address
 */
static struct mcp16502_priv {
	int busid;
	int addr;
} mcp16502;

/* Regulators constrains. */
static struct regulator {
	unsigned int min_uV;
	unsigned int max_uV;
	unsigned int step_uV;
} regulators[] = {
	[MCP16502_BUCK1] = { 1200000, 3700000, 50000, },
	[MCP16502_BUCK2...MCP16502_BUCK4] = { 600000, 1850000, 25000, },
	[MCP16502_LDO1...MCP16502_LDO2] = { 1200000, 3700000, 50000, },
};

/**
 * mcp16502_regulator_id_to_name()	- set regulator voltage
 *
 * @regid:	regulator identifier
 *
 * Returns:	regulator's name on success, NULL in case of failure
 */
const char * const mcp16502_regulator_id_to_name(unsigned int regid)
{
	static const char * const names[] = {
		[MCP16502_BUCK1] = "OUT1",
		[MCP16502_BUCK2] = "OUT2",
		[MCP16502_BUCK3] = "OUT3",
		[MCP16502_BUCK4] = "OUT4",
		[MCP16502_LDO1] = "LDO1",
		[MCP16502_LDO2] = "LDO2",
	};

	if (regid < MCP16502_MIN || regid > MCP16502_MAX)
		return NULL;

	return names[regid];
}

/**
 * mcp16502_regulator_set_voltage()	- set regulator voltage
 *
 * @regid:	regulator identifier
 * @uV:		regulator voltage (in microvolts)
 *
 * Returns:	0 on success, negative number in case of failure
 */
int mcp16502_regulator_set_voltage(unsigned int regid, unsigned int uV)
{
	unsigned char steps, selector, val;
	int ret;

	if (regid < MCP16502_MIN || regid > MCP16502_MAX ||
	    uV < regulators[regid].min_uV || uV > regulators[regid].max_uV)
		return -1;

	ret = twi_read(mcp16502.busid, mcp16502.addr, MCP16502_BASE(regid),
		       1, &val, 1);
	if (ret)
		return ret;

	steps = div((uV - regulators[regid].min_uV), regulators[regid].step_uV);
	selector = (MCP16502_LOW_SEL + steps) & MCP16502_VSEL;
	val &= ~MCP16502_VSEL;
	val |= selector;

	ret = twi_write(mcp16502.busid, mcp16502.addr, MCP16502_BASE(regid),
			1, &val, 1);

	return ret;
}

/**
 * mcp16502_regulator_get_voltage()	- get regulator voltage
 *
 * @regid:	regulator identifier
 *
 * Returns:	voltage value (in microvolts) on success, negative number in
 *		case of failure
 */
int mcp16502_regulator_get_voltage(unsigned int regid)
{
	unsigned char val, steps;
	unsigned int uV;
	int ret;

	if (regid < MCP16502_MIN || regid > MCP16502_MAX)
		return -1;

	ret = twi_read(mcp16502.busid, mcp16502.addr, MCP16502_BASE(regid),
		       1, &val, 1);
	if (ret)
		return ret;

	steps = (val & MCP16502_VSEL) - MCP16502_LOW_SEL;
	uV = regulators[regid].min_uV + regulators[regid].step_uV * steps;

	/* Should not happen. */
	if (uV < regulators[regid].min_uV || uV > regulators[regid].max_uV)
		return -1;

	return uV;
}

/**
 * mcp16502_regulator_set_enable()	- enable/disable regulator
 *
 * @regid:	regulator identifier
 * @enable:	new regulator status (0 - disable, 1 - enable)
 *
 * Returns:	0 on success, negative number in case of failure
 */
int mcp16502_regulator_set_enable(unsigned int regid, unsigned int enable)
{
	unsigned char val;
	int ret;

	if (regid < MCP16502_MIN || regid > MCP16502_MAX)
		return -1;

	ret = twi_read(mcp16502.busid, mcp16502.addr, MCP16502_BASE(regid),
		       1, &val, 1);

	if ((enable && (val & MCP16502_EN)) ||
	    (!enable && !(val & MCP16502_EN)))
		return 0;

	if (enable)
		val |= MCP16502_EN;
	else
		val &= ~MCP16502_EN;

	ret = twi_write(mcp16502.busid, mcp16502.addr, MCP16502_BASE(regid),
			1, &val, 1);

	return ret;
}

/**
 * mcp16502_regulator_get_enable()	- get regulator enable status
 *
 * @regid:	regulator identifier
 *
 * Returns:	regulator status (0 - disable, 1 - enable) or
 *		negative number in case of failure
 */
unsigned int mcp16502_regulator_get_enable(unsigned int regid)
{
	unsigned char val;
	int ret;

	if (regid < MCP16502_MIN || regid > MCP16502_MAX)
		return 0;

	ret = twi_read(mcp16502.busid, mcp16502.addr, MCP16502_BASE(regid),
		       1, &val, 1);
	if (ret)
		return 0;

	return !!(val & MCP16502_EN);
}

/**
 * mcp16502_init()		- init MCP16502 PMIC
 *
 * @dev:	i2c device information
 * @desc:	low power mode pin descriptor
 * @cfgs:	regulators configuration
 * @cfg_no:	number of regulators to be configured
 *
 * Returns:	0 on success, negative number in case of failure
 */
int mcp16502_init(int busid, int addr, const struct pio_desc *lpm_desc,
		  const struct mcp16502_cfg *cfgs, unsigned int cfgs_no)
{
	int i, ret;

	if (busid < 0 || addr < 0)
		return -1;

	mcp16502.busid = busid;
	mcp16502.addr = addr;

	/* Make sure PMIC is in active state. */
	if (lpm_desc)
		pio_configure(lpm_desc);

	/* Setup regulators. */
	for (i = 0; i < cfgs_no && cfgs; i++) {
		if (!cfgs[i].uV)
			continue;

		ret = mcp16502_regulator_set_voltage(cfgs[i].regulator,
						     cfgs[i].uV);
		if (ret) {
			dbg_very_loud("regulator (%d) set voltage failed\n",
					cfgs[i].regulator);
			return ret;
		}

		ret = mcp16502_regulator_set_enable(cfgs[i].regulator,
						    cfgs[i].enable);
		if (ret) {
			dbg_very_loud("regulator (%d) enable failed\n",
				      cfgs[i].regulator);
			return ret;
		}
	}

	return 0;
}
#if defined(CONFIG_MCP16502_SET_VOLTAGE)
void mcp16502_voltage_select(void)
{
	const struct mcp16502_cfg regulators_cfg[] = {
		{.regulator = MCP16502_BUCK1, .uV = CONFIG_VOLTAGE_OUT1 * 1000, .enable = 1, },
		{.regulator = MCP16502_BUCK2, .uV = CONFIG_VOLTAGE_OUT2 * 1000, .enable = 1, },
		{.regulator = MCP16502_BUCK3, .uV = CONFIG_VOLTAGE_OUT3 * 1000, .enable = 1, },
		{.regulator = MCP16502_BUCK4, .uV = CONFIG_VOLTAGE_OUT4 * 1000, .enable = 1, },
		{.regulator = MCP16502_LDO1, .uV = CONFIG_VOLTAGE_LDO1 * 1000, .enable = 1, },
		{.regulator = MCP16502_LDO2, .uV = CONFIG_VOLTAGE_LDO2 * 1000, .enable = 1, },
	};

	int i;
	/*
	 * SAMA7G5's SHDWC keeps LPM pin low by default, so there is no need
	 * to pass pin descriptor to mcp16502_init() for switching to active
	 * state.
	 */
	if (mcp16502_init(CONFIG_PMIC_ON_TWI, 0x5b, NULL, regulators_cfg,
				ARRAY_SIZE(regulators_cfg))) {
		dbg_printf("MCP16502: init failure");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(regulators_cfg); i++) {
		if (!regulators_cfg[i].uV)
			continue;
		dbg_very_loud("MCP16502: %s = %umV\n",
			      mcp16502_regulator_id_to_name(regulators_cfg[i].regulator),
			      regulators_cfg[i].uV / 1000);
	}

	dbg_very_loud("\n");
}
#endif /* CONFIG_MCP16502_SET_VOLTAGE */
