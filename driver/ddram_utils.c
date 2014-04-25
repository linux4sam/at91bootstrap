 
/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2007, Stelian Pop <stelian.pop@leadtechdesign.com>
 * Copyright (c) 2007 Lead Tech Design <www.leadtechdesign.com>
 * Copyright (c) 2014 HAGER Security <www.hager.fr>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
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
#include "hardware.h"
#include "usart.h"
#include "arch/at91_ddrsdrc.h"
#include "debug.h"
#include "ddramc.h"
#include "timer.h"
#include "ddram_utils.h"

#ifdef CONFIG_WITH_CACHE
#include "CP15.h"
#endif /*CONFIG_WITH_CACHE*/


//! @file ddram_utils.c
//! @brief This file contains the RAM utilities functions (checkers ,...)


// Memory test patterns
#define PATTERNS_QTY 5
static const unsigned char PATTERNS_8BIT[PATTERNS_QTY] = 
{
  0x00, 0xFF, 0xAA, 0x55, 0xA5
};

static const unsigned int PATTERNS_32BIT[PATTERNS_QTY] = 
{
  0x00000000, 0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0xA5A5A5A5
};
//**************************************************************
unsigned int 
check_8bit_Ram(unsigned char* const base_address, unsigned int length, const unsigned char pattern)
{
  volatile unsigned char* ram_pos = base_address;
  unsigned int error_count = 0;
  register unsigned char value = 0x00;
  usart_puts("Checking External RAM (8 bit) : \n");
  while ((error_count < 10) && length--)
  {
#if 1
    if ((length & 0xFFFFF) == 0xFFFFF) 
      usart_puts(".");
    
    if ((length & 0xFFFFFF) == 0xFFFFFF)
    {
      usart_puts("+\n");
    }
#endif
    
    *ram_pos = pattern;
    value = *ram_pos;
    if (value != pattern)
    {
      usart_puts("X");
      error_count++;
    }
    ram_pos++;
  }
  
  usart_puts(error_count ? "\n!! 8 bit access test FAILED !! \n" : "\n8 bits access test SUCCEESS\n");
  usart_puts("RAM (8 bit) check done.\n");
  
  return error_count;
}
//*************************************************************
unsigned int 
check_32bit_Ram(unsigned int* const base_address, unsigned int length, const unsigned int pattern)
{
  volatile unsigned int* ram_pos = base_address;
  unsigned int error_count = 0;
  register unsigned int value = 0x00;
  usart_puts("Checking External RAM 32 bits :\n");
  while ((error_count < 10) && length--)
  {
#if 1
    if ((length & 0xFFFF) == 0xFFFF) 
      usart_puts(".");
    
    if ((length & 0xFFFFF) == 0xFFFFF)
    {
      usart_puts("+\n");
    }
#endif

    *ram_pos = pattern;
    value = *ram_pos;
    if (value != pattern)
    {
      usart_puts("X");
      error_count++;
    }
    ram_pos++;
    //pattern ^= (unsigned int)ram_pos;
  }
  
  usart_puts(error_count ? "\nERROR while testing RAM !! \n" : "\nNO Error while testing RAM \n");
  
  return error_count;
}
//*************************************************************
unsigned int 
force_32bit_Ram (unsigned int* const base_address, unsigned int write_value)
{
  unsigned int read_value = ~write_value;
  volatile unsigned int* mem_pos = base_address;
  unsigned int error_count = 0;
  usart_puts("Forcing value in External RAM (32 bit)\n");
  while (read_value != write_value)
  {
    usart_puts("!");
    *mem_pos = write_value;
    read_value = *mem_pos;
    if (read_value == write_value)
      break;
    else
      error_count++;
  }
  usart_puts(" DONE\n");
  return error_count;
}
//**************************************************************
unsigned int 
write_reread_32bit_Ram (unsigned int* const base_address, unsigned int length, const unsigned int pattern)
{
  volatile unsigned int read_value = ~pattern;
  volatile unsigned int* mem_pos = base_address;
  unsigned int read_qty = length;
  unsigned int error_count = -1; //Will be incremented before the test.


  usart_puts("Forcing value in External RAM (32 bit)\n");
  do
  {
    usart_puts("!");
    *mem_pos = pattern;
    read_value = *mem_pos;
    error_count++;
  } while (read_value != pattern);
  
  usart_puts("\nWRITE DONE \n");
  
  while (read_qty--)
  {
    read_value = *mem_pos;
    if (read_value != pattern)
    {
      usart_puts("X");
      //refresh the memory
      *mem_pos = pattern;
      error_count++;
    }
  }
  usart_puts("\nTEST DONE\n");
  return error_count;
}
//****************************************************************
unsigned int 
blank_check_32bit_Ram(unsigned int* const base_address, const unsigned int length)
{
  unsigned int* ram_pos = base_address;
  unsigned int qty = length;
  do
  {
   qty = length;
    //WRITE first
    while (qty--)
    {
      *ram_pos = 0;
      ram_pos++;
    }
    //READ back (qty decremented in the loop : avoid a side effect with the do//while(qty) test.
    qty = length;
    ram_pos = base_address;
    while (qty)
    {
      if (*ram_pos != 0)
        break;
      ram_pos++;
      qty--;
    }
  }while (qty);
  return qty;
}
//****************************************************************
unsigned int 
memset_32bit_Ram(unsigned int* const base_address, unsigned int length, const unsigned int pattern)
{
  unsigned int* ram_pos = base_address;
  unsigned int qty = length;
  while (qty-- > 0)
  {
    *ram_pos = pattern;
    ram_pos++;
  }
  return length - qty;
}

//****************************************************************
void 
do_external_ram_tests_step(void)
{
  unsigned int test_idx = 0;
  for (test_idx = 0 ; test_idx < PATTERNS_QTY ; ++test_idx)
  {
    check_32bit_Ram((unsigned int*)AT91C_BASE_DDRCS, CONFIG_RAM_SIZE * MEGA_WORDS, PATTERNS_32BIT[test_idx]);
  }
  //8 bits
  for (test_idx = 0 ; test_idx < PATTERNS_QTY ; ++test_idx)
  {
    check_8bit_Ram((unsigned char*)AT91C_BASE_DDRCS, CONFIG_RAM_SIZE * MEGA_BYTES, PATTERNS_8BIT[test_idx]);
  }
}
//*****************************************************************
void
do_external_ram_tests(void)
{
  usart_puts("********************************\n");
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
  usart_puts("Base memory access\n");
  do_external_ram_tests_step();  
#endif /*CONFIG_EXTERNAL_RAM_TEST_WITHOUT_BURST*/
  
#ifdef CONFIG_EXTERNAL_RAM_TEST_WITH_BURST
//Now test WITH CACHE Activated
  usart_puts("WITH Memory BURST\n");
  CP15_EnableIcache();
  CP15_EnableDcache();
  
  do_external_ram_tests_step();  
  
  CP15_DisableIcache();
  CP15_DisableDcache();
#endif /*CONFIG_EXTERNAL_RAM_TEST_WITH_BURST*/
  
  usart_puts("----------------------------\n");
#ifdef CONFIG_EXTERNAL_RAM_TEST_INFINITE
}
#endif /*CONFIG_EXTERNAL_RAM_TEST_INFINITE*/

#ifdef CONFIG_WITH_CACHE
  //Enable the CACHE if needed
  CP15_EnableIcache();
  CP15_EnableDcache();
#endif
usart_puts("********************************\n");
}