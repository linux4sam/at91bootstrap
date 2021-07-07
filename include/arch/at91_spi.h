/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_SPI_H__
#define __AT91_SPI_H__

/* *** Register offset in AT91S_SPI structure ***/
#define SPI_CR		0x00	/* Control Register */
#define SPI_MR		0x04	/* Mode Register */
#define SPI_RDR		0x08	/* Receive Data Register */
#define SPI_TDR		0x0C	/* Transmit Data Register */
#define SPI_SR		0x10	/* Status Register */
#define SPI_IER		0x14	/* Interrupt Enable Register */
#define SPI_IDR		0x18	/* Interrupt Disable Register */
#define SPI_IMR		0x1C	/* Interrupt Mask Register */
#define SPI_CSR(x)	(0x30 + 4 * (x))	/* Chip Select Register */

/* -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register --------*/ 
#define AT91C_SPI_SPIEN		(0x1UL <<  0)
#define AT91C_SPI_SPIDIS	(0x1UL <<  1)
#define AT91C_SPI_SWRST		(0x1UL <<  7)
#define AT91C_SPI_LASTXFER	(0x1UL << 24)

/* -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register --------*/ 
#define AT91C_SPI_MSTR		(0x1UL <<  0)
#define AT91C_SPI_PS		(0x1UL <<  1)
#define 	AT91C_SPI_PS_FIXED		(0x0UL <<  1)
#define 	AT91C_SPI_PS_VARIABLE		(0x1UL <<  1)
#define AT91C_SPI_PCSDEC	(0x1UL <<  2)
#define AT91C_SPI_FDIV		(0x1UL <<  3)
#define AT91C_SPI_MODFDIS	(0x1UL <<  4)
#define AT91C_SPI_LLB		(0x1UL <<  7)
#define AT91C_SPI_PCS(x)	(x << 16)
#define AT91C_SPI_DLYBCS(x)	(x << 24)

/* -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register --------*/ 
#define AT91C_SPI_RD(x)		(x << 0)
#define AT91C_SPI_RPCS(x)	(x << 16)

/* -------- SPI_TDR : (SPI Offset: 0xC) Transmit Data Register --------*/ 
#define AT91C_SPI_TD(x)		(x << 0)
#define AT91C_SPI_TPCS(x)	(x << 16)
#define AT91C_SPI_LASTXFER	(0x1UL << 24)

/* -------- SPI_SR : (SPI Offset: 0x10) Status Register --------*/ 
#define AT91C_SPI_RDRF		(0x1UL <<  0)
#define AT91C_SPI_TDRE		(0x1UL <<  1)
#define AT91C_SPI_MODF		(0x1UL <<  2)
#define AT91C_SPI_OVRES		(0x1UL <<  3)
#define AT91C_SPI_ENDRX		(0x1UL <<  4)
#define AT91C_SPI_ENDTX		(0x1UL <<  5)
#define AT91C_SPI_RXBUFF	(0x1UL <<  6)
#define AT91C_SPI_TXBUFE	(0x1UL <<  7)
#define AT91C_SPI_NSSR		(0x1UL <<  8)
#define AT91C_SPI_TXEMPTY	(0x1UL <<  9)
#define AT91C_SPI_SPIENS	(0x1UL << 16)
/* -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register --------*/ 
/* -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- */
/* -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- */

/* -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- */
#define AT91C_SPI_CPOL		(0x1UL << 0)
#define AT91C_SPI_NCPHA		(0x1UL << 1)
#define AT91C_SPI_CSNAAT	(0x1UL << 2)
#define AT91C_SPI_CSAAT		(0x1UL << 3)
#define AT91C_SPI_BITS		(0xFUL << 4)
#define 	AT91C_SPI_BITS_8		(0x0UL << 4)
#define 	AT91C_SPI_BITS_9		(0x1UL << 4)
#define 	AT91C_SPI_BITS_10		(0x2UL << 4)
#define 	AT91C_SPI_BITS_11		(0x3UL << 4)
#define 	AT91C_SPI_BITS_12		(0x4UL << 4)
#define 	AT91C_SPI_BITS_13		(0x5UL << 4)
#define 	AT91C_SPI_BITS_14		(0x6UL << 4)
#define 	AT91C_SPI_BITS_15		(0x7UL << 4)
#define 	AT91C_SPI_BITS_16		(0x8UL << 4)
#define AT91C_SPI_SCBR(x)	(x << 8)
#define AT91C_SPI_DLYBS(x)	(x << 16)
#define AT91C_SPI_DLYBCT(x)	(x << 24)

#endif /* #ifndef __AT91_SPI_H__ */
