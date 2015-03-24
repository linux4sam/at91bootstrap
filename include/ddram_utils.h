/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, HAGER Security

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
#ifndef DDRAM_UTILS_H_
#define DDRAM_UTILS_H_

//Constants 
//! One mega bytes
#define MEGA_BYTES 0x100000

//! One Mega 32 bit words.
#define MEGA_WORDS (MEGA_BYTES/4)


/**
 * This function will check the memory starting from the given base address for the given length based on 8bit access.
 * @param base_address [IN] The base address area to be tested
 * @param length [IN] The length (in bytes) of the area to be tested.
 * @param pattern [IN] The pattern used to test the memory.
 * @return - 0 : Ok , - other : Error occured.
 */
unsigned int check_8bit_Ram(unsigned char* const base_address, unsigned int length, unsigned char pattern);

/**
 * This function will check the memory starting from the given base address for the given length based on 32 bit access.
 * @param base_address [IN] The base address area to be tested
 * @param length [IN] The length (in bytes) of the area to be tested.
 * @param pattern [IN] The pattern used to test the memory.
 * @return - 0 : Ok , - other : Error occured.
 */
unsigned int check_32bit_Ram(unsigned int* const base_address, unsigned int length, unsigned int pattern);

/**
 * This function will write the given value (as 32 bits) until the read value is the same.
 * @param base_address [IN] The used address
 * @param write_value [IN] The test value
 * @return The number of retry.
 */
unsigned int force_32bit_Ram (unsigned int* const base_address, unsigned int write_value);

/**
 * This function will blank and check the memory from the base_address up to length WORD (32bit).
 * @param base_address [IN] The starting word.
 * @param length [IN] The word quantity (in 32 bit words).
 * @return operation status.
 */
unsigned int blank_check_32bit_Ram(unsigned int* const base_address, unsigned int length);

/**
 * This function set the given pattern from base_address for length WORDS.
 */
unsigned int memset_32bit_Ram(unsigned int* const base_address, unsigned int length, const unsigned int pattern);

/**
 * This function force the write of the given value into the RAM (32 bits) and then re-read it several times.
 * @param base_address [IN] The used address
 * @param length [IN] The tested area length int WORDS.
 * @param pattern [IN] The test value
 * @return The number of failure. 
 */
unsigned int write_reread_32bit_Ram (unsigned int* const base_address, unsigned int length, const unsigned int pattern);

/**
 * This function will run the one coded memory tests.
 */
void do_external_ram_tests(void);
void do_external_ram_tests_step(void);

#endif /*DDRAM_UTILS_H_*/