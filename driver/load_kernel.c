/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2006, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
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
#include "board_hw_info.h"
#include "mon.h"
#include "tz_utils.h"

#include "debug.h"

#ifdef CMDLINE
char *bootargs = CMDLINE;
#endif

#ifdef CONFIG_OF_LIBFDT
static int setup_dt_blob(void *blob)
{
	unsigned int mem_bank = MEM_BANK;
	unsigned int mem_size = MEM_SIZE;
	int ret;

	if (check_dt_blob_valid(blob)) {
		dbg_info("DT: the blob is not a valid fdt\n");
		return -1;
	}

	dbg_info("\nUsing device tree in place at %d\n",
						(unsigned int)blob);

#ifdef CMDLINE
	if (bootargs) {
		char *p;

		/* set "/chosen" node */
		for (p = bootargs; *p == ' '; p++)
			;

		if (*p == '\0')
			return -1;

		ret = fixup_chosen_node(blob, p);
		if (ret)
			return ret;
	}
#endif

	ret = fixup_memory_node(blob, &mem_bank, &mem_size);
	if (ret)
		return ret;

	return 0;
}
#else
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
	unsigned int *params = (unsigned int *)(MEM_BANK + 0x100);

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

	memparam->start = MEM_BANK;
	memparam->size = MEM_SIZE;

	params = (unsigned int *)params + TAG_SIZE_MEM32;

	struct tag_cmdline *cmdparam = (struct tag_cmdline *)params;
	setup_commandline_tag(cmdparam, bootargs);

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

#if defined(CONFIG_LINUX_IMAGE)
/* Linux uImage Header */
#define LINUX_UIMAGE_MAGIC	0x27051956
struct linux_uimage_header {
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

/* Linux zImage Header */
#define	LINUX_ZIMAGE_MAGIC	0x016f2818
struct linux_zimage_header {
	unsigned int	code[9];
	unsigned int	magic;
	unsigned int	start;
	unsigned int	end;
};

int kernel_size(unsigned char *addr)
{
	struct linux_uimage_header *uimage_header
			= (struct linux_uimage_header *)addr;

	struct linux_zimage_header *zimage_header
			= (struct linux_zimage_header *)addr;
	unsigned int size = -1;
	unsigned int magic = swap_uint32(uimage_header->magic);

	if (magic == LINUX_UIMAGE_MAGIC)
		size = swap_uint32(uimage_header->size)
			+ sizeof(struct linux_uimage_header);

	if (zimage_header->magic == LINUX_ZIMAGE_MAGIC)
		size = zimage_header->end - zimage_header->start;

	if ((int)size < 0)
		return -1;

	return (int)size;
}

static int boot_image_setup(unsigned char *addr, unsigned int *entry)
{
	struct linux_zimage_header *zimage_header
			= (struct linux_zimage_header *)addr;

	struct linux_uimage_header *uimage_header
			= (struct linux_uimage_header *)addr;
	unsigned int src, dest;
	unsigned int size;
	unsigned int magic;

	dbg_loud("try zImage magic: %d is found\n", zimage_header->magic);
	if (zimage_header->magic == LINUX_ZIMAGE_MAGIC) {
		dbg_info("\nBooting zImage ......\n");
		*entry = ((unsigned int)addr + zimage_header->start);
		return 0;
	}

	magic = swap_uint32(uimage_header->magic);
	dbg_loud("try uImage magic: %d is found\n", magic);
	if (magic == LINUX_UIMAGE_MAGIC) {
		dbg_info("\nBooting uImage ......\n");

		if (uimage_header->comp_type != 0) {
			dbg_info("The uImage compress type not supported\n");
			return -1;
		}

		size = swap_uint32(uimage_header->size);
		dest = swap_uint32(uimage_header->load);
		src = (unsigned int)addr + sizeof(struct linux_uimage_header);

		dbg_info("Relocating kernel image, dest: %d, src: %d\n",
				dest, src);

		memcpy((void *)dest, (void *)src, size);

		dbg_info(" ...... %d bytes data transferred\n", size);

		*entry = swap_uint32(uimage_header->entry_point);
		return 0;
	}

	dbg_info("** Bad uImage magic: %d, zImage magic: %d\n",
			magic, zimage_header->magic);
	return -1;
}
#endif

static int load_kernel_image(struct image_info *image)
{
	int ret;

#if defined(CONFIG_DATAFLASH)
	ret = load_dataflash(image);
#elif defined(CONFIG_NANDFLASH)
	ret = load_nandflash(image);
#elif defined(CONFIG_SDCARD)
	ret = load_sdcard(image);
#else
#error "No booting media specified!"
#endif
	if (ret)
		return ret;

	return 0;
}

int load_kernel(struct image_info *image)
{
	unsigned char *addr = image->dest;
	unsigned int entry_point;
	unsigned int r2;
	unsigned int mach_type;
	int ret;

	void (*kernel_entry)(int zero, int arch, unsigned int params);

	ret = load_kernel_image(image);
	if (ret)
		return ret;

#ifdef CONFIG_SCLK
	slowclk_switch_osc32();
#endif

#if defined(CONFIG_LINUX_IMAGE)
	ret = boot_image_setup(addr, &entry_point);
#endif
	if (ret)
		return -1;

	kernel_entry = (void (*)(int, int, unsigned int))entry_point;

#ifdef CONFIG_OF_LIBFDT
	ret = setup_dt_blob((char *)image->of_dest);
	if (ret)
		return ret;

	mach_type = 0xffffffff;
	r2 = (unsigned int)image->of_dest;
#else
	setup_boot_params();

	mach_type = MACH_TYPE;
	r2 = (unsigned int)(MEM_BANK + 0x100);
#endif

	dbg_info("\nStarting linux kernel ..., machid: %d\n\n",
							mach_type);
#if defined(CONFIG_ENTER_NWD)
	monitor_init();

	init_loadkernel_args(0, mach_type, r2, (unsigned int)kernel_entry);

	dbg_info("Enter Normal World, Run Kernel at %d\n",
					(unsigned int)kernel_entry);

	enter_normal_world();
#else
	kernel_entry(0, mach_type, r2);
#endif

	return 0;
}
