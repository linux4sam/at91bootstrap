/*
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SAM9X60_H__
#define __SAM9X60_H__

/*
 * Peripheral identifiers/interrupts.
 */
#define AT91C_ID_FIQ		0	/* Advanced Interrupt Controller FIQ */
#define AT91C_ID_SYS		1	/* System Controller Interrupt */
#define AT91C_ID_PIOA		2	/* Parallel I/O Controller A and B */
#define AT91C_ID_PIOB		3	/* Parallel I/O Controller A and B */
#define AT91C_ID_PIOC		4	/* Parallel I/O Controller C and D */
#define AT91C_ID_FLEXCOM0	5	/* FLEXCOM 0 */
#define AT91C_ID_FLEXCOM1	6	/* FLEXCOM 1 */
#define AT91C_ID_FLEXCOM2	7	/* FLEXCOM 2 */
#define AT91C_ID_FLEXCOM3	8	/* FLEXCOM 3 */
#define AT91C_ID_FLEXCOM6	9	/* FLEXCOM 6 */
#define AT91C_ID_FLEXCOM7	10	/* FLEXCOM 7 */
#define AT91C_ID_FLEXCOM8	11	/* FLEXCOM 8 */
#define AT91C_ID_SDMMC0		12	/* SDMMC 0 */
#define AT91C_ID_FLEXCOM4	13	/* FLEXCOM 4 */
#define AT91C_ID_FLEXCOM5	14	/* FLEXCOM 5 */
#define AT91C_ID_FLEXCOM9	15	/* FLEXCOM 9 */
#define AT91C_ID_FLEXCOM10	16	/* FLEXCOM 10 */
#define AT91C_ID_TCB		17	/* Timer Counter 0, 1, 2, 3, 4, 5 */
#define AT91C_ID_PWM		18	/* Pulse Width Modulation Controller */
#define AT91C_ID_ADC		19	/* ADC Controller */
#define AT91C_ID_XDMAC		20	/* XDMA Controller */
#define AT91C_ID_MATRIX		21	/* SAM9X60 Matrix (MATRIX) */
#define AT91C_ID_UHPHS		22	/* USB Host High Speed */
#define AT91C_ID_UDPHS		23	/* USB Device High Speed */
#define AT91C_ID_EMAC		24	/* Ethernet MAC 0 */
#define AT91C_ID_LCDC		25	/* LCD or Image Sensor Interface */
#define AT91C_ID_SDMMC1		26	/* SDMMC 1 */
#define AT91C_ID_EMAC1		27	/* Ethernet MAC 1 */
#define AT91C_ID_SSC		28	/* Serial Synchronous Controller */
#define AT91C_ID_CAN0		29	/* CAN Controller 0 */
#define AT91C_ID_CAN1		30	/* CAN Controller 1 */
#define AT91C_ID_IRQ		31	/* Advanced Interrupt Controller IRQ */
#define AT91C_ID_FLEXCOM11	32
#define AT91C_ID_FLEXCOM12	33
#define AT91C_ID_I2SMCC		34
#define AT91C_ID_QSPI0		35
#define AT91C_ID_GFX2D		36
#define AT91C_ID_PIT64B		37
#define AT91C_ID_TRNG		38
#define AT91C_ID_AES		39
#define AT91C_ID_TDES		40
#define AT91C_ID_SHA		41
#define AT91C_ID_CLASSD		42
#define AT91C_ID_ISI		43
#define AT91C_ID_PIOD		44
#define AT91C_ID_TC1		45
#define AT91C_ID_OPTC		46
#define AT91C_ID_DBGU		47
#define AT91C_ID_PMECC		48
#define AT91C_ID_MPDDRC		49
#define AT91C_ID_SDRAMC		49	/* shared PID with MPDDRC */
#define AT91C_ID_UTMI		50

/*
 * User Peripherals physical base addresses
 */
#define AT91C_BASE_XDMAC	0xf0008000
#define AT91C_BASE_SSC		0xf0010000
#define AT91C_BASE_QSPI0	0xf0014000
#define AT91C_BASE_GFX2D	0xf0018000
#define AT91C_BASE_I2SMCC	0xf001C000
#define AT91C_BASE_PIT64B	0xf0028000
#define AT91C_BASE_SHA		0xf002C000
#define AT91C_BASE_TRNG		0xf0030000
#define AT91C_BASE_AES		0xf0034000
#define AT91C_BASE_TDES		0xf0038000
#define AT91C_BASE_CLASSD	0xf003C000
#define AT91C_BASE_CAN0		0xf8000000
#define AT91C_BASE_CAN1		0xf8004000
#define AT91C_BASE_TC0		0xf8008000
#define AT91C_BASE_TC3		0xf800c000
#define AT91C_BASE_EMAC0	0xf802c000
#define AT91C_BASE_EMAC1	0xf8030000
#define AT91C_BASE_PWMC		0xf8034000
#define AT91C_BASE_LCDC		0xf8038000
#define AT91C_BASE_UDPHS	0xf803c000
#define AT91C_BASE_ADC		0xf804c000
#define AT91C_BASE_SFR		0xf8050000
#define AT91C_BASE_FLEXCOM0	0xf801C000
#define AT91C_BASE_FLEXCOM1	0xf8020000
#define AT91C_BASE_FLEXCOM2	0xf8024000
#define AT91C_BASE_FLEXCOM3	0xf8028000
#define AT91C_BASE_FLEXCOM4	0xf0000000
#define AT91C_BASE_FLEXCOM5	0xf0004000
#define AT91C_BASE_FLEXCOM6	0xf8010000
#define AT91C_BASE_FLEXCOM7	0xf8014000
#define AT91C_BASE_FLEXCOM8	0xf8018000
#define AT91C_BASE_FLEXCOM9	0xf8040000
#define AT91C_BASE_FLEXCOM10	0xf8044000
#define AT91C_BASE_FLEXCOM11	0xf0020000
#define AT91C_BASE_FLEXCOM12	0xf0024000

/*
 * System Peripherals physical base addresses.
 */
#define AT91C_BASE_MATRIX	0xffffde00
#define AT91C_BASE_PMECC	0xffffe000
#define AT91C_BASE_PMERRLOC	0xffffe600
#define AT91C_BASE_MPDDRC	0xffffe800
#define AT91C_BASE_SMC		0xffffea00
#define AT91C_BASE_SDRAMC	0xffffec00
/* reserved 0xffffee00 */
#define AT91C_BASE_AIC		0xfffff100
#define AT91C_BASE_DBGU		0xfffff200
#define AT91C_BASE_PIOA		0xfffff400
#define AT91C_BASE_PIOB		0xfffff600
#define AT91C_BASE_PIOC		0xfffff800
#define AT91C_BASE_PIOD		0xfffffa00
#define AT91C_BASE_PMC		0xfffffc00
#define AT91C_BASE_RSTC		0xfffffe00
#define AT91C_BASE_SHDC		0xfffffe10
#define AT91C_BASE_PITC		0xfffffe40
#define AT91C_BASE_SCKCR	0xfffffe50
#define AT91C_BASE_BSCR		0xfffffe54
#define AT91C_BASE_GPBR		0xfffffe60
#define AT91C_BASE_RTC		0xfffffeA8
#define AT91C_BASE_WDT		0xffffff80

/*
 * Internal Memory common on all these SoCs
 */
#define AT91C_BASE_BOOT		0x00000000      /* Boot mapped area */
#define AT91C_BASE_ROM		0x00100000      /* ECC ROM base address */
#define AT91C_BASE_SRAM		0x00300000      /* SRAM */
#define AT91C_BASE_SRAM1	0x00400000      /* SRAM1 */
#define AT91C_BASE_UDPHS_RAM	0x00500000      /* USB Device controller */
#define AT91C_BASE_UHPHS_OHCI	0x00600000      /* UHPHS_OHCI Base address*/
#define AT91C_BASE_UHPHS_EHCI	0x00700000      /* UHPHS_EHCI Base address*/

/* Internal ROM PMECC Galois Field Tables offsets */
#define PMECC_GF_TABLE_512_ALPHA_OFFSET		0x4000
#define PMECC_GF_TABLE_512_INDEX_OFFSET		0x0000
#define PMECC_GF_TABLE_1024_ALPHA_OFFSET	0x10000
#define PMECC_GF_TABLE_1024_INDEX_OFFSET	0x8000

/*
 * External memory
 */
#define AT91C_BASE_DDRCS        0x20000000
#define AT91C_BASE_CS0          0x10000000      /* typically NOR */
#define AT91C_BASE_CS1          0x20000000      /* MPDDRC / SDRAMC */
#define AT91C_BASE_CS2          0x30000000
#define AT91C_BASE_CS3          0x40000000      /* typically NAND */
#define AT91C_BASE_CS4          0x50000000
#define AT91C_BASE_CS5          0x60000000
#define AT91C_BASE_QSPI0_MEM    0x70000000
#define AT91C_BASE_SDHC0        0x80000000
#define AT91C_BASE_SDHC1        0x90000000

#define AT91C_QSPI0_MEM_SIZE	0x10000000

#define AT91C_NUM_PIO		4
#define AT91C_NUM_TWI		0
#define	AT91C_NUM_FLEXCOM	13

/*
 * SoC specific defines
 */
#define AT91C_CPU_NAME         "SAM9X60"

#endif	/* #ifndef __SAM9X60_H__ */
