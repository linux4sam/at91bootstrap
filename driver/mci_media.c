/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "common.h"
#include "string.h"
#include "hardware.h"
#include "board.h"
#include "arch/at91_mci.h"
#include "mci_media.h"
#include "timer.h"

#include "debug.h"

#define DEFAULT_SD_BLOCK_LEN		512
#define CONFIG_SYS_DEFAULT_CLK		400000

static struct sdcard_register	sdcard_register;
static struct sd_command	sdcard_command;
static struct sd_card		atmel_sdcard;

static unsigned int	response[4];

static const struct sd_command	sd_command_table[] =  {
	/* CMD17 */
	{
		.cmd		= SD_CMD_READ_SINGLE_BLOCK,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ
					| AT91C_MCI_TRTYP_SINGLE),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD18 */
	{
		.cmd		= SD_CMD_READ_MULTIPLE_BLOCK,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ
					| AT91C_MCI_TRTYP_MULTIPLE),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD55 */
	{
		.cmd		= SD_CMD_APP_CMD,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* ACMD6 */
	{
		.cmd		= SD_CMD_APP_SET_BUS_WIDTH,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD16 */
	{
		.cmd		= SD_CMD_SET_BLOCKLEN,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD12 */
	{
		.cmd		= SD_CMD_STOP_TRANSMISSION,
		.flag		= (AT91C_MCI_RSPTYP_R1B
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD13 */
	{
		.cmd		= SD_CMD_SEND_STATUS,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD0 */
	{
		.cmd		= SD_CMD_GO_IDLE_STATE,
		.flag		= 0,
		.error_check	= 0,
		.resp		= response,
	},
	/* CMD2 */
	{
		.cmd		= SD_CMD_ALL_SEND_CID,
		.flag		= (AT91C_MCI_RSPTYP_136
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD3 */
	{
		.cmd		= SD_CMD_SEND_RELATIVE_ADDR,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
#ifdef CONFIG_SDCARD_HS
	/* CMD6 */
	{
		.cmd		= SD_CMD_SWITCH_FUN,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
#endif
	/* CMD7 */
	{
		.cmd		= SD_CMD_SELECT_CARD,
		.flag		= (AT91C_MCI_RSPTYP_R1B
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD8 */
	{
		.cmd		= SD_CMD_SEND_IF_COND,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD9 */
	{
		.cmd		= SD_CMD_SEND_CSD,
		.flag		= (AT91C_MCI_RSPTYP_136
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* CMD10 */
	{
		.cmd		= SD_CMD_SEND_CID,
		.flag		= (AT91C_MCI_RSPTYP_136
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* ACMD41 */
	{
		.cmd		= SD_CMD_APP_SD_SEND_OP_COND,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* ACMD51 */
	{
		.cmd		= SD_CMD_APP_SEND_SCR,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
#ifdef CONFIG_MMC_SUPPORT
	/* MMC CMD1 */
	{
		.cmd		= MMC_CMD_SEND_OP_COND,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* MMC CMD6 */
	{
		.cmd		= MMC_CMD_SWITCH_FUN,
		.flag		= (AT91C_MCI_RSPTYP_R1B
					| AT91C_MCI_MAXLAT_64),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* MMC CMD8 */
	{
		.cmd		= MMC_CMD_SEND_EXT_CSD,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* MMC CMD14 */
	{
		.cmd		= MMC_CMD_BUSTEST_R,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
	/* MMC CMD19 */
	{
		.cmd		= MMC_CMD_BUSTEST_W,
		.flag		= (AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_WRITE),
		.error_check	= (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RCRCE
					| AT91C_MCI_RENDE
					| AT91C_MCI_RTOE),
		.resp		= response,
	},
#endif /* #ifdef CONFIG_MMC_SUPPORT */
};

static int init_sd_command(struct sd_command *command)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(sd_command_table); i++) {
		if (command->cmd == sd_command_table[i].cmd)
			break;
	}

	if (i == ARRAY_SIZE(sd_command_table))
		return -1;

	command->cmd = sd_command_table[i].cmd;
	command->flag = sd_command_table[i].flag;
	command->error_check = sd_command_table[i].error_check;
	command->resp = sd_command_table[i].resp;

	return 0;
}

/*
 * Refer to the at91sam9g20 datasheet:
 * Figure 35-9: Command/Response Functional Flow Diagram
 */
static int sd_send_command(struct sd_command *command)
{
	unsigned int cmdr;
	unsigned int cmdarg;
	unsigned int status;
	unsigned int error_status;
	unsigned int *response;
	int ret;

	ret = init_sd_command(command);
	if (ret)
		return ret;

	error_status = command->error_check;
	response = command->resp;

	command->cmd &= (~(SD_APP_CMD | MMC_CMD));

	cmdr = command->cmd;
	cmdr |= command->flag;

	cmdarg = command->argu;

	/* Set the Command Argument Register */
	mci_writel(MCI_ARGR, cmdarg);
	/* Set the Command Register */
	mci_writel(MCI_CMDR, cmdr);

	/* Wait for the command ready status flag */
	while (!((status = mci_readl(MCI_SR)) & AT91C_MCI_CMDRDY))
		;

	/* Check error bits in the status register */
	if (status & AT91C_MCI_RTOE) {
		dbg_log(1, "Cmd: %d Response Time-out\n\r", command->cmd);
		return ERROR_TIMEOUT;
	}

	if (status & error_status) {
		dbg_log(1, "Error command, cmd: %d, status: %d\n\r", \
				command->cmd, status);
		return ERROR_COMM;
	}

	if (!command->flag)
		return 0;

	/*  Read response */
	if ((command->flag & AT91C_MCI_RSPTYP_136) == AT91C_MCI_RSPTYP_136) {
		*response++ = mci_readl(MCI_RSPR);
		*response++ = mci_readl(MCI_RSPR1);
		*response++ = mci_readl(MCI_RSPR2);
		*response++ = mci_readl(MCI_RSPR3);
	} else
		*response = mci_readl(MCI_RSPR);

	return 0;
}

static int sd_card_reset(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_GO_IDLE_STATE;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

static int sd_verify_operating_condition(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SEND_IF_COND;
	command->argu = CHECK_PATTERN;
	command->argu |= (sdcard->votage_host_support
				&& OCR_VOLTAGE_27_36_MASK) ? (0x01 << 8) : 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	if (((command->resp[0] & CHECK_PATTERN) != CHECK_PATTERN)
		|| (((command->resp[0] >> 8) & 0x0f) != 0x01))
		return ERROR_UNUSABLE_CARD;
	else
		return 0;
}

/* Host Capacity Support / Card Capacity Status */
#define OCR_HCR_CCS		(0x01 << 30)
#define OCR_BUSY_STATUS		(0x01 << 31)

static int sd_check_operational_condition(struct sd_card *sdcard,
			unsigned int host_capacity_support)
{
	struct sd_command *command = sdcard->command;
	unsigned int timeout = 1000;
	int ret;

	/*
	 * The host repeatedly issues ACMD41 for at least 1 second
	 * or until the busy bit are set to 1.
	 */
	do {
		command->cmd = SD_CMD_APP_CMD;
		command->argu = sdcard->reg->rca << 16;

		ret = sd_send_command(command);
		if (ret)
			return ret;

		command->cmd = SD_CMD_APP_SD_SEND_OP_COND;
		command->argu = sdcard->votage_host_support
					& OCR_VOLTAGE_27_36_MASK;
		if (host_capacity_support)
			command->argu |= OCR_HCR_CCS;

		ret = sd_send_command(command);
		if (ret)
			return ret;

		udelay(1000);
	} while ((!(command->resp[0] & OCR_BUSY_STATUS)) && --timeout);

	if (!timeout)
		return ERROR_UNUSABLE_CARD;

	sdcard->reg->ocr = command->resp[0];

	return 0;
}

static int sd_card_id_number(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_ALL_SEND_CID;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	sdcard->reg->cid[0] = command->resp[0];
	sdcard->reg->cid[1] = command->resp[1];
	sdcard->reg->cid[2] = command->resp[2];
	sdcard->reg->cid[3] = command->resp[3];

	return 0;
}

static int sd_relative_card_address(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SEND_RELATIVE_ADDR;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	sdcard->reg->rca = (sdcard->card_type == CARD_TYPE_SD) ?
					(command->resp[0] >> 16) & 0xffff : 0;

	return 0;
}

static int sd_send_status(struct sd_card *sdcard, unsigned int timeout)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SEND_STATUS;
	command->argu = sdcard->reg->rca << 16;

	do {
		ret = sd_send_command(command);
		if (ret)
			return ret;

		if ((command->resp[0] >> 8) & 0x01)
			break;

		if (command->resp[0] & CARD_STATUS_MASK)
			return -1;

		udelay(1000);
	} while (--timeout);

	if (!timeout) {
		dbg_log(1, "Timeout, wait for card ready\n\r");
		return ERROR_TIMEOUT;
	}

	return 0;
}

static int sd_enter_transfer_state(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SELECT_CARD;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

static int sd_read_card_specific_data(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SEND_CSD;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	sdcard->reg->csd[0] = command->resp[0];
	sdcard->reg->csd[1] = command->resp[1];
	sdcard->reg->csd[2] = command->resp[2];
	sdcard->reg->csd[3] = command->resp[3];

	return 0;
}

static int sd_read_card_configuration(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int scr[2];
	unsigned int bytes_to_read = 8;
	unsigned int block_len = DEFAULT_SD_BLOCK_LEN;
	int ret;

	command->cmd = SD_CMD_APP_CMD;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	command->cmd = SD_CMD_APP_SEND_SCR;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	ret = at91_mci_read_block_data(scr, bytes_to_read, block_len);
	if (ret)
		return ret;

	sdcard->reg->scr[0] = be32_to_cpu(scr[0]);
	sdcard->reg->scr[1] = be32_to_cpu(scr[1]);

	return 0;
}

static int sd_set_card_bus_width(struct sd_card *sdcard,
				unsigned int bus_width)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_CMD;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	command->cmd = SD_CMD_APP_SET_BUS_WIDTH;
	command->argu = (bus_width == 4) ? 0x02 : 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

#ifdef CONFIG_SDCARD_HS

/* SD SWITCH */
#define SD_SWITCH_MODE_CHECK	0
#define SD_SWITCH_MODE_SET	1

#define SD_SWITCH_GRP_ACCESS_MODE	1
#define SD_SWITCH_GRP_CMD_SYS		2
#define SD_SWITCH_GRP_DRV_STRENGTH	3
#define SD_SWITCH_GRP_CUR_LIMIT		4

#define SD_SWITCH_FUNC_SDR12		0x00
#define SD_SWITCH_FUNC_HS_SDR25		0x01
#define	SD_SWITCH_FUNC_SDR50		0x02
#define SD_SWITCH_FUNC_SDR104		0x03
#define SD_SWITCH_FUNC_DDR50		0x04

static int sd_switch_function(struct sd_card *sdcard,
				unsigned int mode,
				unsigned int group,
				unsigned int func,
				unsigned int *status)
{
	struct sd_command *command = sdcard->command;
	unsigned int bytes_to_read = 64;
	unsigned int block_len = DEFAULT_SD_BLOCK_LEN;
	int ret;

	command->cmd = SD_CMD_SWITCH_FUN;
	command->argu = (mode << 31) | 0xffffff;
	command->argu &= ~(0xf << ((group - 1) * 4));
	command->argu |= func << ((group - 1) * 4);

	ret = sd_send_command(command);
	if (ret)
		return ret;

	ret = at91_mci_read_block_data(status, bytes_to_read, block_len);
	if (ret)
		return ret;

	return 0;
}

/*
 * Refer to Physical Layer Specification Version 3.1
 * 4.3.10.6 Switch Function Flow example
 * 4.3.10.7 Example of Checking
 */
static int switch_check_hs_busy_status_supported(struct sd_card *sdcard,
						unsigned char *support)
{
	unsigned int switch_func_status[16];
	unsigned int status;
	unsigned int version;
	unsigned int timeout = 6;
	int ret;

	do {
		/* Mode 0 operation: check function */
		ret = sd_switch_function(sdcard,
					SD_SWITCH_MODE_CHECK,
					SD_SWITCH_GRP_ACCESS_MODE,
					SD_SWITCH_FUNC_HS_SDR25,
					switch_func_status);
		if (ret)
			return ret;

		/* Check Data Structure version
		 * 0x00 - bits 511:376 are defined
		 * 0x01 - bits 511:272 are defined
		 */
		version = be32_to_cpu(switch_func_status[4]);
		if (((version >> 16) & 0xff) == 0x00)
			break;

		/* Check Busy Status of function */
		status = be32_to_cpu(switch_func_status[7]);
		if (!((status >> 17) & 0x01))
			break;
	} while (--timeout);

	if (!timeout)
		return -1;

	/* Check function supported */
	status = be32_to_cpu(switch_func_status[3]);
	*support = ((status >> 17) & 0x01) ? 1 : 0;

	return 0;
}

static int sd_switch_func_high_speed(struct sd_card *sdcard)
{
	unsigned int switch_func_status[16];
	unsigned int status;
	unsigned char support;
	int ret;

	ret = switch_check_hs_busy_status_supported(sdcard, &support);
	if (ret)
		return ret;

	if (!support) {
		dbg_log(1, "SD: Not support HS function Switch\n\r");
		return 0;
	}

	/* Mode 1 operation: set functioin */
	ret = sd_switch_function(sdcard,
				SD_SWITCH_MODE_SET,
				SD_SWITCH_GRP_ACCESS_MODE,
				SD_SWITCH_FUNC_HS_SDR25,
				switch_func_status);
	if (ret)
		return ret;

	/* Check Switched function */
	status = be32_to_cpu(switch_func_status[4]);
	if ((status >> 24) & 0x01) {
		sdcard->highspeed_card = 1;
		return 0;
	} else
		return -1;
}
#endif	/* #ifdef CONFIG_SDCARD_HS */

static int sd_card_set_bus_width(struct sd_card *sdcard)
{
	unsigned int bus_width;
	int ret;

	bus_width = (sdcard->bus_width_support & 0x04) ? 4 : 1;

	ret = sd_set_card_bus_width(sdcard, bus_width);
	if (ret)
		return ret;

	ret = at91_mci_set_bus_width(bus_width);
	if (ret)
		return ret;

	return 0;
}

/*-----------------------------------------------------------------*/
#ifdef CONFIG_MMC_SUPPORT

static int mmc_cmd_send_op_cond(struct sd_card *sdcard,
				unsigned int ocr)
{
	struct sd_command *command = sdcard->command;
	unsigned int volage_mask = (~(ocr & 0x01 << 0x17)) << 15;
	int ret;

	command->cmd = MMC_CMD_SEND_OP_COND;
	command->argu = (sdcard->votage_host_support & volage_mask)
				| (ocr & ((~(0x1 << 2)) << 30));

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

static int mmc_verify_operating_condition(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int ocr;
	unsigned int timeout = 2000;
	int ret;

	/* Query the card and determine the voltage type of the card */
	ret = mmc_cmd_send_op_cond(sdcard, 0);
	if (ret)
		return ret;

	/*
	 * The SEND_OP_COND (CMD1) command is designed to provide
	 * MultiMediaCard hosts withe mechanism to identify and
	 * reject cards which do not match the Vdd range desire
	 * by the host
	 * The busy bit int the CMD1 response can be used
	 * by a card to tell the host that it is still working
	 * on its power-up/reset procedure and is not ready yet
	 * for communication.
	 * In this case the host must repeat CMD1
	 * until the busy bit is cleared.
	 */
	ocr = command->resp[0];

	do {
		ret = mmc_cmd_send_op_cond(sdcard, ocr);
		if (ret)
			return ret;

		if (command->resp[0]  & (0x01 << 31))
			break;

		udelay(1000);
	} while (--timeout);

	if (!timeout)
		return ERROR_UNUSABLE_CARD;

	sdcard->reg->ocr = command->resp[0];

	return 0;
}

static int mmc_switch(struct sd_card *sdcard,
				unsigned char access_mode,
				unsigned char index,
				unsigned char value)
{
	struct sd_command *command = sdcard->command;
	unsigned int timeout = 1000;
	int ret;

	command->cmd = MMC_CMD_SWITCH_FUN;
	command->argu = (access_mode << 24)
			| (index << 16)
			| (value << 8);

	ret = sd_send_command(command);

	/*
	 * The SWITCH command response is of type R1b,
	 * therefore, the host should read the card status,
	 * using SEND_STATUS command, after the busy is de-asserted,
	 * to check the result of the SWITCH operation.
	 */
	sd_send_status(sdcard, timeout);
	if (ret)
		return ret;

	return 0;
}

static int mmc_send_ext_csd(struct sd_card *sdcard, char *ext_csd)
{
	struct sd_command *command = sdcard->command;
	unsigned int *data = (unsigned int *)ext_csd;
	unsigned int block_len = 512;
	int ret;

	command->cmd = MMC_CMD_SEND_EXT_CSD;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	ret = at91_mci_read_block_data(data, block_len, block_len);
	if (ret)
		return ret;

	return 0;
}

/* EXT_CSD access mode */
#define MMC_EXT_CSD_ACCESS_CMD_SET	0x00
#define MMC_EXT_CSD_ACCESS_SET_BITS	0x01
#define MMC_EXT_CSD_ACCESS_CLEAR_BITS	0x02
#define MMC_EXT_CSD_ACCESS_WRITE_BYTE	0x03

/*  */
#define EXT_CSD_BYTE_BUS_WIDTH		183
#define EXT_CSD_BYTE_HS_TIMING		185
#define EXT_CSD_BYTE_POWER_CLASS	187
#define EXT_CSD_BYTE_CMD_SET_REV	189
#define EXT_CSD_BYTE_CMD_SET		191
#define EXT_CSD_BYTE_EXT_CSD_REV	192
#define EXT_CSD_BYTE_CSD_STRUCTURE	194
#define EXT_CSD_BYTE_CARD_TYPE		196

static int mmc_switch_high_speed(struct sd_card *sdcard)
{
	char ext_csd[512];
	char cardtype;
	int ret;

	ret = mmc_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;

	cardtype = ext_csd[EXT_CSD_BYTE_CARD_TYPE] & 0x03;

	ret = mmc_switch(sdcard,
			MMC_EXT_CSD_ACCESS_WRITE_BYTE,
			EXT_CSD_BYTE_HS_TIMING,
			1);
	if (ret)
		return ret;

	ret = mmc_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;

	if (!ext_csd[EXT_CSD_BYTE_HS_TIMING])
		return -1;

	sdcard->highspeed_card = (cardtype & 0x02) ? 1 : 0;
	return 0;
}

static int mmc_send_bus_test_r(struct sd_card *sdcard,
				unsigned int buswidth,
				unsigned char *data)
{
	struct sd_command *command = sdcard->command;
	unsigned int bytes_to_read;
	unsigned int block_len = 512;
	int ret;

	bytes_to_read = (buswidth == 8) ? 8 : 4;

	command->cmd = MMC_CMD_BUSTEST_R;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	ret = at91_mci_read_block_data((unsigned int *)data,
						bytes_to_read,
						block_len);
	if (ret)
		return ret;

	return 0;
}

static int mmc_send_bus_test_w(struct sd_card *sdcard,
				unsigned int buswidth,
				unsigned char *data)
{
	struct sd_command *command = sdcard->command;
	unsigned int bytes_to_write;
	unsigned int block_len = 512;
	int ret;

	bytes_to_write = (buswidth == 8) ? 8 : 4;

	command->cmd = MMC_CMD_BUSTEST_W;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	ret = at91_mci_write_block_data((unsigned int *)data,
						bytes_to_write,
						block_len);
	if (ret)
		return ret;

	return 0;
}

#define MMC_BUS_WIDTH_8		2
#define MMC_BUS_WIDTH_4		1
#define MMC_BUS_WIDTH_1		0

static int mmc_bus_width_select(struct sd_card *sdcard, unsigned int buswidth)
{
	unsigned char busw;
	int ret;

	if (buswidth == 8)
		busw = MMC_BUS_WIDTH_8;
	else if (buswidth == 4)
		busw = MMC_BUS_WIDTH_4;
	else
		busw = MMC_BUS_WIDTH_1;

	ret = mmc_switch(sdcard,
			MMC_EXT_CSD_ACCESS_WRITE_BYTE,
			EXT_CSD_BYTE_BUS_WIDTH,
			busw);
	if (ret)
		return ret;

	ret = at91_mci_set_bus_width(buswidth);
	if (ret)
		return ret;

	return 0;
}

static int mmc_detect_buswidth(struct sd_card *sdcard)
{
	unsigned char testdata_8bit[8] = { 0x55, 0xaa, 0, 0, 0, 0, 0, 0 };
	unsigned char testdata_4bit[4] = { 0x5a, 0, 0, 0 };
	unsigned char data_r[8];
	unsigned char *pdata_w;

	unsigned char buswidths[] = {8, 4};
	unsigned int busw;
	unsigned int len;
	unsigned int i, j;
	int result;
	int ret;

	for (i = 0; i < ARRAY_SIZE(buswidths); i++) {
		result = 0;

		busw = buswidths[i];
		if (busw == 8) {
			pdata_w = testdata_8bit;
			len = 2;
		} else {
			pdata_w = testdata_4bit;
			len = 1;
		}

		ret = mmc_bus_width_select(sdcard, busw);
		if (ret)
			return ret;

		ret = mmc_send_bus_test_w(sdcard, busw, pdata_w);
		if (ret)
			return ret;

		ret = mmc_send_bus_test_r(sdcard, busw, data_r);
		if (ret)
			return ret;

		for (j = 0; j < len; j++) {
			if ((pdata_w[j] ^ data_r[j]) != 0xff) {
				result = 1;
				break;
			}
		}

		if (!result) {
			dbg_log(1, "MMC: %d-bit bus width detected\n\r", busw);
			break;
		}
	}

	return 0;

}
#endif /* #ifdef CONFIG_MMC_SUPPORT */

/*-----------------------------------------------------------------*/

/*
 * Refer to Physical Layer Specification Version 3.1
 * Figure 4-1: SD Memory Card State Diagram (card identification mode)
 * Figure 4-2: Card Initialization and Indentification Flow (SD mode)
 */
static int sdcard_identification(struct sd_card *sdcard)
{
	unsigned int bl_len_shift;
	int ret;

	udelay(3000);

	ret = sd_card_reset(sdcard);
	if (ret)
		return ret;

	udelay(2000);

#ifdef CONFIG_MMC_SUPPORT
	ret = mmc_verify_operating_condition(sdcard);
	if (ret == 0) {
		sdcard->card_type = CARD_TYPE_MMC;

	} else if (ret == ERROR_TIMEOUT) {
#endif
		/*
		 * SEND_IF_COND (CMD8) is used to verify SD Memory Card
		 * interface operating condition.
		 * The card checks the validity of operating condition
		 * by analyzing the argument of CMD8 and
		 * the host checks the validity by analyzing the response
		 * of CMD8.
		 * CMD8 is defined in the Physical Layer Specification
		 * Version2.00.
		 * It is mandatory to issue CMD8 prior to first ACMD41
		 * to initialize SDHC or SDXC Card.
		 */
		ret = sd_verify_operating_condition(sdcard);
		if (ret == 0) {
			/* Ver 2.00 or later SD Memory Card */
			ret = sd_check_operational_condition(sdcard, 1);
			if (ret == ERROR_UNUSABLE_CARD) {
				dbg_log(1, "Unusable Card\n\r");
				return -1;
			} else if (ret)
				return ret;
		} else if (ret == ERROR_TIMEOUT) {
			/*
			 * No response
			 * V2.00 or later SD Memory (voltage mismatch)
			 * or Ver1.x SD Memory Card
			 * not SD Memory Card
			 */
			/* AACMD41 with HCS = 0 */
			ret = sd_check_operational_condition(sdcard, 0);
			if (ret == ERROR_UNUSABLE_CARD) {
				dbg_log(1, "Unusable Card\n\r");
				return -1;
			} else if (ret)
				return ret;
		}

		sdcard->card_type = CARD_TYPE_SD;

#ifdef CONFIG_MMC_SUPPORT
	} else if (ret == ERROR_UNUSABLE_CARD) {
		/*
		 * Non-compatible voltage range
		 * or checkpattern not correct
		 */
		dbg_log(1, "Unusable Card\n\r");
		return -1;
	} else
		return ret;
#endif

	sdcard->highcapacity_card = (sdcard->reg->ocr & OCR_HCR_CCS) ? 1 : 0;

	if (sdcard->highcapacity_card) {
		if (sdcard->card_type == CARD_TYPE_SD)
			dbg_log(1, "SD: High or Extended " \
					"Capacity SD Card\n\r");
	} else {
		if (sdcard->card_type == CARD_TYPE_SD)
			dbg_log(1, "SD: Standard Capacity "
					"SD Card\n\r");
	}

	/*
	 * Card that is unidentified (which is in Ready State)
	 * sends its CID number
	 */
	ret = sd_card_id_number(sdcard);
	if (ret)
		return ret;

	/* Asks the card to pubish a new relative card address (RCA) */
	ret = sd_relative_card_address(sdcard);
	if (ret)
		return ret;

	/*
	 * The host issues SEND_CSD(CMD9) to obtain
	 * the Card Specific Data (CSD Register),
	 * e.g. block length, card storage capacity, etc
	 */
	ret = sd_read_card_specific_data(sdcard);
	if (ret)
		return ret;

	bl_len_shift = (sdcard->reg->csd[1] >> 16) & 0x0f;
	sdcard->read_bl_len = 1 << bl_len_shift;
	if (sdcard->read_bl_len > DEFAULT_SD_BLOCK_LEN)
		sdcard->read_bl_len = DEFAULT_SD_BLOCK_LEN;

	return 0;
}

static int sd_initialization(struct sd_card *sdcard)
{
	int ret;

	/*
	 * CMD7 is used to select one card and put it into
	 * the Transfer State
	 */
	ret = sd_enter_transfer_state(sdcard);
	if (ret)
		return ret;

	/*
	 * In Transfer State, send SEND_SCR(ACMD51)
	 * to read the SD Configuration Register (SCR)
	 */
	ret = sd_read_card_configuration(sdcard);
	if (ret)
		return ret;

	sdcard->bus_width_support = (sdcard->reg->scr[0] >> 16) & 0x0f;

#ifdef CONFIG_SDCARD_HS
	unsigned int version;
	version = (sdcard->reg->scr[0] >> 24) & 0x0f;
	if (version == 0) {
		sdcard->sd_spec_version = SD_VERSION_1_0;
		dbg_log(1, "SD: Specification Version 1.0 " \
						"and Version 1.01\n\r");
	} else if (version == 1) {
		sdcard->sd_spec_version = SD_VERSION_1_10;
		dbg_log(1, "SD: Specification Version 1.10\n\r");
	} else if (version == 2) {
		if ((sdcard->reg->scr[0] >> 15) & 0x01) {
			sdcard->sd_spec_version = SD_VERSION_3;
			dbg_log(1, "SD: Specification Version 3.0X\n\r");
		} else {
			sdcard->sd_spec_version = SD_VERSION_2;
			dbg_log(1, "SD: Specification Version 2.00\n\r");
		}
	} else {
		sdcard->sd_spec_version = SD_VERSION_1_0;
		dbg_log(1, "SD: Specification Version 1.0" \
						"and Version 1.01\n\r");
	}

	/*
	 * Try to swich to high speed function of Access Mode
	 * CMD6 is valid under the "Transfer Statr"
	 * It is mandatory for an SD memory card of Version 1.10 and higher
	 * to support Switch Function
	 */
	if (sdcard->highspeed_host) {
		if (sdcard->sd_spec_version != SD_VERSION_1_0) {
			ret = sd_switch_func_high_speed(sdcard);
			if (ret)
				return ret;
		}
	}
	if (sdcard->highspeed_card)
		at91_mci_set_clock(50000000);
	else
#endif /* #ifdef CONFIG_SDCARD_HS */

		at91_mci_set_clock(25000000);

	/* Change the bus mode */
	ret = sd_card_set_bus_width(sdcard);
	if (ret)
		return ret;

	return 0;
}

#ifdef CONFIG_MMC_SUPPORT
static int mmc_initialization(struct sd_card *sdcard)
{
	unsigned int version;
	int ret;

	version = (sdcard->reg->csd[0] >> 26) & 0xf;
	if (version == 0) {
		sdcard->sd_spec_version = MMC_VERSION_1_2;
		dbg_log(1, "MMC: Specification Version 1.2\n\r");
	} else if (version == 1) {
		sdcard->sd_spec_version = MMC_VERSION_1_4;
		dbg_log(1, "MM: Specification Version 1.4\n\r");
	} else if (version == 2) {
		sdcard->sd_spec_version = MMC_VERSION_2_2;
		dbg_log(1, "MMC: Specification Version 2.2\n\r");
	} else if (version == 3) {
		sdcard->sd_spec_version = MMC_VERSION_3;
		dbg_log(1, "MMC: Specification Version 3.0\n\r");
	} else if (version == 4) {
		sdcard->sd_spec_version = MMC_VERSION_4;
		dbg_log(1, "MMC: Specification Version 4.1 - 4.2\n\r");
	} else {
		sdcard->sd_spec_version = MMC_VERSION_1_2;
		dbg_log(1, "MMC: Specification Version 1.2\n\r");
	}

	/*
	 * CMD7 is used to select one card and put it into
	 * the Transfer State
	 */
	ret = sd_enter_transfer_state(sdcard);
	if (ret)
		return ret;

	if (sdcard->sd_spec_version >= MMC_VERSION_4) {
		ret = mmc_detect_buswidth(sdcard);
		if (ret)
			return ret;
	}

	/*
	 * After the host verifies that the card complies with
	 * version 4.0, or higher, of this standard, it has to
	 * enable the high speed mode timing in the card,
	 * before changing the clock frequency to a frequency
	 * higher than 20MHz
	 */
	if (sdcard->highspeed_host) {
		if (sdcard->sd_spec_version >= MMC_VERSION_4) {
			ret = mmc_switch_high_speed(sdcard);
			if (ret)
				return ret;
		}
	}

	if (sdcard->highspeed_card == 1)
		at91_mci_set_clock(52000000);
	else
		at91_mci_set_clock(26000000);

	return 0;
}
#endif /* #ifdef CONFIG_MMC_SUPPORT */

static void init_sdcard_struct(struct sd_card *sdcard)
{
	memset((char *)sdcard, 0, sizeof(struct sd_card));
	memset((char *)&sdcard_register, 0, sizeof(struct sdcard_register));
	memset((char *)&sdcard_command, 0, sizeof(struct sd_command));

	sdcard->reg = &sdcard_register;
	sdcard->command = &sdcard_command;

	sdcard->votage_host_support = SD_OCR_VDD_32_33 | SD_OCR_VDD_33_34;

#ifdef CONFIG_SDCARD_HS
	sdcard->highspeed_host = 1;
#endif
}

/*--------------------------------------------------------------------------*/

int sdcard_initialize(void)
{
	struct sd_card *sdcard = &atmel_sdcard;
	int ret;

	ret = at91_mci_init(CONFIG_SYS_DEFAULT_CLK, DEFAULT_SD_BLOCK_LEN);
	if (ret)
		return ret;

	init_sdcard_struct(sdcard);

	/* Card Indentification Mode */
	ret = sdcard_identification(sdcard);
	if (ret)
		return ret;

	if (sdcard->card_type == CARD_TYPE_SD)
		ret = sd_initialization(sdcard);
#ifdef CONFIG_MMC_SUPPORT
	else
		ret = mmc_initialization(sdcard);
#endif
	if (ret)
		return ret;

	return 0;
}

/*------------------------------------------------------------------- */

static int sdcard_set_block_len(struct sd_card *sdcard,
					unsigned int block_len)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SET_BLOCKLEN;
	command->argu = block_len;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

static int sdcard_stop_transmission(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int timeout = 1000;
	int ret;

	command->cmd = SD_CMD_STOP_TRANSMISSION;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	sd_send_status(sdcard, timeout);

	return 0;
}

static int sdcard_read_multi_blocks(struct sd_card *sdcard,
				void *buf,
				unsigned int start,
				unsigned int block_count)
{
	unsigned int block_len = sdcard->read_bl_len;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_READ_MULTIPLE_BLOCK;
	command->argu = (sdcard->highcapacity_card) ? start : start * block_len;

	ret = sd_send_command(command);
	if (ret)
		return 0;

	ret = at91_mci_read_blocks(buf, block_count, block_len);
	if (ret)
		return 0;

	return block_count;
}

static int sdcard_read_single_block(struct sd_card *sdcard,
				void *buf,
				unsigned int start)
{
	unsigned int block_len = sdcard->read_bl_len;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_READ_SINGLE_BLOCK;
	command->argu = (sdcard->highcapacity_card) ? start : start * block_len;

	ret = sd_send_command(command);
	if (ret)
		return 0;

	ret = at91_mci_read_block_data(buf, block_len, block_len);
	if (ret)
		return 0;

	return 1;
}

#define SUPPORT_MAX_BLOCKS	65535
unsigned int sdcard_block_read(unsigned int start,
				unsigned int block_count,
				void *buf)
{
	struct sd_card *sdcard = &atmel_sdcard;
	unsigned int blocks_todo = block_count;
	unsigned int blocks;
	unsigned int block_len = sdcard->read_bl_len;
	unsigned int blocks_read;
	int ret;

	/*
	 * Refer to the at91sam9g20 datasheet:
	 * Figure 35-10. Read Function Flow Diagram
	*/

	/* Send SET_BLOCKLEN command */
	ret = sdcard_set_block_len(sdcard, block_len);
	if (ret)
		return 0;

	for (blocks_todo = block_count; blocks_todo > 0; ) {
		blocks = (blocks_todo > SUPPORT_MAX_BLOCKS) ?
					SUPPORT_MAX_BLOCKS : blocks_todo;

		/*
		 * Set the block length (in bytes)
		 * Set the block count
		 */
		at91_mci_set_blkr(block_count, block_len);

		if (blocks > 1) {
			/*
			 * CMD18 (READ_MULTIPLE_BLOCK) starts
			 * a transfer of several consecutive blocks.
			 * Blocks will be continuously transferred
			 * until a STOP_TRANSMISSION command (CMD12) is issued
			 * The data transfer will terminate and
			 * the card will return to the Transfer state
			 */
			blocks_read = sdcard_read_multi_blocks(sdcard,
							buf, start, blocks);

			ret = sdcard_stop_transmission(sdcard);
			if (ret)
				return ret;
		} else {
			/*
			 * CMD17 (READ_SINGLE_BLOCK) initiates a block read
			 * and after completing the transfer,
			 * the card returns to the Transfer State.
			 */
			blocks_read = sdcard_read_single_block(sdcard,
							buf, start);
		}

		if (blocks_read != blocks)
			return 0;

		blocks_todo -= blocks;
		start += blocks;
		buf += blocks * block_len;
	}

	return block_count;
}
