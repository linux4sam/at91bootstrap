/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Gaël PORTAY <gael.portay@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __UBI_H__
#define __UBI_H__

#include "nand.h"

/* Internal UBI volumes count */
#define UBI_INT_VOL_COUNT 1

/* The maximum number of volumes per one UBI device */
#define UBI_MAX_VOLUMES 128

/* The maximum volume name length */
#define UBI_VOL_NAME_MAX 127

struct ubi_volume {
	unsigned char __unused1[12];
	unsigned char type;
	unsigned char update;
	unsigned short int namesize;
	unsigned char name[UBI_VOL_NAME_MAX + 1];
	unsigned char __unused2[24];
	unsigned int crc;
};

struct ubi_peb {
	unsigned int id;
	unsigned int num;
	unsigned char copy;
	unsigned int data_crc;
	unsigned long long int seqnum;
	struct ubi_peb *next;
};

struct ubi_device {
	struct nand_info *nand;
	unsigned int firstpeb;
	unsigned int numpebs;
	struct ubi_peb *pebs;
	struct ubi_peb *vols[UBI_MAX_VOLUMES + UBI_INT_VOL_COUNT];
	struct ubi_volume *voltable;
	int leb_start;
	int volid_header_offset;
	unsigned char *pagebuf;
	unsigned char *blockbuf;
};

int ubi_init(struct ubi_device *ubi, struct nand_info *nand);

int ubi_loadimage(struct ubi_device *ubi,
		  unsigned int id,
		  unsigned int *length,
		  unsigned char *dest);

const char *ubi_getvolname(struct ubi_device *ubi, unsigned int id);
unsigned int ubi_searchvolume(struct ubi_device *ubi, const char *volname);

#endif /* #ifndef __UBI_H__ */

