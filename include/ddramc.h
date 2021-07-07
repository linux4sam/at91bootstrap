/*
 * Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DDRAMC_H__
#define __DDRAMC_H__

struct ddramc_register {
	unsigned int mdr;
	unsigned int cr;
	unsigned int rtr;
	unsigned int t0pr;
	unsigned int t1pr;
	unsigned int t2pr;
	unsigned int lpr;
	unsigned int lpddr2_lpr;
	unsigned int tim_calr;
	unsigned int cal_mr4r;
};

struct ddram_timings {
	unsigned int tmrd;   /**< Load Mode Register Command to Activate or Refresh Command */
	unsigned int twtr;   /**< Internal Write to Read Delay */
	unsigned int trrd;   /**< Active BankA to Active BankB */
	unsigned int trp;    /**< Row Precharge Delay */
	unsigned int trc;    /**< Row Cycle Delay */
	unsigned int twr;    /**< Write Recovery Delay */
	unsigned int trcd;   /**< Row to Column Delay */
	unsigned int tras;   /**< Active to Precharge Delay */
	unsigned int txp;    /**< Exit Powerdown Delay to First Command */
	unsigned int txsrd;  /**< Exit Self-refresh Delay to Read Command */
	unsigned int txsnr;  /**< Exit Self-refresh Delay to Non-Read Command */
	unsigned int trfc;   /**< Row Cycle Delay */
	unsigned int tfaw;   /**< Four Active Windows */
	unsigned int trtp;   /**< Read to Precharge */
	unsigned int trpa;   /**< Row Precharge All Delay */
	unsigned int txards; /**< Exit Active Powerdown Delay to Read Command in Mode "Slow Exit" */
	unsigned int txard;  /**< Exit Active Powerdown Delay to Read Command in Mode "Fast Exit" */
};

extern void ddram_init(void);

extern int ddr2_sdram_initialize(unsigned int base_address,
		unsigned int ram_address,
		struct ddramc_register *ddramc_config);

extern int lpddr2_sdram_initialize(unsigned int base_address,
				unsigned int ram_address,
				struct ddramc_register *ddramc_config);

extern int ddr3_sdram_initialize(unsigned int base_address,
			unsigned int ram_address,
			struct ddramc_register *ddramc_config);

extern int lpddr3_sdram_initialize(unsigned int base_address,
				   unsigned int ram_address,
				   struct ddramc_register *ddramc_config);

extern int lpddr1_sdram_initialize(unsigned int base_address,
				   unsigned int ram_address,
				   struct ddramc_register *ddramc_config);

extern void ddramc_dump_regs(unsigned int base_address);

extern unsigned int get_ddram_size(void);

#endif /* #ifndef __DDRAMC_H__ */
