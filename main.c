/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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
 */

#include "common.h"
#include "hardware.h"
#include "board.h"
#include "usart.h"
#include "debug.h"
#include "slowclk.h"
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"
#include "flash.h"
#include "string.h"
#include "board_hw_info.h"
#include "tz_utils.h"
#include "pm.h"
#include "act8865.h"
#include "secure.h"

#ifdef CONFIG_EXTERNAL_RAM_TEST
#include "ddram_utils.h"
#ifdef CONFIG_WITH_CACHE
#include "CP15.h"
#endif /*CONFIG_WITH_CACHE*/
#endif /*CONFIG_EXTERNAL_RAM_TEST*/




//Choose the loader function
#if defined(CONFIG_ONLY_INTERNAL_RAM) || defined(CONFIG_UPLOAD_3RD_STAGE)
//! Nothing to load at all.
static const char* const BOOT_MSG_SUCCESS = "Init Done\n";
static const char* const BOOT_MSG_FAILED =  "Init Failure\n";
static const char* const BOOT_MSG_RECOVERY = "SHOULD NEVER HAPPENS\n";
static const char* const BOOT_MSG_INVALID = "SHOULD NEVER HAPPENS\n";

int load_nothing (struct image_info* unused)
{
  //NOTHING TO DO
  usart_puts("NOTHING is LOADED\n");
  return 0;
}
#define load_image load_nothing

#else
static const char* const BOOT_MSG_SUCCESS = "Done to load image\n";
static const char* const BOOT_MSG_FAILED =  "Failed to load image\n";
static const char* const BOOT_MSG_RECOVERY = "Success to recovery\n";
static const char* const BOOT_MSG_INVALID = "Invalid image loaded\n";


#if defined(CONFIG_LOAD_LINUX) || defined(CONFIG_LOAD_ANDROID)
extern int load_kernel(struct image_info *img_info);
#define load_image load_kernel
#endif

#if defined (CONFIG_DATAFLASH)
#define load_image load_dataflash
#elif defined(CONFIG_FLASH)
#define load_image load_norflash
#elif defined(CONFIG_NANDFLASH)
#define load_image load_nandflash
#elif defined(CONFIG_SDCARD)
#define load_image load_sdcard
#endif


#endif /*defined(CONFIG_ONLY_INTERNAL_RAM) || defined(CONFIG_UPLOAD_3RD_STAGE)*/


//Check a loader as been defined
#if !defined (load_image)
#error "No loader defined : must choose one or no external memory !"
#endif


void (*sdcard_set_of_name)(char *) = NULL;
//****************************************************************************
/**
 * This function will check the loaded application with the expected value at the known address : dest+4
 */
#ifdef CONFIG_CHECK_APPLICATION_LOAD
int check_loaded_application( struct image_info const* const image, unsigned int addr_offset, unsigned int expected_value)
{
  const unsigned int value = *(unsigned int*)(image->dest+addr_offset);
  return value == expected_value ? 0 : -3;
}
//*** Signal the application invalid load. TO BE DEFINED per board.
void signal_invalid_application(void);
#else 
#define signal_invalid_application()
#endif /*CONFIG_CHECK_APPLICATION_LOAD*/
//****************************************************************************
static void display_banner (void)
{
#if defined(CONFIG_UPLOAD_3RD_STAGE)
  static const char* const version = BOARD_NAME" Bootstrap - 3rd stage uploaded through DEBUG PROBE";
#elif defined(CONFIG_ONLY_INTERNAL_RAM)
  static const char* const version = BOARD_NAME" Bootstrap - ONLY internal RAM activated";
#else
  static const char* const version = BOARD_NAME" Bootstrap";
#endif

	char *ver_num = " "AT91BOOTSTRAP_VERSION" ("COMPILE_TIME")";

#if defined( CONFIG_CPU_CLK_498MHZ)
	static const char* const clocks_msg = " CLOCKS : Core:498MHz, Bus:166MHz\n";
#elif defined (CONFIG_CPU_CLK_400MHZ)
	static const char* const clocks_msg = " CLOCKS : Core:400MHz, Bus:132MHz\n";
#elif defined (CONFIG_CPU_CLK_528MHZ)
	static const char* const clocks_msg = " CLOCKS : Core:528MHz, Bus:133MHz\n";
#else
	static const char* const clocks_msg = "CLOCKS : UNKNOWN";
#endif
	usart_puts("\n\n");
	usart_puts(version);
	usart_puts(ver_num);
	usart_puts(clocks_msg);
	usart_puts("\n\n");
}
//**************************************************************************
int main(void)
{
	struct image_info image;
	char *media_str = NULL;
	int ret;
  
#ifdef CONFIG_HW_INIT
  hw_init();
#endif

  display_banner();

#if !(defined(CONFIG_ONLY_INTERNAL_RAM) || defined(CONFIG_UPLOAD_3RD_STAGE))
	char filename[FILENAME_BUF_LEN];
	char of_filename[FILENAME_BUF_LEN];
  
	memset(&image, 0, sizeof(image));
	memset(filename, 0, FILENAME_BUF_LEN);
	memset(of_filename, 0, FILENAME_BUF_LEN);

	image.dest = (unsigned char *)JUMP_ADDR;
#ifdef CONFIG_OF_LIBFDT
	image.of = 1;
	image.of_dest = (unsigned char *)OF_ADDRESS;
#endif

#ifdef CONFIG_FLASH
	media_str = "FLASH: ";
	image.offset = IMG_ADDRESS;
#if !defined(CONFIG_LOAD_LINUX) && !defined(CONFIG_LOAD_ANDROID)
	image.length = IMG_SIZE;
#endif
#ifdef CONFIG_OF_LIBFDT
	image.of_offset = OF_OFFSET;
#endif
#endif

#ifdef CONFIG_NANDFLASH
	media_str = "NAND: ";
	image.offset = IMG_ADDRESS;
#if !defined(CONFIG_LOAD_LINUX) && !defined(CONFIG_LOAD_ANDROID)
	image.length = IMG_SIZE;
#endif
#ifdef CONFIG_OF_LIBFDT
	image.of_offset = OF_OFFSET;
#endif
#endif

#ifdef CONFIG_DATAFLASH
	media_str = "SF: ";
	image.offset = IMG_ADDRESS;
#if !defined(CONFIG_LOAD_LINUX) && !defined(CONFIG_LOAD_ANDROID)
	image.length = IMG_SIZE;
#endif
#ifdef CONFIG_OF_LIBFDT
	image.of_offset = OF_OFFSET;
#endif
#endif

#ifdef CONFIG_SDCARD
	media_str = "SD/MMC: ";
	image.filename = filename;
	strcpy(image.filename, IMAGE_NAME);
#ifdef CONFIG_OF_LIBFDT
	image.of_filename = of_filename;
#endif
#endif
 
#endif  /* defined(CONFIG_ONLY_INTERNAL_RAM) || defined(CONFIG_UPLOAD_3RD_STAGE)*/
  
  
#ifdef CONFIG_LOAD_HW_INFO
	/* Load board hw informaion */
	load_board_hw_info();
#endif
//===================================================
#ifdef CONFIG_EXTERNAL_RAM_TEST
#warning RAM TEST
  
/**
 * @note : simply calling the do_external_ram_tests() function is currently LETHAL !!
 * The CP15_WriteControl() call in CP15_DisableDcache() raises an exception, but WHY ?? 
 * Stack looks good and LR too until called, once done, PC == LR !!
 * Nevertheless, it's ok when called "INLINE" as below.
 */
#if 1
#ifdef CONFIG_WITH_CACHE
  //disable the CACHE first.
  CP15_DisableIcache();
  CP15_DisableDcache();
#endif
  
#ifdef CONFIG_EXTERNAL_RAM_TEST_INFINITE
#warning INFINITE RAM TEST
for(;;)
{
#endif /*CONFIG_EXTERNAL_RAM_TEST_INFINITE*/

  usart_puts("##############################\n");
  
#ifdef CONFIG_EXTERNAL_RAM_TEST_WITHOUT_BURST  
  dbg_log(DEBUG_INFO,"Base memory access\n");
  do_external_ram_tests_step();  
#endif /*CONFIG_EXTERNAL_RAM_TEST_WITHOUT_BURST*/
  
#ifdef CONFIG_EXTERNAL_RAM_TEST_WITH_BURST
//Now test WITH CACHE Activated
  dbg_log(DEBUG_INFO,"WITH Memory BURST\n");

  CP15_EnableIcache();
  CP15_EnableDcache();
  
  do_external_ram_tests_step();  
  
  CP15_DisableIcache();
  CP15_DisableDcache();
#endif /*CONFIG_EXTERNAL_RAM_TEST_WITH_BURST*/

  dbg_log(DEBUG_INFO,"----------------------------\n");
  
#ifdef CONFIG_EXTERNAL_RAM_TEST_INFINITE
}
#endif /*CONFIG_EXTERNAL_RAM_TEST_INFINITE*/

//===================================================
#ifdef CONFIG_WITH_CACHE
  //Enable the CACHE if needed
  CP15_EnableIcache();
  CP15_EnableDcache();
#endif /*CONFIG_WITH_CACHE*/
#else 
  //! @note Currently LETHAL, see the note above.
 do_external_ram_tests();
#endif  
  
#endif /*CONFIG_EXTERNAL_RAM_TEST*/
//===================================================
 
#ifdef CONFIG_PM
	at91_board_pm();
#endif

#ifdef CONFIG_DISABLE_ACT8865_I2C
	act8865_workaround();
#endif

	
#if defined(CONFIG_SECURE)
	image.dest -= sizeof(at91_secure_header_t);
#endif

	ret = load_image(&image);
  
#if !defined(CONFIG_UPLOAD_3RD_STAGE)
  
#if defined(CONFIG_SECURE)
	if (!ret)
		ret = secure_check(image.dest);
	image.dest += sizeof(at91_secure_header_t);
#elif defined (CONFIG_CHECK_APPLICATION_LOAD)
  ret = check_loaded_application(&image, CONFIG_CHECK_APPLICATION_VAL_ADDR_OFFSET, CONFIG_CHECK_APPLICATION_VALUE);
#endif
#endif /*CONFIG_UPLOAD_3RD_STAGE*/

	if (media_str)
		dbg_log(DEBUG_INFO,media_str);

	if (ret == 0){
		dbg_log(DEBUG_INFO,BOOT_MSG_SUCCESS);
	}
	if (ret == -1) {
		dbg_log(DEBUG_ERROR,BOOT_MSG_FAILED);
  while(1);
	}
	if (ret == -2) {
		dbg_log(DEBUG_INFO,BOOT_MSG_RECOVERY);
		while (1);
	}
	if (ret == -3) {
    dbg_log(DEBUG_INFO,BOOT_MSG_INVALID);
    while (1) signal_invalid_application();
  }

#ifdef CONFIG_SCLK
	slowclk_switch_osc32();
#endif

#if defined(CONFIG_ENTER_NWD)
	switch_normal_world();

	/* point never reached with TZ support */
#endif
  
return JUMP_ADDR;
}
//****************************************************
//Will just display a running symbol (use the ABI convention for parameters
void displayWaitDbg(unsigned int dbgdscr, unsigned int cpsr)
{
  dbg_log(2,"DBGDSCR:%b ; CPSR:0x%b\n", dbgdscr, cpsr);
  dbg_log(DEBUG_INFO,"Entering HALT Debug Mode, Waiting for the DEBUGGER ...\n");
}
//****************************************************
//Failure message
void displayFailedMsg()
{
  dbg_log(DEBUG_ERROR,"CPU not HALTED !\n");
}
//****************************************************
//Add the rolling prompt
static const char* ROLLING_PROMPT[] = {"|\r","/\r","-\r","\\\r"};

//! This function is called from the startup code if nothing is loaded.
void displayRollingPromptStep()
{
  static unsigned int loopIdx = 0;
  usart_puts(ROLLING_PROMPT[loopIdx++&0x3]);
}
//****************************************************

