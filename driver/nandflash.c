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
 * File Name           : nandflash.c
 * Object              :
 * Creation            : NLe Sep 28th 2006
 *-----------------------------------------------------------------------------
 */
#include <stdlib.h>
#include "part.h"
#include "main.h"
#include "debug.h"

#ifdef CONFIG_NANDFLASH

#include "nandflash.h"
#include "hamming.h"

/*----------------------------------------------------------------------------*/
/* NAND Commands							      */
/*----------------------------------------------------------------------------*/
/* 8 bits devices */
#define WRITE_NAND_COMMAND(d) do { \
	*(volatile unsigned char *) \
	((unsigned long)AT91C_SMARTMEDIA_BASE | AT91_SMART_MEDIA_CLE) = \
	(unsigned char)(d); \
	} while(0)

#define WRITE_NAND_ADDRESS(d) do { \
	*(volatile unsigned char *) \
	((unsigned long)AT91C_SMARTMEDIA_BASE | AT91_SMART_MEDIA_ALE) = \
	(unsigned char)(d); \
	} while(0)

#define WRITE_NAND(d) do { \
	*(volatile unsigned char *) \
	((unsigned long)AT91C_SMARTMEDIA_BASE) = (unsigned char)d; \
	} while(0)

#define READ_NAND() ((unsigned char)(*(volatile unsigned char *) \
	(unsigned long)AT91C_SMARTMEDIA_BASE))

/* 16 bits devices */
#define WRITE_NAND_COMMAND16(d) do { \
	*(volatile unsigned short *) \
	((unsigned long)AT91C_SMARTMEDIA_BASE | AT91_SMART_MEDIA_CLE) = \
	(unsigned short)(d); \
	} while(0)

#define WRITE_NAND_ADDRESS16(d) do { \
	*(volatile unsigned short *) \
	((unsigned long)AT91C_SMARTMEDIA_BASE | AT91_SMART_MEDIA_ALE) = \
	(unsigned short)(d); \
	} while(0)

#define WRITE_NAND16(d) do { \
	*(volatile unsigned short *) \
	((unsigned long)AT91C_SMARTMEDIA_BASE) = (unsigned short)d; \
	} while(0)

#define READ_NAND16() ((unsigned short)(*(volatile unsigned short *) \
						(unsigned long)AT91C_SMARTMEDIA_BASE))

#if 0
static struct SNandInitInfo NandFlash_InitInfo[] = {
    /*
     * ID    blk    blk_size pg_size spare_size bus_width spare_scheme chip_name 
     */
    {0x2cca, 0x800, 0x20000, 0x800, 0x40, 0x1, &Spare_2048, "MT29F2G16AAB\0"},
    {0x2cda, 0x800, 0x20000, 0x800, 0x40, 0x0, &Spare_2048, "MT29F2G08AAC\0"},
    {0x2caa, 0x800, 0x20000, 0x800, 0x40, 0x0, &Spare_2048, "MT29F2G08ABD\0"},
    {0xecda, 0x800, 0x20000, 0x800, 0x40, 0x0, &Spare_2048, "K9F2G08U0M\0"},
    {0xecaa, 0x800, 0x20000, 0x800, 0x40, 0x0, &Spare_2048, "K9F2G08U0A\0"},
    {0x20aa, 0x800, 0x20000, 0x800, 0x40, 0x0, &Spare_2048, "ST NAND02GR3B\0"},
    {0,}
};
#endif

static inline struct SNandInitInfo *AT91F_GetNandInitInfo(unsigned short chipID)
{
    static struct SNandInitInfo info;

    //info.uNandID = chipID;
    info.uNandNbBlocks = 0x800;
    info.uNandBlockSize = 0x20000;
    info.uNandSectorSize = 0x800;
    info.uNandSpareSize = 0x40;
    info.uNandBusWidth = 0;
    info.pSpareScheme = &Spare_2048;

	dbg_log(1, "chip id: %x\n\r", chipID);

    switch (chipID) {
    case 0x2cca:
        info.uNandBusWidth = 0x1;
        break;
    case 0x2cda:
    case 0x2caa:
    case 0xecda:
    case 0xecaa:
    case 0x20aa:
        break;
    default:
        return 0;
    }

    return &info;
}

static void AT91F_NandInit(PSNandInfo pNandInfo, PSNandInitInfo pNandInitInfo)
{
    unsigned int uSectorSize, i = 0;

#if 0
    div_t result;
#endif

    /*
     * Nb of blocks in device 
     */
    pNandInfo->uNbBlocks = pNandInitInfo->uNandNbBlocks;
    /*
     * Nb of data bytes in a block 
     */
    pNandInfo->uBlockNbData = pNandInitInfo->uNandBlockSize;
    /*
     * Nb of bytes in Data area 
     */
    pNandInfo->uDataNbBytes = pNandInitInfo->uNandSectorSize;
    /*
     * Nb of bytes in Spare area 
     */
    pNandInfo->uSpareNbBytes = pNandInitInfo->uNandSpareSize;
    /*
     * Total nb of bytes in a sector 
     */
    pNandInfo->uSectorNbBytes = pNandInfo->uDataNbBytes +
        pNandInfo->uSpareNbBytes;
    pNandInfo->pSpareScheme = pNandInitInfo->pSpareScheme;

#if 0
    /*
     * Nb of sector in a block 
     */
    /*
     * pNandInfo->uBlockNbSectors = pNandInfo->uBlockNbData / pNandInfo->uDataNbBytes; 
     */
    result = udiv(pNandInfo->uBlockNbData, pNandInfo->uDataNbBytes);
    if (result.rem != 0)
        result.quot++;
    pNandInfo->uBlockNbSectors = result.quot;   /* Nb of sector in a block */

    pNandInfo->uBlockNbSpares = pNandInfo->uSpareNbBytes * pNandInfo->uBlockNbSectors;  /* Nb of SpareBytes in a block */
    pNandInfo->uBlockNbBytes = pNandInfo->uSectorNbBytes * pNandInfo->uBlockNbSectors;  /* Total nb of bytes in a block */

    pNandInfo->uNbSectors = pNandInfo->uBlockNbSectors * pNandInfo->uNbBlocks;  /* Total nb of sectors in device */
    pNandInfo->uNbData = pNandInfo->uBlockNbBytes * pNandInfo->uNbBlocks;       /* Nb of DataBytes in device */
    pNandInfo->uNbSpares = pNandInfo->uBlockNbSpares * pNandInfo->uNbBlocks;    /* Nb of SpareBytes in device */
    pNandInfo->uNbBytes = pNandInfo->uNbData + pNandInfo->uNbSpares;    /* Total nb of bytes in device */
#endif
    pNandInfo->uDataBusWidth = pNandInitInfo->uNandBusWidth;    /* Data Bus Width (8/16 bits) */

    uSectorSize = pNandInfo->uDataNbBytes - 1;
    pNandInfo->uOffset = 0;

    while (uSectorSize >> i) {
        pNandInfo->uOffset++;
        i++;
    }

    if (pNandInfo->uDataBusWidth) {
        pNandInfo->uBadBlockInfoOffset = 2 * BAD_BLOCK_INFO_OFFSET;
    } else {
        pNandInfo->uBadBlockInfoOffset = BAD_BLOCK_INFO_OFFSET;
    }
}

static PSNandInitInfo AT91F_NandReadID(void)
{
    unsigned int uChipID;

    unsigned char bManufacturerID, bDeviceID;

    /*
     * Enable chipset 
     */
    NAND_ENABLE_CE();

    /*
     * Ask the Nand its IDs 
     */
    WRITE_NAND_COMMAND(CMD_READID);
    WRITE_NAND_ADDRESS(0x00);

    /*
     * Read answer 
     */
    bManufacturerID = READ_NAND();
    bDeviceID = READ_NAND();

    /*
     * Disable chipset before returning 
     */
    NAND_DISABLE_CE();

    uChipID = (bManufacturerID << 8) | bDeviceID;

    return AT91F_GetNandInitInfo(uChipID);
#if 0
    /*
     * Search in NandFlash_InitInfo[] 
     */
    while (NandFlash_InitInfo[i].uNandID != 0) {
        if (NandFlash_InitInfo[i].uNandID == uChipID)
            return &NandFlash_InitInfo[i];

        i++;
    }

    return 0;
#endif
}

static void AT91F_WriteLarge_BlkAdr(unsigned int Adr)
{
    WRITE_NAND_ADDRESS((Adr >> 0) & 0xFF);
    WRITE_NAND_ADDRESS((Adr >> 8) & 0xFF);
}

static void AT91F_WriteSectorAdr(unsigned int Adr)
{
    AT91F_WriteLarge_BlkAdr(Adr);
    WRITE_NAND_ADDRESS((Adr >> 16) & 0xFF);
}

BOOL AT91F_NandEraseBlock0(void)
{
    unsigned int uPhySecNb = 0;

    BOOL bRet = TRUE;

    NAND_ENABLE_CE();

    WRITE_NAND_COMMAND(CMD_ERASE_1);

    /*
     * Push sector address in three cycles 
     */
    AT91F_WriteSectorAdr(uPhySecNb);

    WRITE_NAND_COMMAND(CMD_ERASE_2);

    /*
     * Wait for nand to be ready 
     */
    NAND_WAIT_READY();
    NAND_WAIT_READY();

    /*
     * Check status bit for error notification 
     */
    WRITE_NAND_COMMAND(CMD_STATUS);
    NAND_WAIT_READY();
    if (READ_NAND() & STATUS_ERROR) {
        bRet = FALSE;
        goto exit;
    }

 exit:
    NAND_DISABLE_CE();

    return bRet;
}

#ifdef NANDFLASH_SMALL_BLOCKS
BOOL AT91F_NandReadSector(PSNandInfo pNandInfo, unsigned int uSectorAddr,
                          unsigned char *pOutBuffer, unsigned int fZone)
{
    BOOL bRet = TRUE;

    unsigned int uBytesToRead, i;

    unsigned char Cmd;

    /*
     * WARNING : During a read procedure you can't call the ReadStatus flash cmd
     * * The ReadStatus fill the read register with 0xC0 and then corrupt the read
     */

    /*
     * Push offset address 
     */
    switch (fZone) {
    case ZONE_DATA:
        uBytesToRead = pNandInfo->uDataNbBytes;
        Cmd = CMD_READ_A0;
        break;
    case ZONE_INFO:
        uBytesToRead = pNandInfo->uSpareNbBytes;
        pOutBuffer += pNandInfo->uDataNbBytes;
        Cmd = CMD_READ_C;
        break;
    case ZONE_DATA | ZONE_INFO:
        uBytesToRead = pNandInfo->uSectorNbBytes;
        Cmd = CMD_READ_A0;
        break;
    default:
        bRet = FALSE;
        goto exit;
    }

    /*
     * Enable the chip 
     */
    NAND_ENABLE_CE();

    /*
     * Write specific command, Read from start 
     */
    if (pNandInfo->uDataBusWidth) {
        /*
         * 16 bits 
         */
        WRITE_NAND_COMMAND16(Cmd);
    } else {
        /*
         * 8 bits 
         */
        WRITE_NAND_COMMAND(Cmd);
    }

    /*
     * Push sector address 
     */
    uSectorAddr >>= pNandInfo->uOffset;

    if (pNandInfo->uDataBusWidth) {
        /*
         * 16 bits 
         */
        WRITE_NAND_ADDRESS16(0x00);
        WRITE_NAND_ADDRESS16((uSectorAddr >> 0) & 0xFF);
        WRITE_NAND_ADDRESS16((uSectorAddr >> 8) & 0xFF);
        WRITE_NAND_ADDRESS16((uSectorAddr >> 16) & 0xFF);
    } else {
        /*
         * 8 bits 
         */
        WRITE_NAND_ADDRESS(0x00);
        WRITE_NAND_ADDRESS((uSectorAddr >> 0) & 0xFF);
        WRITE_NAND_ADDRESS((uSectorAddr >> 8) & 0xFF);
        WRITE_NAND_ADDRESS((uSectorAddr >> 16) & 0xFF);
    }

    /*
     * Wait for flash to be ready (can't pool on status, read upper WARNING) 
     */
    NAND_WAIT_READY();
    /*
     * Need to be done twice, READY detected too early the first time? 
     */
    NAND_WAIT_READY();

    /*
     * Read loop 
     */
    if (pNandInfo->uDataBusWidth) {
        /*
         * 16 bits 
         */
        for (i = 0; i < uBytesToRead / 2; i++)  // Div2 because of 16bits
        {
            *((short *)pOutBuffer) = READ_NAND16();
            pOutBuffer += 2;
        }
    } else {
        /*
         * 8 bits 
         */
        if (Cmd == CMD_READ_C) {
            for (i = 0; i < uBytesToRead; i++) {
                *pOutBuffer = READ_NAND();
                pOutBuffer++;
            }
        } else {
            for (i = 0; i < uBytesToRead / 2; i++) {
                *pOutBuffer = READ_NAND();
                pOutBuffer++;
            }

            Cmd = CMD_READ_A1;
            WRITE_NAND_COMMAND(Cmd);
            WRITE_NAND_ADDRESS(0x00);
            WRITE_NAND_ADDRESS((uSectorAddr >> 0) & 0xFF);
            WRITE_NAND_ADDRESS((uSectorAddr >> 8) & 0xFF);
            WRITE_NAND_ADDRESS((uSectorAddr >> 16) & 0xFF);

            NAND_WAIT_READY();
            /*
             * Need to be done twice, READY detected too early the first time? 
             */
            NAND_WAIT_READY();

            for (i = 0; i < (uBytesToRead / 2); i++) {
                *pOutBuffer = READ_NAND();
                pOutBuffer++;
            }
        }
    }

 exit:
    /*
     * Disable the chip 
     */
    NAND_DISABLE_CE();

    return bRet;
}

#else                           /* For large blocks */
static BOOL AT91F_NandReadSector(PSNandInfo pNandInfo, unsigned int uSectorAddr,
                                 unsigned char *pOutBuffer, unsigned int fZone)
{
    BOOL bRet = TRUE;

    unsigned int uBytesToRead, i;

    unsigned int Addr;

    /*
     * WARNING : During a read procedure you can't call the ReadStatus flash cmd
     * * The ReadStatus fill the read register with 0xC0 and then corrupt the read
     */

    /*
     * Enable the chip 
     */
    NAND_ENABLE_CE();

    /*
     * Write specific command, Read from start 
     */
    WRITE_NAND_COMMAND(CMD_READ_1);

    /*
     * Push offset address 
     */
    Addr = 0x00;
    switch (fZone) {
    case ZONE_DATA:
        uBytesToRead = pNandInfo->uDataNbBytes;
        break;
    case ZONE_INFO:
        uBytesToRead = pNandInfo->uSpareNbBytes;
        pOutBuffer += pNandInfo->uDataNbBytes;
        Addr = pNandInfo->uDataNbBytes;
        if (pNandInfo->uDataBusWidth) { /* 16 bits */
            Addr = Addr / 2;
            /*
             * Div 2 is because we address in word and not in byte 
             */
        }
        break;
    case ZONE_DATA | ZONE_INFO:
        uBytesToRead = pNandInfo->uSectorNbBytes;
        break;
    default:
        bRet = FALSE;
        goto exit;
    }
    AT91F_WriteLarge_BlkAdr(Addr);

    /*
     * Push sector address 
     */
    uSectorAddr >>= pNandInfo->uOffset;

    AT91F_WriteSectorAdr(uSectorAddr);

    WRITE_NAND_COMMAND(CMD_READ_2);

    /*
     * Wait for flash to be ready (can't pool on status, read upper WARNING) 
     */
    NAND_WAIT_READY();
    /*
     * Need to be done twice, READY detected too early the first time? 
     */
    NAND_WAIT_READY();

    /*
     * Read loop 
     */
    if (pNandInfo->uDataBusWidth) {
        /*
         * Div2 because of 16bits 
         */
        for (i = 0; i < uBytesToRead / 2; i++) {
            *((short *)pOutBuffer) = READ_NAND16();
            pOutBuffer += 2;
        }
    } else {
        for (i = 0; i < uBytesToRead; i++) {
            *pOutBuffer++ = READ_NAND();
        }
    }

 exit:
    /*
     * Disable the chip 
     */
    NAND_DISABLE_CE();

    return bRet;
}
#endif

//*----------------------------------------------------------------------------
//* \fn    IsGoodBlock
//* \brief Check if block is marked Bad
//*----------------------------------------------------------------------------
static BOOL IsGoodBlock(PSNandInfo pNandInfo, unsigned int uBlockNb,
                unsigned char *pOutBuffer)
{
    unsigned int i = 0;

    PSSectorInfo pSectorInfo;

    unsigned int uSectorAddr = uBlockNb * pNandInfo->uBlockNbData;

    // Read first page and second page spare zone to detect if block is bad
    for (i = 0; i < 2; i++) {
        AT91F_NandReadSector(pNandInfo,
                             uSectorAddr + i * pNandInfo->uDataNbBytes,
                             pOutBuffer, ZONE_INFO);
        pSectorInfo = (PSSectorInfo) & pOutBuffer[pNandInfo->uDataNbBytes];
        if (pSectorInfo->spare[pNandInfo->uBadBlockInfoOffset] != BAD_BLOCK_TAG) {
            /*
             * Bad block found 
             */
            return FALSE;
        }
    }

    return TRUE;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_NandRead
//* \brief Read Sector Algorithm
//*----------------------------------------------------------------------------
BOOL AT91F_NandRead(PSNandInfo pNandInfo, unsigned int uBlockNb,
                    unsigned int uSectorNb, unsigned int uSpareValue,
                    unsigned char *pOutBuffer)
{
    unsigned int uSectorAddr = uBlockNb * pNandInfo->uBlockNbData
        + uSectorNb * pNandInfo->uDataNbBytes;

    if (IsGoodBlock(pNandInfo, uBlockNb, pOutBuffer) == FALSE) {
        dbg_log(1, "Bad block: #%d\n\r", uBlockNb);
        return FALSE;
    }
#ifndef CONFIG_ENABLE_SW_ECC
    return AT91F_NandReadSector(pNandInfo, uSectorAddr, pOutBuffer, ZONE_DATA);
#else
    {
        BOOL ret;

        unsigned char hamming[48], error;

        ret = AT91F_NandReadSector(pNandInfo, uSectorAddr, pOutBuffer,
                                   ZONE_DATA | ZONE_INFO);

        if (ret != TRUE)
            return ret;
        NandSpareScheme_ReadEcc(pNandInfo->pSpareScheme,
                                pOutBuffer + pNandInfo->uDataNbBytes, hamming);

        error =
            Hamming_Verify256x(pOutBuffer, pNandInfo->uDataNbBytes, hamming);
        if (error && (error != Hamming_ERROR_SINGLEBIT)) {
            dbg_log(1, "ECC error!\n\r");
            return FALSE;
        }
    }
    return TRUE;
#endif
}

int read_nandflash(unsigned char *dst, unsigned long offset, int len)
{
    SNandInfo sNandInfo;

    PSNandInitInfo pNandInitInfo;

    unsigned char *pOutBuffer = dst;

    unsigned int blockIdx, badBlock, length, sizeToRead, nbSector, sectorIdx,
        dataLeft;

    nandflash_hw_init();

    /*
     * Read Nand Chip ID 
     */
    pNandInitInfo = AT91F_NandReadID();

    if (!pNandInitInfo) {
        dbg_log(DEBUG_INFO, "\n\r-E- No NandFlash detected !!!\n\r");
        return -1;
    }
	dbg_log(1, "Copy %d bytes from %d to %d\r\n", len, offset, dst);

	if (1)
	{
		unsigned long *p = (unsigned long *)0x20000000;
		unsigned long pattern[4];
		unsigned int i;

		dbg_log(1, "Forget the above line, do DDR test!\n\r");

		pattern[0] = 0x12345678;
		pattern[1] = 0x87654321;
		pattern[2] = 0x55aa55aa;
		pattern[3] = 0xaa55aa55;

		for (i = 0; i < 8 * 1024 * 1024; i += 16) {
			p[i + 0] = pattern[0];
			p[i + 1] = pattern[1];
			p[i + 2] = pattern[2];
			p[i + 3] = pattern[3];

			if ((i % (1024 * 1024)) == 0)
				dbg_log(1, "%d M bytes are written!\n\r", i / 1024 / 1024);
		}

		for (i = 0; i < 8 * 1024 * 1024; i += 16) {
			if (p[i + 0] != pattern[0]) {
				dbg_log(1, "Mis-match, offset: %d, value: %d, should be: %d\n\r",
						i + 0, p[i + 0], pattern[0]);
			}
			if (p[i + 1] != pattern[1]) {
				dbg_log(1, "Mis-match, offset: %d, value: %d, should be: %d\n\r",
						i + 1, p[i + 1], pattern[1]);
			}
			if (p[i + 2] != pattern[2]) {
				dbg_log(1, "Mis-match, offset: %d, value: %d, should be: %d\n\r",
						i + 2, p[i + 2], pattern[2]);
			}
			if (p[i + 0] != pattern[0]) {
				dbg_log(1, "Mis-match, offset: %d, value: %d, should be: %d\n\r",
						i + 3, p[i + 3], pattern[3]);
			}

			if ((i % (1024 * 1024)) == 0)
				dbg_log(1, "%d M bytes have been tested!\n\r", i / 1024 / 1024);
		}

		dbg_log(1, "\n\r\n\r------ Done ------\r\n");
	}

    /*
     * Initialize NandInfo Structure 
     */
    AT91F_NandInit(&sNandInfo, pNandInitInfo);

    if (!sNandInfo.uDataBusWidth)
        nandflash_cfg_8bits_dbw_init();

    /*
     * Initialize the block offset 
     */
    blockIdx = offset / sNandInfo.uBlockNbData;
    /*
     * Initialize the number of bad blocks 
     */
    badBlock = 0;

    length = len;

    while (length > 0) {
        /*
         * Read a buffer corresponding to a block in the origin file 
         */
        if (length < sNandInfo.uBlockNbData) {
            sizeToRead = length;
        } else {
            sizeToRead = sNandInfo.uBlockNbData;
        }

        /*
         * Adjust the number of sectors to read 
         */
        nbSector = sizeToRead / sNandInfo.uDataNbBytes;
        if (sizeToRead % sNandInfo.uDataNbBytes) {
            nbSector++;
        }

        /*
         * Loop until a valid block has been read 
         */
        while (1) {
            /*
             * Read the sectors 
             */
            for (sectorIdx = 0; sectorIdx < nbSector; sectorIdx++) {
                dataLeft = sizeToRead - (sectorIdx * sNandInfo.uDataNbBytes);
                if (dataLeft < sNandInfo.uDataNbBytes) {
                    dataLeft =
                        sizeToRead - (sectorIdx * sNandInfo.uDataNbBytes);
                } else {
                    dataLeft = sNandInfo.uDataNbBytes;
                }

                /*
                 * Read the sector 
                 */
                if (AT91F_NandRead(&sNandInfo, blockIdx, sectorIdx, ZONE_DATA,
                                   pOutBuffer) == FALSE) {
                    // Move to next block
                    break;
                } else {
                    pOutBuffer += sNandInfo.uDataNbBytes;
                }
            }

            blockIdx++;
            /*
             * The full block is valid, then  exit the loop 
             */
            if (sectorIdx >= nbSector)
                break;
        }

        /*
         * Decrement length 
         */
        length -= sizeToRead;
    }
	dbg_log(1, "\r\n");

    return 0;
}

#endif                          /* CONFIG_NANDFLASH */
