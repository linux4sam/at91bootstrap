// Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"
#include "board.h"
#include "arch/at91_xdmac.h"
#include "xdmac.h"
#include "pmc.h"

static inline unsigned int xdmac_readl(unsigned int reg)
{
	return readl(CONFIG_SYS_BASE_XDMAC + reg);
}

static inline void xdmac_writel(unsigned int reg, unsigned int value)
{
	writel(value, CONFIG_SYS_BASE_XDMAC + reg);
}

int xdmac_configure_transfer(struct xdmac_hwcfg *hwcfg, struct xdmac_cfg *cfg)
{
	unsigned int cc_cfg;
	unsigned int reg, mask;

	cc_cfg = 0;
	mask = (1 << hwcfg->cid);

	pmc_enable_periph_clock(CONFIG_SYS_ID_XDMAC, PMC_PERIPH_CLK_DIVIDER_NA);
	/* The DMA channel should be disabled. */
	reg = xdmac_readl(XDMAC_GS);
	if (reg & mask)
		return -1;

	if (hwcfg->src_is_periph || hwcfg->dst_is_periph) {
		cc_cfg = XDMAC_CC_TYPE_PER_TRAN;
		if (hwcfg->src_is_periph)
			cc_cfg |= XDMAC_CC_DSYNC_PER2MEM |
			          XDMAC_CC_SIF(1) |
			          XDMAC_CC_PERID(hwcfg->rxif);
		if (hwcfg->dst_is_periph)
			cc_cfg |= XDMAC_CC_DSYNC_MEM2PER |
			          XDMAC_CC_DIF(1) |
			          XDMAC_CC_PERID(hwcfg->txif);
	} else {
		cc_cfg = XDMAC_CC_TYPE_MEM_TRAN |
		         XDMAC_CC_SIF(0) |
		         XDMAC_CC_DIF(0) |
		         XDMAC_CC_SWREQ_SWR_CONNECTED;
	}

	cc_cfg |= XDMAC_CC_MBSIZE(cfg->burst_size);
	cc_cfg |= XDMAC_CC_CSIZE(cfg->chunk_size);
	cc_cfg |= XDMAC_CC_DWIDTH(cfg->data_width);
	if (cfg->incr_saddr)
		cc_cfg |= XDMAC_CC_SAM_INCREMENTED_AM;
	if (cfg->incr_daddr)
		cc_cfg |= XDMAC_CC_DAM_INCREMENTED_AM;
	xdmac_writel(XDMAC_CHAN(hwcfg->cid) + XDMAC_CC, cc_cfg);
	return 0;
}

int xdmac_transfer_wait_for_completion(struct xdmac_hwcfg *hwcfg)
{
	unsigned int cis;

	cis = xdmac_readl(XDMAC_CHAN(hwcfg->cid) + XDMAC_CIS);
	while (cis == 0)
		cis = xdmac_readl(XDMAC_CHAN(hwcfg->cid) + XDMAC_CIS);

	if (cis & (XDMAC_CI_ROE | XDMAC_CI_WBE | XDMAC_CI_RBE))
		return -1;
	else if (cis & XDMAC_CI_BI)
		xdmac_writel(XDMAC_GD, (1 << hwcfg->cid));
	return 0;
}

int xdmac_transfer_start(struct xdmac_hwcfg *hwcfg, struct xdmac_transfer_cfg *cfg)
{
	xdmac_writel(XDMAC_CHAN(hwcfg->cid) + XDMAC_CSA,
				(unsigned int)cfg->saddr);
	xdmac_writel(XDMAC_CHAN(hwcfg->cid) + XDMAC_CDA,
				(unsigned int)cfg->daddr);
	xdmac_writel(XDMAC_CHAN(hwcfg->cid) + XDMAC_CUBC,
				XDMAC_CUBC_UBLEN(cfg->len));

	/* Clear pending channel interrupts. */
	(void)xdmac_readl(XDMAC_CHAN(hwcfg->cid) + XDMAC_CIS);
	/* Set the Channel Interrupt Disable register: disable all interrupts*/
	xdmac_writel(XDMAC_CHAN(hwcfg->cid) + XDMAC_CID, 0xffffffff);
	/* Clear channel interrupt status */
	(void)xdmac_readl(XDMAC_GIS);
	/* Set the Global Channel Enable register. */
	xdmac_writel(XDMAC_GE, 1 << hwcfg->cid);
	return 0;
}

void xdmac_transfer_stop(struct xdmac_hwcfg *hwcfg)
{
	/* Disable this channel. */
	xdmac_writel(XDMAC_GD, (1 << hwcfg->cid));
	/* Disable XDMAC clock. */
	pmc_disable_periph_clock(CONFIG_SYS_ID_XDMAC);
}
