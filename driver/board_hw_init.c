// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "arch/at91_pio.h"
#include "gpio.h"
#include "timer.h"
#include "debug.h"
#include "hardware.h"
#include "pmc.h"
#include "sdhc_cal.h"

#ifdef CONFIG_BOARD_QUIRK_SAMA5D3
void HDMI_Qt1070_workaround(void)
{
	/* For the HDMI and QT1070 shar the irq line
	 * if the HDMI does not initialize, the irq line is pulled down by HDMI,
	 * so, the irq line can not used by QT1070
	 */
	pio_set_gpio_output(AT91C_PIN_PC(31), 1);
	udelay(33000);
	pio_set_gpio_output(AT91C_PIN_PC(31), 0);
	udelay(33000);
	pio_set_gpio_output(AT91C_PIN_PC(31), 1);
}
#endif

#if defined(CONFIG_HDMI)
#if defined(CONFIG_BOARD_QUIRK_SAMA5D4)
void SiI9022_hw_reset(void)
{
	pio_set_gpio_output(AT91C_PIN_PB(15), 1);
	pio_set_gpio_output(AT91C_PIN_PB(15), 0);
	udelay(500);
	pio_set_gpio_output(AT91C_PIN_PB(15), 1);
}
#endif
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_SIP
void sdmmc_cal_setup(void)
{
	unsigned int cidr, exid;
	unsigned int reg;

	/* Identify SAMA5D2 SiP that are concerned by the errata */
	cidr = readl(AT91C_BASE_CHIPID + CHIPID_CIDR);
	if ((cidr & 0x7fffffe0) != SAMA5D2_CIDR)
		return;

	exid = readl(AT91C_BASE_CHIPID + CHIPID_EXID);
	if (exid != SAMA5D225C_D1M_EXID
	 && exid != SAMA5D27C_D1G_EXID
	 && exid != SAMA5D28C_D1G_EXID)
		return;

	/*
	 * Even if SDMMC interfaces are not in use, enable the
	 * calibration analog cell and make it remain powered after
	 * calibration procedure is done.
	 * It's needed on SDMMC0 only
	 */
	dbg_loud("Applying VDDSDMMC errata to ID: %x\n", exid);

	/* Enable peripheral clock */
	pmc_enable_periph_clock(AT91C_ID_SDMMC0, PMC_PERIPH_CLK_DIVIDER_NA);

	/* Launch calibration and wait till it's completed */
	reg = readl(AT91C_BASE_SDHC0 + SDMMC_CALCR);
	reg |= SDMMC_CALCR_ALWYSON | SDMMC_CALCR_EN;
	writel(reg, AT91C_BASE_SDHC0 + SDMMC_CALCR);
	while (readl(AT91C_BASE_SDHC0 + SDMMC_CALCR) & SDMMC_CALCR_EN)
		;

	/* Disable peripheral clock */
	pmc_disable_periph_clock(AT91C_ID_SDMMC0);
}
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA5D2_ICP
/*
 * Must set PB25 to LOW to enable the can transceivers.
 * This needs to be replaced later with Linux control over this GPIO
 */
void at91_can_stdby_dis(void)
{
	const struct pio_desc can_pins[] = {
		{"CAN_STDBY", AT91C_PIN_PB(25), 0, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_B},
	};

	pio_configure(can_pins);
}

void peripherals_hw_reset(void)
{
	const struct pio_desc reset_peripherals[] = {
		{"LAN9252_RST",	AT91C_PIN_PB(16),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 200us */
		{"HSIC_RST",	AT91C_PIN_PC(2),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 1us */
		{"USB2534_RST",	AT91C_PIN_PC(17),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 5us */
		{"KSZ8563_RST",	AT91C_PIN_PD(4),	0, PIO_DEFAULT, PIO_OUTPUT},	/* min. deassertion 100us */
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc wake_peripherals[] = {
		{"LAN9252_RST",	AT91C_PIN_PB(16),	1, PIO_DEFAULT, PIO_OUTPUT},
		{"HSIC_RST",	AT91C_PIN_PC(2),	1, PIO_DEFAULT, PIO_OUTPUT},
		{"USB2534_RST",	AT91C_PIN_PC(17),	1, PIO_DEFAULT, PIO_OUTPUT},
		{"KSZ8563_RST",	AT91C_PIN_PD(4),	1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(reset_peripherals);
	udelay(250);
	pio_configure(wake_peripherals);
}
#endif

#ifdef CONFIG_BOARD_QUIRK_SAM9X60_EK
void wilc_pwrseq()
{
	const struct pio_desc wilc_down_pins[] = {
		{"WILC_RESETN", AT91C_PIN_PB(25), 0, PIO_DEFAULT, PIO_OUTPUT},
		{"WILC_EN", AT91C_PIN_PA(29), 0, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc wilc_powerup_pins[] = {
		{"WILC_EN", AT91C_PIN_PA(29), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	const struct pio_desc wilc_en_pins[] = {
		{"WILC_RESETN", AT91C_PIN_PB(25), 1, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_A},
	};

	pio_configure(wilc_down_pins);
	udelay(5000);
	pio_configure(wilc_powerup_pins);
	udelay(5000);
	pio_configure(wilc_en_pins);
}
#endif

#ifdef CONFIG_BOARD_QUIRK_SAMA7G5_EK
/*
 * Must set PC15 and PC16 to LOW to enable the can transceivers.
 * This needs to be replaced later with Linux control over these GPIOs
 */
void at91_can_stdby_dis(void)
{
	const struct pio_desc can_pins[] = {
		{"CAN_STDBY", AT91C_PIN_PC(15), 0, PIO_DEFAULT, PIO_OUTPUT},
		{"CAN_STDBY", AT91C_PIN_PC(16), 0, PIO_DEFAULT, PIO_OUTPUT},
		{(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_B},
	};

	pio_configure(can_pins);
}
#endif

#ifdef CONFIG_BOARD_QUIRK_SAM9X60_CURIOSITY
/*
 * Must set PA4 & PB17 to LOW to enable the can transceivers.
 * This needs to be replaced later with Linux control over this GPIOs
 */
void at91_can_stdby_dis(void)
{
        const struct pio_desc can_pins[] = {
                {"CAN_STDBY", AT91C_PIN_PA(4), 0, PIO_DEFAULT, PIO_OUTPUT},
                {"CAN_STDBY", AT91C_PIN_PB(17), 0, PIO_DEFAULT, PIO_OUTPUT},
                {(char *)0, 0, 0, PIO_DEFAULT, PIO_PERIPH_B},
        };

        pio_configure(can_pins);
}
#endif
