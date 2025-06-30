// Copyright (C) 2024 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "string.h"
#include "mci_media.h"
#include "timer.h"
#include "atmel_mci.h"
#include "sdhc.h"
#include "debug.h"

#define DEFAULT_SD_BLOCK_LEN		512

static struct sdcard_register	sdcard_register;
static struct sdcard_sw_caps	sdcard_sw_caps;
static struct sd_command	sdcard_command;
static struct sd_data		sdcard_data;
static struct sd_card		atmel_sdcard;

static int sd_cmd_set_blocklen(struct sd_card *sdcard,
				unsigned int block_len);

static int sd_cmd_go_idle_state(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_GO_IDLE_STATE;
	command->resp_type = SD_RESP_TYPE_NO_RESP;
	command->argu = 0;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	return 0;
}

static int sd_cmd_send_if_cond(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SEND_IF_COND;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = CHECK_PATTERN;
	command->argu |= (host->caps_voltages
				& OCR_VOLTAGE_27_36_MASK) ? (0x01 << 8) : 0;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	if (((command->resp[0] & CHECK_PATTERN) != CHECK_PATTERN)
		|| (((command->resp[0] >> 8) & 0x0f) != 0x01))
		return ERROR_UNUSABLE_CARD;
	else
		return 0;
}

static int sd_cmd_set_uhs_voltage(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_VOLTAGE_SWITCH;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = 0;

	ret = host->ops->send_command(command, 0);
	return ret;
}

static int sd_cmd_send_app_cmd(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_CMD;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = sdcard->reg->rca << 16;

	ret = host->ops->send_command(command, 0);
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
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_SD_SEND_OP_COND;
	command->resp_type = SD_RESP_TYPE_R3;
	command->argu = host->caps_voltages
				& OCR_VOLTAGE_27_36_MASK;

	if (host->caps_voltages | SD_OCR_VDD_165_195)
		command->argu |= SD_OCR_S18R | SD_OCR_XPC;

	if (capacity_support)
		command->argu |= OCR_HCR_CCS;

	ret = host->ops->send_command(command, 0);
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
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	unsigned int i;
	int ret;
	unsigned int resp;

	command->cmd = SD_CMD_ALL_SEND_CID;
	command->resp_type = SD_RESP_TYPE_R2;
	command->argu = 0;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	/* we need to shift the answer with 8 bits, because
	 * the registers provide R[128:8] in RR3[23:0],
	 * RR2[31:0], RR1[31:0] and RR0[31:0]
	 */
	sdcard->reg->cid[3] = 0x000000ff;
	for (i = 0; i < 4; i++) {
		resp = command->resp[i];
		if (i < 3)
			sdcard->reg->cid[2 - i] = resp >> 24 & 0xff;
		sdcard->reg->cid[3 - i] |= resp << 8 & 0xffffff00;
	}

	return 0;
}

static int sd_cmd_send_relative_addr(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	sdcard->reg->rca = 1;

	command->cmd = SD_CMD_SEND_RELATIVE_ADDR;
	command->resp_type = SD_RESP_TYPE_R6;
	command->argu = sdcard->reg->rca << 16;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	sdcard->reg->rca = (sdcard->card_type == CARD_TYPE_SD) ?
					(command->resp[0] >> 16) & 0xffff : 1;

	return 0;
}

static int sd_cmd_send_status(struct sd_card *sdcard, unsigned int retries)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	unsigned int i;
	int ret;

	command->cmd = SD_CMD_SEND_STATUS;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = sdcard->reg->rca << 16;

	for (i = 0; i < retries; i++) {
		ret = host->ops->send_command(command, 0);
		if (ret)
			return ret;

		if ((command->resp[0] >> 8) & 0x01)
			break;

		udelay(1000);
	};

	if (i == retries) {
		dbg_info("Timeout, wait for card ready\n");
		return ERROR_TIMEOUT;
	}

	return 0;
}

static int sd_cmd_select_card(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SELECT_CARD;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = sdcard->reg->rca << 16;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	return 0;
}

static int sd_cmd_send_csd(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	unsigned int i;
	int ret;
	unsigned int resp;

	command->cmd = SD_CMD_SEND_CSD;
	command->resp_type = SD_RESP_TYPE_R2;
	command->argu = sdcard->reg->rca << 16;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	/* we need to shift the answer with 8 bits, because
	 * the registers provide R[128:8] in RR3[23:0],
	 * RR2[31:0], RR1[31:0] and RR0[31:0]
	 */
	sdcard->reg->csd[3] = 0x000000ff;
	for (i = 0; i < 4; i++) {
		resp = command->resp[i];
		if (i < 3)
			sdcard->reg->csd[2 - i] = resp >> 24 & 0xff;
		sdcard->reg->csd[3 - i] |= resp << 8 & 0xffffff00;
	}

	return 0;
}

static int sd_cmd_app_send_scr(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	unsigned int scr_data[2];
	int ret;

	ret = sd_cmd_send_app_cmd(sdcard);
	if (ret)
		return ret;

	command->cmd = SD_CMD_APP_SEND_SCR;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = sdcard->reg->rca << 16;

	data->buff = (unsigned char *)scr_data;
	data->direction = SD_DATA_DIR_RD;
	data->blocksize = 8;
	data->blocks = 1;

	ret = host->ops->send_command(command, data);
	if (ret)
		return ret;

	sdcard->reg->scr[0] = swap_uint32(scr_data[0]);
	sdcard->reg->scr[1] = swap_uint32(scr_data[1]);

	return 0;
}

static int sd_cmd_app_set_bus_width(struct sd_card *sdcard,
				unsigned int bus_width)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_APP_SET_BUS_WIDTH;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = (bus_width == 4) ? 0x02 : 0;

	ret = host->ops->send_command(command, 0);
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
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	int ret;

	command->cmd = SD_CMD_SWITCH_FUN;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = (mode << 31) | 0xffffff;
	command->argu &= ~(0xf << ((group - 1) * 4));
	command->argu |= func << ((group - 1) * 4);

	data->buff = (unsigned char *)status;
	data->direction = SD_DATA_DIR_RD;
	data->blocksize = 64;
	data->blocks = 1;

	ret = host->ops->send_command(command, data);
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


#ifdef SD_DBG_UHS
static void dump_sw_status(unsigned short *status)
{
	dbg_very_loud("max current \t%x\n\r", swap_uint16(status[0]));
	dbg_very_loud(
		"group6 bits \t%x\n\r" "group5 bits \t%x\n\r" "group4 bits \t%x\n\r"
		"group3 bits \t%x\n\r" "group2 bits \t%x\n\r" "group1 bits \t%x\n\r",
		swap_uint16(status[1]), swap_uint16(status[2]), swap_uint16(status[3]),
		swap_uint16(status[4]), swap_uint16(status[5]), swap_uint16(status[6]));
	dbg_very_loud(
		"group6 func \t%x\n\r" "group5 func \t%x\n\r" "group4 func \t%x\n\r"
		"group3 func \t%x\n\r" "group2 func \t%x\n\r" "group1 func \t%x\n\r",
		swap_uint16(status[7])>>12 & 0xF, swap_uint16(status[7])>>8 & 0xF,
		swap_uint16(status[7])>>4 & 0xF, swap_uint16(status[7]) & 0xF,
		swap_uint16(status[8])>>12 & 0xF, swap_uint16(status[8])>>8 & 0xF);
	dbg_very_loud("struct veri \t%x\n\r", swap_uint16(status[8]) & 0xFF);
	dbg_very_loud(
		"group6 busy \t%x\n\r" "group5 busy \t%x\n\r" "group4 busy \t%x\n\r"
		"group3 busy \t%x\n\r" "group2 busy \t%x\n\r" "group1 busy \t%x\n\r\n\r",
		swap_uint16(status[9]), swap_uint16(status[10]), swap_uint16(status[11]),
		swap_uint16(status[12]), swap_uint16(status[13]), swap_uint16(status[14]));
}
#endif

static int sd_read_switch(struct sd_card *sdcard)
{
	unsigned short status[32];
	unsigned int version;
	unsigned int retries = 6;
	unsigned int i;
	int ret;

	for (i = 0; i < retries; i++) {
		/* Mode 0 operation: check function */
		ret = sd_cmd_switch_fun(sdcard,
					SD_SWITCH_MODE_CHECK,
					SD_SWITCH_GRP_ACCESS_MODE,
					0xF,
					(void *)status);
		if (ret)
			return ret;

		/* Check Data Structure version
		 * 0x00 - bits 511:376 are defined
		 * 0x01 - bits 511:272 are defined
		 */
		version = swap_uint16(status[8]);
		if ((version & 0xff) == 0x00)
			break;

		/* Check Busy Status of functions in groups(1 2 3 4)
		 * Try again if any function in any group is busy
		 */
		if (!swap_uint16(status[14]) &&
			!swap_uint16(status[13]) &&
			!swap_uint16(status[12]) &&
			!swap_uint16(status[11]))
			break;
	};

	if (i == retries)
		return -1;
#ifdef SD_DBG_UHS
	dump_sw_status(status);
#endif
	if (swap_uint16(status[6]) & SD_MODE_HIGH_SPEED)
		sdcard->sw_caps->hs_max_dtr = HIGH_SPEED_MAX_DTR;
	if (sdcard->sd_spec_version == SD_VERSION_3) {
		sdcard->sw_caps->sd3_bus_mode   = swap_uint16(status[6]);
		sdcard->sw_caps->sd3_cmd_sys    = swap_uint16(status[5]);
		sdcard->sw_caps->sd3_drv_type   = swap_uint16(status[4]);
		sdcard->sw_caps->sd3_curr_limit = swap_uint16(status[3]);
	}

	return 0;
}

static int sd_switch_func_uhs(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	unsigned short status[32];
	unsigned int group_no = SD_SWITCH_GRP_ACCESS_MODE;
	unsigned int drv_type;
	unsigned int curr_limit;
	unsigned int bus_mode;
	unsigned int bus_clock;
	unsigned int result;
	int ret;

	/*
	 * Select driver strength.
	 * Type A driver is prefered,
	 * otherwise use the default Type B driver.
	 */
	if (sdcard->sw_caps->sd3_drv_type & SD_DRIVER_TYPE_A) {
		drv_type = SD_SET_DRIVER_TYPE_A;

		/* Set Card driver strength */
		ret = sd_cmd_switch_fun(sdcard,
					SD_SWITCH_MODE_SET,
					SD_SWITCH_GRP_DRV_STRENGTH,
					drv_type,
					(void *)status);
		if (ret)
			return ret;

		result = swap_uint16(status[7]) & 0xF;
		if (result != drv_type)
			return -1;
	} else {
		drv_type = SD_SET_DRIVER_TYPE_B;
	}
	/* Set Host driver strength */
	host->ops->set_uhs_driver(sdcard, drv_type);

	/*
	 * Allowed power consumption for removable cards shall be
	 * up to 1.80W, so first check 1.80W and then 1.44W,
	 * otherwise use the default 0.72W.
	 */
	if (sdcard->sw_caps->sd3_curr_limit & SD_MAX_CURRENT_500) {
		curr_limit = SD_SET_CURRENT_LIMIT_500;
	} else if (sdcard->sw_caps->sd3_curr_limit & SD_MAX_CURRENT_400) {
		curr_limit = SD_SET_CURRENT_LIMIT_400;
	} else {
		curr_limit = SD_SET_CURRENT_LIMIT_200;
	}
	/* Set Card current limit if non-default */
	if (curr_limit != SD_SET_CURRENT_LIMIT_200) {
		ret = sd_cmd_switch_fun(sdcard,
					SD_SWITCH_MODE_SET,
					SD_SWITCH_GRP_CUR_LIMIT,
					curr_limit,
					(void *)status);
		if (ret)
			return ret;

		result = swap_uint16(status[7]) >> 4 & 0xF;
		if (result != curr_limit)
			return -1;
	}

	/*
	 * The SDHC host supports all UHS-I bus speed modes,
	 * therefore select the highest speed mode supported by the SD Card.
	 */
#ifdef CONFIG_SDHC_SD_DDR200
	if (sdcard->sw_caps->sd3_cmd_sys & SD_CMD_SYS_VENDOR) {
		/* Enable DDR200 if Vendor specific flag is supported */
		bus_mode  = UHS_DDR200_BUS_SPEED;
		bus_clock = UHS_DDR200_MAX_DTR;
		group_no  = SD_SWITCH_GRP_CMD_SYS;
	} else
#endif

/* SAMA7G5 EERATA: SDR104, HS200, HS400 modes are not functional
   Using mode SDR104, HS200 or HS400 may lead to tuning issues,
   data read errors or clock switching failures. */
#ifdef CONFIG_SAMA7G5
	sdcard->sw_caps->sd3_bus_mode &= (~SD_MODE_UHS_SDR104);
#endif
	if (sdcard->sw_caps->sd3_bus_mode & SD_MODE_UHS_SDR104) {
		bus_mode  = UHS_SDR104_BUS_SPEED;
		bus_clock = UHS_SDR104_MAX_DTR;
	} else if (sdcard->sw_caps->sd3_bus_mode & SD_MODE_UHS_SDR50) {
		bus_mode  = UHS_SDR50_BUS_SPEED;
		bus_clock = UHS_SDR50_MAX_DTR;
	} else if (sdcard->sw_caps->sd3_bus_mode & SD_MODE_UHS_DDR50) {
		bus_mode  = UHS_DDR50_BUS_SPEED;
		bus_clock = UHS_DDR50_MAX_DTR;
	} else if (sdcard->sw_caps->sd3_bus_mode & SD_MODE_UHS_SDR25) {
		bus_mode  = UHS_SDR25_BUS_SPEED;
		bus_clock = UHS_SDR25_MAX_DTR;
	} else {
		bus_mode  = UHS_SDR12_BUS_SPEED;
	}
	/* Set Card bus speed mode if non-default */
	if (bus_mode != UHS_SDR12_BUS_SPEED) {
		ret = sd_cmd_switch_fun(sdcard,
					SD_SWITCH_MODE_SET,
					group_no,
					bus_mode,
					(void *)status);
		if (ret)
			return ret;
#ifdef SD_DBG_UHS
		dump_sw_status(status);
#endif
		if (group_no == SD_SWITCH_GRP_ACCESS_MODE) {
			result = swap_uint16(status[8])>>8 & 0xF;
		} else if (group_no == SD_SWITCH_GRP_CMD_SYS) {
			result = swap_uint16(status[8])>>12 & 0xF;
		}
		if (result != bus_mode)
			return -1;

		/* Set Host bus speed mode and bus clock */
		host->ops->set_uhs_mode(sdcard,
			bus_mode == UHS_DDR200_BUS_SPEED ? UHS_DDR50_BUS_SPEED : bus_mode);
		if (bus_clock > host->caps_uhs_clock)
			bus_clock = host->caps_uhs_clock;
		host->ops->set_clock(sdcard, bus_clock);

		/*
		 * Sampling clock tuning is required for UHS104 host
		 * and optional for UHS50 host.
		 */
		if (bus_mode == UHS_SDR104_BUS_SPEED) {
			ret = host->ops->exec_tuning(sdcard, SD_CMD_SEND_TUNING_BLOCK);
			if (ret) {
				dbg_info("SD: UHS tuning error\n");
				return -1;
			}
		}
	}

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
		dbg_info("SD: Not support hs function switch\n");
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

static int sd_card_set_bus_width(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	unsigned int bus_width;
	int ret;

	bus_width = (sdcard->bus_width_support & SD_SCR_BUS_WIDTH_4) ? 4 : 1;

	ret = sd_set_bus_width(sdcard, bus_width);
	if (ret)
		return ret;

	if (host->ops->set_bus_width) {
		ret = host->ops->set_bus_width(sdcard, bus_width);
		if (ret)
			return ret;
	} else {
		return -1;
	}

	return 0;
}

static bool sd_card_using_v18(struct sd_card *sdcard)
{
	/*
	 * According to the SD spec., the Bus Speed Mode (function group 1) bits
	 * 2 to 4 are zero if the card is initialized at 3.3V signal level. Thus
	 * they can be used to determine if the card has already switched to
	 * 1.8V signaling.
	 */
	return sdcard->sw_caps->sd3_bus_mode &
	       (SD_MODE_UHS_SDR50 | SD_MODE_UHS_SDR104 | SD_MODE_UHS_DDR50);
}

/*-----------------------------------------------------------------*/
#define OCR_VOLTAGE_WIN_27_36	0x00FF8000
#define OCR_ACCESS_MODE		0x60000000

#define OCR_ACCESS_MODE_BYTE	(0x00 << 30)
#define OCR_ACCESS_MODE_SECTOR	(0x01 << 30)

static int mmc_cmd_send_op_cond(struct sd_card *sdcard,
				unsigned int ocr)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = MMC_CMD_SEND_OP_COND;
	command->resp_type = SD_RESP_TYPE_R3;
	command->argu = (ocr & OCR_VOLTAGE_WIN_27_36)
			| (ocr & OCR_ACCESS_MODE);

	ret = host->ops->send_command(command, 0);
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

	dbg_very_loud("mmc_verify_operating_condition\n");

	/* Query the card and determine the voltage type of the card */
	ret = mmc_cmd_send_op_cond(sdcard, 0);
	if (ret)
		return ret;

	ocr = command->resp[0] | OCR_ACCESS_MODE_SECTOR;

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

	dbg_very_loud("mmc_verify_operating_condition success OCR = %x\n",
			sdcard->reg->ocr);
	return 0;
}

static int mmc_cmd_switch_fun(struct sd_card *sdcard,
				unsigned char access_mode,
				unsigned char index,
				unsigned char value)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	unsigned int retries = 1000;
	int ret;

	command->cmd = MMC_CMD_SWITCH_FUN;
	command->resp_type = SD_RESP_TYPE_R1B;
	command->argu = (access_mode << 24)
			| (index << 16)
			| (value << 8);

	ret = host->ops->send_command(command, 0);

	sd_cmd_send_status(sdcard, retries);
	if (ret)
		return ret;

	return 0;
}

static int mmc_cmd_send_ext_csd(struct sd_card *sdcard, char *ext_csd)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	unsigned short block_len = DEFAULT_SD_BLOCK_LEN;
	int ret;

	command->cmd = MMC_CMD_SEND_EXT_CSD;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = 0;

	data->buff = (unsigned char *)ext_csd;
	data->direction = SD_DATA_DIR_RD;
	data->blocksize = block_len;
	data->blocks = 1;

	ret = host->ops->send_command(command, data);
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

static int mmc_card_identify(struct sd_card *sdcard)
{
	char ext_csd[DEFAULT_SD_BLOCK_LEN];
	char cardtype;
	int ret;

	ret = mmc_cmd_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;

	cardtype = ext_csd[EXT_CSD_BYTE_CARD_TYPE];

	switch(ext_csd[EXT_CSD_BYTE_EXT_CSD_REV]) {
	case 0:
		dbg_printf("MMC: v4.0 detected\n");
		break;
	case 1:
		dbg_printf("MMC: v4.1 detected\n");
		break;
	case 2:
		dbg_printf("MMC: v4.2 detected\n");
		break;
	case 3:
		dbg_printf("MMC: v4.3 detected\n");
		break;
	case 4:
		dbg_printf("MMC: v4.4 detected\n");
		break;
	case 5:
		dbg_printf("MMC: v4.41 detected\n");
		break;
	case 6:
		dbg_printf("MMC: v4.5/4.51 detected\n");
		break;
	case 7:
		dbg_printf("MMC: v5.0/5.01 detected\n");
		break;
	case 8:
		dbg_printf("MMC: v5.1 detected\n");
		break;
	default:
		dbg_printf("MMC: unknown revision\n");
	};

	sdcard->highspeed_card = !!(cardtype & 0x02);

/* SAMA7G5 EERATA: SDR104, HS200, HS400 modes are not functional
   Using mode SDR104, HS200 or HS400 may lead to tuning issues,
   data read errors or clock switching failures. */
#ifdef CONFIG_SAMA7D65
	sdcard->hs200speed_card = !!(cardtype & 0x10);
	sdcard->hs400speed_card = !!(cardtype & 0x40);
#endif
	sdcard->ddr_support = !!(cardtype & 0x04);

	if (sdcard->highspeed_card)
		dbg_printf("MMC: highspeed supported\n");
	if (sdcard->ddr_support)
		dbg_printf("MMC: Dual Data Rate supported\n");

	return 0;
}


static int _mmc_switch_timing(struct sd_card *sdcard, int timing)
{
	int ret;

	if (timing > 3)
		return -1;

	ret = mmc_cmd_switch_fun(sdcard,
			MMC_EXT_CSD_ACCESS_WRITE_BYTE,
			EXT_CSD_BYTE_HS_TIMING,
			timing);
	if (ret)
		return ret;

	return 0;
}

static int mmc_switch_high_speed(struct sd_card *sdcard)
{
	char ext_csd[DEFAULT_SD_BLOCK_LEN];
	int ret;

	ret = _mmc_switch_timing(sdcard, 1);
	if (ret)
		return ret;
	ret = mmc_cmd_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;

	if (!ext_csd[EXT_CSD_BYTE_HS_TIMING])
		return -1;

	return 0;
}

static int mmc_switch_hs200(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	char ext_csd[DEFAULT_SD_BLOCK_LEN];
	int ret;

	ret = _mmc_switch_timing(sdcard, 2);
	if (ret) {
		dbg_info("mmc_switch_hs200 failed \n");
		return ret;
	}

	if (host->ops->set_hs200)
		host->ops->set_hs200(sdcard);

	ret = mmc_cmd_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;
	if (ext_csd[EXT_CSD_BYTE_HS_TIMING] != 2)
		return 1;
	return 0;
}

static int mmc_switch_hs400(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	char ext_csd[DEFAULT_SD_BLOCK_LEN];
	int ret;

	ret =_mmc_switch_timing(sdcard, 3);
	if (ret) {
		dbg_info("mmc_switch_hs400 failed \n");
		return ret;
	}
	if (host->ops->set_hs400)
		host->ops->set_hs400(sdcard);
	ret = mmc_cmd_send_ext_csd(sdcard, ext_csd);
	if (ret)
		return ret;
	if (ext_csd[EXT_CSD_BYTE_HS_TIMING] != 3)
		return 1;
	return 0;
}

static int mmc_cmd_bustest_w(struct sd_card *sdcard,
				unsigned int buswidth,
				unsigned char *buffer)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	unsigned short bytes_to_write;
	int ret;

	bytes_to_write = (buswidth == 8) ? 8 : 4;

	command->cmd = MMC_CMD_BUSTEST_W;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = 0;

	data->buff = buffer;
	data->direction = SD_DATA_DIR_WR;
	data->blocksize = bytes_to_write;
	data->blocks = 1;

	ret = host->ops->send_command(command, data);
	if (ret)
		return ret;

	return 0;
}

static int mmc_cmd_bustest_r(struct sd_card *sdcard,
				unsigned int buswidth,
				unsigned char *buffer)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	unsigned short bytes_to_read;
	int ret;

	bytes_to_read = (buswidth == 8) ? 8 : 4;

	command->cmd = MMC_CMD_BUSTEST_R;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = 0;

	data->buff = buffer;
	data->direction = SD_DATA_DIR_RD;
	data->blocksize = bytes_to_read;
	data->blocks = 1;

	ret = host->ops->send_command(command, data);
	if (ret)
		return ret;

	return 0;
}

#define MMC_BUS_WIDTH_8_DDR	6
#define MMC_BUS_WIDTH_4_DDR	5
#define MMC_BUS_WIDTH_8		2
#define MMC_BUS_WIDTH_4		1
#define MMC_BUS_WIDTH_1		0

static int mmc_bus_width_select(struct sd_card *sdcard, unsigned int buswidth,
				int ddr)
{
	struct sd_host *host = sdcard->host;
	unsigned char busw = MMC_BUS_WIDTH_1;
	int ret;

	if (buswidth == 8 || buswidth == 4) {
		if (!ddr)
			busw = (buswidth == 8) ? MMC_BUS_WIDTH_8 : MMC_BUS_WIDTH_4;
		else
			busw = (buswidth == 8) ? MMC_BUS_WIDTH_8_DDR : MMC_BUS_WIDTH_4_DDR;
	}

	ret = mmc_cmd_switch_fun(sdcard,
			MMC_EXT_CSD_ACCESS_WRITE_BYTE,
			EXT_CSD_BYTE_BUS_WIDTH,
			busw);
	if (ret)
		return ret;

	if (host->ops->set_bus_width) {
		ret = host->ops->set_bus_width(sdcard, buswidth);
		if (ret)
			return ret;
	}

	sd_cmd_send_status(sdcard, 1000);
	if (ret)
		return ret;

	if (ddr && host->ops->set_ddr) {
		ret = host->ops->set_ddr(sdcard);
		if (ret)
			return ret;
	}

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

	console_printf("MMC: detecting buswidth...\n");

	for (busw = 8, len = 2; busw != 0; busw -= 4, len--) {
		pdata_w = (busw == 8) ? data_8bits : data_4bits;

		ret = mmc_bus_width_select(sdcard, busw, 0);
		if (ret)
			continue;

		ret = mmc_cmd_bustest_w(sdcard, busw, pdata_w);
		if (ret)
			continue;

		ret = mmc_cmd_bustest_r(sdcard, busw, read_data);
		if (ret)
			continue;

		for (i = 0; i < len; i++) {
			if ((pdata_w[i] ^ read_data[i]) != 0xff)
				break;
		}

		if (i == len) {
			dbg_info("MMC: %d-bit bus width detected\n", busw);
			break;
		}

	}

	if (!busw && !len) {
		dbg_info("MMC: falling back to 1 bit bus width\n");
		mmc_bus_width_select(sdcard, 1, 0);
	}

	return 0;
}

/*
 * Configure HS200 mode,  set the desired bus width without DDR,
 * switch to HS200 mode and set the clock to > 52Mhz and <=200MHz
 */
static int mmc_select_hs200(struct sd_card *sdcard)
{
	int ret;
	struct sd_host *host = sdcard->host;

	if (host->ops->set_1v8)
		host->ops->set_1v8(sdcard);

	/* Bustest does not work below 26 Mhz */
	if (host->ops->set_clock)
		host->ops->set_clock(sdcard, 26000000);

	ret = mmc_detect_buswidth(sdcard);
	if (ret) {
		console_printf("MMC: Bustest failed !\n");
		return ret;
	}

	ret = mmc_switch_hs200(sdcard);
	if (ret)
		return ret;

	if (host->ops->set_clock)
		host->ops->set_clock(sdcard, 200000000);

	/* Perform the Tuning Process at the HS200 target operating frequency */
	ret = host->ops->exec_tuning(sdcard, MMC_CMD_SEND_TUNING_BLOCK);
	if (ret)
		return ret;

	if (sdcard->hs400speed_card) {
		/* switch to High Speed mode and then set the clock frequency to a value not greater than 52 MHz */
		ret = mmc_switch_high_speed(sdcard);
		if (ret)
			return ret;

		/* host to downgrade to HS timing */
		if (host->ops->set_clock)
			host->ops->set_clock(sdcard, 50000000);

		/* Set BUS_WIDTH[183] to 0x06 to select the dual data rate x8 bus mode */
		ret = mmc_bus_width_select(sdcard, 8, 1);
		if (ret) {
			console_printf("MMC: select 8 bits with DDR failed !\n");
			return ret;
		}
		console_printf("MMC: switch HS400 mode\n");
		ret = mmc_switch_hs400(sdcard);
		if (ret)
			return ret;

		if (host->ops->set_clock)
			host->ops->set_clock(sdcard, 200000000);
	}
	return 0;
}

/*-----------------------------------------------------------------*/

/*
 * Refer to Physical Layer Specification Version 3.1
 * Figure 4-1: SD Memory Card State Diagram (card identification mode)
 * Figure 4-2: Card Initialization and Indentification Flow (SD mode)
 */
static int sdcard_identification(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	int timeout;
	int ret;

	udelay(3000);

	ret = sd_cmd_go_idle_state(sdcard);
	if (ret)
		return ret;

	udelay(2000);

	ret = mmc_verify_operating_condition(sdcard);
	if (ret == 0) {
		sdcard->card_type = CARD_TYPE_MMC;
		dbg_very_loud("Card type is MMC\n");

	} else if (ret == ERROR_TIMEOUT) {
		ret = sd_cmd_send_if_cond(sdcard);
		if (ret == 0) {
			/* Ver 2.00 or later SD Memory Card */
			ret = sd_check_operational_condition(sdcard, 1);
			if (ret == ERROR_UNUSABLE_CARD) {
				dbg_info("Unusable Card\n");
				return -1;
			} else if (ret)
				return ret;
		} else if (ret == ERROR_TIMEOUT) {
			ret = sd_check_operational_condition(sdcard, 0);
			if (ret == ERROR_UNUSABLE_CARD) {
				dbg_info("Unusable Card\n");
				return -1;
			} else if (ret)
				return ret;
		}

		sdcard->card_type = CARD_TYPE_SD;
	} else if (ret == ERROR_UNUSABLE_CARD) {
		/*
		 * Non-compatible voltage range
		 * or checkpattern not correct
		 */
		dbg_info("Unusable Card\n");
		return -1;
	} else
		return ret;

	sdcard->highcapacity_card = (sdcard->reg->ocr & OCR_HCR_CCS) ? 1 : 0;

	if (host->caps_uhs && (sdcard->reg->ocr & SD_ROCR_S18A)) {
		ret = sd_cmd_set_uhs_voltage(sdcard);
		if (ret) {
			dbg_info("SD: Card 1v8 voltage switch failed\n");
			return -1;
		}

		/*
		 * The card should drive cmd and dat[0:3] low immediately
		 * after the response of cmd11, but wait 1 ms to be sure
		 */
		timeout = 10;
		while (!host->ops->card_busy(sdcard) && timeout--)
			udelay(100);
		if (timeout < 0) {
			dbg_info("SD: Timeout waiting for card busy\n");
			return -1;
		}

		ret = host->ops->set_1v8(sdcard);
		if (ret) {
			dbg_info("SD: Host 1v8 voltage switch failed\n");
			return -1;
		}

		/*
		 * Stop the SD clock, and at least 5ms delay here,
		 * otherwise some SD Cards will never be ready.
		 */
		host->ops->set_clock(sdcard, 0);
		mdelay(5);
		/* Start the SD clock from SDR12 */
		host->ops->set_clock(sdcard, UHS_SDR12_MAX_DTR);
		host->ops->set_uhs_mode(sdcard, UHS_SDR12_BUS_SPEED);

		timeout = 100;
		while (host->ops->card_busy(sdcard) && timeout--)
			udelay(100);
		if (timeout < 0) {
			dbg_info("SD: Timeout waiting for card ready\n");
			return -1;
		}

		dbg_info("SD: Switched to 1v8 voltage\n");
	}

	if (sdcard->card_type == CARD_TYPE_SD) {
		dbg_info("SD: Card Capacity: ");
		if (sdcard->highcapacity_card)
			dbg_info("High or Extended\n");
		else
			dbg_info("Standard\n");
	}

	/*
	 * Card that is unidentified (which is in Ready State)
	 * sends its CID number
	 */
	ret = sd_cmd_all_send_cid(sdcard);
	if (ret) {
		dbg_very_loud("sd_cmd_all_send_cid failed\n");
		return ret;
	}

	dbg_very_loud("sd card identified with CID = %x %x %x %x\n",
			sdcard->reg->cid[0], sdcard->reg->cid[1],
			sdcard->reg->cid[2], sdcard->reg->cid[3]);

	/* Asks the card to publish a new relative card address (RCA) */
	ret = sd_cmd_send_relative_addr(sdcard);
	if (ret) {
		dbg_very_loud("sd_cmd_send_relative_addr failed\n");
		return ret;
	}

	/*
	 * The host issues SEND_CSD(CMD9) to obtain
	 * the Card Specific Data (CSD Register),
	 */
	ret = sd_cmd_send_csd(sdcard);
	if (ret) {
		dbg_very_loud("sd_cmd_send_csd failed\n");
		return ret;
	}

	sdcard->read_bl_len = DEFAULT_SD_BLOCK_LEN;

	dbg_very_loud("sdcard_identification success\n");
	return 0;
}

static int sd_initialization(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
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
	sdcard->cmd_support = sdcard->reg->scr[0] & 0x1f;

	unsigned int version;
	version = (sdcard->reg->scr[0] >> 24) & 0x0f;
	dbg_info("SD: Specification Version ");
	if (version == 0) {
		sdcard->sd_spec_version = SD_VERSION_1_0;
		dbg_info("1.0 and 1.01\n");
	} else if (version == 1) {
		sdcard->sd_spec_version = SD_VERSION_1_10;
		dbg_info("1.10\n");
	} else if (version == 2) {
		if ((sdcard->reg->scr[0] >> 15) & 0x01) {
			sdcard->sd_spec_version = SD_VERSION_3;
			dbg_info("3.0X\n");
		} else {
			sdcard->sd_spec_version = SD_VERSION_2;
			dbg_info("2.00\n");
		}
	} else {
		sdcard->sd_spec_version = SD_VERSION_1_0;
		dbg_info("1.0 and 1.01\n");
	}

	if (host->caps_uhs &&
		(sdcard->sd_spec_version == SD_VERSION_3)) {
		if (sd_read_switch(sdcard))
			return -1;
	}

	if (host->caps_uhs &&
		(sd_card_using_v18(sdcard))) {
		if (!sdcard->v1v8) {
			ret = host->ops->set_1v8(sdcard);
			if (ret) {
				dbg_info("SD: Host 1v8 voltage switch failed\n");
				return -1;
			}
			dbg_info("SD: Switched to 1v8 voltage\n");
		}

		/* Change the bus mode */
		ret = sd_card_set_bus_width(sdcard);
		if (ret)
			return ret;

		/* Select UHS-I mode */
		ret = sd_switch_func_uhs(sdcard);
		if (ret)
			return ret;
		dbg_info("SD: Switched to UHS-I mode\n");

		return 0;
	}

	if (host->caps_high_speed) {
		if (sdcard->sd_spec_version != SD_VERSION_1_0) {
			ret = sd_switch_func_high_speed(sdcard);
			if (ret)
				return ret;
		}
	}

	if (host->ops->set_clock) {
		if (sdcard->highspeed_card)
			host->ops->set_clock(sdcard, 50000000);
		else
			host->ops->set_clock(sdcard, 25000000);
	}

	/* Change the bus mode */
	ret = sd_card_set_bus_width(sdcard);
	if (ret)
		return ret;

	return 0;
}

static int mmc_initialization(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	unsigned int version;
	int ret;

	version = (sdcard->reg->csd[0] >> 26) & 0xf;
	dbg_info("MMC: Specification Version ");
	if (version == 0) {
		sdcard->sd_spec_version = MMC_VERSION_1_2;
		dbg_info("1.2\n");
	} else if (version == 1) {
		sdcard->sd_spec_version = MMC_VERSION_1_4;
		dbg_info("1.4\n");
	} else if (version == 2) {
		sdcard->sd_spec_version = MMC_VERSION_2_2;
		dbg_info("2.2\n");
	} else if (version == 3) {
		sdcard->sd_spec_version = MMC_VERSION_3;
		dbg_info("3.0\n");
	} else if (version == 4) {
		sdcard->sd_spec_version = MMC_VERSION_4;
		dbg_info("4.0 or higher\n");
	} else {
		sdcard->sd_spec_version = MMC_VERSION_1_2;
		dbg_info("1.2\n");
	}

	if (version >= 3)
		sdcard->cmd_support |= SD_SCR_CMD23_SUPPORT;

	/*
	 * CMD7 is used to select one card and put it into
	 * the Transfer State
	 */
	ret = sd_cmd_select_card(sdcard);
	if (ret)
		return ret;

	ret = sd_cmd_set_blocklen(sdcard, DEFAULT_SD_BLOCK_LEN);

        if (ret)
                return 0;

	ret = mmc_card_identify(sdcard);

	if (ret)
		return ret;

	if (sdcard->hs200speed_card){
		ret = mmc_select_hs200(sdcard);
		if (!ret)
			return 0;
	}

	if (sdcard->host->caps_high_speed) {
		if (sdcard->sd_spec_version >= MMC_VERSION_4) {
			ret = mmc_switch_high_speed(sdcard);
			if (ret)
				return ret;
		}
	}

	/* Bustest does not work below 26 Mhz */
	host->ops->set_clock(sdcard, 26000000);

	if (sdcard->sd_spec_version >= MMC_VERSION_4) {
		ret = mmc_detect_buswidth(sdcard);
		if (ret) {
			console_printf("MMC: Bustest failed !\n");
			return ret;
		}
	}

	/* Now we can go to cruise speed */
	if (host->ops->set_clock) {
		if (sdcard->highspeed_card) {
			host->ops->set_clock(sdcard, 52000000);
		}
		else
			host->ops->set_clock(sdcard, 26000000);
	}

	/* we enable here DDR if supported */
	if (sdcard->configured_bus_w != 1 && sdcard->ddr_support &&
	    sdcard->host->caps_ddr) {
		ret = mmc_bus_width_select(sdcard, sdcard->configured_bus_w, 1);
		if (ret)
			console_printf("MMC: DDR mode could not be enabled: %d\n", ret);
	}

	return 0;
}

static void init_sdcard_struct(struct sd_card *sdcard)
{
	memset((char *)sdcard, 0, sizeof(*sdcard));
	memset((char *)&sdcard_register, 0, sizeof(sdcard_register));
	memset((char *)&sdcard_sw_caps, 0, sizeof(sdcard_sw_caps));
	memset((char *)&sdcard_command,	0, sizeof(sdcard_command));
	memset((char *)&sdcard_data, 0, sizeof(sdcard_data));

	sdcard->reg = &sdcard_register;
	sdcard->sw_caps = &sdcard_sw_caps;
	sdcard->command = &sdcard_command;
	sdcard->data = &sdcard_data;
}

/*--------------------------------------------------------------------------*/

int sdcard_initialize(void)
{
	struct sd_card *sdcard = &atmel_sdcard;
	struct sd_host *host;
	int ret;

	init_sdcard_struct(sdcard);

#ifdef CONFIG_AT91_MCI
	sdcard_register_at91_mci(sdcard);
#endif

#ifdef CONFIG_SDHC
	sdcard_register_sdhc(sdcard);
#endif

	host = sdcard->host;
	if (host->ops->init) {
		ret = host->ops->init(sdcard);
		if (ret)
			return ret;
	}

	/* Card Indentification Mode */
	ret = sdcard_identification(sdcard);
	if (ret)
		return ret;

	if (sdcard->card_type == CARD_TYPE_SD)
		ret = sd_initialization(sdcard);
	else
		ret = mmc_initialization(sdcard);
	if (ret)
		return ret;

	return 0;
}

/*------------------------------------------------------------------- */

static int sd_cmd_set_blocklen(struct sd_card *sdcard,
					unsigned int block_len)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SET_BLOCKLEN;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = block_len;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	return 0;
}

static int sd_cmd_set_block_count(struct sd_card *sdcard,
					unsigned int block_count)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	int ret;

	command->cmd = SD_CMD_SET_BLOCK_COUNT;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = block_count;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	return 0;
}

static int sd_cmd_stop_transmission(struct sd_card *sdcard)
{
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	unsigned int retries = 1000;
	int ret;

	command->cmd = SD_CMD_STOP_TRANSMISSION;
	command->resp_type = SD_RESP_TYPE_R1B;
	command->argu = 0;

	ret = host->ops->send_command(command, 0);
	if (ret)
		return ret;

	sd_cmd_send_status(sdcard, retries);

	return 0;
}

static int sd_cmd_read_blocks(struct sd_card *sdcard,
				void *buf,
				unsigned int start,
				unsigned int block_count)
{
	unsigned short block_len = sdcard->read_bl_len;
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	int ret;

	command->cmd = SD_CMD_READ_MULTIPLE_BLOCK;
	command->cmd = block_count > 1 ? SD_CMD_READ_MULTIPLE_BLOCK : SD_CMD_READ_SINGLE_BLOCK;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = (sdcard->highcapacity_card) ? start : start * block_len;

	data->buff = (unsigned char *)buf;
	data->direction = SD_DATA_DIR_RD;
	data->blocksize = block_len;
	data->blocks = block_count;

	ret = host->ops->send_command(command, data);
	if (ret)
		return 0;

	return block_count;
}

#define SUPPORT_MAX_BLOCKS	(ADMA2_MAX_NUM_DESC * ADMA2_MAX_DESC_BLOCKS)

unsigned int sdcard_block_read(unsigned int start,
				unsigned int block_count,
				void *buf)
{
	struct sd_card *sdcard = &atmel_sdcard;
	unsigned int blocks_todo = block_count;
	unsigned int blocks;
	unsigned int block_len = sdcard->read_bl_len;
	unsigned int blocks_read;
	unsigned char *read_buf;
	int ret;

	read_buf = (unsigned char *)buf;
	/*
	 * Refer to the at91sam9g20 datasheet:
	 * Figure 35-10. Read Function Flow Diagram
	*/
	/* in DDR mode, we can only use fixed block size: 512 bytes */
	if (!sdcard->ddr) {
		/* Send SET_BLOCKLEN command */
		ret = sd_cmd_set_blocklen(sdcard, block_len);
		if (ret)
			return ret;
	}

	for (blocks_todo = block_count; blocks_todo > 0; ) {
		blocks = (blocks_todo > SUPPORT_MAX_BLOCKS) ?
					SUPPORT_MAX_BLOCKS : blocks_todo;

		if (blocks > 1) {
			if (sdcard->cmd_support & SD_SCR_CMD23_SUPPORT) {
				ret = sd_cmd_set_block_count(sdcard, blocks);
				if (ret)
					return ret;
			}
			blocks_read = sd_cmd_read_blocks(sdcard,
							(void *)read_buf, start, blocks);

			if (sdcard->cmd_support & SD_SCR_CMD23_SUPPORT) {
				if (!blocks_read)
					sd_cmd_stop_transmission(sdcard);
			} else {
				ret = sd_cmd_stop_transmission(sdcard);
				if (ret)
					return ret;
			}
		} else {
			blocks_read = sd_cmd_read_blocks(sdcard,
							(void *)read_buf, start, 1);
		}

		if (blocks_read != blocks)
			return 0;

		blocks_todo -= blocks;
		start += blocks;
		read_buf += blocks * block_len;
	}

	return block_count;
}

#ifdef CONFIG_FAST_BOOT
static int sd_cmd_write_blocks(struct sd_card *sdcard,
				const void *buf,
				unsigned int start,
				unsigned int block_count)
{
	unsigned short block_len = sdcard->read_bl_len;
	struct sd_host *host = sdcard->host;
	struct sd_command *command = sdcard->command;
	struct sd_data *data = sdcard->data;
	int ret;

	command->cmd = block_count > 1 ? SD_CMD_WRITE_MULTIPLE_BLOCK : SD_CMD_WRITE_SINGLE_BLOCK;
	command->resp_type = SD_RESP_TYPE_R1;
	command->argu = (sdcard->highcapacity_card) ? start : start * block_len;

	data->buff = (unsigned char *)buf;
	data->direction = SD_DATA_DIR_WR;
	data->blocksize = block_len;
	data->blocks = block_count;

	ret = host->ops->send_command(command, data);
	if (ret)
		return 0;

	return block_count;
}

unsigned int sdcard_block_write(unsigned int start,
				unsigned int block_count,
				const void *buf)
{
	struct sd_card *sdcard = &atmel_sdcard;
	unsigned int blocks_todo = block_count;
	unsigned int blocks;
	unsigned int block_len = sdcard->read_bl_len;
	unsigned int blocks_written;
	unsigned char *write_buf;
	int ret;

	write_buf = (unsigned char *)buf;
	if (!sdcard->ddr) {
		/* Send SET_BLOCKLEN command */
		ret = sd_cmd_set_blocklen(sdcard, block_len);
		if (ret)
			return 0;
	}
	for (blocks_todo = block_count; blocks_todo > 0; ) {
		blocks = (blocks_todo > SUPPORT_MAX_BLOCKS) ?
					SUPPORT_MAX_BLOCKS : blocks_todo;
		blocks_written = sd_cmd_write_blocks(sdcard,
					(void *)write_buf, start, blocks);
		if (blocks > 1) {
			ret = sd_cmd_stop_transmission(sdcard);
			if (ret)
				return 0;
		}
		if (blocks_written != blocks)
			return 0;
		blocks_todo -= blocks;
		start += blocks;
		write_buf += blocks * block_len;
	}
	return block_count;
}
#endif
