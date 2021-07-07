/*
 * Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __SECURE_H__
#define __SECURE_H__

struct image_info;


#define AT91_SECURE_MAGIC	0x0000aa55

/* the size of this structure MUST be equal to the size of an AES block */
typedef struct at91_secure_header {
	unsigned int		magic;
	unsigned int		file_size;
	unsigned int		reserved[2];
} at91_secure_header_t;

int secure_check(void *data);

#if defined(CONFIG_OCMS_STATIC)
void ocms_init_keys(void);
void ocms_enable(void);
#endif

#endif /* #ifdef __SECURE_H__ */
