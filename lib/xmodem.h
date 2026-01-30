#ifndef __X_MODEM_H__
#define __X_MODEM_H__

typedef int (*recv_byte_func)(unsigned short timeout);
typedef void (*write_byte_func)(int c);

void xmodemInit(recv_byte_func rb, write_byte_func wb);
int xmodemReceive(unsigned char *dest, int destsz);
int xmodemTransmit(unsigned char *src, int srcsz);
#endif // __X_MODEM_H__
