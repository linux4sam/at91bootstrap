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
#include "fdt.h"
#include "onewire_info.h"

#include "debug.h"

#ifdef CONFIG_OF_LIBFDT

static int fixup_chosen_node(void *blob, char *bootargs)
{
	char *p;
	int  ret;

	if (!bootargs)
		return -1;

	/* eat leading white space */
	for (p = bootargs; *p == ' '; p++)
		;

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return -1;

	ret = of_fixup_chosen_node(blob, p);
	if (ret)
		return ret;

	return 0;
}

#define CONFIG_NR_DRAM_BANKS	1
static int fixup_memory_node(void *blob)
{
	int bank;
	unsigned int start[CONFIG_NR_DRAM_BANKS];
	unsigned int size[CONFIG_NR_DRAM_BANKS];
	int ret;

	for (bank = 0; bank < CONFIG_NR_DRAM_BANKS; bank++) {
		start[bank] = OS_MEM_BANK;
		size[bank] = OS_MEM_SIZE;
	}

	ret = of_fixup_memory_node(blob, start, size, CONFIG_NR_DRAM_BANKS);

	return ret;
}

static int setup_dt_blob(void *blob)
{
	unsigned int of_size;
	char *bootargs = LINUX_KERNEL_ARG_STRING;
	int ret;

	if (of_check_dt_header(blob)) {
		dbg_log(1, "DT: the blob is not a valid fdt\n\r");
		return -1;
	}

	ret = of_expand_blob(blob, &of_size);
	if (ret)
		return ret;

	dbg_log(1, "\n\rDT: Using Device Tree in place at %d, end %d\n\r",
			(unsigned int)blob, (unsigned int)blob + of_size - 1);

	ret = fixup_chosen_node(blob, bootargs);
	if (ret)
		return ret;

	ret = fixup_memory_node(blob);
	if (ret)
		return ret;

	return 0;
}

static void setup_boot_params(void) {}

#else
static int setup_dt_blob(void *blob)
{
	return 0;
}

#define TAG_FLAG_NONE		0x00000000
#define TAG_FLAG_CORE		0x54410001
#define TAG_FLAG_MEM		0x54410002
#define TAG_FLAG_SERIAL		0x54410006
#define TAG_FLAG_REVISION	0x54410007
#define TAG_FLAG_CMDLINE	0x54410009

#define	TAG_SIZE_HEADER		8
#define TAG_SIZE_CORE		5
#define TAG_SIZE_MEM32		4
#define TAG_SIZE_SERIAL		4
#define TAG_SIZE_REVISION	3

struct tag_header {
	unsigned int	size;
	unsigned int	tag;
};

struct tag_core {
	struct tag_header	header;
	unsigned int		flags;
	unsigned int		pagesize;
	unsigned int		rootdev;
};

struct tag_mem32 {
	struct tag_header	header;
	unsigned int		size;
	unsigned int		start;
};

struct tag_serial {
	struct tag_header	header;
	unsigned int		low;
	unsigned int		high;
};

struct tag_revision {
	struct tag_header	header;
	unsigned int		version;
};

struct tag_cmdline {
	struct tag_header	header;
	char			cmdline[1];
};

struct tag_none {
	struct tag_header	header;
};

static void setup_commandline_tag(struct tag_cmdline *params,
						char *commandline)
{
	char *p;

	if (!commandline)
		return;

	for (p = commandline; *p == ' '; p++)
		;

	if (*p == '\0')
		return;

	params->header.tag = TAG_FLAG_CMDLINE;
	params->header.size = (TAG_SIZE_HEADER + strlen(p) + 1 + 4) >> 2;

	strcpy(params->cmdline, p);
}

static void setup_boot_params(void)
{
	unsigned int *params = (unsigned int *)(OS_MEM_BANK + 0x100);

	struct tag_core *coreparam = (struct tag_core *)params;
	coreparam->header.tag = TAG_FLAG_CORE;
	coreparam->header.size = TAG_SIZE_CORE;

	coreparam->flags = 0;
	coreparam->pagesize = 0;
	coreparam->rootdev = 0;

	params = (unsigned int *)params + TAG_SIZE_CORE;

	struct tag_mem32 *memparam = (struct tag_mem32 *)params;
	memparam->header.tag = TAG_FLAG_MEM;
	memparam->header.size = TAG_SIZE_MEM32;

	memparam->start = OS_MEM_BANK;
	memparam->size = OS_MEM_SIZE;

	params = (unsigned int *)params + TAG_SIZE_MEM32;

	struct tag_cmdline *cmdparam = (struct tag_cmdline *)params;
	setup_commandline_tag(cmdparam, LINUX_KERNEL_ARG_STRING);

	params = (unsigned int *)params + cmdparam->header.size;

#ifdef CONFIG_LOAD_ONE_WIRE
	struct tag_revision *revparam = (struct tag_revision *)params;
	revparam->header.tag = TAG_FLAG_REVISION;
	revparam->header.size = TAG_SIZE_REVISION;
	revparam->version = get_sys_rev();

	params = (unsigned int *)params + TAG_SIZE_REVISION;

	struct tag_serial *serialparam = (struct tag_serial *)params;
	serialparam->header.tag = TAG_FLAG_SERIAL;
	serialparam->header.size = TAG_SIZE_SERIAL;
	serialparam->low = get_sys_sn();
	serialparam->high = 0;

	params = (unsigned int *)params + TAG_SIZE_SERIAL;
#endif

	/* end tag */
	struct tag_none * noneparam = (struct tag_none *)params;
	noneparam->header.tag = TAG_FLAG_NONE;
	noneparam->header.size = 0;
}
#endif /* #ifdef CONFIG_OF_LIBFDT */

/* Kernel Image Header */
#define KERNEL_IMAGE_MAGIC	0x27051956

struct kernel_image_header {
	unsigned int	magic;
	unsigned int	header_crc;
	unsigned int	time;
	unsigned int	size;
	unsigned int	load;
	unsigned int	entry_point;
	unsigned int	data_crc;
	unsigned char	os_type;
	unsigned char	arch;
	unsigned char	image_type;
	unsigned char	comp_type;
	unsigned char	name[32];
};

int load_kernel(struct image_info *image)
{
	struct kernel_image_header *image_header;
	unsigned int load_addr, image_size;
	unsigned int magic_number;
	unsigned int jump_addr = (unsigned int)image->dest;
	unsigned int r2;
	unsigned int mach_type;
	int ret;

	void (*kernel_entry)(int zero, int arch, unsigned int params);

#ifdef CONFIG_DATAFLASH
	ret = load_dataflash(image);
#endif

#ifdef CONFIG_NANDFLASH
	ret = load_nandflash(image);
#endif

#ifdef CONFIG_SDCARD
	ret = load_sdcard(image);
#endif
	if (ret != 0)
		return ret;

#ifdef CONFIG_SCLK
	slowclk_switch_osc32();
#endif

	image_header = (struct kernel_image_header *)jump_addr;
	magic_number = ntohl(image_header->magic);
	dbg_log(1, "\n\rImage magic: %d is found.\n\r", magic_number);
	if (magic_number != KERNEL_IMAGE_MAGIC) {
		dbg_log(1, "** Bad image magic number found: %d\n\r",
						magic_number);
		return -1;
	}

	image_size = ntohl(image_header->size);
	load_addr = ntohl(image_header->load);

	dbg_log(1, "Image size: %d, load address: %d\n\r",
				image_size, load_addr);

	if (image_header->comp_type != 0) {
		dbg_log(1, "The comp type has not been supported\n\r");
		return -1;
	}
	kernel_entry = (void (*)(int, int, unsigned int))
					ntohl(image_header->entry_point);

	dbg_log(1, "Relocating kernel image, dest: %d, src: %d\n\r",
		load_addr, jump_addr + sizeof(struct kernel_image_header));

	memcpy((void *)load_addr, (void *)(jump_addr
			+ sizeof(struct kernel_image_header)), image_size);

	dbg_log(1, "... %d bytes data transferred\n\r", image_size);

	if (image->of) {
		ret = setup_dt_blob((char *)image->of_dest);
		if (ret)
			return ret;

		mach_type = 0xffffffff;
		r2 = (unsigned int)image->of_dest;
	} else {
		setup_boot_params();

		mach_type = MACH_TYPE;
		r2 = (unsigned int)(OS_MEM_BANK + 0x100);
	}

	dbg_log(1, "\n\rStarting linux kernel ..., machid: %d\n\r\n\r",
							mach_type);

	kernel_entry(0, mach_type, r2);

	return 0;
}
