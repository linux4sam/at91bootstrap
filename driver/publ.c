// Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "backup.h"
#include "board.h"
#include "common.h"
#include "debug.h"
#include "hardware.h"
#include "timer.h"

#include "publ_regs.h"
#include "publ.h"

#include "dram_helpers.h"
#if defined(CONFIG_DDR_SET_BY_TIMING)
#include "umctl2_timing.h"
#else
#include "umctl2_jedec.h"
#endif

static struct publ_regs		*PUBL;

void publ_init(void)
{
	PUBL = (struct publ_regs *) CONFIG_SYS_BASE_PUBL;

#if 1
#ifdef CONFIG_DDR3
	PUBL->PUBL_DCR = PUBL_DCR_DDRMD_DDR3 | PUBL_DCR_DDRMD_DDR8BNK;
#endif
#ifdef CONFIG_DDR2
	PUBL->PUBL_DCR =
			PUBL_DCR_DDRMD_DDR2 |\
			((NB_BANK_BITS == 3) ? PUBL_DCR_DDRMD_DDR8BNK : 0) ;
#endif
#ifdef CONFIG_LPDDR2_S2
	PUBL->PUBL_DCR =
			PUBL_DCR_DDRMD_LPDDR2 |\
			((NB_BANK_BITS == 3) ? PUBL_DCR_DDRMD_DDR8BNK : 0) |
			PUBL_DCR_DDRTYPE_S2;
#endif
#ifdef CONFIG_LPDDR2_S4
	PUBL->PUBL_DCR =
			PUBL_DCR_DDRMD_LPDDR2 |\
			((NB_BANK_BITS == 3) ? PUBL_DCR_DDRMD_DDR8BNK : 0) |
			PUBL_DCR_DDRTYPE_S4;
#endif
#ifdef CONFIG_LPDDR3
	PUBL->PUBL_DCR = PUBL_DCR_DDRMD_LPDDR3 | PUBL_DCR_DDRMD_DDR8BNK;
#endif

	PUBL->PUBL_PGCR =
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
			PUBL_PGCR_DQSCFG |
#endif
			PUBL_PGCR_CKEN(1) | PUBL_PGCR_CKDV(2) |
			PUBL_PGCR_RANKEN(1) | PUBL_PGCR_ZCKSEL(1) |
			PUBL_PGCR_PDDISDX;

	PUBL->PUBL_PTR0 =
	/* Max of 50ns and 8 controller clock cycles, unit is an APB clock cycle */
			PUBL_PTR0_TDLLSRST(MAX(ROUNDUP(50000, DDR_CLOCK_PERIOD), 8)) |\
	/* 5.12us, unit is an APB clock cycle */
			PUBL_PTR0_TDLLLOCK(ROUNDUP(5120000,DDR_CLOCK_PERIOD)) |\
	/* 8 controller clock cycles, unit is an APB clock cycle */
			PUBL_PTR0_TITMSRST(8);
	dbg_very_loud("PUBL_PTR0 %x\n", PUBL->PUBL_PTR0);

#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	PUBL->PUBL_PTR1 =
			PUBL_PTR1_TDINIT0(ROUNDUP(TPRECKE, DDR_CLOCK_PERIOD)) |\
			PUBL_PTR1_TDINIT1(ROUNDUP(TPOSTCKE, DDR_CLOCK_PERIOD));
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_PTR1 =
			PUBL_PTR1_TDINIT0(ROUNDUP(TINIT3, DDR_CLOCK_PERIOD)) |\
			PUBL_PTR1_TDINIT1(ROUNDUP(TINIT1, DDR_CLOCK_PERIOD));
#endif
	dbg_very_loud("PUBL_PTR1 %x\n", PUBL->PUBL_PTR1);


#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	PUBL->PUBL_PTR2 =
			PUBL_PTR2_TDINIT2(ROUNDUP(200000000, DDR_CLOCK_PERIOD)) |\
			PUBL_PTR2_TDINIT3(534);
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_PTR2 =
			PUBL_PTR2_TDINIT2(ROUNDUP(TINIT4 + TINIT5, DDR_CLOCK_PERIOD)) |
			PUBL_PTR2_TDINIT3(ROUNDUP(TZQINIT, DDR_CLOCK_PERIOD));
#endif
	dbg_very_loud("PUBL_PTR2 %x\n", PUBL->PUBL_PTR2);

#ifdef CONFIG_DDR3
	unsigned int mr_cl, mr_wr;
	mr_cl = ((CL == 5) ? 2 : (CL == 6) ? 4 : (CL == 7) ? 6 : \
		(CL == 8) ? 8 : (CL == 9) ? 10 : (CL == 10) ? 12 :\
		(CL == 11) ? 14 : (CL == 12) ? 1 : (CL == 13) ? 3 :\
		(CL == 14) ? 5 : (CL == 15) ? 7 : 9);

	mr_wr = ((WR <= 5) ? 1 : (WR == 6) ? 2 : (WR == 7) ? 3 :\
		(WR == 8) ? 4 : (WR == 10) ? 5 : (WR == 12) ? 6 : 7);
	PUBL->PUBL_MR0 =
			PUBL_MR0_BL |\
			((mr_cl & 0x1) << PUBL_MR0_CL_POS) |\
			(((mr_cl & 0xE) >> 1) << 4) |\
			PUBL_MR0_DR |\
			PUBL_MR0_WR(mr_wr);
#endif
#ifdef CONFIG_DDR2
	PUBL->PUBL_MR0 =
			((BL == 8) ? 3 : 2) |\
			PUBL_MR0_CL(CL) |\
			PUBL_MR0_DR |\
			PUBL_MR0_WR(WR - 1);
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_MR0 = 0;
#endif
	dbg_very_loud("PUBL_MR0 %x\n", PUBL->PUBL_MR0);

#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	PUBL->PUBL_MR1 = PUBL_MR1_RTT0 | PUBL_MR1_AL(AL);
#endif
#if defined(CONFIG_LPDDR2)
	PUBL->PUBL_MR1 = PUBL_MR1_BL(((BL == 16) ? 4 : (BL == 8) ? 3 : 2)) |\
			 PUBL_MR1_NWR(WR - 2);
#endif
#if defined(CONFIG_LPDDR3)
	PUBL->PUBL_MR1 = PUBL_MR1_BL(3) | PUBL_MR1_NWR(WR_SEL - 2);
#endif
	dbg_very_loud("PUBL_MR1 %x\n", PUBL->PUBL_MR1);

#ifdef CONFIG_DDR3
	PUBL->PUBL_MR2 = PUBL_MR2_CWL(CWL - 5)
#ifdef CONFIG_DDR_EXT_TEMP_RANGE
			| PUBL_MR2_ASR | PUBL_MR2_SRT
#endif
	;
#endif
#ifdef CONFIG_DDR2
	PUBL->PUBL_MR2 = 0
#ifdef CONFIG_DDR_EXT_TEMP_RANGE
			|  PUBL_MR2_SRT
#endif
	;
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_MR2 = RL - 2;
#endif
	dbg_very_loud("PUBL_MR2 %x\n", PUBL->PUBL_MR2);


#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_MR3 = 0;
#endif
#ifdef CONFIG_LPDDR2
	PUBL->PUBL_MR3 = PUBL_MR3_DS_40OHM;
#endif
	dbg_very_loud("PUBL_MR3 %x\n", PUBL->PUBL_MR3);

#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	PUBL->PUBL_ODTCR = PUBL_ODTCR_WRODT0(1);
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_ODTCR = 0;
#endif
	dbg_very_loud("PUBL_ODTCR %x\n", PUBL->PUBL_ODTCR);

	PUBL->PUBL_DTPR0 =
#ifdef CONFIG_DDR3
			PUBL_DTPR0_TMRD(TMRD - 4) |
			PUBL_DTPR0_TRP(MIN(MAX(ROUNDUP(TRP,DDR_CLOCK_PERIOD) - 1, 2), 14)) |
#endif
#if defined(CONFIG_DDR2)
			PUBL_DTPR0_TMRD(TMRD) |
			PUBL_DTPR0_TRP(MIN(MAX(ROUNDUP(TRP,DDR_CLOCK_PERIOD), 2), 14)) |
#endif
#ifdef CONFIG_LPDDR2
			PUBL_DTPR0_TMRD(TMRW - 4) |
#if(NB_BANK_BITS == 3)
			PUBL_DTPR0_TRP(MIN(MAX(ROUNDUP(TRPab,DDR_CLOCK_PERIOD)- 1, 2), 14)) |
#else
			PUBL_DTPR0_TRP(MIN(MAX(ROUNDUP(TRPab,DDR_CLOCK_PERIOD), 2), 14)) |
#endif
#endif
#ifdef CONFIG_LPDDR3
			PUBL_DTPR0_TMRD(ROUNDUP(TMRD,DDR_CLOCK_PERIOD) - 8) |
			PUBL_DTPR0_TRP(MIN(MAX(ROUNDUP(TRPab,DDR_CLOCK_PERIOD) - 1, 2), 14)) |
#endif

			PUBL_DTPR0_TRTP(MIN(MAX(ROUNDUP(TRTP,DDR_CLOCK_PERIOD), 2), 6)) |
			PUBL_DTPR0_TWTR(MIN(MAX(ROUNDUP(TWTR,DDR_CLOCK_PERIOD), 1), 6)) |
			PUBL_DTPR0_TRCD(MIN(MAX(ROUNDUP(TRCD,DDR_CLOCK_PERIOD), 2), 15)) |
			PUBL_DTPR0_TRAS(MIN(MAX(ROUNDUP(TRASMIN,DDR_CLOCK_PERIOD), 2), 31)) |
			PUBL_DTPR0_TRRD(MIN(MAX(ROUNDUP(TRRD,DDR_CLOCK_PERIOD), 1), 8)) |
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
			PUBL_DTPR0_TRC(MIN(MAX(ROUNDUP(TRC,DDR_CLOCK_PERIOD), 2), 42));
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
			PUBL_DTPR0_TRC(MIN(MAX(ROUNDUP(TRCab,DDR_CLOCK_PERIOD), 2), 42));
#endif
	dbg_very_loud("PUBL_DTPR0 %x\n", PUBL->PUBL_DTPR0);

	PUBL->PUBL_DTPR1 =
			PUBL_DTPR1_TFAW(MIN(MAX(ROUNDUP(TFAW,DDR_CLOCK_PERIOD), 2), 31)) |
#ifdef CONFIG_DDR3
			PUBL_DTPR1_TMOD(ROUNDUP(TMOD,DDR_CLOCK_PERIOD) - 12) |
#endif
#ifdef CONFIG_DDR2
			PUBL_DTPR1_TAOND(TAOND - 2) |
#endif
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
			PUBL_DTPR1_TRFC(MIN(ROUNDUP(TRFC,DDR_CLOCK_PERIOD), 255)) |
			PUBL_DTPR1_TDQSCKMIN(1) | PUBL_DTPR1_TDQSCKMAX(1)
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
			PUBL_DTPR1_TRFC(MIN(ROUNDUP(TRFCab,DDR_CLOCK_PERIOD), 255)) |
			PUBL_DTPR1_TDQSCKMIN(MIN(MAX(ROUNDDWN(TDQSCK_MIN,DDR_CLOCK_PERIOD), 0), 7)) |
			PUBL_DTPR1_TDQSCKMAX(MIN(MAX(ROUNDUP (TDQSCK_MAX,DDR_CLOCK_PERIOD), 1), 7))
#endif
			;
	dbg_very_loud("PUBL_DTPR1 %x\n", PUBL->PUBL_DTPR1);

	PUBL->PUBL_DTPR2 =
#if defined(CONFIG_DDR3)
			PUBL_DTPR2_TXS( MIN(MAX(MAX(ROUNDUP(TXS,DDR_CLOCK_PERIOD),TXSDLL),2), 1023)) |
			PUBL_DTPR2_TXP(MIN(MAX(ROUNDUP(MAX(TXP,TXPDLL),DDR_CLOCK_PERIOD), 2), 31)) |
			PUBL_DTPR2_TCKE(MIN(MAX(ROUNDUP(TCKESR,DDR_CLOCK_PERIOD), 2), 15)) |
			PUBL_DTPR2_TDLLK(MIN(MAX(TDLLK, 2), 1023))
#endif
#if defined(CONFIG_DDR2)
			PUBL_DTPR2_TXS(MIN(MAX(MAX(ROUNDUP(TXSNR,DDR_CLOCK_PERIOD),TXSRD), 2), 1023)) |
			PUBL_DTPR2_TXP(MIN(MAX(MAX(TXP,MAX(TXARD,TXARDS)), 2), 31)) |
			PUBL_DTPR2_TCKE(MIN(MAX(TCKE, 2), 15)) |
			PUBL_DTPR2_TDLLK(512)
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
			PUBL_DTPR2_TXS(MIN(MAX(ROUNDUP(TXSR,DDR_CLOCK_PERIOD), 2), 1023)) |
			PUBL_DTPR2_TXP(MIN(MAX(ROUNDUP(TXP,DDR_CLOCK_PERIOD), 2), 31)) |
			PUBL_DTPR2_TCKE(MIN(MAX(MAX(TCKE,ROUNDUP(TCKESR,DDR_CLOCK_PERIOD)), 2), 15)) |
			PUBL_DTPR2_TDLLK(512)
#endif
			;
	dbg_very_loud("PUBL_DTPR2 %x\n", PUBL->PUBL_DTPR2);

	PUBL->PUBL_DSGCR =
			PUBL_DSGCR_PUREN | PUBL_DSGCR_BDISEN |
			PUBL_DSGCR_ZUEN | PUBL_DSGCR_LPIOPD | PUBL_DSGCR_LPDLLPD |
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
			PUBL_DSGCR_DQSGX(ROUNDUP(TDQSCK_MAX-TDQSCK_MIN,DDR_CLOCK_PERIOD)) |
			PUBL_DSGCR_DQSGE(ROUNDUP(TDQSCK_MAX-TDQSCK_MIN,DDR_CLOCK_PERIOD)) |
#endif
			PUBL_DSGCR_FXDLAT | PUBL_DSGCR_NL2OE |
			PUBL_DSGCR_TPDOE | PUBL_DSGCR_CKOE |
			PUBL_DSGCR_ODTOE | PUBL_DSGCR_RSTOE |
			PUBL_DSGCR_CKEOE;
	dbg_very_loud("PUBL_DSCGR %x\n", PUBL->PUBL_DSGCR);


#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	PUBL->PUBL_DXCCR = 0;
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_DXCCR = PUBL_DXCCR_DQSRES_500OHM | PUBL_DXCCR_DQSNRES_500OHM
			| PUBL_DXCCR_DQSNRES_PU;
#endif
	dbg_very_loud("PUBL_DXCCR %x\n", PUBL->PUBL_DXCCR);

	PUBL->PUBL_ZQ0CR1 = PUBL_ZQ0CR1_ZPROG_OID(ZPROG_OUTPUT)
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
			| PUBL_ZQ0CR1_ZPROG_ODT(ZPROG_ODT)
#endif
						;
	dbg_very_loud("PUBL_ZQ0CR1 %x\n", PUBL->PUBL_ZQ0CR1);
#endif
}

int publ_idone()
{
	udelay(100);

	WAIT_WHILE_COND(!(PUBL->PUBL_PGSR & PUBL_PGSR_IDONE), 50000);

	return 0;
}

int publ_start()
{
	PUBL->PUBL_PIR = PUBL_PIR_INIT | PUBL_PIR_CTLDINIT;

	return publ_idone();
}

int publ_train()
{
	PUBL->PUBL_PGCR = (PUBL->PUBL_PGCR & ~(PUBL_PGCR_RANKEN_MASK << PUBL_PGCR_RANKEN_POS)) |
			 PUBL_PGCR_RANKEN(1);

	PUBL->PUBL_DTAR = 0;

	PUBL->PUBL_PIR = PUBL_PIR_INIT | PUBL_PIR_QSTRN | PUBL_PIR_RVTRN;

	if (publ_idone())
		return -1;

	dbg_very_loud("PUBL_DCUSR0 %x\n", PUBL->PUBL_DCUSR0);
	dbg_very_loud("PUBL_DCUSR1 %x\n", PUBL->PUBL_DCUSR1);
	if (PUBL->PUBL_PGSR & (PUBL_PGSR_DTERR | PUBL_PGSR_DTIERR |
		PUBL_PGSR_RVERR | PUBL_PGSR_RVEIRR)) {
		dbg_info("PUBL: Error Training PHY : PGSR = %x\n", PUBL->PUBL_PGSR);
		return -1;
	} else if (!backup_resume()) {
		dbg_info("PUBL: Training complete.\n");
	}

	return 0;
}

int publ_bypass_zq_calibration(void)
{
	if (!backup_resume())
		return -1;

	PUBL->PUBL_PIR |= PUBL_PIR_ZCALBYP;

	return 0;
}

int publ_override_zq_calibration(void)
{
	unsigned int data[9];

	if (!backup_resume())
		return -1;

	backup_get_calibration_data(data, ARRAY_SIZE(data));
	PUBL->PUBL_ZQ0CR0 = PUBL_ZQ0CR0_ZDEN | PUBL_ZQ0CR0_ZDATA(data[0]);

	return 0;
}

int publ_zq_recalibrate(void)
{
	PUBL->PUBL_ZQ0CR0 &= ~PUBL_ZQ0CR0_ZDEN;
	PUBL->PUBL_PIR = PUBL_PIR_INIT | PUBL_PIR_ZCAL;

	publ_idone();

	if (PUBL->PUBL_ZQ0SR0 & PUBL_ZQ0SR0_ZERR)
		dbg_very_loud("ZQ calibrate error\n");

	return 0;
}

static void publ_wr_dcu_cmd_cache(unsigned int data, unsigned int address,
				  unsigned int bank, unsigned int cmd,
				  unsigned int dtp, unsigned int repeat)
{
	PUBL->PUBL_DCUDR = data;
	PUBL->PUBL_DCUDR = (address <<  4) |
			   (bank << 20) |
			   (cmd << 23) |
			   ((dtp & 0x07) << 29);

	PUBL->PUBL_DCUDR = (((dtp & 0x18) >> 3) <<  0) | (repeat << 2);
}

int publ_prepare_train_corrupted_data_restore(unsigned int bl)
{
	unsigned int address = 0, bank = 0;
	unsigned int data[9] = {0};

	backup_get_calibration_data(data, ARRAY_SIZE(data));

	/* Use pointer auto-incrementation */
	PUBL->PUBL_DCUAR = PUBL_DCUAR_CWADDR(0x0) |
			   PUBL_DCUAR_CSADDR(0x0) |
			   PUBL_DCUAR_CSEL(0x0) |
			   PUBL_DCUAR_INCA | PUBL_DCUAR_ATYPE;

	/* CMD = ACT 6 / DTP = ACT2RW 21 */
	publ_wr_dcu_cmd_cache(0, address, bank, 6, 21, 0);

	/* CMD = WR 8 / DTP = WR2PRE 23 */
	publ_wr_dcu_cmd_cache(data[1], address, 0, 8, 23, 0);
	publ_wr_dcu_cmd_cache(data[2], address, 0, 8, 23, 0);

	address = (bl == 8) ? 0 : 4;
	publ_wr_dcu_cmd_cache(data[3], address, 0, 8, 23, 0);
	publ_wr_dcu_cmd_cache(data[4], address, 0, 8, 23, 0);

	address = 8;
	publ_wr_dcu_cmd_cache(data[5], address, 0, 8, 23, 0);
	publ_wr_dcu_cmd_cache(data[6], address, 0, 8, 23, 0);

	address = (bl == 8) ? 8 : 12;
	publ_wr_dcu_cmd_cache(data[7], address, 0, 8, 23, 0);
	publ_wr_dcu_cmd_cache(data[8], address, 0, 8, 23, 0);

	/* CMD = PRECHARGE ALL 5 / DTP = NONE 0 */
	publ_wr_dcu_cmd_cache(0, 0, 0, 5, 0, 0);

	return 0;
}

int publ_train_corrupted_data_restore(void)
{
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	PUBL->PUBL_DCURR = PUBL_DCURR_SADDR(0) | PUBL_DCURR_EADDR(9) |
			   PUBL_DCURR_DINST(1);
#endif
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	PUBL->PUBL_DCURR = PUBL_DCURR_SADDR(0) | PUBL_DCURR_EADDR(10) |
			   PUBL_DCURR_DINST(1);
#endif

	WAIT_WHILE_COND(!(PUBL->PUBL_DCUSR0 & PUBL_DCUSR0_RDONE), 50000);

	return 0;
}
