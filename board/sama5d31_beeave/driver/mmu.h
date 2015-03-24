/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

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
#ifndef MMU_H_
#define MMU_H_



/**
 * This structure give the size of each of the external memories EBIi and DDRCS
 * @note all the sizes are in MEGA BYTES !!!
 */
struct ExtMemDescriptor
{
  unsigned int EBICS0Size;
  unsigned int EBICS1Size;
  unsigned int EBICS2Size;
  unsigned int EBICS3Size;
  unsigned int DDRCSSize;
};

/**
 * @brief This function will set the given translation Table into the MMU.
 * @param pTB [IN] The translation table pointer. (short descriptor). No actual Translation.
 */
void MMU_Set (unsigned int* pTB);

/**
 * \brief Initializes a MMU memory mapping, no translation activated according to the size of each external memories areas (EBI, DDRAM)
 * @param pDesc [IN] : external memory descriptor
 * \param pTB  [IN,OUT] : Address of the translation table.
 * @todo The external memories sizes should be checked !!
 */
void MMU_TB_Initialize(struct ExtMemDescriptor* pDesc, unsigned int *pTB);

/**
 * \brief Initializes the memory translation table & set the MMU with it.
 * \param pTB  Address of the translation table.
 * @deprecated use MMU_TB_Initialize() and MMU_Set() instead
 */
void MMU_Initialize(unsigned int *pTB);

//! The Memory descriptor table is defined in the linker script.
extern unsigned int MEMORY_TRANSLATION_TABLE_BASE;

#endif /*MMU_H_*/