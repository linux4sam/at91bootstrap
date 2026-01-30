#include "serial_bootloader.h"
#include "string.h"
#include "xmodem.h"

static boot_config _config;
#define read(buf, size)               \
    do {                              \
        (*_config.readFN)(buf, size); \
    } while (0)
#define write(buf, size)               \
    do {                               \
        (*_config.writeFN)(buf, size); \
    } while (0)

extern void usart_puts(const char* ptr);

static int _recv_byte(unsigned short timout)
{
    if (timout == 0xff)
        return 1;
    uint8_t val;
    if ((*_config.readFN)(&val, 1))
    {
        return (int)val;
    }
    else
    {
        return -1;
    }
}

static void _write_byte(int c)
{
    (*_config.writeFN)((uint8_t*)&c, 1);
}

static bool _get_binary_size(uint32_t* const ret)
{
    char sb = 0;
    do {
        // Wait for the S byte
        sb = (char)_recv_byte(0);
    } while (sb != 'S');
    _write_byte('S');
    // we get the size of the binary
    read((uint8_t*)ret, sizeof(uint32_t));
    // We write the size back to confirm
    write((uint8_t*)ret, sizeof(uint32_t));
    // Host should send any number but 0 if it was correct
    return _recv_byte(0) > 0;
}

static bool verify_binary(const uint8_t* const buf, size_t size)
{
    // We are not verifing yet so just return true
    return true;
}

bool serial_bootloader_load(const boot_config* const config)
{
    uint32_t binary_size = 0;
    bool ret = false;
    memcpy(&_config, config, sizeof(boot_config));
    xmodemInit(_recv_byte, _write_byte);
    if (_get_binary_size(&binary_size))
    {
        int m_ret = xmodemReceive((unsigned char*)_config.binary_dest_addr, binary_size);
        if (m_ret > 0)
        {
            if (verify_binary((uint8_t*)_config.scratch_mem_addr, binary_size))
            {
                /* memcpy( */
                /*     (void*)_config.binary_dest_addr, (void*)_config.scratch_mem_addr, binary_size
                 */
                /* ); */
                ret = true;
                return ret;
            }
        }
    }
    return ret;
}
