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
		.cmdreg		= (17 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ
					| AT91C_MCI_TRTYP_SINGLE),
	},
	/* CMD18 */
	{
		.cmd		= SD_CMD_READ_MULTIPLE_BLOCK,
		.cmdreg		= (18 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ
					| AT91C_MCI_TRTYP_MULTIPLE),
	},
	/* CMD55 */
	{
		.cmd		= SD_CMD_APP_CMD,
		.cmdreg		= (55 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* ACMD6 */
	{
		.cmd		= SD_CMD_APP_SET_BUS_WIDTH,
		.cmdreg		= (6 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD16 */
	{
		.cmd		= SD_CMD_SET_BLOCKLEN,
		.cmdreg		= (16 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD12 */
	{
		.cmd		= SD_CMD_STOP_TRANSMISSION,
		.cmdreg		= (12 | AT91C_MCI_RSPTYP_R1B
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD13 */
	{
		.cmd		= SD_CMD_SEND_STATUS,
		.cmdreg		= (13 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD0 */
	{
		.cmd		= SD_CMD_GO_IDLE_STATE,
		.cmdreg		= 0,
		.error_check	= 0,
	},
	/* CMD2 */
	{
		.cmd		= SD_CMD_ALL_SEND_CID,
		.cmdreg		= (2 | AT91C_MCI_RSPTYP_136
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD3 */
	{
		.cmd		= SD_CMD_SEND_RELATIVE_ADDR,
		.cmdreg		= (3 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
#ifdef CONFIG_SDCARD_HS
	/* CMD6 */
	{
		.cmd		= SD_CMD_SWITCH_FUN,
		.cmdreg		= (6 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
	},
#endif
	/* CMD7 */
	{
		.cmd		= SD_CMD_SELECT_CARD,
		.cmdreg		= (7 | AT91C_MCI_RSPTYP_R1B
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD8 */
	{
		.cmd		= SD_CMD_SEND_IF_COND,
		.cmdreg		= (8 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD9 */
	{
		.cmd		= SD_CMD_SEND_CSD,
		.cmdreg		= (9 | AT91C_MCI_RSPTYP_136
					| AT91C_MCI_MAXLAT_64),
	},
	/* CMD10 */
	{
		.cmd		= SD_CMD_SEND_CID,
		.cmdreg		= (10 | AT91C_MCI_RSPTYP_136
					| AT91C_MCI_MAXLAT_64),
	},
	/* ACMD41 */
	{
		.cmd		= SD_CMD_APP_SD_SEND_OP_COND,
		.cmdreg		= (41 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* ACMD51 */
	{
		.cmd		= SD_CMD_APP_SEND_SCR,
		.cmdreg		= (51 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
	},
#ifdef CONFIG_MMC_SUPPORT
	/* MMC CMD1 */
	{
		.cmd		= MMC_CMD_SEND_OP_COND,
		.cmdreg		= (1 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64),
	},
	/* MMC CMD6 */
	{
		.cmd		= MMC_CMD_SWITCH_FUN,
		.cmdreg		= (6 | AT91C_MCI_RSPTYP_R1B
					| AT91C_MCI_MAXLAT_64),
	},
	/* MMC CMD8 */
	{
		.cmd		= MMC_CMD_SEND_EXT_CSD,
		.cmdreg		= (8 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
	},
	/* MMC CMD14 */
	{
		.cmd		= MMC_CMD_BUSTEST_R,
		.cmdreg		= (14 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_READ),
	},
	/* MMC CMD19 */
	{
		.cmd		= MMC_CMD_BUSTEST_W,
		.cmdreg		= (19 | AT91C_MCI_RSPTYP_48
					| AT91C_MCI_MAXLAT_64
					| AT91C_MCI_TRCMD_START
					| AT91C_MCI_TRDIR_WRITE),
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

	command->cmdreg = sd_command_table[i].cmdreg;

	if (command->cmd == 0)
		command->error_check = 0;
	else {
		command->error_check = (AT91C_MCI_RINDE
					| AT91C_MCI_RDIRE
					| AT91C_MCI_RENDE);

		if ((command->cmd != SD_CMD_APP_SD_SEND_OP_COND)
			&& (command->cmd != MMC_CMD_SEND_OP_COND))
			command->error_check |= AT91C_MCI_RCRCE;
	}

	command->resp = response;

	return 0;
}

/*
 * Refer to the at91sam9g20 datasheet:
 * Figure 35-9: Command/Response Functional Flow Diagram
 */
static int sd_send_command(struct sd_command *command)
{
	unsigned int status;
	unsigned int *response = command->resp;
	int ret;

	ret = init_sd_command(command);
	if (ret)
		return ret;

	/* Set the Command Argument Register */
	mci_writel(MCI_ARGR, command->argu);
	/* Set the Command Register */
	mci_writel(MCI_CMDR, command->cmdreg);

	/* Wait for the command ready status flag*/
	do {
		status = mci_readl(MCI_SR);
	} while (!(status & AT91C_MCI_CMDRDY));

	/* Check error bits in the status register */
	if (status & AT91C_MCI_RTOE) {
		dbg_log(1, "Cmd: %d Response Time-out\n\r",
				command->cmd & (~(SD_APP_CMD | MMC_CMD)));
		return ERROR_TIMEOUT;
	}

	if (status & command->error_check) {
		dbg_log(1, "Cmd: %d, error check, status: %d\n\r", \
			command->cmd & (~(SD_APP_CMD | MMC_CMD)), status);
		return ERROR_COMM;
	}

	/*  Read response */
	*response++ = mci_readl(MCI_RSPR);
	*response++ = mci_readl(MCI_RSPR1);
	*response++ = mci_readl(MCI_RSPR2);
	*response++ = mci_readl(MCI_RSPR3);

	return 0;
}

static int sd_cmd_go_idle_state(struct sd_card *sdcard)
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

static int sd_cmd_send_if_cond(struct sd_card *sdcard)
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

static int sd_cmd_send_app_cmd(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_CMD;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

/* Host Capacity Support / Card Capacity Status */
#define OCR_HCR_CCS		(0x01 << 30)
#define OCR_BUSY_STATUS		(0x01 << 31)
static int sd_cmd_app_sd_send_op_cmd(struct sd_card *sdcard,
				unsigned int capacity_support,
				unsigned int *reponse)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_SD_SEND_OP_COND;
	command->argu = sdcard->votage_host_support
				& OCR_VOLTAGE_27_36_MASK;
	if (capacity_support)
		command->argu |= OCR_HCR_CCS;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	*reponse = command->resp[0];

	return 0;
}

static int sd_check_operational_condition(struct sd_card *sdcard,
			unsigned int capacity_support)
{
	unsigned int response = 0;
	unsigned int retries = 1000;
	unsigned int i;
	int ret;

	/*
	 * The host repeatedly issues ACMD41 for at least 1 second
	 * or until the busy bit are set to 1.
	 */
	for (i = 0; i < retries; i++) {
		ret = sd_cmd_send_app_cmd(sdcard);
		if (ret)
			return ret;

		ret = sd_cmd_app_sd_send_op_cmd(sdcard,
				capacity_support, &response);
		if (ret)
			return ret;

		if (response & OCR_BUSY_STATUS)
			break;

		udelay(1000);
	};

	if (i == retries)
		return ERROR_UNUSABLE_CARD;

	sdcard->reg->ocr = response;

	return 0;
}

static int sd_cmd_all_send_cid(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int i;
	int ret;

	command->cmd = SD_CMD_ALL_SEND_CID;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	for (i = 0; i < 4; i++)
		sdcard->reg->cid[i] = command->resp[i];

	return 0;
}

static int sd_cmd_send_relative_addr(struct sd_card *sdcard)
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

static int sd_cmd_send_status(struct sd_card *sdcard, unsigned int retries)
{
	struct sd_command *command = sdcard->command;
	unsigned int i;
	int ret;

	command->cmd = SD_CMD_SEND_STATUS;
	command->argu = sdcard->reg->rca << 16;

	for (i = 0; i < retries; i++) {
		ret = sd_send_command(command);
		if (ret)
			return ret;

		if ((command->resp[0] >> 8) & 0x01)
			break;

		udelay(1000);
	};

	if (i == retries) {
		dbg_log(1, "Timeout, wait for card ready\n\r");
		return ERROR_TIMEOUT;
	}

	return 0;
}

static int sd_cmd_select_card(struct sd_card *sdcard)
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

static int sd_cmd_send_csd(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int i;
	int ret;

	command->cmd = SD_CMD_SEND_CSD;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	for (i = 0; i < 4; i++)
		sdcard->reg->csd[i] = *command->resp++;

	return 0;
}

static int sd_cmd_app_send_scr(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int data[2];
	unsigned int bytes_to_read = 8;
	unsigned int block_len = DEFAULT_SD_BLOCK_LEN;
	unsigned int i;
	int ret;

	ret = sd_cmd_send_app_cmd(sdcard);
	if (ret)
		return ret;

	command->cmd = SD_CMD_APP_SEND_SCR;
	command->argu = sdcard->reg->rca << 16;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	ret = at91_mci_read_block_data(data, bytes_to_read, block_len);
	if (ret)
		return ret;

	for (i = 0; i < 2; i++)
		sdcard->reg->scr[i] = swap_uint32(data[i]);

	return 0;
}

static int sd_cmd_app_set_bus_width(struct sd_card *sdcard,
				unsigned int bus_width)
{
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_SET_BUS_WIDTH;
	command->argu = (bus_width == 4) ? 0x02 : 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	return 0;
}

static int sd_set_bus_width(struct sd_card *sdcard,
				unsigned int bus_width)
{
	int ret;

	ret = sd_cmd_send_app_cmd(sdcard);
	if (ret)
		return ret;

	ret = sd_cmd_app_set_bus_width(sdcard, bus_width);
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

static int sd_cmd_switch_fun(struct sd_card *sdcard,
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
	unsigned int retries = 6;
	unsigned int i;
	int ret;

	for (i = 0; i < retries; i++) {
		/* Mode 0 operation: check function */
		ret = sd_cmd_switch_fun(sdcard,
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
		version = swap_uint32(switch_func_status[4]);
		if (((version >> 16) & 0xff) == 0x00)
			break;

		/* Check Busy Status of function */
		status = swap_uint32(switch_func_status[7]);
		if (!((status >> 17) & 0x01))
			break;
	};

	if (i == retries)
		return -1;

	/* Check function supported */
	status = swap_uint32(switch_func_status[3]);
	*support = ((status >> 17) & 0x01) ? 1 : 0;

	return 0;
}

static int sd_switch_func_high_speed(struct sd_card *sdcard)
{
	unsigned int switch_func_status[16];
	unsigned int status;
	unsigned char support = 0;
	int ret;

	ret = switch_check_hs_busy_status_supported(sdcard, &support);
	if (ret)
		return ret;

	if (!support) {
		dbg_log(1, "SD: Not support hs function switch\n\r");
		return 0;
	}

	/* Mode 1 operation: set functioin */
	ret = sd_cmd_switch_fun(sdcard,
				SD_SWITCH_MODE_SET,
				SD_SWITCH_GRP_ACCESS_MODE,
				SD_SWITCH_FUNC_HS_SDR25,
				switch_func_status);
	if (ret)
		return ret;

	/* Check Switched function */
	status = swap_uint32(switch_func_status[4]);
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

	ret = sd_set_bus_width(sdcard, bus_width);
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
	unsigned int retries = 1000;
	unsigned int i;
	int ret;

	/* Query the card and determine the voltage type of the card */
	ret = mmc_cmd_send_op_cond(sdcard, 0);
	if (ret)
		return ret;

	ocr = command->resp[0];

	for (i = 0; i < retries; i++) {
		ret = mmc_cmd_send_op_cond(sdcard, ocr);
		if (ret)
			return ret;

		if (command->resp[0]  & (0x01 << 31))
			break;

		udelay(1000);
	};

	if (i == retries)
		return ERROR_UNUSABLE_CARD;

	sdcard->reg->ocr = command->resp[0];

	return 0;
}

static int mmc_cmd_switch_fun(struct sd_card *sdcard,
				unsigned char access_mode,
				unsigned char index,
				unsigned char value)
{
	struct sd_command *command = sdcard->command;
	unsigned int retries = 1000;
	int ret;

	command->cmd = MMC_CMD_SWITCH_FUN;
	command->argu = (access_mode << 24)
			| (index << 16)
			| (value << 8);

	ret = sd_send_command(command);

	sd_cmd_send_status(sdcard, retries);
	if (ret)
		return ret;

	return 0;
}

static int mmc_cmd_send_ext_csd(struct sd_card *sdcard, char *ext_csd)
{
	struct sd_command *command = sdcard->command;
	unsigned int *data = (unsigned int *)ext_csd;
	unsigned int block_len = DEFAULT_SD_BLOCK_LEN;
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
	char ext_csd[DEFAULT_SD_BLOCK_LEN];
	char cardtype;
	int ret;

	ret = mmc_cmd_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;

	cardtype = ext_csd[EXT_CSD_BYTE_CARD_TYPE] & 0x03;

	ret = mmc_cmd_switch_fun(sdcard,
			MMC_EXT_CSD_ACCESS_WRITE_BYTE,
			EXT_CSD_BYTE_HS_TIMING,
			1);
	if (ret)
		return ret;

	ret = mmc_cmd_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;

	if (!ext_csd[EXT_CSD_BYTE_HS_TIMING])
		return -1;

	sdcard->highspeed_card = (cardtype & 0x02) ? 1 : 0;

	return 0;
}

static int mmc_cmd_bustest_w(struct sd_card *sdcard,
				unsigned int buswidth,
				unsigned char *data)
{
	struct sd_command *command = sdcard->command;
	unsigned int bytes_to_write;
	unsigned int block_len = DEFAULT_SD_BLOCK_LEN;
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

static int mmc_cmd_bustest_r(struct sd_card *sdcard,
				unsigned int buswidth,
				unsigned char *data)
{
	struct sd_command *command = sdcard->command;
	unsigned int bytes_to_read;
	unsigned int block_len = DEFAULT_SD_BLOCK_LEN;
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

#define MMC_BUS_WIDTH_8		2
#define MMC_BUS_WIDTH_4		1
#define MMC_BUS_WIDTH_1		0

static int mmc_bus_width_select(struct sd_card *sdcard, unsigned int buswidth)
{
	unsigned char busw;
	int ret;

	busw = (buswidth == 8) ? MMC_BUS_WIDTH_8 : MMC_BUS_WIDTH_4;

	ret = mmc_cmd_switch_fun(sdcard,
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
	unsigned char data_8bits[8] = {0x55, 0xaa, 0, 0, 0, 0, 0, 0};
	unsigned char data_4bits[4] = {0x5a, 0, 0, 0};
	unsigned char read_data[8];
	unsigned char *pdata_w;

	unsigned int busw;
	unsigned int len;
	unsigned int i;
	int ret;

	for (busw = 8, len = 2; busw != 0; busw -= 4, len--) {
		pdata_w = (busw == 8) ? data_8bits : data_4bits;

		ret = mmc_bus_width_select(sdcard, busw);
		if (ret)
			return ret;

		ret = mmc_cmd_bustest_w(sdcard, busw, pdata_w);
		if (ret)
			return ret;

		ret = mmc_cmd_bustest_r(sdcard, busw, read_data);
		if (ret)
			return ret;

		for (i = 0; i < len; i++) {
			if ((pdata_w[i] ^ read_data[i]) != 0xff)
				break;
		}

		if (i == len) {
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
	int ret;

	udelay(3000);

	ret = sd_cmd_go_idle_state(sdcard);
	if (ret)
		return ret;

	udelay(2000);

#ifdef CONFIG_MMC_SUPPORT
	ret = mmc_verify_operating_condition(sdcard);
	if (ret == 0) {
		sdcard->card_type = CARD_TYPE_MMC;

	} else if (ret == ERROR_TIMEOUT) {
#endif
		ret = sd_cmd_send_if_cond(sdcard);
		if (ret == 0) {
			/* Ver 2.00 or later SD Memory Card */
			ret = sd_check_operational_condition(sdcard, 1);
			if (ret == ERROR_UNUSABLE_CARD) {
				dbg_log(1, "Unusable Card\n\r");
				return -1;
			} else if (ret)
				return ret;
		} else if (ret == ERROR_TIMEOUT) {
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

	if (sdcard->card_type == CARD_TYPE_SD) {
		dbg_log(1, "SD: Card Capacity: ");
		if (sdcard->highcapacity_card)
			dbg_log(1, "High or Extended\n\r");
		else
			dbg_log(1, "Standard\n\r");
	}

	/*
	 * Card that is unidentified (which is in Ready State)
	 * sends its CID number
	 */
	ret = sd_cmd_all_send_cid(sdcard);
	if (ret)
		return ret;

	/* Asks the card to pubish a new relative card address (RCA) */
	ret = sd_cmd_send_relative_addr(sdcard);
	if (ret)
		return ret;

	/*
	 * The host issues SEND_CSD(CMD9) to obtain
	 * the Card Specific Data (CSD Register),
	 */
	ret = sd_cmd_send_csd(sdcard);
	if (ret)
		return ret;

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
	ret = sd_cmd_select_card(sdcard);
	if (ret)
		return ret;

	/*
	 * In Transfer State, send SEND_SCR(ACMD51)
	 * to read the SD Configuration Register (SCR)
	 */
	ret = sd_cmd_app_send_scr(sdcard);
	if (ret)
		return ret;

	sdcard->bus_width_support = (sdcard->reg->scr[0] >> 16) & 0x0f;

#ifdef CONFIG_SDCARD_HS
	unsigned int version;
	version = (sdcard->reg->scr[0] >> 24) & 0x0f;
	dbg_log(1, "SD: Specification Version ");
	if (version == 0) {
		sdcard->sd_spec_version = SD_VERSION_1_0;
		dbg_log(1, "1.0 and 1.01\n\r");
	} else if (version == 1) {
		sdcard->sd_spec_version = SD_VERSION_1_10;
		dbg_log(1, "1.10\n\r");
	} else if (version == 2) {
		if ((sdcard->reg->scr[0] >> 15) & 0x01) {
			sdcard->sd_spec_version = SD_VERSION_3;
			dbg_log(1, "3.0X\n\r");
		} else {
			sdcard->sd_spec_version = SD_VERSION_2;
			dbg_log(1, "2.00\n\r");
		}
	} else {
		sdcard->sd_spec_version = SD_VERSION_1_0;
		dbg_log(1, "1.0 and 1.01\n\r");
	}

	if (sdcard->highspeed_host) {
		if (sdcard->sd_spec_version != SD_VERSION_1_0) {
			ret = sd_switch_func_high_speed(sdcard);
			if (ret)
				return ret;
		}
	}
	if (sdcard->highspeed_card)
		/* for SAM9G25-CM by COGENT, it cann't support 50M */
		at91_mci_set_clock(40000000);
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
	dbg_log(1, "MMC: Specification Version ");
	if (version == 0) {
		sdcard->sd_spec_version = MMC_VERSION_1_2;
		dbg_log(1, "1.2\n\r");
	} else if (version == 1) {
		sdcard->sd_spec_version = MMC_VERSION_1_4;
		dbg_log(1, "1.4\n\r");
	} else if (version == 2) {
		sdcard->sd_spec_version = MMC_VERSION_2_2;
		dbg_log(1, "2.2\n\r");
	} else if (version == 3) {
		sdcard->sd_spec_version = MMC_VERSION_3;
		dbg_log(1, "3.0\n\r");
	} else if (version == 4) {
		sdcard->sd_spec_version = MMC_VERSION_4;
		dbg_log(1, "4.1 - 4.2\n\r");
	} else {
		sdcard->sd_spec_version = MMC_VERSION_1_2;
		dbg_log(1, "1.2\n\r");
	}

	/*
	 * CMD7 is used to select one card and put it into
	 * the Transfer State
	 */
	ret = sd_cmd_select_card(sdcard);
	if (ret)
		return ret;

	if (sdcard->sd_spec_version >= MMC_VERSION_4) {
		ret = mmc_detect_buswidth(sdcard);
		if (ret)
			return ret;
	}

	if (sdcard->highspeed_host) {
		if (sdcard->sd_spec_version >= MMC_VERSION_4) {
			ret = mmc_switch_high_speed(sdcard);
			if (ret)
				return ret;
		}
	}

	if (sdcard->highspeed_card)
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

static int sd_cmd_set_blocklen(struct sd_card *sdcard,
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

static int sd_cmd_stop_transmission(struct sd_card *sdcard)
{
	struct sd_command *command = sdcard->command;
	unsigned int retries = 1000;
	int ret;

	command->cmd = SD_CMD_STOP_TRANSMISSION;
	command->argu = 0;

	ret = sd_send_command(command);
	if (ret)
		return ret;

	sd_cmd_send_status(sdcard, retries);

	return 0;
}

static int sd_cmd_read_multiple_block(struct sd_card *sdcard,
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

static int sd_cmd_read_single_block(struct sd_card *sdcard,
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
	ret = sd_cmd_set_blocklen(sdcard, block_len);
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
			blocks_read = sd_cmd_read_multiple_block(sdcard,
							buf, start, blocks);

			ret = sd_cmd_stop_transmission(sdcard);
			if (ret)
				return ret;
		} else {
			blocks_read = sd_cmd_read_single_block(sdcard,
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
