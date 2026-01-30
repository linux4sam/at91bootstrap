#ifndef __FLEXCOMM_USART_H__
#define __FLEXCOMM_USART_H__

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

void flexcomm_usart_init();

bool flexcomm_usart_write(const uint8_t* const data, size_t len);

bool flexcomm_usart_read(uint8_t *const data, size_t len);

#endif // __FLEXCOMM_USART_H__
