/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __MCI_MEDIA_H__
#define __MCI_MEDIA_H__

/* SD Command */
#define SD_CMD_GO_IDLE_STATE	0
#define SD_CMD_ALL_SEND_CID	2
#define SD_CMD_SEND_RELATIVE_ADDR	3
#define SD_CMD_SWITCH_FUN	6
#define SD_CMD_SELECT_CARD	7
#define SD_CMD_SEND_IF_COND	8
#define SD_CMD_SEND_CSD	9
#define SD_CMD_SEND_CID	10
#define SD_CMD_VOLTAGE_SWITCH	11
#define SD_CMD_STOP_TRANSMISSION	12
#define SD_CMD_SEND_STATUS	13
#define SD_CMD_SET_BLOCKLEN	16
#define SD_CMD_READ_SINGLE_BLOCK	17
#define SD_CMD_READ_MULTIPLE_BLOCK	18
#define SD_CMD_WRITE_SINGLE_BLOCK	24
#define SD_CMD_WRITE_MULTIPLE_BLOCK	25
#define SD_CMD_SEND_TUNING_BLOCK	19
#define SD_CMD_SET_BLOCK_COUNT	23
#define SD_CMD_APP_CMD	55

/* SD App Command */
#define SD_CMD_APP_SET_BUS_WIDTH	6
#define SD_CMD_APP_SD_STATUS	13
#define SD_CMD_APP_SD_SEND_OP_COND	41
#define SD_CMD_APP_SEND_SCR	51

/* MMC specifial Command */
#define MMC_CMD_SEND_OP_COND	1
#define MMC_CMD_SWITCH_FUN	6
#define MMC_CMD_SEND_EXT_CSD	8
#define MMC_CMD_BUSTEST_R	14
#define MMC_CMD_BUSTEST_W	19
#define MMC_CMD_SEND_TUNING_BLOCK	21

/* Card State */
#define SD_STATE_INACTIVE	0
#define SD_STATE_IDLE	1
#define SD_STATE_READY	2
#define SD_STATE_IDENTIFICATION	3
#define SD_STATE_STAND_BY	4
#define SD_STATE_TRANSFER	5
#define SD_STATE_SENDING_DATA	6
#define SD_STATE_RECEIVE_DATA	7
#define SD_STATE_PROGRMMING	8
#define SD_STATE_DISCONNECT	9

/* Card Type */
#define CARD_TYPE_SD	1
#define CARD_TYPE_MMC	2

/* SDCARD Capacity Class */
#define SD_CAP_CLASS_SDSC	0x01
#define SD_CAP_CLASS_SDHC	0x02
#define SD_CAP_CLASS_SDXC	0x04

/* SD CARD Version */
#define SD_VERSION_1_0	0x10
#define SD_VERSION_1_10	0x1a
#define SD_VERSION_2	0x20
#define SD_VERSION_3	0x30

/* MMC Card Version */
#define MMC_VERSION_1_2	0x12
#define MMC_VERSION_1_4	0x14
#define MMC_VERSION_2_2	0x22
#define MMC_VERSION_3	0x30
#define MMC_VERSION_4	0x40

/* SD OCR Voltage Range */
#define SD_OCR_VDD_165_195	(0x01 << 7)
#define SD_OCR_VDD_20_21	(0x01 << 8)
#define SD_OCR_VDD_21_22	(0x01 << 9)
#define SD_OCR_VDD_22_23	(0x01 << 10)
#define SD_OCR_VDD_23_24	(0x01 << 11)
#define SD_OCR_VDD_24_25	(0x01 << 12)
#define SD_OCR_VDD_25_26	(0x01 << 13)
#define SD_OCR_VDD_26_27	(0x01 << 14)
#define SD_OCR_VDD_27_28	(0x01 << 15)
#define SD_OCR_VDD_28_29	(0x01 << 16)
#define SD_OCR_VDD_29_30	(0x01 << 17)
#define SD_OCR_VDD_30_31	(0x01 << 18)
#define SD_OCR_VDD_31_32	(0x01 << 19)
#define SD_OCR_VDD_32_33	(0x01 << 20)
#define SD_OCR_VDD_33_34	(0x01 << 21)
#define SD_OCR_VDD_34_35	(0x01 << 22)
#define SD_OCR_VDD_35_36	(0x01 << 23)
#define SD_OCR_S18R	(0x01 << 24)
#define SD_ROCR_S18A	SD_OCR_S18R
#define SD_OCR_XPC	(1 << 28)
#define SD_OCR_CCS	(1 << 30)

#define OCR_VOLTAGE_27_36_MASK	0xff8000
#define CHECK_PATTERN	0xaa

#define ERROR_TIMEOUT	-10
#define ERROR_COMM	-11
#define ERROR_UNUSABLE_CARD	-12

/*
 * Response Types
 */
#define	SD_RESP_TYPE_NO_RESP	0x00
#define	SD_RESP_TYPE_R1	0x10
#define	SD_RESP_TYPE_R1B	0x11
#define	SD_RESP_TYPE_R2	0x20
#define	SD_RESP_TYPE_R3	0x30
#define	SD_RESP_TYPE_R4	0x40
#define	SD_RESP_TYPE_R5	0x50
#define SD_RESP_TYPE_R6	0x60
#define SD_RESP_TYPE_R7	0x70

#define ADMA2_MAX_NUM_DESC	64
#define ADMA2_MAX_DESC_BLOCKS	128

struct sd_command {
	unsigned int cmd;
	unsigned int cmd_type;
	unsigned int resp_type;
	unsigned int argu;
	unsigned int resp[4];
};

#define	SD_DATA_DIR_RD	0x11
#define	SD_DATA_DIR_WR	0x22

struct sd_data {
	unsigned char *buff;
	unsigned int direction;
	unsigned int blocks;
	unsigned short blocksize;
};

struct sd_card;

struct host_ops {
	int (*init)(struct sd_card *sdcard);
	int (*send_command)(struct sd_command *command, struct sd_data *data);
	int (*set_clock)(struct sd_card *sdcard, unsigned int clock);
	int (*set_bus_width)(struct sd_card *sdcard, unsigned int width);
	int (*set_ddr)(struct sd_card *sdcard);
	int (*set_signal_voltage)(struct sd_card *sdcard);
	int (*set_hs200)(struct sd_card *sdcard);
	int (*set_hs400)(struct sd_card *sdcard);
	int (*set_1v8)(struct sd_card *sdcard);
	void (*set_uhs_mode)(struct sd_card *sdcard, unsigned int mode);
	void (*set_uhs_driver)(struct sd_card *sdcard, unsigned int driver);
	int (*exec_tuning)(struct sd_card *sdcard, unsigned int cmd);
	int (*card_busy)(struct sd_card *sdcard);
};

#define	BUS_WIDTH_1_BIT		0x01
#define	BUS_WIDTH_4_BIT		0x04
#define	BUS_WIDTH_8_BIT		0x08

struct sd_host {
	const unsigned char *name;
	struct host_ops *ops;
	unsigned int caps_bus_width;
	unsigned int caps_high_speed;
	unsigned int caps_uhs;
	unsigned int caps_adma2;
	unsigned int caps_ddr;
	unsigned int caps_clk_mult;
	unsigned int caps_max_clock;
	unsigned int caps_min_clock;
	unsigned int caps_uhs_clock;
	unsigned int caps_voltages;
};

struct sdcard_register {
	unsigned int	cid[4];	/* Card identification number */
	unsigned int	rca;	/* Relative card address */
	unsigned int	dsr;	/* Driver Stage Register */
	unsigned int	csd[4];	/* Card Specific Data */
	unsigned int	scr[2];	/* SD Configuration Register */
	unsigned int	ocr;	/* Operation condition register */
	unsigned int	ssr[16];/* SD status */
	unsigned int	csr;	/* Card Status */
};

struct sdcard_sw_caps {
	unsigned int	hs_max_dtr;
	unsigned int	uhs_max_dtr;
#define HIGH_SPEED_MAX_DTR	50000000
#define UHS_DDR200_MAX_DTR	208000000
#define UHS_SDR104_MAX_DTR	208000000
#define UHS_SDR50_MAX_DTR	100000000
#define UHS_DDR50_MAX_DTR	50000000
#define UHS_SDR25_MAX_DTR	UHS_DDR50_MAX_DTR
#define UHS_SDR12_MAX_DTR	25000000
#define DEFAULT_SPEED_MAX_DTR	UHS_SDR12_MAX_DTR
	unsigned int	sd3_bus_mode;
#define UHS_SDR12_BUS_SPEED		0
#define HIGH_SPEED_BUS_SPEED	1
#define UHS_SDR25_BUS_SPEED		1
#define UHS_SDR50_BUS_SPEED		2
#define UHS_SDR104_BUS_SPEED	3
#define UHS_DDR50_BUS_SPEED		4

#define SD_MODE_HIGH_SPEED	(1 << HIGH_SPEED_BUS_SPEED)
#define SD_MODE_UHS_SDR12	(1 << UHS_SDR12_BUS_SPEED)
#define SD_MODE_UHS_SDR25	(1 << UHS_SDR25_BUS_SPEED)
#define SD_MODE_UHS_SDR50	(1 << UHS_SDR50_BUS_SPEED)
#define SD_MODE_UHS_SDR104	(1 << UHS_SDR104_BUS_SPEED)
#define SD_MODE_UHS_DDR50	(1 << UHS_DDR50_BUS_SPEED)
	unsigned int	sd3_cmd_sys;
#define SD_SET_CMD_SYS_EC		1
#define SD_SET_CMD_SYS_OTP		3
#define SD_SET_CMD_SYS_ASSD		4
#define SD_SET_CMD_SYS_ESD		12
#define SD_SET_CMD_SYS_VENDOR	14
#define UHS_DDR200_BUS_SPEED	SD_SET_CMD_SYS_VENDOR

#define SD_CMD_SYS_EC		(1 << SD_SET_CMD_SYS_EC)
#define SD_CMD_SYS_OTP		(1 << SD_SET_CMD_SYS_OTP)
#define SD_CMD_SYS_ASSD		(1 << SD_SET_CMD_SYS_ASSD)
#define SD_CMD_SYS_ESD		(1 << SD_SET_CMD_SYS_ESD)
#define SD_CMD_SYS_VENDOR	(1 << SD_SET_CMD_SYS_VENDOR)
	unsigned int	sd3_drv_type;
#define SD_SET_DRIVER_TYPE_B	0
#define SD_SET_DRIVER_TYPE_A	1
#define SD_SET_DRIVER_TYPE_C	2
#define SD_SET_DRIVER_TYPE_D	3

#define SD_DRIVER_TYPE_B (1 << SD_SET_DRIVER_TYPE_B)
#define SD_DRIVER_TYPE_A (1 << SD_SET_DRIVER_TYPE_A)
#define SD_DRIVER_TYPE_C (1 << SD_SET_DRIVER_TYPE_C)
#define SD_DRIVER_TYPE_D (1 << SD_SET_DRIVER_TYPE_D)
	unsigned int	sd3_curr_limit;
#define SD_SET_CURRENT_LIMIT_200	0
#define SD_SET_CURRENT_LIMIT_400	1
#define SD_SET_CURRENT_LIMIT_600	2
#define SD_SET_CURRENT_LIMIT_800	3
#define SD_SET_CURRENT_LIMIT_500	4

#define SD_MAX_CURRENT_200	(1 << SD_SET_CURRENT_LIMIT_200)
#define SD_MAX_CURRENT_400	(1 << SD_SET_CURRENT_LIMIT_400)
#define SD_MAX_CURRENT_600	(1 << SD_SET_CURRENT_LIMIT_600)
#define SD_MAX_CURRENT_800	(1 << SD_SET_CURRENT_LIMIT_800)
#define SD_MAX_CURRENT_500	(1 << SD_SET_CURRENT_LIMIT_500)
};

struct sd_card {
	unsigned int	card_type;

	unsigned int	sd_spec_version;
	unsigned int	highcapacity_card;
	unsigned int	bus_width_support;
#define SD_SCR_BUS_WIDTH_1  (1<<0)
#define SD_SCR_BUS_WIDTH_4  (1<<2)

	unsigned int	cmd_support;
#define SD_SCR_CMD20_SUPPORT  (1<<0)
#define SD_SCR_CMD23_SUPPORT  (1<<1)
#define SD_SCR_CMD48_SUPPORT  (1<<2)
#define SD_SCR_CMD58_SUPPORT  (1<<3)
#define SD_SCR_ACMD53_SUPPORT (1<<4)

	unsigned int	highspeed_card;  /* is this card a HS according to CARDTYPE */
	unsigned int	hs200speed_card; /* is this card a HS200 according to CARDTYPE */
	unsigned int	hs400speed_card; /* is this card a HS400 according to CARDTYPE */
	unsigned int	ddr; /* is this card running in DDR mode */
	unsigned int	ddr_support; /* is this card a DDR according to CARDTYPE */
	unsigned int	read_bl_len;
	unsigned int	configured_bus_w; /* bus width which we configured */
	unsigned int	v1v8; /* is this card running in 1V8 mode */

	struct sd_host	*host;

	struct sdcard_register	*reg;
	struct sdcard_sw_caps	*sw_caps;
	struct sd_command	*command;
	struct sd_data		*data;
};

#endif /* #ifndef __MCI_MEDIA_H__ */
