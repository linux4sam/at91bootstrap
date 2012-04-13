#include "common.h"
#include "hardware.h"
#include "arch/at91_pmc.h"
#include "string.h"
#include "setup.h"
#include "dataflash.h"
#include "nandflash.h"
#include "sdcard.h"

#include "debug.h"

#ifdef CONFIG_AT91SAM9X5EK
#include "onewire_info.h"
#endif

#define IH_MAGIC	0x27051956	/* Image Magic Number		*/
#define IH_NMLEN	32		/* Image Name Length		*/

/*
 * Legacy format image header,
 * all data in network byte order (aka natural aka bigendian).
 */
typedef struct image_header {
	uint32_t	ih_magic;	/* Image Header Magic Number	*/
	uint32_t	ih_hcrc;	/* Image Header CRC Checksum	*/
	uint32_t	ih_time;	/* Image Creation Timestamp	*/
	uint32_t	ih_size;	/* Image Data Size		*/
	uint32_t	ih_load;	/* Data	 Load  Address		*/
	uint32_t	ih_ep;		/* Entry Point Address		*/
	uint32_t	ih_dcrc;	/* Image Data CRC Checksum	*/
	uint8_t		ih_os;		/* Operating System		*/
	uint8_t		ih_arch;	/* CPU architecture		*/
	uint8_t		ih_type;	/* Image Type			*/
	uint8_t		ih_comp;	/* Compression Type		*/
	uint8_t		ih_name[IH_NMLEN];	/* Image Name		*/
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
	struct tag_serialnr serialnr;

	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = get_sys_sn;
	params->u.serialnr.high= 0;
	params = tag_next (params);
}

static void setup_revision_tag(void)
{
	u32 rev = 0;

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

void load_kernel(void)
{
#if 0
	unsigned long	load_addr, image_size;
	image_header_t	*image_header;
	unsigned long	magic_number;
	
	void (*kernel_entry)(int zero, int arch, uint params);
#endif

#ifdef CONFIG_DATAFLASH
	load_dataflash((unsigned int)IMG_ADDRESS, (unsigned int)IMG_SIZE, (unsigned char *)JUMP_ADDR);
#endif

#ifdef CONFIG_NANDFLASH
	load_nandflash((unsigned int)IMG_ADDRESS, (unsigned int)IMG_SIZE, (unsigned char *)JUMP_ADDR);
#endif

#ifdef CONFIG_SDCARD
	load_sdcard((void *)JUMP_ADDR);
#endif
	setup_boot_tags();

	writel(0xffffffff, ATMEL_BASE_PMC + AT91_PMC_PCER1);

///* enable all clocks unmanaged by Linux */
//(*(volatile unsigned int *)(0xfffffd00)) = (0xffffffff);
/* enable lcd clock */
//(*(volatile unsigned int *)(0xfffffc00)) = (0x8);
/* special configuration for usb certification */
#if 0
reg = (*(volatile unsigned int *)(0xF0038034));
reg &= 0xfff999ff;
reg |= 0x00011107;
(*(volatile unsigned int *)(0xF0038034)) = reg;
reg = (*(volatile unsigned int *)(0xF0038038));
reg &= 0xffffffcc;
reg |= 0x00000344;
(*(volatile unsigned int *)(0xF0038038)) = reg;
#endif
#if 0
	/* Check the image header magic */
	image_header = (image_header_t *)JUMP_ADDR;
	magic_number = ntohl(image_header->ih_magic);
	dbg_log(1, "image magic number found: %d\n\r", magic_number);
#if 0
	if (magic_number != IH_MAGIC) {
		dbg_log(1, "** Bad image magic number found: %d\n\r", magic_number);
		return;
	}
#endif
	image_size = ntohl(image_header->ih_size);
	load_addr = ntohl(image_header->ih_load);
    
	dbg_log(1, "Image size: %d, load_addr: %x\n\r",	image_size, load_addr);

#if 0
	if (hdr->ih_comp != 0) {
		dbg_log(1, "The compression type has not been supported yet\n\r");
		return;
	}
#endif
	kernel_entry = (void (*)(int, int, uint))ntohl(image_header->ih_ep);

	dbg_log(1, "Load_kernel: relocating kernel image, dest: %x, src: %x, image_size: %d, machid: %d\n\r",  
			load_addr, (unsigned long)JUMP_ADDR + sizeof (image_header_t), 
			image_size, MACH_TYPE);

	memcpy((void *)load_addr, 
		(void *)((unsigned long)JUMP_ADDR + sizeof (image_header_t)),
		image_size);

	dbg_log(1, "... %d bytes data transferred\n\r", image_size);

	setup_boot_tags();

	dbg_log(1, "\n\rStarting linux kernel ..., machid: %d, tags: %x\n\r\n\r", 
		MACH_TYPE, (OS_MEM_BANK + 0x100));

	kernel_entry(0, MACH_TYPE, (unsigned int)(OS_MEM_BANK + 0x100));
#endif
}

