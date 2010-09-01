/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  -  ROUSSET  -
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
 * ----------------------------------------------------------------------------
 * File Name           : dataflash.h
 * Object              : ATMEL DataFlash Header File
 * Creation            : NLe Jul 12th 2006
 *---------------------------------------------------------------------------
*/
#ifndef _DATAFLASH_H
#define _DATAFLASH_H

/* Chip Select 0 : NPCS0 %1110 */
#define AT91C_SPI_PCS0_DATAFLASH	0xE
/* Chip Select 1 : NPCS1 %1101 */
#define AT91C_SPI_PCS1_DATAFLASH	0xD
/* Chip Select 2 : NPCS2 %1011 */
#define AT91C_SPI_PCS2_DATAFLASH	0xB
/* Chip Select 3 : NPCS3 %0111 */
#define AT91C_SPI_PCS3_DATAFLASH	0x7

/* Max PDC Size for SPI Continuous Read */
#define AT91C_MAX_PDC_SIZE	0xFFFF

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
/* Command Definition											*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/

/* READ COMMANDS */
#define DB_CONTINUOUS_ARRAY_READ   	0xE8    /* Continuous array read */
#define DB_BURST_ARRAY_READ        	0xE8    /* Burst array read */
#define DB_PAGE_READ               	0xD2    /* Main memory page read */
#define DB_BUF1_READ               	0xD4    /* Buffer 1 read */
#define DB_BUF2_READ               	0xD6    /* Buffer 2 read */
#define DB_STATUS                  	0xD7    /* Status Register */

/* PROGRAM and ERASE COMMANDS */
#define DB_BUF1_WRITE              	0x84    /* Buffer 1 write */
#define DB_BUF2_WRITE              	0x87    /* Buffer 2 write */
#define DB_BUF1_PAGE_ERASE_PGM     	0x83    /* Buffer 1 to main memory page program with built-In erase */
#define DB_BUF1_PAGE_ERASE_FASTPGM 	0x93    /* Buffer 1 to main memory page program with built-In erase, Fast program */
#define DB_BUF2_PAGE_ERASE_PGM     	0x86    /* Buffer 2 to main memory page program with built-In erase */
#define DB_BUF2_PAGE_ERASE_FASTPGM 	0x96    /* Buffer 1 to main memory page program with built-In erase, Fast program */
#define DB_BUF1_PAGE_PGM           	0x88    /* Buffer 1 to main memory page program without built-In erase */
#define DB_BUF1_PAGE_FASTPGM       	0x98    /* Buffer 1 to main memory page program without built-In erase, Fast program */
#define DB_BUF2_PAGE_PGM           	0x89    /* Buffer 2 to main memory page program without built-In erase */
#define DB_BUF2_PAGE_FASTPGM       	0x99    /* Buffer 1 to main memory page program without built-In erase, Fast program */
#define DB_PAGE_ERASE              	0x81    /* Page Erase */
#define DB_BLOCK_ERASE             	0x50    /* Block Erase */
#define DB_PAGE_PGM_BUF1           	0x82    /* Main memory page through buffer 1 */
#define DB_PAGE_FASTPGM_BUF1       	0x92    /* Main memory page through buffer 1, Fast program */
#define DB_PAGE_PGM_BUF2           	0x85    /* Main memory page through buffer 2 */
#define DB_PAGE_FastPGM_BUF2       	0x95    /* Main memory page through buffer 2, Fast program */

/* ADDITIONAL COMMANDS */
#define DB_PAGE_2_BUF1_TRF         	0x53    /* Main memory page to buffer 1 transfert */
#define DB_PAGE_2_BUF2_TRF         	0x55    /* Main memory page to buffer 2 transfert */
#define DB_PAGE_2_BUF1_CMP         	0x60    /* Main memory page to buffer 1 compare */
#define DB_PAGE_2_BUF2_CMP          0x61        /* Main memory page to buffer 2 compare */
#define DB_AUTO_PAGE_PGM_BUF1      	0x58    /* Auto page rewrite throught buffer 1 */
#define DB_AUTO_PAGE_PGM_BUF2      	0x59    /* Auto page rewrite throught buffer 2 */

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
/* ATMEL Dataflash description										*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
#define AT45DB011D		0x0C
#define AT45DB021D		0x14
#define AT45DB041D		0x1C
#define AT45DB081D		0x24
#define AT45DB161D		0x2C
#define AT45DB321D		0x34
#define AT45DB642D		0x3C
#define AT45DB1282D		0x10
#define AT45DB2562D		0x18
#define AT45DB5122D		0x20

#define AT91C_DF_TIMEOUT			10000000

/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
/* Dataflash Interface Definition									*/
/*//////////////////////////////////////////////////////////////////////////////////////////////////////*/
typedef enum _AT91S_DF_SEM {
    UNLOCKED,
    LOCKED
} AT91S_DF_SEM;

typedef enum _AT91S_DF_STATE {
    START_COMMAND,
    WAIT_FOR_BUSY,
    ERASE,
    END_OF_ERASE,

    START_WRITE,
    END_OF_WRITE,

    START_READ,
    END_OF_READ,
    READ_GET_STATUS,
    WAIT_FOR_READ_STATUS
} AT91S_DF_STATE;

/* Dataflash Description Structure */
typedef struct _AT91S_DF_DESC {
    int pages_number;           /* dataflash page number */
    int pages_size;             /* dataflash page size */
    int page_offset;            /* page offset in command */
    int block_size;             /* nb page per block */
    int byte_mask;              /* byte mask in command */
    int binaryPageMode;         /* indicate if configured in power-of-2 binary */
} AT91S_DF_DESC, *AT91PS_DF_DESC;

/* Dataflash Descriptor Structure */
typedef struct _AT91S_DF {
    unsigned char bCs;
    AT91S_DF_SEM bSemaphore;    /* SPI semaphore */
    unsigned int command[2];
    AT91S_DF_DESC dfDescription;
} AT91S_DF, *AT91PS_DF;

#define AT91C_DF_NB_BLOCS(pDf)  (pDf->dfDescription.pages_number / pDf->dfDescription.block_size)
#define AT91C_DF_BLOC_SIZE(pDf) (pDf->dfDescription.block_size * pDf->dfDescription.pages_size)
#define AT91C_DF_NB_PAGE(pDf)   (pDf->dfDescription.pages_number)
#define AT91C_PAGE_SIZE(pDf)    (pDf->dfDescription.pages_size)
#define AT91C_PAGE_OFFSET(pDf)  (pDf->dfDescription.page_offset)

/* ============ READ COMMANDS =============== */
#define df_continuous_read(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_CONTINUOUS_ARRAY_READ, 8, pData, dDataSize, dAddress)
#define df_page_read(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_PAGE_READ, 8, pData, dDataSize, dAddress)
#define df_read_buf1(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF1_READ, 5, pData, dDataSize, dAddress)
#define df_read_buf2(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF2_READ, 5, pData, dDataSize, dAddress)
#define df_get_status(pDf) \
    df_send_command(pDf, DB_STATUS, 2, (char *) 0, 0, 0)

/* ============ WRITE COMMANDS =============== */
#define df_write_buf1(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF1_WRITE, 4, pData, dDataSize, dAddress)
#define df_write_buf2(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF2_WRITE, 4, pData, dDataSize, dAddress)

#define df_pgm_erase_buf1(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF1_PAGE_ERASE_PGM, 4, pData, dDataSize, dAddress)
#define df_pgm_erase_buf2(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF2_PAGE_ERASE_PGM, 4, pData, dDataSize, dAddress)

#define df_pgm_buf1(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF1_PAGE_PGM, 4, pData, dDataSize, dAddress)
#define df_pgm_buf2(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_BUF2_PAGE_PGM, 4, pData, dDataSize, dAddress)

#define df_page_write(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_PAGE_PGM_BUF1, 4, pData, dDataSize, dAddress)

/* ============ ERASE COMMANDS =============== */
#define df_page_erase(pDf, dAddress) \
    df_send_command(pDf, DB_PAGE_ERASE, 4, (char *) 0, 0, dAddress)
#define df_block_erase(pDf, dAddress) \
    df_send_command(pDf, DB_BLOCK_ERASE, 4, (char *) 0, 0, dAddress)

/* ============ ADDITIONAL COMMANDS =============== */
#define df_trf_buf1(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_PAGE_2_BUF1_TRF, 4, (char *) 0, 0, dAddress)
#define df_trf_buf2(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_PAGE_2_BUF1_TRF, 4, (char *) 0, 0, dAddress)

#define df_cmp_buf1(pDf, dAddress) \
    df_send_command(pDf, DB_PAGE_2_BUF1_CMP, 4, (char *) 0, 0, dAddress)
#define df_cmp_buf2(pDf, dAddress) \
    df_send_command(pDf, DB_PAGE_2_BUF2_CMP, 4, (char *) 0, 0, dAddress)

#define df_rwr_buf1(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_AUTO_PAGE_PGM_BUF1, 4, (char *) 0, 0, dAddress)
#define df_rwr_buf2(pDf, pData, dDataSize, dAddress) \
    df_send_command(pDf, DB_AUTO_PAGE_PGM_BUF2, 4, (char *) 0, 0, dAddress)
/* ============ Status Register Fields =============== */
#define df_is_ready(pDf) \
    ((pDf)->command[0] & 0x8000)
#define df_is_different(pDf) \
    ((pDf)->command[0] & 0x4000)

extern void df_hw_init(void);

extern void df_recovery(AT91PS_DF pDf);

extern int load_df(unsigned int pcs, unsigned int img_addr,
                   unsigned int img_size, unsigned int img_dest);

extern char df_send_command(AT91PS_DF pDataFlash, unsigned char bCmd,   // Command value
                            unsigned char bCmdSize,     // Command Size
                            char *pData,        // Data to be sent
                            unsigned int dDataSize,     // Data Size
                            unsigned int dAddress);     // Dataflash Address

/*
extern char df_wait_ready(
	AT91PS_DF pDataFlash);

extern AT91S_DF_SEM df_is_busy(
	AT91PS_DF pDataFlash);
*/

#endif
