/*
 * Copyright (C) 2015 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AES_H__
#define __AES_H__

#define AT91_AES_BLOCK_SIZE_BYTE	16
#define AT91_AES_BLOCK_SIZE_WORD	4

#define AT91_AES_IV_SIZE_BYTE		16
#define AT91_AES_IV_SIZE_WORD		4

typedef enum at91_aes_operation {
	AT91_AES_OP_DECRYPT,
	AT91_AES_OP_ENCRYPT,
	AT91_AES_OP_MAC
} at91_aes_operation_t;

typedef enum at91_aes_mode {
	AT91_AES_MODE_ECB,
	AT91_AES_MODE_CBC,
	AT91_AES_MODE_OFB,
	AT91_AES_MODE_CFB_128,
	AT91_AES_MODE_CFB_64,
	AT91_AES_MODE_CFB_32,
	AT91_AES_MODE_CFB_16,
	AT91_AES_MODE_CFB_8,
	AT91_AES_MODE_CTR,
	AT91_AES_MODE_GCM
} at91_aes_mode_t;

typedef enum at91_aes_key_size {
	AT91_AES_KEY_SIZE_128,
	AT91_AES_KEY_SIZE_192,
	AT91_AES_KEY_SIZE_256
} at91_aes_key_size_t;


typedef struct at91_aes_params {
	/* operation mode */
	at91_aes_operation_t	operation;
	at91_aes_mode_t		mode;

	/* data blocks */
	unsigned int		data_length;
	const void		*input;
	void			*output;

	/* key and IV */
	at91_aes_key_size_t	key_size;
	const unsigned int	*key;
	const unsigned int	*iv;
} at91_aes_params_t;


static inline unsigned int at91_aes_roundup(unsigned int data_length)
{
	unsigned int fixed_length;

	fixed_length = data_length >> 4;
	if (data_length & 0xf)
		fixed_length++;

	return fixed_length << 4;
}


void at91_aes_init(void);
void at91_aes_cleanup(void);

int at91_aes_cbc(unsigned int data_length,
		 const void *input,
		 void *output,
		 int encrypt,
		 at91_aes_key_size_t key_size,
		 const unsigned int *key,
		 const unsigned int *iv);

int at91_aes_cmac(unsigned int data_length,
		  const void *data,
		  unsigned int *cmac,
		  at91_aes_key_size_t key_size,
		  const unsigned int *key);

#endif /* __AES_H__ */
