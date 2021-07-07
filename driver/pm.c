// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "board.h"
#include "twi.h"
#include "wm8904.h"
#include "hdmi_SiI9022.h"
#include "macb.h"
#include "act8865.h"

void at91_board_pm(void)
{
	at91_disable_smd_clock();

#ifdef CONFIG_TWI
	if (!twi_init_done)
		twi_init();
#endif

#ifdef CONFIG_HDMI
	SiI9022_enter_power_state_D3_Cold();
#endif
#ifdef CONFIG_WM8904
	wm8904_enter_low_power();
#endif
#ifdef CONFIG_MACB
	phys_enter_power_down();
#endif
#ifdef CONFIG_ACT8865_POWER_SAVING
	act8865_set_power_saving_mode();
#endif
}
