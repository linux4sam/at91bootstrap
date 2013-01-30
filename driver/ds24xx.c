/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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
#include "hardware.h"
#include "board.h"
#include "arch/at91_pio.h"
#include "gpio.h"
#include "debug.h"
#include "timer.h"
#include "string.h"
#include "onewire_info.h"

#define ROM_COMMAND_READ		0x33
#define ROM_COMMAND_MATCH		0x55
#define ROM_COMMAND_SEARCH		0xF0
#define ROM_COMMAND_SKIP		0xCC
#define ROM_COMMAND_RESUME		0xA5
#define ROM_COMMAND_OSKIP		0x3C
#define ROM_COMMAND_OMATCH		0x69

#define MEMORY_COMMAND_WSCRATCHPAD	0x0F
#define MEMORY_COMMAND_RSCRATCHPAD	0xAA
#define MEMORY_COMMAND_CSCRATCHPAD	0x55
#define MEMORY_COMMAND_READMEMORY	0xF0

#define tSLOT				65
#define tRSTL				480
#define tPDH				60
#define tPDL				240
#define tWOL				60
#define tW1L				5
#define tRL				5
#define tMSR				10
#define tPROG				13000

#define FAMILY_CODE_DS2431		0x2D
#define FAMILY_CODE_DS2433		0x23
#define FAMILY_CODE_DS28EC		0x43

#define MAX_RETRY			10
#define MAX_BUF_LEN			256

#define BOARD_TYPE_CPU			1
#define BOARD_TYPE_EK			2
#define BOARD_TYPE_DM			3

#define MAX_ITEMS			5
#define CHIP_ADDR_LEN			8

#define BOARD_NAME_LEN			12
#define VENDOR_NAME_LEN			10
#define VENDOR_COUNTRY_LEN		2

#define CM_SN_MASK			0x1F
#define CM_SN_OFFSET			0
#define CM_VENDOR_MASK			(0x1F << 5)
#define CM_VENDOR_OFFSET		5
#define CM_REV_MASK			0x1F
#define CM_REV_OFFSET			0

#define LEN_ONE_WIRE_INFO		0x20

/*  */
struct one_wire_info {
	unsigned char total_bytes;
	char vendor_name[VENDOR_NAME_LEN];
	char vendor_country[VENDOR_COUNTRY_LEN];
	unsigned char board_name[BOARD_NAME_LEN];
	unsigned char year;
	unsigned char week;
	unsigned char revision_code;
	unsigned char revision_id;
	unsigned char reserved;
};

struct ek_boards {
	char *board_name;
	unsigned char board_type;
	unsigned char board_id;
};

struct ek_vendors {
	char *vendor_name;
	char vendor_id;
};

static unsigned int sn = 0xffffffff;
static unsigned int rev = 0xffffffff;

static unsigned char device_id_array[MAX_ITEMS][CHIP_ADDR_LEN];
static unsigned char LastDiscrepancy;
static unsigned char LastFamilyDiscrepancy;
static unsigned char LastDeviceFlag;

static unsigned char buf[MAX_BUF_LEN];
static unsigned char cmp[MAX_BUF_LEN];

static struct ek_boards	board_list[] = {
	{"SAM9x5-EK",		BOARD_TYPE_EK,		0},
	{"SAM9x5-DM",		BOARD_TYPE_DM,		1},
	{"SAM9G15-CM",		BOARD_TYPE_CPU,		2},
	{"SAM9G25-CM",		BOARD_TYPE_CPU,		3},
	{"SAM9G35-CM",		BOARD_TYPE_CPU,		4},
	{"SAM9X25-CM",		BOARD_TYPE_CPU,		5},
	{"SAM9X35-CM",		BOARD_TYPE_CPU,		6},
	{"PDA-DM",		BOARD_TYPE_DM,		7},
	{"SAMA5D3x-MB",		BOARD_TYPE_EK,		8},
	{"SAMA5D3x-DM",		BOARD_TYPE_DM,		9},
	{"SAMA5D31-CM",		BOARD_TYPE_CPU,		10},
	{"SAMA5D33-CM",		BOARD_TYPE_CPU,		11},
	{"SAMA5D34-CM",		BOARD_TYPE_CPU,		12},
	{"SAMA5D35-CM",		BOARD_TYPE_CPU,		13},
	{0,			0,			0},
};

static struct ek_vendors	vendor_list[] = {
	{"EMBEST",		VENDOR_EMBEST},
	{"FLEX",		VENDOR_FLEX},
	{"RONETIX",		VENDOR_RONETIX},
	{"COGENT",		VENDOR_COGENT},
	{"PDA",			VENDOR_PDA},
	{0,			0},
};

/*------------------------------------------------*/
static inline void set_wire_low()
{
	pio_set_gpio_output(CONFIG_SYS_ONE_WIRE_PIN, 0);
}

static inline void set_wire_input()
{
	pio_set_gpio_input(CONFIG_SYS_ONE_WIRE_PIN, 0);
}

static inline int read_wire_bit()
{
	return pio_get_value(CONFIG_SYS_ONE_WIRE_PIN);
}

static unsigned char dscrc_table[] = {
	  0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
	157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
	 35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
	190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
	 70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
	219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
	101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
	248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
	140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
	 17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
	175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
	 50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
	202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
	 87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
	233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
	116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53
};

static unsigned char docrc8(unsigned char crc8, unsigned char value)
{
	return dscrc_table[crc8 ^ value];
}

static int ds24xx_reset(void)
{
	int i;

	set_wire_low();
	udelay(tRSTL);

	set_wire_input();
	udelay(tPDH);

	i = read_wire_bit();
	udelay(tPDL);

	return i ^ 1;
}

static void ds24xx_write_bit(int bit)
{
	if (bit == 1) {
		set_wire_low();
		udelay(tW1L);
		set_wire_input();
		udelay(tSLOT-tW1L);
	} else {
		set_wire_low();
		udelay(tWOL);
		set_wire_input();
		udelay(tSLOT-tWOL);
	}
}

static int ds24xx_read_bit()
{
	int status;

	set_wire_low();
	udelay(tRL);

	set_wire_input();
	udelay(tMSR / 2);

	status = read_wire_bit();
	udelay(tSLOT-tRL-tMSR);

	return status;
}

static void ds24xx_write_byte(unsigned char data)
{
	int i;

	for (i = 0; i < 8; i++) {
		ds24xx_write_bit(data & 1);
		data >>= 1;
	}
}

static unsigned char ds24xx_read_byte()
{
	int i;
	unsigned char result = 0;

	for (i = 0; i < 8; i++) {
		result >>= 1;
		if (ds24xx_read_bit())
			result |= 0x80;
	}

	return result;
}

/* MAXIM App. Note #187 */
static int ds24xx_search_rom()
{
	int id_bit_number;
	int last_zero, rom_byte_number, search_result;
	int id_bit, cmp_id_bit;
	unsigned char rom_byte_mask, search_direction;
	unsigned char crc8 = 0;

	/* initialize for search */
	id_bit_number = 1;
	last_zero = 0;
	rom_byte_number = 0;
	rom_byte_mask = 1;
	search_result = 0;

	/* if the last call was not the last one */
	if (!LastDeviceFlag) {
		/* 1-Wire reset */
		if (!ds24xx_reset()) {
			 /* reset the search*/
			 dbg_log(1, "1-Wire: reset fail\n\r");
			 LastDiscrepancy = 0;
			 LastDeviceFlag = 0;
			 LastFamilyDiscrepancy = 0;
			 return 0;
		}

		/* issue the search command */
		ds24xx_write_byte(ROM_COMMAND_SEARCH);

		/* loop to do the search */
		do
		{
			/* read a bit and its complement */
			id_bit = ds24xx_read_bit();
			cmp_id_bit = ds24xx_read_bit();

			/* check for no devices on 1-Wire */
			if ((id_bit == 1) && (cmp_id_bit == 1))
				break;
			else {
				/* all devices coupled have 0 or 1 */
				if (id_bit != cmp_id_bit)
					search_direction = id_bit;
				else {
					/*
					 * if this discrepancy if before
					 * the Last Discrepancy on a previous
					 * next then pick the same as last time
					 */
					if (id_bit_number < LastDiscrepancy)
						search_direction =
							((buf[rom_byte_number]
							& rom_byte_mask) > 0);
					else
						/*
						 * if equal to last pick 1,
						 * if not then pick 0
						 */
						search_direction
						= (id_bit_number
							== LastDiscrepancy);

					/*
					 * if 0 was picked then record its
					 * position in LastZero
					 */
					if (search_direction == 0) {
						last_zero = id_bit_number;
						/*
						 * check for Last discrepancy
						 * in family
						 */
						if (last_zero < 9)
							LastFamilyDiscrepancy
								= last_zero;
					}
				}

				/*
				 * set or clear the bit in the ROM byte
				 * rom_byte_number with mask rom_byte_mask
				 */
				if (search_direction == 1)
					buf[rom_byte_number] |= rom_byte_mask;
				else
					buf[rom_byte_number] &= ~rom_byte_mask;

				/* serial number search direction write bit */
				if (search_direction == 1)
					ds24xx_write_bit(1);
				else
					ds24xx_write_bit(0);

				/*
				 * increment the byte counter id_bit_number
				 * and shift the mask rom_byte_mask
				 */
				id_bit_number++;
				rom_byte_mask <<= 1;

				/*
				 * if the mask is 0 then go to new SerialNum
				 * byte rom_byte_number and reset mask
				 */
				if (rom_byte_mask == 0) {
					crc8 = docrc8(crc8,
						buf[rom_byte_number]);
					rom_byte_number++;
					rom_byte_mask = 1;
				}
			}
		} while(rom_byte_number < 8);  /* loop until through all ROM bytes 0-7 */

		/* if the search was successful then */
		if (!((id_bit_number < 65) || (crc8 != 0))) {
			/* search successful so set LastDiscrepancy,LastDeviceFlag,search_result */
			LastDiscrepancy = last_zero;

			/* check for last device */
			if (LastDiscrepancy == 0)
				LastDeviceFlag = 1;

			search_result = 1;
		}
	}

	/* if no device found then reset counters so next 'search' will be like a first */
	if (!search_result || !buf[0]) {
		LastDiscrepancy = 0;
		LastDeviceFlag = 0;
		LastFamilyDiscrepancy = 0;
		search_result = 0;
	}

	return search_result;
}

static int ds24xx_find_first()
{
	/* reset the search state */
	LastDiscrepancy = 0;
	LastDeviceFlag = 0;
	LastFamilyDiscrepancy = 0;

	return ds24xx_search_rom();
}

static int ds24xx_find_next()
{
	/* leave the search state alone */
	return ds24xx_search_rom();
}

static unsigned int enumerate_all_rom(void)
{
	int i;
	int result;
	unsigned int cnt = 0;

	dbg_log(1, "1-Wire: ROM Searching ... ");

	result = ds24xx_find_first();
	while (result) {

		/* save device info */
		for (i = 7; i >= 0; i--)
			device_id_array[cnt][i] = buf[i];
		cnt++;

		result = ds24xx_find_next();
	}

	dbg_log(1, "Done, %d 1-Wire chips found\n\r\n\r", cnt);

	return cnt;
}

static int ds24xx_read_memory(int chip_index, unsigned char addrh,
	unsigned char addrl, int len,unsigned char *p)
{
	int i, round, retries = 0;
	unsigned char *pbuf[2] = {p, cmp};

	switch(device_id_array[chip_index][0]){
	case FAMILY_CODE_DS2431:
	case FAMILY_CODE_DS2433:
	case FAMILY_CODE_DS28EC:
		break;
	default:
		dbg_log(1, "1-Wire: family %d is not supported\n\r",
					device_id_array[chip_index][0]);
		return -1;
	}

retry:
	for (round = 0; round < 2; round++) {
		if (!ds24xx_reset())
			dbg_log(1, "1-Wire: reset failed\n\r");

		ds24xx_write_byte(ROM_COMMAND_MATCH);
		for(i = 0; i < 8; i++)
			ds24xx_write_byte(device_id_array[chip_index][i]);

		ds24xx_write_byte(MEMORY_COMMAND_READMEMORY);
		ds24xx_write_byte(addrl);
		ds24xx_write_byte(addrh);

		for(i = 0; i < len; i++)
			pbuf[round][i] = ds24xx_read_byte();
	}


	/* Compare the buffer, if all the same, return 0 */
	for (i = 0; i < len; i++) {
		if (p[i] != cmp[i])
			break;
	}

	if (i == len)
		return 0;

	if (retries++ < MAX_RETRY)
		goto retry;

	return -1;
}

static unsigned char normalize_rev_code(const unsigned char c)
{
	if ((c >= 'A') && (c <= 'Z'))
		return c;

	if ((c >= 'a') && (c <= 'z'))
		return c - 0x20;

	/* by default, return revision 'A' */
	return 'A';
}

static unsigned char normalize_rev_id(const unsigned char c)
{
	if ((c >= '0') && (c <= '9'))
		return c;

	if (c > '9') {
		if (((c >= 'A') && (c <= 'F'))
			|| ((c >= 'a') && (c <= 'f')))
			return '9';
	}

	/* by default, return revision '0' */
	return '0';
}

struct board_info {
	unsigned char board_type;
	unsigned char board_id;
	unsigned char revision_code;
	unsigned char revision_id;
	unsigned char vendor_id;
};

static int get_board_info(unsigned char *buffer,
				unsigned char bd_sn,
				struct board_info *bd_info)
{
	int i;
	char tmp[20];
	struct one_wire_info one_wire;
	struct one_wire_info *p = &one_wire;
	unsigned char *pbuf = buffer;

	char *boardname;
	char *vendorname;
	unsigned revcode;
	unsigned revid;

	p->total_bytes = (unsigned char)*pbuf;

	pbuf = buffer + 1;
	for (i = 0; i < VENDOR_NAME_LEN; i++)
		p->vendor_name[i] = *pbuf++;

	pbuf = buffer + 11;
	for (i = 0; i < VENDOR_COUNTRY_LEN; i++)
		p->vendor_country[i] = *pbuf++;

	pbuf = buffer + 13;
	for (i = 0; i < BOARD_NAME_LEN; i++)
		p->board_name[i] = *pbuf++;

	p->year = *pbuf++;
	p->week = *pbuf++;
	p->revision_code = *pbuf++;
	p->revision_id = *pbuf++;

	memset(tmp, 0, sizeof(tmp));

	for (i = 0; i < BOARD_NAME_LEN; i++) {
		if (p->board_name[i] == 0x20)
			break;

		tmp[i] = p->board_name[i];
	}

	for (i = 0; i < ARRAY_SIZE(board_list); i++) {
		if (strncmp(board_list[i].board_name, tmp,
			strlen(board_list[i].board_name)) == 0) {
			bd_info->board_type = board_list[i].board_type;
			bd_info->board_id = board_list[i].board_id;
			bd_info->revision_code
				= normalize_rev_code(p->revision_code);
			bd_info->revision_id = normalize_rev_id(p->revision_id);
			break;
		}
	}

	boardname = board_list[i].board_name;
	revcode = bd_info->revision_code;
	revid = bd_info->revision_id;

	if (i == ARRAY_SIZE(board_list)) {
		return -1;
	}

	memset(tmp, 0, sizeof(tmp));
	for (i = 0; i < VENDOR_NAME_LEN; i++) {
		if (p->vendor_name[i] == 0x20)
			break;
		tmp[i] = p->vendor_name[i];
	}

	for (i = 0; i < ARRAY_SIZE(vendor_list); i++) {
		if (strncmp(vendor_list[i].vendor_name, tmp,
			    strlen(vendor_list[i].vendor_name)) == 0) {
			bd_info->vendor_id = vendor_list[i].vendor_id;
			break;
		}
	}

	if (i == ARRAY_SIZE(vendor_list)) {
		return -1;
	}

	vendorname = vendor_list[i].vendor_name;

	dbg_log(1, "  #%d", bd_sn);
	dbg_log(1, "  %s [%c%c]      %s\n\r",
			boardname, revcode, revid, vendorname);

	return 0;
}

void load_1wire_info()
{
	int i;
	unsigned int	cnt;
	unsigned int	size = LEN_ONE_WIRE_INFO;
	struct board_info	board_info;
	struct board_info	*bd_info;

	memset(&board_info, 0, sizeof(board_info));
	bd_info= &board_info;

	dbg_log(1, "1-Wire: Loading 1-Wire information ...\n\r");

	sn = rev = 0;

	cnt = enumerate_all_rom();
	if (!cnt) {
		dbg_log(1, "WARNING: 1-Wire: No 1-Wire chip found\n\r ");
		goto err;
	}

	dbg_log(1, "1-Wire: BoardName | [Revid] | VendorName\n\r");

	for (i = 0; i < cnt; i++) {
		if (ds24xx_read_memory(i, 0, 0, size, buf) < 0) {
			dbg_log(1, "WARNING: 1-Wire: Failed to " \
				"read from 1-Wire chip!\n\r");
			goto err;
		}

		if (get_board_info(buf,	i, bd_info)) {
			dbg_log(1, "WARNING: 1-Wire: Failed to " \
						"get board information\n\r");
			goto err;
		}

		switch (bd_info->board_type) {
		case BOARD_TYPE_CPU:
			sn  |= (bd_info->board_id & 0x1F);
			sn  |= ((bd_info->vendor_id & 0x1F) << 5);
			rev |= (bd_info->revision_code - 'A');
			rev |= (((bd_info->revision_id - '0') & 0x3) << 15);
			break;

		case BOARD_TYPE_DM:
			sn  |= ((bd_info->board_id & 0x1F) << 10);
			sn  |= ((bd_info->vendor_id & 0x1F) << 15);
			rev |= ((bd_info->revision_code - 'A') << 5);
			rev |= (((bd_info->revision_id - '0') & 0x3) << 18);
			break;

		case BOARD_TYPE_EK:
			sn  |= ((bd_info->board_id & 0x1F) << 20);
			sn  |= ((bd_info->vendor_id & 0x1F) << 25);
			rev |= ((bd_info->revision_code - 'A') << 10);
			rev |= (((bd_info->revision_id - '0') & 0x3) << 21);
			break;

		default:
			dbg_log(1, "WARNING: 1-Wire: Unknown board type\n\r");
			goto err;
		}
	}

	/* save to GPBR #2 and #3 */
	writel(sn, AT91C_BASE_GPBR + 4 * 2);
	writel(rev, AT91C_BASE_GPBR + 4 * 3);

err:
	dbg_log(1, "\n\r");

	return;
}

unsigned int get_sys_sn()
{
	if (sn == 0xffffffff) {
		dbg_log(1, "Error: no system_sn defined, using 0!\n\r");
		return 0;
	}

	return sn;
}

unsigned int get_sys_rev()
{
	if (rev == 0xffffffff) {
		dbg_log(1, "Error: no system_rev defined, using 0!\n\r");
		return 0;
	}

	return rev;
}

unsigned int get_cm_sn()
{
	return (sn & CM_SN_MASK) >> CM_SN_OFFSET;
}

unsigned int get_cm_vendor()
{
	return (sn & CM_VENDOR_MASK) >> CM_VENDOR_OFFSET;
}

char get_cm_rev()
{
	return 'A' + ((rev & CM_REV_MASK) >> CM_REV_OFFSET);
}
