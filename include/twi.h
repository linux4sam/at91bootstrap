/*
 * Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __TWI_H__
#define __TWI_H__

extern unsigned int twi_init_done;

extern int twi_read(unsigned int twi_no, unsigned char device_addr,
		unsigned int internal_addr, unsigned char iaddr_size,
		unsigned char *data, unsigned int bytes);

extern int twi_write(unsigned int twi_no, unsigned char device_addr,
		unsigned int internal_addr, unsigned char iaddr_size,
		unsigned char *data, unsigned int bytes);

extern void twi_init(void);
extern int twi_bus_init(unsigned int (*at91_twi_hw_init)(unsigned int index), unsigned int index);

#endif
