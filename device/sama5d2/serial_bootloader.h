#ifndef __SERIAL_BOOTLOADER_H__
#define __SERIAL_BOOTLOADER_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef bool (*read_func)(uint8_t* const dataout, size_t size);
typedef bool (*write_func)(const uint8_t* const datain, size_t size);

typedef struct
{
    read_func readFN;
    write_func writeFN;
    uintptr_t scratch_mem_addr;
    uintptr_t binary_dest_addr;
} boot_config;

bool serial_bootloader_load(const boot_config* const config);
#endif //__SERIAL_BOOTLOADER_H__
