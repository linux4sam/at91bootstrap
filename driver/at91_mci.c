/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
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
#include "mmc.h"
#include "pit_timer.h"

#include "debug.h"

/* command definition */
#define MMC_CMD_GO_IDLE_STATE		0
#define MMC_CMD_SEND_OP_COND		1
#define MMC_CMD_ALL_SEND_CID		2
#define MMC_CMD_SET_RELATIVE_ADDR	3
#define MMC_CMD_SET_DSR			4
#define MMC_CMD_SWITCH			6
#define MMC_CMD_SELECT_CARD		7
#define MMC_CMD_SEND_EXT_CSD		8
#define MMC_CMD_SEND_CSD		9
#define MMC_CMD_SEND_CID		10
#define MMC_CMD_STOP_TRANSMISSION	12
#define MMC_CMD_SEND_STATUS		13
#define MMC_CMD_SET_BLOCKLEN		16
#define MMC_CMD_READ_SINGLE_BLOCK	17
#define MMC_CMD_READ_MULTIPLE_BLOCK	18
#define MMC_CMD_WRITE_SINGLE_BLOCK	24
#define MMC_CMD_WRITE_MULTIPLE_BLOCK	25
#define MMC_CMD_APP_CMD			55
#define MMC_CMD_SPI_READ_OCR		58
#define MMC_CMD_SPI_CRC_ON_OFF		59

#define SD_CMD_SEND_RELATIVE_ADDR	3
#define SD_CMD_SWITCH_FUNC		6
#define SD_CMD_SEND_IF_COND		8

#define SD_CMD_APP_SET_BUS_WIDTH	6
#define SD_CMD_APP_SEND_OP_COND		41
#define SD_CMD_APP_SEND_SCR		51
#define SD_CMD_APP_SD_STATUS		13

#define CONFIG_SYS_MMC_DEFAULT_CLK	1000000
#define CONFIG_SYS_MMC_DEFAULT_BLKLEN	512

#define MCI_SUPPORT_MAX_BLKS 65535

/* function macro */
#define mci_readl(reg)					\
	readl((void *)CONFIG_SYS_BASE_MCI + reg)

#define mci_writel(reg, value)				\
	writel((value), (void *)CONFIG_SYS_BASE_MCI + reg)

/* Setup for MCI Clock and Block Size */
static void mci_set_mode(unsigned int clock, unsigned int blklen)
{
	unsigned int main_clock = MASTER_CLOCK; 
	unsigned int clkdiv = 255;
	unsigned int reg;

	if (clock > 0)
		clkdiv = (main_clock + clock) / clock;

	blklen &= 0xfffc;

#if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(AT91SAMA5D3X)
	/* set blklen in Block Register */
	reg = mci_readl(MCI_BLKR);
	reg &= ~(((0x1 << 16) -1) << 16);
	reg |= (blklen << 16);
	mci_writel(MCI_BLKR, reg);

	/* set Mode Register */
	reg = AT91C_MCI_RDPROOF_ENABLE;
	reg |= AT91C_MCI_WRPROOF_ENABLE;

	clkdiv -= 2;
	reg |= (clkdiv >> 1);
	if (clkdiv & 1)
		reg |=	AT91C_MCI_CLKODD;

	mci_writel(MCI_MR, reg);
#else
	clkdiv = clkdiv / 2 - 1;
	if (clkdiv & ~255UL)
		clkdiv = 255;

	reg = AT91C_MCI_MRBLKLEN(blklen)
		| AT91C_MCI_RDPROOF_ENABLE
		| AT91C_MCI_WRPROOF_ENABLE
		| AT91C_MCI_CLKDIV(clkdiv);

	mci_writel(MCI_MR, reg);
#endif	/* #if defined(AT91SAM9X5) || defined(AT91SAM9N12) || defined(AT91SAMA5D3X) */
}

static void mci_set_clock(unsigned int clock)
{
	mci_set_mode(clock, CONFIG_SYS_MMC_DEFAULT_BLKLEN);
}

static int mci_set_blkr(unsigned int blkcnt, unsigned int blklen)
{
	mci_writel(MCI_BLKR, (blklen << 16) | blkcnt);
	return 0;
}

static int mci_set_bus_width(unsigned int buswidth)
{
	unsigned int reg;

	reg = mci_readl(MCI_SDCR);

	if (buswidth == 8)
		reg |=  AT91C_MCI_SCDBUS_8BIT;
	else if (buswidth == 4)
		reg |= AT91C_MCI_SCDBUS_4BIT;
	else
		reg |= AT91C_MCI_SCDBUS_1BIT;

	mci_writel(MCI_SDCR, reg);

	return 0;
}

static void mci_init(void)
{
	/* software reset */
	mci_writel(MCI_CR, AT91C_MCI_SWRST);

	/* disable mci and disable power save mode */
	mci_writel(MCI_CR, AT91C_MCI_PWSDIS | AT91C_MCI_MCIDIS);

	/* SDCard/SDIO Slot */
	mci_writel(MCI_SDCR, AT91C_MCI_SCDSEL_SLOTA);

	/* initialize timeout register */
	mci_writel(MCI_DTOR, 0x7f);

	/* disable Interrupt */
	mci_writel(MCI_IDR, ~0L);

	/* set default bus width */
	mci_set_bus_width(1);

	/* set default clocks and blocklen */
	mci_set_mode(CONFIG_SYS_MMC_DEFAULT_CLK, CONFIG_SYS_MMC_DEFAULT_BLKLEN);

	/* enable mci */
	mci_writel(MCI_CR, AT91C_MCI_MCIEN);
}

/* response type definition */
#define MMC_RSP_PRESENT (1 << 0)
#define MMC_RSP_136	(1 << 1)	/* 136 bit response */
#define MMC_RSP_CRC	(1 << 2)	/* expect valid crc */
#define MMC_RSP_BUSY	(1 << 3)	/* card may send busy */
#define MMC_RSP_OPCODE	(1 << 4)	/* response contains opcode */

#define MMC_RSP_NONE	(0)
#define MMC_RSP_R1	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1b	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE| \
			MMC_RSP_BUSY)
#define MMC_RSP_R2	(MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3	(MMC_RSP_PRESENT)
#define MMC_RSP_R4	(MMC_RSP_PRESENT)
#define MMC_RSP_R5	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

/* Data Time-out Error */
/* Response Direction Error */
/* Response End Bit Error */
/* Response Index Error */
/* Response Time-out Error */
#define ERROR_FLAGS	(AT91C_MCI_DTOE	\
			| AT91C_MCI_RDIRE \
			| AT91C_MCI_RENDE \
			| AT91C_MCI_RINDE \
			| AT91C_MCI_RTOE)

static int mmc_cmd(unsigned short cmd,
			unsigned int resp_type,
			unsigned int cmdarg,
			unsigned int flags,
			unsigned int *response)
{
	unsigned int cmdr;
	unsigned int status;
	unsigned int error_flags = ERROR_FLAGS;

	/* Default Flags for the Command */
	flags |= AT91C_MCI_MAXLAT_64;

	if (resp_type & MMC_RSP_CRC)
		error_flags |= AT91C_MCI_RCRCE; 
	if (resp_type & MMC_RSP_136)
		flags |= AT91C_MCI_RSPTYP_136; 
	else if (resp_type & MMC_RSP_BUSY)
		flags |= AT91C_MCI_RSPTYP_R1B; 
	else if (resp_type & MMC_RSP_PRESENT)
		flags |= AT91C_MCI_RSPTYP_48;

	cmdr = cmd | flags;

	/* Send the command */
	mci_writel(MCI_ARGR, cmdarg);
	mci_writel(MCI_CMDR, cmdr);

	/* Wait for the command to complete */
	while (!((status = mci_readl(MCI_SR)) & AT91C_MCI_CMDRDY));

	if (status & AT91C_MCI_RTOE) {
		dbg_log(1, "Cmd Response Time-out Error\n\r");
		return TIMEOUT;
	}
	if (status & error_flags) {
		dbg_log(1, "Error status,cmd: %d, status: %d\n\r", cmd, status);
		return COMM_ERR;
	}

	/* Copy the response to the response buffer */
	if (resp_type & MMC_RSP_136) {
		*response++ = mci_readl(MCI_RSPR);
		*response++ = mci_readl(MCI_RSPR1);
		*response++ = mci_readl(MCI_RSPR2);
		*response++ = mci_readl(MCI_RSPR3);
	} else
		*response = mci_readl(MCI_RSPR); 

	return 0;
}

static int mmc_go_idle(void)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	udelay(1000);

	cmd = MMC_CMD_GO_IDLE_STATE;
	cmdarg = 0;
	resp_type = MMC_RSP_NONE;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	udelay(2000);

	return 0;
}

static int mmc_send_if_cond(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	cmd = SD_CMD_SEND_IF_COND;

	/* We set the bit if the host supports voltages between 2.7 and 3.6 V */
	cmdarg = ((mmc->voltages & 0xff8000) != 0) << 8 | 0xaa;
	resp_type = MMC_RSP_R7;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	if ((response[0] & 0xff) != 0xaa)
		return UNUSABLE_ERR;
	else
		mmc->version = SD_VERSION_2;

	return 0;
}

static int sd_send_op_cond(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;
	int timeout = 1000;

	do {
		cmd = MMC_CMD_APP_CMD;
		resp_type = MMC_RSP_R1;
		cmdarg = 0;
		flags = 0;

		ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
		if (ret)
			return ret;

		cmd = SD_CMD_APP_SEND_OP_COND;
		resp_type = MMC_RSP_R3;

		/*
		 * Most cards do not answer if some reserved bits
		 * in the ocr are set. However, Some controller
		 * can set bit 7 (reserved for low voltages), but
		 * how to manage low voltages SD card is not yet
		 * specified.
		 */
		cmdarg = mmc->voltages & 0xff8000;

		if (mmc->version == SD_VERSION_2)
			cmdarg |= OCR_HCS;

		flags = 0;

		ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
		if (ret)
			return ret;

		udelay(1000);

	} while ((!(response[0] & OCR_BUSY)) && timeout--);

	if (timeout <= 0)
		return UNUSABLE_ERR;

	if (mmc->version != SD_VERSION_2)
		mmc->version = SD_VERSION_1_0;

	mmc->ocr = response[0];

	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
	mmc->rca = 0;

	return 0;
}

static int mmc_send_op_cond(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;
	int timeout = 10000;

 	/* Asking to the card its capabilities */
 	cmd = MMC_CMD_SEND_OP_COND;
 	resp_type = MMC_RSP_R3;
 	cmdarg = 0;
 	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
 	if (ret)
 		return ret;

 	udelay(1000);

	do {
		cmd = MMC_CMD_SEND_OP_COND;
		resp_type = MMC_RSP_R3;
		cmdarg = (mmc->voltages & (response[0] & OCR_VOLTAGE_MASK))
				| (response[0] & OCR_ACCESS_MODE);
		flags = 0;

		ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
		if (ret)
			return ret;

		udelay(1000);
	} while (!(response[0] & OCR_BUSY) && timeout--);

	if (timeout <= 0)
		return UNUSABLE_ERR;

	mmc->version = MMC_VERSION_UNKNOWN;
	mmc->ocr = response[0];

	mmc->high_capacity = ((mmc->ocr & OCR_HCS) == OCR_HCS);
	mmc->rca = 0;

	return 0;
}

static int sd_init_card(struct mmc *mmc)
{
	int ret;

	ret = mmc_go_idle();
	if (ret)
		return ret;

	/* Test for SD version 2 */
	ret = mmc_send_if_cond(mmc);

	/* Now try to get the SD card's operating condition */
	ret = sd_send_op_cond(mmc);

	return ret;
}

static int mmc_init_card(struct mmc *mmc)
{
	int ret;

	ret = mmc_go_idle();
	if (ret)
		return ret;

	ret = mmc_send_op_cond(mmc);

	return ret;
}

static int mmc_send_status(struct mmc *mmc, int timeout)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	cmd = MMC_CMD_SEND_STATUS;
	resp_type = MMC_RSP_R1;
	cmdarg = mmc->rca << 16;
	flags = 0;

	do {
		ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
		if (ret)
			return ret;
		else if (response[0] & MMC_STATUS_RDY_FOR_DATA)
			break;

		udelay(1000);

		if (response[0] & MMC_STATUS_MASK) {
			dbg_log(1, "send_status, card status Error: %d\n\r", response[0]);
			return COMM_ERR;
		}
	} while (timeout--);

	if (!timeout) {
		dbg_log(1, "send_status, timeout waiting card ready\n\r");
		return TIMEOUT;
	}

	return 0;
}

static int mmc_send_all_cid(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	/* Put the Card in Identify Mode */
	cmd = MMC_CMD_ALL_SEND_CID;
	resp_type = MMC_RSP_R2;
	cmdarg = 0;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	memcpy(mmc->cid, response, 16);
	return 0;
}

static int mmc_send_rca(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	cmd = SD_CMD_SEND_RELATIVE_ADDR;
	cmdarg = mmc->rca << 16;
	resp_type = MMC_RSP_R6;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	if (IS_SD(mmc))
		mmc->rca = (response[0] >> 16) & 0xffff;

	return 0;
}

static int mmc_send_csd(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;
	int timeout = 1000;

	cmd = MMC_CMD_SEND_CSD;
	resp_type = MMC_RSP_R2;
	cmdarg = mmc->rca << 16;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);

	/* Waiting for the ready status */
	mmc_send_status(mmc, timeout);
	if (ret)
		return ret;

	mmc->csd[0] = response[0];
	mmc->csd[1] = response[1];
	mmc->csd[2] = response[2];
	mmc->csd[3] = response[3];

	if (mmc->version == MMC_VERSION_UNKNOWN) {
		int version = (mmc->csd[0] >> 26) & 0xf;

		if (version == 0)
			mmc->version = MMC_VERSION_1_2;
		else if (version == 1)
			mmc->version = MMC_VERSION_1_4;
		else if (version == 2)
			mmc->version = MMC_VERSION_2_2;
		else if (version == 3)
			mmc->version = MMC_VERSION_3;
		else if (version == 4)
			mmc->version = MMC_VERSION_4;
		else
			mmc->version = MMC_VERSION_1_2;
	}

	mmc->read_bl_len = 1 << ((mmc->csd[1] >> 16) & 0xf);
	if (mmc->read_bl_len > 512)
		mmc->read_bl_len = 512;

	return 0;
}

static int mmc_send_select_card(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	cmd = MMC_CMD_SELECT_CARD;
	resp_type = MMC_RSP_R1b;
	cmdarg = mmc->rca << 16;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	return 0;
}

static int mmc_data_read(struct mmc *mmc,
			unsigned int *data,
			unsigned int blocksize,
			unsigned int blkcnt)
{
	unsigned int status;
	unsigned int word_count;
	unsigned int block_count;
	unsigned int *tmp;
	unsigned int sys_blocksize = mmc->read_bl_len;
	unsigned int dummy;
	unsigned int timeout;

	for (block_count = 0; block_count < blkcnt; block_count++) {
		word_count = 0;

		/* read the data of the block */
		do {
			do {
				status = mci_readl(MCI_SR);
				if (status & (ERROR_FLAGS | AT91C_MCI_OVRE)) {
					dbg_log(1, "Comm/Overrun Error, MCI_SR:%d\n\r", status);
					return status;
				}
			} while (!(status & AT91C_MCI_RXRDY));

			if (status & AT91C_MCI_RXRDY) {
				*data++ = mci_readl(MCI_RDR);
				word_count++;
			}
		} while (word_count < (blocksize / 4));

		/* read the rest of the full block */
		tmp = &dummy;
		while (word_count < (sys_blocksize / 4)) {
			do {
				status = mci_readl(MCI_SR);
				if (status & (ERROR_FLAGS | AT91C_MCI_OVRE)) {
					dbg_log(1, "Comm/Overrun Error, MCI_SR:%d\n\r", status);
					return status;
				}
			} while (!(status & AT91C_MCI_RXRDY));

			if (status & AT91C_MCI_RXRDY) {
				*tmp = mci_readl(MCI_RDR);
				word_count++;
			}
		}
	}

	timeout = 0;
	do {
		status = mci_readl(MCI_SR);
		if (status & ERROR_FLAGS) {
			dbg_log(1, "Comm Error MCI_SR:%d\n\r", status);
			return COMM_ERR;
		}
		timeout++;
	} while ((status & AT91C_MCI_DTIP) && (timeout < 10000));

	if (status & AT91C_MCI_DTIP) {
		dbg_log(1, "MCI_SR:%d\n\r", status);
		return COMM_ERR;
	}

	return 0;
}

static int sd_set_bus_width_4(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	cmd = MMC_CMD_APP_CMD;
	resp_type = MMC_RSP_R1;
	cmdarg = mmc->rca << 16;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	cmd = SD_CMD_APP_SET_BUS_WIDTH;
	resp_type = MMC_RSP_R1;
	cmdarg = 2;	/* 4 bit width */
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	mci_set_bus_width(4);

	return 0;
}

static int sd_send_scr(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;
	int timeout;

	unsigned int scr[2];
	unsigned int blocksize = 8;

	mmc->card_caps = 0;

	/* Read the SCR to find out if this card supports higher speeds */
	cmd = MMC_CMD_APP_CMD;
	resp_type = MMC_RSP_R1;
	cmdarg = mmc->rca << 16;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	cmd = SD_CMD_APP_SEND_SCR;
	resp_type = MMC_RSP_R1;
	cmdarg = 0;
	flags = AT91C_MCI_TRCMD_START | AT91C_MCI_TRDIR_READ;

	timeout = 3;
retry_scr:
	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret) {
		if (timeout--)
			goto retry_scr;

		return ret;
	}

	blocksize = 8;
	ret = mmc_data_read(mmc, scr, blocksize, 1);
	if (ret)
		return ret;

	mmc->scr[0] = be32_to_cpu(scr[0]);
	mmc->scr[1] = be32_to_cpu(scr[1]);

	int version = (mmc->scr[0] >> 24) & 0xf;

	if (version ==  0)
		mmc->version = SD_VERSION_1_0;
	else if (version == 1)
		mmc->version = SD_VERSION_1_10;
	else if (version == 2)
		mmc->version = SD_VERSION_2;
	else
		mmc->version = SD_VERSION_1_0;

	if (mmc->scr[0] & SD_DATA_4BIT)
		mmc->card_caps |= MMC_MODE_4BIT;

	return 0;
}

static int mmc_send_ext_csd(struct mmc *mmc, char *ext_csd)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	unsigned int *data = (unsigned int *)ext_csd;
	unsigned int blocksize = 512;

	/* Get the Card Status Register */
	cmd = MMC_CMD_SEND_EXT_CSD;
	resp_type = MMC_RSP_R1;
	cmdarg = 0;
	flags = AT91C_MCI_TRCMD_START | AT91C_MCI_TRDIR_READ;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	ret = mmc_data_read(mmc, data, blocksize, 1);
	if (ret)
		return ret;

	return 0;
}

static int mmc_switch(struct mmc *mmc, unsigned char set, unsigned char index, unsigned char value)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	int timeout = 1000;

	cmd = MMC_CMD_SWITCH;
	resp_type = MMC_RSP_R1b;
	cmdarg = (MMC_SWITCH_MODE_WRITE_BYTE << 24)
			| (index << 16)
			| (value << 8);
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);

	/* Waiting for the ready status */
	mmc_send_status(mmc, timeout);

	return ret;

}

static int sd_switch(struct mmc *mmc,
			int mode,
			int group,
			unsigned char value,
			unsigned char *resp)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	unsigned int *data = (unsigned int *)resp;
	unsigned int blocksize = 64;

	/* Switch the frequency */
	cmd = SD_CMD_SWITCH_FUNC;
	resp_type = MMC_RSP_R1;
	cmdarg = (mode << 31) | 0xffffff;
	cmdarg &= ~(0xf << (group * 4));
	cmdarg |= value << (group * 4);
	flags = AT91C_MCI_TRCMD_START | AT91C_MCI_TRDIR_READ;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	ret = mmc_data_read(mmc, data, blocksize, 1);
	if (ret)
		return ret;

	return 0;
}

static int mmc_change_freq(struct mmc *mmc)
{
	int ret;
	char ext_csd[512];
	char cardtype;

	mmc->card_caps = 0;

	/* Only version 4 supports high-speed */
	if (mmc->version < MMC_VERSION_4)
		return 0;

	mmc->card_caps |= MMC_MODE_4BIT;

	ret = mmc_send_ext_csd(mmc, ext_csd);
	if (ret)
		return ret;

	cardtype = ext_csd[196] & 0xf;

	ret = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_HS_TIMING, 1);

	if (ret)
		return ret;

	/* Now check to see that it worked */
	ret = mmc_send_ext_csd(mmc, ext_csd);
	if (ret)
		return ret;

	/* No high-speed support */
	if (!ext_csd[185])
		return 0;

	/* High Speed is set, there are two types: 52MHz and 26MHz */
	if (cardtype & MMC_HS_52MHZ)
		mmc->card_caps |= MMC_MODE_HS_52MHz | MMC_MODE_HS;
	else
		mmc->card_caps |= MMC_MODE_HS;

	return 0;
}

static int sd_change_freq(struct mmc *mmc)
{
	unsigned int switch_status[16];
	int timeout;
	int ret;

	timeout = 6;
	while (timeout--) {
		ret = sd_switch(mmc, SD_SWITCH_CHECK, 0, 1, (unsigned char *)&switch_status);
		if (ret)
			return ret;

		/* The high-speed function is busy.  Try again */
		if (!(be32_to_cpu(switch_status[7]) & SD_HIGHSPEED_BUSY))
			break;
	}

	/* If high-speed isn't supported, we return */
	if (!(be32_to_cpu(switch_status[3]) & SD_HIGHSPEED_SUPPORTED))
		return 0;

	ret = sd_switch(mmc, SD_SWITCH_SWITCH, 0, 1, (unsigned char *)&switch_status);
	if (ret)
		return ret;

	if ((be32_to_cpu(switch_status[4]) & 0x0f000000) == 0x01000000)
		mmc->card_caps |= MMC_MODE_HS;

	return 0;
}

static int mmc_set_buswidth_clock(struct mmc *mmc)
{
	int ret;

	if (IS_SD(mmc)) {
		/* Read the SD Configuration Register(SCR) */
		ret = sd_send_scr(mmc);
		if (ret)
			return ret;

		/* Version 1.0 doesn't support switching */
		if (mmc->version != SD_VERSION_1_0)
			ret = sd_change_freq(mmc);
			if (ret)
				return ret;
	} else {
		ret = mmc_change_freq(mmc);
		if (ret)
			return ret;
	}

	/* Restrict card's capabilities by what the host can do */
	mmc->card_caps &= mmc->host_caps;

	if (IS_SD(mmc)) {
		if (mmc->card_caps & MMC_MODE_4BIT)
			ret = sd_set_bus_width_4(mmc);
			if (ret)
				return ret;

		if (mmc->card_caps & MMC_MODE_HS)
			mci_set_clock(40000000);
		else
			mci_set_clock(20000000);
	} else {
		if (mmc->card_caps & MMC_MODE_4BIT) {
			/* Set the card to use 4 bit*/
			ret = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
					EXT_CSD_BUS_WIDTH,
					EXT_CSD_BUS_WIDTH_4);

			if (ret)
				return ret;

			mci_set_bus_width(4);
		} else if (mmc->card_caps & MMC_MODE_8BIT) {
			/* Set the card to use 8 bit*/
			ret = mmc_switch(mmc, EXT_CSD_CMD_SET_NORMAL,
					EXT_CSD_BUS_WIDTH,
					EXT_CSD_BUS_WIDTH_8);

			if (ret)
				return ret;

			mci_set_bus_width(8);
		}

		if (mmc->card_caps & MMC_MODE_HS) {
			if (mmc->card_caps & MMC_MODE_HS_52MHz)
				mci_set_clock(52000000);
			else
				mci_set_clock(26000000);
		} else
			mci_set_clock(20000000);
	}

	return 0;
}

static struct mmc atmel_mmc;

int mmc_initialize(void)
{
	struct mmc *mmc = &atmel_mmc;
	int ret;

	mmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34;
#ifdef CONFIG_SDCARD_HS
	mmc->host_caps = MMC_MODE_4BIT | MMC_MODE_HS;
#else
	mmc->host_caps = MMC_MODE_4BIT;
#endif

	/* Initialize mci interface */
	mci_init();

	/* Card Indentification mode */
	ret = sd_init_card(mmc);
	if (ret == TIMEOUT) {
		ret = mmc_init_card(mmc);
		if (ret)
			return UNUSABLE_ERR;
	}

	/* Ask any card CID number */
	ret = mmc_send_all_cid(mmc);
	if (ret)
		return ret;

	/*
	 * For MMC cards, set the Relative Address.
	 * For SD cards, get the Relatvie Address.
	 * This also puts the cards into Standby State
	 */
	ret = mmc_send_rca(mmc);
	if (ret)
		return ret;

	/* Get the Card-Specific Data */
	ret = mmc_send_csd(mmc);
	if (ret)
		return ret;

	/* Select the card, and put it into Transfer Mode */
	ret = mmc_send_select_card(mmc);
	if (ret)
		return ret;

	/* Set bus width and clock */
	ret = mmc_set_buswidth_clock(mmc);
	if (ret)
		return ret;

	return 0;
}

static int mmc_set_blocklen(int blocklen)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	cmd = MMC_CMD_SET_BLOCKLEN;
	resp_type = MMC_RSP_R1;
	cmdarg = blocklen;
	flags = 0;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return ret;

	return 0;
}

static int mmc_stop_transmission(struct mmc *mmc)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int timeout = 1000;

	cmd = MMC_CMD_STOP_TRANSMISSION;
	cmdarg = 0;
	resp_type = MMC_RSP_R1b;
	flags = 0;
	if (mmc_cmd(cmd, resp_type, cmdarg, flags, response)) {
		dbg_log(1, "mmc fail to send stop cmd\n\r");
		return 0;
	}

	/* Waiting for the ready status */
	mmc_send_status(mmc, timeout);

	return 0;
}

static int mmc_read_blocks(struct mmc *mmc,
				void *dest,
				unsigned int start,
				unsigned int blkcnt)
{
	unsigned short cmd;
	unsigned int  cmdarg;
	unsigned int  resp_type;
	unsigned int  flags;
	unsigned int  response[4];
	int ret;

	unsigned int blocklen = mmc->read_bl_len;

	/* set block count and block length */
	mci_set_blkr(blkcnt, blocklen);

	flags = AT91C_MCI_TRCMD_START | AT91C_MCI_TRDIR_READ;
	if (blkcnt > 1) {
		cmd = MMC_CMD_READ_MULTIPLE_BLOCK;
		flags |= AT91C_MCI_TRTYP_MULTIPLE;
	} else {
		cmd = MMC_CMD_READ_SINGLE_BLOCK;
		flags |= AT91C_MCI_TRTYP_SINGLE;
	}

	if (mmc->high_capacity) 
		cmdarg = start;
	else
		cmdarg = start * mmc->read_bl_len;

	resp_type = MMC_RSP_R1;

	ret = mmc_cmd(cmd, resp_type, cmdarg, flags, response);
	if (ret)
		return 0;

	ret = mmc_data_read(mmc, dest, blocklen, blkcnt);
	if (ret)
		return 0;

	if (blkcnt > 1) 
		mmc_stop_transmission(mmc);

	return blkcnt;
}

unsigned int mmc_bread(unsigned int start, unsigned int blkcnt, void *dest)
{
	struct mmc *mmc = &atmel_mmc;
	unsigned int cur_blocks, blocks_todo = blkcnt;

	if (blkcnt == 0)
		return 0;

	if (mmc_set_blocklen(mmc->read_bl_len))
		return 0;

	do {
		cur_blocks = (blocks_todo > MCI_SUPPORT_MAX_BLKS) ? MCI_SUPPORT_MAX_BLKS : blocks_todo;
		if(mmc_read_blocks(mmc, dest, start, cur_blocks) != cur_blocks)
			return 0;

		blocks_todo -= cur_blocks;
		start += cur_blocks;
		dest += cur_blocks * mmc->read_bl_len;
	} while (blocks_todo > 0);

	return blkcnt;
}
