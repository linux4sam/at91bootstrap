/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SAM9X7_H__
#define __SAM9X7_H__

/*
 * Peripheral identifiers/interrupts.
 */
#define AT91C_ID_FIQ			0 /**<  0 Advanced Interrupt Controller (FIQ) */
#define AT91C_ID_SYS			1 /**<  1 Logical-OR interrupt of SYSC, PMC, WDT, PIT, RSTC, RTT, RTC (SYSC) */
#define AT91C_ID_PIOA			2 /**<  2 Parallel I/O Controller A (PIOA) */
#define AT91C_ID_PIOB			3 /**<  3 Parallel I/O Controller B (PIOB) */
#define AT91C_ID_PIOC			4 /**<  4 Parallel I/O Controller C (PIOC) */
#define AT91C_ID_FLEXCOM0		5 /**<  5 Flexcom 0 (FLEXCOM0) */
#define AT91C_ID_FLEXCOM1		6 /**<  6 Flexcom 1 (FLEXCOM1) */
#define AT91C_ID_FLEXCOM2		7 /**<  7 Flexcom 2 (FLEXCOM2) */
#define AT91C_ID_FLEXCOM3		8 /**<  8 Flexcom 3 (FLEXCOM3) */
#define AT91C_ID_FLEXCOM6		9 /**<  9 Flexcom 6 (FLEXCOM6) */
#define AT91C_ID_FLEXCOM7		10 /**< 10 Flexcom 7 (FLEXCOM7) */
#define AT91C_ID_FLEXCOM8		11 /**< 11 Flexcom 8 (FLEXCOM8) */
#define AT91C_ID_SDMMC0			12 /**< 12 Secure Data Memory Card Controller 0 (SDMMC0) */
#define AT91C_ID_FLEXCOM4		13 /**< 13 Flexcom 4 (FLEXCOM4) */
#define AT91C_ID_FLEXCOM5		14 /**< 14 Flexcom 5 (FLEXCOM5) */
#define AT91C_ID_FLEXCOM9		15 /**< 15 Flexcom 9 (FLEXCOM9) */
#define AT91C_ID_FLEXCOM10		16 /**< 16 Flexcom 10 (FLEXCOM10) */
#define AT91C_ID_TC0			17 /**< 17 TC 0,1,2 (TC0) */
#define AT91C_ID_PWM			18 /**< 18 Pulse Width Modulation Controller (PWM) */
#define AT91C_ID_ADC			19 /**< 19 ADC Controller (ADC) */
#define AT91C_ID_XDMAC			20 /**< 20 Extended DMA Controller (XDMAC) */
#define AT91C_ID_MATRIX			21 /**< 21 Matrix (MATRIX) */
#define AT91C_ID_UHPHS			22 /**< 22 USB Host High Speed (UHPHS) */
#define AT91C_ID_UDPHS			23 /**< 23 USB Device High Speed (UDPHS) */
#define AT91C_ID_GMAC			24 /**< 24 Gigabit Ethernet MAC (GMAC) */
#define AT91C_ID_XLCDC			25 /**< 25 LCD Controller (XLCDC) */
#define AT91C_ID_SDMMC1			26 /**< 26 Secure Data Memory Card Controller 1 (SDMMC1) */
#define AT91C_ID_SSC			28 /**< 28 Synchronous Serial Controller (SSC) */
#define AT91C_ID_MCAN0_INT0		29 /**< 29 Master CAN 0 (MCAN0_INT0) */
#define AT91C_ID_MCAN1_INT0		30 /**< 30 Master CAN 1 (MCAN1_INT0) */
#define AT91C_ID_IRQ			31 /**< 31 Advanced Interrupt Controller (IRQ) */
#define AT91C_ID_FLEXCOM11		32 /**< 32 Flexcom 11 (FLEXCOM11) */
#define AT91C_ID_FLEXCOM12		33 /**< 33 Flexcom 12 (FLEXCOM12) */
#define AT91C_ID_I2SMCC			34 /**< 34 I2S Multi Channel Controller (I2SMCC) */
#define AT91C_ID_QSPI0			35 /**< 35 Quad I/O SPI Controller (QSPI) */
#define AT91C_ID_GFX2D			36 /**< 36 2D Graphic Controller (GFX2D) */
#define AT91C_ID_PIT64B0		37 /**< 37 64-b Timer 0 (PIT64B0) */
#define AT91C_ID_TRNG			38 /**< 38 True Random Number Generator (TRNG) */
#define AT91C_ID_AES			39 /**< 39 Advanced Encryption Standard (AES) */
#define AT91C_ID_TDES			40 /**< 40 Triple Data Encryption Standard (TDES) */
#define AT91C_ID_SHA			41 /**< 41 Secure Hash Algorithm (SHA) */
#define AT91C_ID_CLASSD			42 /**< 42 CLASS D Controller (CLASSD) */
#define AT91C_ID_ISC			43 /**< 43 Camera Interface (ISC) */
#define AT91C_ID_PIOD			44 /**< 44 Parallel I/O Controller D (PIOD) */
#define AT91C_ID_TC1			45 /**< 45 TC 3,4,5 (TC1) */
#define AT91C_ID_OTPC			46 /**< 46 OTP Controller (OTPC) */
#define AT91C_ID_DBGU			47 /**< 47 DBGU (DBGU) */
#define AT91C_ID_PMECC			48 /**< 48 logical-OR interrupt of PMECC and PMERRLOC (PMECC) */
#define AT91C_ID_MPDDRC			49 /**< 49 logical-OR interrupt of MPDDRC and SMC (MPDDRC) */
#define AT91C_ID_UTMI			50 /**< 50 UTMI (UTMI) */
#define AT91C_ID_I3C			51 /**< 51 I3C Master Controller (I3C) */
#define AT91C_ID_CSI2DC			52 /**< 52 CSI to Demultiplexer Controller (CSI2DC) */
#define AT91C_ID_CSI4L			53 /**< 53 Camera Serial Interface 2 4-Lanes (CSI4L) */
#define AT91C_ID_DSI4L			54 /**< 54 Display Serial Interface 4-Lanes (DSI4L) */
#define AT91C_ID_MIPIPHY		55 /**< 55 MIPI DPHY interface (MIPIPHY) */
#define AT91C_ID_LVDSC			56 /**< 56 Display Serial Interface between XLCDC and LVDS interface (LVDSC) */
#define AT91C_ID_LVDSPHY		57 /**< 57 LVDS PHY (LVDSPHY) */
#define AT91C_ID_PIT64B1		58 /**< 58 64-b Timer 1 (PIT64B1) */
#define AT91C_ID_PUF			59 /**< 59 HW PUF QuiddiKey IP (PUF) */
#define AT91C_ID_GMAC_Q1		60 /**< 60 GMAC Queue 1 Interrupt signal toggled on a DMA write to the first word of each DMA data buffer associated with queue 1 (GMAC_Q1) */
#define AT91C_ID_GMAC_Q2		61 /**< 61 GMAC Queue 2 Interrupt signal toggled on a DMA write to the first word of each DMA data buffer associated with queue 2 (GMAC_Q2) */
#define AT91C_ID_GMAC_Q3		62 /**< 62 GMAC Queue 3 Interrupt signal toggled on a DMA write to the first word of each DMA data buffer associated with queue 3 (GMAC_Q3) */
#define AT91C_ID_GMAC_Q4		63 /**< 63 GMAC Queue 4 Interrupt signal toggled on a DMA write to the first word of each DMA data buffer associated with queue 4 (GMAC_Q4) */
#define AT91C_ID_GMAC_Q5		64 /**< 64 GMAC Queue 5 Interrupt signal toggled on a DMA write to the first word of each DMA data buffer associated with queue 5 (GMAC_Q5) */
#define AT91C_ID_GMAC_EMAC		65 /**< 65 Gigabit Ethernet MAC - Express MAC (GMAC_EMAC) */
#define AT91C_ID_GMAC_MMSL		66 /**< 66 Gigabit Ethernet MAC - Mac Merge SubLayer (GMAC_MMSL) */
#define AT91C_ID_GMAC_TSU		67 /**< 67 Gigabit Ethernet MAC - Time Stamp Unit (GMAC_TSU) */
#define AT91C_ID_MCAN0_INT1		68 /**< 68 Master CAN 0 interrupt 1 (MCAN0_INT1) */
#define AT91C_ID_MCAN1_INT1		69 /**< 69 Master CAN 1 interrupt 1 (MCAN1_INT1) */

/*
 * User Peripherals physical base addresses
 */
#define AT91C_BASE_FLEXCOM4	0xf0000000
#define AT91C_BASE_FLEXCOM5	0xf0004000
#define AT91C_BASE_XDMAC	0xf0008000
#define AT91C_BASE_SSC		0xf0010000
#define AT91C_BASE_QSPI0	0xf0014000
#define AT91C_BASE_GFX2D	0xf0018000
#define AT91C_BASE_I2SMCC	0xf001c000
#define AT91C_BASE_FLEXCOM11	0xf0020000
#define AT91C_BASE_FLEXCOM12	0xf0024000
#define AT91C_BASE_PIT64B0	0xf0028000
#define AT91C_BASE_SHA		0xf002c000
#define AT91C_BASE_TRNG		0xf0030000
#define AT91C_BASE_AES		0xf0034000
#define AT91C_BASE_TDES		0xf0038000
#define AT91C_BASE_CLASSD	0xf003c000
#define AT91C_BASE_PIT64B1	0xf0040000
#define AT91C_BASE_MCAN0	0xf8000000
#define AT91C_BASE_MCAN1	0xf8004000
#define AT91C_BASE_TC0		0xf8008000
#define AT91C_BASE_TC1		0xf800c000
#define AT91C_BASE_FLEXCOM6	0xf8010000
#define AT91C_BASE_FLEXCOM7	0xf8014000
#define AT91C_BASE_FLEXCOM8	0xf8018000
#define AT91C_BASE_FLEXCOM0	0xf801c000
#define AT91C_BASE_FLEXCOM1	0xf8020000
#define AT91C_BASE_FLEXCOM2	0xf8024000
#define AT91C_BASE_FLEXCOM3	0xf8028000
#define AT91C_BASE_GMAC		0xf802c000
#define AT91C_BASE_PUF		0xf8030000
#define AT91C_BASE_PWM		0xf8034000
#define AT91C_BASE_XLCD		0xf8038000
#define AT91C_BASE_UDPH		0xf803c000
#define AT91C_BASE_FLEXCOM9	0xf8040000
#define AT91C_BASE_FLEXCOM10	0xf8044000
#define AT91C_BASE_ISC		0xf8048000
#define AT91C_BASE_ADC		0xf804c000
#define AT91C_BASE_SFR		0xf8050000
#define AT91C_BASE_DSI4L	0xf8054000
#define AT91C_BASE_CSI4L	0xf8058000
#define AT91C_BASE_CSI2DC	0xf805c000
#define AT91C_BASE_LVDSC	0xf8060000

/*
 * System Peripherals physical base addresses.
 */
#define AT91C_BASE_MATRIX	0xffffde00u
#define AT91C_BASE_PMECC	0xffffe000u
#define AT91C_BASE_PMERRLOC	0xffffe600u
#define AT91C_BASE_MPDDRC	0xffffe800u
#define AT91C_BASE_SMC		0xffffea00u
#define AT91C_BASE_AIC		0xfffff100u
#define AT91C_BASE_DBGU		0xfffff200u
#define AT91C_BASE_PIOA		0xfffff400u
#define AT91C_BASE_PIOB		0xfffff600u
#define AT91C_BASE_PIOC		0xfffff800u
#define AT91C_BASE_PIOD		0xfffffa00u
#define AT91C_BASE_PMC		0xfffffc00u
#define AT91C_BASE_RSTC		0xfffffe00u
#define AT91C_BASE_SHDWC	0xfffffe10u
#define AT91C_BASE_RTT		0xfffffe20u
#define AT91C_BASE_PITC		0xfffffe40u
#define AT91C_BASE_SCKCR	0xfffffe50u
#define AT91C_BASE_BSC		0xfffffe54u
#define AT91C_BASE_GPBR		0xfffffe60u
#define AT91C_BASE_RTC		0xfffffea8u
#define AT91C_BASE_SYSCWP	0xfffffedcu
#define AT91C_BASE_WDT		0xffffff80u

/*
 * Internal Memory common on all these SoCs
 */
#define AT91C_BASE_BOOT		0x00000000	/* Boot mapped area */
#define AT91C_BASE_ROM		0x00100000	/* ECC ROM base address */
#define AT91C_BASE_SRAM		0x00300000	/* SRAM */
#define AT91C_BASE_SRAM1	0x00400000	/* SRAM1 */
#define AT91C_BASE_UDPHS_RAM	0x00500000	/* USB Device controller */
#define AT91C_BASE_UHPHS_OHCI	0x00600000	/* UHPHS_OHCI Base address*/
#define AT91C_BASE_UHPHS_EHCI	0x00700000	/* UHPHS_EHCI Base address*/
#define AT91C_QSPI0_MEM_SIZE	0x10000000

/* Internal ROM PMECC Galois Field Tables offsets */
#define PMECC_GF_TABLE_512_ALPHA_OFFSET		0x4000
#define PMECC_GF_TABLE_512_INDEX_OFFSET		0x0000
#define PMECC_GF_TABLE_1024_ALPHA_OFFSET	0x10000
#define PMECC_GF_TABLE_1024_INDEX_OFFSET	0x8000

/*
 * External memory
 */
#define AT91C_BASE_DDRCS	0x20000000
#define AT91C_BASE_CS0		0x10000000	/* typically NOR */
#define AT91C_BASE_CS1		0x20000000	/* MPDDRC / SDRAMC */
#define AT91C_BASE_CS2		0x30000000	/* typically NAND */
#define AT91C_BASE_QSPI0_MEM	0x60000000
#define AT91C_BASE_SDHC0	0x80000000
#define AT91C_BASE_SDHC1	0x90000000
#define AT91C_BASE_CSI2DC_MEM	0xd0000000

#define AT91C_NUM_PIO		4
#define AT91C_NUM_TWI		0
#define	AT91C_NUM_FLEXCOM	13

/*
 * SoC specific defines
 */
#define AT91C_CPU_NAME		"SAM9X7"

#endif	/* #ifndef __SAM9X7_H__ */
