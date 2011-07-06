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

#ifndef NAND_WAIT_READY
extern void NAND_WAIT_READY();
#endif

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
#undef CONFIG_USE_PMECC
#if defined(CPU_HAS_PMECC) && !defined(CONFIG_ENABLE_SW_ECC)
#define CONFIG_USE_PMECC
#endif

#ifdef CONFIG_USE_PMECC
#define TT_MAX  25

/* ECC offset in spare area */
#define ECC_START_ADDR		48
#define ECC_END_ADDR		63

#ifdef CONFIG_AT91SAM9X5EK
#define PMECC_ALGO_FCT_ADDR     0x00100008
#define LOOKUP_TABLE_ALPHA_TO   0x10C000;
#define LOOKUP_TABLE_INDEX_OF   0x108000;
#endif

struct _PMECC_paramDesc_struct {
    unsigned int pageSize;
    unsigned int spareSize;
    unsigned int sectorSize;  // 0 for 512, 1 for 1024 bytes, like in PMECCFG register
    unsigned int errBitNbrCapability;
    unsigned int eccSizeByte;
    unsigned int eccStartAddr;
    unsigned int eccEndAddr;

    unsigned int nandWR;
    unsigned int spareEna;
    unsigned int modeAuto;
    unsigned int clkCtrl;
    unsigned int interrupt;

    int tt;
    int mm;
    int nn;

    short *alpha_to;
    short *index_of;

    short partialSyn[100];
    short si[100];

    /* sigma table */
    short smu[TT_MAX + 2][2 * TT_MAX + 1];
    /* polynom order */
    short lmu[TT_MAX + 1];

} PMECC_paramDesc_struct;

typedef int (*PMECC_CorrectionAlgo_Rom_Func)(unsigned long pPMECC,
                                unsigned long pPMERRLOC,
                                struct _PMECC_paramDesc_struct *PMECC_desc,
                                unsigned int PMECC_status,
                                void *pageBuffer);

PMECC_CorrectionAlgo_Rom_Func PMECC_CorrectionAlgo;

#endif /* CONFIG_USE_PMECC */

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
    case 0x2cdc:
        info.uNandNbBlocks = 0x1000;
        break;
    case 0x2cda:
    case 0x2caa:
    case 0xecda:
    case 0xecaa:
    case 0x20aa:
    case 0xadda:
        break;
    default:
        return 0;
    }

    return &info;
}

static void AT91F_NandInit(PSNandInfo pNandInfo, PSNandInitInfo pNandInitInfo)
{
    unsigned int uSectorSize, i = 0;

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

static void reset_nandflash(void)
{
    NAND_ENABLE_CE();
    WRITE_NAND_COMMAND(0xFF);
    NAND_WAIT_READY();
    NAND_WAIT_READY();
    NAND_DISABLE_CE();
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

#ifdef CONFIG_USE_PMECC
    unsigned int bch_status;
    unsigned char *pbuf = pOutBuffer;

    PMECC_paramDesc_struct.modeAuto = AT91C_BCH_AUTO_ENA;
    PMECC_paramDesc_struct.nandWR = 0;

    writel(AT91C_BCH_RST, AT91C_BCH_PMECCTRL);
    writel(AT91C_BCH_DISABLE, AT91C_BCH_PMECCTRL);
    writel(PMECC_paramDesc_struct.errBitNbrCapability |
        PMECC_paramDesc_struct.sectorSize |
        PMECC_paramDesc_struct.pageSize |
        PMECC_paramDesc_struct.nandWR |
        PMECC_paramDesc_struct.spareEna |
        PMECC_paramDesc_struct.modeAuto, AT91C_BCH_PMECCFG0);
    writel(PMECC_paramDesc_struct.spareSize - 1, AT91C_BCH_PMECCFG1);
    writel(PMECC_paramDesc_struct.eccStartAddr, AT91C_BCH_PMECCFG2);
    writel(PMECC_paramDesc_struct.eccEndAddr, AT91C_BCH_PMECCFG3);
    writel(PMECC_paramDesc_struct.clkCtrl, AT91C_BCH_PMECCFG4);
    writel(0xFF, AT91C_BCH_PMECCIDR);
    writel(AT91C_BCH_ENABLE, AT91C_BCH_PMECCTRL);
    writel(AT91C_BCH_DATAMODE, AT91C_BCH_PMECCTRL);

    fZone = ZONE_DATA | ZONE_INFO;
#endif
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

#ifdef CONFIG_USE_PMECC
    while (readl(AT91C_BCH_PMECCSR) & 1)
        ;
    bch_status = readl(AT91C_BCH_PMECCISR);
    i = 0;
    if (bch_status)
        i = PMECC_CorrectionAlgo(AT91C_BCH_PMECCFG0, AT91C_BCHEL_PMECCELCR,
            &PMECC_paramDesc_struct, bch_status, pbuf);
    if (i != 0)
        bRet = FALSE;
#endif

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
            dbg_log(1, "Hamming ECC error!\n\r");
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
    reset_nandflash();

    /*
     * Read Nand Chip ID 
     */
    pNandInitInfo = AT91F_NandReadID();

    if (!pNandInitInfo) {
        dbg_log(DEBUG_INFO, "\n\r-E- No NandFlash detected !!!\n\r");
        return -1;
    }
    dbg_log(1, "Copy %d bytes from %d to %d\r\n", len, offset, dst);

    /*
     * Initialize NandInfo Structure 
     */
    AT91F_NandInit(&sNandInfo, pNandInitInfo);

    if (!sNandInfo.uDataBusWidth)
        nandflash_cfg_8bits_dbw_init();

#ifdef CONFIG_USE_PMECC
    PMECC_CorrectionAlgo = (PMECC_CorrectionAlgo_Rom_Func)
        (*(unsigned int *)PMECC_ALGO_FCT_ADDR);
    switch(sNandInfo.uDataNbBytes) {
    case 2048:
        PMECC_paramDesc_struct.pageSize = AT91C_BCH_PAGESIZE_4;
        PMECC_paramDesc_struct.sectorSize = AT91C_BCH_BLKSIZE_512;
        PMECC_paramDesc_struct.spareSize = 64;
        PMECC_paramDesc_struct.errBitNbrCapability = 0; /* 2bits correction */
        PMECC_paramDesc_struct.eccSizeByte = 16;
        PMECC_paramDesc_struct.eccStartAddr = ECC_START_ADDR;
        PMECC_paramDesc_struct.eccEndAddr = ECC_END_ADDR;
        PMECC_paramDesc_struct.spareEna = 0;
        PMECC_paramDesc_struct.clkCtrl = 2;  /* stated in datasheet */
        PMECC_paramDesc_struct.interrupt = 0;
        PMECC_paramDesc_struct.tt = 2;
        PMECC_paramDesc_struct.mm = 13;
        PMECC_paramDesc_struct.nn = (1 << PMECC_paramDesc_struct.mm) - 1;
        PMECC_paramDesc_struct.alpha_to = (short *)LOOKUP_TABLE_ALPHA_TO;
        PMECC_paramDesc_struct.index_of = (short *)LOOKUP_TABLE_INDEX_OF;
        break;
    case 512:
    case 1024:
    case 4096:
        /* TODO */
    default:
        dbg_log(1, "Not supported page size: %d\n\r", sNandInfo.uDataNbBytes);
        return -1;
    }
#endif

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

    return 0;
}

#endif /* CONFIG_NANDFLASH */
