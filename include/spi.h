/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SPI_H__
#define __SPI_H__

/* SPI mode flags */
#define	SPI_MODE0	0
#define	SPI_MODE1	1
#define	SPI_MODE2	2	
#define	SPI_MODE3	3

/* Controller-specific definitions: */
#define AT91C_SPI_PCS0_DATAFLASH	0
#define AT91C_SPI_PCS1_DATAFLASH	1
#define AT91C_SPI_PCS2_DATAFLASH	2
#define AT91C_SPI_PCS3_DATAFLASH	3

/* functions */
extern void at91_spi_cs_activate(void);
extern void at91_spi_cs_deactivate(void);

extern void at91_spi_enable(void);
extern void at91_spi_disable(void);
extern int at91_spi_init(unsigned int pcs,
			unsigned int clock,
			unsigned int mode);
extern void at91_spi_write_data(unsigned short data);
extern unsigned int at91_spi_read_spi(void);
extern unsigned int at91_spi_read_sr(void);

#endif	/* #ifndef __SPI_H__ */
