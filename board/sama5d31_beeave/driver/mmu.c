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
#include "common.h"
#include "hardware.h"
#include "usart.h"
#include "debug.h"

#include "mmu.h"
#include "CP15.h"

//***************************************************
void MMU_Initialize(unsigned int *pTB)
  {
    struct ExtMemDescriptor desc =
      { 255, 255, 255, 255, 511};
    MMU_TB_Initialize (&desc, pTB);
    MMU_Set(pTB);
  }
//****************************************************
void MMU_TB_Initialize(struct ExtMemDescriptor* pDesc, unsigned int *pTB)
  {
    unsigned int index;
    unsigned int addr;

    //TODO : check pDesc sizes : EBICSi < 256 , DDRCSSize < 512 !!
    
    /* Reset table entries */
    for (index = 0; index < 4096; index++)
    pTB[index] = 0;

    /* section Boot (code + data)*/
    /* ROM address (after remap) 0x0000_0000*/
    pTB[0x000] = (0x000 << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 1 << 3)|// C bit : cachable => YES
    ( 1 << 2)|// B bit : write-back => YES
    ( 2 << 0);// Set as 1 Mbyte section
    
    /* section ROM (code + data) */
    /* ROM address (after remap) 0x0010_0000 */
    pTB[0x001] = (0x001 << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 1 << 2)|// B bit : write-back => YES
    ( 2 << 0);// Set as 1 Mbyte section

    /* section NFC SRAM  */
    /* SRAM address 0x0020_0000 */
    pTB[0x002] = (0x002 << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 1 << 2)|// B bit : write-back => YES
    ( 2 << 0);// Set as 1 Mbyte section

    /* section RAM 0 remapped in 0 ! => same attributs BUT the start RAM address.*/
    /* SRAM address (after remap) 0x0030_0000 */
    pTB[0x003] = (0x003 << 20)| // Physical Address
                 pTB[0x000];
    
    /* section NFC SRAM  */
    /* SRAM address 0x0040_0000 */
    for(addr = 0x4; addr < 0xB; addr++)
    pTB[addr] = (addr << 20)|   // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 1 << 2)|// B bit : write-back => YES
    ( 2 << 0);// Set as 1 Mbyte section

    /* section PERIPH */
    /* periph address 0xF000_0000 */
    pTB[0xF00] = (0xF00ul << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section PERIPH */
    /* periph address 0xF800_0000 */
    pTB[0xF80] = (0xF80ul << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section PERIPH */
    /* periph address 0xFFF0_0000 */
    pTB[0xFFF] = (0xFFFul << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section NFC */
    /* periph address 0x7000_0000 */
    for(addr = 0x700; addr < 0x800; addr++)
    pTB[addr] = (addr << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section EBI CS0 */
    /* periph address 0x1000_0000 */
    for(addr = 0x100; addr < (0x100 + pDesc->EBICS0Size); addr++)
    pTB[addr] = (addr << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section EBI CS1 */
    /* periph address 0x4000_0000 */
    for(addr = 0x400; addr < (0x400 + pDesc->EBICS1Size); addr++)
    pTB[addr] = (addr << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section EBI CS2 */
    /* periph address 0x5000_0000 */
    for(addr = 0x500; addr < (0x500 + pDesc->EBICS2Size); addr++)
    pTB[addr] = (addr << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section EBI CS3 */
    /* periph address 0x6000_0000 */
    for(addr = 0x600; addr < (0x600 + pDesc->EBICS3Size); addr++)
    pTB[addr] = (addr << 20)| // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 0 << 3)|// C bit : cachable => NO
    ( 0 << 2)|// B bit : write-back => NO
    ( 2 << 0);// Set as 1 Mbyte section

    /* section SDRAM/DDRAM */
    /* address 0x2000_0000 */
    for(addr = 0x200; addr < (0x200 + pDesc->DDRCSSize); addr++)
    pTB[addr] = (addr << 20)|   // Physical Address
    ( 3 << 10)|// Access in supervisor mode (AP)
    ( 1 << 12)|// TEX[0]
    ( 0xF << 5)|// Domain 0xF
    ( 1 << 4)|// (XN)
    ( 1 << 3)|// C bit : cachable => YES
    ( 1 << 2)|// B bit : write-back => YES
    ( 2 << 0);// Set as 1 Mbyte section

  }
//****************************************************************
void MMU_Set (unsigned int* pTB)
  {
    CP15_WriteTTB((unsigned int)pTB);
    /* Program the domain access register */
    CP15_WriteDomainAccessControl(0xC0000000); // only domain 15: access are not checked
  }
//****************************************************************
