/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __TZ_MATRIX_H__
#define __TZ_MATRIX_H__

#define MATRIX_MCFG(n)	(0x0000 + (n) * 4)/* Master Configuration Register */
#define MATRIX_SCFG(n)	(0x0040 + (n) * 4)/* Slave Configuration Register */
#define MATRIX_PRAS(n)	(0x0080 + (n) * 8)/* Priority Register A for Slave */
#define MATRIX_PRBS(n)	(0x0084 + (n) * 8)/* Priority Register B for Slave */

#define MATRIX_MRCR	0x0100	/* Master Remap Control Register */
#define MATRIX_MEIER	0x0150	/* Master Error Interrupt Enable Register */
#define MATRIX_MEIDR	0x0154	/* Master Error Interrupt Disable Register */
#define MATRIX_MEIMR	0x0158	/* Master Error Interrupt Mask Register */
#define MATRIX_MESR	0x015c	/* Master Error Statue Register */

/* Master n Error Address Register */
#define MATRIX_MEAR(n)	(0x0160 + (n) * 4)

#define MATRIX_WPMR	0x01E4		/* Write Protect Mode Register */
#define MATRIX_WPSR	0x01E8		/* Write Protect Status Register */

/* Security Slave n Register */
#define MATRIX_SSR(n)	(0x0200 + (n) * 4)
/* Security Area Split Slave n Register */
#define MATRIX_SASSR(n)	(0x0240 + (n) * 4)
/* Security Region Top Slave n Register */
#define MATRIX_SRTSR(n)	(0x0280 + (n) * 4)

/* Security Peripheral Select n Register */
#define MATRIX_SPSELR(n)	(0x02c0	+ (n) * 4)
#define MATRIX_SPSELR_COUNT	3

/**************************************************************************/
/* Write Protect Mode Register (MATRIX_WPMR) */
#define MATRIX_WPMR_WPEN	(1 << 0)	/* Write Protect Enable */
#define		MATRIX_WPMR_WPEN_DISABLE	(0 << 0)
#define		MATRIX_WPMR_WPEN_ENABLE		(1 << 0)
#define	MATRIX_WPMR_WPKEY	(PASSWD << 8) /* Write Protect KEY */
#define		MATRIX_WPMR_WPKEY_PASSWD	(0x4D4154 << 8)

/* Security Slave Registers (MATRIX_SSRx) */
#define MATRIX_LANSECH(n, bit)	((bit) << n)
#define		MATRIX_LANSECH_S(n)	(0x00 << n)
#define		MATRIX_LANSECH_NS(n)	(0x01 << n)
#define MATRIX_RDNSECH(n, bit)	((bit) << (n + 8))
#define		MATRIX_RDNSECH_S(n)	(0x00 << (n + 8))
#define		MATRIX_RDNSECH_NS(n)	(0x01 << (n + 8))
#define MATRIX_WRNSECH(n, bit)	((bit) << (n + 16))
#define		MATRIX_WRNSECH_S(n)	(0x00 << (n + 16))
#define		MATRIX_WRNSECH_NS(n)	(0x01 << (n + 16))

/* Security Areas Split Slave Registers (MATRIX_SASSRx) */
#define MATRIX_SASPLIT(n, value)	((value) << (4 * n))
#define		MATRIX_SASPLIT_VALUE_4K		0x00
#define		MATRIX_SASPLIT_VALUE_8K		0x01
#define		MATRIX_SASPLIT_VALUE_16K	0x02
#define		MATRIX_SASPLIT_VALUE_32K	0x03
#define		MATRIX_SASPLIT_VALUE_64K	0x04
#define		MATRIX_SASPLIT_VALUE_128K	0x05
#define		MATRIX_SASPLIT_VALUE_256K	0x06
#define		MATRIX_SASPLIT_VALUE_512K	0x07
#define		MATRIX_SASPLIT_VALUE_1M		0x08
#define		MATRIX_SASPLIT_VALUE_2M		0x09
#define		MATRIX_SASPLIT_VALUE_4M		0x0a
#define		MATRIX_SASPLIT_VALUE_8M		0x0b
#define		MATRIX_SASPLIT_VALUE_16M	0x0c
#define		MATRIX_SASPLIT_VALUE_32M	0x0d
#define		MATRIX_SASPLIT_VALUE_64M	0x0e
#define		MATRIX_SASPLIT_VALUE_128M	0x0f

/* Security Region Top Slave Registers (MATRIX_SRTSRx) */
#define MATRIX_SRTOP(n, value)		((value) << (4 * n))
#define		MATRIX_SRTOP_VALUE_4K		0x00
#define		MATRIX_SRTOP_VALUE_8K		0x01
#define		MATRIX_SRTOP_VALUE_16K		0x02
#define		MATRIX_SRTOP_VALUE_32K		0x03
#define		MATRIX_SRTOP_VALUE_64K		0x04
#define		MATRIX_SRTOP_VALUE_128K		0x05
#define		MATRIX_SRTOP_VALUE_256K		0x06
#define		MATRIX_SRTOP_VALUE_512K		0x07
#define		MATRIX_SRTOP_VALUE_1M		0x08
#define		MATRIX_SRTOP_VALUE_2M		0x09
#define		MATRIX_SRTOP_VALUE_4M		0x0a
#define		MATRIX_SRTOP_VALUE_8M		0x0b
#define		MATRIX_SRTOP_VALUE_16M		0x0c
#define		MATRIX_SRTOP_VALUE_32M		0x0d
#define		MATRIX_SRTOP_VALUE_64M		0x0e
#define		MATRIX_SRTOP_VALUE_128M		0x0f

#define QOS_REGULAR_DELIVERY   0
#define QOS_BANDWIDTH_SHORTAGE 1
#define QOS_LATENCY_SENSITIVE  2
#define QOS_LATENCY_CRITICAL   3

#define RESET_DEFAULT_MASTER_SQOS0  QOS_LATENCY_SENSITIVE  /*-- <Master_0>  CSS / CPU -> QOS_LATENCY_SENSITIVE */
#define RESET_DEFAULT_MASTER_SQOS1  QOS_LATENCY_CRITICAL   /*-- <Master_1>  PSS / MASTERx_DRIVES_LQOS=TRUE -> QOS_LATENCY_CRITICAL */
#define RESET_DEFAULT_MASTER_SQOS2  QOS_LATENCY_CRITICAL   /*-- <Master_2>  MSS / MASTERx_DRIVES_LQOS=TRUE -> QOS_LATENCY_CRITICAL */
#define RESET_DEFAULT_MASTER_SQOS3  QOS_REGULAR_DELIVERY   /*-- <Master_3>  MCAN0 */
#define RESET_DEFAULT_MASTER_SQOS4  QOS_REGULAR_DELIVERY   /*-- <Master_4>  MCAN1 */
#define RESET_DEFAULT_MASTER_SQOS5  QOS_REGULAR_DELIVERY   /*-- <Master_5>  MCAN2 */
#define RESET_DEFAULT_MASTER_SQOS6  QOS_REGULAR_DELIVERY   /*-- <Master_6>  MCAN3 */
#define RESET_DEFAULT_MASTER_SQOS7  QOS_REGULAR_DELIVERY   /*-- <Master_7>  MCAN4 */
#define RESET_DEFAULT_MASTER_SQOS8  QOS_REGULAR_DELIVERY   /*-- <Master_8>  MCAN5 */
#define RESET_DEFAULT_MASTER_SQOS9  QOS_REGULAR_DELIVERY   /*-- <Master_9>  ICM */
#define RESET_DEFAULT_MASTER_SQOS10 QOS_REGULAR_DELIVERY   /*-- <Master_10> UDPHS0_DMA */
#define RESET_DEFAULT_MASTER_SQOS11 QOS_REGULAR_DELIVERY   /*-- <Master_11> UDPHS1_DMA */
#define RESET_DEFAULT_MASTER_SQOS12 QOS_REGULAR_DELIVERY   /*-- <Master_12> OHCI_DMA */
#define RESET_DEFAULT_MASTER_SQOS13 QOS_REGULAR_DELIVERY   /*-- <Master_13> EHCI_DMA */
#define RESET_DEFAULT_MASTER_SQOS14 QOS_LATENCY_CRITICAL   /*-- <Master_14> AESB / MASTERx_DRIVES_LQOS=TRUE -> QOS_LATENCY_CRITICAL */
#define RESET_DEFAULT_MASTER_SQOS15 QOS_REGULAR_DELIVERY   /*-- <Master_15> */

#define MATRIX_SLAVE_PORTS 10

#define MATRIX_PRAS0	0x80
#define MATRIX_PRAS1	(MATRIX_PRAS0 + 0x8)
#define MATRIX_PRAS2	(MATRIX_PRAS1 + 0x8)
#define MATRIX_PRAS3	(MATRIX_PRAS2 + 0x8)
#define MATRIX_PRAS4	(MATRIX_PRAS3 + 0x8)
#define MATRIX_PRAS5	(MATRIX_PRAS4 + 0x8)
#define MATRIX_PRAS6	(MATRIX_PRAS5 + 0x8)
#define MATRIX_PRAS7	(MATRIX_PRAS6 + 0x8)
#define MATRIX_PRAS8	(MATRIX_PRAS7 + 0x8)
#define MATRIX_PRAS9	(MATRIX_PRAS8 + 0x8)

#define MATRIX_PRBS0	0x84
#define MATRIX_PRBS1	(MATRIX_PRBS0 + 0x8)
#define MATRIX_PRBS2	(MATRIX_PRBS1 + 0x8)
#define MATRIX_PRBS3	(MATRIX_PRBS2 + 0x8)
#define MATRIX_PRBS4	(MATRIX_PRBS3 + 0x8)
#define MATRIX_PRBS5	(MATRIX_PRBS4 + 0x8)
#define MATRIX_PRBS6	(MATRIX_PRBS5 + 0x8)
#define MATRIX_PRBS7	(MATRIX_PRBS6 + 0x8)
#define MATRIX_PRBS8	(MATRIX_PRBS7 + 0x8)
#define MATRIX_PRBS9	(MATRIX_PRBS8 + 0x8)

#define MATRIX_PRAS_M0PR_MASK	(0x3 << 0)
#define MATRIX_PRAS_M1PR_MASK	(0x3 << 4)
#define MATRIX_PRAS_M2PR_MASK	(0x3 << 8)
#define MATRIX_PRAS_M3PR_MASK	(0x3 << 12)
#define MATRIX_PRAS_M4PR_MASK	(0x3 << 16)
#define MATRIX_PRAS_M5PR_MASK	(0x3 << 20)
#define MATRIX_PRAS_M6PR_MASK	(0x3 << 24)
#define MATRIX_PRAS_M7PR_MASK	(0x3 << 28)

#define MATRIX_PRAS_M8PR_MASK	(0x3 << 0)
#define MATRIX_PRAS_M9PR_MASK	(0x3 << 4)
#define MATRIX_PRAS_M10PR_MASK	(0x3 << 8)
#define MATRIX_PRAS_M11PR_MASK	(0x3 << 12)
#define MATRIX_PRAS_M12PR_MASK	(0x3 << 16)
#define MATRIX_PRAS_M13PR_MASK	(0x3 << 20)
#define MATRIX_PRAS_M14PR_MASK	(0x3 << 24)
#define MATRIX_PRAS_M15PR_MASK	(0x3 << 28)

#define MATRIX_PRAS_M0PR(v)	((v) << 0)
#define MATRIX_PRAS_M1PR(v)	((v) << 4)
#define MATRIX_PRAS_M2PR(v)	((v) << 8)
#define MATRIX_PRAS_M3PR(v)	((v) << 12)
#define MATRIX_PRAS_M4PR(v)	((v) << 16)
#define MATRIX_PRAS_M5PR(v)	((v) << 20)
#define MATRIX_PRAS_M6PR(v)	((v) << 24)
#define MATRIX_PRAS_M7PR(v)	((v) << 28)

#define MATRIX_PRBS_M8PR(v)	((v) << 0)
#define MATRIX_PRBS_M9PR(v)	((v) << 4)
#define MATRIX_PRBS_M10PR(v)	((v) << 8)
#define MATRIX_PRBS_M11PR(v)	((v) << 12)
#define MATRIX_PRBS_M12PR(v)	((v) << 16)
#define MATRIX_PRBS_M13PR(v)	((v) << 20)
#define MATRIX_PRBS_M14PR(v)	((v) << 24)
#define MATRIX_PRBS_M15PR(v)	((v) << 28)

#endif /* #ifndef __TZ_MATRIX_H__ */
