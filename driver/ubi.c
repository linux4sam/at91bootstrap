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
#include "common.h"
#include "ubi.h"
#ifdef CONFIG_UBI_CRC32
#include "crc32.h"
#endif
#include "div.h"
#include "debug.h"
#include "nandflash.h"

#include <string.h>

#define UBI_CRC32_INIT         0xFFFFFFFFU
#define UBI_EC_HDR_MAGIC       0x55424923U
#define UBI_VID_HDR_MAGIC      0x55424921U
#define UBI_INTERNAL_VOL_START 0x7FFFEFFFU
#define UBI_UNUSED_PEB         0xFFFFFFFFU

enum {
	UBI_VID_DYNAMIC = 1,
	UBI_VID_STATIC  = 2
};

struct ec_header {
	unsigned int magic;
	unsigned char __unused1[12];
	unsigned int volid_header_offset;
	unsigned int data_offset;
	unsigned char __unused2[36];
	unsigned int hdr_crc;
};

struct volid_header {
	unsigned int magic;
	unsigned char version;
	unsigned char type;
	unsigned char copy;
	unsigned char compat;
	unsigned int id;
	unsigned int num;
	unsigned char padding1[4];
	unsigned int data_size;
	unsigned char __unused2[8];
	unsigned int data_crc;
	unsigned char __unused3[4];
	unsigned long long int seqnum;
	unsigned char __unused4[12];
	unsigned int hdr_crc;
};

#define UBI_EC_HDR_SIZE  sizeof(struct ec_header)
#define UBI_VID_HDR_SIZE sizeof(struct volid_header)

#ifdef CONFIG_UBI_CRC32
#define UBI_EC_HDR_SIZE_CRC  (UBI_EC_HDR_SIZE  - sizeof(unsigned int))
#define UBI_VID_HDR_SIZE_CRC (UBI_VID_HDR_SIZE - sizeof(unsigned int))
#endif

static int read_page(struct ubi_device *ubi,
		     unsigned int block,
		     unsigned int page,
		     unsigned char *dest) {
	if (nand_read_page(ubi->nand, block, page, 0, dest)) {
		dbg_info("UBI: Failed to read page %u in block %u!\n",
			 page, block);
		return -1;
	}

	return 0;
}

static int read_headers(struct ubi_device *ubi,
			unsigned int block,
			struct ec_header **ec_header,
			struct volid_header **vid_header) {
	struct ec_header *ec_hdr;
	struct volid_header *vid_hdr;
#ifdef CONFIG_UBI_CRC32
	unsigned int hdr_crc, crc;
#endif
	*ec_header = NULL;
	*vid_header = NULL;

	if (read_page(ubi, block, 0, ubi->pagebuf))
		return -1;

	ec_hdr = (struct ec_header *) ubi->pagebuf;
	if (swap_uint32(ec_hdr->magic) != UBI_EC_HDR_MAGIC) {
		if (swap_uint32(ec_hdr->magic) != 0xffffffffU)
			dbg_loud("UBI: Mismatch Erase-Counter Header magic"
				 " at PEB %u! (%x != %x)\n", block,
				 swap_uint32(ec_hdr->magic), UBI_EC_HDR_MAGIC);
		return -1;
	}
	*ec_header = ec_hdr;

#ifdef CONFIG_UBI_CRC32
	crc = crc32(UBI_CRC32_INIT, (const unsigned char *) ec_hdr,
		    UBI_EC_HDR_SIZE_CRC);
	hdr_crc = swap_uint32(ec_hdr->hdr_crc);

	if (hdr_crc != crc) {
		dbg_info("UBI: Bad Erase-Counter Header CRC"
			 " at PEB %u! (%x != %x)\n", block, hdr_crc, crc);
		return -1;
	}
#endif

	if (swap_uint32(ec_hdr->volid_header_offset) >= ubi->nand->pagesize) {
		unsigned int p;
		unsigned char *b;

		p = div(swap_uint32(ec_hdr->volid_header_offset),
			ubi->nand->pagesize);
		b = (unsigned char *) (ubi->pagebuf +
						    (p * ubi->nand->pagesize));
		if (read_page(ubi, block, p, b))
			return -1;

		vid_hdr = (struct volid_header *) b;
	} else {
		vid_hdr = (struct volid_header *) (ubi->pagebuf +
				     swap_uint32(ec_hdr->volid_header_offset));
	}

	if (swap_uint32(vid_hdr->magic) != UBI_VID_HDR_MAGIC) {
		if (swap_uint32(vid_hdr->magic) != 0xffffffffU)
			dbg_info("UBI: Mismatch Volume-ID Header magic"
				 " at PEB %u! (%x != %x)\n", block,
				 swap_uint32(vid_hdr->magic),
				 UBI_VID_HDR_MAGIC);
		return -1;
	}
	*vid_header = vid_hdr;

#ifdef CONFIG_UBI_CRC32
	crc = crc32(UBI_CRC32_INIT, (const unsigned char *) vid_hdr,
		    UBI_VID_HDR_SIZE_CRC);
	hdr_crc = swap_uint32(vid_hdr->hdr_crc);

	if (hdr_crc != crc) {
		dbg_info("UBI: Bad Volume-ID Header CRC"
			 " at PEB %u! (%x != %x)\n", block, hdr_crc, crc);
		return -1;
	}
#endif

	return 0;
}

static int read_leb(struct ubi_device *ubi,
		    unsigned int block,
		    struct ec_header *ec_header,
		    struct volid_header *vid_header,
		    unsigned int *length,
		    unsigned char *dest) {
	unsigned int l = 0, p, size, s;
	unsigned char *d = dest;
#ifdef CONFIG_UBI_CRC32
	unsigned int data_crc, crc;
#endif

	if (vid_header->type == UBI_VID_STATIC)
		size = swap_uint32(vid_header->data_size);
	else
		size = ubi->nand->blocksize -
					   swap_uint32(ec_header->data_offset);
	size = MIN(size, *length);

	p = div(swap_uint32(ec_header->data_offset), ubi->nand->pagesize);
	while ((size > 0) && (p < ubi->nand->pages_block)) {
		s = MIN(ubi->nand->pagesize, size);
		if (read_page(ubi, block, p, d))
			return -1;
		p++;
		d += s;
		size -= s;
		l += s;
	}

#ifdef CONFIG_UBI_CRC32
	crc = crc32(UBI_CRC32_INIT, dest, swap_uint32(vid_header->data_size));
	data_crc = swap_uint32(vid_header->data_crc);

	if (data_crc != crc) {
		dbg_info("UBI: Bad Volume-ID Data CRC"
			 " at PEB %u! (%x != %x)\n", block, data_crc, crc);
		return -1;
	}
#endif

	*length = l;
	return *length ? 0 : -1;
}

static int read_peb(struct ubi_device *ubi,
		    unsigned int block,
		    unsigned int *length,
		    unsigned char *dest,
		    unsigned int offset) {
	unsigned char *d = dest;
	struct ec_header *ec_hdr;
	struct volid_header *vid_hdr;

	if (read_headers(ubi, block, &ec_hdr, &vid_hdr)) {
		dbg_info("UBI: Failed to read Headers at block %u!\n", block);
		return -1;
	}

	if (offset == (unsigned int) -1) {
		unsigned int size, lebsize;

		lebsize = ubi->nand->blocksize -
					      swap_uint32(ec_hdr->data_offset);
		offset = swap_uint32(vid_hdr->num) * lebsize;

		if (*length < offset) {
			*length = 0;
			return 0;
		}

		*length -= offset;
		d += offset;

		size = swap_uint32(vid_hdr->data_size);
		if (vid_hdr->type != UBI_VID_STATIC)
			size = lebsize;
		size = MIN(size, *length);
		*length = size;
	}

	if (read_leb(ubi, block, ec_hdr, vid_hdr, length, dest + offset)) {
		dbg_info("UBI: Failed to read LEB at block %u!\n", block);
		return -1;
	}

	return *length ? 0 : -1;
}

static int check_peb(struct ubi_device *ubi,
		     unsigned int peb1,
		     unsigned int peb2) {
#ifdef CONFIG_UBI_CRC32
	unsigned int size, new, old;

	if (ubi->pebs[peb1].seqnum > ubi->pebs[peb2].seqnum) {
		new = peb1;
		old = peb2;
	} else {
		new = peb2;
		old = peb1;
	}

	/* Check for copy flag first... */
	if (!ubi->pebs[new].copy)
		return new;

	/* ... and for PEB consistency (if copy flag is set)... */
	if (read_peb(ubi, new, &size, ubi->blockbuf, 0)) {
		dbg_info("UBI: PEB %u is inconsistent!\n", new);
		return old;
	}

	return new;
#else
	/* Or simply pick up the one with higher sequence number,
	   if unable to check for PEB consistency. */
	return ubi->pebs[peb1].seqnum > ubi->pebs[peb2].seqnum ? peb1 : peb2;
#endif
}

int ubi_init(struct ubi_device *ubi, struct nand_info *nand)
{
	unsigned int peb, addr = UBI_ADDRESS;
	struct ubi_peb *a;

	ubi->nand = nand;

	ubi->firstpeb = div(UBI_OFFSET, nand->blocksize);
	ubi->numpebs = nand->numblocks - ubi->firstpeb;
	ubi->pebs = (struct ubi_peb *) addr;
	memset(ubi->pebs, 0xFF, ubi->numpebs * sizeof(struct ubi_peb));
	addr += (ubi->numpebs * sizeof(struct ubi_peb));

	memset(ubi->vols, 0x00, sizeof(struct ubi_peb *) *
					(UBI_MAX_VOLUMES + UBI_INT_VOL_COUNT));
	ubi->voltable = (struct ubi_volume *) addr;
	addr += (sizeof(struct ubi_volume) * UBI_MAX_VOLUMES);

	ubi->pagebuf = (unsigned char *) addr;
	addr += (nand->pagesize + nand->oobsize);
	ubi->blockbuf = (unsigned char *) addr;

	/* This fist loop parse the whole UBI partition: */
	for (peb = ubi->firstpeb; peb < ubi->numpebs; peb++) {
		struct ec_header *ec_hdr;
		struct volid_header *vid_hdr;

		/* - Skip bad blocks */
		if (nand_check_badblock(nand, peb, ubi->pagebuf))
			continue;

		/* - Check for PEB headers (to skip unused of invalid) */
		if (read_headers(ubi, peb, &ec_hdr, &vid_hdr))
			continue;

		/* - Registered valid PEBs */
		ubi->pebs[peb].id = swap_uint32(vid_hdr->id);
		ubi->pebs[peb].num = swap_uint32(vid_hdr->num);
		ubi->pebs[peb].data_crc = swap_uint32(vid_hdr->data_crc);
		ubi->pebs[peb].seqnum = swap_uint64(vid_hdr->seqnum);
		ubi->pebs[peb].copy = vid_hdr->copy;
		ubi->pebs[peb].next = NULL;
	}

	/* This second loop links the PEBs togethers,
	 * and check for duplicates LEBs. */
	for (peb = ubi->firstpeb; peb < ubi->numpebs; peb++) {
		unsigned int p;

		/* Ignore unused EB */
		if (ubi->pebs[peb].id == UBI_UNUSED_PEB)
			continue;

		/* Link PEB */
		for (p = peb + 1; p < ubi->numpebs; p++) {
			/* Ignore reserved UBI volumes
			 * (excepted volume-table) */
			if ((ubi->pebs[peb].id > UBI_INTERNAL_VOL_START) ||
			    (ubi->pebs[p].id != ubi->pebs[peb].id)) {
				continue;
			}

			/* peb is p */
			if (ubi->pebs[peb].num ==
			    (ubi->pebs[p].num + 1)) {
				ubi->pebs[p].next = &ubi->pebs[peb];
				continue;
			} else if (ubi->pebs[peb].num ==	/* p is peb */
				 (ubi->pebs[p].num - 1)) {
				ubi->pebs[peb].next = &ubi->pebs[p];
				continue;
			} else if (ubi->pebs[peb].num != ubi->pebs[p].num) { /* Both PEBs are not related */
				continue;
			}

			/* At this point both PEBs refers to the same LEB... */
			if (check_peb(ubi, peb, p) == peb) {
				ubi->pebs[p].id = UBI_UNUSED_PEB;
				dbg_info("UBI: New PEB for LEB %u is %u!"
					 "Old was %u.\n",
					 peb, ubi->pebs[peb].num, p);
			} else {
				ubi->pebs[peb].id = UBI_UNUSED_PEB;
				dbg_info("UBI: New PEB for LEB %u is %u!"
					 "Old was %u.\n",
					 p, ubi->pebs[p].num, peb);
			}
		}

		/* - And keep a trace of the first LEB for each volumes */
		if (ubi->pebs[peb].num == 0) {
			dbg_loud("UBI: First LEB for volume-id %u"
				 " is at PEB %x!\n", ubi->pebs[peb].id, peb);
			if (ubi->pebs[peb].id < UBI_INTERNAL_VOL_START)
				ubi->vols[ubi->pebs[peb].id] = &ubi->pebs[peb];
			else if (ubi->pebs[peb].id == UBI_INTERNAL_VOL_START)
				ubi->vols[UBI_MAX_VOLUMES] = &ubi->pebs[peb];
		}
	}

	a = ubi->vols[UBI_MAX_VOLUMES];
	while (a) {
		unsigned int size = sizeof(struct ubi_volume) * UBI_MAX_VOLUMES;

		peb = (unsigned int) (a - ubi->pebs);

		dbg_info("UBI: Loading volume-table %u at PEB %u%s!\n",
				ubi->pebs[peb].num, peb,
				ubi->pebs[peb].copy ? " with copy flag" : "");

		if (read_peb(ubi, peb, &size,
			     (unsigned char *) ubi->voltable, 0) == 0) {
			break;
		}

		dbg_info("UBI: Failed to read volume-table at PEB %u!\n", peb);
		a = a->next;
	}

	if (!a) {
		dbg_info("Warning: UBI: No valid volume-table found!"
			 " Keep going...\n");
	}

	return 0;
}

const char *ubi_getvolname(struct ubi_device *ubi, unsigned int id)
{
	if (id < UBI_INTERNAL_VOL_START)
		return (const char *) ubi->voltable[id].name;
	else if (id == UBI_INTERNAL_VOL_START)
		return "volume-table";

	return NULL;
}

unsigned int ubi_searchvolume(struct ubi_device *ubi, const char *volname)
{
	unsigned int i;

	for (i = 0; i < UBI_MAX_VOLUMES; i++) {
		if (!ubi->voltable[i].namesize || !*ubi->voltable[i].name ||
		    !ubi->vols[i])
			continue;

		if (strncmp(volname, (const char *) ubi->voltable[i].name,
		    ubi->voltable[i].namesize) == 0)
			return i;
	}

	return -1;
}

int ubi_loadimage(struct ubi_device *ubi,
		  unsigned int id,
		  unsigned int *length,
		  unsigned char *dest)
{
	struct ubi_peb *a = ubi->vols[id];

	unsigned int len = 0, peb = (unsigned int) (a - ubi->pebs);

	if (!ubi->vols[id])
		return -1;

	a = ubi->vols[id];
	while (a && len < (*length)) {
		unsigned int l = *length;

		peb = (unsigned int) (a - ubi->pebs);

		dbg_loud("UBI: Reading LEB %x at PEB %x for Volume-ID %u...\n",
			 a->num, peb, id);
		if (read_peb(ubi, peb, &l, dest, (unsigned int) -1))
			dbg_info("Warning: UBI: Failed to read PEB %u!"
				 " Keep going...\n", peb);

		a = a->next;
		len += l;
	}

	*length = len;
	return 0;
}
