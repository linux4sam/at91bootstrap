#include "main.h"
#include "debug.h"
#include "dbgu.h"
#include "linux_tags.h"
#include "dataflash.h"
#include "nandflash.h"

#ifdef CONFIG_LOAD_LINUX

#ifdef WINCE

#ifdef CONFIG_AT91SAM9260EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9261EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9263EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9RLEK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9G10EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9G20EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9G45EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=128M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=128M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=128M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9M10EK
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9G45EKES
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=128M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=128M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=128M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif
#ifdef CONFIG_AT91SAM9M10EKES
#ifdef CONFIG_DATAFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_NANDFLASH
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 mtdparts=atmel_nand:4M(bootstrap),60M(rootfs),-(spare) root=/dev/mtdblock1 rw rootfstype=jffs2"
#endif
#ifdef CONFIG_SDCARD
#define LINUX_KERNEL_ARG_STRING "mem=64M console=ttyS0,115200 root=/dev/mmcblk0p2 rootdelay=2"
#endif
#endif

#endif                          /* WINCE */

#define BIN_LOAD_ADDR (OS_MEM_BANK + 0x2000000)
#define IMAGE_MAGIC 0x27051956

size_t strlen(const char *str);

char *strcpy(char *dst, const char *src);

void *memcpy(void *dst, const void *src, size_t cnt);

#if 0
#ifndef CONFIG_THUMB
static inline unsigned int get_cp15(void)
{
    unsigned int value;

    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0":"=r"(value));

    return value;
}

static inline void set_cp15(unsigned int value)
{
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0"::"r"(value));
}

static inilne unsigned int get_cpsr(void)
{
    unsigned int value;

    __asm__ __volatile__("mrs %0, cpsr":"=r"(value));

    return value;
}

static inline void set_cpsr(unsigned int value)
{
    __asm__ __volatile__("msr cpsr_c, %1"::"r"(value));
}

#else
static inline unsigned int get_cp15(void);

static inline void set_cp15(unsigned int value);

static inilne unsigned int get_cpsr(void);

static inline void set_cpsr(unsigned int value);
#endif

#endif

#if 0
static inline unsigned int get_cp15(void);

static inline void set_cp15(unsigned int value);

static inline unsigned int get_cpsr(void);

static inline void set_cpsr(unsigned int value);
#endif
extern inline void disable_icache(void);

extern inline void disable_dcache(void);

extern inline void disable_irq(void);

extern inline void flush_idcache(void);

typedef struct image_header {
    unsigned long ih_magic;
    unsigned long ih_hcrc;
    unsigned long ih_time;
    unsigned long ih_size;
    unsigned long ih_load;
    unsigned long ih_ep;
    unsigned long ih_dcrc;
    unsigned char ih_os;
    unsigned char ih_arch;
    unsigned char ih_type;
    unsigned char ih_comp;
    unsigned char ih_name[32];
} image_header_t;

static long ntohl(unsigned long dat)
{
    return (((dat & 0x000000FF) << 24)
            | ((dat & 0x0000FF00) << 8)
            | ((dat & 0xFF000000) >> 24)
            | ((dat & 0x00FF0000) >> 8)
        );
}

static void setup_cmdline_tag(struct tag *tag, char *commandline)
{
    char *p;

    //if (!commandline)
    //    return;

    /*
     * eat leading white space 
     */
    for (p = commandline; *p == ' '; p++) ;

    /*
     * skip non-existent command lines so the kernel will still
     * * use its default command line.
     */
    if (*p == '\0')
        return;

    tag->hdr.tag = ATAG_CMDLINE;
    tag->hdr.size = (sizeof (struct tag_header) + strlen(p) + 1 + 4) >> 2;
    strcpy(tag->u.cmdline.cmdline, p);
}

void clean_environment()
{
#ifndef WINCE
    /*
     * Disable ARM Core interrupt 
     */
    disable_irq();
#if 0
    tmp = get_cpsr;
    tmp |= 0xc0;
    set_cpsr(tmp);
#endif

    /*
     * Turen off I/D cache 
     */
    disable_icache();
    disable_dcache();
    /*
     * Flush I/D cache 
     */
    flush_idcache();

#if 0
    /*
     * disable interrupt 
     */
    dbg_log(1, "Disable interrupt...\n\r");
    __asm__ __volatile__("mrs %0, cpsr\n"
                         "orr %1, %0, #0xc0\n"
                         "msr cpsr_c, %1":"=r"(old), "=r"(tmp)
                         ::"memory");

#define C1_IC (1 << 12)         /* ICache OFF/ON */
#define C1_DC (1 << 2 )         /* DCache OFF/ON */
    dbg_log(1, "Process Cache ...\n\r");
    /*
     * turn off I/D cache 
     */
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0":"=r"(i));

    i &= ~(C1_DC | C1_IC);
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0"::"r"(i));

    i = 0;
    __asm__ __volatile__("mcr p15, 0, %0, c7, c7, 0"::"r"(i));

    dbg_log(1, "End clean environment...\n\r");
#endif
#endif
}

//struct tag *tags = (struct tag *)(OS_MEM_BANK + 0x100);

void setup_tags()
{
    struct tag *tag = (struct tag *)(OS_MEM_BANK + 0x100);

    /*
     * start tag 
     */
    tag->hdr.tag = ATAG_CORE;
    tag->hdr.size = tag_size(tag_core);
    tag->u.core.flags = 0;
    tag->u.core.pagesize = 0;
    tag->u.core.rootdev = 0;
    tag = tag_next(tag);

    /*
     * mem tag 
     */
    tag->hdr.tag = ATAG_MEM;
    tag->hdr.size = tag_size(tag_mem32);
    tag->u.mem.start = OS_MEM_BANK;
    tag->u.mem.size = OS_MEM_SIZE;
    tag = tag_next(tag);

    setup_cmdline_tag(tag, LINUX_KERNEL_ARG_STRING);
    tag = tag_next(tag);

    /*
     * end tag 
     */
    tag->hdr.tag = ATAG_NONE;
    tag->hdr.size = 0;
}

void LoadLinux()
{
    unsigned long ep, load_addr, len;

    void load_SDCard();

    void (*theKernel) (int zero, int arch, unsigned int params);

    image_header_t *hdr;

#ifdef CONFIG_DATAFLASH
    load_df(AT91C_SPI_PCS_DATAFLASH, IMG_ADDRESS, IMG_SIZE, JUMP_ADDR);
#endif
#ifdef CONFIG_NANDFLASH
    read_nandflash((unsigned char *)JUMP_ADDR, (unsigned long)IMG_ADDRESS,
                   (int)IMG_SIZE);
#endif
#ifdef CONFIG_SDCARD
    load_SDCard();
#endif

    hdr = (image_header_t *) JUMP_ADDR;
    if (ntohl(hdr->ih_magic) != IMAGE_MAGIC) {
        dbg_log(1, "Bad Image Magic Number found! %d\n\r", ntohl(hdr->ih_magic));
        return;
    }

    len = ntohl(hdr->ih_size);
    load_addr = ntohl(hdr->ih_load);
    ep = ntohl(hdr->ih_ep);
    dbg_log(1, "Image size: %d, load_addr: %x, ep: %x\n\r", len, load_addr, ep);

    //if (hdr->ih_comp != 0) {
    //    dbg_log(1, "Compressed U-Boot Image has not been supported yet!\n\r");
    //    return;
    //}

    theKernel = (void (*)(int, int, unsigned int))ep;

    //clean_environment();

    dbg_log(1,
            "relocating linux kernel to proper address, dst: %x, src: %x, len: %d, machid: %d\n\r",
            load_addr, (unsigned long)JUMP_ADDR + sizeof (image_header_t), len, MACH_TYPE);
    memcpy((void *)load_addr,
           (void *)((unsigned long)JUMP_ADDR + sizeof (image_header_t)), len);
    //dbg_log(1, "... %d bytes data transferred!\n\r", len);

    setup_tags();
    //dbg_log(1, "\n\rStarting linux kernel ..., machid: %d, tags: %x\n\r\n\r", MACH_TYPE, (OS_MEM_BANK + 0x100));

    theKernel(0, MACH_TYPE, (unsigned int)(OS_MEM_BANK + 0x100));

    /*
     * never reach here 
     */
    //return;
}

#endif
