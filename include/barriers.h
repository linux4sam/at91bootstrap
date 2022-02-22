//Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifndef ARM_BARRIERS_H_
#define ARM_BARRIERS_H_

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

void dsb(void);

#if defined(CONFIG_CORE_ARM926EJS)

static inline void dmb(void)
{
	asm("" ::: "memory");
}

static inline void isb(void)
{
	asm("" ::: "memory");
}

#elif defined(CONFIG_CORE_CORTEX_A5)

static inline void dmb(void)
{
	asm("dmb" ::: "memory");
}

static inline void isb(void)
{
	asm("isb" ::: "memory");
}

#endif

#endif /* ARM_BARRIERS_H_ */
