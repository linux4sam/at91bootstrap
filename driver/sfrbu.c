// Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "arch/at91_sfrbu.h"

/**
 * sfrbu_select_ba_power_source: select power source for backup area
 * @vddin33:	if 1 switch backup area to 3v3 power source
 * 		if 0 switch backup area to battery
 *
 * Returns:	void
 */
void sfrbu_select_ba_power_source(int vddin33)
{
	unsigned int val = readl(AT91C_BASE_SFRBU + SFRBU_PSWBU);
	unsigned int state = vddin33 ? AT91C_PSWBU_STATE : 0;
	unsigned int softsw = vddin33 ? AT91C_PSWBU_SOFTSWITCH : 0;

	/* Return if nothing to be done. */
	if (!(!!vddin33 ^ !!(val & AT91C_PSWBU_STATE)))
		return;

	val |= (AT9CC_PWSBU_CTRL | softsw | AT91C_PSWBU_PSWKEY);
	writel(val, AT91C_BASE_SFRBU + SFRBU_PSWBU);

	/* Wait for update. */
	val = readl(AT91C_BASE_SFRBU + SFRBU_PSWBU);
	while ((val & state) != state)
		val = readl(AT91C_BASE_SFRBU + SFRBU_PSWBU);
}

/**
 * sfrbu_ddr_is_powered: get DDR power mode
 *
 * Returns: 	1 - DDR ON
 * 		0 - DDR OFF
 */
int sfrbu_ddr_is_powered(void)
{
	unsigned int val = readl(AT91C_BASE_SFRBU + SFRBU_DDRBUMCR);

	return !(val & AT91C_DDRBUMCR_BUMEN);
}

/**
 * sfrbu_set_ddr_power_mode: set DDR power mode
 * @on:		if 1 set DDR to power mode ON
 * 		if 0 set DDR to power mode OFF
 *
 * Returns:	void
 */
void sfrbu_set_ddr_power_mode(int on)
{
	writel(!on, AT91C_BASE_SFRBU + SFRBU_DDRBUMCR);
}

