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
	asm volatile ("" ::: "memory");
}

static inline void isb(void)
{
	asm volatile ("" ::: "memory");
}

#elif defined(CONFIG_CORE_CORTEX_A5) || defined(CONFIG_CORE_CORTEX_A7)

static inline void dmb(void)
{
	asm volatile ("dmb" ::: "memory");
}

static inline void isb(void)
{
	asm volatile ("isb" ::: "memory");
}

#endif

#endif /* ARM_BARRIERS_H_ */
