// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "backup.h"
#include "board.h"
#include "debug.h"
#include "hardware.h"
#include "timer.h"

#ifdef CONFIG_RSTC
#include "rstc.h"
#endif


#include "dram_helpers.h"
#if defined(CONFIG_DDR_SET_BY_TIMING)
#include "umctl2_timing.h"
#else
#include "umctl2_jedec.h"
#endif
#include "umctl2_regs.h"
#include "umctl2.h"
#ifdef CONFIG_PUBL
#include "publ.h"
#endif

#include "arch/at91_sfrbu.h"

#define MP_AXI_PORT_ENABLE(x) (1 << (x))

static struct umctl2_config_state *umctl2_config;

static struct uddrc_regs	*UDDRC_REGS;
static struct uddrc_mp		*UDDRC_MP;


inline static void uddrc_mp_setup()
{
	/* how many clocks until changing to alternate transaction store (rd or wr depending on config) */
	UDDRC_REGS->UDDRC_SCHED	= UDDRC_SCHED_rdwr_idle_gap (umctl2_config->rdwr_idle_gap) |
	/* number of entries in low prio store minus one */
			UDDRC_SCHED_lpr_num_entries(umctl2_config->lpr_num_entries - 1) |
	/* midway policy between Open and Close page policies. meaning keep open or close after use */
			(umctl2_config->pageclose ? UDDRC_SCHED_pageclose : 0) |
	/* choose which transaction store is preffered */
			(umctl2_config->prefer_write ? UDDRC_SCHED_prefer_write : 0) |
	/* this is active low, so disabling force low priority */
			UDDRC_SCHED_force_low_pri_n;
	/* timer for pageclose policy of precharging */
	UDDRC_REGS->UDDRC_SCHED1 = UDDRC_SCHED1_pageclose_timer(umctl2_config->pageclose_timer);

	/* add starvation counters setup for the queues
	 * performance starvation settings on different queues (for 5ns clock)
	 */
	/* how many transactions to service once high prio read queue goes critical */
	UDDRC_REGS->UDDRC_PERFHPR1 = UDDRC_PERFHPR1_hpr_xact_run_length(umctl2_config->hpr_xact_run_length) |
	/* how many DFI clocks that high prio read queue can be starved until going critical */
			UDDRC_PERFHPR1_hpr_max_starve(umctl2_config->hpr_max_starve);
	/* how many transactions to service once low prio read queue goes critical */
	UDDRC_REGS->UDDRC_PERFLPR1 = UDDRC_PERFLPR1_lpr_xact_run_length(umctl2_config->hpr_xact_run_length) |
	/* how many DFI clocks that low prio read queue can be starved until going critical */
			UDDRC_PERFLPR1_lpr_max_starve(umctl2_config->lpr_max_starve);

	/* how many transactions to service once write queue goes critical (low + high prio) */
	UDDRC_REGS->UDDRC_PERFWR1 = UDDRC_PERFWR1_w_xact_run_length(umctl2_config->w_xact_run_length) |
	/* how many DFI clocks that write queue can be starved until going critical (low+high prio)*/
			UDDRC_PERFWR1_w_max_starve(umctl2_config->w_max_starve);

	/* auto precharge for collision cases*/
	UDDRC_REGS->UDDRC_DBG0 = (umctl2_config->dis_collision_page_opt ? UDDRC_DBG0_dis_collision_page_opt : 0) |
	/* disable write combined */
			(umctl2_config->dis_wc ? UDDRC_DBG0_dis_wc : 0 );

	/* reenable dequeue transactions from CAM and issues to DRAM*/
	UDDRC_REGS->UDDRC_DBG1 = 0;

	/* FPGA specific */
	UDDRC_REGS->UDDRC_DBGCMD = 0;

	/* enable interrupt for read//write/slverr AXI transaction poisoning
	   signal to AXI  */
	/* deprecated by TZC ? */

#if defined(AXI_TRANSACTION_POISONING_IRQ_EN)
	UDDRC_REGS->UDDRC_POISONCFG = UDDRC_POISONCFG_rd_poison_intr_en |
			UDDRC_POISONCFG_wr_poison_intr_en |
			UDDRC_POISONCFG_wr_poison_slverr_en;
#endif

	/* multi-port register settings (urgent bit are not connected in the DESIGN
	 *	because they cant be used in the matrix (no master capable))
 	 */

	/* burst length expansion mode = 0 -> each axi burst into multiple HIF commands.
			(this is recommended only for DDR4)
	 * pagematch limit =0 -> no limit on consecutive same page DDRC transactions
	 * go2critical_en = 0 -> signals to go to critical are not in design .
	 */

	UDDRC_MP->UDDRC_PCCFG = 0;

	/* if port is enabled */
	/* port 0 should always be enabled otherwise CPU can't access DDR */
	if (umctl2_config->axi_port_bitmap & MP_AXI_PORT_ENABLE(0)) {
	/* keep read/writes in order ? */
		UDDRC_MP->UDDRC_PCFGR_0 = (umctl2_config->port_x_rdwr_ordered_en ?
			UDDRC_PCFGR_0_rdwr_ordered_en : 0) |
	/* enable pagematch feature: keep port granted if same memory page */
			UDDRC_PCFGR_0_rd_port_pagematch_en |
	/* enable aging function for the read channel */
			UDDRC_PCFGR_0_rd_port_aging_en |
	/* reorder bypass ? */
			UDDRC_PCFGR_0_read_reorder_bypass_en |
	/* initial aging counter for port */
			UDDRC_PCFGR_0_rd_port_priority(0x3FF);

	/* enable pagematch feature: keep port granted if same memory page */
		UDDRC_MP->UDDRC_PCFGW_0 = UDDRC_PCFGW_0_wr_port_pagematch_en |
	/* enable aging for write on the port */
			UDDRC_PCFGW_0_wr_port_aging_en |
	/* initial load value of aging counter for write */
			UDDRC_PCFGW_0_wr_port_priority(0x3FF);

	/* arqos region mapping */
		UDDRC_MP->UDDRC_PCFGQOS0_0 =
			/* end of region 0 mapping */
			UDDRC_PCFGQOS0_0_rqos_map_level1(umctl2_config->port_x_read_region0_last[0]) |
			/* region 2 not used as this is single queue */
			UDDRC_PCFGQOS0_0_rqos_map_level2(0xe) |
			/* region 0 is LPR */
			UDDRC_PCFGQOS0_0_rqos_map_region0(0) |
			/* region 1 is VPR */
			UDDRC_PCFGQOS0_0_rqos_map_region1(1) |
			/* region 2 is unused */
			UDDRC_PCFGQOS0_0_rqos_map_region2(2);

	/* timeout for transactions on blue and red queue */
		UDDRC_MP->UDDRC_PCFGQOS1_0 = UDDRC_PCFGQOS1_0_rqos_map_timeoutb(0x0100) |
			UDDRC_PCFGQOS1_0_rqos_map_timeoutr(0x0100);
	/* awqos region mapping */
		UDDRC_MP->UDDRC_PCFGWQOS0_0 =
			UDDRC_PCFGWQOS0_0_wqos_map_level1(umctl2_config->port_x_write_region0_last[0]) |
			UDDRC_PCFGWQOS0_0_wqos_map_level2(umctl2_config->port_x_write_region1_last[0]) |
			UDDRC_PCFGWQOS0_0_wqos_map_region0(0) |
			UDDRC_PCFGWQOS0_0_wqos_map_region1(1);

	/* timeout for write transactions in the regions */
		UDDRC_MP->UDDRC_PCFGWQOS1_0 = UDDRC_PCFGWQOS1_0_wqos_map_timeout(0x0100);
	}

	/* if port is enabled */
	/* port 1 should always be enabled otherwise we can't access regmap */
	if (umctl2_config->axi_port_bitmap & MP_AXI_PORT_ENABLE(1)) {

	/* keep read/writes in order ? */
	UDDRC_MP->UDDRC_PCFGR_1 = (umctl2_config->port_x_rdwr_ordered_en ?
				UDDRC_PCFGR_1_rdwr_ordered_en : 0) |
	/* enable pagematch feature: keep port granted if same memory page */
			UDDRC_PCFGR_1_rd_port_pagematch_en |
	/* enable aging function for the read channel */
			UDDRC_PCFGR_1_rd_port_aging_en |
	/* reorder bypass ? */
			UDDRC_PCFGR_1_read_reorder_bypass_en |
	/* initial aging counter for port */
			UDDRC_PCFGR_1_rd_port_priority(0x3FF);

	/* enable pagematch feature: keep port granted if same memory page */
		UDDRC_MP->UDDRC_PCFGW_1	= UDDRC_PCFGW_1_wr_port_pagematch_en |
	/* enable aging for write on the port */
			UDDRC_PCFGW_1_wr_port_aging_en |
	/* initial load value of aging counter for write */
			UDDRC_PCFGW_1_wr_port_priority(0x3FF);

	/* arqos region mapping */
		UDDRC_MP->UDDRC_PCFGQOS0_1 =
			/* end of region 0 mapping */
			UDDRC_PCFGQOS0_1_rqos_map_level1(umctl2_config->port_x_read_region0_last[1]) |
			/* region 2 not used as this is single queue */
			UDDRC_PCFGQOS0_1_rqos_map_level2(umctl2_config->port_x_read_region1_last[1]) |
			/* region 0 is VPR */
			UDDRC_PCFGQOS0_1_rqos_map_region0(1) |
			/* region 1 is VPR */
			UDDRC_PCFGQOS0_1_rqos_map_region1(1) |
			/* region 2 is unused */
			UDDRC_PCFGQOS0_1_rqos_map_region2(2);

	/* timeout for transactions on blue and red queue */
		UDDRC_MP->UDDRC_PCFGQOS1_1 = UDDRC_PCFGQOS1_1_rqos_map_timeoutb(0x040) |
			UDDRC_PCFGQOS1_1_rqos_map_timeoutr(0x040);
	/* awqos region mapping */
	UDDRC_MP->UDDRC_PCFGWQOS0_1 =
			UDDRC_PCFGWQOS0_1_wqos_map_level1(umctl2_config->port_x_write_region0_last[1]) |
			UDDRC_PCFGWQOS0_1_wqos_map_level2(umctl2_config->port_x_write_region1_last[1]) |
			UDDRC_PCFGWQOS0_1_wqos_map_region0(1) |
			UDDRC_PCFGWQOS0_1_wqos_map_region1(1);

	/* timeout for write transactions in the regions */
		UDDRC_MP->UDDRC_PCFGWQOS1_1 = UDDRC_PCFGWQOS1_1_wqos_map_timeout(0x040);
	}
	/* if port is enabled */
	/* port 2 is dual queue, for PSS */
	if (umctl2_config->axi_port_bitmap & MP_AXI_PORT_ENABLE(2)) {

	/* keep read/writes in order ? */
		UDDRC_MP->UDDRC_PCFGR_2 = (umctl2_config->port_x_rdwr_ordered_en ?
			UDDRC_PCFGR_2_rdwr_ordered_en : 0) |
	/* enable pagematch feature: keep port granted if same memory page */
			UDDRC_PCFGR_2_rd_port_pagematch_en |
	/* enable aging function for the read channel */
			UDDRC_PCFGR_2_rd_port_aging_en |
	/* reorder bypass ? */
			UDDRC_PCFGR_2_read_reorder_bypass_en |
	/* initial aging counter for port */
			UDDRC_PCFGR_2_rd_port_priority(0x3FF);

	/* enable pagematch feature: keep port granted if same memory page */
		UDDRC_MP->UDDRC_PCFGW_2	= UDDRC_PCFGW_2_wr_port_pagematch_en |
	/* enable aging for write on the port */
			UDDRC_PCFGW_2_wr_port_aging_en |
	/* initial load value of aging counter for write */
			UDDRC_PCFGW_2_wr_port_priority(0x3FF);

	/* arqos region mapping */
		UDDRC_MP->UDDRC_PCFGQOS0_2 =
			/* end of region 0 mapping */
			UDDRC_PCFGQOS0_2_rqos_map_level1(umctl2_config->port_x_read_region0_last[2]) |
			/* end of region 1 mapping */
			UDDRC_PCFGQOS0_2_rqos_map_level2(umctl2_config->port_x_read_region1_last[2]) |
			/* region 0 is LPR */
			UDDRC_PCFGQOS0_2_rqos_map_region0(0) |
			/* region 1 is vPR */
			UDDRC_PCFGQOS0_2_rqos_map_region1(1) |
			/* region 2 is HPR */
			UDDRC_PCFGQOS0_2_rqos_map_region2(2);

	/* timeout for transactions on blue and red queue */
		UDDRC_MP->UDDRC_PCFGQOS1_2 = UDDRC_PCFGQOS1_2_rqos_map_timeoutb(0x0200) |
			UDDRC_PCFGQOS1_2_rqos_map_timeoutr(0x0200);
	/* awqos region mapping */
		UDDRC_MP->UDDRC_PCFGWQOS0_2 =
			UDDRC_PCFGWQOS0_2_wqos_map_level1(umctl2_config->port_x_write_region0_last[2]) |
			UDDRC_PCFGWQOS0_2_wqos_map_level2(umctl2_config->port_x_write_region1_last[2]) |
			UDDRC_PCFGWQOS0_2_wqos_map_region0(0) |
			UDDRC_PCFGWQOS0_2_wqos_map_region1(1);

	/* timeout for write transactions in the regions */
		UDDRC_MP->UDDRC_PCFGWQOS1_2 = UDDRC_PCFGWQOS1_2_wqos_map_timeout1(0x0200) |
				UDDRC_PCFGWQOS1_2_wqos_map_timeout2(0x0200);
	}
	if (umctl2_config->axi_port_bitmap & MP_AXI_PORT_ENABLE(3)) {

	/* keep read/writes in order ? */
		UDDRC_MP->UDDRC_PCFGR_3 = (umctl2_config->port_x_rdwr_ordered_en ?
				UDDRC_PCFGR_3_rdwr_ordered_en : 0) |
	/* enable pagematch feature: keep port granted if same memory page */
			UDDRC_PCFGR_3_rd_port_pagematch_en |
	/* enable aging function for the read channel */
			UDDRC_PCFGR_3_rd_port_aging_en |
	/* reorder bypass ? */
			UDDRC_PCFGR_3_read_reorder_bypass_en |
	/* initial aging counter for port */
			UDDRC_PCFGR_3_rd_port_priority(0x3FF);

	/* enable pagematch feature: keep port granted if same memory page */
		UDDRC_MP->UDDRC_PCFGW_3	= UDDRC_PCFGW_3_wr_port_pagematch_en |
	/* enable aging for write on the port */
			UDDRC_PCFGW_3_wr_port_aging_en |
	/* initial load value of aging counter for write */
			UDDRC_PCFGW_3_wr_port_priority(0x3FF);

	/* arqos region mapping */
		UDDRC_MP->UDDRC_PCFGQOS0_3 =
			/* end of region 0 mapping */
			UDDRC_PCFGQOS0_3_rqos_map_level1(umctl2_config->port_x_read_region0_last[3]) |
			UDDRC_PCFGQOS0_3_rqos_map_level2(umctl2_config->port_x_read_region1_last[3]) |
			/* region 0 is LPR */
			UDDRC_PCFGQOS0_3_rqos_map_region0(0) |
			/* region 1 is VPR */
			UDDRC_PCFGQOS0_3_rqos_map_region1(1) |
			UDDRC_PCFGQOS0_3_rqos_map_region2(2);

	/* timeout for transactions on blue and red queue */
		UDDRC_MP->UDDRC_PCFGQOS1_3 = UDDRC_PCFGQOS1_3_rqos_map_timeoutb(0x0100) |
			UDDRC_PCFGQOS1_3_rqos_map_timeoutr(0x0100);
	/* awqos region mapping */
		UDDRC_MP->UDDRC_PCFGWQOS0_3 =
			UDDRC_PCFGWQOS0_3_wqos_map_level1(umctl2_config->port_x_write_region0_last[3]) |
			UDDRC_PCFGWQOS0_3_wqos_map_level2(umctl2_config->port_x_write_region1_last[3]) |
			UDDRC_PCFGWQOS0_3_wqos_map_region0(0) |
			UDDRC_PCFGWQOS0_3_wqos_map_region1(1);

	/* timeout for write transactions in the regions */
		UDDRC_MP->UDDRC_PCFGWQOS1_3 = UDDRC_PCFGWQOS1_3_wqos_map_timeout(0x0100);
	}


	if (umctl2_config->axi_port_bitmap & MP_AXI_PORT_ENABLE(4)) {

	/* keep read/writes in order ? */
		UDDRC_MP->UDDRC_PCFGR_4 = (umctl2_config->port_x_rdwr_ordered_en ?
			UDDRC_PCFGR_4_rdwr_ordered_en : 0) |
	/* enable pagematch feature: keep port granted if same memory page */
			UDDRC_PCFGR_4_rd_port_pagematch_en |
	/* enable aging function for the read channel */
			UDDRC_PCFGR_4_rd_port_aging_en |
	/* reorder bypass ? */
			UDDRC_PCFGR_4_read_reorder_bypass_en |
	/* initial aging counter for port */
			UDDRC_PCFGR_4_rd_port_priority(0x3FF);

	/* enable pagematch feature: keep port granted if same memory page */
		UDDRC_MP->UDDRC_PCFGW_4	= UDDRC_PCFGW_4_wr_port_pagematch_en |
	/* enable aging for write on the port */
			UDDRC_PCFGW_4_wr_port_aging_en |
	/* initial load value of aging counter for write */
			UDDRC_PCFGW_4_wr_port_priority(0x3FF);

	/* arqos region mapping */
		UDDRC_MP->UDDRC_PCFGQOS0_4 =
			/* end of region 0 mapping */
			UDDRC_PCFGQOS0_4_rqos_map_level1(umctl2_config->port_x_read_region0_last[4]) |
			UDDRC_PCFGQOS0_4_rqos_map_level2(umctl2_config->port_x_read_region1_last[4]) |
			/* region 0 is LPR */
			UDDRC_PCFGQOS0_4_rqos_map_region0(0) |
			/* region 1 is VPR */
			UDDRC_PCFGQOS0_4_rqos_map_region1(1) |
			UDDRC_PCFGQOS0_4_rqos_map_region2(2);

	/* timeout for transactions on blue and red queue */
		UDDRC_MP->UDDRC_PCFGQOS1_4 = UDDRC_PCFGQOS1_4_rqos_map_timeoutb(0x0100) |
			UDDRC_PCFGQOS1_4_rqos_map_timeoutr(0x0100);
	/* awqos region mapping */
		UDDRC_MP->UDDRC_PCFGWQOS0_4 =
			UDDRC_PCFGWQOS0_4_wqos_map_level1(umctl2_config->port_x_write_region0_last[4]) |
			UDDRC_PCFGWQOS0_4_wqos_map_level2(umctl2_config->port_x_write_region1_last[4]) |
			UDDRC_PCFGWQOS0_4_wqos_map_region0(0) |
			UDDRC_PCFGWQOS0_4_wqos_map_region1(1);

	/* timeout for write transactions in the regions */
		UDDRC_MP->UDDRC_PCFGWQOS1_4 = UDDRC_PCFGWQOS1_4_wqos_map_timeout(0x0100);
	}
}


inline static void uddrc_spin_cam_pipeline_empty()
{
	/* spin until both rd and wr pipelines are empty */
	while (!(UDDRC_REGS->UDDRC_DBGCAM & UDDRC_DBGCAM_wr_data_pipeline_empty));
	while (!(UDDRC_REGS->UDDRC_DBGCAM & UDDRC_DBGCAM_rd_data_pipeline_empty));
	/* must read them twice according to datasheet */
	while (!(UDDRC_REGS->UDDRC_DBGCAM & UDDRC_DBGCAM_wr_data_pipeline_empty));
	while (!(UDDRC_REGS->UDDRC_DBGCAM & UDDRC_DBGCAM_rd_data_pipeline_empty));
}

inline static void uddrc_dis_dq()
{
	/* disable dequeuing of rd/wr commands from CAM to DRAM */
	UDDRC_REGS->UDDRC_DBG1 |= UDDRC_DBG1_dis_dq;
#if defined SPIN_CAM_PIPELINE_EMPTY
	uddrc_spin_cam_pipeline_empty();
#endif
}

inline static void uddrc_selfref_en()
{
	/* put DRAM into self refresh after a number of clocks PWRTMG.selfref_to_x32 */
	UDDRC_REGS->UDDRC_PWRCTL |= UDDRC_PWRCTL_selfref_en;
}

inline static void uddrc_mstr()
{
	/* initialize MSTR - master register */
	/* DRAM burst length of 8 for DDR3/DDR2 */
	UDDRC_REGS->UDDRC_MSTR = UDDRC_MSTR_burst_rdwr(UDDRC_MSTR_burst_rdwr_BL8)
	/* use burstchop only for DDR3*/
#ifdef CONFIG_DDR3
							| UDDRC_MSTR_burstchop
#endif
#ifdef CONFIG_DDR3
							| UDDRC_MSTR_ddr3
#endif
#ifdef CONFIG_LPDDR2
							| UDDRC_MSTR_lpddr2
#endif
#ifdef CONFIG_LPDDR3
							| UDDRC_MSTR_lpddr3
#endif
	;

	dbg_very_loud("UMCTL2 MSTR %x\n", UDDRC_REGS->UDDRC_MSTR);
}

inline static void uddrc_derate()
{
#ifdef CONFIG_DDR_EXT_TEMP_RANGE
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	UDDRC_REGS->UDDRC_DERATEEN = UDDRC_DERATEEN_derate_enable |
					UDDRC_DERATEEN_derate_value(0) |
					UDDRC_DERATEEN_derate_byte(0);
	/* Compute the MR4 read interval, according to below formula: */
	/* 10C/sec * (ReadInterval + t_tsi + 1 ms) <= 2C */
	/* <=> ReadInterval + t_tsi + SysRespDelay <= 200 ms */
	/* <=> ReadInterval <= 200ms - t_tsi - SysRespDelay*/
	UDDRC_REGS->UDDRC_DERATEINT =
		UDDRC_DERATEINT_mr4_read_interval(T_TSI);
#endif
#endif
}

inline static void uddrc_configure_lowpwr()
{
	UDDRC_REGS->UDDRC_PWRTMG = UDDRC_PWRTMG_selfref_to_x32(2) |
	/* minimum deep power down time */
			UDDRC_PWRTMG_t_dpd_x4096(0xaf) |
	/* after this many clocks of DDRC idle go to powerdown, multiples of 32 DFI clocks */
			UDDRC_PWRTMG_powerdown_to_x32(3);
	dbg_very_loud("PWRTMG %x\n", UDDRC_REGS->UDDRC_PWRTMG);
}

inline static void uddrc_ena_hw_lowpwr()
{
	/* Enable low power control */
	UDDRC_REGS->UDDRC_HWLPCTL =
				UDDRC_HWLPCTL_hw_lp_exit_idle_en |
				UDDRC_HWLPCTL_hw_lp_idle_x32(0x4d);
}

inline static void uddrc_configure_refresh()
{
	/* number of 32 DFI clocks before critical refresh/page timer */
	UDDRC_REGS->UDDRC_RFSHCTL0 =
				UDDRC_RFSHCTL0_refresh_margin(0x2) |
	/* speculative refresh, number of 32 DFI clocks until can run speculative refresh */
				UDDRC_RFSHCTL0_refresh_to_x32(0x2) |
	/* how many refresh timeouts can handle before refresh is forced to execute (+1)*/
				UDDRC_RFSHCTL0_refresh_burst(0);
	/* not disable refresh on ranks */
	UDDRC_REGS->UDDRC_RFSHCTL3 = 0;
	dbg_very_loud("RFSHCTL0 %x\n", UDDRC_REGS->UDDRC_RFSHCTL0);
	dbg_very_loud("RFSHCTL3 %x\n", UDDRC_REGS->UDDRC_RFSHCTL3);
}

inline static void uddrc_rank_refresh()
{
	UDDRC_REGS->UDDRC_RFSHTMG =
				UDDRC_RFSHTMG_t_rfc_min(T_RFC_MIN) |
				UDDRC_RFSHTMG_t_rfc_nom_x32(T_RFC_NOM_X1_X32);
	dbg_very_loud("RFSHTMG %x\n", UDDRC_REGS->UDDRC_RFSHTMG);
}

inline static void uddrc_dis_crc_parity()
{
	/* do not enable any CRC parity control */
	UDDRC_REGS->UDDRC_CRCPARCTL0 = 0;
}

inline static void uddrc_init0()
{
	/* DRAM init register 0 */
	UDDRC_REGS->UDDRC_INIT0 =
	/* wait val * 1024 DFI cycles after CKE is high to start the DRAM init */
	/* used in step 4) from DDR3 state machine init seq */
				UDDRC_INIT0_post_cke_x1024(POST_CKE_X1024) |
	/* wait val * 1024 DFI cycles before CKE is high , to start the DRAM init */
	/* used in step 3) from DDR3 state machine init seq */
				UDDRC_INIT0_pre_cke_x1024(PRE_CKE_X1024)
	;
	dbg_very_loud("UMCTL2 INIT 0 %x\n", UDDRC_REGS->UDDRC_INIT0);
}


inline static void uddrc_init1()
{
	/* DRAM init register 1 */
	/* number of cycles to assert DRAM reset during init sequence - dfi_reset_n */
	/* used in step 2) from DDR3 state machine init seq */
	UDDRC_REGS->UDDRC_INIT1 = UDDRC_INIT1_dram_rstn_x1024(DRAM_RSTN_X1024) |
	/* number of 32 DFI clocks to wait before driving OCD (driver calibration?) complete to DRAM */
				UDDRC_INIT1_pre_ocd_x32(PRE_OCD_X32)
	;
	dbg_very_loud("UMCTL2 INIT 1 %x\n", UDDRC_REGS->UDDRC_INIT1);

}

inline static void uddrc_init2()
{
	UDDRC_REGS->UDDRC_INIT2 = UDDRC_INIT2_min_stable_clock_x1(MIN_STABLE_CLOCK_X1)
				| UDDRC_INIT2_idle_after_reset_x32(IDLE_AFTER_RESET_X32);
	dbg_very_loud("UMCTL2 INIT 2 %x\n", UDDRC_REGS->UDDRC_INIT2);
}


inline static void uddrc_init3()
{
	UDDRC_REGS->UDDRC_INIT3 = UDDRC_INIT3_mr(MR) | UDDRC_INIT3_emr(EMR);
	dbg_very_loud("UMCTL2 INIT 3v %x\n",UDDRC_INIT3_mr(MR) | UDDRC_INIT3_emr(EMR));
	dbg_very_loud("UMCTL2 INIT 3 %x\n", UDDRC_REGS->UDDRC_INIT3);
}

inline static void uddrc_init4()
{
	/* DRAM init register 4 */
	UDDRC_REGS->UDDRC_INIT4 = UDDRC_INIT4_emr2(EMR2) | UDDRC_INIT4_emr3(EMR3);
	dbg_very_loud("UMCTL2 INIT 4 v %x\n",  UDDRC_INIT4_emr2(EMR2) | UDDRC_INIT4_emr3(EMR3));
	dbg_very_loud("UMCTL2 INIT 4 %x\n", UDDRC_REGS->UDDRC_INIT4);
}

inline static void uddrc_init5()
{
	/* DRAM init register 5 */
	/* initial calibration time */
	UDDRC_REGS->UDDRC_INIT5 =
				UDDRC_INIT5_dev_zqinit_x32(DEV_ZQINIT_X32) |
				UDDRC_INIT5_max_auto_init_x1024(MAX_AUTO_INIT_X1024);
	dbg_very_loud("UMCTL2 INIT 5 %x\n", UDDRC_REGS->UDDRC_INIT5);
}

inline static void uddrc_dimmctl()
{
	/* do not have address mirroring, do not have multi rank */
	UDDRC_REGS->UDDRC_DIMMCTL = 0;
}

inline static void uddrc_dramtmg()
{
	/* configure DRAMTMG* registers */
	/* write to precharge on same bank :
	 * (WriteLatency + Burstlength/2 + tWR write recovery)/2 - freq ratio 1:2
	 */
	/* tRAS min */
	UDDRC_REGS->UDDRC_DRAMTMG0 =
				UDDRC_DRAMTMG0_t_ras_min(T_RAS_MIN) |\
	/* tRAS max, max time activate to precharge, in amounts of 1024 clocks */
				UDDRC_DRAMTMG0_t_ras_max(T_RAS_MAX) |\
	/* tFAW/2 (en clock) : valid if 8 or more banks */
				UDDRC_DRAMTMG0_t_faw(T_FAW) |\
				UDDRC_DRAMTMG0_wr2pre(WR2PRE);
	/* time from powerdown exit until any operation */
	/* tRC - row cycle ? time between activates to same bank , = tRCD + tWR + tRP = tRAS + tRP */
	UDDRC_REGS->UDDRC_DRAMTMG1 =
				UDDRC_DRAMTMG1_t_rc(T_RC) |\
	/* read to precharge of same bank, (tAL + max(tRTP,4))/2 */
				UDDRC_DRAMTMG1_rd2pre(RD2PRE) |\
				UDDRC_DRAMTMG1_t_xp(T_XP);
	/* tWL - write latency, not required in DDR3. Only for LPDDR2*/
	/* write to read latency = (Cas write latency CWL + BL/2 + tWTR (internal write to read ))/2 */
	UDDRC_REGS->UDDRC_DRAMTMG2 =
				UDDRC_DRAMTMG2_wr2rd(WR2RD) |\
	/* read to write latency = (tRL + BL/2 +2 - tWL )/2 */
				UDDRC_DRAMTMG2_rd2wr(RD2WR) |\
	/* tRL - read latency, not required in DDR3. Only for LPDDR2 */
				UDDRC_DRAMTMG2_read_latency(READ_LATENCY) |\
				UDDRC_DRAMTMG2_write_latency(WRITE_LATENCY);
	/* tMRD/2 (cycles to wait after a mode reg write or read) */
	UDDRC_REGS->UDDRC_DRAMTMG3 =
				UDDRC_DRAMTMG3_t_mrd(T_MRD) |\
	/* tMOD/2 : cycles between load mode command and following non-load mode command */
				UDDRC_DRAMTMG3_t_mod(T_MOD) |\
				UDDRC_DRAMTMG3_t_mrw(T_MRW);
	/* (tRCD - tAL)/2 : row to column delay - activate to read or write to same bank */
	/* tRP : minimum time from precharge to activate of the same bank , precharge delay */
	UDDRC_REGS->UDDRC_DRAMTMG4 =
				UDDRC_DRAMTMG4_t_rp(T_RP) |\
	/* tRRD/2 : minimum time between activates from bank a to bank b */
				UDDRC_DRAMTMG4_t_rrd(T_RRD) |\
	/* tCCD/2 :  minimum time between two reads or two writes */
				UDDRC_DRAMTMG4_t_ccd(T_CCD) |\
				UDDRC_DRAMTMG4_t_rcd(T_RCD);
	/* TCKSRX/2 (time before self refresh exit that CK is maintained as a valid clock before issuing SRX) */
	/* RoundUp(tCKE/2) */
	UDDRC_REGS->UDDRC_DRAMTMG5 =
				UDDRC_DRAMTMG5_t_cke(T_CKE) |\
	/* (tCKE+1)/2 (minimum CKE Low width for self refresh to exit) */
				UDDRC_DRAMTMG5_t_ckesr(T_CKESR) |\
	/* TCKSRE/2 (time after self refresh down entry that CK is maintained as a valid clock) */
				UDDRC_DRAMTMG5_t_cksre(T_CKSRE) |\
				UDDRC_DRAMTMG5_t_cksrx(T_CKSRX);
	/* LPDDR only */
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	UDDRC_REGS->UDDRC_DRAMTMG6 =
				UDDRC_DRAMTMG6_t_ckcsx(T_CKCSX) |\
				UDDRC_DRAMTMG6_t_ckdpdx(T_CKDPDX) |\
				UDDRC_DRAMTMG6_t_ckdpde(T_CKDPDE);

	UDDRC_REGS->UDDRC_DRAMTMG7 =
				UDDRC_DRAMTMG7_t_ckpdx(T_CKPDX) |\
				UDDRC_DRAMTMG7_t_ckpde(T_CKPDE);
#endif
	/* tXSDLL/2 : exit self refresh to commands requiring a locked DLL */
	/* tXS/2 : exit self refresh to commands not requiring a locked DLL */
	UDDRC_REGS->UDDRC_DRAMTMG8 =
				UDDRC_DRAMTMG8_t_xs_x32(T_XS_X32) |\
				UDDRC_DRAMTMG8_t_xs_dll_x32(T_XS_DLL_X32);
	//UDDRC_REGS->UDDRC_DRAMTMG14 = UDDRC_DRAMTMG14_t_xsr(T_XSR);
	dbg_very_loud("DRAMTMG0 %x\n", UDDRC_REGS->UDDRC_DRAMTMG0);
	dbg_very_loud("DRAMTMG1 %x\n", UDDRC_REGS->UDDRC_DRAMTMG1);
	dbg_very_loud("DRAMTMG2 %x\n", UDDRC_REGS->UDDRC_DRAMTMG2);
	dbg_very_loud("DRAMTMG3 %x\n", UDDRC_REGS->UDDRC_DRAMTMG3);
	dbg_very_loud("DRAMTMG4 %x\n", UDDRC_REGS->UDDRC_DRAMTMG4);
	dbg_very_loud("DRAMTMG5 %x\n", UDDRC_REGS->UDDRC_DRAMTMG5);
	dbg_very_loud("DRAMTMG6 %x\n", UDDRC_REGS->UDDRC_DRAMTMG6);
	dbg_very_loud("DRAMTMG7 %x\n", UDDRC_REGS->UDDRC_DRAMTMG7);
	dbg_very_loud("DRAMTMG8 %x\n", UDDRC_REGS->UDDRC_DRAMTMG8);
	dbg_very_loud("DRAMTMG14 %x\n", UDDRC_REGS->UDDRC_DRAMTMG14);
}

inline static void uddrc_config_zq_calib()
{
	/* enable generation of auto ZQ calibration by controller */
	/* number of DFI nops to run after ZQ calibration short */
	UDDRC_REGS->UDDRC_ZQCTL0 =
				UDDRC_ZQCTL0_t_zq_short_nop(T_ZQ_SHORT_NOP) |\
	/* ZQ calibration resistor is not shared between ranks */
	/* number of DFI nops to run after ZQ calibration long */
				UDDRC_ZQCTL0_t_zq_long_nop(T_ZQ_LONG_NOP);
	UDDRC_REGS->UDDRC_ZQCTL1 =
				UDDRC_ZQCTL1_t_zq_short_interval_x1024(T_ZQ_SHORT_INTERVAL_X1024) |
				UDDRC_ZQCTL1_t_zq_reset_nop(T_ZQ_RESET_NOP);
	dbg_very_loud("ZQCTL0 %x\n", UDDRC_REGS->UDDRC_ZQCTL0);
	dbg_very_loud("ZQCTL1 %x\n", UDDRC_REGS->UDDRC_ZQCTL1);
}

inline static void uddrc_config_dfi()
{
	/* DFI clocks after assert/deassert of signals until PHY-DRAM reflects them */
	/* clocks from write command to wrdata_en tWRlat*/
	UDDRC_REGS->UDDRC_DFITMG0 =
				UDDRC_DFITMG0_dfi_tphy_wrlat(
				((WLTPHY & 0x1) ? ((WLTPHY - 1) / 2) : ((WLTPHY - 2) / 2))) |\
	/* clocks from assertion of wrdata_en to write data is driven */
				UDDRC_DFITMG0_dfi_tphy_wrdata(0) |\
	/* select to use DFI or DFI PHY clock for dfi signals */
	/* clocks from assertion of DFI signals until dfi_rddata_en -phy specific*/
				UDDRC_DFITMG0_dfi_t_rddata_en(
				((RLTPHY & 0x1) ? ((RLTPHY - 3) / 2) : ((RLTPHY - 2) / 2))) |\
				UDDRC_DFITMG0_dfi_t_ctrl_delay(2);
	/* clocks between dfi_cs asserted and dfi_parity_in is driven */
	/* clocks between dfi_dram-clk_disable asserted until first rising edge to DRAM clock */
	UDDRC_REGS->UDDRC_DFITMG1 =
				UDDRC_DFITMG1_dfi_t_dram_clk_enable(2) |\
	/* clocks between dfi_dram_clk_disable asserted until clock to DRAM maintains low value */
				UDDRC_DFITMG1_dfi_t_dram_clk_disable(2) |\
	/* clocks between dfi_wrdata_en asserted and data transfered completed on bus */
				UDDRC_DFITMG1_dfi_t_wrdata_delay(0);
	/* clocks for tlp_resp time low power response time - assumed*/
	UDDRC_REGS->UDDRC_DFILPCFG0 =
	/* clocks to drive on dfi_lp_wakeup when enter power down - 16 cycles should be 0x3 or 0x0 ? */
				UDDRC_DFILPCFG0_dfi_lp_wakeup_pd (7) |\
	/* clocks to drive on dfi_lp_wakeup when enter self refresh - 4096 cycles should be 0x8 or 0x80 ? */
				UDDRC_DFILPCFG0_dfi_lp_wakeup_sr (7) |\
				UDDRC_DFILPCFG0_dfi_lp_wakeup_dpd(7)|\
				UDDRC_DFILPCFG0_dfi_tlp_resp(7);
	/* enable automatic generation of dfi_ctrlupd_req */
	/* min clocks that dfi_ctrlupd_req can assert */
	UDDRC_REGS->UDDRC_DFIUPD0 =
				UDDRC_DFIUPD0_dfi_t_ctrlup_min(3) |\
	/* max clocks that dfi_ctrlupd_req can assert */
				UDDRC_DFIUPD0_dfi_t_ctrlup_max(1023);
	/* min number of 1024 clocks between DFI update requests initiated by umctl2 */
	UDDRC_REGS->UDDRC_DFIUPD1 =
				UDDRC_DFIUPD1_dfi_t_ctrlupd_interval_max_x1024\
				(255) |\
				UDDRC_DFIUPD1_dfi_t_ctrlupd_interval_min_x1024\
				(240);
	/* enable support for acking phy initiated updates */
	UDDRC_REGS->UDDRC_DFIUPD2 = UDDRC_DFIUPD2_dfi_phyupd_en;
	/* enable support for acking phy initiated updates */
	/* disable PHY master interface */
	UDDRC_REGS->UDDRC_DFIPHYMSTR = 0;

	dbg_very_loud("DFITMG0 %x\n", UDDRC_REGS->UDDRC_DFITMG0);
	dbg_very_loud("DFITMG1 %x\n", UDDRC_REGS->UDDRC_DFITMG1);
	dbg_very_loud("DFILPCFG0 %x\n", UDDRC_REGS->UDDRC_DFILPCFG0);
	dbg_very_loud("DFIUPD0 %x\n", UDDRC_REGS->UDDRC_DFIUPD0);
	dbg_very_loud("DFIUPD1 %x\n", UDDRC_REGS->UDDRC_DFIUPD1);
}

inline static void uddrc_addrmap_init()
{
	unsigned int addrmap_col_b2;
	unsigned int addrmap_col_b3;
	unsigned int addrmap_col_b4;
	unsigned int addrmap_col_b5;
	unsigned int addrmap_col_b6;
	unsigned int addrmap_col_b7;
	unsigned int addrmap_col_b8;
	unsigned int addrmap_col_b9;
	unsigned int addrmap_col_b10;
	unsigned int addrmap_col_b11;
	unsigned int addrmap_bank_b0;
	unsigned int addrmap_bank_b1;
	unsigned int addrmap_bank_b2;
	unsigned int addrmap_row_b0;
	unsigned int addrmap_row_b1;
	unsigned int addrmap_row_b2_10;
	unsigned int addrmap_row_b11;
	unsigned int addrmap_row_b12;
	unsigned int addrmap_row_b13;
	unsigned int addrmap_row_b14;
	unsigned int addrmap_row_b15;

	/* To calculate the pagematch attribute of a port, the XPI needs to
	know logical to physical address mapping. Logical address is the
	command address of a transaction as presented on one of the ports.
	A physical address is the set of bank group, bank, row and column
	address as presented to the SDRAM memory. The actual conversion
	from logical to physical address is performed by the DDRC (see
	ADDRMAPx registers with x=0 to 11). The bank address locations
	are indicated in the ADDRMAP1 register. The row address locations
	are indicated in ADDRMAP5, ADDRMAP6, and ADDRMAP7 registers and
	depending on the value of the ADDRMAP5.addrmap_row_b2_10 field,
	in ADDRMAP9, ADDRMAP10 and ADDRMAP11 registers (see UMCTL2_REGS
	Registers). The XPI block uses these registers to determine the
	pagematch attribute of each DDRC command forwarded to the PA. */

	/* base_addr = 0x6000_0000/512MB = 3 */
	UDDRC_MP->UDDRC_SARBASE0 = AT91C_BASE_DDRCS / (512 * 1024 * 1024);
	/* nblocks=(2GB/512MB)-1 = 3 */
	UDDRC_MP->UDDRC_SARSIZE0 = 3;
	dbg_very_loud("sarbase %x, offset = %x\n", UDDRC_MP->UDDRC_SARBASE0,
			OFFSETOF(struct uddrc_mp, UDDRC_SARBASE0));

	addrmap_col_b2  = (NB_COL_BITS >  2) ? 0 : 15; /* internal base = 2  (unused col  = 15)*/
	addrmap_col_b3  = (NB_COL_BITS >  3) ? 0 : 15; /* internal base = 3  (unused col  = 15)*/
	addrmap_col_b4  = (NB_COL_BITS >  4) ? 0 : 15; /* internal base = 4  (unused col  = 15)*/
	addrmap_col_b5  = (NB_COL_BITS >  5) ? 0 : 15; /* internal base = 5  (unused col  = 15)*/
	addrmap_col_b6  = (NB_COL_BITS >  6) ? 0 : 31; /* internal base = 6  (unused col  = 31)*/
	addrmap_col_b7  = (NB_COL_BITS >  7) ? 0 : 31; /* internal base = 7  (unused col  = 31)*/
	addrmap_col_b8  = (NB_COL_BITS >  8) ? 0 : 31; /* internal base = 8  (unused col  = 31)*/
	addrmap_col_b9  = (NB_COL_BITS >  9) ? 0 : 31; /* internal base = 9  (unused col  = 31)*/
	addrmap_col_b10 = (NB_COL_BITS > 10) ? 0 : 31; /* internal base = 10 (unused col  = 31)*/
	addrmap_col_b11 = (NB_COL_BITS > 11) ? 0 : 31; /* internal base = 11 (unused col  = 31)*/
	addrmap_bank_b0 = (NB_BANK_BITS > 0) ? (NB_COL_BITS - 2) : 63; /* internal base = 2 (unused ba  = 63) */
	addrmap_bank_b1 = (NB_BANK_BITS > 1) ? (NB_COL_BITS - 2) : 63; /* internal base = 3 (unused ba  = 63) */
	addrmap_bank_b2 = (NB_BANK_BITS > 2) ? (NB_COL_BITS - 2) : 63; /* internal base = 4 (unused ba  = 63) */
	addrmap_row_b0  = (NB_ROW_BITS >  0) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 31;
	/* internal base = 6  (unused row  = 31) */
	addrmap_row_b1     = (NB_ROW_BITS >  1) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 31;
	/* internal base = 7  (unused row  = 31) */
	addrmap_row_b2_10  = (NB_ROW_BITS >  2) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 31;
	/* internal base = 8  (unused row  = 31) */
	addrmap_row_b11    = (NB_ROW_BITS > 11) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 31;
	/* internal base = 17 (unused row  = 31) */
	addrmap_row_b12    = (NB_ROW_BITS > 12) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 15;
	/* internal base = 18 (unused row  = 15) */
	addrmap_row_b13    = (NB_ROW_BITS > 13) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 15;
	/* internal base = 19 (unused row  = 15) */
	addrmap_row_b14    = (NB_ROW_BITS > 14) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 15;
	/* internal base = 20 (unused row  = 15) */
	addrmap_row_b15    = (NB_ROW_BITS > 15) ? (NB_COL_BITS + NB_BANK_BITS - 6) : 15;
	/* internal base = 21 (unused row  = 15) */

	UDDRC_REGS->UDDRC_ADDRMAP1 = UDDRC_ADDRMAP1_addrmap_bank_b0(addrmap_bank_b0) |
					UDDRC_ADDRMAP1_addrmap_bank_b1(addrmap_bank_b1) |
					UDDRC_ADDRMAP1_addrmap_bank_b2(addrmap_bank_b2);
	UDDRC_REGS->UDDRC_ADDRMAP2 = UDDRC_ADDRMAP2_addrmap_col_b2(addrmap_col_b2 ) |
					UDDRC_ADDRMAP2_addrmap_col_b3(addrmap_col_b3 ) |
					UDDRC_ADDRMAP2_addrmap_col_b4(addrmap_col_b4 ) |
					UDDRC_ADDRMAP2_addrmap_col_b5(addrmap_col_b5 );
	UDDRC_REGS->UDDRC_ADDRMAP3 = UDDRC_ADDRMAP3_addrmap_col_b6(addrmap_col_b6 ) |
					UDDRC_ADDRMAP3_addrmap_col_b7(addrmap_col_b7 ) |
					UDDRC_ADDRMAP3_addrmap_col_b8(addrmap_col_b8 ) |
					UDDRC_ADDRMAP3_addrmap_col_b9(addrmap_col_b9 );
	UDDRC_REGS->UDDRC_ADDRMAP4 = UDDRC_ADDRMAP4_addrmap_col_b10(addrmap_col_b10) |
					UDDRC_ADDRMAP4_addrmap_col_b11(addrmap_col_b11);
	UDDRC_REGS->UDDRC_ADDRMAP5 = UDDRC_ADDRMAP5_addrmap_row_b0(addrmap_row_b0) |
					UDDRC_ADDRMAP5_addrmap_row_b1(addrmap_row_b1) |
					UDDRC_ADDRMAP5_addrmap_row_b2_10(addrmap_row_b2_10) |
					UDDRC_ADDRMAP5_addrmap_row_b11(addrmap_row_b11);
	UDDRC_REGS->UDDRC_ADDRMAP6 = UDDRC_ADDRMAP6_addrmap_row_b12(addrmap_row_b12) |
					UDDRC_ADDRMAP6_addrmap_row_b13(addrmap_row_b13) |
					UDDRC_ADDRMAP6_addrmap_row_b14(addrmap_row_b14) |
					UDDRC_ADDRMAP6_addrmap_row_b15(addrmap_row_b15);
	UDDRC_REGS->UDDRC_ADDRMAP9   = 0; /* unused because UDDRC_ADDRMAP5_ADDRMAP_ROW_B2_10!=15 */
	UDDRC_REGS->UDDRC_ADDRMAP10  = 0; /* unused because UDDRC_ADDRMAP5_ADDRMAP_ROW_B2_10!=15 */
	UDDRC_REGS->UDDRC_ADDRMAP11  = 0; /* unused because UDDRC_ADDRMAP5_ADDRMAP_ROW_B2_10!=15 */
	dbg_very_loud("UDDRC_REGS->UDDRC_ADDRMAP1 =%x\n",UDDRC_REGS->UDDRC_ADDRMAP1);
	dbg_very_loud("UDDRC_REGS->UDDRC_ADDRMAP2 =%x\n",UDDRC_REGS->UDDRC_ADDRMAP2);
	dbg_very_loud("UDDRC_REGS->UDDRC_ADDRMAP3 =%x\n",UDDRC_REGS->UDDRC_ADDRMAP3);
	dbg_very_loud("UDDRC_REGS->UDDRC_ADDRMAP4 =%x\n",UDDRC_REGS->UDDRC_ADDRMAP4);
	dbg_very_loud("UDDRC_REGS->UDDRC_ADDRMAP5 =%x\n",UDDRC_REGS->UDDRC_ADDRMAP5);
	dbg_very_loud("UDDRC_REGS->UDDRC_ADDRMAP6 =%x\n",UDDRC_REGS->UDDRC_ADDRMAP6);
}

inline static void uddrc_mr1()
{
	UDDRC_REGS->UDDRC_MRCTRL0 = 0
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	/* select mode register 1 MR1 */
			| UDDRC_MRCTRL0_mr_addr(0x1)
#endif
	/* select rank 0 only */
			| UDDRC_MRCTRL0_mr_rank(0x1);
	dbg_very_loud("MRCTRL0 %x\n", UDDRC_REGS->UDDRC_MRCTRL0);
	dbg_very_loud("MRCTRL1 %x\n", UDDRC_REGS->UDDRC_MRCTRL1);
}

inline static void uddrc_dis_hw_lowpwr()
{
	/* disable hardware low power features */
	UDDRC_REGS->UDDRC_HWLPCTL = 0;
}

inline static void uddrc_config_odt_timings()
{
#if defined(CONFIG_DDR3) || defined(CONFIG_DDR2)
	/* DFI clocks to delay between read and setting ODT values , recommended CL - CWL */
	UDDRC_REGS->UDDRC_ODTCFG = UDDRC_ODTCFG_rd_odt_delay(RD_ODT_DELAY) |\
	/* DFI clocks to hold ODT for a read, 6 is recommended */
				UDDRC_ODTCFG_rd_odt_hold (RD_ODT_HOLD) |\
	/* DFI clocks to delay between write and setting ODT values , 0 recommended */
				UDDRC_ODTCFG_wr_odt_delay(WR_ODT_DELAY) |\
	/* DFI clocks to hold ODT for a write, 6 is recommended */
				UDDRC_ODTCFG_wr_odt_hold(WR_ODT_HOLD);
	/* which remote ODTs must be turned on during a read on rank X (we have just rank 0) */
	UDDRC_REGS->UDDRC_ODTMAP = UDDRC_ODTMAP_rank0_wr_odt | UDDRC_ODTMAP_rank0_rd_odt;
#endif
/* LPDDR2 does not use ODT */
#if defined(CONFIG_LPDDR2) || defined(CONFIG_LPDDR3)
	UDDRC_REGS->UDDRC_ODTCFG = 0;
	UDDRC_REGS->UDDRC_ODTMAP = 0;
#endif
	dbg_very_loud("ODTCFG %x\n", UDDRC_REGS->UDDRC_ODTCFG);
	dbg_very_loud("ODTMAP %x\n", UDDRC_REGS->UDDRC_ODTMAP);
}

/* Main entry point of the UMCTL2 DRAM driver.
 * state is a preconfigured umctl2_config.
 * The driver will initialize the Controller and then turn back control.
 * state is useless after this call returns.
 */
int umctl2_init (struct umctl2_config_state *state)
{
	unsigned int ret = 0;

#ifndef CONFIG_SYS_BASE_UMCTL2
#error "CONFIG_SYS_BASE_UMCTL2 undefined"
#endif

#ifndef CONFIG_SYS_BASE_UMCTL2_MP
#error "CONFIG_SYS_BASE_UMCTL2_MP undefined"
#endif

	UDDRC_REGS = (struct uddrc_regs *) CONFIG_SYS_BASE_UMCTL2;
	UDDRC_MP = (struct uddrc_mp *) CONFIG_SYS_BASE_UMCTL2_MP;

	/* hold a global pointer to the state */
	umctl2_config = state;

	/* Make sure IOs are not in retention mode. */
	if (!backup_resume()) {
		sfrbu_set_ddr_power_mode(1);
		while (!sfrbu_ddr_is_powered()) ;
	}

	rstc_ddr_assert();
	udelay(100);

#ifdef CONFIG_RSTC
	/*
	 * STEP 0: Deassert reset signal DDR PHY. This ensures that the
	 * PHY starts.
	 */
	rstc_ddr_phy_rst_deassert();
#else
#error "UMCTL2 requires RSTC access for ddrc_phy_rstn signal"
#endif
	/* wait for clock synchronization */
	udelay(100);

	/* STEP 1
	 * Program the DWC_ddr_umctl2 registers
	 * (Ensure that DFIMISC.dfi_init_complete_en is set to 0)
	 */

	/* Clear the DFI Miscellaneous Control register */
	UDDRC_REGS->UDDRC_DFIMISC = 0;
	/* disable dequeuing of rd/wr commands from CAM to DRAM */
	uddrc_dis_dq();
	/* configure master register MSTR - type of DDR, burst length*/
	uddrc_mstr();
	/* configure automatic temperature derating */
	uddrc_derate();
	/* Update the Low Power Timing register */
	uddrc_configure_lowpwr();
	/* enable hardware low power features */
	uddrc_ena_hw_lowpwr();
	/* configure refresh-related parameters */
	uddrc_configure_refresh();
	/* configure refresh per rank */
	uddrc_rank_refresh();
	/* disable crc parity control */
	uddrc_dis_crc_parity();
	/* configure INIT0 - clocks to wait before and after CKE is asserted,
	 * mode of operation after reset is removed
	 */
	uddrc_init0();
	/* configure INIT1 - clocks to assert DRAM reset during init,
	 * pre-ocd complete delay
	 */
	uddrc_init1();
	/* configure INIT2 - Min stable clock, idle after reset */
	uddrc_init2();
	/* configure INIT3 - DRAM registers MR0 and MR1 */
	uddrc_init3();
	/* configure INIT4 - DRAM registers MR2 and MR3 */
	uddrc_init4();
	/* configure INIT5 - initial calibration time */
	uddrc_init5();
	/* configure DIMM control */
	uddrc_dimmctl();
	/* configure DRAM timings */
	uddrc_dramtmg();
	/* Update ZQ Control registers 0 and 1 */
	uddrc_config_zq_calib();
	/* configure mapping between HIF addr to bank, column, row
	 internal address */
	/* configure DFI interface to PHY */
	uddrc_config_dfi();
	/* configure mapping between HIF addr to bank, column, row internal address */
	uddrc_addrmap_init();
	/* configure DFI clocks to wait on ODT rd/wr commands */
	uddrc_config_odt_timings();

	/* multi-port register settings (urgent bit are not connected in the DESIGN) */
	uddrc_mp_setup();

	if (backup_resume()) {
		/* Skip SDRAM init while keeping the controller in self-refresh. */
		UDDRC_REGS->UDDRC_INIT0 |= UDDRC_INIT0_skip_dram_init(3);
		UDDRC_REGS->UDDRC_PWRCTL |= UDDRC_PWRCTL_selfref_sw;
		UDDRC_REGS->UDDRC_DFIMISC &= ~UDDRC_DFIMISC_dfi_init_complete_en;
	}

#ifdef CONFIG_RSTC
	/* STEP 2
	 * Deassert reset signal core_ddrc_rstn ! (mandatory)
	 */
	rstc_ddr_rst_deassert();
#else
#error "UMCTL2 requires RSTC access for core_ddrc_rstn signal"
#endif

#if defined POWER_CYCLE_ON_PHY_INIT
	if (!backup_resume()) {
		UDDRC_REGS->UDDRC_DBG1 = 0;
		/* power down and power up ? */
		UDDRC_REGS->UDDRC_PWRCTL &= UDDRC_PWRCTL_powerdown_en;
		UDDRC_REGS->UDDRC_PWRCTL = 0;
	}
#endif

#if defined(CONFIG_DDR2) || defined(CONFIG_DDR3) || defined(CONFIG_LPDDR2)
	//UDDRC_REGS->UDDRC_PWRCTL = UDDRC_PWRCTL_en_dfi_dram_clk_disable;
#endif

	/* STEP 3
	 * Init PHY
	 */
#if defined CONFIG_PUBL
	state->phy_init();
#endif
	if (backup_resume()) {
		if (state->phy_bypass_zq_calibration)
			state->phy_bypass_zq_calibration();
		else
			dbg_very_loud("UMCTL2: phy_bypass_zq_calibration() required for backup mode!");
	}

	/* STEP 4
	 * Wait PHY init
	 */
	if (state->phy_idone())
		return -1;

	if (backup_resume()) {
		if (state->phy_override_zq_calibration)
			state->phy_override_zq_calibration();
		else
			dbg_printf("UMCTL2: phy_override_zq_calibration() required for backup mode!");

		if (state->phy_prepare_train_corrupted_data_restore)
			state->phy_prepare_train_corrupted_data_restore(BL);
		else
			dbg_printf("UMCTL2: phy_prepare_train_corrupted_data_restore() required for backup mode!");
	}

	/* STEP 5
	 * Enable uMCTL2 dfi init start signal
	 * in case of DRAM init is done via PHY: start PHY
	 */
	if (state->phy_start())
		return -1;

	if (backup_resume()) {
		/* Remove IOs from retention mode. */
		sfrbu_set_ddr_power_mode(1);
		while (!sfrbu_ddr_is_powered()) ;

		if (state->phy_zq_recalibrate)
			state->phy_zq_recalibrate();
		else
			dbg_very_loud("UMCTL2: phy_sr_exit_phase1() required for backup mode!");
	}

	/* STEP 6
	 * Set SWCTL.sw_done to 0 : to enable programming of
	 * quasi-static registers outside of reset
	 */
	/* DO NOT Check SWSTAT.sw_done_ack = 1 */
	UDDRC_REGS->UDDRC_SWCTL = 0;

	/* STEP 7
	 * set DFI init complete to 1
	 */
	UDDRC_REGS->UDDRC_DFIMISC |= UDDRC_DFIMISC_dfi_init_complete_en;

	/* STEP 8
	 * Set software done to 1; also,
	 * Only quasi-dinamic registers can be modified from now on
	 */
	UDDRC_REGS->UDDRC_SWCTL	= UDDRC_SWCTL_sw_done;

	/* STEP 9
	 * Wait for SWSTAT.sw_done_ack to become 1 :
	 * ONLY AFTER UDDRC_SWCTL_sw_done
	 */
	WAIT_WHILE_COND((UDDRC_REGS->UDDRC_SWSTAT != UDDRC_SWSTAT_sw_done_ack), 0xA6);

	if (backup_resume()) {
		/* Triger self-refresh exit. */
		UDDRC_REGS->UDDRC_PWRCTL &= ~UDDRC_PWRCTL_selfref_sw;

		WAIT_WHILE_COND (((UDDRC_REGS->UDDRC_STAT & UDDRC_STAT_operating_mode_Msk) !=
			UDDRC_STAT_operating_mode_Normal), 10000);
	}

	/* STEP 10
	 * Check for uMCTL2 in normal mode
	 */
	WAIT_WHILE_COND (((UDDRC_REGS->UDDRC_STAT & UDDRC_STAT_operating_mode_Msk) !=
		UDDRC_STAT_operating_mode_Normal), 10000);

	/* STEP 11
	 * Disable auto-refreshes
	 */
	UDDRC_REGS->UDDRC_RFSHCTL3 |= UDDRC_RFSHCTL3_dis_auto_refresh;
	UDDRC_REGS->UDDRC_RFSHCTL3 ^= UDDRC_RFSHCTL3_refresh_update_level;

	/* STEP 11a
	 * Mask transitions in phy_dfi_init_complete during PHY training
	 */
	UDDRC_REGS->UDDRC_SWCTL = 0;
	UDDRC_REGS->UDDRC_DFIMISC &= ~UDDRC_DFIMISC_dfi_init_complete_en;
	UDDRC_REGS->UDDRC_SWCTL = UDDRC_SWCTL_sw_done;

	WAIT_WHILE_COND((UDDRC_REGS->UDDRC_SWSTAT != UDDRC_SWSTAT_sw_done_ack), 0xA6);

	/* STEP 12
	 * Train PHY
	 */
	ret = state->phy_train();
	if (ret)
		return ret;

	if (backup_resume()) {
		if (state->phy_train_corrupted_data_restore)
			state->phy_train_corrupted_data_restore();
		else
			dbg_very_loud("UMCTL2: phy_train_corrupted_data_restore() required for backup mode!");
	}

	/* STEP 13
	 * Revert steps 11 and 11a
	 */
	UDDRC_REGS->UDDRC_RFSHCTL3 &= ~UDDRC_RFSHCTL3_dis_auto_refresh;
	UDDRC_REGS->UDDRC_RFSHCTL3 ^= UDDRC_RFSHCTL3_refresh_update_level;

	UDDRC_REGS->UDDRC_SWCTL = 0;
	UDDRC_REGS->UDDRC_DFIMISC |= UDDRC_DFIMISC_dfi_init_complete_en;
	UDDRC_REGS->UDDRC_SWCTL = UDDRC_SWCTL_sw_done;

	WAIT_WHILE_COND((UDDRC_REGS->UDDRC_SWSTAT != UDDRC_SWSTAT_sw_done_ack), 0xA6);

	/* STEP 14
	 * AXI ports can now take transactions
	 */
	if (umctl2_config->axi_port_bitmap &  MP_AXI_PORT_ENABLE(0))
		UDDRC_MP->UDDRC_PCTRL_0	= UDDRC_PCTRL_0_port_en;
	if (umctl2_config->axi_port_bitmap &  MP_AXI_PORT_ENABLE(1))
		UDDRC_MP->UDDRC_PCTRL_1	= UDDRC_PCTRL_1_port_en;
	if (umctl2_config->axi_port_bitmap &  MP_AXI_PORT_ENABLE(2))
		UDDRC_MP->UDDRC_PCTRL_2	= UDDRC_PCTRL_2_port_en;
	if (umctl2_config->axi_port_bitmap &  MP_AXI_PORT_ENABLE(3))
		UDDRC_MP->UDDRC_PCTRL_3	= UDDRC_PCTRL_3_port_en;
	if (umctl2_config->axi_port_bitmap &  MP_AXI_PORT_ENABLE(4))
		UDDRC_MP->UDDRC_PCTRL_4	= UDDRC_PCTRL_4_port_en;

	return ret;
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
