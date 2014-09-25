/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
#include "twi.h"
#include "board_hw_info.h"
#include "debug.h"

#define	EK_AT24XX_ADDR		0x54

#define	MAX_AT24XX_BYTES	256
#define EK_INFO_OFFSET		(MAX_AT24XX_BYTES - HW_INFO_TOTAL_SIZE)

static int at24_read(unsigned char device_addr, unsigned char internal_addr,
			unsigned char *buff, unsigned int length)
{
	unsigned char iaddr_size = 1;
	int ret = 0;

	ret = twi_read(device_addr, internal_addr, iaddr_size, buff, length);
	if (ret)
		dbg_loud("EEPROM: Failed to read\n");

	return ret;
}

int load_ek_at24xx(unsigned char *buff, unsigned int length)
{
	unsigned char dev_addr = EK_AT24XX_ADDR;
	unsigned char offset = EK_INFO_OFFSET;
	int ret = 0;
	unsigned int i;
	unsigned char *tmp = buff;

	ret = at24_read(dev_addr, offset, buff, length);

	dbg_loud("EEPROM Buff:\n");
	for (i = 0; i < length; i++)
		dbg_loud("%d ", *tmp++);
	dbg_loud("\n");

	return ret;
}
