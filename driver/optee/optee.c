// Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "debug.h"
#include "optee.h"
#include "types.h"
#include "string.h"

#define OPTEE_MAGIC             0x4554504f
#define OPTEE_VERSION           1
#define OPTEE_ARCH_ARM32        0
#define OPTEE_ARCH_ARM64        1

struct nw_params {
	unsigned int r1;
	unsigned int r2;
	void *nw_addr;
} __attribute__((packed));

static struct nw_params nw_params;

struct optee_header {
        u32 magic;
        u8 version;
        u8 arch;
        u16 flags;
        u32 init_size;
        u32 init_load_addr_hi;
        u32 init_load_addr_lo;
        u32 init_mem_usage;
        u32 paged_size;
} __attribute__((packed));

/*
 * Save r0, r1, r2 to be set when jumping to normal world at nw_addr.
 */
void optee_init_nw_params(void *nw_addr, unsigned int r0,
			  unsigned int r1, unsigned int r2)
{
	/* r0 is set to 0 when returning to normal world by OP-TEE */
	if (r0 != 0)
		dbg_loud("r0 must be set to 0 !");

	nw_params.r1 = r1;
	nw_params.r2 = r2;
	nw_params.nw_addr = nw_addr;
}

void optee_image_init(struct image_info *image)
{
	memset(image, 0, sizeof(*image));

	image->dest = (unsigned char *) CONFIG_OPTEE_JUMP_ADDR;

#ifdef CONFIG_SDCARD
	image->filename = CONFIG_OPTEE_IMAGE_NAME;
#endif

}

int optee_image_check(struct image_info *image, void **pagestore,
		      unsigned long *optee_size)
{
	struct optee_header *hdr = (struct optee_header *) image->dest;

	if ((u32) image->dest % 4) {
		dbg_loud("Invalid OP-TEE image alignment\n");
		return -1;
	}

	if (hdr->magic != OPTEE_MAGIC ||
	    hdr->version != OPTEE_VERSION ||
	    hdr->arch != OPTEE_ARCH_ARM32 ||
	    hdr->init_load_addr_lo != CONFIG_OPTEE_JUMP_ADDR ||
	    hdr->init_load_addr_hi != 0) {
		dbg_loud("Invalid OP-TEE image\n");
		return -1;
	}

	*optee_size = hdr->init_size + hdr->paged_size;

	if (*optee_size > CONFIG_OPTEE_IMG_SIZE) {
		dbg_loud("OP-TEE image size too big\n");
		return -1;
	}

	*pagestore = (void *) (image->dest + *optee_size);

	return 0;
}

#ifdef CONFIG_LOAD_SW
static void optee_load_image(void **page_store)
{
	int ret;
	unsigned long optee_size = 0;
	struct image_info image = {0};
	load_function load_func = get_image_load_func();

	optee_image_init(&image);

	ret = load_func(&image);
	if (ret) {
		dbg_loud("Failed to load OP-TEE\n");
		while(1);
	}

	ret = optee_image_check(&image, page_store, &optee_size);
	if (ret < 0)
		while(1);

	/*
	 * Since OP-TEE is loaded by default at 0x20000000 which is the DDR
	 * base, we can't copy it with the header offset. thus we load it at
	 * the load address and then memmove it in the correct location.
	 * OP-TEE is relatively small and the memmove overhead is really small.
	 */
	memmove(image.dest, image.dest + sizeof(struct optee_header),
		optee_size);
}
#else
static void optee_load_image(void **page_store) {}
#endif

void optee_start(void *pager, u32 r1, u32 dtb_addr, void *nw_addr);

void optee_load(void)
{
	void *page_store = NULL;

	optee_load_image(&page_store);

	/*
	 * If not overriden (by load_kernel for instance), set nw_addr to
	 * JUMP_ADDR and r2 to the normal world device tree
	 */
	if (nw_params.nw_addr == NULL)
		nw_params.nw_addr = (void *)JUMP_ADDR;

	dbg_info("Starting OP-TEE, Run at %x, Non-secure entry at %x\n",
		 CONFIG_OPTEE_JUMP_ADDR, nw_params.nw_addr);

	optee_start(page_store, nw_params.r1, nw_params.r2, nw_params.nw_addr);
}
