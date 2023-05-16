/*
 * Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef XDMAC_H
#define XDMAC_H

#define DMA_DATA_WIDTH_BYTE			0
#define DMA_DATA_WIDTH_HALF_WORD	1
#define DMA_DATA_WIDTH_WORD			2
#define DMA_DATA_WIDTH_DWORD		3

#define DMA_CHUNK_SIZE_1	0
#define DMA_CHUNK_SIZE_2	1
#define DMA_CHUNK_SIZE_4	2
#define DMA_CHUNK_SIZE_8	3
#define DMA_CHUNK_SIZE_16	4

#define DMA_MEM_BURST_1		0
#define DMA_MEM_BURST_4		1
#define DMA_MEM_BURST_8		2
#define DMA_MEM_BURST_16	3

struct xdmac_hwcfg {
	/* Peripheral clock ID. */
	unsigned int	pid;
	/* Channel ID. */
	unsigned int	cid;
	unsigned char src_is_periph;
	unsigned char dst_is_periph;
	unsigned int txif;
	unsigned int rxif;
};

struct xdmac_cfg {
	unsigned int data_width;
	unsigned int chunk_size;
	unsigned int burst_size;
	unsigned char incr_saddr;
	unsigned char incr_daddr;
};

struct xdmac_transfer_cfg {
	void *saddr;
	void *daddr;
	unsigned int len;
};

/* functions */
extern int xdmac_configure_transfer(struct xdmac_hwcfg *hwcfg,
		struct xdmac_cfg *cfg);
extern int xdmac_transfer_start(struct xdmac_hwcfg *hwcfg,
		struct xdmac_transfer_cfg *cfg);
extern void xdmac_transfer_stop(struct xdmac_hwcfg *hwcfg);
extern int xdmac_transfer_wait_for_completion(struct xdmac_hwcfg *hwcfg);

#endif /* XDMAC_H */

