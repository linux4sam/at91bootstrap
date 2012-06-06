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
#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef CONFIG_AT91SAM9260EK
#include "at91sam9260ek.h"
#endif

#ifdef CONFIG_AT91SAM9XEEK
#include "at91sam9xeek.h"
#endif

#ifdef CONFIG_AT91SAM9G10EK
#include "at91sam9g10ek.h"
#endif

#ifdef CONFIG_AT91SAM9G20EK
#include "at91sam9g20ek.h"
#endif

#ifdef CONFIG_AT91SAM9M10G45EK
#include "at91sam9m10g45ek.h"
#endif

#ifdef CONFIG_AT91SAM9261EK
#include "at91sam9261ek.h"
#endif

#ifdef CONFIG_AT91SAM9263EK
#include "at91sam9263ek.h"
#endif

#ifdef CONFIG_AT91SAM9RLEK
#include "at91sam9rlek.h"
#endif

#ifdef CONFIG_AT91SAM9X5EK
#include "at91sam9x5ek.h"
#endif

#ifdef CONFIG_AT91SAM9N12EK
#include "at91sam9n12ek.h"
#endif

#ifdef CONFIG_AT91SAMA5D3XEK
#include "at91sama5d3xek.h"
#endif

#endif /* #ifndef __BOARD_H__ */
