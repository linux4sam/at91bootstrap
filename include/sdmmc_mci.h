/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation

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
 */

//------------------------------------------------------------------------------
/// \page "sdcard sd mode initialization and identification"
///
/// !Purpose
/// 
/// sdcard sd mode initialization and identification sequence
///
/// !Description
/// - Host sends Cmd0 to do card reset, card is in "idle state".
/// - Host sends Cmd8 and checks the response of the card, only sdcard supports physical
///    layer version 2.00 will response correctly to Cmd8, and this command is mandatory to be
///    sent before ACmd41 for sdcard which support physical layer version 2.00, to enable new
///    functions or to validate a dual-voltage card.
///       - refer to "If Cmd8 response ok" branch for the initialize of sdcard 2.0.
///       - refer to "If Cmd8 response fail" branch for the initialize of sdcard 1.x, mmc card, sdcard2.0
///          with invalid voltage.
/// - If Cmd8 response ok
///       - Host sends ACmd41* with argument "HCS" equal to "1". 
///       - If the response to ACmd41 failed, it means the card does not match the voltage 
///          desired by the host, the card will be put into inactive state, initialize ends.
///       - If the response with "CCS" equal to "1", the card is a version 2.0 high capacity sdcard, 
///          refer to "Card Initialize" for the succeeding initialize sequence.
///       - If the response with "CCS" equal to "0", the card is a version 2.0 standard capacity sdcard.
///          refer to "Card Initialize" for the succeeding initialize sequence.
/// - If Cmd8 response fail
///       - Host sends ACmd41* argument "HCS" equal to "0".
///       - If the response to ACmd41 ok, the card is a version 1.x sdcard, refer to "Card Initialize" for 
///          the succeeding initialize sequence.
///       - If the response to ACmd41 fails
///          - Host sends Cmd0 to reset card.
///          - Host sends Cmd1 with argument "hdSupport" equal to "1" to card.
///          - If card has response to Cmd1, the card is a MMC card, refer to "Card Initialize" for the 
///             succeeding initialize sequence. Furthermore, if the response with bit[30:29] equal to 
///             "00" or "11", the card is a High Density MMC, else the card is a standard MMC.
///          - If card has no response to Cmd1, the card is either an unknown card or a card does 
///             not match host's voltage, the initialize ends.
/// - Card Initialize
///       - Host sends Cmd2 to get the its unique card identification number (CID).
///       - Host sends Cmd3 to ask the card to publish a new relative card address (RCA), once the 
///          RCA is received the card state changes to the "stand-by state".
///       - Host sends Cmd9 to get the Card Specific Data (CSD).
///       - At this stage, the initialization and identification process is over, the following steps are done 
///          for the sdcard's succeeding operation.
///       - Host sends Cmd13 to obtain the card status, make sure the card is "ready-for-data".
///       - Host sends Cmd7 to transit card in "transfer state".
///       - If card is a sdcard*, hosts send ACmd6 to set bus to 4-wire mode.
///       - If card is a mmc card, the bus is set as 1-wire mode.
///
///     \note Send Cmd55 before send ACmd41. \endnote
///     \note sdcard include ver 1.x sdcard, ver2.0 standard capacity sdcard, ver2.0 high capacity sdcard \endnote
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "sdcard sd mode write"
///
/// !Purpose
/// 
/// sdcard sd mode write process
///
/// !Description
/// - Make sure sdcard is under "transfer state", if the sdcard is under other state, host will send
///    Cmd12 to stop the current operation and to transit sdcard to "stand-by state".
/// - Host sends Cmd13 to check sdcard's status, to make sure sdcard is "ready-for-data".
/// - Host sends Cmd25 to do multiple blocks write, the address here is different between high capacity
///    sdcard and normal sdcard, the address of SDHC is equal to the block number, while normal sdcard's
///    address is equal to  block number times 512.
///
/// !Write Optimization
/// - To optimize the write multiple blocks, try to keep the sdcard in the "rcv state" as long as possible.
///    after send WRITE_MULTIPLE_BLOCK command, set the block number in the MCI_BLKR as 0, each time a 
///    new write start, do not re-send the WRITE_MULTIPLE_BLOCK command, just re-configure the PDC. In 
///    this case, host does not have to send STOP_TRANSMISSION to transfer the sdcard's state and the
///    performance is optimized.
/// - MoveToTransferState will check the state of the sdcard, and send STOP_TRANSMISSION if need
///   to transfer state. Normally this function is called between the state tranfer.
/// - ContinuousWrite will be called if WRITE_MULTIPLE_BLOCK already been sent and this function
///    will not re-send the write command, but will re-configure PDC accordingly.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "sdcard sd mode read"
///
/// !Purpose
/// 
/// sdcard sd mode read process
///
/// !Description
/// - Make sure sdcard is under "transfer state", if the sdcard is under other state, host will send
///    Cmd12 to stop the current operation and to transit sdcard to "stand-by state".
/// - Host sends Cmd13 to check sdcard's status, to make sure sdcard is "ready-for-data".
/// - Host sends Cmd18 to do multiple blocks read, the address here is different between high capacity
///    sdcard and normal sdcard, the address of SDHC is equal to the block number, while normal sdcard's
///    address is equal to  block number times 512.
/// 
/// !Read Optimization
/// - To optimize the read multiple blocks, try to keep the sdcard in the "data state" as long as possible.
///    after send READ_MULTIPLE_BLOCK command, set the block number in the MCI_BLKR as 0, each time a 
///    new read start, do not re-send the READ_MULTIPLE_BLOCK command, just re-configure the PDC. In this
///    case, host does not have to send STOP_TRANSMISSION to transfer the sdcard's state and the
///    performance is optimized.
/// - MoveToTransferState will check the state of the sdcard, and send STOP_TRANSMISSION if need
///   to transfer state. Normally this function is called between the state tranfer.
/// - ContinuousRead will be called if READ_MULTIPLE_BLOCK already been sent and this function
///    will not re-send the read command, but will re-configure PDC accordingly.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "sdhc"
///
/// !Purpose
/// 
/// highlight of sdhc
///
/// !Sdhc initialization and identification
///
///   - Refer to page "sdcard sd mode initialization and identification" for the initialization and identification
///       sequence of a sdhc.
/// 
/// !Functional difference between sdhc and standard capacity sdcard
///
/// - Command argument is different:
///   - Sdhc uses block address format in memory access commands*, block length is fixed to 512 bytes.
///   - Standard capacity sdcard uses byte address format in memory access commands, block length
///       is defined in Cmd16.
/// - Partial access and misalign access are disabled in sdhc as the block address is used.
/// - Sdhc does not support write-protected commands (Cmd28, Cmd29, Cmd30).
///
/// \note Memory access commands means block read commands (CMD17, CMD18), block write commands 
///   (CMD24, CMD25), and block erase commands (CMD32, CMD33).
///
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "sdmmc_mci"
///
/// !Purpose
/// 
/// Implementation for sdcard sd mode physical layer driver. Supply a set of sdcard sd mode's
/// interface.
///
/// !Usage
///
/// -# SD_Init: Run the SDcard initialization sequence
/// -# SD_MCI_Init : Run the SDcard SD Mode initialization sequence
/// -# SD_Stop: Stop the SDcard by sending Cmd12
/// -# SD_ReadBlock : Read blocks of data
/// -# SD_WriteBlock : Write blocks of data
/// -# Cmd0 : Resets all cards to idle state
/// -# Cmd1 : MMC send operation condition command
/// -# Cmd2 : Asks any card to send the CID numbers on the CMD line
/// -# Cmd3 : Ask the card to publish a new relative address
/// -# Cmd7 : Command toggles a card between the stand-by and transfer states or between
///                the programming and disconnect states
/// -# Cmd8 : Sends SD Memory Card interface condition, which includes host supply voltage 
///                information and asks the card whether card supports voltage
/// -# Cmd9 : Addressed card sends its card-specific data (CSD) on the CMD line
/// -# Cmd12 : Forces the card to stop transmission
/// -# Cmd13 : Addressed card sends its status register
/// -# Cmd16 : Set block length
/// -# Cmd18 : Read multiple blocks
/// -# Cmd25 : Write multiple blocks
/// -# Cmd55 : App command, should be sent before application specific command
/// -# Acmd6 : Defines the data bus width 
/// -# Acmd41 : Asks to all cards to send their operations conditions
/// -# CmdEMMC8 : Sends eMMC EXT_CSD command
/// -# CmdEMMC6 : Switches the mode of operation of the selected card or modifies the
///                        EXT_CSD registers
//------------------------------------------------------------------------------

#ifndef SDMMC_MCI_H
#define SDMMC_MCI_H

//------------------------------------------------------------------------------
//         Header
//------------------------------------------------------------------------------

#include "part.h"
#if !defined(MCI2_INTERFACE)
#include "mci.h"
#else
#include "mci_hs.h"
#endif

//------------------------------------------------------------------------------
//         Constants
//------------------------------------------------------------------------------

/// There was an error with the SD driver.
#define SD_ERROR_DRIVER          1
/// The SD card did not answer the command.
#define SD_ERROR_NORESPONSE      2
/// The SD card did not answer the command.
#define SD_ERROR_NOT_INITIALIZED 3
/// The SD card is busy
#define SD_ERROR_BUSY            4
/// The operation is not supported
#define SD_ERROR_NOT_SUPPORT     5

/// SD card block size in bytes.
#define SD_BLOCK_SIZE           512
/// SD card block size binary shift value
#define SD_BLOCK_SIZE_BIT       9

//- MMC Card Command Types
/// Broadcast commands (bc), no response
#define MMC_CCT_BC             0
/// Broadcase commands with response (bcr)
#define MMC_CCT_BCR            1
/// Addressed commands (ac), no data transfer on DAT lines
#define MMC_CCT_AC             2
/// Addressed data transfer commands (adtc), data transfer on DAT lines
#define MMC_CCT_ADTC           3

//- MMC Card Command Classes (CCC)
/// Class 0: basic
#define MMC_CCC_BASIC               0
/// Class 1: stream read
#define MMC_CCC_STREAM_READ         1
/// Class 2: block read
#define MMC_CCC_BLOCK_READ          2
/// Class 3: stream write
#define MMC_CCC_STREAM_WRITE        3
/// Class 4: block write
#define MMC_CCC_BLOCK_WRITE         4
/// Class 5: erase
#define MMC_CCC_ERASE               5
/// Class 6: write protection
#define MMC_CCC_WRITE_PROTECTION    6
/// Class 7: lock card
#define MMC_CCC_LOCK_CARD           7
/// Class 8: application specific
#define MMC_CCC_APP_SPEC            8
/// Class 9: I/O mode
#define MMC_CCC_IO_MODE             9

//- MMC/SD Card Command Response Type
/// R1 (normal response command), 48bits
#define MMC_RESP_R1                 1
#define SD_RESP_R1                  MMC_RESP_R1
/// R1b: busy signal transmitted on the data line DAT0
#define MMC_RESP_R1b                1
#define SD_RESP_R1b                 MMC_RESP_R1b
/// R2: 136bits, CID, CSD register
#define MMC_RESP_R2                 2
#define SD_RESP_R2                  MMC_RESP_R2
/// R3: 48bits, OCR
#define MMC_RESP_R3                 3
#define SD_RESP_R3                  MMC_RESP_R3
/// R4 (Fast I/O), 48bits
#define MMC_RESP_R4                 4
/// R5 (Interrupt request), 48bits
#define MMC_RESP_R5                 5
/// R6 (Published RCA response), 48bits
#define SD_RESP_R6                  6
/// R7 (Card interface condition), 48bits
#define SD_RESP_R7                  7

//- MMC Card CMD6 access mode
#define MMC_SWITCH_CMDSET           0
#define MMC_SWITCH_SETBITS          1
#define MMC_SWITCH_CLRBITS          2
#define MMC_SWITCH_WRITE            3

//-MMC Boot partition enable
/// Boot partition 1 enabled for boot
#define MMC_BOOT_PART_1             1
/// Boot partition 2 enabled for boot
#define MMC_BOOT_PART_2             2
/// User area enabled for boot
#define MMC_BOOT_PART_USER          7

//-MMC Boot partition access
/// R/W boot partition 1
#define MMC_BOOT_ACC_PART1          1
/// R/W boot partition 2
#define MMC_BOOT_ACC_PART2          2

//------------------------------------------------------------------------------
//         Macros
//------------------------------------------------------------------------------

// CID register access macros (128 bits, 4 * 32 bits).
#define SD_CID(pSd, bitfield, bits)   (  (pSd->cid[3-(bitfield)/32] >> ((bitfield)%32)) & ((1 << (bits)) - 1))
#define SD_CID_MID(pSd)               SD_CID(pSd, 120, 8)       ///< Manufacturer ID
#define SD_CID_BGA(pSd)               SD_CID(pSd, 112, 2)       ///< Card/BGA(eMMC)
#define SD_CID_CBS(pSd)               SD_CID(pSd, 112, 2)       ///< Card/BGA(eMMC)
#define SD_CID_OID_BYTE_1(pSd)        SD_CID(pSd, 112, 8)       ///< OEM/Application ID byte 1
#define SD_CID_OID_BYTE_0(pSd)        SD_CID(pSd, 104, 8)       ///< OEM/Application ID byte 0
#define SD_CID_PNM_BYTE_4(pSd)        SD_CID(pSd,  96, 8)       ///< Product revision byte 4
#define SD_CID_PNM_BYTE_3(pSd)        SD_CID(pSd,  88, 8)       ///< Product revision byte 3
#define SD_CID_PNM_BYTE_2(pSd)        SD_CID(pSd,  80, 8)       ///< Product revision byte 2
#define SD_CID_PNM_BYTE_1(pSd)        SD_CID(pSd,  72, 8)       ///< Product revision byte 1
#define SD_CID_PNM_BYTE_0(pSd)        SD_CID(pSd,  64, 8)       ///< Product revision byte 0
#define SD_CID_PRV_1(pSd)             SD_CID(pSd,  24, 8)       ///< Product serial number 1
#define SD_CID_PRV_2(pSd)             SD_CID(pSd,  32,24)       ///< Product serial number 2
#define SD_CID_MDT_YEAR(pSd)          (SD_CID(pSd, 12, 8))+2000 ///< Manufacturing date year
#define SD_CID_MDT_MONTH(pSd)         SD_CID(pSd,   8, 4)       ///< Manufacturing date month
#define SD_CID_CRC(pSd)               SD_CID(pSd,   1, 7)       ///< CRC7 checksum

// CSD register access macros (128 bits, 4 * 32 bits).
#define SD_CSD(pSd, bitfield, bits)   ((((pSd)->csd)[3-(bitfield)/32] >> ((bitfield)%32)) & ((1 << (bits)) - 1))
#define SD_CSD_STRUCTURE(pSd)          SD_CSD(pSd, 126, 2)      ///< CSD structure 00b  Version 1.0 01b version 2.0 High Cap
#define SD_CSD_SPEC_VERS(pSd)          SD_CSD(pSd, 122, 4)      ///< System Specification Version Number
#define SD_CSD_TAAC(pSd)               SD_CSD(pSd, 112, 8)      ///< Data read-access-time-1
#define SD_CSD_NSAC(pSd)               SD_CSD(pSd, 104, 8)      ///< Data read access-time-2 in CLK cycles
#define SD_CSD_TRAN_SPEED(pSd)         SD_CSD(pSd, 96,  8)      ///< Max. data transfer rate
#define SD_CSD_CCC(pSd)                SD_CSD(pSd, 84, 12)      ///< Card command class
#define SD_CSD_READ_BL_LEN(pSd)        SD_CSD(pSd, 80,  4)      ///< Max. read data block length
#define SD_CSD_READ_BL_PARTIAL(pSd)    SD_CSD(pSd, 79,  1)      ///< Bartial blocks for read allowed
#define SD_CSD_WRITE_BLK_MISALIGN(pSd) SD_CSD(pSd, 78,  1)      ///< Write block misalignment
#define SD_CSD_READ_BLK_MISALIGN(pSd)  SD_CSD(pSd, 77,  1)      ///< Read block misalignment
#define SD_CSD_DSR_IMP(pSd)            SD_CSD(pSd, 76,  1)      ///< DSP implemented
#define SD_CSD_C_SIZE(pSd)             ((SD_CSD(pSd, 72,  2) << 10) + \
                                        (SD_CSD(pSd, 64,  8) << 2)  + \
                                        SD_CSD(pSd, 62,  2))    ///< Device size
#define SD_CSD_C_SIZE_HC(pSd)          ((SD_CSD(pSd, 64,  6) << 16) + \
                                        (SD_CSD(pSd, 56,  8) << 8)  + \
                                        SD_CSD(pSd, 48,  8))    ///< Device size v2.0 High Capacity
#define SD_CSD_VDD_R_CURR_MIN(pSd)     SD_CSD(pSd, 59,  3)      ///< Max. read current @VDD min
#define SD_CSD_VDD_R_CURR_MAX(pSd)     SD_CSD(pSd, 56,  3)      ///< Max. read current @VDD max
#define SD_CSD_VDD_W_CURR_MIN(pSd)     SD_CSD(pSd, 53,  3)      ///< Max. write current @VDD min
#define SD_CSD_VDD_W_CURR_MAX(pSd)     SD_CSD(pSd, 50,  3)      ///< Max. write current @VDD max
#define SD_CSD_C_SIZE_MULT(pSd)        SD_CSD(pSd, 47,  3)      ///< Device size multiplier
#define SD_CSD_ERASE_BLK_EN(pSd)       SD_CSD(pSd, 46,  1)      ///< Erase single block enable
#define MMC_CSD_ERASE_BLK_EN(pSd)      SD_CSD(pSd, 46,  1)      ///< Erase single block enable
#define MMC_CSD_ERASE_GRP_SIZE(pSd)    SD_CSD(pSd, 42,  4)      ///< Erase group size
#define SD_CSD_ERASE_GRP_MULT(pSd)     SD_CSD(pSd, 37,  4)      ///< Erase group size multiplier
#define SD_CSD_SECTOR_SIZE(pSd)        ((SD_CSD(pSd, 40,  6) << 1) + SD_CSD(pSd, 39,  1))       ///< Erase sector size
#define SD_CSD_WP_GRP_SIZE(pSd)        SD_CSD(pSd, 32,  7)      ///< Write protect group size
#define SD_CSD_WP_GRP_ENABLE(pSd)      SD_CSD(pSd, 31,  1)      ///< write protect group enable
#define SD_CSD_R2W_FACTOR(pSd)         SD_CSD(pSd, 26,  3)      ///< Write speed factor
#define SD_CSD_WRITE_BL_LEN(pSd)       ((SD_CSD(pSd, 24,  2) << 2) + SD_CSD(pSd, 22,  2))       ///< Max write block length
#define SD_CSD_WRITE_BL_PARTIAL(pSd)   SD_CSD(pSd, 21,  1)      ///< Partial blocks for write allowed
#define SD_CSD_CONTENT_PROT_APP(pSd)   SD_CSD(pSd, 16,  1)      ///< File format group
#define SD_CSD_FILE_FORMAT_GRP(pSd)    SD_CSD(pSd, 15,  1)      ///< File format group
#define SD_CSD_COPY(pSd)               SD_CSD(pSd, 14,  1)      ///< Copy flag (OTP)
#define SD_CSD_PERM_WRITE_PROTECT(pSd) SD_CSD(pSd, 13,  1)      ///< Permanent write protect
#define SD_CSD_TMP_WRITE_PROTECT(pSd)  SD_CSD(pSd, 12,  1)      ///< Temporary write protection
#define SD_CSD_FILE_FORMAT(pSd)        SD_CSD(pSd, 10,  2)      ///< File format
#define SD_CSD_ECC(pSd)                SD_CSD(pSd,  8,  2)      ///< CRC
#define SD_CSD_CRC(pSd)                SD_CSD(pSd,  1,  7)      ///< CRC
#define SD_CSD_MULT(pSd)               (1 << (SD_CSD_C_SIZE_MULT(pSd) + 2))
#define SD_CSD_BLOCKNR(pSd)            ((SD_CSD_C_SIZE(pSd) + 1) * SD_CSD_MULT(pSd))
#define SD_CSD_BLOCKNR_HC(pSd)         ((SD_CSD_C_SIZE_HC(pSd) + 1) * 1024)
#define SD_CSD_BLOCK_LEN(pSd)          (1 << SD_CSD_READ_BL_LEN(pSd))
#define SD_CSD_TOTAL_SIZE(pSd)         (SD_CSD_BLOCKNR(pSd) * SD_CSD_BLOCK_LEN(pSd))
#define SD_CSD_TOTAL_SIZE_HC(pSd)      ((SD_CSD_C_SIZE_HC(pSd) + 1) * 512* 1024)
#define SD_TOTAL_SIZE(pSd)             ((pSd)->totalSize)
#define SD_TOTAL_BLOCK(pSd)            ((pSd)->blockNr)

// SCR register access macros (64 bits, 2 * 32 bits, 8 * 8 bits).
#define SD_EXT_OFFSET_SD_SCR                0   // DW
#define SD_SCR(pSd, bitfield, bits) \
    ( ((char*)(pSd)->extData)[7 - ((bitfield)/8)] >> ((bitfield)%8) \
                                                  & ((1 << (bits)) - 1) \
    )
#define SD_SCR_SCR_STRUCTURE(pSd)           SD_SCR(pSd, 60, 4)
#define     SD_SCR_SCR_STRUCTURE_1_0        0
#define SD_SCR_SD_SPEC(pSd)                 SD_SCR(pSd, 56, 4)
#define     SD_SCR_SD_SPEC_1_0_01           0
#define     SD_SCR_SD_SPEC_1_10             1
#define     SD_SCR_SD_SPEC_2_00             2
#define SD_SCR_DATA_STAT_AFTER_ERASE(pSd)   SD_SCR(pSd, 55, 1)
#define SD_SCR_SD_SECURITY(pSd)             SD_SCR(pSd, 52, 3)
#define     SD_SCR_SD_SECURITY_NO           0
#define     SD_SCR_SD_SECURITY_NOTUSED      1
#define     SD_SCR_SD_SECURITY_1_01         2
#define     SD_SCR_SD_SECURITY_2_00         3
#define SD_SCR_SD_BUS_WIDTHS(pSd)           SD_SCR(pSd, 48, 4)
#define     SD_SCR_SD_BUS_WIDTH_1BITS       (1 << 0)
#define     SD_SCR_SD_BUS_WIDTH_4BITS       (1 << 2)

// SD Status access macros (512 bits, 16 * 32 bits, 64 * 8 bits).
#define SD_EXT_OFFSET_SD_STAT               2   // DW
#define SD_STAT(pSd, bitfield, bits) \
    ( ((char*)&(pSd)->extData[2])[63 - ((bitfield)/8)] >> ((bitfield)%8) \
                                                  & ((1 << (bits)) - 1) \
    )
/// Bus width, 00: default, 10:4-bit
#define SD_STAT_DAT_BUS_WIDTH(pSd)           SD_STAT(pSd, 510, 2)
#define     SD_STAT_DATA_BUS_WIDTH_1BIT      0x0
#define     SD_STAT_DATA_BUS_WIDTH_4BIT      0x2
/// Secured Mode
#define SD_STAT_SECURED_MODE(pSd)            SD_STAT(pSd, 509, 1)
/// SD Memory Cards as defined in 1.01~2.00
#define SD_STAT_SD_CARD_TYPE(pSd)           (SD_STAT(pSd, 480, 8) \
                                           + (SD_STAT(pSd, 488, 8) << 8) )
/// STD: ThisSize*Multi*BlockLen, HC: Size in bytes
#define SD_STAT_SIZE_OF_PROTECTED_AREA(pSd) (SD_STAT(pSd, 448, 8) \
                                           + (SD_STAT(pSd, 456, 8) <<  8) \
                                           + (SD_STAT(pSd, 464, 8) << 16) \
                                           + (SD_STAT(pSd, 472, 8) << 24) )
/// Speed Class, value can be calculated by Pw/2
#define SD_STAT_SPEED_CLASS(pSd)             SD_STAT(pSd, 440, 8)
#define     SD_STAT_SPEED_CLASS_0            0
#define     SD_STAT_SPEED_CLASS_2            1  // >= 2MB/s
#define     SD_STAT_SPEED_CLASS_4            2  // >= 4MB/s
#define     SD_STAT_SPEED_CLASS_6            3  // >= 6MB/s
/// 8-bit, by 1MB/s step.
#define SD_STAT_PERFORMANCE_MOVE(pSd)        SD_STAT(pSd, 432, 8)
/// AU Size, in power of 2 from 16KB
#define SD_STAT_AU_SIZE(pSd)                 SD_STAT(pSd, 428, 4)
#define     SD_STAT_AU_SIZE_16K              1
#define     SD_STAT_AU_SIZE_32K              2
#define     SD_STAT_AU_SIZE_64K              3
#define     SD_STAT_AU_SIZE_128K             4
#define     SD_STAT_AU_SIZE_256K             5
#define     SD_STAT_AU_SIZE_512K             6
#define     SD_STAT_AU_SIZE_1M               7
#define     SD_STAT_AU_SIZE_2M               8
#define     SD_STAT_AU_SIZE_4M               9
/// 16-bit, number of AUs erased.
#define SD_STAT_ERASE_SIZE(pSd)             (SD_STAT(pSd, 408, 8) \
                                          + (SD_STAT(pSd, 416, 8) << 8) )
#define SD_STAT_ERASE_TIMEOUT(pSd)           SD_STAT(pSd, 402, 6)
#define SD_STAT_ERASE_OFFSET(pSd)            SD_STAT(pSd, 400, 2)

// SD Switch Status access macros (512 bits, 16 * 32 bits, 64 * 8 bits).
#define SD_SW_STAT(p, bitfield, bits) \
    ( ((char*)(p))[63 - ((bitfield)/8)] >> ((bitfield)%8) \
                                                  & ((1 << (bits)) - 1) \
    )
#define SD_SW_STAT_MAX_CURRENT_CONSUMPTION(p)   ( SD_SW_STAT(p, 496, 8) \
                                               + (SD_SW_STAT(p, 504, 8) << 8) )
#define SD_SW_STAT_FUN_GRP6_INFO(p)             ( SD_SW_STAT(p, 480, 8) \
                                               + (SD_SW_STAT(p, 488, 8) << 8) )
#define SD_SW_STAT_FUN_GRP5_INFO(p)             ( SD_SW_STAT(p, 464, 8) \
                                               + (SD_SW_STAT(p, 472, 8) << 8) )
#define SD_SW_STAT_FUN_GRP4_INFO(p)             ( SD_SW_STAT(p, 448, 8) \
                                               + (SD_SW_STAT(p, 456, 8) << 8) )
#define SD_SW_STAT_FUN_GRP3_INFO(p)             ( SD_SW_STAT(p, 432, 8) \
                                               + (SD_SW_STAT(p, 440, 8) << 8) )
#define SD_SW_STAT_FUN_GRP2_INFO(p)             ( SD_SW_STAT(p, 416, 8) \
                                               + (SD_SW_STAT(p, 424, 8) << 8) )
#define SD_SW_STAT_FUN_GRP1_INFO(p)             ( SD_SW_STAT(p, 400, 8) \
                                               + (SD_SW_STAT(p, 408, 8) << 8) )
#define SD_SW_STAT_FUN_GRP6_RC(p)                SD_SW_STAT(p, 396, 4)
#define SD_SW_STAT_FUN_GRP5_RC(p)                SD_SW_STAT(p, 392, 4)
#define SD_SW_STAT_FUN_GRP4_RC(p)                SD_SW_STAT(p, 388, 4)
#define SD_SW_STAT_FUN_GRP3_RC(p)                SD_SW_STAT(p, 384, 4)
#define SD_SW_STAT_FUN_GRP2_RC(p)                SD_SW_STAT(p, 380, 4)
#define SD_SW_STAT_FUN_GRP1_RC(p)                SD_SW_STAT(p, 376, 4)
#define     SD_SW_STAT_FUN_GRP_RC_ERROR         0xF
#define SD_SW_STAT_DATA_STRUCT_VER(p)            SD_SW_STAT(p, 368, 8)
#define SD_SW_STAT_FUN_GRP6_BUSY(p)             ( SD_SW_STAT(p, 352, 8) \
                                               + (SD_SW_STAT(p, 360, 8) << 8) )
#define SD_SW_STAT_FUN_GRP5_BUSY(p)             ( SD_SW_STAT(p, 336, 8) \
                                               + (SD_SW_STAT(p, 344, 8) << 8) )
#define SD_SW_STAT_FUN_GRP4_BUSY(p)             ( SD_SW_STAT(p, 320, 8) \
                                               + (SD_SW_STAT(p, 328, 8) << 8) )
#define SD_SW_STAT_FUN_GRP3_BUSY(p)             ( SD_SW_STAT(p, 304, 8) \
                                               + (SD_SW_STAT(p, 312, 8) << 8) )
#define SD_SW_STAT_FUN_GRP2_BUSY(p)             ( SD_SW_STAT(p, 288, 8) \
                                               + (SD_SW_STAT(p, 296, 8) << 8) )
#define SD_SW_STAT_FUN_GRP1_BUSY(p)             ( SD_SW_STAT(p, 272, 8) \
                                               + (SD_SW_STAT(p, 280, 8) << 8) )
#define SD_SW_STAT_FUN_GRP_FUN_BUSY(funNdx)     (1 << (funNdx))

// EXT_CSD register definition.
#define SD_EXTCSD_S_CMD_SET_INDEX              504      // Below belongs to Properties Segment
#define SD_EXTCSD_BOOT_INFO_INDEX              228
#define SD_EXTCSD_BOOT_SIZE_MULTI_INDEX        226
#define SD_EXTCSD_ACC_SIZE_INDEX               225
#define SD_EXTCSD_HC_ERASE_GRP_SIZE_INDEX      224
#define SD_EXTCSD_ERASE_TIMEOUT_MULT_INDEX     223
#define SD_EXTCSD_REL_WR_SEC_C_INDEX           222
#define SD_EXTCSD_HC_WP_GRP_SIZE_INDEX         221
#define SD_EXTCSD_S_C_VCC_INDEX                220
#define SD_EXTCSD_S_C_VCCQ_INDEX               219
#define SD_EXTCSD_S_A_TIMEOUT_INDEX            217
#define SD_EXTCSD_SEC_COUNT_INDEX              212
#define SD_EXTCSD_MIN_PERF_W_8_52_INDEX        210
#define SD_EXTCSD_MIN_PERF_R_8_52_INDEX        209
#define SD_EXTCSD_MIN_PERF_W_8_26_4_52_INDEX   208
#define SD_EXTCSD_MIN_PERF_R_8_26_4_52_INDEX   207
#define SD_EXTCSD_MIN_PERF_W_4_26_INDEX        206
#define SD_EXTCSD_MIN_PERF_R_4_26_INDEX        205
#define SD_EXTCSD_PWR_CL_26_360_INDEX          203
#define SD_EXTCSD_PWR_CL_52_360_INDEX          202
#define SD_EXTCSD_PWR_CL_26_195_INDEX          201
#define SD_EXTCSD_PWR_CL_52_195_INDEX          200
#define SD_EXTCSD_CARD_TYPE_INDEX              196
#define SD_EXTCSD_CSD_STRUCTURE_INDEX          194
#define SD_EXTCSD_EXT_CSD_REV_INDEX            192

#define SD_EXTCSD_CMD_SET_INDEX                191      //Below belongs to Mode Segment
#define SD_EXTCSD_CMD_SET_REV_INDEX            189
#define SD_EXTCSD_POWER_CLASS_INDEX            187
#define SD_EXTCSD_HS_TIMING_INDEX              185
#define SD_EXTCSD_BUS_WIDTH_INDEX              183
#define SD_EXTCSD_ERASED_MEM_CONT_INDEX        181
#define SD_EXTCSD_BOOT_CONFIG_INDEX            179
#define SD_EXTCSD_BOOT_BUS_WIDTH_INDEX         177
#define SD_EXTCSD_ERASE_GROUP_DEF_INDEX        175

// Ext_CSD register access marco
#define MMC_EXTCSD_U8(pSd, bytefield) \
    ( ((unsigned char*)((pSd)->extData))[(bytefield)] )
#define MMC_EXTCSD_U16(pSd, bytefield) \
    ( (((unsigned char*)((pSd)->extData))[(bytefield)    ] << 0) + \
      (((unsigned char*)((pSd)->extData))[(bytefield) + 1] << 8) )
#define MMC_EXTCSD_U32(pSd, bytefield) \
    ( (((unsigned char*)((pSd)->extData))[(bytefield)     ] <<  0) + \
      (((unsigned char*)((pSd)->extData))[(bytefield) +  1] <<  8) + \
      (((unsigned char*)((pSd)->extData))[(bytefield) +  2] << 16) + \
      (((unsigned char*)((pSd)->extData))[(bytefield) + 24] << 24) )
#define MMC_EXTCSD(pSd) ((unsigned char*)((pSd)->extData))
#define SD_EXTCSD_S_CMD_SET(pSd)               (MMC_EXTCSD(pSd)[SD_EXTCSD_S_CMD_SET_INDEX])     // Supported Command Sets
#define SD_EXTCSD_BOOT_INFO(pSd)               (MMC_EXTCSD(pSd)[SD_EXTCSD_BOOT_INFO_INDEX])     // Boot information
#define SD_EXTCSD_BOOT_SIZE_MULTI(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_BOOT_SIZE_MULTI_INDEX])       // Boot partition size
#define SD_EXTCSD_ACC_SIZE(pSd)                (MMC_EXTCSD(pSd)[SD_EXTCSD_ACC_SIZE_INDEX])      // Access size
#define SD_EXTCSD_HC_ERASE_GRP_SIZE(pSd)       (MMC_EXTCSD(pSd)[SD_EXTCSD_HC_ERASE_GRP_SIZE_INDEX])     // High-capacity erase unit size
#define SD_EXTCSD_ERASE_TIMEOUT_MULT(pSd)      (MMC_EXTCSD(pSd)[SD_EXTCSD_ERASE_TIMEOUT_MULT_INDEX])    // High-capacity erase timeout
#define SD_EXTCSD_REL_WR_SEC_C(pSd)            (MMC_EXTCSD(pSd)[SD_EXTCSD_REL_WR_SEC_C_INDEX])  // Reliable write sector count
#define SD_EXTCSD_HC_WP_GRP_SIZE(pSd)          (MMC_EXTCSD(pSd)[SD_EXTCSD_HC_WP_GRP_SIZE_INDEX])        // High-capacity write protect group size
#define SD_EXTCSD_S_C_VCC(pSd)                 (MMC_EXTCSD(pSd)[SD_EXTCSD_S_C_VCC_INDEX])       // Sleep current(VCC)
#define SD_EXTCSD_S_C_VCCQ(pSd)                (MMC_EXTCSD(pSd)[SD_EXTCSD_S_C_VCCQ_INDEX])      // Sleep current(VCCQ)
#define SD_EXTCSD_S_A_TIMEOUT(pSd)             (MMC_EXTCSD(pSd)[SD_EXTCSD_S_A_TIMEOUT_INDEX])   // Sleep/awake timeout
#define SD_EXTCSD_SEC_COUNT(pSd)               ((MMC_EXTCSD(pSd)[SD_EXTCSD_SEC_COUNT_INDEX]) + \
                                                (MMC_EXTCSD(pSd)[SD_EXTCSD_SEC_COUNT_INDEX+1] << 8 ) + \
                                                (MMC_EXTCSD(pSd)[SD_EXTCSD_SEC_COUNT_INDEX+2] << 16 ) + \
                                                (MMC_EXTCSD(pSd)[SD_EXTCSD_SEC_COUNT_INDEX+3] << 24 ))  //Sector Count
#define SD_EXTCSD_MIN_PERF_W_8_52(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_MIN_PERF_W_8_52_INDEX])       // Minimum Write Performance for 8bit at 52MHz
#define SD_EXTCSD_MIN_PERF_R_8_52(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_MIN_PERF_R_8_52_INDEX])       // Minimum Read Performance for 8bit at 52MHz
#define SD_EXTCSD_MIN_PERF_W_8_26_4_52(pSd)    (MMC_EXTCSD(pSd)[SD_EXTCSD_MIN_PERF_W_8_26_4_52_INDEX])  // Minimum Write Performance for 8bit at 26MHz, for 4bit at 52MHz
#define SD_EXTCSD_MIN_PERF_R_8_26_4_52(pSd)    (MMC_EXTCSD(pSd)[SD_EXTCSD_MIN_PERF_R_8_26_4_52_INDEX])  // Minimum Read Performance for 8bit at 26MHz, for 4bit at 52MHz
#define SD_EXTCSD_MIN_PERF_W_4_26(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_MIN_PERF_W_4_26_INDEX])       // Minimum Write Performance for 4bit at 26MHz
#define SD_EXTCSD_MIN_PERF_R_4_26(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_MIN_PERF_R_4_26_INDEX])       // Minimum Read Performance for 4bit at 26MHz
#define SD_EXTCSD_PWR_CL_26_360(pSd)           (MMC_EXTCSD(pSd)[SD_EXTCSD_PWR_CL_26_360_INDEX]) // Power class for 26MHz at 3.6v
#define SD_EXTCSD_PWR_CL_52_360(pSd)           (MMC_EXTCSD(pSd)[SD_EXTCSD_PWR_CL_52_360_INDEX]) // Power class for 52MHz at 3.6v
#define SD_EXTCSD_PWR_CL_26_195(pSd)           (MMC_EXTCSD(pSd)[SD_EXTCSD_PWR_CL_26_195_INDEX]) // Power class for 26MHz at 1.95v
#define SD_EXTCSD_PWR_CL_52_195(pSd)           (MMC_EXTCSD(pSd)[SD_EXTCSD_PWR_CL_52_195_INDEX]) // Power class for 52MHz at 1.95v
#define SD_EXTCSD_CARD_TYPE(pSd)               (MMC_EXTCSD(pSd)[SD_EXTCSD_CARD_TYPE_INDEX])     // Card type
#define SD_EXTCSD_CSD_STRUCTURE(pSd)           (MMC_EXTCSD(pSd)[SD_EXTCSD_CSD_STRUCTURE_INDEX]) // CSD structure version
#define SD_EXTCSD_EXT_CSD_REV(pSd)             (MMC_EXTCSD(pSd)[SD_EXTCSD_EXT_CSD_REV_INDEX])   // Extended CSD structure version
#define SD_EXTCSD_CMD_SET(pSd)                 (MMC_EXTCSD(pSd)[SD_EXTCSD_CMD_SET_INDEX])       // Command set
#define SD_EXTCSD_CMD_SET_REV(pSd)             (MMC_EXTCSD(pSd)[SD_EXTCSD_CMD_SET_REV_INDEX])   // Command set revision
#define SD_EXTCSD_POWER_CLASS(pSd)             (MMC_EXTCSD(pSd)[SD_EXTCSD_POWER_CLASS_INDEX])   // Power class
#define SD_EXTCSD_HS_TIMING(pSd)               (MMC_EXTCSD(pSd)[SD_EXTCSD_HS_TIMING_INDEX])     // High-speed interface timing
#define SD_EXTCSD_BUS_WIDTH(pSd)               (MMC_EXTCSD(pSd)[SD_EXTCSD_BUS_WIDTH_INDEX])     // Bus width mode
#define SD_EXTCSD_ERASED_MEM_CONT(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_ERASED_MEM_CONT_INDEX])       // Erased memory content
#define SD_EXTCSD_BOOT_CONFIG(pSd)             (MMC_EXTCSD(pSd)[SD_EXTCSD_BOOT_CONFIG_INDEX])   // Boot configuration
#define SD_EXTCSD_BOOT_BUS_WIDTH(pSd)          (MMC_EXTCSD(pSd)[SD_EXTCSD_BOOT_BUS_WIDTH_INDEX])        // Boot bus width
#define SD_EXTCSD_ERASE_GROUP_DEF(pSd)         (MMC_EXTCSD(pSd)[SD_EXTCSD_ERASE_GROUP_DEF_INDEX])       // High-density erase group definition

// EXTCSD total size and block number
#define SD_EXTCSD_TOTAL_SIZE(pSd)              (SD_EXTCSD_SEC_COUNT(pSd)*512)
#define SD_EXTCSD_BLOCKNR(pSd)                 (SD_EXTCSD_SEC_COUNT(pSd))

// Bus width Byte
#define SD_EXTCSD_BUS_WIDTH_1BIT               (0x0UL)
#define SD_EXTCSD_BUS_WIDTH_4BIT               (0x1UL)
#define SD_EXTCSD_BUS_WIDTH_8BIT               (0x2UL)

// High speed mode
#define SD_EXTCSD_HS_TIMING_ENABLE             (0x1UL)
#define SD_EXTCSD_HS_TIMING_DISABLE            (0x0UL)

// Boot config
#define SD_EXTCSD_BOOT_PARTITION_ACCESS        (0x7UL)  // boot partition access
#define SD_EXTCSD_BOOT_PART_NO_ACCESS          (0x0UL)
#define SD_EXTCSD_BOOT_PART_RW_PART1           (0x1UL)
#define SD_EXTCSD_BOOT_PART_RW_PART2           (0x2UL)
#define SD_EXTCSD_BOOT_PARTITION_ENABLE        (0x7UL << 3)     // boot partition enable
#define SD_EXTCSD_BOOT_PART_DISABLE            (0x0UL << 3)
#define SD_EXTCSD_BOOT_PART_ENABLE_PART1       (0x1UL << 3)
#define SD_EXTCSD_BOOT_PART_ENABLE_PART2       (0x2UL << 3)
#define SD_EXTCSD_BOOT_PART_ENABLE_USER        (0x7UL << 3)
#define SD_EXTCSD_BOOT_PARTITION_ACK           (0x1UL << 7)     // boot acknowledge
#define SD_EXTCSD_BOOT_PART_NOACK              (0x0UL << 7)
#define SD_EXTCSD_BOOT_PART_ACK                (0x1UL << 7)

// Boot bus width
#define SD_EXTCSD_BOOT_BUS_WIDTH_BIT           (0x3UL)  // boot bus width
#define SD_EXTCSD_BOOT_BUS_1BIT                (0x0UL)
#define SD_EXTCSD_BOOT_BUS_4BIT                (0x1UL)
#define SD_EXTCSD_BOOT_BUS_8BIT                (0x2UL)
#define SD_EXTCSD_RESET_BOOT_BUS_WIDTH_BIT     (0x1UL << 2)     // boot bus width
#define SD_EXTCSD_RESET_BOOT_BUS               (0x0UL << 2)
#define SD_EXTCSD_RETAIN_BOOT_BUS              (0x1UL << 2)

// Mode Switch Arguments for CMD6
#define MMC_CMD6_ARG_ACCESS
#define MMC_CMD6_ARG_INDEX
#define MMC_CMD6_ARG_VALUE
#define MMC_CMD6_ARG_CMDSET

//------------------------------------------------------------------------------
//         Types
//------------------------------------------------------------------------------

typedef MciCallback SdCallback;

typedef MciCmd SdCmd;

typedef Mci SdDriver;

//------------------------------------------------------------------------------
/// Sdcard driver structure. It holds the current command being processed and
/// the SD card address.
//------------------------------------------------------------------------------
typedef struct _SdCard {

    /// Pointer to the underlying MCI driver.
    SdDriver *pSdDriver;
    /// Current MCI command being processed.
    SdCmd command;
    /// Card IDentification (CID register)   
    unsigned int cid[4];
    /// Card-specific data (CSD register)   
    unsigned int csd[4];
    /// Previous access block number.
    unsigned int preBlock;
    /// Card total size
    unsigned int totalSize;
    /// Card block number
    unsigned int blockNr;
    /// SD SCR(64 bit), Status(512 bit) or MMC EXT_CSD(512 bytes) register
    unsigned int extData[512 / 4];
    /// Card option command support list
    unsigned int optCmdBitMap;
    /// Card CSD TRANS_SPEED
    unsigned int transSpeed;
    /// SD card current address.
    unsigned short cardAddress;
    /// Card type
    unsigned char cardType;
    /// Card access mode
    unsigned char mode;
    /// State after sd command complete
    unsigned char state;
} SdCard;

typedef struct _MmcCmd6Arg {

    /// Access
    unsigned char access;
    /// Index
    unsigned char index;
    /// Value
    unsigned char value;
    /// Cmd Set
    unsigned char cmdSet;
} MmcCmd6Arg;

typedef struct _SdCmd6Arg {
    unsigned int accessMode:4,  /// [ 3: 0] function group 1, access mode
     command:4,                 /// [ 7: 4] function group 2, command system
     reserveFG3:4,              /// [11: 8] function group 3, 0xF or 0x0
     reserveFG4:4,              /// [15:12] function group 4, 0xF or 0x0
     reserveFG5:4,              /// [19:16] function group 5, 0xF or 0x0
     reserveFG6:4,              /// [23:20] function group 6, 0xF or 0x0
     reserved:7,                /// [30:24] reserved 0
     mode:1;                    /// [31   ] Mode, 0: Check, 1: Switch
} SdCmd6Arg;

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

extern unsigned char SD_Init(SdCard * pSd, SdDriver * pSdDriver);

extern unsigned char SD_Read(SdCard * pSd,
                             unsigned int address,
                             void *pData,
                             unsigned short length,
                             SdCallback pCallback, void *pArgs);

extern unsigned char SD_Write(SdCard * pSd,
                              unsigned int address,
                              void *pData,
                              unsigned short length,
                              SdCallback pCallback, void *pArgs);

extern unsigned char SD_ReadBlock(SdCard * pSd,
                                  unsigned int address,
                                  unsigned short nbBlocks,
                                  unsigned char *pData);

extern unsigned char SD_WriteBlock(SdCard * pSd,
                                   unsigned int address,
                                   unsigned short nbBlocks,
                                   const unsigned char *pData);

extern unsigned char SD_Stop(SdCard * pSd, SdDriver * pSdDriver);

extern unsigned char SD_HighSpeedMode(SdCard * pSd, unsigned char cardHsMode);

extern unsigned char MMC_SetupBootMode(SdCard * pSd,
                                       unsigned char resetBus,
                                       unsigned char busWidth,
                                       unsigned char bootPart,
                                       unsigned char accPart,
                                       unsigned char bootAck);

extern unsigned char MMC_BootInit(SdCard * pSd);

extern unsigned char MMC_BootRead(SdCard * pSd,
                                  unsigned int nbBlocks, unsigned char *pData);
extern unsigned char MMC_BootStop(SdCard * pSd);

extern unsigned int MMC_GetTotalSizeKB(SdCard * pSd);

extern void SD_DisplayRegisterCID(SdCard * pSd);

extern void SD_DisplayRegisterCSD(SdCard * pSd);

extern void SD_DisplayRegisterECSD(SdCard * pSd);

extern void SD_DisplayRegisterSCR(SdCard * pSd);

extern void SD_DisplaySdStatus(SdCard * pSd);

#endif                          //#ifndef SDCARD_H
