/*
 * Copyright (C) 2012 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __FDT_H__
#define __FDT_H__

extern unsigned int of_get_dt_total_size(void *blob);
extern int check_dt_blob_valid(void *blob);
extern int fixup_chosen_node(void *blob, char *bootargs);
extern int fixup_memory_node(void *blob,
				unsigned int *mem_bank,
				unsigned int *mem_bank2,
				unsigned int *mem_size);
#endif /* #ifndef __FDT_H__ */
