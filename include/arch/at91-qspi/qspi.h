/*
 * Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef	__AT91_QSPI_H__
#define	__AT91_QSPI_H__

#if defined(CONFIG_SAMA5D2)
#include "qspi-sama5d2.h"
#elif defined(CONFIG_SAM9X60)
#include "qspi-sam9x60.h"
#else
#error "QSPI not supported for this SoC"
#endif

/*
 * Register Definitions
 */
#define	QSPI_CR		0x00	/* Control Register */
#define	QSPI_MR		0x04	/* Mode Register */
#define	QSPI_RDR	0x08	/* Receive Data Register */
#define	QSPI_TDR	0x0c	/* Transmit Data Register */
#define	QSPI_SR		0x10	/* Status Register */
#define	QSPI_IER	0x14	/* Interrupt Enable Register */
#define	QSPI_IDR	0x18	/* Interrupt Disable Register */
#define	QSPI_IMR	0x1c	/* Interrupt Mask Register */
#define	QSPI_SCR	0x20	/* Serial Clock Register */
#define	QSPI_IAR	0x30	/* Instruction Address Register */
#define	QSPI_IFR	0x38	/* Instruction Frame Register */
/* 0x3c Reserved */
#define	QSPI_SMR	0x40	/* Scrambling Mode Register */
#define	QSPI_SKR	0x44	/* Scrambling Key Register */
/* 0x48 ~ 0xe0 */
#define	QSPI_WPMR	0xe4	/* Write Protection Mode Register */
#define	QSPI_WPSR	0xe8	/* Write Protection Status Register */
/* 0xec ~ 0xf8 Reserved */
/* 0xfc Reserved */

/*
 * Register Field Definitions
 */
/* QSPI_CR */
#define	QSPI_CR_QSPIEN		(0x1 << 0)	/* QSPI Enable */
#define	QSPI_CR_QSPIDIS		(0x1 << 1)	/* QSPI Disable */
#define	QSPI_CR_SWRST		(0x1 << 7)	/* QSPI Software Reset */
#define	QSPI_CR_LASTXFER	(0x1 << 24)	/* Last Transfer */

/* QSPI_MR */
#define	QSPI_MR_SMM		(0x1 << 0)	/* Serial Memory Mode */
#define	QSPI_MR_WDRBT		(0x1 << 2)	/* Wait Data Read Before Transfer */
#define	QSPI_MR_SMRM		(0x1 << 3)	/* Serial Memory Register Mode */
#define	QSPI_MR_CSMODE		(0x3 << 4)	/* Chip Select Mode */
#define		QSPI_MR_CSMODE_NOT_RELOADED	(0x0 << 4)
#define		QSPI_MR_CSMODE_LASTXFER		(0x1 << 4)
#define		QSPI_MR_CSMODE_SYSTEMATICALLY	(0x2 << 4)
#define	QSPI_MR_NBBITS		(0xf << 8)	/* Number of Bits Per Transfer */
#define		QSPI_MR_NBBITS_8_BIT		(0x0 << 8)
#define		QSPI_MR_NBBITS_16_BIT		(0x8 << 8)
#define	QSPI_MR_DLYBCT		(0xff << 16)	/* Delay Between Consecutive Transfers */
#define	QSPI_MR_DLYCS		(0xff << 24)	/* Minimum Inactive QCS Delay */

/* QSPI_SR */
#define	QSPI_SR_RDRF		(0x1 << 0)	/* Receive Data Register Full */
#define	QSPI_SR_TDRE		(0x1 << 1)	/* Transmit Data Register Empty */
#define	QSPI_SR_TXEMPTY		(0x1 << 2)	/* Transmission Registers Empty */
#define	QSPI_SR_OVRES		(0x1 << 3)	/* Overrun Error Status */
#define	QSPI_SR_CSR		(0x1 << 8)	/* Chip Select Rise */
#define	QSPI_SR_CSS		(0x1 << 9)	/* Chip Select Status */
#define	QSPI_SR_INSTRE		(0x1 << 10)	/* Instruction End Status */
#define	QSPI_SR_QSPIENS		(0x1 << 24)	/* QSPI Enable Status */

/* QSPI_SCR */
#define	QSPI_SCR_CPOL		(0x1 << 0)	/* Clock Polarity */
#define	QSPI_SCR_CPHA		(0x1 << 1)	/* Clock Phase */
#define	QSPI_SCR_SCBR		(0xff << 8)
#define	QSPI_SCR_SCBR_(x)	(((x) << 8) & QSPI_SCR_SCBR)	/* Serial Clock Baud Rate */
#define	QSPI_SCR_DLYBS_(x)	((x) << 16)	/* Delay Before QSCK */

/* QSPI_ICR */
#define QSPI_ICR_INST_MASK     0xff
#define QSPI_ICR_INST(inst)    ((inst) & QSPI_ICR_INST_MASK)
#define QSPI_ICR_OPT_MASK      (0xff << 16)
#define QSPI_ICR_OPT(opt)      (((opt) << 16) & QSPI_ICR_OPT_MASK)

/* QSPI_IFR */
#define	QSPI_IFR_WIDTH		(0x7 << 0)	/* Width of Instruction Code, Address, Option Code and Data */
#define		QSPI_IFR_WIDTH_SINGLE_BIT_SPI	(0x0 << 0)
#define		QSPI_IFR_WIDTH_DUAL_OUTPUT	(0x1 << 0)
#define		QSPI_IFR_WIDTH_QUAD_OUTPUT	(0x2 << 0)
#define		QSPI_IFR_WIDTH_DUAL_IO		(0x3 << 0)
#define		QSPI_IFR_WIDTH_QUAD_IO		(0x4 << 0)
#define		QSPI_IFR_WIDTH_DUAL_CMD		(0x5 << 0)
#define		QSPI_IFR_WIDTH_QUAD_CMD		(0x6 << 0)
#define QSPI_IFR_WIDTH_(x)	(((x) << 0) & QSPI_IFR_WIDTH)
#define	QSPI_IFR_INSTEN		(0x1 << 4)	/* Instruction Enable*/
#define	QSPI_IFR_ADDREN		(0x1 << 5)	/* Address Enable*/
#define	QSPI_IFR_OPTEN		(0x1 << 6)	/* Option Enable*/
#define	QSPI_IFR_DATAEN		(0x1 << 7)	/* Data Enable*/
#define	QSPI_IFR_OPTL		(0x3 << 8)	/* Option Code Length */
#define		QSPI_IFR_OPTL_1BIT		(0x0 << 8)
#define		QSPI_IFR_OPTL_2BIT		(0x1 << 8)
#define		QSPI_IFR_OPTL_4BIT		(0x2 << 8)
#define		QSPI_IFR_OPTL_8BIT		(0x3 << 8)
#define	QSPI_IFR_ADDRL		(0x1 << 10)	/* Address Length */
#define		QSPI_IFR_ADDRL_24_BIT		(0x0 << 10)
#define		QSPI_IFR_ADDRL_32_BIT		(0x1 << 10)
#define	QSPI_IFR_TFRTYPE_MEM	(0x1 << 12)
#define	QSPI_IFR_CRM		(0x1 << 14)	/* Continuous Read Mode */
#define	QSPI_IFR_NBDUM_(x)	((x) << 16)	/* Number Of Dummy Cycles */

#endif
