/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation

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
 * ----------------------------------------------------------------------------
 * File Name           : dataflash.c
 * Object              : 
 * Creation            :
 *---------------------------------------------------------------------------
*/

#include "hardware.h"
#include "board.h"
#include "spi_flash.h"

#include "debug.h"


int load_dataflash(unsigned int offset, unsigned int size, unsigned char *dest)
{
	int ret;
	struct spi_flash *flash;

	at91_spi0_hw_init();

	flash = spi_flash_probe(CONFIG_SPI_BUS,
				CONFIG_SPI_CS,
				CONFIG_SPI_CLOCK,
				CONFIG_SPI_MODE);
	if (!flash) {
		dbg_log(1, "spi_flash_probe() failed\n\r");
		return 1;
	}

	dbg_log(1, "SF: Copy %d bytes from %d to %d\r\n", size, offset, dest);

	ret = spi_flash_read(flash, offset, size, dest);
	if (ret) {
		dbg_log(1, "** Serial flash read error **\n\r");
		return 1;
	}

	return 0;
}

