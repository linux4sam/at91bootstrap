/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Ulf Samuelsson <ulf.samuelsson@atmel.com>
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
 * ----------------------------------------------------------------------------
 * File Name           : ddr2.c
 * Object              :
 * Creation            :
 *-----------------------------------------------------------------------------
 */
#include "../include/ddr2.h"
#include "../include/part.h"
#include "../include/main.h"

#ifdef CONFIG_DDR2

/* Write DDR2 register */
static inline void write_ddr2(unsigned int offset, const unsigned int value)
{
}

/* Read DDR2 registers */
static inline unsigned int read_ddr2(unsigned int offset)
{
    return 0;
}

//*----------------------------------------------------------------------------
//* \fn    ddr2_init
//* \brief Initialize the DDR2 Controller
//*----------------------------------------------------------------------------
int ddr2_init(unsigned int sdramc_cr, unsigned int sdramc_tr)
{
    return 0;
}

#endif                          /* CONFIG_DDR2 */
