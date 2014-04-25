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
#ifndef __AT91_DDRSDRC_H__
#define __AT91_DDRSDRC_H__

/**** Register offset in AT91S_HDDRSDRC2 structure ***/
#define HDDRSDRC2_MR		0x00	/* Mode Register */
#define HDDRSDRC2_RTR		0x04	/* Refresh Timer Register */
#define HDDRSDRC2_CR		0x08	/* Configuration Register */
#define HDDRSDRC2_T0PR		0x0C	/* Timing Parameter 0 Register */
#define HDDRSDRC2_T1PR		0x10	/* Timing Parameter 1 Register */
#define HDDRSDRC2_T2PR		0x14	/* Timing Parameter 2 Register */
#define HDDRSDRC2_T3PR		0x18	/* Timing Parameter 3 Register */
#define HDDRSDRC2_LPR		0x1C	/* Low-power Register */
#define HDDRSDRC2_MDR		0x20	/* Memory Device Register */
#define HDDRSDRC2_DLL		0x24	/* DLL Information Register */
#define HDDRSDRC2_HS		0x2C	/* High Speed Register */

/* below items defined for sama5d3x */
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

#define MPDDRC_LPR        0x1C  /* MPDDRC LP-DDR1 Low Power Mode Register */

/* 0x94 ~ 0xE0 Reserved */
#define HDDRSDRC2_WPCR		0xE4	/* Write Protect Mode Register */
#define HDDRSDRC2_WPSR		0xE8	/* Write Protect Status Register */

/* -------- HDDRSDRC2_MR : (HDDRSDRC2 Offset: 0x0) Mode Register --------*/ 
#define AT91C_DDRC2_MODE	(0x7UL << 0)
#define 	AT91C_DDRC2_MODE_NORMAL_CMD		(0x0UL)
#define 	AT91C_DDRC2_MODE_NOP_CMD		(0x1UL)
#define 	AT91C_DDRC2_MODE_PRCGALL_CMD		(0x2UL)
#define 	AT91C_DDRC2_MODE_LMR_CMD		(0x3UL)
#define 	AT91C_DDRC2_MODE_RFSH_CMD		(0x4UL)
#define 	AT91C_DDRC2_MODE_EXT_LMR_CMD		(0x5UL)
#define 	AT91C_DDRC2_MODE_DEEP_CMD		(0x6UL)
#define 	AT91C_DDRC2_MODE_Reserved		(0x7UL)

/* -------- HDDRSDRC2_RTR : (HDDRSDRC2 Offset: 0x4) Refresh Timer Register -------- */
#define AT91C_DDRC2_COUNT	(0xFFFUL << 0)

/* -------- HDDRSDRC2_CR : (HDDRSDRC2 Offset: 0x8) Configuration Register --------*/ 
#define AT91C_DDRC2_NC		(0x3UL <<  0)
#define 	AT91C_DDRC2_NC_DDR9_SDR8	(0x0UL)
#define 	AT91C_DDRC2_NC_DDR10_SDR9	(0x1UL)
#define 	AT91C_DDRC2_NC_DDR11_SDR10	(0x2UL)
#define 	AT91C_DDRC2_NC_DDR12_SDR11	(0x3UL)
#define AT91C_DDRC2_NR		(0x3UL << 2)
#define 	AT91C_DDRC2_NR_11		(0x0UL << 2)
#define 	AT91C_DDRC2_NR_12		(0x1UL << 2)
#define 	AT91C_DDRC2_NR_13		(0x2UL << 2)
#define 	AT91C_DDRC2_NR_14		(0x3UL << 2)
#define AT91C_DDRC2_CAS		(0x7UL << 4)
#define 	AT91C_DDRC2_CAS_2		(0x2UL << 4)
#define 	AT91C_DDRC2_CAS_3		(0x3UL << 4)
#define 	AT91C_DDRC2_CAS_4		(0x4UL << 4)
#define 	AT91C_DDRC2_CAS_5		(0x5UL << 4)
#define 	AT91C_DDRC2_CAS_2_5		(0x6UL << 4)
#define AT91C_DDRC2_DLL		(0x1UL << 7)
#define 	AT91C_DDRC2_DLL_RESET_DISABLED	(0x0UL << 7)
#define 	AT91C_DDRC2_DLL_RESET_ENABLED	(0x1UL << 7)
#define AT91C_DDRC2_DIC_DS	(0x1UL << 8)
#define AT91C_DDRC2_DIS_DLL	(0x1UL << 9)
#define 	AT91C_DDRC2_DIS_DLL_DISABLED	(0x0UL << 9)
#define 	AT91C_DDRC2_DIS_DLL_ENABLED	(0x1UL << 9)
#define AT91C_DDRC2_OCD		(0x7UL << 12)
#define 	AT91C_DDRC2_OCD_EXIT		(0x0UL << 12)
#define 	AT91C_DDRC2_OCD_DEFAULT		(0x7UL << 12)
#define AT91C_DDRC2_EBISHARE	(0x1UL << 16)
#define AT91C_DDRC2_ENRDM	(0x1UL << 17)
#define 	AT91C_DDRC2_ENRDM_DISABLE	(0x0UL << 17)
#define 	AT91C_DDRC2_ENRDM_ENABLE	(0x1UL << 17)
#define AT91C_DDRC2_ACTBST	(0x1UL << 18)
#define AT91C_DDRC2_NB_BANKS	(0x1UL << 20)
#define 	AT91C_DDRC2_NB_BANKS_4		(0x0UL << 20)
#define 	AT91C_DDRC2_NB_BANKS_8		(0x1UL << 20)
#define AT91C_DDRC2_NDQS	(0x1UL << 21)	/* Not DQS(sama5d3x only) */
#define 	AT91C_DDRC2_NDQS_ENABLED	(0x0UL << 21)
#define 	AT91C_DDRC2_NDQS_DISABLED	(0x1UL << 21)
#define AT91C_DDRC2_DECOD	(0x1UL << 22)
#define 	AT91C_DDRC2_DECOD_SEQUENTIAL	(0x0UL << 22)
#define 	AT91C_DDRC2_DECOD_INTERLEAVED	(0x1UL << 22)
#define AT91C_DDRC2_UNAL	(0x1UL << 23)	/* Support Unaligned Access(sama5d3x only) */
#define 	AT91C_DDRC2_UNAL_UNSUPPORTED		(0x0UL << 23)
#define 	AT91C_DDRC2_UNAL_SUPPORTED		(0x1UL << 23)

/* -------- HDDRSDRC2_T0PR : (HDDRSDRC2 Offset: 0xc) Timing0 Register --------*/ 
#define AT91C_DDRC2_TRAS	(0xFUL <<  0)
#define 	AT91C_DDRC2_TRAS_0		(0x0UL)
#define 	AT91C_DDRC2_TRAS_1		(0x1UL)
#define 	AT91C_DDRC2_TRAS_2		(0x2UL)
#define 	AT91C_DDRC2_TRAS_3		(0x3UL)
#define 	AT91C_DDRC2_TRAS_4		(0x4UL)
#define 	AT91C_DDRC2_TRAS_5		(0x5UL)
#define 	AT91C_DDRC2_TRAS_6		(0x6UL)
#define 	AT91C_DDRC2_TRAS_7		(0x7UL)
#define 	AT91C_DDRC2_TRAS_8		(0x8UL)
#define 	AT91C_DDRC2_TRAS_9		(0x9UL)
#define 	AT91C_DDRC2_TRAS_10		(0xAUL)
#define 	AT91C_DDRC2_TRAS_11		(0xBUL)
#define 	AT91C_DDRC2_TRAS_12		(0xCUL)
#define 	AT91C_DDRC2_TRAS_13		(0xDUL)
#define 	AT91C_DDRC2_TRAS_14		(0xEUL)
#define 	AT91C_DDRC2_TRAS_15		(0xFUL)
#define AT91C_DDRC2_TRCD	(0xFUL <<  4)
#define 	AT91C_DDRC2_TRCD_0		(0x0UL << 4)
#define 	AT91C_DDRC2_TRCD_1		(0x1UL << 4)
#define 	AT91C_DDRC2_TRCD_2		(0x2UL << 4)
#define 	AT91C_DDRC2_TRCD_3		(0x3UL << 4)
#define 	AT91C_DDRC2_TRCD_4		(0x4UL << 4)
#define 	AT91C_DDRC2_TRCD_5		(0x5UL << 4)
#define 	AT91C_DDRC2_TRCD_6		(0x6UL << 4)
#define 	AT91C_DDRC2_TRCD_7		(0x7UL << 4)
#define 	AT91C_DDRC2_TRCD_8		(0x8UL << 4)
#define 	AT91C_DDRC2_TRCD_9		(0x9UL << 4)
#define 	AT91C_DDRC2_TRCD_10		(0xAUL << 4)
#define 	AT91C_DDRC2_TRCD_11		(0xBUL << 4)
#define 	AT91C_DDRC2_TRCD_12		(0xCUL << 4)
#define 	AT91C_DDRC2_TRCD_13		(0xDUL << 4)
#define 	AT91C_DDRC2_TRCD_14		(0xEUL << 4)
#define 	AT91C_DDRC2_TRCD_15		(0xFUL << 4)
#define AT91C_DDRC2_TWR		(0xFUL << 8)
#define 	AT91C_DDRC2_TWR_0		(0x0UL << 8)
#define 	AT91C_DDRC2_TWR_1		(0x1UL << 8)
#define 	AT91C_DDRC2_TWR_2		(0x2UL << 8)
#define 	AT91C_DDRC2_TWR_3		(0x3UL << 8)
#define 	AT91C_DDRC2_TWR_4		(0x4UL << 8)
#define 	AT91C_DDRC2_TWR_5		(0x5UL << 8)
#define 	AT91C_DDRC2_TWR_6		(0x6UL << 8)
#define 	AT91C_DDRC2_TWR_7		(0x7UL << 8)
#define 	AT91C_DDRC2_TWR_8		(0x8UL << 8)
#define 	AT91C_DDRC2_TWR_9		(0x9UL << 8)
#define 	AT91C_DDRC2_TWR_10		(0xAUL << 8)
#define 	AT91C_DDRC2_TWR_11		(0xBUL << 8)
#define 	AT91C_DDRC2_TWR_12		(0xCUL << 8)
#define 	AT91C_DDRC2_TWR_13		(0xDUL << 8)
#define 	AT91C_DDRC2_TWR_14		(0xEUL << 8)
#define 	AT91C_DDRC2_TWR_15		(0xFUL << 8)
#define AT91C_DDRC2_TRC		(0xFUL << 12)
#define 	AT91C_DDRC2_TRC_0		(0x0UL << 12)
#define 	AT91C_DDRC2_TRC_1		(0x1UL << 12)
#define 	AT91C_DDRC2_TRC_2		(0x2UL << 12)
#define 	AT91C_DDRC2_TRC_3		(0x3UL << 12)
#define 	AT91C_DDRC2_TRC_4		(0x4UL << 12)
#define 	AT91C_DDRC2_TRC_5		(0x5UL << 12)
#define 	AT91C_DDRC2_TRC_6		(0x6UL << 12)
#define 	AT91C_DDRC2_TRC_7		(0x7UL << 12)
#define 	AT91C_DDRC2_TRC_8		(0x8UL << 12)
#define 	AT91C_DDRC2_TRC_9		(0x9UL << 12)
#define 	AT91C_DDRC2_TRC_10		(0xAUL << 12)
#define 	AT91C_DDRC2_TRC_11		(0xBUL << 12)
#define 	AT91C_DDRC2_TRC_12		(0xCUL << 12)
#define 	AT91C_DDRC2_TRC_13		(0xDUL << 12)
#define 	AT91C_DDRC2_TRC_14		(0xEUL << 12)
#define 	AT91C_DDRC2_TRC_15		(0xFUL << 12)
#define AT91C_DDRC2_TRP		(0xFUL << 16)
#define 	AT91C_DDRC2_TRP_0		(0x0UL << 16)
#define 	AT91C_DDRC2_TRP_1		(0x1UL << 16)
#define 	AT91C_DDRC2_TRP_2		(0x2UL << 16)
#define 	AT91C_DDRC2_TRP_3		(0x3UL << 16)
#define 	AT91C_DDRC2_TRP_4		(0x4UL << 16)
#define 	AT91C_DDRC2_TRP_5		(0x5UL << 16)
#define 	AT91C_DDRC2_TRP_6		(0x6UL << 16)
#define 	AT91C_DDRC2_TRP_7		(0x7UL << 16)
#define 	AT91C_DDRC2_TRP_8		(0x8UL << 16)
#define 	AT91C_DDRC2_TRP_9		(0x9UL << 16)
#define 	AT91C_DDRC2_TRP_10		(0xAUL << 16)
#define 	AT91C_DDRC2_TRP_11		(0xBUL << 16)
#define 	AT91C_DDRC2_TRP_12		(0xCUL << 16)
#define 	AT91C_DDRC2_TRP_13		(0xDUL << 16)
#define 	AT91C_DDRC2_TRP_14		(0xEUL << 16)
#define 	AT91C_DDRC2_TRP_15		(0xFUL << 16)
#define AT91C_DDRC2_TRRD	(0xFUL << 20)
#define 	AT91C_DDRC2_TRRD_0		(0x0UL << 20)
#define 	AT91C_DDRC2_TRRD_1		(0x1UL << 20)
#define 	AT91C_DDRC2_TRRD_2		(0x2UL << 20)
#define 	AT91C_DDRC2_TRRD_3		(0x3UL << 20)
#define 	AT91C_DDRC2_TRRD_4		(0x4UL << 20)
#define 	AT91C_DDRC2_TRRD_5		(0x5UL << 20)
#define 	AT91C_DDRC2_TRRD_6		(0x6UL << 20)
#define 	AT91C_DDRC2_TRRD_7		(0x7UL << 20)
#define 	AT91C_DDRC2_TRRD_10		(0xAUL << 20)
#define 	AT91C_DDRC2_TRRD_11		(0xBUL << 20)
#define 	AT91C_DDRC2_TRRD_12		(0xCUL << 20)
#define 	AT91C_DDRC2_TRRD_13		(0xDUL << 20)
#define 	AT91C_DDRC2_TRRD_14		(0xEUL << 20)
#define 	AT91C_DDRC2_TRRD_15		(0xFUL << 20)
#define AT91C_DDRC2_TWTR          (0x7UL << 24) // (HDDRSDRC2) Internal write to read delay
#define 	AT91C_DDRC2_TWTR_0                    (0x0UL << 24)
#define 	AT91C_DDRC2_TWTR_1                    (0x1UL << 24)
#define 	AT91C_DDRC2_TWTR_2                    (0x2UL << 24)
#define 	AT91C_DDRC2_TWTR_3                    (0x3UL << 24)
#define 	AT91C_DDRC2_TWTR_4                    (0x4UL << 24)
#define 	AT91C_DDRC2_TWTR_5                    (0x5UL << 24)
#define 	AT91C_DDRC2_TWTR_6                    (0x6UL << 24)
#define 	AT91C_DDRC2_TWTR_7                    (0x7UL << 24)
#define AT91C_DDRC2_TMRD	(0xFUL << 28)
#define 	AT91C_DDRC2_TMRD_0		(0x0UL << 28)
#define 	AT91C_DDRC2_TMRD_1		(0x1UL << 28)
#define 	AT91C_DDRC2_TMRD_2		(0x2UL << 28)
#define 	AT91C_DDRC2_TMRD_3		(0x3UL << 28)
#define 	AT91C_DDRC2_TMRD_4		(0x4UL << 28)
#define 	AT91C_DDRC2_TMRD_5		(0x5UL << 28)
#define 	AT91C_DDRC2_TMRD_6		(0x6UL << 28)
#define 	AT91C_DDRC2_TMRD_7		(0x7UL << 28)
#define 	AT91C_DDRC2_TMRD_8		(0x8UL << 28)
#define 	AT91C_DDRC2_TMRD_9		(0x9UL << 28)
#define 	AT91C_DDRC2_TMRD_10		(0xAUL << 28)
#define 	AT91C_DDRC2_TMRD_11		(0xBUL << 28)
#define 	AT91C_DDRC2_TMRD_12		(0xCUL << 28)
#define 	AT91C_DDRC2_TMRD_13		(0xDUL << 28)
#define 	AT91C_DDRC2_TMRD_14		(0xEUL << 28)
#define 	AT91C_DDRC2_TMRD_15		(0xFUL << 28)

/* -------- HDDRSDRC2_T1PR : (HDDRSDRC2 Offset: 0x10) Timing1 Register -------- */
#define AT91C_DDRC2_TRFC	(0x1FUL <<  0)
#define 	AT91C_DDRC2_TRFC_0		(0x0UL)
#define 	AT91C_DDRC2_TRFC_1		(0x1UL)
#define 	AT91C_DDRC2_TRFC_2		(0x2UL)
#define 	AT91C_DDRC2_TRFC_3		(0x3UL)
#define 	AT91C_DDRC2_TRFC_4		(0x4UL)
#define 	AT91C_DDRC2_TRFC_5		(0x5UL)
#define 	AT91C_DDRC2_TRFC_6		(0x6UL)
#define 	AT91C_DDRC2_TRFC_7		(0x7UL)
#define 	AT91C_DDRC2_TRFC_8		(0x8UL)
#define 	AT91C_DDRC2_TRFC_9		(0x9UL)
#define 	AT91C_DDRC2_TRFC_10		(0xAUL)
#define 	AT91C_DDRC2_TRFC_11		(0xBUL)
#define 	AT91C_DDRC2_TRFC_12		(0xCUL)
#define 	AT91C_DDRC2_TRFC_13		(0xDUL)
#define 	AT91C_DDRC2_TRFC_14		(0xEUL)
#define 	AT91C_DDRC2_TRFC_15		(0xFUL)
#define 	AT91C_DDRC2_TRFC_16		(0x10UL)
#define 	AT91C_DDRC2_TRFC_17		(0x11UL)
#define 	AT91C_DDRC2_TRFC_18		(0x12UL)
#define 	AT91C_DDRC2_TRFC_19		(0x13UL)
#define 	AT91C_DDRC2_TRFC_20		(0x14UL)
#define 	AT91C_DDRC2_TRFC_21		(0x15UL)
#define 	AT91C_DDRC2_TRFC_22		(0x16UL)
#define 	AT91C_DDRC2_TRFC_23		(0x17UL)
#define 	AT91C_DDRC2_TRFC_24		(0x18UL)
#define 	AT91C_DDRC2_TRFC_25		(0x19UL)
#define 	AT91C_DDRC2_TRFC_26		(0x1AUL)
#define 	AT91C_DDRC2_TRFC_27		(0x1BUL)
#define 	AT91C_DDRC2_TRFC_28		(0x1CUL)
#define 	AT91C_DDRC2_TRFC_29		(0x1DUL)
#define 	AT91C_DDRC2_TRFC_30		(0x1EUL)
#define 	AT91C_DDRC2_TRFC_31		(0x1FUL)
#define AT91C_DDRC2_TXSNR	(0xFFUL << 8)
#define 	AT91C_DDRC2_TXSNR_0		(0x0UL << 8)
#define 	AT91C_DDRC2_TXSNR_8		(0x8UL << 8)
#define 	AT91C_DDRC2_TXSNR_16		(0x10UL << 8)
#define 	AT91C_DDRC2_TXSNR_19		(0x13UL << 8)
#define 	AT91C_DDRC2_TXSNR_28		(0x1CUL << 8)
#define 	AT91C_DDRC2_TXSNR_32		(0x20UL << 8)
#define		AT91C_DDRC2_TXSNR_35		(0x23UL << 8)
#define 	AT91C_DDRC2_TXSNR_48		(0x30UL << 8)
#define 	AT91C_DDRC2_TXSNR_64		(0x40UL << 8)
#define 	AT91C_DDRC2_TXSNR_80		(0x50UL << 8)
#define 	AT91C_DDRC2_TXSNR_96		(0x60UL << 8)
#define 	AT91C_DDRC2_TXSNR_112		(0x70UL << 8)
#define 	AT91C_DDRC2_TXSNR_128		(0x80UL << 8)
#define 	AT91C_DDRC2_TXSNR_144		(0x90UL << 8)
#define 	AT91C_DDRC2_TXSNR_160		(0xA0UL << 8)
#define 	AT91C_DDRC2_TXSNR_176		(0xB0UL << 8)
#define 	AT91C_DDRC2_TXSNR_192		(0xC0UL << 8)
#define 	AT91C_DDRC2_TXSNR_208		(0xD0UL << 8)
#define 	AT91C_DDRC2_TXSNR_224		(0xE0UL << 8)
#define 	AT91C_DDRC2_TXSNR_240		(0xF0UL << 8)
#define 	AT91C_DDRC2_TXSNR_255		(0xFFUL << 8)

#define AT91C_DDRC2_TXSR(val) (((val)&0x0FF)<<8)

#define AT91C_DDRC2_TXSRD	(0xFFUL << 16)
#define 	AT91C_DDRC2_TXSRD_0		(0x0UL << 16)
#define 	AT91C_DDRC2_TXSRD_8		(0x8UL << 16)
#define 	AT91C_DDRC2_TXSRD_16		(0x10UL << 16)
#define 	AT91C_DDRC2_TXSRD_32		(0x20UL << 16)
#define 	AT91C_DDRC2_TXSRD_48		(0x30UL << 16)
#define 	AT91C_DDRC2_TXSRD_64		(0x40UL << 16)
#define 	AT91C_DDRC2_TXSRD_80		(0x50UL << 16)
#define 	AT91C_DDRC2_TXSRD_96		(0x60UL << 16)
#define 	AT91C_DDRC2_TXSRD_112		(0x70UL << 16)
#define 	AT91C_DDRC2_TXSRD_128		(0x80UL << 16)
#define 	AT91C_DDRC2_TXSRD_144		(0x90UL << 16)
#define 	AT91C_DDRC2_TXSRD_160		(0xA0UL << 16)
#define 	AT91C_DDRC2_TXSRD_176		(0xB0UL << 16)
#define 	AT91C_DDRC2_TXSRD_192		(0xC0UL << 16)
#define 	AT91C_DDRC2_TXSRD_200		(0xC8UL << 16)
#define 	AT91C_DDRC2_TXSRD_202		(0xCAUL << 16)
#define 	AT91C_DDRC2_TXSRD_208		(0xD0UL << 16)
#define 	AT91C_DDRC2_TXSRD_224		(0xE0UL << 16)
#define 	AT91C_DDRC2_TXSRD_240		(0xF0UL << 16)
#define 	AT91C_DDRC2_TXSRD_255		(0xFFUL << 16)
#define AT91C_DDRC2_TXP		(0xFUL << 24)
#define 	AT91C_DDRC2_TXP_0		(0x0UL << 24)
#define 	AT91C_DDRC2_TXP_1		(0x1UL << 24)
#define 	AT91C_DDRC2_TXP_2		(0x2UL << 24)
#define 	AT91C_DDRC2_TXP_3		(0x3UL << 24)
#define 	AT91C_DDRC2_TXP_4		(0x4UL << 24)
#define 	AT91C_DDRC2_TXP_5		(0x5UL << 24)
#define 	AT91C_DDRC2_TXP_6		(0x6UL << 24)
#define 	AT91C_DDRC2_TXP_7		(0x7UL << 24)
#define 	AT91C_DDRC2_TXP_8		(0x8UL << 24)
#define 	AT91C_DDRC2_TXP_9		(0x9UL << 24)
#define 	AT91C_DDRC2_TXP_10		(0xAUL << 24)
#define 	AT91C_DDRC2_TXP_11		(0xBUL << 24)
#define 	AT91C_DDRC2_TXP_12		(0xCUL << 24)
#define 	AT91C_DDRC2_TXP_13		(0xDUL << 24)
#define 	AT91C_DDRC2_TXP_14		(0xEUL << 24)
#define 	AT91C_DDRC2_TXP_15		(0xFUL << 24)

/* -------- HDDRSDRC2_T2PR : (HDDRSDRC2 Offset: 0x14) Timing2 Register --------*/
#define AT91C_DDRC2_TXARD	(0xFUL << 0) 
#define 	AT91C_DDRC2_TXARD_0		(0x0UL)
#define 	AT91C_DDRC2_TXARD_1		(0x1UL)
#define 	AT91C_DDRC2_TXARD_2		(0x2UL)
#define 	AT91C_DDRC2_TXARD_3		(0x3UL)
#define 	AT91C_DDRC2_TXARD_4		(0x4UL)
#define 	AT91C_DDRC2_TXARD_5		(0x5UL)
#define 	AT91C_DDRC2_TXARD_6		(0x6UL)
#define 	AT91C_DDRC2_TXARD_7		(0x7UL)
#define 	AT91C_DDRC2_TXARD_8		(0x8UL)
#define 	AT91C_DDRC2_TXARD_9		(0x9UL)
#define 	AT91C_DDRC2_TXARD_10		(0xAUL)
#define 	AT91C_DDRC2_TXARD_11		(0xBUL)
#define 	AT91C_DDRC2_TXARD_12		(0xCUL)
#define 	AT91C_DDRC2_TXARD_13		(0xDUL)
#define 	AT91C_DDRC2_TXARD_14		(0xEUL)
#define 	AT91C_DDRC2_TXARD_15		(0xFUL)
#define AT91C_DDRC2_TXARDS	(0xFUL << 4)
#define 	AT91C_DDRC2_TXARDS_0		(0x0UL << 4)
#define 	AT91C_DDRC2_TXARDS_1		(0x1UL << 4)
#define 	AT91C_DDRC2_TXARDS_2		(0x2UL << 4)
#define 	AT91C_DDRC2_TXARDS_3		(0x3UL << 4)
#define 	AT91C_DDRC2_TXARDS_4		(0x4UL << 4)
#define 	AT91C_DDRC2_TXARDS_5		(0x5UL << 4)
#define 	AT91C_DDRC2_TXARDS_6		(0x6UL << 4)
#define 	AT91C_DDRC2_TXARDS_7		(0x7UL << 4)
#define 	AT91C_DDRC2_TXARDS_8		(0x8UL << 4)
#define 	AT91C_DDRC2_TXARDS_9		(0x9UL << 4)
#define 	AT91C_DDRC2_TXARDS_10		(0xAUL << 4)
#define 	AT91C_DDRC2_TXARDS_11		(0xBUL << 4)
#define 	AT91C_DDRC2_TXARDS_12		(0xCUL << 4)
#define 	AT91C_DDRC2_TXARDS_13		(0xDUL << 4)
#define 	AT91C_DDRC2_TXARDS_14		(0xEUL << 4)
#define 	AT91C_DDRC2_TXARDS_15		(0xFUL << 4)
#define AT91C_DDRC2_TRPA	(0xFUL << 8)
#define 	AT91C_DDRC2_TRPA_0		(0x0UL << 8)
#define 	AT91C_DDRC2_TRPA_1		(0x1UL << 8)
#define 	AT91C_DDRC2_TRPA_2		(0x2UL << 8)
#define 	AT91C_DDRC2_TRPA_3		(0x3UL << 8)
#define 	AT91C_DDRC2_TRPA_4		(0x4UL << 8)
#define 	AT91C_DDRC2_TRPA_5		(0x5UL << 8)
#define 	AT91C_DDRC2_TRPA_6		(0x6UL << 8)
#define 	AT91C_DDRC2_TRPA_7		(0x7UL << 8)
#define 	AT91C_DDRC2_TRPA_8		(0x8UL << 8)
#define 	AT91C_DDRC2_TRPA_9		(0x9UL << 8)
#define 	AT91C_DDRC2_TRPA_10		(0xAUL << 8)
#define 	AT91C_DDRC2_TRPA_11		(0xBUL << 8)
#define 	AT91C_DDRC2_TRPA_12		(0xCUL << 8)
#define 	AT91C_DDRC2_TRPA_13		(0xDUL << 8)
#define 	AT91C_DDRC2_TRPA_14		(0xEUL << 8)
#define 	AT91C_DDRC2_TRPA_15		(0xFUL << 8)
#define AT91C_DDRC2_TRTP		(0xFUL << 12)
#define 	AT91C_DDRC2_TRTP_0		(0x0UL << 12)
#define 	AT91C_DDRC2_TRTP_1		(0x1UL << 12)
#define 	AT91C_DDRC2_TRTP_2		(0x2UL << 12)
#define 	AT91C_DDRC2_TRTP_3		(0x3UL << 12)
#define 	AT91C_DDRC2_TRTP_4		(0x4UL << 12)
#define 	AT91C_DDRC2_TRTP_5		(0x5UL << 12)
#define 	AT91C_DDRC2_TRTP_6		(0x6UL << 12)
#define 	AT91C_DDRC2_TRTP_7		(0x7UL << 12)
#define 	AT91C_DDRC2_TRTP_8		(0x8UL << 12)
#define 	AT91C_DDRC2_TRTP_9		(0x9UL << 12)
#define 	AT91C_DDRC2_TRTP_10		(0xAUL << 12)
#define 	AT91C_DDRC2_TRTP_11		(0xBUL << 12)
#define 	AT91C_DDRC2_TRTP_12		(0xCUL << 12)
#define 	AT91C_DDRC2_TRTP_13		(0xDUL << 12)
#define 	AT91C_DDRC2_TRTP_14		(0xEUL << 12)
#define 	AT91C_DDRC2_TRTP_15		(0xFUL << 12)
#define AT91C_DDRC2_TFAW		(0xFUL << 16)
#define 	AT91C_DDRC2_TFAW_0		(0x0UL << 16)
#define 	AT91C_DDRC2_TFAW_1		(0x1UL << 16)
#define 	AT91C_DDRC2_TFAW_2		(0x2UL << 16)
#define 	AT91C_DDRC2_TFAW_3		(0x3UL << 16)
#define 	AT91C_DDRC2_TFAW_4		(0x4UL << 16)
#define 	AT91C_DDRC2_TFAW_5		(0x5UL << 16)
#define 	AT91C_DDRC2_TFAW_6		(0x6UL << 16)
#define 	AT91C_DDRC2_TFAW_7		(0x7UL << 16)
#define 	AT91C_DDRC2_TFAW_8		(0x8UL << 16)
#define 	AT91C_DDRC2_TFAW_9		(0x9UL << 16)
#define 	AT91C_DDRC2_TFAW_10		(0xAUL << 16)
#define 	AT91C_DDRC2_TFAW_11		(0xBUL << 16)
#define 	AT91C_DDRC2_TFAW_12		(0xCUL << 16)
#define 	AT91C_DDRC2_TFAW_13		(0xDUL << 16)
#define 	AT91C_DDRC2_TFAW_14		(0xEUL << 16)
#define 	AT91C_DDRC2_TFAW_15		(0xFUL << 16)

/* -------- HDDRSDRC2_LPR : (HDDRSDRC2 Offset: 0x1c) --------*/
#define AT91C_DDRC2_LPCB	(0x3UL << 0)
#define 	AT91C_DDRC2_LPCB_DISABLED	(0x0UL)
#define 	AT91C_DDRC2_LPCB_SELFREFRESH	(0x1UL)
#define 	AT91C_DDRC2_LPCB_POWERDOWN	(0x2UL)
#define 	AT91C_DDRC2_LPCB_DEEP_PWD	(0x3UL)
#define AT91C_DDRC2_CLK_FR	(0x1UL << 2)
#define AT91C_DDRC2_PASR	(0x7UL << 4)
#define AT91C_DDRC2_DS		(0x7UL << 8)
#define AT91C_DDRC2_TIMEOUT	(0x3UL << 12)
#define 	AT91C_DDRC2_TIMEOUT_0		(0x0UL << 12)
#define 	AT91C_DDRC2_TIMEOUT_64		(0x1UL << 12)
#define 	AT91C_DDRC2_TIMEOUT_128		(0x2UL << 12)
#define 	AT91C_DDRC2_TIMEOUT_Reserved	(0x3UL << 12)
#define AT91C_DDRC2_ADPE	(0x1UL << 16)
#define 	AT91C_DDRC2_ADPE_FAST		(0x0UL << 16)
#define 	AT91C_DDRC2_ADPE_SLOW		(0x1UL << 16)
#define AT91C_DDRC2_UPD_MR	(0x3UL << 20)

/* -------- HDDRSDRC2_MDR : (HDDRSDRC2 Offset: 0x20) Memory Device Register -------- */
#define AT91C_DDRC2_MD		(0x7UL << 0)
#define 	AT91C_DDRC2_MD_SDR_SDRAM	(0x0UL)
#define 	AT91C_DDRC2_MD_LP_SDR_SDRAM	(0x1UL)
#define 	AT91C_DDRC2_MD_DDR_SDRAM	(0x2UL)
#define 	AT91C_DDRC2_MD_LP_DDR_SDRAM	(0x3UL)
#define 	AT91C_DDRC2_MD_DDR2_SDRAM	(0x6UL)
#define AT91C_DDRC2_DBW		(0x1UL << 4)
#define 	AT91C_DDRC2_DBW_32_BITS		(0x0UL << 4)
#define 	AT91C_DDRC2_DBW_16_BITS		(0x1UL << 4)

/* -------- HDDRSDRC2_DLL : (HDDRSDRC2 Offset: 0x24) DLL Information Register --------*/ 
#define AT91C_DDRC2_MDINC	(0x1UL << 0)
#define AT91C_DDRC2_MDDEC	(0x1UL << 1)
#define AT91C_DDRC2_MDOVF	(0x1UL << 2)
#define AT91C_DDRC2_MDVAL	(0xFFUL << 8

/* -------- HDDRSDRC2_HS : (HDDRSDRC2 Offset: 0x2c) High Speed Register --------*/ 
#define AT91C_DDRC2_NO_ANT	(0x1UL << 2)

/* -------- MPDDRC_IO_CALIBR : (MPDDRC Offset: 0x34) IO Calibration --------*/
#define AT91C_MPDDRC_RDIV	(0x7UL << 0)
#define 	AT91C_MPDDRC_RDIV_LPDDR2_RZQ_34		(0x1UL << 0)
#define 	AT91C_MPDDRC_RDIV_LPDDR2_RZQ_48		(0x3UL << 0)
#define 	AT91C_MPDDRC_RDIV_LPDDR2_RZQ_60		(0x4UL << 0)
#define 	AT91C_MPDDRC_RDIV_LPDDR2_RZQ_120	(0x7UL << 0)

#define 	AT91C_MPDDRC_RDIV_DDR2_RZQ_33_3		(0x2UL << 0)
#define 	AT91C_MPDDRC_RDIV_DDR2_RZQ_50		(0x4UL << 0)
#define 	AT91C_MPDDRC_RDIV_DDR2_RZQ_100		(0x7UL << 0)

#define AT91C_MPDDRC_TZQIO	(0x1FUL << 8)
#define 	AT91C_MPDDRC_TZQIO_0			(0x0UL << 8)
#define 	AT91C_MPDDRC_TZQIO_1			(0x1UL << 8)
#define 	AT91C_MPDDRC_TZQIO_4			(0x4UL << 8)
#define 	AT91C_MPDDRC_TZQIO_31			(0x1FUL << 8)

/* -------- MPDDRC_LPR : (MPDDRC Offset: 0x1C) Low-power Register --------*/

#define AT91C_MPDDRC_LPR_LPCB_NOLOWPOWER (0x0)
#define AT91C_MPDDRC_LPR_LPCB_SELFREFRESH (0x1)
#define AT91C_MPDDRC_LPR_LPCB_POWERDOWN (0x2)
#define AT91C_MPDDRC_LPR_LPCB_DEEPPOWERDOWN (0x3)

#define AT91C_MPDDRC_LPR_PASR(val) (((val) & 7) << 4)
#define AT91C_MPDDRC_LPR_DS(val) (((val) & 7) << 8)

#define AT91C_MPDDRC_LPR_CLK_FR_ENABLE (1 << 2)
#define AT91C_MPDDRC_LPR_CLK_FR_DISABLE (0 << 2)

#define AT91C_MPDDRC_LPR_TIMEOUT_NONE (0 << 12)
#define AT91C_MPDDRC_LPR_TIMEOUT_64CK (1 << 12)
#define AT91C_MPDDRC_LPR_TIMEOUT_128CK (2 << 12)

#define AT91C_MPDDRC_LPR_UPD_MR_NO_UPDATE (0 << 20)
#define AT91C_MPDDRC_LPR_UPD_MR_UPDATE_SHAREDBUS (1 << 20)
#define AT91C_MPDDRC_LPR_UPD_MR_UPDATE_NOSHAREDBUS (2 << 20)


/* -------- MPDDRC_DLL_MOR : (MPDDRC Offset: 0x74) DLL Master Offset Register --------*/
#define AT91C_MPDDRC_MOFF	(0xFUL << 0)
#define 	AT91C_MPDDRC_MOFF_1	(0x1UL << 0)
#define 	AT91C_MPDDRC_MOFF_7	(0x7UL << 0)
#define AT91C_MPDDRC_CLK90OFF	(0x1FUL << 8)
#define 	AT91C_MPDDRC_CLK90OFF_1		(0x1UL << 8)
#define 	AT91C_MPDDRC_CLK90OFF_31	(0x1FUL << 8)
#define AT91C_MPDDRC_SELOFF	(0x1UL << 16)
#define 	AT91C_MPDDRC_SELOFF_DISABLED	(0x0UL << 16)
#define 	AT91C_MPDDRC_SELOFF_ENABLED	(0x1UL << 16)
#define AT91C_MPDDRC_KEY	(0xC5UL << 24)

/* -------- MPDDRC_DLL_SOR : (MPDDRC Offset: 0x78) DLL Slave Offset Register --------*/
#define AT91C_MPDDRC_S0OFF_1	(0x1UL << 0)
#define AT91C_MPDDRC_S1OFF_1	(0x1UL << 8)
#define AT91C_MPDDRC_S2OFF_1	(0x1UL << 16)
#define AT91C_MPDDRC_S3OFF_1	(0x1UL << 24)

/* -------- HDDRSDRC2_WPCR : (HDDRSDRC2 Offset: 0xe4) Write Protect Control Register --------*/ 
#define AT91C_DDRC2_WPEN	(0x1UL << 0)
#define AT91C_DDRC2_WPKEY	(0xFFFFFFUL << 8)

/* -------- HDDRSDRC2_WPSR : (HDDRSDRC2 Offset: 0xe8) Write Protect Status Register --------*/ 
#define AT91C_DDRC2_WPVS	(0x1UL << 0)
#define AT91C_DDRC2_WPSRC	(0xFFFFUL << 8)

#endif	/* #ifndef __AT91_DDRSDRC_H__ */
