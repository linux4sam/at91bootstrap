/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SAMA5_L2CC_H__
#define __SAMA5_L2CC_H__

#define L2CC_IDR	0x00	/* Cache ID Register */
#define L2CC_TYPR	0x04	/* Cache Type Register */
#define L2CC_CR		0x100	/* Control Register */
#define L2CC_ACR	0x104	/* Auxiliary Control Register */
#define L2CC_TRCR	0x108	/* Tag RAM Control Register */
#define L2CC_DRCR	0x10C	/* Data RAM Control Register */
/* 0x110 ~ 0x1fc Reserved*/
#define L2CC_ECR	0x200U	/* Event Counter Control Register */
#define L2CC_ECFGR1	0x204	/* Event Counter 1 Configuration Register */
#define L2CC_ECFGR0	0x208	/* Event Counter 0 Configuration Register */
#define L2CC_EVR1	0x20C	/* Event Counter 1 Value Register */
#define L2CC_EVR0	0x210	/* Event Counter 0 Value Register */
#define L2CC_IMR	0x214	/* Interrupt Mask Register */
#define L2CC_MISR	0x218	/* Masked Interrupt Status Register */
#define L2CC_RISR	0x21C	/* Raw Interrupt Status Register */
#define L2CC_ICR	0x220	/* Interrupt Clear Register */
/* 0x224 ~72c Reserved */
#define L2CC_CSR	0x730	/* Cache Synchronization Register */
#define L2CC_IPALR	0x770	/* Invalidate Physical Address Line Register */
#define L2CC_IWR	0x77C	/* Invalidate Way Register */
#define L2CC_CPALR	0x7B0	/* Clean Physical Address Line Register */
#define L2CC_CIR	0x7B8	/* Clean Index Register */
#define L2CC_CWR	0x7BC	/* Clean Way Register */
#define L2CC_CIPALR	0x7F0	/* Clean Invalidate Physical Address Line Register */
#define L2CC_CIIR	0x7F8	/* Clean Invalidate Index Register */
#define L2CC_CIWR	0x7FC	/* Clean Invalidate Way Register */
#define L2CC_DLKR	0x900	/* Data Lockdown Register */
#define L2CC_ILKR	0x904	/* Instruction Lockdown Register */
/* 0x908 ~ 0xf3c Reserved */
#define L2CC_DCR	0xF40	/* Debug Control Register */
#define L2CC_PCR	0xF60	/* Prefetch Control Register */
#define L2CC_POWCR	0xF80	/* Power Control Register */

/*-------- L2CC_PCR : (L2CC Offset: 0xF60) Prefetch Control Register --------*/
#define L2CC_PCR_OFFSET(value)	(((value) & 0x1f) << 0)	/* Prefetch Offset */
#define L2CC_PCR_NSIDEN		(0x01 << 21)	/* Incr Double Linefill Enable */
#define L2CC_PCR_IDLEN		(0x01 << 23)	/* Incr Double Linefill Enable */
#define L2CC_PCR_PDEN		(0x01 << 24)	/* Prefetch Drop Enable */
#define L2CC_PCR_DLFWRDIS	(0x01 << 27)	/* Double Linefill on WRAP Read Disable */
#define L2CC_PCR_DATPEN		(0x01 << 28)	/* Data Prefetch Enable */
#define L2CC_PCR_INSPEN		(0x01 << 29)	/* Instruction Prefetch Enable */
#define L2CC_PCR_DLEN		(0x01 << 30)	/* Double Linefill Enable */

/*-------- L2CC_POWCR : (L2CC Offset: 0xF80) Power Control Register --------*/
#define L2CC_POWCR_STBYEN	(0x01 << 0)	/* Standby Mode enable */
#define L2CC_POWCR_DCKGATEN	(0x01 << 1)	/* Dynamic Clock Gating Enable */

#endif /* #ifndef __SAMA5_L2CC_H__ */
