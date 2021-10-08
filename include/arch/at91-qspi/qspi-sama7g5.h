/*
 * Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef	__AT91_QSPI_SAMA7G5_H__
#define	__AT91_QSPI_SAMA7G5_H__

#define QSPI_ISR		0x10
#define QSPI_SR			0x24
#define QSPI_WICR		0x34
#define QSPI_RICR		0x3c
#define QSPI_REFRESH		0x50
#define QSPI_WRACNT		0x54
#define QSPI_DLLCFG		0x58
#define QSPI_PCALCFG		0x5c
#define QSPI_PCALBP		0x60
#define QSPI_TOUT		0x64

#define QSPI_CR_DLLON		(0x1 << 2)
#define QSPI_CR_DLLOFF		(0x1 << 3)
#define QSPI_CR_STPCAL		(0x1 << 4)
#define QSPI_CR_SRFRSH		(0x1 << 5)
#define QSPI_CR_UPDCFG		(0x1 << 8)
#define QSPI_CR_STTFR		(0x1 << 9)
#define QSPI_CR_RTOUT		(0x1 << 10)

#define QSPI_MR_DQSDLYEN	(0x1 << 3)
#define QSPI_MR_OENSD		(0x1 << 15)

#define QSPI_ISR_RDRF		(0x1 << 0)
#define QSPI_ISR_TDRE		(0x1 << 1)
#define QSPI_ISR_TXEMPTY	(0x1 << 2)
#define QSPI_ISR_OVRES		(0x1 << 3)
#define QSPI_ISR_CSR		(0x1 << 8)
#define QSPI_ISR_INSTRE		(0x1 << 10)
#define QSPI_ISR_LWRA		(0x1 << 11)
#define QSPI_ISR_QITF		(0x1 << 12)
#define QSPI_ISR_QITR		(0x1 << 13)
#define QSPI_ISR_CSFA		(0x1 << 14)
#define QSPI_ISR_CSRA		(0x1 << 15)
#define QSPI_ISR_RFRHD		(0x1 << 16)
#define QSPI_ISR_TOUT		(0x1 << 17)

#define QSPI_SR_SYNCBSY		(0x1 << 0)
#define QSPI_SR_QSPIENS		(0x1 << 1)
#define QSPI_SR_CSS		(0x1 << 2)
#define QSPI_SR_RBUSY		(0x1 << 3)
#define QSPI_SR_HIDLE		(0x1 << 4)
#define QSPI_SR_DLOCK		(0x1 << 5)
#define QSPI_SR_CALBSY		(0x1 << 6)

#define QSPI_WICR_WRINST_MASK	0xffff
#define QSPI_WICR_WRINST(x)	((x) & QSPI_WICR_WRINST_MASK)
#define QSPI_WICR_WROPT_MASK	(0xff << 16)
#define QSPI_WICR_WROPT(x)	(((x) << 16) & QSPI_WICR_WROPT_MASK)

#define QSPI_IFR_WIDTH_OCT_OUTPUT       (0x7 << 0)
#define QSPI_IFR_WIDTH_OCT_IO           (0x8 << 0)
#define QSPI_IFR_WIDTH_OCT_CMD          (0x9 << 0)
#define QSPI_IFR_ADDRL_MASK		(0x3 << 10)
#define QSPI_IFR_ADDRL(x)		(((x) << 10) & QSPI_IFR_ADDRL_MASK)
#define QSPI_IFR_DDREN			(0x1 << 15)
#define QSPI_IFR_END			(0x1 << 22)
#define QSPI_IFR_SMRM			(0x1 << 23)
#define QSPI_IFR_APBTFRTYP		(0x1 << 24)
#define QSPI_IFR_DQSEN			(0x1 << 25)
#define QSPI_IFR_DDRCMDEN		(0x1 << 26)
#define QSPI_IFR_HFWBEN			(0x1 << 27)
#define QSPI_IFR_PROTTYP_STD_SPI	(0 << 28)
#define QSPI_IFR_PROTTYP_TWIN_QUAD	(1 << 28)
#define QSPI_IFR_PROTTYP_OCTAFLASH	(2 << 28)
#define QSPI_IFR_PROTTYP_HYPERFLASH	(3 << 28)

#define QSPI_RICR_RDINST_MASK	0xffff
#define QSPI_RICR_RDINST(x)	((x) & QSPI_RICR_RDINST_MASK)
#define QSPI_RICR_RDOPT_MASK	(0xff << 16)
#define QSPI_RICR_RDOPT(x)	(((x) << 16) & QSPI_RICR_RDOPT_MASK)

#define QSPI_SMR_SCRKL			(0x1 << 2)

#define QSPI_REFRESH_DELAY_COUNTER_MASK	0xffffffff
#define QSPI_REFRESH_DELAY_COUNTER(x)	((x) & QSPI_REFRESH_DELAY_COUNTER_MASK)

#define QSPI_WRACNT_NBWRA_MASK		0xffffffff
#define QSPI_WRACNT_NBWRA(x)		((x) & QSPI_WRACNT_NBWRA_MASK)

#define QSPI_DLLCFG_RANGE		(0x1 << 0)

#define QSPI_PCALCFG_AAON		(0x1 << 0)
#define QSPI_PCALCFG_DAPCAL		(0x1 << 1)
#define QSPI_PCALCFG_DIFFPM		(0x1 << 2)
#define QSPI_PCALCFG_CLKDIV_MASK	0x70
#define QSPI_PCALCFG_CLKDIV(x)		(((x) << 4) & QSPI_PCALCFG_CLKDIV_MASK)
#define QSPI_PCALCFG_CALCNT_MASK	0x1ff00
#define QSPI_PCALCFG_CALCNT(x)		(((x) << 8) & QSPI_PCALCFG_CALCNT_MASK)

#define QSPI_PCALCFG_CALP		(0xf << 24)
#define QSPI_PCALCFG_CALN		(0xf << 28)

#define QSPI_PCALBP_BPEN		(0x1 << 0)
#define QSPI_PCALBP_CALPBP		(0xf << 8)
#define QSPI_PCALBP_CALNBP		(0xf << 16)

#define QSPI_TOUT_TCNTM			0xffff

#define QSPI_WPMR_WPITEN		(0x1 << 1)
#define QSPI_WPMR_WPCREN		(0x1 << 2)

#endif
