// Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
// Copyright (C) 2007 Lead Tech Design <www.leadtechdesign.com>
// Copyright (C) 2007 Stelian Pop <stelian.pop@leadtechdesign.com>
//
// SPDX-License-Identifier: MIT

#include "barriers.h"
#include "hardware.h"
#include "arch/at91_ddrsdrc.h"
#include "arch/at91_pmc/pmc.h"
#include "arch/at91_sfr.h"
#include "arch/at91_sfrbu.h"
#include "backup.h"
#include "debug.h"
#include "pmc.h"
#include "ddramc.h"
#include "timer.h"
#include "usart.h"

#if defined(CONFIG_DDR_SET_BY_JEDEC)
#include "ddr_jedec.h"
#elif defined(CONFIG_DDR_SET_BY_DEVICE)
#include "ddr_device.h"
#endif

static void ddram_reg_config(struct ddramc_register *ddramc_config)
{
	unsigned int type, dbw, col, row, cas, bank;

#if defined(CONFIG_DDR_SET_BY_JEDEC) || defined(CONFIG_DDR_SET_BY_TIMING)
	unsigned int mck;
#endif

#if defined(CONFIG_DDR_SET_BY_DEVICE)
#if defined(CONFIG_DDR_MT41K128M16_D2)
/* Two DDR3L(MT41H128M16JT-125-K = 16 Mbit x 16 x 8 banks), total 4Gbit on SAMA5D2 Xplained Ultra Evaluation Kit*/
	type = AT91C_DDRC2_MD_DDR3_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_5;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_116MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 907(0x38b) */
	ddramc_config->rtr = 0x38b;
#elif defined(CONFIG_BUS_SPEED_166MHZ)
/* Refresh Timer is (64ms / 8k) * 166MHz = 1297(0x511) */
	ddramc_config->rtr = 0x511;
#else
	#error "No CLK setting defined"
#endif
	/*
	 * According to the sama5d2 datasheet and the following values:
	 * T Sens = 0.75%/C, V Sens = 0.2%/mV, T driftrate = 1C/sec and V driftrate = 15 mV/s
	 * Warning: note that the values T driftrate and V driftrate are dependent on
	 * the application environment.
	 * ZQCS period is 1.5 / ((0.75 x 1) + (0.2 x 15)) = 0.4s
	 * If tref is 7.8us, we have: 400000 / 7.8 = 51282(0xC852)
	 * */
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xC852);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(64);

#elif defined(CONFIG_DDR_MT41K128M16)
/* DDR3L(MT41H128M16JT-125-K = 16 Mbit x 16 x 8 banks), total 2Gbit on SAM9X75-DDR3-EB */
	type = AT91C_DDRC2_MD_DDR3_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_5;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_200MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 1562(0x61a) */
	ddramc_config->rtr = 0x61a;
#elif defined(CONFIG_BUS_SPEED_266MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 2078(0x81e) */
	ddramc_config->rtr = 0x81e;
#else
	#error "No CLK setting defined"
#endif
#elif defined(CONFIG_DDR_W632GU6NB12I)
/* DDR3L(W632GU6NB12I = 16 Mbit x 16 x 8 banks), total 2Gbit on SAM9X75D2G */
	type = AT91C_DDRC2_MD_DDR3_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_5;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_200MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 1562(0x61a) */
	ddramc_config->rtr = 0x61a;
#elif defined(CONFIG_BUS_SPEED_266MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 2078(0x81e) */
	ddramc_config->rtr = 0x81e;
#else
	#error "No CLK setting defined"
#endif
	/*
	 * According to the sam9x7 datasheet and the following values:
	 * T Sens = 0.75%/C, V Sens = 0.2%/mV, T driftrate = 1C/sec and V driftrate = 15 mV/s
	 * Warning: note that the values T driftrate and V driftrate are dependent on
	 * the application environment.
	 * ZQCS period is 1.5 / ((0.75 x 1) + (0.2 x 15)) = 0.4s
	 * If tref is 7.8us, we have: 400000 / 7.8 = 51282(0xC852)
	 */
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xC852);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(64);

#elif defined(CONFIG_DDR_W631GU6NB12I)
/* DDR3L(W631GU6NG = 8 Mbit x 16 x 8 banks), total 1Gbit on SAM9X75 SIP */
	type = AT91C_DDRC2_MD_DDR3_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_13;
	cas = AT91C_DDRC2_CAS_5;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_200MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 1562(0x61a) */
	ddramc_config->rtr = 0x61a;
#elif defined(CONFIG_BUS_SPEED_266MHZ)
	/* Refresh Timer is (64ms / 8k) * 116MHz = 2078(0x81e) */
	ddramc_config->rtr = 0x81e;
#else
	#error "No CLK setting defined"
#endif
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xC852);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(64);
#elif defined(CONFIG_DDR_W9751G6NB)
/* DDR2(W9751G6NB = 8 Mbit x 16 x 4 banks), total 512M bit on SAM9X75 SIP */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_13;
	bank = AT91C_DDRC2_NB_BANKS_4;
#if defined(CONFIG_BUS_SPEED_200MHZ)
	cas = AT91C_DDRC2_CAS_3;
	/* Refresh Timer is (64ms / 8k) * 116MHz = 1562(0x61a) */
	ddramc_config->rtr = 0x61a;
#elif defined(CONFIG_BUS_SPEED_266MHZ)
	cas = AT91C_DDRC2_CAS_5;
	/* Refresh Timer is (64ms / 8k) * 116MHz = 2078(0x81e) */
	ddramc_config->rtr = 0x81e;
#else
	#error "No CLK setting defined"
#endif
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xC852);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(64);
#elif defined(CONFIG_DDR_W632GU6MB)
/* Two DDR3L(W632GU6MB-12 = 16 Mbit x 16 x 8 banks), total 4 Gbit on SAMA5D2 ICP*/
	type = AT91C_DDRC2_MD_DDR3_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_5;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_166MHZ)
	ddramc_config->rtr = 0x298;
#else
	#error "No CLK setting defined"
#endif
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0x5355);
#elif defined(CONFIG_DDR_W972GG6KB_D2)
/* Two DDR2 (W972GG6KB-25-2 Gbits = 16 Mbits x 16 x 8 banks), total 4 Gbits on the SAMA5D2-PTC-EK */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
	ddramc_config->rtr = 0x500;
#elif defined(CONFIG_DDR_W972GG6KB_9X60)
/* One DDR2 (W972GG6KB-25-2 Gbits = 16 Mbits x 16 x 8 banks), total 2 Gbits on the SAM9X60-EK */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
	ddramc_config->rtr = 0x30e;
#elif defined(CONFIG_DDR_W971GG6SB_D2)
/* DDR2 (W971GG6SB = 8 Mwords x 8 Banks x 16 bits), total 1 Gbit in SiP on the SAMA5D2-SOM-EK */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_13;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
	ddramc_config->rtr = 0x4FF;
#elif defined(CONFIG_DDR_W9712G6KB25I)
/* 2 Mwords x 4 Banks x 16 bits DDR2 SDRAM (128 Mbit) in SAMA5D2 Sip */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
	row = AT91C_DDRC2_NR_12;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_4;
	ddramc_config->rtr = 0x4FF;
#elif defined(CONFIG_DDR_W9751G6KB) || defined(CONFIG_DDR_W971GG6SB)
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_16_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_13;
	cas = AT91C_DDRC2_CAS_3;
#if defined(CONFIG_DDR_W9751G6KB)
/* DDR2 (W9751G6KB = 8 Mwords x 4 Banks x 16 bits), total 512 Mbit in SAM9X60D5M and ATSAMA5D27C-D5M SiP */
	bank = AT91C_DDRC2_NB_BANKS_4;
#else // defined(CONFIG_DDR_W971GG6SB)
/* DDR2 (W971GG6SB = 8 Mwords x 8 Banks x 16 bits), total 1 Gbit in SAM9X60D1G and ATSAMA5D27C-D1G SiP */
	bank = AT91C_DDRC2_NB_BANKS_8;
#endif
#if defined(CONFIG_DDR_EXT_TEMP_RANGE)
#if defined(CONFIG_BUS_SPEED_166MHZ)
	ddramc_config->rtr = 0x2A5;
#elif defined(CONFIG_BUS_SPEED_200MHZ)
	ddramc_config->rtr = 0x30c;
#else
	#error "No CLK setting defined"
#endif
#else
#if defined(CONFIG_BUS_SPEED_166MHZ)
	ddramc_config->rtr = 0x50E;
#elif defined(CONFIG_BUS_SPEED_200MHZ)
	ddramc_config->rtr = 0x618;
#else
	#error "No CLK setting defined"
#endif
#endif
#elif defined(CONFIG_DDR_AD220032D)
/* LPDDR2 (AD220032D = 8 Mwords x 8 Banks x 32 bits), total 2 Gbit in SiP on SAMA5D27-WLSOM1-EK */
	type = AT91C_DDRC2_MD_LPDDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
	ddramc_config->rtr = AT91C_DDRC2_ENABLE_ADJ_REF | 0x27f;
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xFFFE) |
				   AT91C_DDRC2_MR4R(0xFFFE);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(15);
	ddramc_config->lpddr2_lpr = AT91C_LPDDRC2_DS(0x03);
#elif defined(CONFIG_DDR_AS4C128M32MD2A)
/* LPDDR2 (AS4C128M32MD2A = 16 Mwords x 8 Banks x 32 bits), total 4 Gbit on the SAMA5D29-Curiosity */
	type = AT91C_DDRC2_MD_LPDDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
	ddramc_config->rtr = AT91C_DDRC2_ENABLE_ADJ_REF | 0x27f;
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xFFFE) |
				   AT91C_DDRC2_MR4R(0xFFFE);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(15);
	ddramc_config->lpddr2_lpr = AT91C_LPDDRC2_DS(0x03);
#elif defined(CONFIG_DDR_AD210032F)
/* 4 Mwords x 8 Banks x 32 bits LPDDR2-SDRAM (1 Gbit) on the SAMA5D2 SiP */
	type = AT91C_DDRC2_MD_LPDDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
	row = AT91C_DDRC2_NR_13;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
	ddramc_config->rtr = AT91C_DDRC2_ENABLE_ADJ_REF | 0x27f;
	ddramc_config->cal_mr4r = AT91C_DDRC2_COUNT_CAL(0xFFFE) |
				   AT91C_DDRC2_MR4R(0xFFFE);
	ddramc_config->tim_calr = AT91C_DDRC2_ZQCS(15);
	ddramc_config->lpddr2_lpr = AT91C_LPDDRC2_DS(0x03);
#elif defined(CONFIG_DDR_MT47H128M16)
/* DDR2 (MT47H128M16 = 8 Mwords x 8 Banks x 32 bits), total 2 Gbit on the SAMA5D3-EK */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_DDR_EXT_TEMP_RANGE)
/* The refresh period is 64ms (commercial) or 32ms (industrial and automotive). */
#if defined(CONFIG_BUS_SPEED_133MHZ)
	ddramc_config->rtr = 0x207;
#elif defined(CONFIG_BUS_SPEED_148MHZ)
	ddramc_config->rtr = 0x242;
#elif defined(CONFIG_BUS_SPEED_166MHZ)
	ddramc_config->rtr = 0x288;
#elif defined(CONFIG_BUS_SPEED_170MHZ)
	ddramc_config->rtr = 0x298;
#elif defined(CONFIG_BUS_SPEED_176MHZ)
	ddramc_config->rtr = 0x2b0;
#elif defined(CONFIG_BUS_SPEED_200MHZ)
	ddramc_config->rtr = 0x30e;
#else
	#error "No CLK setting defined"
#endif
#else
#if defined(CONFIG_BUS_SPEED_133MHZ)
	ddramc_config->rtr = 0x40e;
#elif defined(CONFIG_BUS_SPEED_148MHZ)
	ddramc_config->rtr = 0x484;
#elif defined(CONFIG_BUS_SPEED_166MHZ)
	ddramc_config->rtr = 0x510;
#elif defined(CONFIG_BUS_SPEED_170MHZ)
	ddramc_config->rtr = 0x530;
#elif defined(CONFIG_BUS_SPEED_176MHZ)
	ddramc_config->rtr = 0x55f;
#elif defined(CONFIG_BUS_SPEED_200MHZ)
	ddramc_config->rtr = 0x61a;
#else
	#error "No CLK setting defined"
#endif
#endif
#elif defined(CONFIG_DDR_MT47H64M16)
/* DDR2 (MT47H64M16 x 2 = 8 Mwords x 8 Banks x 16 bits x 2), total 2 Gbit on the SAMA5D3-Xplained */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_13;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_133MHZ)
	ddramc_config->rtr = 0x40F;
#elif defined(CONFIG_BUS_SPEED_166MHZ)
	ddramc_config->rtr = 0x510;
#else
	#error "No CLK setting defined"
#endif
#elif defined(CONFIG_DDR_MT47H128M8)
/* DDR2 (MT47H128M8 x 2 = 8 Mwords x 8 Banks x 16 bits x 2), total 2 Gbit on the SAMA5D4-EK */
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
	dbw = AT91C_DDRC2_DBW_32_BITS;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	row = AT91C_DDRC2_NR_14;
	cas = AT91C_DDRC2_CAS_3;
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined(CONFIG_BUS_SPEED_148MHZ)
	ddramc_config->rtr = 0x243;
#elif defined(CONFIG_BUS_SPEED_170MHZ)
	ddramc_config->rtr = 0x229;
#elif defined(CONFIG_BUS_SPEED_176MHZ)
	ddramc_config->rtr = 0x2b0;
#elif defined(CONFIG_BUS_SPEED_200MHZ)
	ddramc_config->rtr = 0x30e;
#else
	#error "No CLK setting defined"
#endif
#else
#error "DDR-SDRAM device is not supportted!"
#endif

#else

/* Configure the type of memory used. */
#if defined(CONFIG_LPDDR1)
	type = AT91C_DDRC2_MD_LP_DDR_SDRAM;
#elif defined(CONFIG_DDR2)
	type = AT91C_DDRC2_MD_DDR2_SDRAM;
#elif defined(CONFIG_LPDDR2)
	type = AT91C_DDRC2_MD_LPDDR2_SDRAM;
#elif defined(CONFIG_DDR3)
	type = AT91C_DDRC2_MD_DDR3_SDRAM;
#elif defined(CONFIG_LPDDR3)
	type = AT91C_DDRC2_MD_LPDDR3_SDRAM;
#endif

/* Configure the data Bus Width */
#if defined(CONFIG_DBW_32)
	dbw = AT91C_DDRC2_DBW_32_BITS;
#else
	dbw = AT91C_DDRC2_DBW_16_BITS;
#endif

/* Configure the number of column bits */
#if defined(CONFIG_LPDDR1)
	bank = AT91C_DDRC2_NB_BANKS_4;

#if defined (CONFIG_DDR_64_MBIT)
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#else
	row = AT91C_DDRC2_NR_11;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#endif
	
#elif defined (CONFIG_DDR_128_MBIT)
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
	#else
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#endif

#elif defined (CONFIG_DDR_256_MBIT)
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#else
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#endif

#elif defined (CONFIG_DDR_512_MBIT)
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR11_SDR10;
#else
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#endif

#elif defined (CONFIG_DDR_1_GBIT)
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR11_SDR10;
#else
#if defined (CONFIG_R14_C10)
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#elif defined(CONFIG_R13_C11)
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR11_SDR10;
#endif /* Endif CONFIG_R14_C10 */
#endif /* Endif CONFIG_DBW_16 */

#elif defined (CONFIG_DDR_2_GBIT)
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR12_SDR11;
#else
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR11_SDR10;
#endif /* Endif CONFIG_DBW_16 */
#endif /* Endif CONFIG_DDR_2_GBIT */
#endif /* Endif LPDDR1 */

#if defined(CONFIG_DDR2)
#if defined (CONFIG_DDR_128_MBIT)
	bank = AT91C_DDRC2_NB_BANKS_4;
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#elif defined (CONFIG_DDR_256_MBIT)
	bank = AT91C_DDRC2_NB_BANKS_4;
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#elif defined (CONFIG_DDR_512_MBIT) 
	bank = AT91C_DDRC2_NB_BANKS_4;
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#elif defined (CONFIG_DDR_1_GBIT)
	bank = AT91C_DDRC2_NB_BANKS_8;
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#elif defined (CONFIG_DDR_2_GBIT)
	bank = AT91C_DDRC2_NB_BANKS_8;
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#endif /* Endif of CONFIG_DDR_128_MBIT */
#endif /* Endif of DDR2 */

#if defined(CONFIG_LPDDR2)
#if defined (CONFIG_DDR_128_MBIT)
	bank = AT91C_DDRC2_NB_BANKS_4;
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#else
#error "128Mbit 32bit width LPDDR2 not supported"
#endif /* endif of CONFIG_DBW_16 */

#elif defined (CONFIG_DDR_256_MBIT)
	bank = AT91C_DDRC2_NB_BANKS_4;
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#else
#error "256Mbit 32bit width LPDDR2 not supported"
#endif /* endif of CONFIG_DBW_16 */
#elif defined (CONFIG_DDR_512_MBIT)
	bank = AT91C_DDRC2_NB_BANKS_4;
#if defined (CONFIG_DBW_16)
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#else
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#endif /* endif of CONFIG_DBW_16 */
#elif defined (CONFIG_DDR_1_GBIT)
#if defined (CONFIG_DBW_16)
	/* 16 bit bus width */
#if defined CONFIG_LPDDR2_S2
	bank = AT91C_DDRC2_NB_BANKS_4;
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#else
	bank = AT91C_DDRC2_NB_BANKS_8;
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#endif /* endif of LPDDR2_S2 */
#else
	/* 32bit bus width */
#if defined CONFIG_LPDDR2_S2
	bank = AT91C_DDRC2_NB_BANKS_4;
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#else
	bank = AT91C_DDRC2_NB_BANKS_8;
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#endif /* endif of CONFIG_DBW_16 */
#endif
#elif defined (CONFIG_DDR_2_GBIT)
#if defined (CONFIG_DBW_16)
	/* 16 bit bus width */
#if defined CONFIG_LPDDR2_S4
	bank = AT91C_DDRC2_NB_BANKS_8;
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#else
#error "LPDDR2 2Gb 16bit width with 4 banks is not supported!"
#endif
#else
	/* 32bit bus width */
#if defined CONFIG_LPDDR2_S4
	bank = AT91C_DDRC2_NB_BANKS_8;
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR9_SDR8;
#else
#error "LPDDR2 2Gb 32bit width with 4 banks is not supported!"
#endif /* endif of CONFIG_LPDDR2_S4 */
#endif /* endif of CONFIG_DBW_16 */
#endif /* endif of CONFIG_DDR_128_MBIT */
#endif /* endif LPDDR2 */

#if defined(CONFIG_DDR3)
	bank = AT91C_DDRC2_NB_BANKS_8;
#if defined (CONFIG_DDR_512_MBIT)
	row = AT91C_DDRC2_NR_12;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#elif defined (CONFIG_DDR_1_GBIT)
	row = AT91C_DDRC2_NR_13;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#elif defined (CONFIG_DDR_2_GBIT)
	row = AT91C_DDRC2_NR_14;
	col = AT91C_DDRC2_NC_DDR10_SDR9;
#endif /* endif of CONFIG_DDR_512_MBIT */
#endif /* Endif DDR3 */

#if defined(CONFIG_CAS_2)
	cas = AT91C_DDRC2_CAS_2;
#elif defined(CONFIG_CAS_3)
	cas = AT91C_DDRC2_CAS_3;
#elif defined(CONFIG_CAS_4)
	cas = AT91C_DDRC2_CAS_4;
#elif defined(CONFIG_CAS_5)
	cas = AT91C_DDRC2_CAS_5;
#elif defined(CONFIG_CAS_6)
	cas = AT91C_DDRC2_CAS_6;
#endif

#endif
	ddramc_config->mdr = type | dbw;
	ddramc_config->cr = (col |
						 row |
						 bank |
						 cas |
#if defined(CONFIG_NOT_DQS_DISABLED)
						 AT91C_DDRC2_NDQS_DISABLED |
#endif
#if defined(CONFIG_LPDDR2)
						AT91C_DDRC2_ZQ_SHORT |
#endif
						AT91C_DDRC2_DECOD_INTERLEAVED |
#if defined(CONFIG_DDR3)
						AT91C_DDRC2_DISABLE_DLL |
#if defined(CONFIG_BUS_SPEED_266MHZ)
						AT91C_DDRC2_CASWR_6 |
#else
						AT91C_DDRC2_CASWR_5 |
#endif
						AT91C_DDRC2_WEAK_STRENGTH_RZQ7 |
#endif
						AT91C_DDRC2_DECOD_INTERLEAVED |
						AT91C_DDRC2_UNAL_SUPPORTED
						);
#if defined(CONFIG_LPDDR1)
	ddramc_config->lpr = 0;
#endif

#if defined(CONFIG_DDR_SET_BY_JEDEC)
#ifdef CONFIG_BUS_SPEED_116MHZ
	mck = 116;
#elif CONFIG_BUS_SPEED_133MHZ
	mck = 133;
#elif CONFIG_BUS_SPEED_148MHZ
	mck = 148;
#elif CONFIG_BUS_SPEED_166MHZ
	mck = 166;
#elif CONFIG_BUS_SPEED_164MHZ
	mck = 164;
#elif CONFIG_BUS_SPEED_170MHZ
	mck = 170;
#elif CONFIG_BUS_SPEED_176MHZ
	mck = 176;
#elif CONFIG_BUS_SPEED_200MHZ
	mck = 200;
#endif
	/* Refresh Timer is (refresh_window / refresh_cycles) * master_clock */
	ddramc_config->rtr = CONFIG_REF_WIN * mck * 1000 / CONFIG_REF_CYCLE;
	ddramc_config->t0pr = ( AT91C_DDRC2_TRAS_(NS2CYCLES(ddr_ddram_timings.tras, mck)) |
							AT91C_DDRC2_TRCD_(NS2CYCLES(ddr_ddram_timings.trcd, mck)) |
							AT91C_DDRC2_TWR_(NS2CYCLES(ddr_ddram_timings.twr, mck)) |
							AT91C_DDRC2_TRC_(NS2CYCLES(ddr_ddram_timings.trc, mck)) |
							AT91C_DDRC2_TRP_(NS2CYCLES(ddr_ddram_timings.trp, mck)) |
							AT91C_DDRC2_TRRD_(NS2CYCLES(ddr_ddram_timings.trrd, mck))|
							AT91C_DDRC2_TWTR_(ddr_ddram_timings.twtr) |
							AT91C_DDRC2_TMRD_(ddr_ddram_timings.tmrd)
						  );
	ddramc_config->t1pr = ( AT91C_DDRC2_TRFC_(NS2CYCLES(ddr_ddram_timings.trfc, mck)) |
							AT91C_DDRC2_TXSNR_(NS2CYCLES(ddr_ddram_timings.txsnr, mck)) |
							AT91C_DDRC2_TXSRD_(NS2CYCLES(ddr_ddram_timings.txsrd, mck)) |
#if defined(CONFIG_LPDDR1)
							AT91C_DDRC2_TXP_(NS2CYCLES(ddr_ddram_timings.txp, mck))
#else
							AT91C_DDRC2_TXP_(ddr_ddram_timings.txp)
#endif
						  );
#if !defined(CONFIG_DDR2)
	ddramc_config->t2pr = ( AT91C_DDRC2_TXARD_(0) |
							AT91C_DDRC2_TXARDS_(0) |
#else
/* This field is found only in the DDR2-SDRAM devices */
	ddramc_config->t2pr = ( AT91C_DDRC2_TXARD_(ddr_ddram_timings.txard) |
							AT91C_DDRC2_TXARDS_(ddr_ddram_timings.txards) |
#endif
							AT91C_DDRC2_TRPA_(NS2CYCLES(ddr_ddram_timings.trpa, mck)) |
							AT91C_DDRC2_TRTP_(NS2CYCLES(ddr_ddram_timings.trtp, mck)) |
							AT91C_DDRC2_TFAW_(NS2CYCLES(ddr_ddram_timings.tfaw,mck))
						  );

#elif defined(CONFIG_DDR_SET_BY_DEVICE)
	ddramc_config->t0pr = ( AT91C_DDRC2_TRAS_(ddr_ddram_timings.tras) |
							AT91C_DDRC2_TRCD_(ddr_ddram_timings.trcd) |
							AT91C_DDRC2_TWR_(ddr_ddram_timings.twr) |
							AT91C_DDRC2_TRC_(ddr_ddram_timings.trc) |
							AT91C_DDRC2_TRP_(ddr_ddram_timings.trp) |
							AT91C_DDRC2_TRRD_(ddr_ddram_timings.trrd)|
							AT91C_DDRC2_TWTR_(ddr_ddram_timings.twtr) |
							AT91C_DDRC2_TMRD_(ddr_ddram_timings.tmrd)
						  );
	ddramc_config->t1pr = ( AT91C_DDRC2_TRFC_(ddr_ddram_timings.trfc) |
							AT91C_DDRC2_TXSNR_(ddr_ddram_timings.txsnr) |
							AT91C_DDRC2_TXSRD_(ddr_ddram_timings.txsrd) |
							AT91C_DDRC2_TXP_(ddr_ddram_timings.txp)
						  );
/* This field is found only in the DDR2-SDRAM devices */
	ddramc_config->t2pr = ( AT91C_DDRC2_TXARD_(ddr_ddram_timings.txard) |
							AT91C_DDRC2_TXARDS_(ddr_ddram_timings.txards) |
							AT91C_DDRC2_TRPA_(ddr_ddram_timings.trpa) |
							AT91C_DDRC2_TRTP_(ddr_ddram_timings.trtp) |
							AT91C_DDRC2_TFAW_(ddr_ddram_timings.tfaw)
						  );

#elif defined(CONFIG_DDR_SET_BY_TIMING)
	/* Refresh Timer is (refresh_window / refresh_cycles) * master_clock */
	ddramc_config->rtr = CONFIG_DDR_RTC;
/* Assume the ddram_timings for 6ns min clock period */
	ddramc_config->t0pr = ( AT91C_DDRC2_TRAS_(CONFIG_DDR_TRSA) |
							AT91C_DDRC2_TRCD_(CONFIG_DDR_TRCD) |
							AT91C_DDRC2_TWR_(CONFIG_DDR_TWR) |
							AT91C_DDRC2_TRC_(CONFIG_DDR_TRC) |
							AT91C_DDRC2_TRP_(CONFIG_DDR_TRP) |
							AT91C_DDRC2_TRRD_(CONFIG_DDR_TRRD)|
							AT91C_DDRC2_TWTR_(CONFIG_DDR_TWTR) |
							AT91C_DDRC2_TMRD_(CONFIG_DDR_TMRD)
						  );
	ddramc_config->t1pr = ( AT91C_DDRC2_TRFC_(CONFIG_DDR_TRFC) |
							AT91C_DDRC2_TXSNR_(CONFIG_DDR_TXSNR) |
							AT91C_DDRC2_TXSRD_(CONFIG_DDR_TXSRD) |
							AT91C_DDRC2_TXP_(CONFIG_DDR_TXP)
						  );
#if !defined(CONFIG_DDR2)
	ddramc_config->t2pr = ( AT91C_DDRC2_TXARD_(0) |
							AT91C_DDRC2_TXARDS_(0) |
#else
/* This field is found only in the DDR2-SDRAM devices */
	ddramc_config->t2pr = ( AT91C_DDRC2_TXARD_(CONFIG_DDR_TXARD) |
							AT91C_DDRC2_TXARDS_(CONFIG_DDR_TXARDS) |
#endif
							AT91C_DDRC2_TRPA_(CONFIG_DDR_TRPA) |
							AT91C_DDRC2_TRTP_(CONFIG_DDR_TRTP) |
							AT91C_DDRC2_TFAW_(CONFIG_DDR_TFAW)
						  );
#endif
}

unsigned int get_ddram_size(void)
{
#if defined(CONFIG_DDR_8_GBIT)
	return 0x40000000;
#elif defined(CONFIG_DDR_4_GBIT)
	return 0x20000000;
#elif defined(CONFIG_DDR_2_GBIT)
	return 0x10000000;
#elif defined(CONFIG_DDR_1_GBIT)
	return 0x8000000;
#elif defined(CONFIG_DDR_512_MBIT)
	return 0x4000000;
#elif defined(CONFIG_DDR_256_MBIT)
	return 0x2000000;
#elif defined(CONFIG_DDR_128_MBIT)
	return 0x1000000;
#elif defined(CONFIG_DDR_64_MBIT)
	return 0x800000;
#endif
}

void ddram_init(void)
{
	struct ddramc_register ddramc_reg;
	unsigned int reg;

	ddram_reg_config(&ddramc_reg);

	pmc_enable_periph_clock(AT91C_ID_MPDDRC, PMC_PERIPH_CLK_DIVIDER_NA);
	pmc_enable_system_clock(AT91C_PMC_DDR);

#if defined(CONFIG_LPDDR1)
	/*
	 * Before starting the initialization sequence, the user must force
	 * the DDR_DQ and DDR_DQS input buffers to always on by setting
	 * the FDQIEN and FDQSIEN bits in the SFR_DDRCFG register.
	 */
#if defined(CONFIG_SAMA5D2) || defined(CONFIG_SAMA5D4)
	pmc_enable_periph_clock(AT91C_ID_SFR, PMC_PERIPH_CLK_DIVIDER_NA);
#endif
	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	reg |= AT91C_DDRCFG_FDQIEN;
	reg |= AT91C_DDRCFG_FDQSIEN;
	writel(reg, AT91C_BASE_SFR + SFR_DDRCFG);
#endif

	/* MPDDRC I/O Calibration Register */
	reg = readl(AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR);

#ifdef CONFIG_SAM9X60
	reg &= ~AT91C_MPDDRC_CK_F_RANGE;
	 /* sam9x60 has the CK_F_RANGE written always with 7 (bits 2:0) */
	reg |= 0x7;
#else
	reg &= ~AT91C_MPDDRC_RDIV;
	reg |= AT91C_MPDDRC_RDIV_DDR2_RZQ_50;
#endif

	reg &= ~AT91C_MPDDRC_TZQIO;
	/* TZQIO field must be set to 600ns */
#ifdef CONFIG_BUS_SPEED_116MHZ
	reg |= AT91C_MPDDRC_TZQIO_(70);
#elif CONFIG_BUS_SPEED_166MHZ
	reg |= AT91C_MPDDRC_TZQIO_(100);
#elif CONFIG_BUS_SPEED_164MHZ
	reg |= AT91C_MPDDRC_TZQIO_(101);
#elif CONFIG_BUS_SPEED_200MHZ
	reg |= AT91C_MPDDRC_TZQIO_(121);
#else
	reg |= AT91C_MPDDRC_TZQIO_(100);
#endif
	writel(reg, AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR);

#ifdef CONFIG_SAM9X60
	writel(AT91C_MPDDRC_RD_DATA_PATH_TWO_CYCLES,
			(AT91C_BASE_MPDDRC + MPDDRC_RD_DATA_PATH));
#else
#if defined(CONFIG_DDR3)
	writel(AT91C_MPDDRC_RD_DATA_PATH_TWO_CYCLES,
			(AT91C_BASE_MPDDRC + MPDDRC_RD_DATA_PATH));
#else
	writel(AT91C_MPDDRC_RD_DATA_PATH_ONE_CYCLES,
			AT91C_BASE_MPDDRC + MPDDRC_RD_DATA_PATH);
#endif
#endif /* defined(CONFIG_SAM9X60) */

#if defined(CONFIG_LPDDR1)
	lpddr1_sdram_initialize(AT91C_BASE_MPDDRC,
							AT91C_BASE_DDRCS, &ddramc_reg);
#elif defined(CONFIG_DDR2)
	
	writel(reg, (AT91C_BASE_MPDDRC + MPDDRC_IO_CALIBR));


	ddr2_sdram_initialize(AT91C_BASE_MPDDRC,
							AT91C_BASE_DDRCS, &ddramc_reg);
#elif defined(CONFIG_LPDDR2)
	lpddr2_sdram_initialize(AT91C_BASE_MPDDRC,
							AT91C_BASE_DDRCS, &ddramc_reg);
#elif defined(CONFIG_DDR3)
	ddr3_sdram_initialize(AT91C_BASE_MPDDRC,
							AT91C_BASE_DDRCS, &ddramc_reg);
#else
#error "No DDRAM setting defined"
#endif
	ddramc_dump_regs(AT91C_BASE_MPDDRC);
}


/* write DDRC register */
static void write_ddramc(unsigned int address,
			unsigned int offset,
			const unsigned int value)
{
	writel(value, (address + offset));
}

/* read DDRC registers */
static unsigned int read_ddramc(unsigned int address, unsigned int offset)
{
	return readl(address + offset);
}

#if defined(CONFIG_DDR2) || defined(CONFIG_DDR3) ||\
    (defined(CONFIG_SAMA5D2) && defined(CONFIG_LPDDR2))
#undef DEBUG_BKP_SR_INIT

void ddr3_lpddr2_sdram_bkp_init(unsigned int base_address,
				unsigned int ram_address,
				struct ddramc_register *ddramc_config)
{
	/*
	 * Program the memory device type in the MPDDRC Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);
	dmb();

	/*
	 * Program features of the DDR3-SDRAM/LPDDR2-SDRAM device in the MPDDRC
	 * Configuration Register and in the MPDDRC Timing Parameter 0 Register
	 * /MPDDRC Timing Parameter 1 Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register (MPDDRC_RTR):
	 * refresh rate = delay between refresh cycles.
	 * Please check the datasheet for refresh periods of
	 * DDR3-SDRAM/LPDDR2-SDRAM device.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/*
	 * Configure the CAL MR4 & TIM CAL registers
	 */
	write_ddramc(base_address,
		     MPDDRC_LPDDR2_CAL_MR4, ddramc_config->cal_mr4r);

	write_ddramc(base_address,
		     MPDDRC_LPDDR2_TIM_CAL, ddramc_config->tim_calr);

#if defined(DEBUG_BKP_SR_INIT)
	/* wait for the SELF_DONE bit to raise */
	usart_puts("BKP: about to check SELF_DONE\n");
#endif

	/*
	 * make sure to configure the DDR controller's interface like
	 * it was when it entered the Backup+Self-Refresh mode:
	 * - Normal CMD mode
	 * - Low-power Command Bit positioned
	 **/
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	write_ddramc(base_address,
		     HDDRSDRC2_LPR, AT91C_DDRC2_LPCB_SELFREFRESH);
	dmb();

	while (!(read_ddramc(base_address, HDDRSDRC2_LPR) & AT91C_DDRC2_SELF_DONE));
#if defined(DEBUG_BKP_SR_INIT)
	usart_puts("BKP: SELF_DONE ok\n");
#endif

	/* re-connect DDR Pads to the CPU domain (VCCCORE) */
	sfrbu_set_ddr_power_mode(1);
	dmb();

#if defined(DEBUG_BKP_SR_INIT)
	usart_puts("BKP: pads CX\n");

	/* take some time to re-synchronize pads with DDR controller */
	mdelay(1000);
#endif

	/* make sure to actually perform an access to the DDR chip */
	*((unsigned volatile int *)ram_address) = 0;

	/* switch back to NOLOWPOWER by clearing the Low-power Command Bit */
	write_ddramc(base_address,
		     HDDRSDRC2_LPR, AT91C_DDRC2_LPCB_DISABLED);
	dmb();
	/* make sure to actually perform an access to the DDR chip */
	*((unsigned volatile int *)ram_address) = 0;
}
#endif /* CONFIG_DDR3 || (CONFIG_LPDDR2 && CONFIG_SAMA5D2) */

#ifdef CONFIG_DDR2
static int ddramc_decodtype_is_seq(unsigned int ddramc_cr)
{
#if defined(CONFIG_SAMA5D3X) || defined(CONFIG_SAMA5D4) \
	|| defined(CONFIG_SAMA5D2) || defined(CONFIG_SAM9X60) || defined(CONFIG_SAM9X7)
	if (ddramc_cr & AT91C_DDRC2_DECOD_INTERLEAVED)
		return 0;
#endif
	return 1;
}

int ddr2_sdram_initialize(unsigned int base_address,
			unsigned int ram_address,
			struct ddramc_register *ddramc_config)
{
	unsigned int ba_offset;
	unsigned int cr = 0;

	if (backup_resume()) {
		ddr3_lpddr2_sdram_bkp_init(base_address, ram_address,
					   ddramc_config);
		return 0;
	}

	/* compute BA[] offset according to CR configuration */
	ba_offset = (ddramc_config->cr & AT91C_DDRC2_NC) + 9;
	if (ddramc_decodtype_is_seq(ddramc_config->cr))
		ba_offset += ((ddramc_config->cr & AT91C_DDRC2_NR) >> 2) + 11;

	ba_offset += (ddramc_config->mdr & AT91C_DDRC2_DBW) ? 1 : 2;

	dbg_very_loud(" ba_offset = %x ...\n", ba_offset);

	/*
	 * Step 1: Program the memory device type into the Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program the feature of DDR2-SDRAM device into
	 * the Timing Register, and into the Configuration Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: An NOP command is issued to the DDR2-SDRAM
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	/* Now, clocks which drive the DDR2-SDRAM device are enabled */

	/* A minimum pause wait 200 us is provided to precede any signal toggle.
	(6 core cycles per iteration, core is at 396MHz: min 13340 loops) */
	udelay(200);

	/*
	 * Step 4:  An NOP command is issued to the DDR2-SDRAM
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;
	/* Now, CKE is driven high */
	/* wait 400 ns min */
	udelay(1);

	/*
	 * Step 5: An all banks precharge command is issued to the DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 6: An Extended Mode Register set(EMRS2) cycle is issued to chose between commercial or high
	 * temperature operations.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x2 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 7: An Extended Mode Register set(EMRS3) cycle is issued
	 * to set the Extended Mode Register to "0".
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x3 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 8: An Extened Mode Register set(EMRS1) cycle is issued to enable DLL,
	 * and to program D.I.C(Output Driver Impedance Control)
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x1 << ba_offset))) = 0;

	/* An additional 200 cycles of clock are required for locking DLL */
	udelay(1);

	/*
	 * Step 9: Program DLL field into the Configuration Register to high(Enable DLL reset)
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_ENABLE_RESET_DLL);

	/*
	 * Step 10: A Mode Register set(MRS) cycle is issied to reset DLL.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1:0] bits are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x0 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 11: An all banks precharge command is issued to the DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/* wait 400 ns min (not needed on certain DDR2 devices) */
	udelay(1);

	/*
	 * Step 12: Two auto-refresh (CBR) cycles are provided.
	 * Program the auto refresh command (CBR) into the Mode Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/* wait TRFC cycles min (135 ns min) extended to 400 ns */
	udelay(1);

	/* Set 2nd CBR */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/* wait TRFC cycles min (135 ns min) extended to 400 ns */
	udelay(1);

	/*
	 * Step 13: Program DLL field into the Configuration Register to low(Disable DLL reset).
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr & (~AT91C_DDRC2_ENABLE_RESET_DLL));

	/*
	 * Step 14: A Mode Register set (MRS) cycle is issued to program
	 * the parameters of the DDR2-SDRAM devices, in particular CAS latency,
	 * burst length and to disable DDL reset.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1:0] bits are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x0 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 15: Program OCD field into the Configuration Register
	 * to high (OCD calibration default).
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_OCD_DEFAULT);

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 16: An Extended Mode Register set (EMRS1) cycle is issued to OCD default value.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x1 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 17: Program OCD field into the Configuration Register
	 * to low (OCD calibration mode exit).
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr & (~AT91C_DDRC2_OCD_DEFAULT));

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 18: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit.
	 * Perform a write access to DDR2-SDRAM to acknowledge this command.
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x1 << ba_offset))) = 0;

	/* wait 2 cycles min (of tCK) = 15 ns min */
	udelay(1);

	/*
	 * Step 19: A Nornal mode command is provided.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*(((unsigned volatile int *)ram_address)) = 0;

	/*
	 * Step 20: Perform a write access to any DDR2-SDRAM address
	 */
	*(((unsigned volatile int *)ram_address)) = 0;

	/*
	 * Step 21: Write the refresh rate into the count field in the Refresh Timer register.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/*
	 * Now we are ready to work on the DDRSDR
	 *  wait for end of calibration
	 */
	udelay(10);

	return 0;
}

#elif defined(CONFIG_LPDDR2)

/*
 * This is the sama5d2-compatible initialization sequence for LP-DDR2
 * Check after the #else for sama5d3 and sama5d4 LP-DDR2 initialization sequence
 */
#if defined(CONFIG_SAMA5D2)

int lpddr2_sdram_initialize(unsigned int base_address,
			    unsigned int ram_address,
			    struct ddramc_register *ddramc_config)
{
	unsigned int reg;

	if (backup_resume()) {
		ddr3_lpddr2_sdram_bkp_init(base_address, ram_address,
					   ddramc_config);
		return 0;
	}

	write_ddramc(base_address,
		     MPDDRC_LPDDR2_LPR, ddramc_config->lpddr2_lpr);

	write_ddramc(base_address,
		     MPDDRC_LPDDR2_TIM_CAL, ddramc_config->tim_calr);

	/*
	 * Step 1: Program the memory device type.
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program the feature of the low-power DDR2-SDRAM device.
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: A NOP command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);

	/*
	 * Step 3bis: Add memory barrier then Perform a write access to
	 * any low-power DDR2-SDRAM address to acknowledge the command.
	 */
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 4: A pause of at least 100 ns must be observed before
	 * a single toggle.
	 */
	udelay(1);

	/*
	 * Step 5: A NOP command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 6: A pause of at least 200 us must be observed before a Reset
	 * Command.
	 */
	udelay(200);

	/*
	 * Step 7: A Reset command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(63) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 8: A pause of at least tINIT5 must be observed before issuing
	 * any commands.
	 */
	udelay(1);

	/*
	 * Step 9: A Calibration command is issued to the low-power DDR2-SDRAM.
	 */
	reg = read_ddramc(base_address, HDDRSDRC2_CR);
	reg &= ~AT91C_DDRC2_ZQ;
	reg |= AT91C_DDRC2_ZQ_RESET;
	write_ddramc(base_address, HDDRSDRC2_CR, reg);

	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(10) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 9bis: The ZQ Calibration command is now issued.
	 * Program the type of calibration in the MPDDRC_CR: set the
	 * ZQ field to the SHORT value.
	 */
	reg = read_ddramc(base_address, HDDRSDRC2_CR);
	reg &= ~AT91C_DDRC2_ZQ;
	reg |= AT91C_DDRC2_ZQ_SHORT;
	write_ddramc(base_address, HDDRSDRC2_CR, reg);

	/*
	 * Step 10: A Mode Register Write command with 1 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(1) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 11: A Mode Register Write command with 2 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(2) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 12: A Mode Register Write command with 3 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(3) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 13: A Mode Register Write command with 16 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(16) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 14: In the DDR Configuration Register, open the input buffers.
	 */
	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	reg |= AT91C_DDRCFG_FDQIEN;
	reg |= AT91C_DDRCFG_FDQSIEN;
	writel(reg, AT91C_BASE_SFR + SFR_DDRCFG);

	/*
	 * Step 15: A NOP command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 16: A Mode Register Read command with 5 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(5) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 17: A Mode Register Read command with 6 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(6) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 18: A Mode Register Read command with 8 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(8) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 19: A Mode Register Read command with 0 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(0) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 20: A Normal Mode command is provided.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 21: In the DDR Configuration Register, close the input buffers.
	 */
	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	reg &= ~AT91C_DDRCFG_FDQIEN;
	reg &= ~AT91C_DDRCFG_FDQSIEN;
	writel(reg, AT91C_BASE_SFR + SFR_DDRCFG);

	/*
	 * Step 22: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/*
	 * Now configure the CAL MR4 register.
	 */
	write_ddramc(base_address,
		     MPDDRC_LPDDR2_CAL_MR4, ddramc_config->cal_mr4r);

	return 0;
}

#else

int lpddr2_sdram_initialize(unsigned int base_address,
			    unsigned int ram_address,
			    struct ddramc_register *ddramc_config)
{
	unsigned int reg;

	write_ddramc(base_address,
		     MPDDRC_LPDDR2_LPR, ddramc_config->lpddr2_lpr);

	write_ddramc(base_address,
		     MPDDRC_LPDDR2_TIM_CAL, ddramc_config->tim_calr);

	/*
	 * Step 1: Program the memory device type.
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program the feature of the low-power DDR2-SDRAM device.
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

#if 0 /* Adjust Refresh function: we don't use the feature */
	/*
	 * Step 2bis: As we don't use the Adjust Refresh function, no need
	 * to open the input buffers.
	 */
	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	reg |= AT91C_DDRCFG_FDQIEN;
	reg |= AT91C_DDRCFG_FDQSIEN;
	writel(reg, AT91C_BASE_SFR + SFR_DDRCFG);
#endif

	/*
	 * Step 3: A NOP command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);

	/*
	 * Step 3bis: Add memory barrier then Perform a write access to
	 * any low-power DDR2-SDRAM address to acknowledge the command.
	 */
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 4: A pause of at least 100 ns must be observed before
	 * a single toggle.
	 */
	udelay(1);

	/*
	 * Step 5: A NOP command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 6: A pause of at least 200 us must be observed before a Reset
	 * Command.
	 */
	udelay(200);

	/*
	 * Step 7: A Reset command is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(63) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 8: A pause of at least tINIT5 must be observed before issuing
	 * any commands.
	 */
	udelay(1);

	/*
	 * Step 9: A Calibration command is issued to the low-power DDR2-SDRAM.
	 */
	reg = read_ddramc(base_address, HDDRSDRC2_CR);
	reg &= ~AT91C_DDRC2_ZQ;
	reg |= AT91C_DDRC2_ZQ_RESET;
	write_ddramc(base_address, HDDRSDRC2_CR, reg);

	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(10) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 9bis: The ZQ Calibration command is now issued.
	 * Program the type of calibration in the MPDDRC_CR: set the
	 * ZQ field to the SHORT value.
	 */
	reg = read_ddramc(base_address, HDDRSDRC2_CR);
	reg &= ~AT91C_DDRC2_ZQ;
	reg |= AT91C_DDRC2_ZQ_SHORT;
	write_ddramc(base_address, HDDRSDRC2_CR, reg);

	/*
	 * Step 10: A Mode Register Write command with 1 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(1) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 11: A Mode Register Write command with 2 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(2) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 12: A Mode Register Write command with 3 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(3) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 13: A Mode Register Write command with 16 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(16) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 14: A Normal Mode command is provided.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	dmb();
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 15: close the input buffers: error in documentation: no need.
	 */

	/*
	 * Step 16: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/*
	 * Now configure the CAL MR4 register.
	 */
	write_ddramc(base_address,
		     MPDDRC_LPDDR2_CAL_MR4, ddramc_config->cal_mr4r);

	return 0;
}

#endif

#elif defined(CONFIG_DDR3)

int ddr3_sdram_initialize(unsigned int base_address,
			unsigned int ram_address,
			struct ddramc_register *ddramc_config)
{
	unsigned int ba_offset;
#if defined(CONFIG_BUS_SPEED_266MHZ)
	unsigned int cr;
#endif

	if (backup_resume()) {
		ddr3_lpddr2_sdram_bkp_init(base_address, ram_address,
					   ddramc_config);
		return 0;
	}

	/* Compute BA[] offset according to CR configuration */
	ba_offset = (ddramc_config->cr & AT91C_DDRC2_NC) + 9;
	if (!(ddramc_config->cr & AT91C_DDRC2_DECOD_INTERLEAVED))
		ba_offset += ((ddramc_config->cr & AT91C_DDRC2_NR) >> 2) + 11;

	ba_offset += (ddramc_config->mdr & AT91C_DDRC2_DBW) ? 1 : 2;

	dbg_very_loud(" ba_offset = %x ...\n", ba_offset);

	write_ddramc(base_address,
		     MPDDRC_LPDDR2_TIM_CAL, ddramc_config->tim_calr);

	/*
	 * Step 1: Program the memory device type in the MPDDRC Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program features of the DDR3-SDRAM device in the MPDDRC
	 * Configuration Register and in the MPDDRC Timing Parameter 0 Register
	 * /MPDDRC Timing Parameter 1 Register
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: A NOP command is issued to the DDR3-SRAM.
	 * Program the NOP command in the MPDDRC Mode Register (MPDDRC_MR).
	 * The application must write a one to the MODE field in the MPDDRC_MR
	 * Perform a write access to any DDR3-SDRAM address to acknowledge this command.
	 * The clock which drive the DDR3-SDRAM device are now enabled.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 4: A pause of at least 500us must be observed before a single toggle.
	 */
	udelay(500);

	/*
	 * Step 5: A NOP command is issued to the DDR3-SDRAM
	 * Program the NOP command in the MPDDRC_MR.
	 * The application must write a one to the MODE field in the MPDDRC_MR.
	 * Perform a write access to any DDR3-SDRAM address to acknowledge this command.
	 * CKE is now driven high.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 6: An Extended Mode Register Set (EMRS2) cycle is issued to choose
	 * between commercial or high temperature operations. The application must
	 * write a five to the MODE field in the MPDDRC_MR and perform a write
	 * access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[2] is set to 0,
	 * BA[1] is set to 1 and signal BA[0] is set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x2 << ba_offset))) = 0;

	/*
	 * Step 7: An Extended Mode Register Set (EMRS3) cycle is issued to set
	 * the Extended Mode Register to 0. The application must write a five
	 * to the MODE field in the MPDDRC_MR and perform a write access to the
	 * DDR3-SDRAM to acknowledge this command. The write address must be
	 * chosen so that signal BA[2] is set to 0, BA[1] is set to 1 and signal
	 * BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x3 << ba_offset))) = 0;

#if defined(CONFIG_BUS_SPEED_266MHZ)
	/*
	 * Set MPDDRC_CR.DIS_DLL (Disable DLL) to 1 in DLL Off mode, or to 0 in DLL On
	 * mode.
	 */
	cr = read_ddramc(base_address, HDDRSDRC2_CR);
	write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_ENABLE_DLL);
#endif
	/*
	 * Step 8: An Extended Mode Register Set (EMRS1) cycle is issued to
	 * disable and to program O.D.S. (Output Driver Strength).
	 * The application must write a five to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[2:1] is set to 0
	 * and signal BA[0] is set to 1.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x1 << ba_offset))) = 0;

	/*
	 * Step 9: Write a one to the DLL bit (enable DLL reset) in the MPDDRC
	 * Configuration Register (MPDDRC_CR)
	 */
#if defined(CONFIG_BUS_SPEED_266MHZ)
		cr = read_ddramc(base_address, HDDRSDRC2_CR);
		write_ddramc(base_address, HDDRSDRC2_CR, cr | AT91C_DDRC2_ENABLE_RESET_DLL);
#endif

	/*
	 * Step 10: A Mode Register Set (MRS) cycle is issued to reset DLL.
	 * The application must write a three to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	udelay(50);

	/*
	 * Step 11: A Calibration command (MRS) is issued to calibrate RTT and
	 * RON values for the Process Voltage Temperature (PVT).
	 * The application must write a six to the MODE field in the MPDDRC_MR
	 * and perform a write access to the DDR3-SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[2:0] are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_DEEP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 12: A Normal Mode command is provided.
	 * Program the Normal mode in the MPDDRC_MR and perform a write access
	 * to any DDR3-SDRAM address to acknowledge this command.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 13: Perform a write access to any DDR3-SDRAM address.
	 */
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 14: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register (MPDDRC_RTR):
	 * refresh rate = delay between refresh cycles.
	 * The DDR3-SDRAM device requires a refresh every 7.81 us.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	/*
	 * Now configure the CAL MR4 register.
	 */
	write_ddramc(base_address,
		     MPDDRC_LPDDR2_CAL_MR4, ddramc_config->cal_mr4r);

	return 0;
}

#elif defined(CONFIG_LPDDR3)
int lpddr3_sdram_initialize(unsigned int base_address,
			    unsigned int ram_address,
			    struct ddramc_register *ddramc_config)
{
	unsigned int reg;

	write_ddramc(base_address, MPDDRC_LPDDR2_LPR,
		     ddramc_config->lpddr2_lpr);

	/*
	 * Step 1: Program the memory device type in the MPDDRC Memory
	 * Device Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program features of the low-power DDR3-SDRAM device
	 * in the MPDDRC Configuration Register and in the MPDDRC Timing
	 * Parameter 0 Register/MPDDRC Timing Parameter 1 Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: A NOP command is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 4: A pause of at least 100ns must be observed before
	 * a single toggle.
	 */
	 udelay(1);

	/*
	 * Step 5: A NOP command is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 6: A pause of at least 200us must be observed before issuing
	 * a Reset Command
	 */
	udelay(200);

	/*
	 * Step 7: A Reset command is issued to the Low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(63) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 8: A pause of at least tINIT5 must be observed before issuing
	 * any commands.
	 */
	udelay(1);

	/*
	 * Step 9: A Calibration command is issued to the low-power DDR3-SDRAM.
	 */
	reg = read_ddramc(base_address, HDDRSDRC2_CR);
	reg &= ~AT91C_DDRC2_ZQ;
	reg |= AT91C_DDRC2_ZQ_RESET;
	write_ddramc(base_address, HDDRSDRC2_CR, reg);

	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(10) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	reg = read_ddramc(base_address, HDDRSDRC2_CR);
	reg &= ~AT91C_DDRC2_ZQ;
	reg |= AT91C_DDRC2_ZQ_SHORT;
	write_ddramc(base_address, HDDRSDRC2_CR, reg);

	/*
	 * Step 10: A Mode Register Write command with 1 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(1) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 11: A Mode Register Write command with 2 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(2) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 12: A Mode Register Write command with 3 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(3) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 13: A Mode Register Write command with 16 to the MRS field
	 * is issued to the low-power DDR2-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(16) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 14: In the DDR Configuration Register, open the input buffers.
	 */
	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	reg |= AT91C_DDRCFG_FDQIEN;
	reg |= AT91C_DDRCFG_FDQSIEN;
	writel(reg, AT91C_BASE_SFR + SFR_DDRCFG);

	/*
	 * Step 15: A NOP command is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 16: A Mode Register Read command with 5 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(5) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 17: A Mode Register Read command with 6 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(6) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 18: A Mode Register Read command with 8 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(8) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 19: A Mode Register Read command with 0 to the MRS field
	 * is issued to the low-power DDR3-SDRAM.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR,
		     AT91C_DDRC2_MRS(0) | AT91C_DDRC2_MODE_LPDDR2_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 20: A Normal Mode command is provided.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 21: In the DDR Configuration Register, close the input buffers.
	 */
	reg = readl(AT91C_BASE_SFR + SFR_DDRCFG);
	reg &= ~AT91C_DDRCFG_FDQIEN;
	reg &= ~AT91C_DDRCFG_FDQSIEN;
	writel(reg, AT91C_BASE_SFR + SFR_DDRCFG);

	/*
	 * Step 22: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register. The low-power DDR3-SDRAM device requires
	 * a refresh every 3.9 us.
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	return 0;
}

#elif defined(CONFIG_LPDDR1)

int lpddr1_sdram_initialize(unsigned int base_address,
			    unsigned int ram_address,
			    struct ddramc_register *ddramc_config)
{
	unsigned int ba_offset;

	/* Compute BA[] offset according to CR configuration */
	ba_offset = (ddramc_config->cr & AT91C_DDRC2_NC) + 8;
	if (!(ddramc_config->cr & AT91C_DDRC2_DECOD_INTERLEAVED))
		ba_offset += ((ddramc_config->cr & AT91C_DDRC2_NR) >> 2) + 11;

	ba_offset += (ddramc_config->mdr & AT91C_DDRC2_DBW) ? 1 : 2;

	dbg_very_loud(" ba_offset = %x ...\n", ba_offset);

	/*
	 * Step 1: Program the memory device type in the MPDDRC Memory Device Register
	 */
	write_ddramc(base_address, HDDRSDRC2_MDR, ddramc_config->mdr);

	/*
	 * Step 2: Program the features of the low-power DDR1-SDRAM device
	 * in the MPDDRC Configuration Register and in the MPDDRC Timing
	 * Parameter 0 Register/MPDDRC Timing Parameter 1 Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_CR, ddramc_config->cr);

	write_ddramc(base_address, HDDRSDRC2_T0PR, ddramc_config->t0pr);
	write_ddramc(base_address, HDDRSDRC2_T1PR, ddramc_config->t1pr);
	write_ddramc(base_address, HDDRSDRC2_T2PR, ddramc_config->t2pr);

	/*
	 * Step 3: Program Temperature Compensated Self-refresh (TCR),
	 * Partial Array Self-refresh (PASR) and Drive Strength (DS) parameters
	 * in the MPDDRC Low-power Register.
	 */
	write_ddramc(base_address, HDDRSDRC2_LPR, ddramc_config->lpr);

	/*
	 * Step 4: A NOP command is issued to the low-power DDR1-SDRAM.
	 * Program the NOP command in the MPDDRC Mode Register (MPDDRC_MR).
	 * The clocks which drive the low-power DDR1-SDRAM device
	 * are now enabled.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 5: A pause of at least 200 us must be observed before
	 * a signal toggle.
	 */
	 udelay(200);

	/*
	 * Step 6: A NOP command is issued to the low-power DDR1-SDRAM.
	 * Program the NOP command in the MPDDRC_MR. calibration request is
	 * now made to the I/O pad.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NOP_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 7: An All Banks Precharge command is issued
	 * to the low-power DDR1-SDRAM.
	 * Program All Banks Precharge command in the MPDDRC_MR.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_PRCGALL_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 8: Two auto-refresh (CBR) cycles are provided.
	 * Program the Auto Refresh command (CBR) in the MPDDRC_MR.
	 * The application must write a four to the MODE field
	 * in the MPDDRC_MR. Perform a write access to any low-power
	 * DDR1-SDRAM location twice to acknowledge these commands.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_RFSH_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 9: An Extended Mode Register Set (EMRS) cycle is issued to
	 * program the low-power DDR1-SDRAM parameters (TCSR, PASR, DS).
	 * The application must write a five to the MODE field in the MPDDRC_MR
	 * and perform a write access to the SDRAM to acknowledge this command.
	 * The write address must be chosen so that signal BA[1] is set to 1
	 * and BA[0] is set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_EXT_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x2 << ba_offset))) = 0;

	/*
	 * Step 10: A Mode Register Set (MRS) cycle is issued to program
	 * parameters of the low-power DDR1-SDRAM devices, in particular
	 * CAS latency.
	 * The application must write a three to the MODE field in the MPDDRC_MR
	 * and perform a write access to the SDRAM to acknowledge this command.
	 * The write address must be chosen so that signals BA[1:0] are set to 0.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_LMR_CMD);
	*((unsigned volatile int *)(ram_address + (0x0 << ba_offset))) = 0;

	/*
	 * Step 11: The application must enter Normal mode, write a zero
	 * to the MODE field in the MPDDRC_MR and perform a write access
	 * at any location in the SDRAM to acknowledge this command.
	 */
	write_ddramc(base_address, HDDRSDRC2_MR, AT91C_DDRC2_MODE_NORMAL_CMD);
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 12: Perform a write access to any low-power DDR1-SDRAM address.
	 */
	*((unsigned volatile int *)ram_address) = 0;

	/*
	 * Step 14: Write the refresh rate into the COUNT field in the MPDDRC
	 * Refresh Timer Register (MPDDRC_RTR):
	 */
	write_ddramc(base_address, HDDRSDRC2_RTR, ddramc_config->rtr);

	return 0;
}

#else
#error "No right DDR-SDRAM device driver provided!"
#endif

void ddramc_dump_regs(unsigned int base_address)
{
#if (BOOTSTRAP_DEBUG_LEVEL >= DEBUG_LOUD)
	unsigned int size = 0x160;

	dbg_info("\nDump DDRAMC Registers:\n");
	dbg_hexdump((unsigned char *)base_address, size, DUMP_WIDTH_BIT_32);
#endif
}
