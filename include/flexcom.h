/*
 * Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef FLEXCOM_H_
#define FLEXCOM_H_

#ifdef CONFIG_FLEXCOM

#define AT91C_OFFSET_FLEXCOM_USART		0x200
#define AT91C_OFFSET_FLEXCOM_SPI		0x400
#define AT91C_OFFSET_FLEXCOM_TWI		0x600

#define FLEXCOM_USART		0x1
#define FLEXCOM_SPI		0x2
#define FLEXCOM_TWI		0x3

struct at91_flexcom {
	unsigned int id; 		/* SOC Peripheral ID */
	unsigned int mode;		/* Peripheral mode : SPI/USART/TWI */
	unsigned int addr; 		/* Flexcom Address */
	unsigned int regmap;		/* register base for either SPI/USART/TWI */
};

extern void flexcoms_init(struct at91_flexcom *board_specific_flexcoms);
extern int flexcom_set_mode(unsigned int flexcom_num, unsigned int mode);
extern int flexcom_init(unsigned int flexcom_num);
extern unsigned int flexcom_get_base(unsigned int flexcom_num);
extern unsigned int flexcom_get_regmap(unsigned int flexcom_num);

#endif /* CONFIG_FLEXCOM */
#endif /* FLEXCOM_H_ */
