/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __SPI_H__
#define __SPI_H__

/* Controller-specific definitions: */

/* SPI mode flags */
#define	SPI_CPHA	0x01			/* clock phase */
#define	SPI_CPOL	0x02			/* clock polarity */
#define	SPI_MODE0	(0|0)			/* (original MicroWire) */
#define	SPI_MODE1	(0|SPI_CPHA)
#define	SPI_MODE2	(SPI_CPOL|0)
#define	SPI_MODE3	(SPI_CPOL|SPI_CPHA)

/* SPI transfer flags */
#define SPI_XFER_BEGIN	0x01			/* Assert CS before transfer */
#define SPI_XFER_END	0x02			/* Deassert CS after transfer */

/* Chip Select 0 : NPCS0 %1110 */
#define AT91C_SPI_PCS0_DATAFLASH	0xE
/* Chip Select 1 : NPCS1 %1101 */
#define AT91C_SPI_PCS1_DATAFLASH	0xD
/* Chip Select 2 : NPCS2 %1011 */
#define AT91C_SPI_PCS2_DATAFLASH	0xB
/* Chip Select 3 : NPCS3 %0111 */
#define AT91C_SPI_PCS3_DATAFLASH	0x7

/* export functions */
extern int at91_spi_init(unsigned int clock, unsigned int mode);
extern int at91_spi_enable(void);
extern void at91_spi_disable(void);
extern int spi_xfer(unsigned int len,
			const void *dout,
			void *din,
			unsigned long flags);

#endif	/* #ifndef __SPI_H__ */
