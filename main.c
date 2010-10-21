/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

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
 * File Name           : main.c
 * Object              :
 * Creation            : ODi Apr 19th 2006
 *-----------------------------------------------------------------------------
 */
#include "part.h"
#include "main.h"
#include "dbgu.h"
#include "debug.h"
#include "dataflash.h"
#include "nandflash.h"
#include "flash.h"
#ifdef CONFIG_USER_HW_INIT
void user_hw_init(void);
#endif

extern void Jump(unsigned int addr);    // Function import from startup.s file

extern unsigned int load_SDCard();

void sclk_enable(void);

void LoadLinux();

void LoadWince();

/*------------------------------------------------------------------------------*/
/* Function Name       : Wait							*/
/* Object              : software loop waiting function				*/
/*------------------------------------------------------------------------------*/
void Wait(unsigned int count)
{
    volatile unsigned int i;

#ifdef WINCE
    volatile unsigned int j = 0;
#endif

    for (i = 0; i < count; i++) {
#ifdef WINCE
        j++;
#else
        asm("    nop");
#endif
    }
}

/*------------------------------------------------------------------------------*/
/* Function Name       : main							*/
/* Object              : Main function						*/
/* Input Parameters    : none							*/
/* Output Parameters   : True							*/
/*------------------------------------------------------------------------------*/
int main(void)
{
    /*
     * ================== 1st step: Hardware Initialization ================= 
     *
     * Performs the hardware initialization 
     */
#ifdef CONFIG_HW_INIT
    hw_init();
#endif

#ifdef CONFIG_USER_HW_INIT
    user_hw_init();
#endif

    dbg_log(1, "Begin to load image...\n\r");
    /*
     * ==================== 2nd step: Load from media ==================== 
     *
     * Load from Dataflash in RAM 
     */
#if defined(CONFIG_DATAFLASH) || defined(CONFIG_DATAFLASH_CARD)
#if defined(CONFIG_LOAD_LINUX)
    LoadLinux();
#elif defined(CONFIG_LOAD_NK) || defined(CONFIG_LOAD_EBOOT)
    LoadWince();
#else
    load_df(AT91C_SPI_PCS_DATAFLASH, IMG_ADDRESS, IMG_SIZE, JUMP_ADDR);
#endif
#endif

    /*
     * Load from Nandflash in RAM 
     */
#if defined(CONFIG_NANDFLASH)
#if defined(CONFIG_LOAD_LINUX)
    LoadLinux();
#elif defined(CONFIG_LOAD_NK) || defined(CONFIG_LOAD_EBOOT)
    LoadWince();
#else
    read_nandflash((unsigned char *)JUMP_ADDR, (unsigned long)IMG_ADDRESS,
                   (int)IMG_SIZE);
#endif
#endif

    /*
     * Load from Norflash in RAM 
     */
#ifdef CONFIG_FLASH
    load_norflash(IMG_ADDRESS, IMG_SIZE, JUMP_ADDR);
#endif

#if defined(CONFIG_SDCARD)
#if defined(CONFIG_LOAD_LINUX)
    LoadLinux();
#elif defined(CONFIG_LOAD_NK) || defined(CONFIG_LOAD_EBOOT)
    LoadWince();
#else
    load_SDCard();
#endif
#endif

    dbg_log(1, "Loading image done.\n\r");
    /*
     * ==================== 3rd step:  Process the Image =================== 
     */
    /*
     * Uncompress the image 
     */
#ifdef CONFIG_GUNZIP
    decompress_image((void *)IMG_ADDRESS, (void *)JUMP_ADDR, IMG_SIZE); /* NOT IMPLEMENTED YET */
    msg_print(MSG_DECOMPRESS);
#endif

    /*
     * ==================== 4th step: Start the application =================== 
     */
    /*
     * Set linux arguments 
     */
#ifdef CONFIG_LINUX_ARG
    linux_arg(LINUX_ARG);       /* NOT IMPLEMENTED YET */
    msg_print(MSG_LINUX);
#endif                          /* LINUX_ARG */

#ifdef CONFIG_SCLK
    sclk_enable();
#endif

#ifdef WINCE
#ifdef CONFIG_LOAD_NK
    Jump(JUMP_ADDR + 0x1000);
#else
    Jump(JUMP_ADDR);
#endif
#else                           /* !WINCE */
#ifdef CONFIG_LOAD_NK
    return (JUMP_ADDR + 0x1000);
#else
    return JUMP_ADDR;
#endif
#endif
}
