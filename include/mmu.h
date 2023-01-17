// Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifndef __MMU_H__
#define __MMU_H__

void mmu_tlb_init(unsigned int *tlb);
void mmu_enable(void);
void mmu_disable(void);

void mmu_configure(void *tlb);

#endif	/* #ifndef __MMU_H__ */
