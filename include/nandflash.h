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
 * this list of conditions and the disclaimer below.
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
 * File Name           : nandflash.h
 * Object              :
 * Creation            : NLe Sep 28th 2006
 *-----------------------------------------------------------------------------
 */
#ifndef _NANDFLASH_H
#define _NANDFLASH_H

#include "NandSpareScheme.h"

typedef struct SNandInitInfo {
    //unsigned short         uNandID; /* Nand Chip ID */
    unsigned short uNandNbBlocks;
    unsigned int uNandBlockSize;
    unsigned short uNandSectorSize;
    unsigned char uNandSpareSize;
    unsigned char uNandBusWidth;
    struct NandSpareScheme *pSpareScheme;
    //char                 name[32]         ; /* Nand Name */
} SNandInitInfo, *PSNandInitInfo;

/* Group all usefull sizes for the nandflash chip */
typedef struct _NandInfo {
    unsigned int uDataNbBytes;  /* Nb of bytes in data section */
    unsigned int uSpareNbBytes; /* Nb of bytes in spare section */
    unsigned int uSectorNbBytes;        /* Total nb of bytes in a sector */

    unsigned int uNbBlocks;     /* Nb of blocks in device */
    unsigned int uBlockNbData;  /* Nb of DataBytes in a block */
#if 0
    unsigned int uBlockNbSectors;       /* Nb of sector in a block */
    unsigned int uBlockNbSpares;        /* Nb of SpareBytes in a block */
    unsigned int uBlockNbBytes; /* Total nb of bytes in a block */

    unsigned int uNbSectors;    /* Total nb of sectors in device */
#endif
    unsigned int uNbData;       /* Nb of DataBytes in device */
    unsigned int uNbSpares;     /* Nb of SpareBytes in device */
    unsigned int uNbBytes;      /* Total nb of bytes in device */

    unsigned int uOffset;

    unsigned int uDataBusWidth; /* Data Bus Width (8/16 bits) */

    unsigned int uBadBlockInfoOffset;   /* Bad block info offset in spare zone (in bytes) */
    struct NandSpareScheme *pSpareScheme;
} SNandInfo, *PSNandInfo;

/* Sector Info Structure */
//typedef struct  __attribute__((__packed__)) _SectorInfo
//{
//    unsigned int dwReserved1;       /* Reserved - used by FAL */
//    char  bOEMReserved;             /* For use by OEM */
//    char  bBadBlock;              /* Indicates if block is BAD */
//    short wReserved2;               /* Reserved - used by FAL */
//}SSectorInfo, *PSSectorInfo;

#ifdef NANDFLASH_SMALL_BLOCKS
#define BAD_BLOCK_INFO_OFFSET 5
#define SPARE_DATA_SIZE      64
#else
#define BAD_BLOCK_INFO_OFFSET 0
#define SPARE_DATA_SIZE      16
#endif

#define BAD_BLOCK_TAG   0xFF

typedef struct _SectorInfo {
    unsigned char spare[SPARE_DATA_SIZE];
} SSectorInfo, *PSSectorInfo;

/* Wait mode */
#define WAIT_POOL			POOL_ON_READYBUSY       /* Default pool mode */
#define WAIT_INTERRUPT			INTERRUPT_ON_READYBUSY  /* Default interrupt mode */
#define	ERASE_TIMEOUT			10      /* erase maximum time in ms */
#define RESET_TIMEOUT			10      /* reset maximum time in ms */
#define READ_TIMEOUT			10      /* read maximum time in ms */
#define WRITE_TIMEOUT			10      /* write maximum time in ms */

#define POOL_ON_READYBUSY		0x01    /* Pool on ReadyBusy PIO */
#define INTERRUPT_ON_READYBUSY		0x02    /* Interrupt on ReadyBusy PIO */
#define POOL_ON_STATUS			0x04    /* Pool on Status byte */

/* Sector zones */
#define SPARE_VALUE			0xFF

#define ZONE_DATA			0x01    /* Sector data zone */
#define ZONE_INFO			0x02    /* Sector info zone */

/* Nand flash chip status codes */
#define STATUS_READY                (0x01<<6)   /* Status code for Ready */
#define STATUS_ERROR                (0x01<<0)   /* Status code for Error */

/* Nand flash commands */
#define CMD_READ_1			0x00
#define CMD_READ_2			0x30

#define CMD_READID			0x90

#define CMD_WRITE_1			0x80
#define CMD_WRITE_2			0x10

#define CMD_ERASE_1			0x60
#define CMD_ERASE_2			0xD0

#define CMD_STATUS			0x70
#define CMD_RESET			0xFF

/* Nand flash commands (small blocks) */
#define CMD_READ_A0			0x00
#define CMD_READ_A1			0x01
#define CMD_READ_C			0x50

#define CMD_WRITE_A			0x00
#define CMD_WRITE_C			0x50

#define NAND_BUS_WIDTH_8BITS		0x0
#define NAND_BUS_WIDTH_16BITS		0x1

/* NandFlash functions */
extern void nandflash_hw_init(void);

extern void nandflash_cfg_16bits_dbw_init(void);

extern void nandflash_cfg_8bits_dbw_init(void);

//extern int load_nandflash(unsigned int img_addr, unsigned int img_size, unsigned int img_dest);
extern int load_nandflash(void);

extern BOOL AT91F_NandEraseBlock0(void);

extern int read_nandflash(unsigned char *dst, unsigned long offset, int len);

#endif
