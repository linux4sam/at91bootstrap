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
 */
#include "common.h"
#include "hardware.h"
#include "arch/at91_pmc.h"
#include "string.h"
#include "slowclk.h"
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"

#include "debug.h"

#ifdef CONFIG_AT91SAM9X5EK
#include "onewire_info.h"
#endif

/*
 * The new way of passing information: a list of tagged entries
 */

/* The list ends with an ATAG_NONE node. */
#define ATAG_NONE	0x00000000

struct tag_header {
	unsigned int size;
	unsigned int tag;
};

/* The list must start with an ATAG_CORE node */
#define ATAG_CORE	0x54410001

struct tag_core {
	unsigned int flags;		/* bit 0 = read-only */
	unsigned int pagesize;
	unsigned int rootdev;
};

/* it is allowed to have multiple ATAG_MEM nodes */
#define ATAG_MEM	0x54410002

struct tag_mem32 {
	unsigned int	size;
	unsigned int	start;	/* physical start address */
};

/* board serial number. "64 bits should be enough for everybody" */
#define ATAG_SERIAL	0x54410006

struct tag_serialnr {
	unsigned int low;
	unsigned int high;
};

/* board revision */
#define ATAG_REVISION	0x54410007

struct tag_revision {
	unsigned int rev;
};

/* command line: \0 terminated string */
#define ATAG_CMDLINE	0x54410009

struct tag_cmdline {
	char	cmdline[1];	/* this is the minimum size */
};

struct tag {
	struct tag_header hdr;
	union {
		struct tag_core		core;
		struct tag_mem32	mem;
		struct tag_serialnr	serialnr;
		struct tag_revision	revision;
		struct tag_cmdline	cmdline;
	} u;
};

#define tag_next(t)	((struct tag *)((unsigned int *)(t) + (t)->hdr.size))
#define tag_size(type)	((sizeof(struct tag_header) + sizeof(struct type)) >> 2)

#define IH_MAGIC	0x27051956	/* Image Magic Number		*/
#define IH_NMLEN	32		/* Image Name Length		*/

/*
 * Legacy format image header,
 * all data in network byte order (aka natural aka bigendian).
 */
typedef struct image_header {
	unsigned int	ih_magic;	/* Image Header Magic Number	*/
	unsigned int	ih_hcrc;	/* Image Header CRC Checksum	*/
	unsigned int	ih_time;	/* Image Creation Timestamp	*/
	unsigned int	ih_size;	/* Image Data Size		*/
	unsigned int	ih_load;	/* Data	 Load  Address		*/
	unsigned int	ih_ep;		/* Entry Point Address		*/
	unsigned int	ih_dcrc;	/* Image Data CRC Checksum	*/
	unsigned char	ih_os;		/* Operating System		*/
	unsigned char	ih_arch;	/* CPU architecture		*/
	unsigned char	ih_type;	/* Image Type			*/
	unsigned char	ih_comp;	/* Compression Type		*/
	unsigned char	ih_name[IH_NMLEN];	/* Image Name		*/
} image_header_t;

static struct tag *params = (struct tag *)(OS_MEM_BANK + 0x100);

static void setup_start_tag (void)
{
	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

static void setup_memory_tags (void)
{
	params->hdr.tag = ATAG_MEM;
	params->hdr.size = tag_size (tag_mem32);

	params->u.mem.start = OS_MEM_BANK; 
	params->u.mem.size = OS_MEM_SIZE; 

	params = tag_next (params);
}

static void setup_commandline_tag (char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}

#ifdef CONFIG_AT91SAM9X5EK
static void setup_serial_tag (void)
{
	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = get_sys_sn();
	params->u.serialnr.high= 0;
	params = tag_next (params);
}

static void setup_revision_tag(void)
{
	unsigned int rev = 0;

	rev = get_sys_rev();
	params->hdr.tag = ATAG_REVISION;
	params->hdr.size = tag_size (tag_revision);
	params->u.revision.rev = rev;
	params = tag_next (params);
}
#endif /* #ifdef CONFIG_AT91SAM9X5EK */

static void setup_end_tag (void)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

static void setup_boot_tags(void)
{
	/* Start tag */
	setup_start_tag();

	/* Mem tag */
	setup_memory_tags();

	/* Command line tag */
	setup_commandline_tag(LINUX_KERNEL_ARG_STRING);

#ifdef CONFIG_AT91SAM9X5EK
	/* System Rev tag */
	setup_revision_tag();
	
	/* Board Serial tag */
	setup_serial_tag();
#endif

	/* end tag */
	setup_end_tag();
}

int load_kernel(struct image_info *img_info)
{
	image_header_t	*image_header;
	unsigned int load_addr, image_size;
	unsigned int magic_number;
	unsigned int jump_addr = (unsigned int)img_info->dest;
	unsigned int tags_addr = (unsigned int)(OS_MEM_BANK + 0x100);
	int mach_type = MACH_TYPE;
	int ret;

	void (*kernel_entry)(int zero, int arch, unsigned int params);

#ifdef CONFIG_DATAFLASH
	ret = load_dataflash(img_info);
#endif

#ifdef CONFIG_NANDFLASH
	ret = load_nandflash(img_info);
#endif

#ifdef CONFIG_SDCARD
	ret = load_sdcard(img_info);
#endif
	if (ret != 0)
		return -1;

#ifdef CONFIG_SCLK
	slowclk_switch_osc32();
#endif

	/* Check the image header magic */
	image_header = (image_header_t *)jump_addr;
	magic_number = ntohl(image_header->ih_magic);
	dbg_log(1, "\n\rImage magic: %d is found.\n\r", magic_number);
#if 0
	if (magic_number != IH_MAGIC) {
		dbg_log(1, "** Bad image magic number found: %d\n\r", magic_number);
		return -1;
	}
#endif
	image_size = ntohl(image_header->ih_size);
	load_addr = ntohl(image_header->ih_load);
    
	dbg_log(1, "Image size: %d, load address: %d\n\r", image_size, load_addr);

#if 0
	if (image_header->ih_comp != 0) {
		dbg_log(1, "The compression type has not been supported yet\n\r");
		return -1;
	}
#endif
	kernel_entry = (void (*)(int, int, unsigned int))ntohl(image_header->ih_ep);

	dbg_log(1, "Relocating kernel image, dest: %d, src: %d\n\r",
		load_addr, jump_addr + sizeof(image_header_t));

	memcpy((void *)load_addr, (void *)(jump_addr + sizeof(image_header_t)), image_size);

	dbg_log(1, "... %d bytes data transferred\n\r", image_size);

	setup_boot_tags();

	dbg_log(1, "\n\rStarting linux kernel ..., machid: %d, tags: %d\n\r\n\r",
		mach_type, tags_addr);

	kernel_entry(0, mach_type, tags_addr);

	return 0;
}
