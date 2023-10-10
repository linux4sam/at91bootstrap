/*
 * Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_XDMAC_H__
#define __AT91_XDMAC_H__

/*** Register offset in AT91S_XDMAC structure ***/
#define XDMAC_GTYPE	0x00
#define XDMAC_GCFG	0x04
#define XDMAC_GWAC	0x08
#define XDMAC_GIE	0x0C
#define XDMAC_GID	0x10
#define XDMAC_GIM	0x14
#define XDMAC_GIS	0x18
#define XDMAC_GE	0x1C
#define XDMAC_GD	0x20
#define XDMAC_GS	0x24
#define XDMAC_GRS	0x28
#define XDMAC_GWS	0x2C
#define XDMAC_GRWS	0x30
#define XDMAC_GRWR	0x34
#define XDMAC_GSWR	0x38
#define XDMAC_GSWS	0x3C
#define XDMAC_GSWF	0x40
#if defined(CONFIG_SAMA7G5) || defined(CONFIG_SAMA7D65)
#define XDMAC_CHAN(i)	(0x60 + ((i) * 0x40))
#else
#define XDMAC_CHAN(i)	(0x50 + ((i) * 0x40))
#endif

/*** Channel relative registers offsets ***/
#define XDMAC_CIE	0x00
#define XDMAC_CID	0x04
#define XDMAC_CIM	0x08
#define XDMAC_CIS	0x0C
#define XDMAC_CSA	0x10
#define XDMAC_CDA	0x14
#define XDMAC_CNDA	0x18
#define XDMAC_CNDC	0x1C
#define XDMAC_CUBC	0x20
#define XDMAC_CBC	0x24
#define XDMAC_CC	0x28
#define XDMAC_CDS_MSP	0x2C
#define XDMAC_CSUS	0x30
#define XDMAC_CDUS	0x34

/*-------- XDMAC_GTYPE: (Offset: 0x0) -------*/
#define XDMAC_GTYPE_NB_CH(i)	(((i) & 0x1F) + 1)
#define XDMAC_GTYPE_FIFO_SZ(i)	(((i) >> 5) & 0x7FF)
#define XDMAC_GTYPE_NB_REQ(i)	((((i) >> 16) & 0x3F) + 1)

/*-------- XDMAC_GCFG: (Offset: 0x4) -------*/
#define XDMAC_GCFG_CGDISREG	(0x1 << 0)
#define XDMAC_GCFG_CGDISPIPE	(0x1 << 1)
#define XDMAC_GCFG_CGDISFIFO	(0x1 << 2)
#define XDMAC_GCFG_CGDISIF	(0x1 << 3)
#define XDMAC_GCFG_BXKBEN	(0x1 << 8)

/*-------- XDMAC_GWAC: (Offset: 0x8) -------*/
#define XDMAC_GWAC_PW0(i)	(((i) & 0xF) << 0)
#define XDMAC_GWAC_PW1(i)	(((i) & 0xF) << 4)
#define XDMAC_GWAC_PW2(i)	(((i) & 0xF) << 8)
#define XDMAC_GWAC_PW3(i)	(((i) & 0xF) << 12)

/*-------- XDMAC_CI: (Offset: 0x50) -------*/
#define XDMAC_CI_BI	(0x1 << 0)
#define XDMAC_CI_LI	(0x1 << 1)
#define XDMAC_CI_DI	(0x1 << 2)
#define XDMAC_CI_FI	(0x1 << 3)
#define XDMAC_CI_RBE	(0x1 << 4)
#define XDMAC_CI_WBE	(0x1 << 5)
#define XDMAC_CI_ROE	(0x1 << 6)

/*-------- XDMAC_CNDA: (Offset: 0x68) -------*/
#define XDMAC_CNDA_NDAIF	(0x1 << 0)
#define XDMAC_CNDA_NDA(i)	((i) & 0xFFFFFFFC)

/*-------- XDMAC_CNDC: (Offset: 0x6C) -------*/
#define XDMAC_CNDC_NDE		(0x1 << 0)
#define XDMAC_CNDC_NDSUP	(0x1 << 1)
#define XDMAC_CNDC_NDDUP	(0x1 << 2)
#define XDMAC_CNDC_NDVIEW_MASK	(0x3 << 3)
#define XDMAC_CNDC_NDVIEW_NDV0	(0x0 << 3)
#define XDMAC_CNDC_NDVIEW_NDV1	(0x1 << 3)
#define XDMAC_CNDC_NDVIEW_NDV2	(0x2 << 3)
#define XDMAC_CNDC_NDVIEW_NDV3	(0x3 << 3)
#define XDMAC_CNDC_QOS_MASK	(0x3 << 5)
#define XDMAC_CNDC_QOS(i)	(((i) << 5) & XDMAC_CNDC_QOS_MASK)

/*-------- XDMAC_CUBC: (Offset: 0x70) -------*/
#define XDMAC_CUBC_UBLEN_MASK	(0xFFFFFF << 0)
#define XDMAC_CUBC_UBLEN(i)	(((i) << 0) & XDMAC_CUBC_UBLEN_MASK)

/*-------- XDMAC_CBC: (Offset: 0x74) -------*/
#define XDMAC_CBC_BLEN_MASK	(0xFFF << 0)
#define XDMAC_CBC_BLEN(i)	(((i) << 0) & XDMAC_CBC_BLEN_MASK)

/*-------- XDMAC_CC: (Offset: 0x78) -------*/
#define XDMAC_CC_TYPE_PER_TRAN	(0x1 << 0)
#define XDMAC_CC_TYPE_MEM_TRAN	(0x0 << 0)
#define XDMAC_CC_TYPE_PER_TRAN	(0x1 << 0)
#define XDMAC_CC_MBSIZE_MASK	(0x3 << 1)
#define XDMAC_CC_MBSIZE_SINGLE	(0x0 << 1)
#define XDMAC_CC_MBSIZE_FOUR	(0x1 << 1)
#define XDMAC_CC_MBSIZE_EIGHT	(0x2 << 1)
#define XDMAC_CC_MBSIZE_SIXTEEN	(0x3 << 1)
#define XDMAC_CC_MBSIZE(i)		(((i) & 0x3) << 1)
#define XDMAC_CC_DSYNC		(0x1 << 4)
#define XDMAC_CC_DSYNC_PER2MEM	(0x0 << 4)
#define XDMAC_CC_DSYNC_MEM2PER	(0x1 << 4)
#define XDMAC_CC_PROT		(0x1 << 5)
#define XDMAC_CC_PROT_SEC	(0x0 << 5)
#define XDMAC_CC_PROT_UNSEC	(0x1 << 5)
#define XDMAC_CC_SWREQ		(0x1 << 6)
#define XDMAC_CC_SWREQ_HWR_CONNECTED	(0x0 << 6)
#define XDMAC_CC_SWREQ_SWR_CONNECTED	(0x1 << 6)
#define XDMAC_CC_MEMSET			(0x1 << 7)
#define XDMAC_CC_MEMSET_NORMAL_MODE	(0x0 << 7)
#define XDMAC_CC_MEMSET_HW_MODE		(0x1 << 7)
#define XDMAC_CC_CSIZE(i)		(((i) & 0x7) << 8)
#define XDMAC_CC_DWIDTH_OFFSET		11
#define XDMAC_CC_DWIDTH_MASK		(0x3 << 11)
#define XDMAC_CC_DWIDTH(i)		(((i) & 0x3) << 11)
#define XDMAC_CC_DWIDTH_BYTE		0x0
#define XDMAC_CC_DWIDTH_HALFWORD	0x1
#define XDMAC_CC_DWIDTH_WORD		0x2
#define XDMAC_CC_DWIDTH_DWORD		0x3
#define XDMAC_CC_SIF(i)			(((i) & 0x1) << 13)
#define XDMAC_CC_DIF(i)			(((i) & 0x1) << 14)
#define XDMAC_CC_SAM_MASK		(0x3 << 16)
#define XDMAC_CC_SAM_FIXED_AM		(0x0 << 16)
#define XDMAC_CC_SAM_INCREMENTED_AM	(0x1 << 16)
#define XDMAC_CC_SAM_UBS_AM		(0x2 << 16)
#define XDMAC_CC_SAM_UBS_DS_AM		(0x3 << 16)
#define XDMAC_CC_DAM_MASK		(0x3 << 18)
#define XDMAC_CC_DAM_FIXED_AM		(0x0 << 18)
#define XDMAC_CC_DAM_INCREMENTED_AM	(0x1 << 18)
#define XDMAC_CC_DAM_UBS_AM		(0x2 << 18)
#define XDMAC_CC_DAM_UBS_DS_AM		(0x3 << 18)
#define XDMAC_CC_INITD			(0x1 << 21)
#define XDMAC_CC_INITD_TERMINATED	(0x0 << 21)
#define XDMAC_CC_INITD_IN_PROGRESS	(0x1 << 21)
#define XDMAC_CC_RDIP			(0x1 << 22)
#define XDMAC_CC_RDIP_DONE		(0x0 << 22)
#define XDMAC_CC_RDIP_IN_PROGRESS	(0x1 << 22)
#define XDMAC_CC_WRIP			(0x1 << 23)
#define XDMAC_CC_WRIP_DONE		(0x0 << 23)
#define XDMAC_CC_WRIP_IN_PROGRESS	(0x1 << 23)
#define XDMAC_CC_PERID(i)		(((i) & 0x7f) << 24)

/*-------- XDMAC_CDS_MSP: (Offset: 0x7C) -------*/
#define XDMAC_CDS_MSP_SDS_MSP_MASK	(0xFFFF << 0)
#define XDMAC_CDS_MSP_SDS_MSP(i)	(((i) << 0) & XDMAC_CDS_MSP_SDS_MSP_MASK)
#define XDMAC_CDS_MSP_DDS_MSP_MASK	(0xFFFF << 16)
#define XDMAC_CDS_MSP_DDS_MSP(i)	(((i) << 16) & XDMAC_CDS_MSP_DDS_MSP_MASK)

/*-------- XDMAC_CSUS: (Offset: 0x80) -------*/
#define XDMAC_CSUS_SUBS_MASK	(0xFFFFFF << 0)
#define XDMAC_CSUS_SUBS(i)	(((i) << 0) & XDMAC_CSUS_SUBS_MASK)

/*-------- XDMAC_CDUS: (Offset: 0x84) -------*/
#define XDMAC_CDUS_DUBS_MASK	(0xFFFFFF << 0)
#define XDMAC_CDUS_DUBS(i)	(((i) << 0) & XDMAC_CDUS_DUBS_MASK)

#endif /* #ifndef __AT91_XDMAC_H__ */
