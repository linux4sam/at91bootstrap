#include "main.h"
#include "debug.h"
#include "dbgu.h"
#include "dataflash.h"
#include "nandflash.h"

unsigned int load_SDCard();

typedef struct {
    unsigned int dwSize;
    unsigned int dwEbootCodeFlashAddr;
    unsigned int dwEbootSettingsFlashAddr;
    unsigned int dwCrc32;
} T_BOOTLOADER_FLASH_CONFIG;

#ifdef CONFIG_DATAFLASH
#ifdef AT91SAM9G10
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9G20
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x200000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9G45
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9M10
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9RL
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9263
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9261
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9260
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x200000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x4000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x25000)
#endif
#endif

#ifdef CONFIG_NANDFLASH
#ifdef AT91SAM9G10
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9G20
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x200000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9G45
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9M10
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9RL
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9263
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9261
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x80000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x180000)
#endif
#ifdef AT91SAM9260
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x200000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x4000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x25000)
#endif
#endif

#ifdef CONFIG_SDCARD
#ifdef AT91SAM9G10
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x5000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x50000)
#endif
#ifdef AT91SAM9G20
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x200000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x5000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x50000)
#endif
#ifdef AT91SAM9G45
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x5000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x50000)
#endif
#ifdef AT91SAM9M10
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x5000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x50000)
#endif
#ifdef AT91SAM9RL
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x5000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x50000)
#endif
#ifdef AT91SAM9263
#define BOOTLOADER_FLASH_CONFIG_ADDR 0x300000
#define EBOOT_FLASH_CODE_ADDR		(0xE0000000|0x5000)
#define EBOOT_FLASH_SETTINGS_ADDR	(0xE0000000|0x50000)
#endif
#endif

unsigned long ComputeCRC32(unsigned char *buffer, int len)
{
    unsigned long crc;

    unsigned long temp;

    int j;

    crc = 0xFFFFFFFF;

    while (len--) {
        temp = (unsigned long)((crc & 0xFF) ^ *buffer++);
        for (j = 0; j < 8; j++) {
            if (temp & 0x1)
                temp = (temp >> 1) ^ 0xEDB88320;
            else
                temp >>= 1;
        }
        crc = (crc >> 8) ^ temp;
    }
    return crc ^ 0xFFFFFFFF;
}

void set_eboot_settings()
{
    volatile T_BOOTLOADER_FLASH_CONFIG *pBootFlashConfig =
        (T_BOOTLOADER_FLASH_CONFIG *) (BOOTLOADER_FLASH_CONFIG_ADDR);

    // Set flash configuration
    pBootFlashConfig->dwEbootCodeFlashAddr = EBOOT_FLASH_CODE_ADDR;
    pBootFlashConfig->dwEbootSettingsFlashAddr = EBOOT_FLASH_SETTINGS_ADDR;
    pBootFlashConfig->dwSize = sizeof (T_BOOTLOADER_FLASH_CONFIG);
    pBootFlashConfig->dwCrc32 =
        ComputeCRC32((unsigned char *)pBootFlashConfig,
                     sizeof (T_BOOTLOADER_FLASH_CONFIG) -
                     sizeof (unsigned int));
}

void set_nk_settings()
{
    char *ptr = (unsigned char *)GLBDRV_ADDR;

    memset(ptr, 0, 0x1000);
    *(unsigned int *)(GLBDRV_ADDR + 0x808) = 'SGRA';    // SIGNATURE
    *(unsigned short *)(GLBDRV_ADDR + 0x80C) = 0x1;     // OALVERSION
    *(unsigned short *)(GLBDRV_ADDR + 0x80E) = 0x1;     // BSPVERSION
#ifdef CONFIG_AT91SAM9260EK
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 200;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 4; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9261EK
    *(unsigned int *)(GLBDRV_ADDR + 0x84C) = 200;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 4; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9263EK
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 200;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 4; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9G10EK
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 200;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 2; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9G20EK
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 0x320;     // PLL_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 0x1;       // PRESCALER
    *(unsigned int *)(GLBDRV_ADDR + 0x858) = 0x6;       // PROC_DIVIDER
    *(unsigned int *)(GLBDRV_ADDR + 0x85C) = 0x2;       // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9RLEK
    *(unsigned int *)(GLBDRV_ADDR + 0x858) = 200;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x85C) = 2; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9G45EK
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 400;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 2; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9M10EK
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 400;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 2; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9G45EKES
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 400;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 2; // BUS_DIVIDER
#endif
#ifdef CONFIG_AT91SAM9M10EKES
    *(unsigned int *)(GLBDRV_ADDR + 0x850) = 400;       // CORE_FREQUENCY
    *(unsigned int *)(GLBDRV_ADDR + 0x854) = 2; // BUS_DIVIDER
#endif
}

void LoadWince()
{
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

#ifdef CONFIG_LOAD_EBOOT
    set_eboot_settings();
#else
    set_nk_settings();
#endif
}
