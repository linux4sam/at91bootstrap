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
#ifndef __AT91SAMA_MPDDRC_H__
#define __AT91SAMA_MPDDRC_H__

/* Register offset in AT91S_MPDDRC structure */
#define	MPDDRC_MR		0x00	/* MPDDRC Mode Register */
#define	MPDDRC_RTR		0x04	/* MPDDRC Refresh Timer Register */
#define	MPDDRC_CR		0x08	/* MPDDRC Configuration Register */
#define	MPDDRC_TPR0		0x0C	/* MPDDRC Timing Parameter 0 Register */
#define	MPDDRC_TPR1		0x10	/* MPDDRC Timing Parameter 1 Register */
#define	MPDDRC_TPR2		0x14	/* MPDDRC Timing Parameter 2 Register */
/* 0x18 Reserved */
#define	MPDDRC_LPR		0x1C	/* MPDDRC Low-power Register */
#define	MPDDRC_MD		0x20	/* MPDDRC Memory Device Register */
/* 0x24 Reserved */
#define	MPDDRC_LPDDR2_LPR	0x28	/* MPDDRC LPDDR2 Low-power Register */
#define	MPDDRC_LPDDR2_CAL_MR4	0x2C	/* MPDDRC LPDDR2 Calibration and MR4 Register */
#define	MPDDRC_LPDDR2_TIM_CAL	0x30	/* MPDDRC LPDDR2 Timing Calibration Register */
#define	MPDDRC_IO_CALIBR	0x34	/* MPDDRC IO Calibration */
#define	MPDDRC_OCMS		0x38	/* MPDDRC OCMS Register */
#define	MPDDRC_OCMS_KEY1	0x3C	/* MPDDRC OCMS KEY1 Register */
#define	MPDDRC_OCMS_KEY2	0x40	/* MPDDRC OCMS KEY2 Register */
/* 0x54 ~ 0x70 Reserved */
#define	MPDDRC_DLL_MOR		0x74	/* MPDDRC DLL Master Offset Register */
#define	MPDDRC_DLL_SOR		0x78	/* MPDDRC DLL Slave Offset Register */
#define	MPDDRC_DLL_MSR		0x7C	/* MPDDRC DLL Master Status Register */
#define	MPDDRC_DLL_S0SR		0x80	/* MPDDRC DLL Slave 0 Status Register */
#define	MPDDRC_DLL_S1SR		0x84	/* MPDDRC DLL Slave 1 Status Register */
/* 0x94 ~ 0xE0 Reserved */
#define	MPDDRC_WPCR		0xE4	/* MPDDRC Write Protect Control Register */
#define	MPDDRC_WPSR		0xE8	/* MPDDRC Write Protect Status Register */

/*--------------- MPDDRC_MR (Offset: 0x00) Mode Register-----------------------*/
#define		AT91C_MPDDRC_MODE	(0x7 << 0)		/* Command Mode */
#define			AT91C_MPDDRC_MODE_NORMAL		0	/* Normal Mode */
#define			AT91C_MPDDRC_MODE_NOP		1	/* NOP command */
#define			AT91C_MPDDRC_MODE_PRECHARGE	2	/* All Bank Precharge */
#define			AT91C_MPDDRC_MODE_LMR		3	/* Load Mode Register */
#define			AT91C_MPDDRC_MODE_REFRESH	4	/* Auto Refresh */
#define			AT91C_MPDDRC_MODE_EXT_LMR	5	/* Extended Load Mode Register */
#define			AT91C_MPDDRC_MODE_DEEP		6	/* Deep Power Mode */
#define			AT91C_MPDDRC_MODE_LPDDR2		7	/* LPDDR2 Mode Register */
#define		AT91C_MPDDRC_MRS		(0xff << 8)		/* Mode Register Select LPDDR2*/

/*--------------- MPDDRC_RTR (Offset: 0x04) Refresh Timer Register-----------------------*/
#define		AT91C_MPDDRC_COUNT	(0xfff << 0)		/* Refresh Timer Counter */
#define		AT91C_MPDDRC_ADJ_REF	(0x01 << 16)		/* Adjust Refresh Rate */
#define		AT91C_MPDDRC_REF_PB	(0x01 << 17)		/* Refresh Per Bank */
#define		AT91C_MPDDRC_MR4_VALUE	(0x07 << 20		/* Content of MR4 Register*/

/*--------------- MPDDRC_CR (Offset: 0x08) Configuration Register -----------------------*/
#define		AT91C_MPDDRC_NC		(3 << 0)		/* Number of Column Bits */
#define			AT91C_MPDDRC_NC_DDR9	(0 << 0)
#define			AT91C_MPDDRC_NC_DDR10	(1 << 0)
#define			AT91C_MPDDRC_NC_DDR11	(2 << 0)
#define			AT91C_MPDDRC_NC_DDR12	(3 << 0)
#define		AT91C_MPDDRC_NR		(3 << 2)		/* Number of Row Bits */
#define			AT91C_MPDDRC_NR_11	(0 << 2)
#define			AT91C_MPDDRC_NR_12	(1 << 2)
#define			AT91C_MPDDRC_NR_13	(2 << 2)
#define			AT91C_MPDDRC_NR_14	(3 << 2)
#define		AT91C_MPDDRC_CAS	(7 << 4)		/* CAS Latency */
#define			AT91C_MPDDRC_CAS_3_DDR2		(3 << 4)
#define			AT91C_MPDDRC_CAS_4_DDR2		(4 << 4)
#define			AT91C_MPDDRC_CAS_5_DDR2		(5 << 4)
#define			AT91C_MPDDRC_CAS_6_DDR2		(6 << 4)
#define			AT91C_MPDDRC_CAS_3_LPDDR2	(3 << 4)
#define			AT91C_MPDDRC_CAS_4_LPDDR2	(4 << 4)
#define			AT91C_MPDDRC_CAS_5_LPDDR2	(5 << 4)
#define		AT91C_MPDDRC_RST_DLL	(1 << 7)		/* Reset DLL */
#define			AT91C_MPDDRC_DISABLE_RST_DLL	(0 << 7)	/* Disable reset DLL */
#define			AT91C_MPDDRC_ENABLE_RST_DLL	(1 << 7)	/* Enable reset DLL */
#define		AT91C_MPDDRC_DIC_DS	(1 << 8)		/* Output impedance control */
#define		AT91C_MPDDRC_DIS_DLL	(1 << 9)		/* Disable DLL */
#define		AT91C_MPDDRC_ZQ		(3 << 10)		/* ZQ Calibration */
#define			AT91C_MPDDRC_ZQ_INIT		(0 << 10)
#define			AT91C_MPDDRC_ZQ_LONG		(1 << 10)
#define			AT91C_MPDDRC_ZQ_SHORT		(2 << 10)
#define			AT91C_MPDDRC_ZQ_RESET		(3 << 10)
#define		AT91C_MPDDRC_OCD	(7 << 12)		/* Off-Chip Driver */
#define			AT91C_MPDDRC_OCD_EXIT		(0 << 12)
#define			AT91C_MPDDRC_OCD_DEFAULT		(7 << 12)
#define		AT91C_MPDDRC_DQMS	(1 << 16)		/* Mask Data is Shared */
#define		AT91C_MPDDRC_ENRDM	(1 << 17)		/* Enable Read Measure */
#define		AT91C_MPDDRC_NB		(1 << 20)		/* Number of Bandks */
#define			AT91C_MPDDRC_NB_4		(0 << 20)
#define			AT91C_MPDDRC_NB_8		(1 << 20)
#define		AT91C_MPDDRC_NDQS	(1 << 21)		/* Not DQS */
#define			AT91C_MPDDRC_NDQS_ENABLED	(0 << 21)
#define			AT91C_MPDDRC_NDQS_DISABLED	(1 << 21)
#define		AT91C_MPDDRC_DECOD	(1 << 22)		/* Type of Decoding */
#define			AT91C_MPDDRC_DECOD_SEQUENTIAL	(0 << 22)	/* Sequential decoding */
#define			AT91C_MPDDRC_DECOD_INTERLEAVED	(1 << 22)	/* Interleaved decoding */
#define		AT91C_MPDDRC_UNAL	(1 << 23)		/* Support Unaligned Access */
#define			AT91C_MPDDRC_UNAL_UNSUPPORTED	(0 << 23)
#define			AT91C_MPDDRC_UNAL_SUPPORTED	(1 << 23)

/*--------------- MPDDRC_TPR0(Offset: 0x0C) Timing Parameter Register 0-----------------------*/
#define		AT91C_MPDDRC_TRAS	(0xf <<  0)		/* Active to Precharge delay */
#define			AT91C_MPDDRC_TRAS_0	(0x0 <<  0)
#define			AT91C_MPDDRC_TRAS_1	(0x1 <<  0)
#define			AT91C_MPDDRC_TRAS_2	(0x2 <<  0)
#define			AT91C_MPDDRC_TRAS_3	(0x3 <<  0)
#define			AT91C_MPDDRC_TRAS_4	(0x4 <<  0)
#define			AT91C_MPDDRC_TRAS_5	(0x5 <<  0)
#define			AT91C_MPDDRC_TRAS_6	(0x6 <<  0)
#define			AT91C_MPDDRC_TRAS_7	(0x7 <<  0)
#define			AT91C_MPDDRC_TRAS_8	(0x8 <<  0)
#define			AT91C_MPDDRC_TRAS_9	(0x9 <<  0)
#define			AT91C_MPDDRC_TRAS_10	(0xA <<  0)
#define			AT91C_MPDDRC_TRAS_11	(0xB <<  0)
#define			AT91C_MPDDRC_TRAS_12	(0xC <<  0)
#define			AT91C_MPDDRC_TRAS_13	(0xD <<  0)
#define			AT91C_MPDDRC_TRAS_14	(0xE <<  0)
#define			AT91C_MPDDRC_TRAS_15	(0xF <<  0)
#define		AT91C_MPDDRC_TRCD	(0xf <<  4)		/* Row to Column delay */
#define			AT91C_MPDDRC_TRCD_0	(0x0 <<  4)
#define			AT91C_MPDDRC_TRCD_1	(0x1 <<  4)
#define			AT91C_MPDDRC_TRCD_2	(0x2 <<  4)
#define			AT91C_MPDDRC_TRCD_3	(0x3 <<  4)
#define			AT91C_MPDDRC_TRCD_4	(0x4 <<  4)
#define			AT91C_MPDDRC_TRCD_5	(0x5 <<  4)
#define			AT91C_MPDDRC_TRCD_6	(0x6 <<  4)
#define			AT91C_MPDDRC_TRCD_7	(0x7 <<  4)
#define			AT91C_MPDDRC_TRCD_8	(0x8 <<  4)
#define			AT91C_MPDDRC_TRCD_9	(0x9 <<  4)
#define			AT91C_MPDDRC_TRCD_10	(0xA <<  4)
#define			AT91C_MPDDRC_TRCD_11	(0xB <<  4)
#define			AT91C_MPDDRC_TRCD_12	(0xC <<  4)
#define			AT91C_MPDDRC_TRCD_13	(0xD <<  4)
#define			AT91C_MPDDRC_TRCD_14	(0xE <<  4)
#define			AT91C_MPDDRC_TRCD_15	(0xF <<  4)
#define		AT91C_MPDDRC_TWR	(0xf <<  8)		/* Write recovery delay */
#define			AT91C_MPDDRC_TWR_0	(0x0 <<  8)
#define			AT91C_MPDDRC_TWR_1	(0x1 <<  8)
#define			AT91C_MPDDRC_TWR_2	(0x2 <<  8)
#define			AT91C_MPDDRC_TWR_3	(0x3 <<  8)
#define			AT91C_MPDDRC_TWR_4	(0x4 <<  8)
#define			AT91C_MPDDRC_TWR_5	(0x5 <<  8)
#define			AT91C_MPDDRC_TWR_6	(0x6 <<  8)
#define			AT91C_MPDDRC_TWR_7	(0x7 <<  8)
#define			AT91C_MPDDRC_TWR_8	(0x8 <<  8)
#define			AT91C_MPDDRC_TWR_9	(0x9 <<  8)
#define			AT91C_MPDDRC_TWR_10	(0xA <<  8)
#define			AT91C_MPDDRC_TWR_11	(0xB <<  8)
#define			AT91C_MPDDRC_TWR_12	(0xC <<  8)
#define			AT91C_MPDDRC_TWR_13	(0xD <<  8)
#define			AT91C_MPDDRC_TWR_14	(0xE <<  8)
#define			AT91C_MPDDRC_TWR_15	(0xF <<  8)
#define		AT91C_MPDDRC_TRC	(0xf << 12)		/* Row cycle delay */
#define			AT91C_MPDDRC_TRC_0	(0x0 << 12)
#define			AT91C_MPDDRC_TRC_1	(0x1 << 12)
#define			AT91C_MPDDRC_TRC_2	(0x2 << 12)
#define			AT91C_MPDDRC_TRC_3	(0x3 << 12)
#define			AT91C_MPDDRC_TRC_4	(0x4 << 12)
#define			AT91C_MPDDRC_TRC_5	(0x5 << 12)
#define			AT91C_MPDDRC_TRC_6	(0x6 << 12)
#define			AT91C_MPDDRC_TRC_7	(0x7 << 12)
#define			AT91C_MPDDRC_TRC_8	(0x8 << 12)
#define			AT91C_MPDDRC_TRC_9	(0x9 << 12)
#define			AT91C_MPDDRC_TRC_10	(0xA << 12)
#define			AT91C_MPDDRC_TRC_11	(0xB << 12)
#define			AT91C_MPDDRC_TRC_12	(0xC << 12)
#define			AT91C_MPDDRC_TRC_13	(0xD << 12)
#define			AT91C_MPDDRC_TRC_14	(0xE << 12)
#define			AT91C_MPDDRC_TRC_15	(0xF << 12)
#define		AT91C_MPDDRC_TRP	(0xf << 16)		/* Row precharge delay */
#define			AT91C_MPDDRC_TRP_0	(0x0 << 16)
#define			AT91C_MPDDRC_TRP_1	(0x1 << 16)
#define			AT91C_MPDDRC_TRP_2	(0x2 << 16)
#define			AT91C_MPDDRC_TRP_3	(0x3 << 16)
#define			AT91C_MPDDRC_TRP_4	(0x4 << 16)
#define			AT91C_MPDDRC_TRP_5	(0x5 << 16)
#define			AT91C_MPDDRC_TRP_6	(0x6 << 16)
#define			AT91C_MPDDRC_TRP_7	(0x7 << 16)
#define			AT91C_MPDDRC_TRP_8	(0x8 << 16)
#define			AT91C_MPDDRC_TRP_9	(0x9 << 16)
#define			AT91C_MPDDRC_TRP_10	(0xA << 16)
#define			AT91C_MPDDRC_TRP_11	(0xB << 16)
#define			AT91C_MPDDRC_TRP_12	(0xC << 16)
#define			AT91C_MPDDRC_TRP_13	(0xD << 16)
#define			AT91C_MPDDRC_TRP_14	(0xE << 16)
#define			AT91C_MPDDRC_TRP_15	(0xF << 16)
#define		AT91C_MPDDRC_TRRD	(0xf << 20)		/* Active BankA to BankB */
#define			AT91C_MPDDRC_TRRD_0	(0x0 << 20)
#define			AT91C_MPDDRC_TRRD_1	(0x1 << 20)
#define			AT91C_MPDDRC_TRRD_2	(0x2 << 20)
#define			AT91C_MPDDRC_TRRD_3	(0x3 << 20)
#define			AT91C_MPDDRC_TRRD_4	(0x4 << 20)
#define			AT91C_MPDDRC_TRRD_5	(0x5 << 20)
#define			AT91C_MPDDRC_TRRD_6	(0x6 << 20)
#define			AT91C_MPDDRC_TRRD_7	(0x7 << 20)
#define			AT91C_MPDDRC_TRRD_8	(0x8 << 20)
#define			AT91C_MPDDRC_TRRD_9	(0x9 << 20)
#define			AT91C_MPDDRC_TRRD_10	(0xA << 20)
#define			AT91C_MPDDRC_TRRD_11	(0xB << 20)
#define			AT91C_MPDDRC_TRRD_12	(0xC << 20)
#define			AT91C_MPDDRC_TRRD_13	(0xD << 20)
#define			AT91C_MPDDRC_TRRD_14	(0xE << 20)
#define			AT91C_MPDDRC_TRRD_15	(0xF << 20)
#define		AT91C_MPDDRC_TWTR	(0xf << 24)		/* Internal Write to Read delay */
#define			AT91C_MPDDRC_TWTR_0	(0x0 << 24)
#define			AT91C_MPDDRC_TWTR_1	(0x1 << 24)
#define			AT91C_MPDDRC_TWTR_2	(0x2 << 24)
#define			AT91C_MPDDRC_TWTR_3	(0x3 << 24)
#define			AT91C_MPDDRC_TWTR_4	(0x4 << 24)
#define			AT91C_MPDDRC_TWTR_5	(0x5 << 24)
#define			AT91C_MPDDRC_TWTR_6	(0x6 << 24)
#define			AT91C_MPDDRC_TWTR_7	(0x7 << 24)
#define			AT91C_MPDDRC_TWTR_8	(0x8 << 24)
#define			AT91C_MPDDRC_TWTR_9	(0x9 << 24)
#define			AT91C_MPDDRC_TWTR_10	(0xA << 24)
#define			AT91C_MPDDRC_TWTR_11	(0xB << 24)
#define			AT91C_MPDDRC_TWTR_12	(0xC << 24)
#define			AT91C_MPDDRC_TWTR_13	(0xD << 24)
#define			AT91C_MPDDRC_TWTR_14	(0xE << 24)
#define			AT91C_MPDDRC_TWTR_15	(0xF << 24)
#define		AT91C_MPDDRC_TMRD	(0xf << 28)		/* Load mode to active/refresh delay */
#define			AT91C_MPDDRC_TMRD_0	(0x0 << 28)
#define			AT91C_MPDDRC_TMRD_1	(0x1 << 28)
#define			AT91C_MPDDRC_TMRD_2	(0x2 << 28)
#define			AT91C_MPDDRC_TMRD_3	(0x3 << 28)
#define			AT91C_MPDDRC_TMRD_4	(0x4 << 28)
#define			AT91C_MPDDRC_TMRD_5	(0x5 << 28)
#define			AT91C_MPDDRC_TMRD_6	(0x6 << 28)
#define			AT91C_MPDDRC_TMRD_7	(0x7 << 28)
#define			AT91C_MPDDRC_TMRD_8	(0x8 << 28)
#define			AT91C_MPDDRC_TMRD_9	(0x9 << 28)
#define			AT91C_MPDDRC_TMRD_10	(0xA << 28)
#define			AT91C_MPDDRC_TMRD_11	(0xB << 28)
#define			AT91C_MPDDRC_TMRD_12	(0xC << 28)
#define			AT91C_MPDDRC_TMRD_13	(0xD << 28)
#define			AT91C_MPDDRC_TMRD_14	(0xE << 28)
#define			AT91C_MPDDRC_TMRD_15	(0xF << 28)

/*--------------- MPDDRC_TPR1(Offset: 0x10) Timing Parameter Register 1-----------------------*/
#define		AT91C_MPDDRC_TRFC	(0x1f << 0)		/* Row Cycle Delay */
#define		AT91C_MPDDRC_TXSNR	(0xff << 8)		/* Exit self-refresh to non-read */
#define		AT91C_MPDDRC_TXSRD	(0xff << 16)		/* Exit self-refresh to read */
#define		AT91C_MPDDRC_TXP		(0xf  << 24)		/* Exit power-down delay */

/*--------------- MPDDRC_TPR2(Offset: 0x14) Timing Parameter Register 2-----------------------*/
#define		AT91C_MPDDRC_TXARD	(0xf  << 0)		/* Exit active power down delay to read command in mode "Fast Exit" */
#define			AT91C_MPDDRC_TXARD_0	(0x0  << 0)
#define			AT91C_MPDDRC_TXARD_1	(0x1  << 0)
#define			AT91C_MPDDRC_TXARD_2	(0x2  << 0)
#define			AT91C_MPDDRC_TXARD_3	(0x3  << 0)
#define			AT91C_MPDDRC_TXARD_4	(0x4  << 0)
#define			AT91C_MPDDRC_TXARD_5	(0x5  << 0)
#define			AT91C_MPDDRC_TXARD_6	(0x6  << 0)
#define			AT91C_MPDDRC_TXARD_7	(0x7  << 0)
#define			AT91C_MPDDRC_TXARD_8	(0x8  << 0)
#define			AT91C_MPDDRC_TXARD_9	(0x9  << 0)
#define			AT91C_MPDDRC_TXARD_10	(0xA  << 0)
#define			AT91C_MPDDRC_TXARD_11	(0xB  << 0)
#define			AT91C_MPDDRC_TXARD_12	(0xC  << 0)
#define			AT91C_MPDDRC_TXARD_13	(0xD  << 0)
#define			AT91C_MPDDRC_TXARD_14	(0xE  << 0)
#define			AT91C_MPDDRC_TXARD_15	(0xF  << 0)
#define		AT91C_MPDDRC_TXARDS	(0xf  << 4)		/* Exit active power down delay to read command in mode "Slow Exit" */
#define			AT91C_MPDDRC_TXARDS_0	(0x0  << 4)
#define			AT91C_MPDDRC_TXARDS_1	(0x1  << 4)
#define			AT91C_MPDDRC_TXARDS_2	(0x2  << 4)
#define			AT91C_MPDDRC_TXARDS_3	(0x3  << 4)
#define			AT91C_MPDDRC_TXARDS_4	(0x4  << 4)
#define			AT91C_MPDDRC_TXARDS_5	(0x5  << 4)
#define			AT91C_MPDDRC_TXARDS_6	(0x6  << 4)
#define			AT91C_MPDDRC_TXARDS_7	(0x7  << 4)
#define			AT91C_MPDDRC_TXARDS_8	(0x8  << 4)
#define			AT91C_MPDDRC_TXARDS_9	(0x9  << 4)
#define			AT91C_MPDDRC_TXARDS_10	(0xA  << 4)
#define			AT91C_MPDDRC_TXARDS_11	(0xB  << 4)
#define			AT91C_MPDDRC_TXARDS_12	(0xC  << 4)
#define			AT91C_MPDDRC_TXARDS_13	(0xD  << 4)
#define			AT91C_MPDDRC_TXARDS_14	(0xE  << 4)
#define			AT91C_MPDDRC_TXARDS_15	(0xF  << 4)
#define		AT91C_MPDDRC_TRPA	(0xf  << 8)		/* Row Precharge All delay */
#define			AT91C_MPDDRC_TRPA_0	(0x0  << 8)
#define			AT91C_MPDDRC_TRPA_1	(0x1  << 8)
#define			AT91C_MPDDRC_TRPA_2	(0x2  << 8)
#define			AT91C_MPDDRC_TRPA_3	(0x3  << 8)
#define			AT91C_MPDDRC_TRPA_4	(0x4  << 8)
#define			AT91C_MPDDRC_TRPA_5	(0x5  << 8)
#define			AT91C_MPDDRC_TRPA_6	(0x6  << 8)
#define			AT91C_MPDDRC_TRPA_7	(0x7  << 8)
#define			AT91C_MPDDRC_TRPA_8	(0x8  << 8)
#define			AT91C_MPDDRC_TRPA_9	(0x9  << 8)
#define			AT91C_MPDDRC_TRPA_10	(0xA  << 8)
#define			AT91C_MPDDRC_TRPA_11	(0xB  << 8)
#define			AT91C_MPDDRC_TRPA_12	(0xC  << 8)
#define			AT91C_MPDDRC_TRPA_13	(0xD  << 8)
#define			AT91C_MPDDRC_TRPA_14	(0xE  << 8)
#define			AT91C_MPDDRC_TRPA_15	(0xF  << 8)
#define		AT91C_MPDDRC_TRTP	(0x7  << 12)		/* Read to Precharge delay */
#define			AT91C_MPDDRC_TRTP_0	(0x0  << 12)
#define			AT91C_MPDDRC_TRTP_1	(0x1  << 12)
#define			AT91C_MPDDRC_TRTP_2	(0x2  << 12)
#define			AT91C_MPDDRC_TRTP_3	(0x3  << 12)
#define			AT91C_MPDDRC_TRTP_4	(0x4  << 12)
#define			AT91C_MPDDRC_TRTP_5	(0x5  << 12)
#define			AT91C_MPDDRC_TRTP_6	(0x6  << 12)
#define			AT91C_MPDDRC_TRTP_7	(0x7  << 12)
#define		AT91C_MPDDRC_TFAW	(0xf  << 16)		/* Four Active Windows delay */
#define			AT91C_MPDDRC_TFAW_0	(0x0  << 16)
#define			AT91C_MPDDRC_TFAW_1	(0x1  << 16)
#define			AT91C_MPDDRC_TFAW_2	(0x2  << 16)
#define			AT91C_MPDDRC_TFAW_3	(0x3  << 16)
#define			AT91C_MPDDRC_TFAW_4	(0x4  << 16)
#define			AT91C_MPDDRC_TFAW_5	(0x5  << 16)
#define			AT91C_MPDDRC_TFAW_6	(0x6  << 16)
#define			AT91C_MPDDRC_TFAW_7	(0x7  << 16)
#define			AT91C_MPDDRC_TFAW_8	(0x8  << 16)
#define			AT91C_MPDDRC_TFAW_9	(0x9  << 16)
#define			AT91C_MPDDRC_TFAW_10	(0xA  << 16)
#define			AT91C_MPDDRC_TFAW_11	(0xB  << 16)
#define			AT91C_MPDDRC_TFAW_12	(0xC  << 16)
#define			AT91C_MPDDRC_TFAW_13	(0xD  << 16)
#define			AT91C_MPDDRC_TFAW_14	(0xE  << 16)
#define			AT91C_MPDDRC_TFAW_15	(0xF  << 16)

/*--------------- MPDDRC_LPR(Offset: 0x1C) Low-power Register -----------------------*/
#define		AT91C_MPDDRC_LPCB	(3 << 0)		/* Low-power Command Bit*/
#define			AT91C_MPDDRC_LPCB_DISABLED		0
#define			AT91C_MPDDRC_LPCB_SELF_REFRESH		1
#define			AT91C_MPDDRC_LPCB_POWER_DOWN		2
#define			AT91C_MPDDRC_LPCB_DEEP_POWER_DOWN	3
#define		AT91C_MPDDRC_CLKFR		(1 << 2)	/* Clock Frozen Command Bit */
#define		AT91C_MPDDRC_LPDDR2_PWOFF	(1 << 3)	/* LPDDR2 Power Off Bit */
#define		AT91C_MPDDRC_PASR		(7 << 4)	/* Partial Array Self Refresh */
#define		AT91C_MPDDRC_DS			(7 << 8)	/* Drive Strength */
#define		AT91C_MPDDRC_TIMEOUT		(3 << 12)	/* Time to define when Low Power Mode is enabled */
#define			AT91C_MPDDRC_TIMEOUT_0_CLK_CYCLES	(0 << 12)
#define			AT91C_MPDDRC_TIMEOUT_64_CLK_CYCLES	(1 << 12)
#define			AT91C_MPDDRC_TIMEOUT_128_CLK_CYCLES	(2 << 12)
#define		AT91C_MPDDRC_APDE		(1 << 16)	 /* Active power down exit time */
#define		AT91C_MPDDRC_UPD_MR		(3 << 20)	 /* Update load mode register and extended mode register */

/*--------------- MPDDRC_LPR(Offset: 0x20) Memory Device Register -----------------------*/
#define		AT91C_MPDDRC_MD		(3 << 0)		/* Memory Device Type */
#define			AT91C_MPDDRC_MD_LPDDR_SDRAM		(3 << 0)
#define			AT91C_MPDDRC_MD_DDR2_SDRAM		(6 << 0)
#define			AT91C_MPDDRC_MD_LPDDR2_SDRAM		(7 << 0)
#define		AT91C_MPDDRC_DBW	(1 << 4)		/* Data Bus Width */
#define			AT91C_MPDDRC_DBW_32BITS		(0 <<  4)
#define			AT91C_MPDDRC_DBW_16BITS		(1 <<  4)

#endif /* #ifndef __AT91SAMA_MPDDR_H__ */

