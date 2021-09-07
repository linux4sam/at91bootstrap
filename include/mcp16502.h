/*
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __MCP16502_H__
#define __MCP16502_H__
#if defined(CONFIG_MCP16502)

#include "gpio.h"
#include "twi.h"

#define MCP16502_MIN	(0)
#define MCP16502_BUCK1	(MCP16502_MIN)
#define MCP16502_BUCK2	(1)
#define MCP16502_BUCK3	(2)
#define MCP16502_BUCK4	(3)
#define MCP16502_LDO1	(4)
#define MCP16502_LDO2	(5)
#define MCP16502_MAX	(MCP16502_LDO2)

/**
 * struct mcp16502_cfg - MCP16502 configuration descriptor
 * @regulator:	regulator identifier
 * @uV:		regulator voltage (in microvolts)
 * @enable:	regulator enable status
 */
struct mcp16502_cfg {
	unsigned int regulator;
	unsigned int uV;
	unsigned int enable;
};

extern int mcp16502_init(int busid, int addr, const struct pio_desc *lpm_desc,
			 const struct mcp16502_cfg *cfg, unsigned int cfg_no);
extern int mcp16502_regulator_get_voltage(unsigned int regid);
extern int mcp16502_regulator_set_voltage(unsigned int regid, unsigned int uV);
extern int mcp16502_regulator_set_enable(unsigned int regid,
			 unsigned int enable);
extern unsigned int mcp16502_regulator_get_enable(unsigned int regid);
extern const char * const mcp16502_regulator_id_to_name(unsigned int regid);
#if defined(CONFIG_MCP16502_SET_VOLTAGE)
extern void mcp16502_voltage_select(void);
#endif
#endif
#endif
