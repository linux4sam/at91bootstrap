// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "hardware.h"

#define qspi_readl_poll_timeout(addr, val, cond, timeout_us)	\
({ \
	unsigned long timeout = timeout_us; \
	do { \
		(val) = readl(addr); \
		if (cond) \
			break; \
		udelay(1); \
	} while (--timeout); \
	(cond) ? 0 : -1; \
})

extern const struct spi_ops qspi_ops;

struct qspi_priv {
	u32		reg_base;
	void		*mem;
	u32 pclk_rate;
	u32 mr;
	unsigned long mmap_size;
};

unsigned int qspi_readl(struct qspi_priv *qspi, u32 reg);
void qspi_writel(u32 value, struct qspi_priv *qspi, u32 reg);
