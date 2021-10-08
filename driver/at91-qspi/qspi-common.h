// Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

extern const struct spi_ops qspi_ops;

struct qspi_priv {
	u32		reg_base;
	void		*mem;
};

unsigned int qspi_readl(struct qspi_priv *qspi, u32 reg);
void qspi_writel(struct qspi_priv *qspi, u32 reg, u32 value);
