/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * m#define	SUCCESS	1
#define	FAILURE	0odification, are permitted provided that the following conditions are met:
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
 * File Name           : part.h
 * Object              :
 * Creation            : NLe Sep 28th 2006
 *-----------------------------------------------------------------------------
 */
#ifndef _PART_H
#define _PART_H

#define	FAILURE	0
#define	SUCCESS	1

#ifdef AT91SAM9260
#include "AT91SAM9260_inc.h"
#ifdef CONFIG_AT91SAM9260EK
#include "at91sam9260ek.h"
#endif
#ifdef CONFIG_AFEB9260
#include "afeb9260.h"
#endif
#endif

#ifdef AT91SAM9XE
/* For all SAM9XE chips 128/256/512/.. we use the XE128 file */
#include "AT91SAM9XE128_inc.h"
#include "at91sam9xeek.h"
#endif

#ifdef AT91SAM9G10
#include "AT91SAM9261_inc.h"
#include "at91sam9g10ek.h"
#endif

#ifdef AT91SAM9G20
#include "AT91SAM9260_inc.h"
#include "at91sam9g20ek.h"
#endif

#ifdef AT91SAM9G45
#include "AT91SAM9G45_inc.h"
#ifdef	CONFIG_AT91SAM9G45EKES
#include "at91sam9g45ekes.h"
#endif
#ifdef	CONFIG_AT91SAM9G45EK
#include "at91sam9g45ek.h"
#endif
#endif

#ifdef AT91SAM9M10
#include "AT91SAM9G45_inc.h"
#ifdef CONFIG_AT91SAM9M10EK
#include "at91sam9m10ek.h"
#endif
#ifdef CONFIG_AT91SAM9M10EKES
#include "at91sam9m10ekes.h"
#endif
#endif

#ifdef AT91SAM9261
#include "AT91SAM9261_inc.h"
#include "at91sam9261ek.h"
#endif

#ifdef AT91SAM9263
#include "AT91SAM9263_inc.h"
#include "at91sam9263ek.h"
#endif

#ifdef AT91CAP9
#include "AT91CAP9_inc.h"
#ifdef at91cap9adk
#include "at91cap9adk.h"
#elif at91cap9stk
#include "at91cap9stk.h"
#endif
#endif

#ifdef AT91SAM9RL
#include "AT91SAM9RL_inc.h"
#include "at91sam9rlek.h"
#endif

#ifdef AT91SAM9X5
#include "AT91SAM9GX5_inc.h"
#include "at91sam9x5ek.h"
#endif

#endif                          /* _PART_H */
