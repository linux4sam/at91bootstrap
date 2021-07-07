/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef _PUBL_REGS_H_
#define _PUBL_REGS_H_

#ifndef __I
#define __I  volatile const /**< Defines 'read-only'  permissions */
#endif
#ifndef __O
#define __O  volatile       /**< Defines 'write-only' permissions */
#endif
#ifndef __IO
#define __IO volatile       /**< Defines 'read/write' permissions */
#endif

/*
 * Synopsys PUBL DDR PHY register map configuration.
 */

struct publ_regs {
	/* Revision Identification Register */
	__I  unsigned int PUBL_RIDR;
	/* PHY Initialization Register */
	__IO unsigned int PUBL_PIR;
	/* PHY General Configuration Register */
	__IO unsigned int PUBL_PGCR;
	/* PHY General Status Register */
	__IO unsigned int PUBL_PGSR;
	/* PHY DLL General Control Register */
	__IO unsigned int PUBL_DLLGCR;
	/* Unused */
	__I  unsigned int Reserved1;
	/* PHY Timing Register 0 */
	__IO unsigned int PUBL_PTR0;
	/* PHY Timing Register 0 */
	__IO unsigned int PUBL_PTR1;
	/* PHY Timing Register 2 */
	__IO unsigned int PUBL_PTR2;
	/* AC I/O Configuration Register */
	__IO unsigned int PUBL_ACIOCR;
	/* DATX8 Common Configuration Register */
	__IO unsigned int PUBL_DXCCR;
	/* DDR System General Configuration Register */
	__IO unsigned int PUBL_DSGCR;
	/* DRAM Config register */
	__IO unsigned int PUBL_DCR;
	/* DRAM Timing Parameters Register 0 */
	__IO unsigned int PUBL_DTPR0;
	/* DRAM Timing Parameters Register 1 */
	__IO unsigned int PUBL_DTPR1;
	/* DRAM Timing Parameters Register 2 */
	__IO unsigned int PUBL_DTPR2;
	/* DRAM Mode Register 0 */
	__IO unsigned int PUBL_MR0;
	/* DRAM Mode Register 1 */
	__IO unsigned int PUBL_MR1;
	/* DRAM Mode Register 2 */
	__IO unsigned int PUBL_MR2;
	/* DRAM Mode Register 3 */
	__IO unsigned int PUBL_MR3;
	/* ODT Configuration Register */
	__IO unsigned int PUBL_ODTCR;
	/* Data Training Address Register */
	__IO unsigned int PUBL_DTAR;
	/* Data Training Address Register 0 */
	__IO unsigned int PUBL_DTDR0;
	/* Data Training Address Register 1 */
	__IO unsigned int PUBL_DTDR1;
	/* Unused */
	__I unsigned int Reserved2[24];
	__IO unsigned int PUBL_DCUAR;
	__IO unsigned int PUBL_DCUDR;
	__IO unsigned int PUBL_DCURR;
	__I unsigned int Reserved3[3];
	__I unsigned int PUBL_DCUSR0;
	__I unsigned int PUBL_DCUSR1;
	/* Unused */
	__I unsigned int Reserved4[40];
	/* ZQ 0 Impedance Control Register 0 */
	__IO unsigned int PUBL_ZQ0CR0;
	/* ZQ 0 Impedance Control Register 1 */
	__IO unsigned int PUBL_ZQ0CR1;
	__IO unsigned int PUBL_ZQ0SR0;
};

/* PUBL register helpers
 * {
 */
/* -------- PUBL_PIR : (PUBL Offset: 0x4) PHY Initialization Register -------- */
/* Initialization Trigger */
#define PUBL_PIR_INIT				(0x1UL << 0)
/* DLL Lock */
#define PUBL_PIR_DLLLOCK			(0x1UL << 2)
/* Impedance Calibrate */
#define PUBL_PIR_ZCAL				(0x1UL << 3)
/* Read DQS Training */
#define PUBL_PIR_QSTRN				(0x1UL << 7)
/* RV Training */
#define PUBL_PIR_RVTRN				(0x1UL << 8)
/* Controller DRAM Init */
#define PUBL_PIR_CTLDINIT			(0x1UL << 18)
/* Impedance calibration bypass */
#define PUBL_PIR_ZCALBYP			(0x1UL << 30)

/* -------- PUBL_PGCR : (PUBL Offset: 0x8) General Config Register -------- */
/* ITM DDR Mode */
#define PUBL_PGCR_ITMDMD			(0x1UL << 0)
/* DQS Gating Configuration */
#define PUBL_PGCR_DQSCFG			(0x1UL << 1)
/* DQS Drift Compensation */
#define PUBL_PGCR_DFTCMP			(0x1UL << 2)
/* CK Enable */
#define PUBL_PGCR_CKEN_MASK			0x7UL
#define PUBL_PGCR_CKEN_POS			9
#define PUBL_PGCR_CKEN(v)			(((v) & PUBL_PGCR_CKEN_MASK) \
						<< PUBL_PGCR_CKEN_POS)
/* CK Disable Value */
#define PUBL_PGCR_CKDV_MASK			0x3UL
#define PUBL_PGCR_CKDV_POS			12
#define PUBL_PGCR_CKDV(v)			(((v) & PUBL_PGCR_CKDV_MASK) \
						<< PUBL_PGCR_CKDV_POS)
/* Rank Enable */
#define PUBL_PGCR_RANKEN_MASK			0xFUL
#define PUBL_PGCR_RANKEN_POS			18
#define PUBL_PGCR_RANKEN(v)			(((v) & PUBL_PGCR_RANKEN_MASK) \
						<< PUBL_PGCR_RANKEN_POS)
/* Impedance Clock Divider Select */
#define PUBL_PGCR_ZCKSEL_MASK			0x3UL
#define PUBL_PGCR_ZCKSEL_POS			22
#define PUBL_PGCR_ZCKSEL(v)			(((v) & PUBL_PGCR_ZCKSEL_MASK) \
						<< PUBL_PGCR_ZCKSEL_POS)
/* Power Down Disabled Byte */
#define PUBL_PGCR_PDDISDX			(0x1UL << 24)

/* -------- PUBL_PGSR : (PUBL Offset: 0xC) General Status Register -------- */
/* Initialization done */
#define PUBL_PGSR_IDONE				(0x1UL << 0)
/* DQS Gate Training Error */
#define PUBL_PGSR_DTERR				(0x1UL << 5)
/* DQS Drift Error */
#define PUBL_PGSR_DTIERR			(0x1UL << 6)
/* Read Valid Training Error */
#define PUBL_PGSR_RVERR				(0x1UL << 8)
/* Read Valid Training Intermittent Error */
#define PUBL_PGSR_RVEIRR			(0x1UL << 9)

/* -------- PUBL_PTR0 : (PUBL Offset: 0x18) PHY Timing Register 0 -------- */
/* DLL Soft Reset Time */
#define PUBL_PTR0_TDLLSRST_MASK			0x3FUL
#define PUBL_PTR0_TDLLSRST_POS			0
#define PUBL_PTR0_TDLLSRST(v)			(((v) & PUBL_PTR0_TDLLSRST_MASK) \
						<< PUBL_PTR0_TDLLSRST_POS)
/* DLL Lock Time */
#define PUBL_PTR0_TDLLLOCK_MASK			0xFFFUL
#define PUBL_PTR0_TDLLLOCK_POS			6
#define PUBL_PTR0_TDLLLOCK(v)			(((v) & PUBL_PTR0_TDLLLOCK_MASK) \
						<< PUBL_PTR0_TDLLLOCK_POS)
/* ITM Soft Reset Time */
#define PUBL_PTR0_TITMSRST_MASK			0xFUL
#define PUBL_PTR0_TITMSRST_POS			18
#define PUBL_PTR0_TITMSRST(v)			(((v) & PUBL_PTR0_TITMSRST_MASK) \
						<< PUBL_PTR0_TITMSRST_POS)

/* -------- PUBL_PTR1 : (PUBL Offset: 0x1C) PHY Timing Register 1 -------- */
/* DRAM Init Time 0 */
#define PUBL_PTR1_TDINIT0_MASK			0x7FFFFUL
#define PUBL_PTR1_TDINIT0_POS			0
#define PUBL_PTR1_TDINIT0(v)			(((v) & PUBL_PTR1_TDINIT0_MASK) \
						<< PUBL_PTR1_TDINIT0_POS)
/* DRAM Init Time 1 */
#define PUBL_PTR1_TDINIT1_MASK			0xFFUL
#define PUBL_PTR1_TDINIT1_POS			19
#define PUBL_PTR1_TDINIT1(v)			(((v) & PUBL_PTR1_TDINIT1_MASK) \
						<< PUBL_PTR1_TDINIT1_POS)

/* -------- PUBL_PTR2 : (PUBL Offset: 0x20) PHY Timing Register 2 -------- */
/* DRAM Init Time 2 */
#define PUBL_PTR2_TDINIT2_MASK			0x1FFFFUL
#define PUBL_PTR2_TDINIT2_POS			0
#define PUBL_PTR2_TDINIT2(v)			(((v) & PUBL_PTR2_TDINIT2_MASK) \
						<< PUBL_PTR2_TDINIT2_POS)
/* DRAM Init Time 3*/
#define PUBL_PTR2_TDINIT3_MASK			0x3FFUL
#define PUBL_PTR2_TDINIT3_POS			17
#define PUBL_PTR2_TDINIT3(v)			(((v) & PUBL_PTR2_TDINIT3_MASK) \
						<< PUBL_PTR2_TDINIT3_POS)

/* -------- PUBL_DXCCR : (PUBL Offset: 0x28) DATX8 Common Configuration Register -------- */
/* DQS Resistor */
#define PUBL_DXCCR_DQSRES_POS			4
#define PUBL_DXCCR_DQSRES_688OHM		(1UL << PUBL_DXCCR_DQSRES_POS)
/* DQS# Resistor */
#define PUBL_DXCCR_DQSNRES_POS			8
#define PUBL_DXCCR_DQSNRES_688OHM                (1UL << PUBL_DXCCR_DQSNRES_POS)
#define PUBL_DXCCR_DQSNRES_PU			(1UL << PUBL_DXCCR_DQSNRES_POS << 3)

/* -------- PUBL_DSGCR : (PUBL Offset: 0x2C) System General Configuration Register -------- */
/* PHY Update Request Enable */
#define PUBL_DSGCR_PUREN			(1UL << 0)
/* Byte Disable Enable */
#define PUBL_DSGCR_BDISEN			(1UL << 1)
/* Impedance Update Enable */
#define PUBL_DSGCR_ZUEN				(1UL << 2)
/* Low power IO power down */
#define PUBL_DSGCR_LPIOPD			(1UL << 3)
/* Low power DLL Power Down */
#define PUBL_DSGCR_LPDLLPD			(1UL << 4)
/* DQS Gating Extension */
#define PUBL_DSGCR_DQSGX_MASK			0x3UL
#define PUBL_DSGCR_DQSGX_POS			5
#define PUBL_DSGCR_DQSGX(v)			(((v) & PUBL_DSGCR_DQSGX_MASK) \
						<< PUBL_DSGCR_DQSGX_POS)
/* DQS Gate Early */
#define PUBL_DSGCR_DQSGE_MASK			0x3UL
#define PUBL_DSGCR_DQSGE_POS			8
#define PUBL_DSGCR_DQSGE(v)			(((v) & PUBL_DSGCR_DQSGE_MASK) \
						<< PUBL_DSGCR_DQSGE_POS)
/* No Bubbles */
#define PUBL_DSGCR_NOBUB			(1UL << 11)
/* Fixed Read Latency */
#define PUBL_DSGCR_FXDLAT			(1UL << 12)
/* Non-lpddr2-lpddr3 Output Enable */
#define PUBL_DSGCR_NL2OE			(1UL << 25)
/* SDRAM TPD Power Down Driver */
#define PUBL_DSGCR_TPDOE			(1UL << 27)
/* SDRAM CK Output Enable */
#define PUBL_DSGCR_CKOE				(1UL << 28)
/* SDRAM ODT Output Enable */
#define PUBL_DSGCR_ODTOE			(1UL << 29)
/* SDRAM Reset Output Enable */
#define PUBL_DSGCR_RSTOE			(1UL << 30)
/* SDRAM CKE Output Enable */
#define PUBL_DSGCR_CKEOE			(1UL << 31)

/* -------- PUBL_DCR : (PUBL Offset: 0x30) DRAM Config Register -------- */
/* DDRMD : DDR Mode */
#define PUBL_DCR_DDRMD_MASK			0x7UL
#define PUBL_DCR_DDRMD_POS			0
#define PUBL_DCR_DDRMD_DDR3			((0x3UL & PUBL_DCR_DDRMD_MASK) \
						 << PUBL_DCR_DDRMD_POS)
#define PUBL_DCR_DDRMD_DDR2			((0x2UL & PUBL_DCR_DDRMD_MASK) \
						 << PUBL_DCR_DDRMD_POS)
#define PUBL_DCR_DDRMD_LPDDR2			((0x4UL & PUBL_DCR_DDRMD_MASK) \
						 << PUBL_DCR_DDRMD_POS)
#define PUBL_DCR_DDRMD_LPDDR3			((0x5UL & PUBL_DCR_DDRMD_MASK) \
						 << PUBL_DCR_DDRMD_POS)
/* DDR8BNK: DDR 8 Banks */
#define PUBL_DCR_DDRMD_DDR8BNK			(0x1UL << 3)

/* LPDDR2 TYPE S4 or S2 */
#define PUBL_DCR_DDRTYPE_S4			(0x0 << 8)
#define PUBL_DCR_DDRTYPE_S2			(0x1 << 8)

/* -------- PUBL_DTPR0 : (PUBL Offset: 0x34) DRAM Timing Parameters Register 0  -------- */
/* tMRD */
#define PUBL_DTPR0_TMRD_MASK			0x3UL
#define PUBL_DTPR0_TMRD_POS			0
#define PUBL_DTPR0_TMRD(v)			(((v) & PUBL_DTPR0_TMRD_MASK) \
						 << PUBL_DTPR0_TMRD_POS)
/* tRTP */
#define PUBL_DTPR0_TRTP_MASK			0x7UL
#define PUBL_DTPR0_TRTP_POS			2
#define PUBL_DTPR0_TRTP(v)			(((v) & PUBL_DTPR0_TRTP_MASK) \
						 << PUBL_DTPR0_TRTP_POS)
/* tWTR */
#define PUBL_DTPR0_TWTR_MASK			0x7UL
#define PUBL_DTPR0_TWTR_POS			5
#define PUBL_DTPR0_TWTR(v)			(((v) & PUBL_DTPR0_TWTR_MASK) \
						 << PUBL_DTPR0_TWTR_POS)
/* tRP */
#define PUBL_DTPR0_TRP_MASK			0xFUL
#define PUBL_DTPR0_TRP_POS			8
#define PUBL_DTPR0_TRP(v)			(((v) & PUBL_DTPR0_TRP_MASK) \
						 << PUBL_DTPR0_TRP_POS)
/* tRCD */
#define PUBL_DTPR0_TRCD_MASK			0xFUL
#define PUBL_DTPR0_TRCD_POS			12
#define PUBL_DTPR0_TRCD(v)			(((v) & PUBL_DTPR0_TRCD_MASK) \
						 << PUBL_DTPR0_TRCD_POS)
/* tRAS */
#define PUBL_DTPR0_TRAS_MASK			0x1FUL
#define PUBL_DTPR0_TRAS_POS			16
#define PUBL_DTPR0_TRAS(v)			(((v) & PUBL_DTPR0_TRAS_MASK) \
						 << PUBL_DTPR0_TRAS_POS)
/* tRRD */
#define PUBL_DTPR0_TRRD_MASK			0xFUL
#define PUBL_DTPR0_TRRD_POS			21
#define PUBL_DTPR0_TRRD(v)			(((v) & PUBL_DTPR0_TRRD_MASK) \
						 << PUBL_DTPR0_TRRD_POS)
/* tRC */
#define PUBL_DTPR0_TRC_MASK			0x3FUL
#define PUBL_DTPR0_TRC_POS			25
#define PUBL_DTPR0_TRC(v)			(((v) & PUBL_DTPR0_TRC_MASK) \
						 << PUBL_DTPR0_TRC_POS)
/* tCCD */
#define PUBL_DTPR0_TCCD				(1UL << 31)

/* -------- PUBL_DTPR1 : (PUBL Offset: 0x38) DRAM Timing Parameters Register 1  -------- */
/* ODT turn-off/turn-on delays */
#define PUBL_DTPR1_TAOND_MASK			0x3UL
#define PUBL_DTPR1_TAOND_POS			0
#define PUBL_DTPR1_TAOND(v)			(((v) & PUBL_DTPR1_TAOND_MASK) \
						<< PUBL_DTPR1_TAOND_POS)

/* tFAW */
#define PUBL_DTPR1_TFAW_MASK			0x3FUL
#define PUBL_DTPR1_TFAW_POS			3
#define PUBL_DTPR1_TFAW(v)			(((v) & PUBL_DTPR1_TFAW_MASK) \
						<< PUBL_DTPR1_TFAW_POS)

/* tMOD */
#define PUBL_DTPR1_TMOD_MASK			0x3UL
#define PUBL_DTPR1_TMOD_POS			9
#define PUBL_DTPR1_TMOD(v)			(((v) & PUBL_DTPR1_TMOD_MASK) \
						<< PUBL_DTPR1_TMOD_POS)
/* tRFC */
#define PUBL_DTPR1_TRFC_MASK			0xFFUL
#define PUBL_DTPR1_TRFC_POS			16
#define PUBL_DTPR1_TRFC(v)			(((v) & PUBL_DTPR1_TRFC_MASK) \
						<< PUBL_DTPR1_TRFC_POS)
/* tDQSCKMIN */
#define PUBL_DTPR1_TDQSCKMIN_MASK		0x7UL
#define PUBL_DTPR1_TDQSCKMIN_POS		24
#define PUBL_DTPR1_TDQSCKMIN(v)			(((v) & PUBL_DTPR1_TDQSCKMIN_MASK) \
						<< PUBL_DTPR1_TDQSCKMIN_POS)
/* tDQSCKMAX */
#define PUBL_DTPR1_TDQSCKMAX_MASK		0x7UL
#define PUBL_DTPR1_TDQSCKMAX_POS		27
#define PUBL_DTPR1_TDQSCKMAX(v)			(((v) & PUBL_DTPR1_TDQSCKMAX_MASK) \
						<< PUBL_DTPR1_TDQSCKMAX_POS)

/* -------- PUBL_DTPR2 : (PUBL Offset: 0x3C) DRAM Timing Parameters Register 2  -------- */
/* tXS */
#define PUBL_DTPR2_TXS_MASK			0x3FFUL
#define PUBL_DTPR2_TXS_POS			0
#define PUBL_DTPR2_TXS(v)			(((v) & PUBL_DTPR2_TXS_MASK) \
						<< PUBL_DTPR2_TXS_POS)
/* tXP */
#define PUBL_DTPR2_TXP_MASK			0x1FUL
#define PUBL_DTPR2_TXP_POS			10
#define PUBL_DTPR2_TXP(v)			(((v) & PUBL_DTPR2_TXP_MASK) \
						<< PUBL_DTPR2_TXP_POS)
/* tCKE */
#define PUBL_DTPR2_TCKE_MASK			0xFUL
#define PUBL_DTPR2_TCKE_POS			15
#define PUBL_DTPR2_TCKE(v)			(((v) & PUBL_DTPR2_TCKE_MASK) \
						<< PUBL_DTPR2_TCKE_POS)
/* tDLLK */
#define PUBL_DTPR2_TDLLK_MASK			0x3FFUL
#define PUBL_DTPR2_TDLLK_POS			19
#define PUBL_DTPR2_TDLLK(v)			(((v) & PUBL_DTPR2_TDLLK_MASK) \
						<< PUBL_DTPR2_TDLLK_POS)

/* -------- PUBL_MR0 : (PUBL Offset: 0x40) PHY Mode Register 0 -------- */
#ifdef CONFIG_DDR3
/* DDR3 view of the register */
/* CL - Cas Latency - mask is not contiguous ! */
#define PUBL_MR0_CL_MASK			0x1DUL
#define PUBL_MR0_CL_POS				2
#define PUBL_MR0_CL(v)				(((v) & PUBL_MR0_CL_MASK) \
						<< PUBL_MR0_CL_POS)
#endif
/* Write Recovery */
#define PUBL_MR0_WR_MASK			0x7UL
#define PUBL_MR0_WR_POS				9
#define PUBL_MR0_WR(v)				(((v) & PUBL_MR0_WR_MASK) \
						<< PUBL_MR0_WR_POS)
#if defined(CONFIG_DDR2) || defined(CONFIG_LPDDR1)
/* DDR2 view of the register */
/* CL */
#define PUBL_MR0_CL_MASK			0x7UL
#define PUBL_MR0_CL_POS				4
#define PUBL_MR0_CL(v)				(((v) & PUBL_MR0_CL_MASK) \
						<< PUBL_MR0_CL_POS)
/* Burst Length */
#define PUBL_MR0_BL_MASK			0x3UL
#define PUBL_MR0_BL_POS				0
#define PUBL_MR0_BL_8				(((3) & PUBL_MR0_BL_MASK) \
						<< PUBL_MR0_BL_POS)
#endif

/* -------- PUBL_MR1 : (PUBL Offset: 0x44) PHY Mode Register 1 -------- */
/* RTT: On Die termination */
#define PUBL_MR1_RTT0				(0x1UL << 2)
#define PUBL_MR1_RTT1				(0x1UL << 6)
#define PUBL_MR1_RTT2				(0x1UL << 9)

/* Additive Latency */
#define PUBL_MR1_AL_MASK			0x3UL
#define PUBL_MR1_AL_POS				3
#define PUBL_MR1_AL(v)				(((v) & PUBL_MR1_AL_MASK) \
						<< PUBL_MR1_AL_POS)
#ifdef CONFIG_DDR2
#define PUBL_MR1_OCD_MASK			0x7UL
#define PUBL_MR1_OCD_POS			7
#define PUBL_MR1_OCD(v)				(((v) & PUBL_MR1_OCD_MASK) \
						<< PUBL_MR1_OCD_POS)
#endif
/* Burst length */
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
#define PUBL_MR1_BL_MASK			0x7UL
#define PUBL_MR1_BL_POS				0
#define PUBL_MR1_BL(v)				(((v) & PUBL_MR1_BL_MASK) \
						<< PUBL_MR1_BL_POS)
/* Write recovery */
#define PUBL_MR1_NWR_MASK			0x7UL
#define PUBL_MR1_NWR_POS			5
#define PUBL_MR1_NWR(v)				(((v) & PUBL_MR1_NWR_MASK) \
						<< PUBL_MR1_NWR_POS)
#endif

/* -------- PUBL_MR2 : (PUBL Offset: 0x48) PHY Mode Register 2 -------- */
/* Cas Write Latency */
#define PUBL_MR2_CWL_MASK			0x7UL
#define PUBL_MR2_CWL_POS			3
#define PUBL_MR2_CWL(v)				(((v) & PUBL_MR2_CWL_MASK) \
						<< PUBL_MR2_CWL_POS)

/* Self refresh temperature */
#define PUBL_MR2_SRT				(0x1 << 7)
/* Auto Self refresh */
#define PUBL_MR2_ASR				(0x1 << 6)

#define PUBL_MR2_RLWL_POS			0
#define PUBL_MR2_RLWL_4_2			(2 << PUBL_MR2_RLWL_POS)
#define PUBL_MR2_RLWL_5_2			(3 << PUBL_MR2_RLWL_POS)
#define PUBL_MR2_RLWL_6_3			(4 << PUBL_MR2_RLWL_POS)
#define PUBL_MR2_RLWL_7_4			(5 << PUBL_MR2_RLWL_POS)
#define PUBL_MR2_RLWL_8_4			(6 << PUBL_MR2_RLWL_POS)

/* -------- PUBL_MR3 : (PUBL Offset: 0x4C) PHY Mode Register 3 -------- */
#define PUBL_MR3_DS_40OHM			(0x2 << 0)
#define PUBL_MR3_DS_48OHM			(0x3 << 0)

/* -------- PUBL_ODTCR : (PUBL Offset: 0x50) ODT Configuration Register -------- */
#define PUBL_ODTCR_WRODT0_MASK			0xFUL
#define PUBL_ODTCR_WRODT0_POS			16
#define PUBL_ODTCR_WRODT0(v)			(((v) & PUBL_ODTCR_WRODT0_MASK) \
						<< PUBL_ODTCR_WRODT0_POS)

/* -------- PUBL_DTAR : (PUBL Offset: 0x54) DTAR Register -------- */
/* Data Training using MPR */
#define PUBL_DTAR_DTMPR				(0x1UL << 31)

/* -------- PUBL_DCUAR : (PUBL Offset: 0xC0) DCU Address Register -------- */
/* Cache Word Address */
#define PUBL_DCUAR_CWADDR_POS			0
#define PUBL_DCUAR_CWADDR_MASK			0xFUL
#define PUBL_DCUAR_CWADDR(v)			(((v) & PUBL_DCUAR_CWADDR_MASK) \
						<< PUBL_DCUAR_CWADDR_POS)

/* Cache Slice Address */
#define PUBL_DCUAR_CSADDR_POS			4
#define PUBL_DCUAR_CSADDR_MASK			0xFUL
#define PUBL_DCUAR_CSADDR(v)			(((v) & PUBL_DCUAR_CSADDR_MASK) \
						<< PUBL_DCUAR_CSADDR_POS)

/* Cache select */
#define PUBL_DCUAR_CSEL_POS			8
#define PUBL_DCUAR_CSEL_MASK			0x3UL
#define PUBL_DCUAR_CSEL(v)			(((v) & PUBL_DCUAR_CSEL_MASK) \
						<< PUBL_DCUAR_CSEL_POS)

/* Increment Address */
#define PUBL_DCUAR_INCA				(0x1UL << 10)

/* Access Type */
#define PUBL_DCUAR_ATYPE			(0x1UL << 11)

/* -------- PUBL_DCURR : (PUBL Offset: 0xC8) DCU Run Register -------- */
/* DCU Instruction */
#define PUBL_DCURR_DINST_POS			0
#define PUBL_DCURR_DINST_MASK			0xFUL
#define PUBL_DCURR_DINST(v)			(((v) & PUBL_DCURR_DINST_MASK) \
						<< PUBL_DCURR_DINST_POS)

/* Start Address */
#define PUBL_DCURR_SADDR_POS			4
#define PUBL_DCURR_SADDR_MASK			0xFUL
#define PUBL_DCURR_SADDR(v)			(((v) & PUBL_DCURR_SADDR_MASK) \
						<< PUBL_DCURR_SADDR_POS)

/* End Address */
#define PUBL_DCURR_EADDR_POS			8
#define PUBL_DCURR_EADDR_MASK			0xFUL
#define PUBL_DCURR_EADDR(v)			(((v) & PUBL_DCURR_EADDR_MASK) \
						<< PUBL_DCURR_EADDR_POS)

/* -------- PUBL_DCUSR0 : (PUBL Offset: 0xD8) DCU Status-0 Register -------- */
/* Run Done */
#define PUBL_DCUSR0_RDONE			(0x1UL << 0)

/* -------- PUBL_ZQ0CR0 : (PUBL Offset: 0x180) Impedance Control Register 0 -------- */
/* ZDATA Impedance over-ride data */
#define PUBL_ZQ0CR0_ZDATA_MASK			0xFFFFFFFUL
#define PUBL_ZQ0CR0_ZDATA_POS			0
#define PUBL_ZQ0CR0_ZDATA(v)			(((v) & PUBL_ZQ0CR0_ZDATA_MASK) \
						<< PUBL_ZQ0CR0_ZDATA_POS)

/* ZDEN Impedance over-ride enable */
#define PUBL_ZQ0CR0_ZDEN			(0x1UL << 28)

/* -------- PUBL_ZQ0CR1 : (PUBL Offset: 0x184) Impedance Control Register 1 -------- */
/* ZPROG Output impedance divide select */
#define PUBL_ZQ0CR1_ZPROG_OID_MASK		0xFUL
#define PUBL_ZQ0CR1_ZPROG_OID_POS		0
#define PUBL_ZQ0CR1_ZPROG_OID(v)		(((v) & PUBL_ZQ0CR1_ZPROG_OID_MASK) \
						<< PUBL_ZQ0CR1_ZPROG_OID_POS)
/* ZPROG On die termination divide select */
#define PUBL_ZQ0CR1_ZPROG_ODT_MASK		0xFUL
#define PUBL_ZQ0CR1_ZPROG_ODT_POS		4
#define PUBL_ZQ0CR1_ZPROG_ODT(v)		(((v) & PUBL_ZQ0CR1_ZPROG_ODT_MASK) \
						<< PUBL_ZQ0CR1_ZPROG_ODT_POS)

/* -------- PUBL_ZQ0SR0 : (PUBL Offset: 0x188) Impedance Status Register 0 -------- */
/* ZERR Impedance calibration error */
#define PUBL_ZQ0SR0_ZERR			(1 << 30)
/*
 * }
 */
#endif
