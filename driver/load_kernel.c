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

#ifdef CONFIG_LOAD_ANDROID
#ifdef CONFIG_SAMA5D3XEK
#ifdef CONFIG_NANDFLASH
static char *cmd_line_android_pda = "console=ttyS0,115200 " \
		"mtdparts=atmel_nand:8M(bootstrap/kernel),125M(system)," \
		"-(userdata) " \
		"ubi.mtd=1 ubi.mtd=2 rw root=ubi0:system rootfstype=ubifs "\
		"init=/init "\
		"androidboot.hardware=sama5d3x-pda androidboot.console=ttyS0";

static char *cmd_line_android = "console=ttyS0,115200 " \
		"mtdparts=atmel_nand:8M(bootstrap/kernel),125M(system)," \
		"-(userdata) " \
		"ubi.mtd=1 ubi.mtd=2 rw root=ubi0:system rootfstype=ubifs " \
		"init=/init " \
		"androidboot.hardware=sama5d3x-ek androidboot.console=ttyS0";
#endif
#ifdef CONFIG_SDCARD
static char *cmd_line_android_pda = "console=ttyS0,115200 " \
		"root=/dev/mmcblk0p2 rw rootwait init=/init " \
		"androidboot.hardware=sama5d3x-pda androidboot.console=ttyS0";

static char *cmd_line_android = "console=ttyS0,115200 " \
		"root=/dev/mmcblk0p2 rw rootwait init=/init " \
		"androidboot.hardware=sama5d3x-ek androidboot.console=ttyS0";
#endif
#endif /* #ifdef CONFIG_SAMA5D3XEK */
#endif /* #ifdef CONFIG_LOAD_ANDROID */

#ifdef CONFIG_OF_LIBFDT

static int setup_dt_blob(void *blob)
{
	char *bootargs = LINUX_KERNEL_ARG_STRING;
	char *p;
	unsigned int mem_bank = MEM_BANK;
	unsigned int mem_size = MEM_SIZE;
	int ret;

	if (check_dt_blob_valid(blob)) {
		dbg_info("DT: the blob is not a valid fdt\n");
		return -1;
	}

	dbg_info("\nUsing device tree in place at %d\n",
						(unsigned int)blob);

#if defined(CONFIG_LOAD_ANDROID) && defined(CONFIG_SAMA5D3XEK)
	if (get_dm_sn() == BOARD_ID_PDA_DM)
		bootargs = cmd_line_android_pda;
	else
		bootargs = cmd_line_android;
#endif

	/* set "/chosen" node */
	for (p = bootargs; *p == ' '; p++)
		;

	if (*p == '\0')
		return -1;

	ret = fixup_chosen_node(blob, p);
	if (ret)
		return ret;

	ret = fixup_memory_node(blob, &mem_bank, &mem_size);
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

#if defined(CONFIG_LINUX_UIMAGE)
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

static int boot_uimage_setup(unsigned char *addr, unsigned int *entry)
{
	struct linux_uimage_header *image_header
			= (struct linux_uimage_header *)addr;
	unsigned int src, dest;
	unsigned int size;
	unsigned int magic;

	dbg_info("\nBooting uImage ......\n");
	magic = swap_uint32(image_header->magic);
	dbg_info("uImage magic: %d is found\n", magic);
	if (magic != LINUX_UIMAGE_MAGIC) {
		dbg_info("** Bad uImage magic found: %d\n", magic);
		return -1;
	}

	if (image_header->comp_type != 0) {
		dbg_info("The uImage compress type not supported\n");
		return -1;
	}

	size = swap_uint32(image_header->size);
	dest = swap_uint32(image_header->load);
	src = (unsigned int)addr + sizeof(struct linux_uimage_header);

	dbg_info("Relocating kernel image, dest: %d, src: %d\n", dest, src);

	memcpy((void *)dest, (void *)src, size);

	dbg_info(" ...... %d bytes data transferred\n", size);

	*entry = swap_uint32(image_header->entry_point);

	return 0;
}

unsigned int kernel_size(unsigned char *addr)
{
	struct linux_uimage_header *image_header
		= (struct linux_uimage_header *)addr;

	return swap_uint32(image_header->size)
			+ sizeof(struct linux_uimage_header);
}

#elif defined(CONFIG_LINUX_ZIMAGE)

#define	LINUX_ZIMAGE_MAGIC	0x016f2818

struct linux_zimage_header {
	unsigned int	code[9];
	unsigned int	magic;
	unsigned int	start;
	unsigned int	end;
};

static int boot_zimage_setup(unsigned char *addr, unsigned int *entry)
{
	struct linux_zimage_header *image_header
			= (struct linux_zimage_header *)addr;

	dbg_info("\nBooting zImage ......\n");
	dbg_info("zImage magic: %d is found\n", image_header->magic);
	if (image_header->magic != LINUX_ZIMAGE_MAGIC) {
		dbg_info("** Bad zImage magic found: %d\n",
					image_header->magic);
		return -1;
	}

	*entry = ((unsigned int)addr + image_header->start);

	return 0;
}

unsigned int kernel_size(unsigned char *addr)
{
	struct linux_zimage_header *image_header
		= (struct linux_zimage_header *)addr;

	return image_header->end - image_header->start;
}
#else
#error "No Linux image type provided!"
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

#if defined(CONFIG_LINUX_UIMAGE)
	ret = boot_uimage_setup(addr, &entry_point);
#elif defined(CONFIG_LINUX_ZIMAGE)
	ret = boot_zimage_setup(addr, &entry_point);
#else
#error "No Linux image type provided!"
#endif
	if (ret)
		return -1;

	kernel_entry = (void (*)(int, int, unsigned int))entry_point;

	if (image->of) {
		ret = setup_dt_blob((char *)image->of_dest);
		if (ret)
			return ret;

		mach_type = 0xffffffff;
		r2 = (unsigned int)image->of_dest;
	} else {
		setup_boot_params();

		mach_type = MACH_TYPE;
		r2 = (unsigned int)(MEM_BANK + 0x100);
	}

	dbg_info("\nStarting linux kernel ..., machid: %d\n\n",
							mach_type);

	kernel_entry(0, mach_type, r2);

	return 0;
}
