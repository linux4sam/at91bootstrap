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

#if defined(CONFIG_SDCARD)

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "sdmmc_mci.h"

#include "dbgu.h"
#include "debug.h"

#include "pio.h"

#include <string.h>

//------------------------------------------------------------------------------
//         Global variables
//------------------------------------------------------------------------------

#if defined(MCI2_INTERFACE)

unsigned char gSdmmcAutoHsEnable = 1;
#else
unsigned char gSdmmcAutoHsEnable = 0;
#endif

//------------------------------------------------------------------------------
//         Local constants
//------------------------------------------------------------------------------

// Timeout wait loop
#define TO_LOOP             0x10000

// SD card operation states
#define SD_STATE_IDLE        0
#define SD_STATE_INIT        1
#define SD_STATE_READY       2
#define SD_STATE_READ     0x10
#define SD_STATE_RD_RDY   0x11
#define SD_STATE_RD_BSY   0x12
#define SD_STATE_WRITE    0x20
#define SD_STATE_WR_RDY   0x21
#define SD_STATE_WR_BSY   0x22
#define SD_STATE_BOOT     0x30

// Card type
#define UNKNOWN_CARD      0
#define CARD_SD           1
#define CARD_SDHC         2
#define CARD_MMC          3
#define CARD_MMCHD        4     // High density MMC

// Delay between sending MMC commands
#define MMC_DELAY     0x4FF

//#define SD_ADDRESS(pSd, address) \
//    ((((pSd)->cardType == CARD_SDHC) || ((pSd)->cardType == CARD_MMCHD)) ? \
//        (address):((address) << SD_BLOCK_SIZE_BIT))
#define SD_ADDRESS(pSd, address) \
    ( ((pSd)->totalSize == 0xFFFFFFFF) ? \
                            (address):((address) << SD_BLOCK_SIZE_BIT) )

//-----------------------------------------------------------------------------
/// MMC/SD in SPI mode reports R1 status always, and R2 for SEND_STATUS
/// R1 is the low order byte; R2 is the next highest byte, when present.
//-----------------------------------------------------------------------------
#define R1_SPI_IDLE             (1 << 0)
#define R1_SPI_ERASE_RESET      (1 << 1)
#define R1_SPI_ILLEGAL_COMMAND  (1 << 2)
#define R1_SPI_COM_CRC          (1 << 3)
#define R1_SPI_ERASE_SEQ        (1 << 4)
#define R1_SPI_ADDRESS          (1 << 5)
#define R1_SPI_PARAMETER        (1 << 6)
// R1 bit 7 is always zero
#define R2_SPI_CARD_LOCKED      (1 << 0)
#define R2_SPI_WP_ERASE_SKIP    (1 << 1)
#define R2_SPI_LOCK_UNLOCK_FAIL R2_SPI_WP_ERASE_SKIP
#define R2_SPI_ERROR            (1 << 2)
#define R2_SPI_CC_ERROR         (1 << 3)
#define R2_SPI_CARD_ECC_ERROR   (1 << 4)
#define R2_SPI_WP_VIOLATION     (1 << 5)
#define R2_SPI_ERASE_PARAM      (1 << 6)
#define R2_SPI_OUT_OF_RANGE     (1 << 7)
#define R2_SPI_CSD_OVERWRITE    R2_SPI_OUT_OF_RANGE

// Status register constants
#define STATUS_APP_CMD          (1 << 5)
#define STATUS_SWITCH_ERROR     (1 << 7)
#define STATUS_READY_FOR_DATA   (1 << 8)
#define STATUS_IDLE             (0 << 9)
#define STATUS_READY            (1 << 9)
#define STATUS_IDENT            (2 << 9)
#define STATUS_STBY             (3 << 9)
#define STATUS_TRAN             (4 << 9)
#define STATUS_DATA             (5 << 9)
#define STATUS_RCV              (6 << 9)
#define STATUS_PRG              (7 << 9)
#define STATUS_DIS              (8 << 9)
#define STATUS_STATE          (0xF << 9)
#define STATUS_ERASE_RESET       (1 << 13)
#define STATUS_WP_ERASE_SKIP     (1 << 15)
#define STATUS_CIDCSD_OVERWRITE  (1 << 16)
#define STATUS_OVERRUN           (1 << 17)
#define STATUS_UNERRUN           (1 << 18)
#define STATUS_ERROR             (1 << 19)
#define STATUS_CC_ERROR          (1 << 20)
#define STATUS_CARD_ECC_FAILED   (1 << 21)
#define STATUS_ILLEGAL_COMMAND   (1 << 22)
#define STATUS_COM_CRC_ERROR     (1 << 23)
#define STATUS_UN_LOCK_FAILED    (1 << 24)
#define STATUS_CARD_IS_LOCKED    (1 << 25)
#define STATUS_WP_VIOLATION      (1 << 26)
#define STATUS_ERASE_PARAM       (1 << 27)
#define STATUS_ERASE_SEQ_ERROR   (1 << 28)
#define STATUS_BLOCK_LEN_ERROR   (1 << 29)
#define STATUS_ADDRESS_MISALIGN  (1 << 30)
#define STATUS_ADDR_OUT_OR_RANGE (1 << 31)

#define STATUS_STOP ( STATUS_CARD_IS_LOCKED \
                        | STATUS_COM_CRC_ERROR \
                        | STATUS_ILLEGAL_COMMAND \
                        | STATUS_CC_ERROR \
                        | STATUS_ERROR \
                        | STATUS_STATE \
                        | STATUS_READY_FOR_DATA )

#define STATUS_WRITE ( STATUS_ADDR_OUT_OR_RANGE \
                        | STATUS_ADDRESS_MISALIGN \
                        | STATUS_BLOCK_LEN_ERROR \
                        | STATUS_WP_VIOLATION \
                        | STATUS_CARD_IS_LOCKED \
                        | STATUS_COM_CRC_ERROR \
                        | STATUS_ILLEGAL_COMMAND \
                        | STATUS_CC_ERROR \
                        | STATUS_ERROR \
                        | STATUS_ERASE_RESET \
                        | STATUS_STATE \
                        | STATUS_READY_FOR_DATA )

#define STATUS_READ  ( STATUS_ADDR_OUT_OR_RANGE \
                        | STATUS_ADDRESS_MISALIGN \
                        | STATUS_BLOCK_LEN_ERROR \
                        | STATUS_CARD_IS_LOCKED \
                        | STATUS_COM_CRC_ERROR \
                        | STATUS_ILLEGAL_COMMAND \
                        | STATUS_CARD_ECC_FAILED \
                        | STATUS_CC_ERROR \
                        | STATUS_ERROR \
                        | STATUS_ERASE_RESET \
                        | STATUS_STATE \
                        | STATUS_READY_FOR_DATA )

#define STATUS_SD_SWITCH ( STATUS_ADDR_OUT_OR_RANGE \
                            | STATUS_CARD_IS_LOCKED \
                            | STATUS_COM_CRC_ERROR \
                            | STATUS_ILLEGAL_COMMAND \
                            | STATUS_CARD_ECC_FAILED \
                            | STATUS_CC_ERROR \
                            | STATUS_ERROR \
                            | STATUS_UNERRUN \
                            | STATUS_OVERRUN \
                            | STATUS_STATE)

#define STATUS_MMC_SWITCH ( STATUS_CARD_IS_LOCKED \
                            | STATUS_COM_CRC_ERROR \
                            | STATUS_ILLEGAL_COMMAND \
                            | STATUS_CC_ERROR \
                            | STATUS_ERROR \
                            | STATUS_ERASE_RESET \
                            | STATUS_STATE \
                            | STATUS_READY_FOR_DATA \
                            | STATUS_SWITCH_ERROR )

//-----------------------------------------------------------------------------
/// OCR Register
//-----------------------------------------------------------------------------
#define AT91C_VDD_16_17          (1 << 4)
#define AT91C_VDD_17_18          (1 << 5)
#define AT91C_VDD_18_19          (1 << 6)
#define AT91C_VDD_19_20          (1 << 7)
#define AT91C_VDD_20_21          (1 << 8)
#define AT91C_VDD_21_22          (1 << 9)
#define AT91C_VDD_22_23          (1 << 10)
#define AT91C_VDD_23_24          (1 << 11)
#define AT91C_VDD_24_25          (1 << 12)
#define AT91C_VDD_25_26          (1 << 13)
#define AT91C_VDD_26_27          (1 << 14)
#define AT91C_VDD_27_28          (1 << 15)
#define AT91C_VDD_28_29          (1 << 16)
#define AT91C_VDD_29_30          (1 << 17)
#define AT91C_VDD_30_31          (1 << 18)
#define AT91C_VDD_31_32          (1 << 19)
#define AT91C_VDD_32_33          (1 << 20)
#define AT91C_VDD_33_34          (1 << 21)
#define AT91C_VDD_34_35          (1 << 22)
#define AT91C_VDD_35_36          (1 << 23)
#define AT91C_CARD_POWER_UP_BUSY (1 << 31)
#define AT91C_MMC_OCR_BIT2930    (3 << 29)

#define AT91C_MMC_HOST_VOLTAGE_RANGE     (AT91C_VDD_27_28 +\
                                          AT91C_VDD_28_29 +\
                                          AT91C_VDD_29_30 +\
                                          AT91C_VDD_30_31 +\
                                          AT91C_VDD_31_32 +\
                                          AT91C_VDD_32_33)

// MMC OCR response for Bit 29, 30
#define AT91C_MMC_NORM_DENSITY   (0x0UL << 29)
#define AT91C_MMC_HIGH_DENSITY   (0x2UL << 29)

#define AT91C_CCS    (1 << 30)

// MCI_CMD Register Value
#define AT91C_POWER_ON_INIT      (0 | AT91C_MCI_TRCMD_NO    \
                                    | AT91C_MCI_SPCMD_INIT  \
                                    | AT91C_MCI_OPDCMD)

//-----------------------------------------------------------------------------
/// eMMC CMD6
//-----------------------------------------------------------------------------
#define AT91C_EMMC_CMD6ARG_ACCESS_BITS        (0x3UL << 24)
#define AT91C_EMMC_CMD6ARG_ACCESS_SHIFT       (24)
// change command sets
#define AT91C_EMMC_CMD6ARG_ACCESS_CMDSETS     (0x0UL << 24)
// set bits in the value field
#define AT91C_EMMC_CMD6ARG_ACCESS_SETBITS     (0x1UL << 24)
// clear bits in the value field
#define AT91C_EMMC_CMD6ARG_ACCESS_CLRBITS     (0x2UL << 24)
// the value field is written into the pointed byte
#define AT91C_EMMC_CMD6ARG_ACCESS_WRBYTES     (0x3UL << 24)
#define AT91C_EMMC_CMD6ARG_INDEX_BITS         (0xffUL << 16)
#define AT91C_EMMC_CMD6ARG_INDEX_SHIFT        (16)
#define AT91C_EMMC_CMD6ARG_VALUE_BITS         (0xffUL << 8)
#define AT91C_EMMC_CMD6ARG_VALUE_SHIFT        (8)
#define AT91C_EMMC_CMD6ARG_CMDSET_BITS        (0x7UL << 0)
#define AT91C_EMMC_CMD6ARG_CMDSET_SHIFT       (0)

//-----------------------------------------------------------------------------
// Command Classes
//-----------------------------------------------------------------------------
//
// Class 0, 2, 4, 5, 7 and 8 are mandatory and shall be supported by
// all SD Memory Cards.
//
// Basic Commands (class 0)
//
// Cmd0 MCI + SPI
#define   AT91C_GO_IDLE_STATE_CMD     (0 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE )
// Cmd1 SPI
#define   AT91C_MMC_SEND_OP_COND_CMD  (1 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_48 \
                                         | AT91C_MCI_OPDCMD)
// Cmd2 MCI
#define   AT91C_ALL_SEND_CID_CMD      (2 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_136 )
// Cmd3 MCI
#define   AT91C_SET_RELATIVE_ADDR_CMD (3 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_48 \
                                         | AT91C_MCI_MAXLAT )
// Cmd4 MCI
#define AT91C_SET_DSR_CMD             (4 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_NO \
                                         | AT91C_MCI_MAXLAT )
// Cmd6 SD/MMC
#if defined(MCI2_INTERFACE)
#define AT91C_MMC_SWITCH_CMD          (6 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_R1B \
                                         | AT91C_MCI_MAXLAT )
#else
#define AT91C_MMC_SWITCH_CMD          (6 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_48 \
                                         | AT91C_MCI_MAXLAT )
#endif
#define AT91C_SD_SWITCH_CMD           (6 | AT91C_MCI_TRCMD_START \
                                         | AT91C_MCI_TRTYP_BLOCK \
                                         | AT91C_MCI_TRDIR_READ \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_48 \
                                         | AT91C_MCI_MAXLAT )
// cmd7 MCI
#define   AT91C_SEL_DESEL_CARD_CMD    (7 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_48 \
                                         | AT91C_MCI_MAXLAT )
#define   AT91C_SEL_CARD_CMD          (7 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_48 \
                                         | AT91C_MCI_MAXLAT )
#define   AT91C_DESEL_CARD_CMD        (7 | AT91C_MCI_TRCMD_NO \
                                         | AT91C_MCI_SPCMD_NONE \
                                         | AT91C_MCI_RSPTYP_NO \
                                         | AT91C_MCI_MAXLAT )
// Cmd8 MCI + SPI
#define   AT91C_SEND_IF_COND          (8  | AT91C_MCI_TRCMD_NO \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_RSPTYP_48 \
                                          | AT91C_MCI_MAXLAT )
// Cmd9 MCI + SPI
#define   AT91C_SEND_CSD_CMD          (9  | AT91C_MCI_TRCMD_NO \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_RSPTYP_136 \
                                          | AT91C_MCI_MAXLAT )
// Cmd10 MCI + SPI
#define   AT91C_SEND_CID_CMD          (10 | AT91C_MCI_TRCMD_NO \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_RSPTYP_136 \
                                          | AT91C_MCI_MAXLAT )
// Cmd12 MCI + SPI
#if defined(MCI2_INTERFACE)
#define   AT91C_STOP_TRANSMISSION_CMD (12 | AT91C_MCI_TRCMD_STOP \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_RSPTYP_R1B \
                                          | AT91C_MCI_MAXLAT )
#else
#define   AT91C_STOP_TRANSMISSION_CMD (12 | AT91C_MCI_TRCMD_STOP \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_RSPTYP_48 \
                                          | AT91C_MCI_MAXLAT )
#endif
// Cmd13 MCI + SPI
#define   AT91C_SEND_STATUS_CMD       (13 | AT91C_MCI_TRCMD_NO \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_RSPTYP_48 \
                                          | AT91C_MCI_MAXLAT )
// Cmd15 MCI
#define AT91C_GO_INACTIVE_STATE_CMD   (15 | AT91C_MCI_RSPTYP_NO )

// Cmd58 SPI
#define   AT91C_READ_OCR_CMD          (58 | AT91C_MCI_RSPTYP_48 \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_MAXLAT )
// Cmd59 SPI
#define   AT91C_CRC_ON_OFF_CMD        (59 | AT91C_MCI_RSPTYP_48 \
                                          | AT91C_MCI_SPCMD_NONE \
                                          | AT91C_MCI_MAXLAT )

//*------------------------------------------------
//* Class 2 commands: Block oriented Read commands
//*------------------------------------------------

// Cmd8 for MMC
#define AT91C_SEND_EXT_CSD_CMD          (8 | AT91C_MCI_SPCMD_NONE \
                                           | AT91C_MCI_OPDCMD_PUSHPULL \
                                           | AT91C_MCI_RSPTYP_48 \
                                           | AT91C_MCI_TRCMD_START \
                                           | AT91C_MCI_TRTYP_BLOCK \
                                           | AT91C_MCI_TRDIR \
                                           | AT91C_MCI_MAXLAT)

// Cmd16
#define AT91C_SET_BLOCKLEN_CMD          (16 | AT91C_MCI_TRCMD_NO \
                                            | AT91C_MCI_SPCMD_NONE \
                                            | AT91C_MCI_RSPTYP_48 \
                                            | AT91C_MCI_MAXLAT )
// Cmd17
#define AT91C_READ_SINGLE_BLOCK_CMD     (17 | AT91C_MCI_SPCMD_NONE \
                                            | AT91C_MCI_RSPTYP_48 \
                                            | AT91C_MCI_TRCMD_START \
                                            | AT91C_MCI_TRTYP_BLOCK \
                                            | AT91C_MCI_TRDIR \
                                            | AT91C_MCI_MAXLAT)
// Cmd18
#define AT91C_READ_MULTIPLE_BLOCK_CMD   (18 | AT91C_MCI_SPCMD_NONE \
                                            | AT91C_MCI_RSPTYP_48 \
                                            | AT91C_MCI_TRCMD_START \
                                            | AT91C_MCI_TRTYP_MULTIPLE \
                                            | AT91C_MCI_TRDIR \
                                            | AT91C_MCI_MAXLAT)

//*------------------------------------------------
//* Class 4 commands: Block oriented write commands
//*------------------------------------------------
// Cmd24
#define AT91C_WRITE_BLOCK_CMD           (24 | AT91C_MCI_SPCMD_NONE \
                                            | AT91C_MCI_RSPTYP_48 \
                                            | AT91C_MCI_TRCMD_START \
                                            | (AT91C_MCI_TRTYP_BLOCK \
                                                & ~(AT91C_MCI_TRDIR)) \
                                            | AT91C_MCI_MAXLAT)
// Cmd25
#define AT91C_WRITE_MULTIPLE_BLOCK_CMD  (25 | AT91C_MCI_SPCMD_NONE \
                                            | AT91C_MCI_RSPTYP_48 \
                                            | AT91C_MCI_TRCMD_START \
                                            | (AT91C_MCI_TRTYP_MULTIPLE \
                                                & ~(AT91C_MCI_TRDIR)) \
                                            | AT91C_MCI_MAXLAT)
// Cmd27
#define AT91C_PROGRAM_CSD_CMD           (27 | AT91C_MCI_RSPTYP_48 )

//*----------------------------------------
//* Class 5 commands: Erase commands
//*----------------------------------------
// Cmd32
//#define AT91C_TAG_SECTOR_START_CMD          (32 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT)
// Cmd33
//#define AT91C_TAG_SECTOR_END_CMD            (33 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT)
// Cmd38
//#define AT91C_ERASE_CMD                     (38 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT )

//*----------------------------------------
//* Class 7 commands: Lock commands
//*----------------------------------------
// Cmd42
//#define AT91C_LOCK_UNLOCK           (42 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT) // not tested

//*-----------------------------------------------
// Class 8 commands: Application specific commands
//*-----------------------------------------------
// Cmd55
#define AT91C_APP_CMD               (55 | AT91C_MCI_SPCMD_NONE \
                                        | AT91C_MCI_RSPTYP_48 \
                                        | AT91C_MCI_TRCMD_NO \
                                        | AT91C_MCI_MAXLAT)
// cmd 56
//#define AT91C_GEN_CMD               (56 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO | AT91C_MCI_MAXLAT)    // not tested
// ACMD6
#define AT91C_SD_SET_BUS_WIDTH_CMD          (6  | AT91C_MCI_SPCMD_NONE \
                                                | AT91C_MCI_RSPTYP_48 \
                                                | AT91C_MCI_TRCMD_NO \
                                                | AT91C_MCI_MAXLAT)
// ACMD13
#define AT91C_SD_STATUS_CMD                 (13 | AT91C_MCI_SPCMD_NONE \
                                                | AT91C_MCI_RSPTYP_48 \
                                                | AT91C_MCI_TRCMD_START \
                                                | AT91C_MCI_TRTYP_BLOCK \
                                                | AT91C_MCI_TRDIR_READ \
                                                | AT91C_MCI_MAXLAT)
// ACMD22
//#define AT91C_SD_SEND_NUM_WR_BLOCKS_CMD     (22 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT)
// ACMD23
//#define AT91C_SD_SET_WR_BLK_ERASE_COUNT_CMD (23 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT)
// ACMD41
#define AT91C_SD_APP_OP_COND_CMD            (41 | AT91C_MCI_SPCMD_NONE \
                                                | AT91C_MCI_RSPTYP_48 \
                                                | AT91C_MCI_TRCMD_NO )
// ACMD42
//#define AT91C_SD_SET_CLR_CARD_DETECT_CMD    (42 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO    | AT91C_MCI_MAXLAT)
// ACMD51
#define AT91C_SD_SEND_SCR_CMD               (51 | AT91C_MCI_SPCMD_NONE \
                                                | AT91C_MCI_RSPTYP_48 \
                                                | AT91C_MCI_TRCMD_START \
                                                | AT91C_MCI_TRDIR_READ \
                                                | AT91C_MCI_TRTYP_BLOCK \
                                                | AT91C_MCI_MAXLAT)

#ifdef AT91C_MCI_SPCMD_BOOTREQ
// BOOTREQ
#define AT91C_BOOTREQ           (AT91C_MCI_SPCMD_BOOTREQ \
                                    | AT91C_MCI_TRDIR_READ \
                                    | AT91C_MCI_TRCMD_START \
                                    | AT91C_MCI_MAXLAT)
// BOOTEND
#define AT91C_BOOTEND           (AT91C_MCI_SPCMD_BOOTEND \
                                    | AT91C_MCI_OPDCMD_PUSHPULL)
#endif
// Optional commands
#define SD_ACMD6_SUPPORT        (1 << 0)
#define SD_ACMD13_SUPPORT       (1 << 1)
#define SD_ACMD41_SUPPORT       (1 << 2)
#define SD_ACMD51_SUPPORT       (1 << 3)

#define SD_CMD16_SUPPORT        (1 << 8)

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// DecodeR1
/// \param R1  
//------------------------------------------------------------------------------
void DecodeR1(unsigned char R1)
{
#if 0
    if ((R1 & R1_SPI_IDLE) == R1_SPI_IDLE) {
        TRACE_DEBUG("R1_SPI_IDLE\n\r");
    }
    if ((R1 & R1_SPI_ERASE_RESET) == R1_SPI_ERASE_RESET) {
        TRACE_DEBUG("R1_SPI_ERASE_RESET\n\r");
    }
    if ((R1 & R1_SPI_ILLEGAL_COMMAND) == R1_SPI_ILLEGAL_COMMAND) {
        TRACE_DEBUG("R1_SPI_ILLEGAL_COMMAND\n\r");
    }
    if ((R1 & R1_SPI_COM_CRC) == R1_SPI_COM_CRC) {
        TRACE_DEBUG("R1_SPI_COM_CRC\n\r");
    }
    if ((R1 & R1_SPI_ERASE_SEQ) == R1_SPI_ERASE_SEQ) {
        TRACE_DEBUG("R1_SPI_ERASE_SEQ\n\r");
    }
    if ((R1 & R1_SPI_ADDRESS) == R1_SPI_ADDRESS) {
        TRACE_DEBUG("R1_SPI_ADDRESS\n\r");
    }
    if ((R1 & R1_SPI_PARAMETER) == R1_SPI_PARAMETER) {
        TRACE_DEBUG("R1_SPI_PARAMETER\n\r");
    }
#endif
}

//------------------------------------------------------------------------------
/// DecodeR2
/// \param R2  
//------------------------------------------------------------------------------
void DecodeR2(unsigned char R2)
{
#if 0
    if ((R2 & R2_SPI_CARD_LOCKED) == R2_SPI_CARD_LOCKED) {
        TRACE_DEBUG("R2_SPI_CARD_LOCKED\n\r");
    }
    if ((R2 & R2_SPI_WP_ERASE_SKIP) == R2_SPI_WP_ERASE_SKIP) {
        TRACE_DEBUG("R2_SPI_WP_ERASE_SKIP/R2_SPI_LOCK_UNLOCK_FAIL\n\r");
    }
    if ((R2 & R2_SPI_ERROR) == R2_SPI_ERROR) {
        TRACE_DEBUG("R2_SPI_ERROR\n\r");
    }
    if ((R2 & R2_SPI_CC_ERROR) == R2_SPI_CC_ERROR) {
        TRACE_DEBUG("R2_SPI_CC_ERROR\n\r");
    }
    if ((R2 & R2_SPI_CARD_ECC_ERROR) == R2_SPI_CARD_ECC_ERROR) {
        TRACE_DEBUG("R2_SPI_CARD_ECC_ERROR\n\r");
    }
    if ((R2 & R2_SPI_WP_VIOLATION) == R2_SPI_WP_VIOLATION) {
        TRACE_DEBUG("R2_SPI_WP_VIOLATION\n\r");
    }
    if ((R2 & R2_SPI_ERASE_PARAM) == R2_SPI_ERASE_PARAM) {
        TRACE_DEBUG("R2_SPI_ERASE_PARAM\n\r");
    }
    if ((R2 & R2_SPI_OUT_OF_RANGE) == R2_SPI_OUT_OF_RANGE) {
        TRACE_DEBUG("R2_SPI_OUT_OF_RANGE/R2_SPI_CSD_OVERWRITE\n\r");
    }
#endif
}

//------------------------------------------------------------------------------
/// Get Trans Speed Value
/// \param pSd    
//------------------------------------------------------------------------------
void GetTransSpeedValue(SdCard * pSd)
{
    unsigned int unit, value;

    // CSD register, TRANS_SPEED bit
    const unsigned int units[4] = { 10, 100, 1000, 10000 };     // *Kbit/s 
    const unsigned int values_emmc[16] = { 0, 10, 12, 13, 15, 20,
        26, 30, 35, 40, 45, 52,
        55, 60, 70, 80
    };
    const unsigned int values_sdmmc[16] = { 0, 10, 12, 13, 15, 20,
        25, 30, 35, 40, 45, 50,
        55, 60, 70, 80
    };

    unit = (SD_CSD_TRAN_SPEED(pSd) & 0x7);
    if (unit < 4)
        unit = units[unit];
    else
        return;
    value = (SD_CSD_TRAN_SPEED(pSd) >> 3) & 0xF;
    if (value < 16) {
        if (pSd->cardType >= CARD_MMC && SD_CID_BGA(pSd) == 1) {
            value = values_emmc[value];
        } else
            value = values_sdmmc[value];
    } else
        return;

    pSd->transSpeed = (unit * value) * 1000;
}

#if 1
//------------------------------------------------------------------------------
/// Reset the SdCmd
//------------------------------------------------------------------------------
static void ResetCommand(SdCmd * pCommand)
{
#if 0
    unsigned char *p = (unsigned char *)pCommand;

    unsigned int l = sizeof (SdCmd);

    while (l--)
        *p++ = 0;
#else
    pCommand->cmd = 0;
    pCommand->arg = 0;
    pCommand->pData = 0;
    pCommand->blockSize = 0;
    pCommand->nbBlock = 0;
    pCommand->pResp = 0;
    pCommand->callback = 0;
    pCommand->pArg = 0;
    pCommand->resType = 0;
    pCommand->dataTran = 0;
    pCommand->tranType = 0;
    pCommand->isRead = 0;
    pCommand->status = 0;
#endif
}
#else
// GNU halt on memset now
# define ResetCommand(pCommand) memset(pCommand, 0, sizeof(SdCmd))
#endif

//------------------------------------------------------------------------------
/// Delay some loop
//------------------------------------------------------------------------------
void Delay(volatile unsigned int loop)
{
    for (; loop > 0; loop--) ;
}

//------------------------------------------------------------------------------
/// Sends the current SD card driver command to the card.
/// Returns 0 if successful; Otherwise, returns the transfer status code or
/// SD_ERROR_DRIVER if there was a problem with the SD transfer.
/// \param pSd  Pointer to a SdCard driver instance.
//------------------------------------------------------------------------------
static unsigned char SendCommand(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    SdDriver *pSdDriver = pSd->pSdDriver;

    unsigned char error;

    // Send command
    error = MCI_SendCommand((Mci *) pSdDriver, (MciCmd *) pCommand);
    if (error) {

        return SD_ERROR_DRIVER;
    }
    // Wait for command to complete (if no callback defined)
    if (pCommand->callback == 0) {
        while (!MCI_IsTxComplete((Mci *) pSdDriver)) ;
    }
    // Check for using fifo to transfer data
#if !defined(MCI_DMA_ENABLE) && defined(MCI2_INTERFACE)
    if (pCommand->dataTran && pCommand->nbBlock) {
        MCI_FifoTransfer((Mci *) pSdDriver, (MciCmd *) pCommand);
    }
#endif

    return pCommand->status;
}

//------------------------------------------------------------------------------
/// Initialization delay: The maximum of 1 msec, 74 clock cycles and supply ramp
/// up time.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SdCard driver instance.
//------------------------------------------------------------------------------
static unsigned char Pon(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned int response;

    unsigned char error;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_POWER_ON_INIT;
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);
    return error;
}

#if defined(MCI2_INTERFACE)
//------------------------------------------------------------------------------
/// Initialization delay: The maximum of 1 msec, 74 clock cycles and supply ramp
/// up time, CMD keeps low so that the device run in boot mode.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SdCard driver instance.
//------------------------------------------------------------------------------
static unsigned char PonBoot(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned int response;

    unsigned char error;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_POWER_ON_INIT;
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);
    return error;
}
#endif

//------------------------------------------------------------------------------
/// Resets all cards to idle state
/// \param pSd  Pointer to a SdCard driver instance.
/// \param arg  Argument used.
/// \return the command transfer result (see SendCommand).
//------------------------------------------------------------------------------
static unsigned char Cmd0(SdCard * pSd, unsigned int arg)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned int response;

    unsigned char error;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_GO_IDLE_STATE_CMD;
    pCommand->arg = arg;
    pCommand->pResp = &response;

    // send command
    error = SendCommand(pSd);
    return error;
}

//------------------------------------------------------------------------------
/// MMC send operation condition command.
/// Sends host capacity support information and activates the card's
/// initialization process.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SdCard driver instance.
/// \param hdSupport  Indicate whether the host support high density MMC.
/// \param pHdSupport  Indicate whether the card is a high density MMC.
//------------------------------------------------------------------------------
static unsigned char Cmd1(SdCard * pSd,
                          unsigned char hdSupport, unsigned char *pHdSupport)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_MMC_SEND_OP_COND_CMD;
    pCommand->arg = AT91C_MMC_HOST_VOLTAGE_RANGE;
    if (hdSupport) {
        pCommand->arg |= AT91C_MMC_HIGH_DENSITY;
    } else {
        pCommand->arg |= AT91C_MMC_NORM_DENSITY;
    }
    pCommand->resType = 3;
    pCommand->pResp = &response;

    // send command
    *pHdSupport = 0;
    error = SendCommand(pSd);
    if (error) {
        return error;
    }
    if ((response & AT91C_CARD_POWER_UP_BUSY) == AT91C_CARD_POWER_UP_BUSY) {
        if ((response & AT91C_MMC_OCR_BIT2930) == AT91C_MMC_HIGH_DENSITY) {
            *pHdSupport = 1;
        }
        return 0;
    } else {
        return SD_ERROR_DRIVER;
    }
}

//------------------------------------------------------------------------------
/// Asks any card to send the CID numbers
/// on the CMD line (any card that is
/// connected to the host will respond)
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
/// \param pCid  Buffer for storing the CID numbers.
//------------------------------------------------------------------------------
static unsigned char Cmd2(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    ResetCommand(pCommand);
    // Fill the command information
    pCommand->cmd = AT91C_ALL_SEND_CID_CMD;
    pCommand->resType = 2;
    pCommand->pResp = pSd->cid;

    // Send the command
    return SendCommand(pSd);
}

//------------------------------------------------------------------------------
/// Ask the card to publish a new relative address (RCA)
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
static unsigned char Cmd3(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned int cardAddress;

    unsigned char error;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SET_RELATIVE_ADDR_CMD;

    // Assign relative address to MMC card
    if ((pSd->cardType == CARD_MMC) || (pSd->cardType == CARD_MMCHD)) {
        pCommand->arg = (0x1 << 16);
    }
    pCommand->resType = 1;
    pCommand->pResp = &cardAddress;

    // Send command
    error = SendCommand(pSd);
    if (error) {
        return error;
    }
    // Save card address in driver
    if ((pSd->cardType == CARD_SD) || (pSd->cardType == CARD_SDHC)) {
        pSd->cardAddress = (cardAddress >> 16) & 0xFFFF;
    } else {
        // Default MMC RCA is 0x0001
        pSd->cardAddress = 1;
    }

    return 0;
}

//------------------------------------------------------------------------------
/// Command toggles a card between the
/// stand-by and transfer states or between
/// the programming and disconnect states.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
/// \param address  Relative Card Address (0 deselects all).
//------------------------------------------------------------------------------
static unsigned char Cmd7(SdCard * pSd, unsigned int address)
{
    SdCmd *pCommand = &(pSd->command);

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SEL_DESEL_CARD_CMD;
    pCommand->arg = address << 16;
    pCommand->resType = 1;

    // Send command
    return SendCommand(pSd);
}

//------------------------------------------------------------------------------
/// Switches the mode of operation of the selected card (SD/MMC) or
/// modifies the EXT_CSD registers (for MMC only).
/// CMD6 is valid under the "trans" state.
/// \return The command transfer result (see SendCommand).
/// \param  pSd         Pointer to a SD/MMC card driver instance.
/// \param  pSwitchArg  Pointer to a MmcCmd6Arg instance.
/// \param  pStatus     Pointer to where the 512bit status is returned.
/// \param  pResp       Pointer to where the response is returned.
//------------------------------------------------------------------------------
static unsigned char Cmd6(SdCard * pSd,
                          const void *pSwitchArg,
                          unsigned int *pStatus, unsigned int *pResp)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned int response;

    unsigned char error;

    SdCmd6Arg *pSdSwitch;

    MmcCmd6Arg *pMmcSwitch;

    ResetCommand(pCommand);

    if (pSd->cardType >= CARD_MMC) {
        pMmcSwitch = (MmcCmd6Arg *) pSwitchArg;
        // R1b response
        pCommand->cmd = AT91C_MMC_SWITCH_CMD;
        pCommand->resType = 1;
        pCommand->arg = (pMmcSwitch->access << 24)
            | (pMmcSwitch->index << 16)
            | (pMmcSwitch->value << 8)
            | (pMmcSwitch->cmdSet << 0);
    } else if (pSd->cardType >= CARD_SD) {

        pSdSwitch = (SdCmd6Arg *) pSwitchArg;
        // R1 response & 512 bits of status on DAT
        pCommand->cmd = AT91C_SD_SWITCH_CMD;
        pCommand->resType = 1;
        pCommand->arg = (pSdSwitch->mode << 31)
            | (pSdSwitch->reserved << 30)
            | (pSdSwitch->reserveFG6 << 20)
            | (pSdSwitch->reserveFG5 << 16)
            | (pSdSwitch->reserveFG4 << 12)
            | (pSdSwitch->reserveFG3 << 8)
            | (pSdSwitch->command << 4)
            | (pSdSwitch->accessMode << 0);
        if (pStatus) {
            pCommand->blockSize = 512 / 8;
            pCommand->nbBlock = 1;
            pCommand->pData = (unsigned char *)pStatus;

            pCommand->dataTran = 1;
            pCommand->isRead = 1;
            pCommand->tranType = MCI_NEW_TRANSFER;
        }
    }
    pCommand->pResp = &response;

    error = SendCommand(pSd);

    if (error)
        return error;
    else if (pResp)
        *pResp = response;

    return 0;
}

//------------------------------------------------------------------------------
/// SD:  Sends SD Memory Card interface condition, which includes host supply
///      voltage information and asks the card whether card supports voltage.
///      Should be performed at initialization time to detect the card type.
/// MMC: SEND_EXT_CSD, to get EXT_CSD register as a block of data.
///      Valid under "trans" state.
/// \param pSd   Pointer to a SD card driver instance.
/// \param sdCmd For SD Memory Card interface condition 
/// \param arg   Expected supply voltage(SD) or 512 byte buffer pointer (MMC).
/// \return 0 if successful;
///         otherwise returns SD_ERROR_NORESPONSE if the card did not answer
///         the command, or SD_ERROR_DRIVER.
//------------------------------------------------------------------------------
static unsigned char Cmd8(SdCard * pSd, unsigned char sdCmd, void *arg)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned int response;

    unsigned char error;

    unsigned char supplyVoltage = (unsigned char)((unsigned int)arg);

    ResetCommand(pCommand);

    if (sdCmd) {

        // Fill command information
        pCommand->cmd = AT91C_SEND_IF_COND;
        pCommand->arg = (supplyVoltage << 8) | (0xAA);
        pCommand->resType = 7;

    } else {

        pCommand->cmd = AT91C_SEND_EXT_CSD_CMD;
        pCommand->resType = 1;

        pCommand->blockSize = SD_BLOCK_SIZE;
        pCommand->nbBlock = 512 / SD_BLOCK_SIZE;
        pCommand->pData = arg;

        pCommand->dataTran = 1;
        pCommand->isRead = 1;
        pCommand->tranType = MCI_NEW_TRANSFER;
    }
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);

    if (sdCmd) {

        // Check result
        if (error == MCI_STATUS_NORESPONSE) {

            return SD_ERROR_NORESPONSE;
        }
        // SD_R7
        // Bit 0 - 7: check pattern (echo-back)
        // Bit 8 -11: voltage accepted
        else if (!error &&
                 ((response & 0x00000FFF) == ((supplyVoltage << 8) | 0xAA))) {
            return 0;
        } else {
            return SD_ERROR_DRIVER;
        }
    }

    return error;
}

//------------------------------------------------------------------------------
/// Addressed card sends its card-specific
/// data (CSD) on the CMD line.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
static unsigned char Cmd9(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SEND_CSD_CMD;
    pCommand->arg = pSd->cardAddress << 16;
    pCommand->resType = 2;
    pCommand->pResp = pSd->csd;

    // Send command
    error = SendCommand(pSd);
    return error;
}

//------------------------------------------------------------------------------
/// Forces the card to stop transmission
/// \param pSd      Pointer to a SD card driver instance.
/// \param stopRead Stop reading stream/writing stream.
/// \param pStatus  Pointer to a status variable.
//------------------------------------------------------------------------------
static unsigned char Cmd12(SdCard * pSd,
                           unsigned char stopRead, unsigned int *pStatus)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_STOP_TRANSMISSION_CMD;
    pCommand->isRead = stopRead;
    pCommand->tranType = MCI_STOP_TRANSFER;
    pCommand->resType = 1;
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);
    if (pStatus)
        *pStatus = response;
    return error;
}

//------------------------------------------------------------------------------
/// Addressed card sends its status register.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
/// \param pStatus  Pointer to a status variable.
//------------------------------------------------------------------------------
static unsigned char Cmd13(SdCard * pSd, unsigned int *pStatus)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SEND_STATUS_CMD;
    pCommand->arg = pSd->cardAddress << 16;
    pCommand->resType = 1;
    pCommand->pResp = pStatus;

    // Send command
    error = SendCommand(pSd);

    return error;
}

//------------------------------------------------------------------------------
/// In the case of a Standard Capacity SD Memory Card, this command sets the
/// block length (in bytes) for all following block commands
/// (read, write, lock).
/// Default block length is fixed to 512 Bytes.
/// Set length is valid for memory access commands only if partial block read
/// operation are allowed in CSD.
/// In the case of a High Capacity SD Memory Card, block length set by CMD16
/// command does not affect the memory read and write commands. Always 512
/// Bytes fixed block length is used. This command is effective for LOCK_UNLOCK
/// command. In both cases, if block length is set larger than 512Bytes, the
/// card sets the BLOCK_LEN_ERROR bit.
/// \param pSd  Pointer to a SD card driver instance.
/// \param blockLength  Block length in bytes.
//------------------------------------------------------------------------------
static unsigned char Cmd16(SdCard * pSd, unsigned short blockLength)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SET_BLOCKLEN_CMD;
    pCommand->arg = blockLength;
    pCommand->resType = 1;
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);

    return error;
}

//------------------------------------------------------------------------------
/// Continously transfers datablocks from card to host until interrupted by a
/// STOP_TRANSMISSION command.
/// \param pSd        Pointer to a SD card driver instance.
/// \param blockSize  Block size (shall be set to 512 in case of high capacity).
/// \param pData      Pointer to the DW aligned buffer to be filled.
/// \param address    SD card address.
//------------------------------------------------------------------------------
static unsigned char Cmd18(SdCard * pSd,
                           unsigned short nbBlock,
                           unsigned char *pData,
                           unsigned int address, unsigned int *pStatus)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_READ_MULTIPLE_BLOCK_CMD;
    pCommand->arg = address;
    pCommand->resType = 1;
    pCommand->pResp = &response;

    pCommand->blockSize = SD_BLOCK_SIZE;
    pCommand->nbBlock = nbBlock;
    pCommand->pData = pData;

    pCommand->dataTran = 1;
    pCommand->isRead = 1;
    pCommand->tranType = MCI_NEW_TRANSFER;

    // Send command
    error = SendCommand(pSd);

    if (pStatus)
        *pStatus = response;

    return error;
}

//------------------------------------------------------------------------------
/// Write block command
/// \param pSd  Pointer to a SD card driver instance.
/// \param blockSize  Block size (shall be set to 512 in case of high capacity).
/// \param pData  Pointer to the DW aligned buffer to be filled.
/// \param address  SD card address.
//------------------------------------------------------------------------------
static unsigned char Cmd25(SdCard * pSd,
                           unsigned short nbBlock,
                           unsigned char *pData,
                           unsigned int address, unsigned int *pStatus)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_WRITE_MULTIPLE_BLOCK_CMD;
    pCommand->arg = address;
    pCommand->resType = 1;
    pCommand->pResp = &response;

    pCommand->blockSize = SD_BLOCK_SIZE;
    pCommand->nbBlock = nbBlock;
    pCommand->pData = pData;

    pCommand->dataTran = 1;
    pCommand->tranType = MCI_NEW_TRANSFER;

    // Send command
    error = SendCommand(pSd);
    if (pStatus)
        *pStatus = response;

    return error;
}

//------------------------------------------------------------------------------
/// Initialization delay: The maximum of 1 msec, 74 clock cycles and supply
/// ramp up time.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
static unsigned char Cmd55(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_APP_CMD;
    pCommand->arg = (pSd->cardAddress << 16);
    pCommand->resType = 1;
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);

    return error;
}

/*
//------------------------------------------------------------------------------
/// SPI Mode, Reads the OCR register of a card
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
/// \param pOcr   OCR value of the card
//------------------------------------------------------------------------------
static unsigned char Cmd58(SdCard *pSd, unsigned int *pOcr)
{
    SdCmd *pCommand = &(pSd->command);
    unsigned char error;
    unsigned int response[2];

    TRACE_DEBUG("Cmd58()\n\r");
    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_READ_OCR_CMD;
    pCommand->resType = 3;
    pCommand->pResp = &response[0];

    // Send command
    error = SendCommand(pSd);
    return error;
}

//------------------------------------------------------------------------------
/// SPI Mode, Set CRC option of a card
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
/// \param option  CRC option, 1 to turn on, 0 to trun off
//------------------------------------------------------------------------------
static unsigned char Cmd59(SdCard *pSd, unsigned char option)
{
    SdCmd *pCommand = &(pSd->command);
    unsigned char error;
    unsigned int response;

    TRACE_DEBUG("Cmd59()\n\r");
    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_CRC_ON_OFF_CMD;
    pCommand->arg = (option & 0x1);
    pCommand->resType = 1;
    pCommand->pResp = &response;

    // Send command
    error = SendCommand(pSd);

    return error;
}
*/

//------------------------------------------------------------------------------
/// Defines the data bus width (00=1bit or 10=4 bits bus) to be used for data
/// transfer.
/// The allowed data bus widths are given in SCR register.
/// \param pSd  Pointer to a SD card driver instance.
/// \param busWidth  Bus width in bits.
/// \return the command transfer result (see SendCommand).
//------------------------------------------------------------------------------
static unsigned char Acmd6(SdCard * pSd, unsigned char busWidth)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    error = Cmd55(pSd);
    if (error) {

        return error;
    }

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SD_SET_BUS_WIDTH_CMD;
    pCommand->arg = (busWidth == 4) ? SD_STAT_DATA_BUS_WIDTH_4BIT :
        SD_STAT_DATA_BUS_WIDTH_1BIT;
    pCommand->resType = 1;
    pCommand->pResp = &response;

    // Send command
    return SendCommand(pSd);
}

//------------------------------------------------------------------------------
/// The SD Status contains status bits that are related to the SD memory Card
/// proprietary features and may be used for future application-specific usage.
/// Can be sent to a card only in 'tran_state'.
//------------------------------------------------------------------------------
static unsigned char Acmd13(SdCard * pSd, unsigned int *pSdSTAT)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response[1];

    error = Cmd55(pSd);
    if (error) {

        return error;
    }

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SD_STATUS_CMD;
    pCommand->resType = 1;
    pCommand->pResp = response;

    pCommand->blockSize = 512 / 8;
    pCommand->nbBlock = 1;
    pCommand->pData = (unsigned char *)pSdSTAT;

    pCommand->dataTran = 1;
    pCommand->isRead = 1;
    pCommand->tranType = MCI_NEW_TRANSFER;

    // Send command
    error = SendCommand(pSd);

    return error;
}

//------------------------------------------------------------------------------
/// Asks to all cards to send their operations conditions.
/// Returns the command transfer result (see SendCommand).
/// \param pSd  Pointer to a SD card driver instance.
/// \param hcs  Shall be true if Host support High capacity.
/// \param pCCS  Set the pointed flag to 1 if hcs != 0 and SD OCR CCS flag is set.
//------------------------------------------------------------------------------
static unsigned char Acmd41(SdCard * pSd, unsigned char hcs,
                            unsigned char *pCCS)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response;

    do {
        error = Cmd55(pSd);
        if (error) {
            return error;
        }

        ResetCommand(pCommand);
        // Fill command information
        pCommand->cmd = AT91C_SD_APP_OP_COND_CMD;
        pCommand->arg = AT91C_MMC_HOST_VOLTAGE_RANGE;
        if (hcs) {
            pCommand->arg |= AT91C_CCS;
        }

        pCommand->resType = 3;
        pCommand->pResp = &response;

        // Send command

        error = SendCommand(pSd);
        if (error) {
            return error;
        }
        *pCCS = ((response & AT91C_CCS) != 0);
    }
    while ((response & AT91C_CARD_POWER_UP_BUSY) != AT91C_CARD_POWER_UP_BUSY);

    return 0;
}

//------------------------------------------------------------------------------
/// SD Card Configuration Register (SCR) provides information on the SD Memory
/// Card's special features that were configured into the given card. The size
/// of SCR register is 64 bits.
//------------------------------------------------------------------------------
static unsigned char Acmd51(SdCard * pSd, unsigned int *pSCR)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    unsigned int response[1];

    error = Cmd55(pSd);
    if (error) {

        return error;
    }

    ResetCommand(pCommand);
    // Fill command information
    pCommand->cmd = AT91C_SD_SEND_SCR_CMD;
    pCommand->resType = 1;
    pCommand->pResp = response;

    pCommand->blockSize = 64 / 8;
    pCommand->nbBlock = 1;
    pCommand->pData = (unsigned char *)pSCR;

    pCommand->dataTran = 1;
    pCommand->isRead = 1;
    pCommand->tranType = MCI_NEW_TRANSFER;

    // Send command
    error = SendCommand(pSd);

    //if (!error) Int2MsbFirstStream((unsigned char*)pSCR, 8 / 4);

    return error;
}

#if defined(MCI2_INTERFACE) && defined(AT91C_MCI_SPCMD_BOOTREQ)
//------------------------------------------------------------------------------
/// Terminate boot stream.
/// \param pSd      Pointer to SdCard instance.
//------------------------------------------------------------------------------
static unsigned char BootEnd(SdCard * pSd)
{
    SdCmd *pCommand = &(pSd->command);

    ResetCommand(pCommand);

    // Send boot end
    pCommand->cmd = AT91C_BOOTEND;

    return SendCommand(pSd);
}

//------------------------------------------------------------------------------
/// In boot operation mode, the processor can read boot data from the slave,
/// by keeping the CMD line low after power-on before issuing CMD1.
/// BootEnd() must be invoked after the boot request done.
/// \param pSd      Pointer to SdCard instance.
/// \param pBuffer  The buffer holding received data.
/// \param length   The buffer length.
//------------------------------------------------------------------------------
static unsigned char BootREQ(SdCard * pSd,
                             unsigned char *pBuffer,
                             unsigned int nbBlocks, unsigned char ackEnable)
{
    SdCmd *pCommand = &(pSd->command);

    unsigned char error;

    ResetCommand(pCommand);

    // Send boot request
    pCommand->cmd = ackEnable ? (AT91C_BOOTREQ | AT91C_MCI_BOOTACK)
        : AT91C_BOOTREQ;
    pCommand->blockSize = SD_BLOCK_SIZE;
    pCommand->nbBlock = nbBlocks;
    pCommand->pData = pBuffer;
    pCommand->isRead = 1;
    pCommand->tranType = MCI_NEW_TRANSFER;

    error = SendCommand(pSd);
    if (error) {

        return error;
    }
    return error;
}
#endif

//------------------------------------------------------------------------------
/// Continue to transfer datablocks from card to host until interrupted by a
/// STOP_TRANSMISSION command.
/// \param pSd  Pointer to a SD card driver instance.
/// \param blockSize  Block size (shall be set to 512 in case of high capacity).
/// \param pData  Pointer to the application buffer to be filled.
/// \param address  SD card address.
//------------------------------------------------------------------------------
static unsigned char ContinuousRead(SdCard * pSd,
                                    unsigned short nbBlock,
                                    unsigned char *pData,
                                    SdCallback pCb, void *pArg)
{
    SdCmd *pCommand = &(pSd->command);

    ResetCommand(pCommand);
    // Fill command information
    pCommand->blockSize = SD_BLOCK_SIZE;
    pCommand->nbBlock = nbBlock;
    pCommand->pData = pData;

    pCommand->dataTran = 1;
    pCommand->tranType = MCI_CONTINUE_TRANSFER;
    pCommand->isRead = 1;

    pCommand->callback = pCb;
    pCommand->pArg = pArg;

    // Send command
    return SendCommand(pSd);
}

//------------------------------------------------------------------------------
/// Continue to transfer datablocks from host to card until interrupted by a
/// STOP_TRANSMISSION command.
/// \param pSd  Pointer to a SD card driver instance.
/// \param blockSize  Block size (shall be set to 512 in case of high capacity).
/// \param pData  Pointer to the application buffer to be filled.
//------------------------------------------------------------------------------
static unsigned char ContinuousWrite(SdCard * pSd,
                                     unsigned short nbBlock,
                                     const unsigned char *pData,
                                     SdCallback pCb, void *pArg)
{
    SdCmd *pCommand = &(pSd->command);

    ResetCommand(pCommand);
    // Fill command information
    pCommand->blockSize = SD_BLOCK_SIZE;
    pCommand->nbBlock = nbBlock;
    pCommand->pData = (unsigned char *)pData;

    pCommand->dataTran = 1;
    pCommand->tranType = MCI_CONTINUE_TRANSFER;

    pCommand->callback = pCb;
    pCommand->pArg = pArg;

    // Send command
    return SendCommand(pSd);
}

//------------------------------------------------------------------------------
/// Try SW Reset several times (CMD0 with ARG 0)
/// \param pSd      Pointer to a SD card driver instance.
/// \param retry    Retry times.
/// \return 0 or MCI error code.
//------------------------------------------------------------------------------
static unsigned char SwReset(SdCard * pSd, unsigned int retry)
{
    unsigned int i;

    unsigned char error = 0;

    for (i = 0; i < retry; i++) {
        error = Cmd0(pSd, 0);
        if (error != MCI_STATUS_NORESPONSE)
            break;
    }
    return error;
}

/*
//------------------------------------------------------------------------------
/// Re-init card to trans state.
//------------------------------------------------------------------------------
static unsigned char ReInit(SdCard *pSd)
{
    #if 0
    unsigned char error;
    error = SwReset(pSd, 1);
    if (error) {
        TRACE_ERROR("ReInit.Cmd0: %d\n\r", error);
        return error;
    }
    error = Cmd1(pSd);
    if (error) {
        TRACE_ERROR("ReInit.Cmd1: %d\n\r", error);
        return error;
    }
    error = Cmd2(pSd);
    if (error) {
        TRACE_ERROR("ReInit.Cmd2: %d\n\r", error);
        return error;
    }
    error = Cmd3(pSd);
    if (error) {
        TRACE_ERROR("ReInit.Cmd3: %d\n\r", error);
        return error;
    }
    error = Cmd7(pSd, pSd->cardAddress);
    if (error) {
        TRACE_ERROR("ReInit.Cmd7: %d\n\r", error);
        return error;
    }
    #endif
    return 0;
}
*/
//------------------------------------------------------------------------------
/// Move SD card to transfer state.
//------------------------------------------------------------------------------
static unsigned char MoveToTranState(SdCard * pSd)
{
    unsigned char error;

    unsigned int status;

    // Quit transfer state
    if ((pSd->state == SD_STATE_READ)
        || (pSd->state == SD_STATE_WRITE)) {

        error = Cmd12(pSd, (pSd->state == SD_STATE_READ), &status);
        if (error) {

            return error;
        }
    }
    // Put device into tran state
    error = Cmd13(pSd, &status);
    if (error) {

        return error;
    }
    if ((status & STATUS_STATE) == STATUS_STBY) {
        error = Cmd7(pSd, pSd->cardAddress);
        if (error) {

            return error;
        }
    }

    return 0;
}

//------------------------------------------------------------------------------
/// Move SD card to transfer state. The buffer size must be at
/// least 512 byte long. This function checks the SD card status register and
/// address the card if required before sending the transfer command.
/// Returns 0 if successful; otherwise returns an code describing the error.
/// \param pSd      Pointer to a SD card driver instance.
/// \param address  Address of the block to transfer.
/// \param nbBlocks Number of blocks to be transfer, 0 for infinite transfer.
/// \param pData    Data buffer whose size is at least the block size.
/// \param isRead   1 for read data and 0 for write data.
//------------------------------------------------------------------------------
static unsigned char MoveToTransferState(SdCard * pSd,
                                         unsigned int address,
                                         unsigned short nbBlocks,
                                         unsigned char *pData,
                                         unsigned char isRead)
{
    unsigned int status;

    unsigned char error;

    if ((pSd->state == SD_STATE_READ)
        || (pSd->state == SD_STATE_WRITE)) {
#if 1                           //!defined(MCI2_INTERFACE)
        if (pSd->state == SD_STATE_WRITE) {
        }
#endif
        // RW MULTI with length
        error = Cmd12(pSd, (pSd->state == SD_STATE_READ), &status);
        if (error) {

            return error;
        }
#if !defined(MCI2_INTERFACE)
        // RW MULTI Infinite
        if (pSd->state == SD_STATE_WRITE) {
//            while(MCI_CheckBusy((Mci *)pSd->pSdDriver) != 0);
        }
#endif
    }

    if (isRead) {
        // Wait for card to be ready for data transfers
        do {
            error = Cmd13(pSd, &status);
            if (error) {

                return error;
            }
            if (((status & STATUS_STATE) == STATUS_IDLE)
                || ((status & STATUS_STATE) == STATUS_READY)
                || ((status & STATUS_STATE) == STATUS_IDENT)) {

                return SD_ERROR_NOT_INITIALIZED;
            }
            // If the card is in sending data state or in receivce data state
            if (((status & STATUS_STATE) == STATUS_RCV)
                || ((status & STATUS_STATE) == STATUS_DATA)) {

            }
        }
        while (((status & STATUS_READY_FOR_DATA) == 0)
               || ((status & STATUS_STATE) != STATUS_TRAN));

        // Read data
        // Move to Sending data state
        error = Cmd18(pSd, nbBlocks, pData, SD_ADDRESS(pSd, address), &status);
        if (error) {

            return error;
        }
        if (status & ~(STATUS_READY_FOR_DATA | STATUS_STATE)) {

            return SD_ERROR_DRIVER;
        }
    } else {
        // Wait for card to be ready for data transfers
        do {
            error = Cmd13(pSd, &status);
            if (error) {

                return error;
            }
        }
        while ((status & STATUS_READY_FOR_DATA) == 0);
        // Move to Sending data state
        error = Cmd25(pSd, nbBlocks, pData, SD_ADDRESS(pSd, address), &status);
        if (error) {

            return error;
        }
        if (status & (STATUS_WRITE & ~(STATUS_READY_FOR_DATA | STATUS_STATE))) {

            return SD_ERROR_DRIVER;
        }
    }

    if (!error)
        pSd->preBlock = address + (nbBlocks - 1);
    return error;
}

//------------------------------------------------------------------------------
/// Switch the bus width of card
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Switch the HS mode of card
/// \param pSd      Pointer to SdCard instance.
/// \param hsEnable 1 to enable, 0 to disable.
//------------------------------------------------------------------------------
static unsigned char SdMmcSwitchHsMode(SdCard * pSd, unsigned char hsEnable)
{
    unsigned int status;

    unsigned char error = SD_ERROR_DRIVER;

    if (pSd->mode == hsEnable)
        return 0;
    if (pSd->cardType >= CARD_MMC) {
        MmcCmd6Arg cmd6Arg;

        cmd6Arg.access = 0x3;
        cmd6Arg.index = SD_EXTCSD_HS_TIMING_INDEX;
        cmd6Arg.value = hsEnable ? SD_EXTCSD_HS_TIMING_ENABLE
            : SD_EXTCSD_HS_TIMING_DISABLE;
        cmd6Arg.cmdSet = 0;
        error = Cmd6(pSd, &cmd6Arg, 0, &status);
        if (error) {

        } else if (status & STATUS_SWITCH_ERROR) {

            error = SD_ERROR_DRIVER;
        } else {

            pSd->mode = hsEnable;
        }
    } else if (pSd->cardType >= CARD_SD) {
        SdCmd6Arg cmd6Arg;

        unsigned int switchStatus[512 / 32];

        cmd6Arg.mode = 1;
        cmd6Arg.reserved = 0;
        cmd6Arg.reserveFG6 = 0xF;
        cmd6Arg.reserveFG5 = 0xF;
        cmd6Arg.reserveFG4 = 0xF;
        cmd6Arg.reserveFG3 = 0xF;
        cmd6Arg.command = 0;
        cmd6Arg.accessMode = 1;
        error = Cmd6(pSd, &cmd6Arg, switchStatus, &status);
#if 0
        unsigned int i;

        printf("SD Switch status:");
        for (i = 0; i < 512 / 8; i++) {
            if ((i % 8) == 0)
                printf("\n\r[%3d]", i);
            printf(" %02x", ((char *)switchStatus)[i]);
        }
        printf("\n\r");
        printf(" _FG1_INFO %x\n\r", SD_SW_STAT_FUN_GRP1_INFO(switchStatus));
        printf(" _FG1_RC   %x\n\r", SD_SW_STAT_FUN_GRP1_RC(switchStatus));
        printf(" _FG1_BUSY %x\n\r", SD_SW_STAT_FUN_GRP1_BUSY(switchStatus));
        printf(" _FG1_DS_V %x\n\r", SD_SW_STAT_DATA_STRUCT_VER(switchStatus));
#endif
        if (error) {

        } else if (status & STATUS_SWITCH_ERROR) {

            error = SD_ERROR_DRIVER;
        } else if (SD_SW_STAT_FUN_GRP1_RC(switchStatus)
                   == SD_SW_STAT_FUN_GRP_RC_ERROR) {

            error = SD_ERROR_DRIVER;
        } else if (SD_SW_STAT_FUN_GRP1_BUSY(switchStatus)) {

            error = SD_ERROR_DRIVER;
        } else {

            pSd->mode = hsEnable;
        }
    }

    return error;
}

//------------------------------------------------------------------------------
/// Process a list of SWITCH command
/// \param  pSd      Pointer to SdCard instance.
/// \param  pArgList Argument list.
/// \param  listSize Number of arguments listed.
/// \return 0, or error code and argument index.
//------------------------------------------------------------------------------
static unsigned short MmcSwitchSettings(SdCard * pSd,
                                        const MmcCmd6Arg * pArgList,
                                        unsigned int listSize,
                                        unsigned int *pErrSta)
{
    unsigned int i, status;

    unsigned char error;

    for (i = 0; i < listSize; i++) {
        error = Cmd6(pSd, &pArgList[i], 0, &status);
        if (pErrSta)
            *pErrSta = status;
        if (error) {
            return (error | (i << 8));
        }
        if (status & ~(STATUS_STATE | STATUS_READY_FOR_DATA)) {

        } else {

        }
    }
    return 0;
}

//------------------------------------------------------------------------------
/// Switch card state between STBY and TRAN
/// \param pSd      Pointer to a SD card driver instance.
/// \param address  Card address to TRAN, 0 to STBY
//------------------------------------------------------------------------------
static unsigned char MmcSelectCard(SdCard * pSd, unsigned short address)
{
    unsigned char error;

    unsigned int status;

    unsigned int targetState = address ? STATUS_TRAN : STATUS_STBY;

    unsigned int srcState = address ? STATUS_STBY : STATUS_TRAN;

    // At this stage the Initialization and identification process is achieved
    // The SD card is supposed to be in Stand-by State
    while (1) {
        error = Cmd13(pSd, &status);
        if (error) {

            return error;
        }
        if ((status & STATUS_READY_FOR_DATA)) {
            unsigned int currState = status & STATUS_STATE;

            if (currState == targetState)
                return 0;
            if (currState != srcState) {

                return SD_ERROR_DRIVER;
            }
            break;
        }
    }

    // witch to TRAN mode to Select the current SD/MMC
    // so that SD ACMD6 can process or EXT_CSD can read.
    error = Cmd7(pSd, address);
    if (error == SD_ERROR_NOT_INITIALIZED && address == 0) {
    } else if (error) {

    }

    return error;
}

//------------------------------------------------------------------------------
/// Get EXT_CSD information
/// \param pSd      Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
static unsigned char MmcGetExtInformation(SdCard * pSd)
{
    unsigned char error;

    // Reset data (512 bytes)
    // memset(pSd->extData, 0x00, 512);

    // MMC 4.0 Higher version
    if (SD_CSD_STRUCTURE(pSd) >= 2) {

        error = Cmd8(pSd, 0, pSd->extData);
        if (error) {

        }
    }
    return 0;
}

//------------------------------------------------------------------------------
/// Get SCR and SD Status information
/// \param pSd      Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
static unsigned char SdGetExtInformation(SdCard * pSd)
{
    unsigned char error;

    // Reset data (64 + 512 bits, 8 + 64 bytes)
    // memset(pSd->extData, 0x00, 512);

    // SD Status
    if (pSd->optCmdBitMap & SD_ACMD13_SUPPORT) {
        error = Acmd13(pSd, &pSd->extData[SD_EXT_OFFSET_SD_STAT]);
        if (error) {

            pSd->optCmdBitMap &= ~SD_ACMD13_SUPPORT;
        }
    }
    // SD SCR
    error = Acmd51(pSd, &pSd->extData[SD_EXT_OFFSET_SD_SCR]);
    if (error) {

    }

    return 0;
}

//------------------------------------------------------------------------------
/// Update SD/MMC information.
/// Update CSD for card speed switch.
/// Update ExtDATA for any card function switch.
/// \param pSd      Pointer to a SD card driver instance.
/// \return error code when update CSD error.
//------------------------------------------------------------------------------
static unsigned char SdMmcUpdateInformation(SdCard * pSd,
                                            unsigned char csd,
                                            unsigned char extData)
{
    unsigned char error;

    // Update CSD for new TRAN_SPEED value
    if (csd) {
        MmcSelectCard(pSd, 0);
        Delay(800);
        error = Cmd9(pSd);
        if (error) {

            return error;
        }
        error = MmcSelectCard(pSd, pSd->cardAddress);
    }
    if (pSd->cardType >= CARD_MMC)
        MmcGetExtInformation(pSd);
    else if (pSd->cardType >= CARD_SD)
        SdGetExtInformation(pSd);
    GetTransSpeedValue(pSd);

    return 0;
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Write Block of data in a buffer pointed by pData. The buffer size must be at
/// least 512 byte long. This function checks the SD card status register and
/// address the card if required before sending the read command.
/// Returns 0 if successful; otherwise returns an code describing the error.
/// \param pSd      Pointer to a SD card driver instance.
/// \param address  Address of the block to read.
/// \param pData    Data buffer whose size is at least the block size, it can
///            be 1,2 or 4-bytes aligned when used with DMA.
/// \param length   Number of blocks to be read.
/// \param pCallback Pointer to callback function that invoked when read done.
///                  0 to start a blocked read.
/// \param pArgs     Pointer to callback function arguments.
//------------------------------------------------------------------------------
#if !defined(OP_BOOTSTRAP_MCI_on)
unsigned char SD_Write(SdCard * pSd,
                       unsigned int address,
                       void *pData,
                       unsigned short length, SdCallback pCallback, void *pArgs)
{
    unsigned char error;

    // If callback is defined, performe none blocked writing
    if (pCallback) {
        if (MCI_IsTxComplete((Mci *) pSd) == 0) {
            return SD_ERROR_BUSY;
        }
    }
    if (pSd->state != SD_STATE_WRITE || pSd->preBlock + 1 != address) {
        // Start infinite block writing
        error = MoveToTransferState(pSd, address, 0, 0, 0);
    } else
        error = 0;
    if (!error) {
        pSd->state = SD_STATE_WRITE;
        error = ContinuousWrite(pSd, length, pData, pCallback, pArgs);
        pSd->preBlock = address + (length - 1);
    }

    return 0;
}
#endif
//------------------------------------------------------------------------------
/// Read Block of data in a buffer pointed by pData. The buffer size must be at
/// least 512 byte long. This function checks the SD card status register and
/// address the card if required before sending the read command.
/// Returns 0 if successful; otherwise returns an code describing the error.
/// \param pSd  Pointer to a SD card driver instance.
/// \param address  Address of the block to read.
/// \param nbBlocks Number of blocks to be read.
/// \param pData    Data buffer whose size is at least the block size, it can
///            be 1,2 or 4-bytes aligned when used with DMA.
//------------------------------------------------------------------------------
unsigned char SD_ReadBlock(SdCard * pSd,
                           unsigned int address,
                           unsigned short nbBlocks, unsigned char *pData)
{
    unsigned char error = 0;

#if !defined(MCI2_INTERFACE)
#if !defined(AT91C_MCI_RDPROOF)
    error = MoveToTransferState(pSd, address, nbBlocks, pData, 1);
    pSd->state = SD_STATE_READ;
#else
    if ((pSd->state == SD_STATE_READ)
        && ((pSd->preBlock + 1) == address)) {

#if defined(at91rm9200)
        error = Cmd12(pSd, 0);
        if (error) {
            return error;
        }
#else

        error = ContinuousRead(pSd, nbBlocks, pData, 0, 0);
        pSd->preBlock = address + (nbBlocks - 1);
#endif
    } else {
        error = MoveToTransferState(pSd, address, nbBlocks, pData, 1);
        pSd->state = SD_STATE_READ;
    }
#endif
#else
    if (pSd->state != SD_STATE_READ || pSd->preBlock + 1 != address) {
        // Start infinite block reading
        error = MoveToTransferState(pSd, address, 0, 0, 1);
    }
    if (!error) {
        pSd->state = SD_STATE_READ;
        error = ContinuousRead(pSd, nbBlocks, pData, 0, 0);
        if (!error)
            pSd->preBlock = address + (nbBlocks - 1);
    }
#endif
    return error;
}

//------------------------------------------------------------------------------
/// Write Block of data pointed by pData. The buffer size must be at
/// least 512 byte long. This function checks the SD card status register and
/// address the card if required before sending the read command.
/// Returns 0 if successful; otherwise returns an SD_ERROR code.
/// \param pSd  Pointer to a SD card driver instance.
/// \param address  Address of block to write.
/// \param nbBlocks Number of blocks to be read
/// \param pData    Data buffer whose size is at least the block size, it can
///            be 1,2 or 4-bytes aligned when used with DMA.
//------------------------------------------------------------------------------
#if !defined(OP_BOOTSTRAP_MCI_on)
unsigned char SD_WriteBlock(SdCard * pSd,
                            unsigned int address,
                            unsigned short nbBlocks, const unsigned char *pData)
{
    unsigned char error = 0;

#if !defined(MCI2_INTERFACE)
#if !defined(AT91C_MCI_WRPROOF)
    error = MoveToTransferState(pSd, address, nbBlocks,
                                (unsigned char *)pData, 0);
    pSd->state = SD_STATE_WRITE;
#else
    if ((pSd->state == SD_STATE_WRITE)
        && ((pSd->preBlock + 1) == address)) {

        error = ContinuousWrite(pSd, nbBlocks, pData, 0, 0);
        pSd->preBlock = address + (nbBlocks - 1);
    } else {

        //TRACE_FATAL("SD_WriteBlock:MoveToTransferState\n\r");
        error = MoveToTransferState(pSd, address, nbBlocks,
                                    (unsigned char *)pData, 0);
        pSd->state = SD_STATE_WRITE;
    }
#endif
#else
    if (pSd->state != SD_STATE_WRITE || pSd->preBlock + 1 != address) {
        // Start infinite block writing
        error = MoveToTransferState(pSd, address, 0, 0, 0);
    }
    if (!error) {
        pSd->state = SD_STATE_WRITE;
        error = ContinuousWrite(pSd, nbBlocks, pData, 0, 0);
        if (!error)
            pSd->preBlock = address + (nbBlocks - 1);
    }
#endif

    return error;
}
#endif
//------------------------------------------------------------------------------
/// Run the SDcard SD Mode initialization sequence. This function runs the
/// initialisation procedure and the identification process, then it sets the
/// SD card in transfer state to set the block length and the bus width.
/// Returns 0 if successful; otherwise returns an SD_ERROR code.
/// \param pSd  Pointer to a SD card driver instance.
/// \param pSdDriver  Pointer to SD driver already initialized
//------------------------------------------------------------------------------
static unsigned short SdMmcInit(SdCard * pSd, SdDriver * pSdDriver)
{
    unsigned char isCCSet;

    unsigned short error;

    unsigned int status = 0;

    unsigned char cmd8Retries = 1;

    unsigned int cmd1Retries = 10000;   //120;

    unsigned char isHdSupport = 0;

    unsigned char isHsSupport = 0;

    unsigned char updateInformation = 0;

    // The command GO_IDLE_STATE (CMD0) is the software reset command and sets
    // card into Idle State regardless of the current card state.
    MCI_EnableHsMode((Mci *) pSdDriver, 0);
    error = SwReset(pSd, 1);
    if (error) {

        return error;
    }
    // CMD8 is newly added in the Physical Layer Specification Version 2.00 to
    // support multiple voltage ranges and used to check whether the card
    // supports supplied voltage. The version 2.00 host shall issue CMD8 and
    // verify voltage before card initialization.
    // The host that does not support CMD8 shall supply high voltage range...

    do {
        error = Cmd8(pSd, 1, (void *)1);
    }
    while ((error == SD_ERROR_NORESPONSE) && (cmd8Retries-- > 0));

    if (error == SD_ERROR_NORESPONSE) {
        // No response : Ver2.00 or later SD Memory Card(voltage mismatch)
        // or Ver1.X SD Memory Card
        // or not SD Memory Card

        Delay(800);

        // ACMD41 is a synchronization command used to negotiate the operation
        // voltage range and to poll the cards until they are out of their
        // power-up sequence.
        error = Acmd41(pSd, 0, &isCCSet);
        if (error) {

            // Acmd41 failed : MMC card or unknown card
            error = SwReset(pSd, 10);
            if (error) {

                return error;
            }
#if !(defined(CONFIG_AT91SAM9G10EK))
            do {
                error = Cmd1(pSd, 1, &isHdSupport);
            }
            while ((error) && (cmd1Retries-- > 0));
            if (error) {

                return error;
            } else
#endif
            {
                pSd->cardType = CARD_MMC;
                if (isHdSupport) {
                    pSd->cardType = CARD_MMCHD;

                } else {

                }
            }
        } else {

            if (isCCSet == 0) {

                pSd->cardType = CARD_SD;
            }
        }
    } else if (!error) {

        // Valid response : Ver2.00 or later SD Memory Card
        error = Acmd41(pSd, 1, &isCCSet);
        if (error) {

            return error;
        }
        if (isCCSet) {

            pSd->cardType = CARD_SDHC;
        } else {

            pSd->cardType = CARD_SD;
        }
    } else {

        return error;
    }

    // The host then issues the command ALL_SEND_CID (CMD2) to the card to get
    // its unique card identification (CID) number.
    // Card that is unidentified (i.e. which is in Ready State) sends its CID
    // number as the response (on the CMD line).
    error = Cmd2(pSd);
    if (error) {

        return error;
    }
    // Thereafter, the host issues CMD3 (SEND_RELATIVE_ADDR) asks the
    // card to publish a new relative card address (RCA), which is shorter than
    // CID and which is used to address the card in the future data transfer
    // mode. Once the RCA is received the card state changes to the Stand-by
    // State. At this point, if the host wants to assign another RCA number, it
    // can ask the card to publish a new number by sending another CMD3 command
    // to the card. The last published RCA is the actual RCA number of the card.
    error = Cmd3(pSd);
    if (error) {

        return error;
    }
    // SEND_CSD (CMD9) to obtain the Card Specific Data (CSD register),
    // e.g. block length, card storage capacity, etc...
    error = Cmd9(pSd);
    if (error) {

        return error;
    }
    // Now select the card, to TRAN state
    error = MmcSelectCard(pSd, pSd->cardAddress);
    if (error) {

        return error;
    }
    // Now in TRAN, reset bus width to 1bit and obtain setup information
    MCI_SetBusWidth((Mci *) pSd->pSdDriver, MCI_SDCBUS_1BIT);

    // If the card support EXT_CSD, read it!

#if !(defined(CONFIG_AT91SAM9G10EK))
    // Get extended information of the card
    SdMmcUpdateInformation(pSd, 0, 0);

    // Advanced settings for HD & HS card
    if (pSd->cardType >= CARD_MMC) {

        if (SD_CSD_STRUCTURE(pSd) >= 2) {

            MmcCmd6Arg cmd6Arg;

            unsigned char busWidth, widthMode;

            // Calculate MMC busWidth (limited by slot information)
            switch (pSd->pSdDriver->mciMode & AT91C_MCI_SCDBUS) {
#if defined(AT91C_MCI_SCDBUS_8BITS)
            case AT91C_MCI_SCDBUS_8BITS:
                busWidth = 8;
                widthMode = MCI_SDCBUS_8BIT;
                break;
#endif

#if defined(AT91C_MCI_SCDBUS_4BITS)
            case AT91C_MCI_SCDBUS_4BITS:
                busWidth = 4;
                widthMode = MCI_SDCBUS_4BIT;
                break;
#endif

            default:
                busWidth = 1;
                widthMode = MCI_SDCBUS_1BIT;
            }

            // Switch to max bus width (4 now)
            cmd6Arg.access = 0x3;
            cmd6Arg.index = SD_EXTCSD_BUS_WIDTH_INDEX;
            cmd6Arg.value = SD_EXTCSD_BUS_WIDTH_4BIT;
            cmd6Arg.cmdSet = 0;
            error = Cmd6(pSd, &cmd6Arg, 0, 0);
            if (!error) {

                MCI_SetBusWidth((Mci *) pSd->pSdDriver, widthMode);
                updateInformation = 1;
            } else {

            }

#if !defined(OP_BOOTSTRAP_MCI_on)
            // Switch to HS mode
            if (gSdmmcAutoHsEnable) {
                cmd6Arg.access = 0x3;
                cmd6Arg.index = SD_EXTCSD_HS_TIMING_INDEX;
                cmd6Arg.value = SD_EXTCSD_HS_TIMING_ENABLE;
                cmd6Arg.cmdSet = 0;
                error = Cmd6(pSd, &cmd6Arg, 0, &status);
                if (error || (status & STATUS_SWITCH_ERROR)) {

                } else {
                    MCI_EnableHsMode((Mci *) pSdDriver, 1);

                    isHsSupport = 1;
                    updateInformation = 1;
                }
            }
#endif                          // end of OP_BOOTSTRAP_MCI_on
        }
    } else if (pSd->cardType >= CARD_SD) {

        // Switch to 4-bits bus width
        // (All SD Card shall support 1-bit, 4 bitswidth)
        error = Acmd6(pSd, 4);

        if (error) {

            return error;
        }
        MCI_SetBusWidth((Mci *) pSd->pSdDriver, MCI_SDCBUS_4BIT);

#if !defined(OP_BOOTSTRAP_MCI_on)
        // SD Spec V1.10 or higher, switch to high-speed mode
        if (gSdmmcAutoHsEnable) {
            if (SD_SCR_SD_SPEC(pSd) >= SD_SCR_SD_SPEC_1_10) {
                SdCmd6Arg cmd6Arg;

                unsigned int switchStatus[512 / 32];

                cmd6Arg.mode = 1;
                cmd6Arg.reserved = 0;
                cmd6Arg.reserveFG6 = 0xF;
                cmd6Arg.reserveFG5 = 0xF;
                cmd6Arg.reserveFG4 = 0xF;
                cmd6Arg.reserveFG3 = 0xF;
                cmd6Arg.command = 0;
                cmd6Arg.accessMode = 1;
                error = Cmd6(pSd, &cmd6Arg, switchStatus, &status);
#if 0
                unsigned int i;

                printf("SD Switch status:");
                for (i = 0; i < 512 / 8; i++) {
                    if ((i % 8) == 0)
                        printf("\n\r[%3d]", i);
                    printf(" %02x", ((char *)switchStatus)[i]);
                }
                printf("\n\r");
                printf(" _FG1_INFO %x\n\r",
                       SD_SW_STAT_FUN_GRP1_INFO(switchStatus));
                printf(" _FG1_RC   %x\n\r",
                       SD_SW_STAT_FUN_GRP1_RC(switchStatus));
                printf(" _FG1_BUSY %x\n\r",
                       SD_SW_STAT_FUN_GRP1_BUSY(switchStatus));
                printf(" _FG1_DS_V %x\n\r",
                       SD_SW_STAT_DATA_STRUCT_VER(switchStatus));
#endif
                if (error || (status & STATUS_SWITCH_ERROR)) {

                } else if (SD_SW_STAT_FUN_GRP1_RC(switchStatus)
                           == SD_SW_STAT_FUN_GRP_RC_ERROR) {

                } else if (SD_SW_STAT_FUN_GRP1_BUSY(switchStatus)) {

                } else {
                    MCI_EnableHsMode((Mci *) pSdDriver, 1);

                    isHsSupport = 1;
                }
            }
        }
#endif
        // Update
        updateInformation = 1;
    }

    if (updateInformation) {

        SdMmcUpdateInformation(pSd, isHsSupport, 1);
    }
#else
    pSd->transSpeed = (1000 * 25) * 1000;
#endif
    return 0;
}

//------------------------------------------------------------------------------
/// Run the SDcard initialization sequence. This function runs the
/// initialisation procedure and the identification process, then it sets the
/// SD card in transfer state to set the block length and the bus width.
/// Returns 0 if successful; otherwise returns an SD_ERROR code.
/// \param pSd  Pointer to a SD card driver instance.
/// \param pSdDriver  Pointer to SD driver already initialized.
//------------------------------------------------------------------------------
unsigned char SD_Init(SdCard * pSd, SdDriver * pSdDriver)
{
    unsigned char error;

    //TRACE_DEBUG("SD_Init()\n\r");

    // Initialize SdCard structure
    pSd->pSdDriver = pSdDriver;
    pSd->cardAddress = 0;
    pSd->preBlock = 0xffffffff;
    pSd->state = SD_STATE_INIT;
    pSd->cardType = UNKNOWN_CARD;
    pSd->optCmdBitMap = 0xFFFFFFFF;
    pSd->mode = 0;
    ResetCommand(&pSd->command);

    // Initialization delay: The maximum of 1 msec, 74 clock cycles and supply
    // ramp up time. Supply ramp up time provides the time that the power is
    // built up to the operating level (the bus master supply voltage) and the
    // time to wait until the SD card can accept the first command.

    // Power On Init Special Command
    //TRACE_DEBUG("Pon()\n\r");
    error = Pon(pSd);
    if (error) {

        return error;
    }
    // After power-on or CMD0, all cards?CMD lines are in input mode, waiting
    // for start bit of the next command.
    // The cards are initialized with a default relative card address
    // (RCA=0x0000) and with a default driver stage register setting
    // (lowest speed, highest driving current capability).

    error = (unsigned char)SdMmcInit(pSd, pSdDriver);
    if (error) {

        return error;
    }
    // In the case of a Standard Capacity SD Memory Card, this command sets the
    // block length (in bytes) for all following block commands
    // (read, write, lock).
    // Default block length is fixed to 512 Bytes.
    // Set length is valid for memory access commands only if partial block read
    // operation are allowed in CSD.
    // In the case of a High Capacity SD Memory Card, block length set by CMD16
    // command does not affect the memory read and write commands. Always 512
    // Bytes fixed block length is used. This command is effective for
    // LOCK_UNLOCK command.
    // In both cases, if block length is set larger than 512Bytes, the card sets
    // the BLOCK_LEN_ERROR bit.
    if (pSd->cardType == CARD_SD) {
        error = Cmd16(pSd, SD_BLOCK_SIZE);
        if (error) {
            pSd->optCmdBitMap &= ~SD_CMD16_SUPPORT;

        }
    }
    // Reset status for R/W
    pSd->state = SD_STATE_READY;

    // If MMC Card & get size from EXT_CSD
    if (pSd->cardType >= CARD_MMC && SD_CSD_C_SIZE(pSd) == 0xFFF) {
        pSd->blockNr = SD_EXTCSD_BLOCKNR(pSd);
        // Block number less than 0x100000000/512
        if (pSd->blockNr > 0x800000)
            pSd->totalSize = 0xFFFFFFFF;
        else
            pSd->totalSize = SD_EXTCSD_TOTAL_SIZE(pSd);
    }
    // If SD CSD v2.0
    else if (pSd->cardType >= CARD_SD && SD_CSD_STRUCTURE(pSd) >= 1) {
        pSd->blockNr = SD_CSD_BLOCKNR_HC(pSd);
        pSd->totalSize = 0xFFFFFFFF;
    }
    // Normal card
    else {
        pSd->totalSize = SD_CSD_TOTAL_SIZE(pSd);
        pSd->blockNr = SD_CSD_BLOCKNR(pSd);
    }

    if (pSd->cardType == UNKNOWN_CARD) {
        return SD_ERROR_NOT_INITIALIZED;
    } else {
        return 0;
    }
}

//------------------------------------------------------------------------------
/// Switch the SD/MMC card to High-Speed mode.
/// pSd->transSpeed will change to new speed limit.
/// Invoke MCI_SetSpeed() and MCI_EnableHsMode() to change MCI timing after.
/// For SD/MMC card, the speed mode will not change back until another init.
/// \param pSd      Pointer to a SD card driver instance.
/// \param hsMode   1 to enable HS mode, 0 to disable
///                 0xFF to return current mode.
/// \return current mode is hsMode is 0xFF;
///         error code if hsMode is 0 or 1.
//------------------------------------------------------------------------------
#if 0
unsigned char SD_HighSpeedMode(SdCard * pSd, unsigned char hsMode)
{
    unsigned char error = 0;

    if (hsMode == 0xFF)
        return pSd->mode;
    if (hsMode == 0) {

        return SD_ERROR_DRIVER;
    }
    // Quit transfer state
    error = MoveToTranState(pSd);
    if (error) {

        return error;
    }

    if (pSd->mode != hsMode) {
        error = SdMmcSwitchHsMode(pSd, hsMode);
#if !(defined(CONFIG_AT91SAM9G10EK) && defined(WINCE))
        if (error == 0)
            error = SdMmcUpdateInformation(pSd, 1, 1);
#endif
    }
    // Reset state for data R/W
    pSd->state = SD_STATE_READY;

    return error;
}
#endif

unsigned char SD_BusWidth(SdCard * pSd, unsigned char busWidth)
{
    return 0;
    // Reset state for data R/W
    pSd->state = SD_STATE_READY;
}

#if defined(MCI2_INTERFACE) && defined(AT91C_MCI_SPCMD_BOOTREQ)
//------------------------------------------------------------------------------
/// Read Block of data in a buffer pointed by pData. The buffer size must be at
/// least 512 byte long. This function checks the SD card status register and
/// address the card if required before sending the read command.
/// Returns 0 if successful; otherwise returns an code describing the error.
/// \param pSd  Pointer to a SD card driver instance.
/// \param address  Address of the block to read.
/// \param nbBlocks Number of blocks to be read.
/// \param pData  Data buffer whose size is at least the block size.
//------------------------------------------------------------------------------
unsigned char MMC_BootRead(SdCard * pSd,
                           unsigned int nbBlocks, unsigned char *pData)
{
    unsigned char error;

    unsigned char bootAck = 0;

    unsigned char busWidth = MCI_SDCBUS_4BIT;

    if (pSd->state != SD_STATE_BOOT)
        return SD_ERROR_DRIVER;

#if 0
    switch (SD_EXTCSD_BOOT_BUS_WIDTH(pSd)) {
    case SD_EXTCSD_BOOT_BUS_1BIT:
        busWidth = MCI_SDCBUS_1BIT;
        break;
    case SD_EXTCSD_BOOT_BUS_8BIT:
        busWidth = MCI_SDCBUS_8BIT;
        break;
    }

    if (SD_EXTCSD_BOOT_CONFIG(pSd) & SD_EXTCSD_BOOT_PARTITION_ACK)
        bootAck = 1;
#endif

    MCI_SetBusWidth((Mci *) pSd->pSdDriver, busWidth);
    error = BootREQ(pSd, pData, nbBlocks, bootAck);
    pSd->state = SD_STATE_BOOT;

    return error;
}

//------------------------------------------------------------------------------
/// In boot operation mode, the master can read boot data from the slave.
/// By keeping CMD line low after power-on
/// \param pSd  Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
unsigned char MMC_BootInit(SdCard * pSd)
{
    unsigned char error = 0;

    error = PonBoot(pSd);

    if (!error) {

        //error = BootREQ(pSd, 0, 0, 0);

        if (!error)
            pSd->state = SD_STATE_BOOT;
        else {

        }
    } else {

    }

    return error;
}

//------------------------------------------------------------------------------
/// In boot operation mode, the master can read boot data from the slave.
/// By sending CMD0 with argument + 0xFFFFFFFA
/// \param pSd  Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
unsigned char MMC_BootStart(SdCard * pSd)
{
    unsigned char error;

    if (pSd->state == SD_STATE_BOOT)
        return 0;

    if (pSd->cardType >= CARD_MMC
        && SD_CSD_STRUCTURE(pSd) >= 2
        && SD_CID_BGA(pSd) == 1 && SD_EXTCSD_BOOT_INFO(pSd) == 1) {
    } else
        return SD_ERROR_NOT_SUPPORT;

    error = Cmd0(pSd, 0xFFFFFFFA);
    pSd->state = SD_STATE_BOOT;

    return 0;
}

//------------------------------------------------------------------------------
/// Terminate the boot operation mode
/// \param pSd  Pointer to a SD card driver instance.
//------------------------------------------------------------------------------
unsigned char MMC_BootStop(SdCard * pSd)
{
    unsigned char error;

    if (pSd->state != SD_STATE_BOOT)
        return 0;

    error = BootEnd(pSd);

    if (!error)
        pSd->state = SD_STATE_IDLE;

    return error;
}

//------------------------------------------------------------------------------
/// Setup Boot Settings
/// \param resetBus Wether bus width is reset to 1-bit after quit boot mode.
/// \param busWidth The bus width in boot operation.
/// \param bootPart The partition used for boot operation.
/// \param accPart  The partition to access with normal read/write.
/// \param bootAck  Enable boot acknoledge.
/// \return 0 or error code.
//------------------------------------------------------------------------------
unsigned char MMC_SetupBootMode(SdCard * pSd,
                                unsigned char resetBus,
                                unsigned char busWidth,
                                unsigned char bootPart,
                                unsigned char accPart, unsigned char bootAck)
{
    unsigned int status;

    unsigned short error;

    const MmcCmd6Arg bootArgs[] = {
        // BOOT_CONFIG
        {3, 179, (bootAck << 6) | (bootPart << 3) | (accPart << 0), 0},
        // BOOT_BUS_WIDTH
        {3, 177, (busWidth << 2) | (resetBus << 0), 0}
    };

    if (pSd->cardType >= CARD_MMC
        && SD_CSD_STRUCTURE(pSd) >= 2 && SD_CID_CBS(pSd) == 1) {
    } else
        return SD_ERROR_NOT_SUPPORT;
    //if (MMC_GetBootSizeKB(pSd) == 0) return SD_ERROR_NOT_SUPPORT;

    // Quit transfer state
    error = MoveToTranState(pSd);
    if (error) {

        return error;
    }
    // Setup all boot informations
    error = MmcSwitchSettings(pSd,
                              bootArgs,
                              sizeof (bootArgs) / sizeof (MmcCmd6Arg), &status);
    if (error) {

        return (unsigned char)error;
    }
    // Update the EXT_CSD
#if 1
    error = Cmd8(pSd, 0, pSd->extData);
    if (error) {

    }
#if 0
    if (SD_EXTCSD_BOOT_BUS_WIDTH(pSd) != bootArgs[0].value
        || SD_EXTCSD_BOOT_CONFIG(pSd) != bootArgs[1].value) {

        TRACE_ERROR("MMC_SetupBootMode: ExtCSD not changed\n\r");

#if 1
        Cmd13(pSd, &status);
        TRACE_INFO("  CARD status: 0x%x\n\r", status);
#endif
        return SD_ERROR_DRIVER;
    }
#endif
#endif

    // Reset state for data R/W
    pSd->state = SD_STATE_READY;

    return 0;
}

//------------------------------------------------------------------------------
/// \return 0 or error code.
//------------------------------------------------------------------------------
unsigned char MMC_StopBootMode()
{
    return 0;
}
#endif

//------------------------------------------------------------------------------
/// Display the content of the CID register
/// \param pCid  Pointer to the Cid register value
//------------------------------------------------------------------------------
void SD_DisplayRegisterCID(SdCard * pSd)
{

#if 1

#else
    TRACE_INFO("CID MID Manufacturer ID       %02X\n\r", SD_CID_MID(pSd));

    TRACE_INFO("CID OID OEM/Application ID    %c%c\n\r",
               (char)SD_CID_OID_BYTE_1(pSd), (char)SD_CID_OID_BYTE_0(pSd));

    TRACE_INFO("CID PNM Product revision      %c%c%c%c%c\n\r",
               (char)SD_CID_PNM_BYTE_4(pSd),
               (char)SD_CID_PNM_BYTE_3(pSd),
               (char)SD_CID_PNM_BYTE_2(pSd),
               (char)SD_CID_PNM_BYTE_1(pSd), (char)SD_CID_PNM_BYTE_0(pSd));

    TRACE_INFO("CID PRV Product serial number %02X%04X\n\r",
               SD_CID_PRV_2(pSd), SD_CID_PRV_1(pSd));

    TRACE_INFO("CID MDT Manufacturing date    %04d/%02d\n\r",
               (unsigned short)SD_CID_MDT_YEAR(pSd),
               (unsigned char)SD_CID_MDT_MONTH(pSd));

    TRACE_INFO("CID CRC checksum              %02X\n\r", SD_CID_CRC(pSd));
#endif
}

//------------------------------------------------------------------------------
/// Display the content of the CSD register
/// \param pSd  
//------------------------------------------------------------------------------
void SD_DisplayRegisterCSD(SdCard * pSd)
{
#if 0
#if 0
    {
        unsigned int i;

        unsigned char *p = (unsigned char *)pSd->csd;

        for (i = 0; i < 128 / 8; i++) {
            if ((i % 16) == 0)
                TRACE_INFO_WP("\n\r [%3d]:", i);
            TRACE_INFO_WP(" %2x", p[i]);
        }
        TRACE_INFO_WP("\n\r");
        TRACE_INFO("------------------------\n\r");
    }
#else
    TRACE_INFO_WP("\n\r");
#endif
    TRACE_INFO(" .CSD_STRUCTURE      0x%x\r\n", SD_CSD_STRUCTURE(pSd));
    TRACE_INFO(" .SPEC_VERS          0x%x\r\n", SD_CSD_SPEC_VERS(pSd));
    TRACE_INFO(" .TAAC               0x%X\r\n", SD_CSD_TAAC(pSd));
    TRACE_INFO(" .NSAC               0x%X\r\n", SD_CSD_NSAC(pSd));
    TRACE_INFO(" .TRAN_SPEED         0x%X\r\n", SD_CSD_TRAN_SPEED(pSd));
    TRACE_INFO(" .CCC                0x%X\r\n", SD_CSD_CCC(pSd));
    TRACE_INFO(" .READ_BL_LEN        0x%X\r\n", SD_CSD_READ_BL_LEN(pSd));
    TRACE_INFO(" .READ_BL_PARTIAL    0x%X\r\n", SD_CSD_READ_BL_PARTIAL(pSd));
    TRACE_INFO(" .WRITE_BLK_MISALIGN 0x%X\r\n", SD_CSD_WRITE_BLK_MISALIGN(pSd));
    TRACE_INFO(" .READ_BLK_MISALIGN  0x%X\r\n", SD_CSD_READ_BLK_MISALIGN(pSd));
    TRACE_INFO(" .DSR_IMP            0x%X\r\n", SD_CSD_DSR_IMP(pSd));
    TRACE_INFO(" .C_SIZE             0x%X\r\n", SD_CSD_C_SIZE(pSd));
    TRACE_INFO(" .C_SIZE_HC          0x%X\r\n", SD_CSD_C_SIZE_HC(pSd));
    TRACE_INFO(" .VDD_R_CURR_MIN     0x%X\r\n", SD_CSD_VDD_R_CURR_MIN(pSd));
    TRACE_INFO(" .VDD_R_CURR_MAX     0x%X\r\n", SD_CSD_VDD_R_CURR_MAX(pSd));
    TRACE_INFO(" .VDD_W_CURR_MIN     0x%X\r\n", SD_CSD_VDD_W_CURR_MIN(pSd));
    TRACE_INFO(" .VDD_W_CURR_MAX     0x%X\r\n", SD_CSD_VDD_W_CURR_MAX(pSd));
    TRACE_INFO(" .C_SIZE_MULT        0x%X\r\n", SD_CSD_C_SIZE_MULT(pSd));
    TRACE_INFO(" .ERASE_BLK_EN       0x%X\r\n", SD_CSD_ERASE_BLK_EN(pSd));
    TRACE_INFO(" .SECTOR_SIZE        0x%X\r\n", SD_CSD_SECTOR_SIZE(pSd));
    TRACE_INFO(" .WP_GRP_SIZE        0x%X\r\n", SD_CSD_WP_GRP_SIZE(pSd));
    TRACE_INFO(" .WP_GRP_ENABLE      0x%X\r\n", SD_CSD_WP_GRP_ENABLE(pSd));
    TRACE_INFO(" .R2W_FACTOR         0x%X\r\n", SD_CSD_R2W_FACTOR(pSd));
    TRACE_INFO(" .WRITE_BL_LEN       0x%X\r\n", SD_CSD_WRITE_BL_LEN(pSd));
    TRACE_INFO(" .WRITE_BL_PARTIAL   0x%X\r\n", SD_CSD_WRITE_BL_PARTIAL(pSd));
    TRACE_INFO(" .FILE_FORMAT_GRP    0x%X\r\n", SD_CSD_FILE_FORMAT_GRP(pSd));
    TRACE_INFO(" .COPY               0x%X\r\n", SD_CSD_COPY(pSd));
    TRACE_INFO(" .PERM_WRITE_PROTECT 0x%X\r\n", SD_CSD_PERM_WRITE_PROTECT(pSd));
    TRACE_INFO(" .TMP_WRITE_PROTECT  0x%X\r\n", SD_CSD_TMP_WRITE_PROTECT(pSd));
    TRACE_INFO(" .FILE_FORMAT        0x%X\r\n", SD_CSD_FILE_FORMAT(pSd));
    TRACE_INFO(" .ECC                0x%X\r\n", SD_CSD_ECC(pSd));
    TRACE_INFO(" .CRC                0x%X\r\n", SD_CSD_CRC(pSd));
    TRACE_INFO(" .MULT               0x%X\r\n", SD_CSD_MULT(pSd));
    TRACE_INFO(" .BLOCKNR            0x%X\r\n", SD_CSD_BLOCKNR(pSd));
    TRACE_INFO(" .BLOCKNR_HC         0x%X\r\n", SD_CSD_BLOCKNR_HC(pSd));
    TRACE_INFO(" .BLOCK_LEN          0x%X\r\n", SD_CSD_BLOCK_LEN(pSd));
    TRACE_INFO(" .TOTAL_SIZE         0x%X\r\n", SD_CSD_TOTAL_SIZE(pSd));
    TRACE_INFO(" .TOTAL_SIZE_HC      0x%X\r\n", SD_CSD_TOTAL_SIZE_HC(pSd));
    TRACE_INFO(" -SD_TOTAL_SIZE      0x%X\r\n", SD_TOTAL_SIZE(pSd));
    TRACE_INFO(" -SD_TOTAL_BLOCK     0x%X\r\n", SD_TOTAL_BLOCK(pSd));
#endif
}

//------------------------------------------------------------------------------
/// Display the content of the EXT_CSD register
/// \param pSd  
//------------------------------------------------------------------------------
void SD_DisplayRegisterECSD(SdCard * pSd)
{
#if 0
    if (pSd->cardType >= CARD_MMC && SD_CSD_STRUCTURE(pSd) >= 2) {
    } else {
        TRACE_INFO("** EXT_CSD NOT SUPPORTED\n\r");
        return;
    }
    TRACE_INFO("======= EXT_CSD =======");
#if 0
    {
        unsigned int i;

        unsigned char *p = (unsigned char *)pSd->extData;

        for (i = 0; i < 512; i++) {
            if ((i % 16) == 0)
                TRACE_INFO_WP("\n\r [%3d]:", i);
            TRACE_INFO_WP(" %2x", p[i]);
        }
        TRACE_INFO_WP("\n\r");
        TRACE_INFO("------------------------\n\r");
    }
#else
    TRACE_INFO_WP("\n\r");
#endif
    TRACE_INFO(" .S_CMD_SET            : 0x%X\n\r", SD_EXTCSD_S_CMD_SET(pSd));
    TRACE_INFO(" .BOOT_INFO            : 0x%X\n\r", SD_EXTCSD_BOOT_INFO(pSd));
    TRACE_INFO(" .BOOT_SIZE_MULTI      : 0x%X\n\r",
               SD_EXTCSD_BOOT_SIZE_MULTI(pSd));
    TRACE_INFO(" .ACC_SIZE             : 0x%X\n\r", SD_EXTCSD_ACC_SIZE(pSd));
    TRACE_INFO(" .HC_ERASE_GRP_SIZE    : 0x%X\n\r",
               SD_EXTCSD_HC_ERASE_GRP_SIZE(pSd));
    TRACE_INFO(" .ERASE_TIMEOUT_MULT   : 0x%X\n\r",
               SD_EXTCSD_ERASE_TIMEOUT_MULT(pSd));
    TRACE_INFO(" .REL_WR_SEC_C         : 0x%X\n\r",
               SD_EXTCSD_REL_WR_SEC_C(pSd));
    TRACE_INFO(" .HC_WP_GRP_SIZE       : 0x%X\n\r",
               SD_EXTCSD_HC_WP_GRP_SIZE(pSd));
    TRACE_INFO(" .S_C_VCC              : 0x%X\n\r", SD_EXTCSD_S_C_VCC(pSd));
    TRACE_INFO(" .S_C_VCCQ             : 0x%X\n\r", SD_EXTCSD_S_C_VCCQ(pSd));
    TRACE_INFO(" .S_A_TIMEOUT          : 0x%X\n\r", SD_EXTCSD_S_A_TIMEOUT(pSd));
    TRACE_INFO(" .SEC_COUNT            : 0x%X\n\r", SD_EXTCSD_SEC_COUNT(pSd));
    TRACE_INFO(" .MIN_PERF_W_8_52      : 0x%X\n\r",
               SD_EXTCSD_MIN_PERF_W_8_52(pSd));
    TRACE_INFO(" .MIN_PERF_R_8_52      : 0x%X\n\r",
               SD_EXTCSD_MIN_PERF_R_8_52(pSd));
    TRACE_INFO(" .MIN_PERF_W_8_26_4_52 : 0x%X\n\r",
               SD_EXTCSD_MIN_PERF_W_8_26_4_52(pSd));
    TRACE_INFO(" .MIN_PERF_R_8_26_4_52 : 0x%X\n\r",
               SD_EXTCSD_MIN_PERF_R_8_26_4_52(pSd));
    TRACE_INFO(" .MIN_PERF_W_4_26      : 0x%X\n\r",
               SD_EXTCSD_MIN_PERF_W_4_26(pSd));
    TRACE_INFO(" .MIN_PERF_R_4_26      : 0x%X\n\r",
               SD_EXTCSD_MIN_PERF_R_4_26(pSd));
    TRACE_INFO(" .PWR_CL_26_360        : 0x%X\n\r",
               SD_EXTCSD_PWR_CL_26_360(pSd));
    TRACE_INFO(" .PWR_CL_52_360        : 0x%X\n\r",
               SD_EXTCSD_PWR_CL_52_360(pSd));
    TRACE_INFO(" .PWR_CL_26_195        : 0x%X\n\r",
               SD_EXTCSD_PWR_CL_26_195(pSd));
    TRACE_INFO(" .PWR_CL_52_195        : 0x%X\n\r",
               SD_EXTCSD_PWR_CL_52_195(pSd));
    TRACE_INFO(" .CARD_TYPE            : 0x%X\n\r", SD_EXTCSD_CARD_TYPE(pSd));
    TRACE_INFO(" .CSD_STRUCTURE        : 0x%X\n\r",
               SD_EXTCSD_CSD_STRUCTURE(pSd));
    TRACE_INFO(" .EXT_CSD_REV          : 0x%X\n\r", SD_EXTCSD_EXT_CSD_REV(pSd));
    TRACE_INFO(" .CMD_SET              : 0x%X\n\r", SD_EXTCSD_CMD_SET(pSd));
    TRACE_INFO(" .CMD_SET_REV          : 0x%X\n\r", SD_EXTCSD_CMD_SET_REV(pSd));
    TRACE_INFO(" .POWER_CLASS          : 0x%X\n\r", SD_EXTCSD_POWER_CLASS(pSd));
    TRACE_INFO(" .HS_TIMING            : 0x%X\n\r", SD_EXTCSD_HS_TIMING(pSd));
    TRACE_INFO(" .BUS_WIDTH            : 0x%X\n\r", SD_EXTCSD_BUS_WIDTH(pSd));
    TRACE_INFO(" .ERASED_MEM_CONT      : 0x%X\n\r",
               SD_EXTCSD_ERASED_MEM_CONT(pSd));
    TRACE_INFO(" .BOOT_CONFIG          : 0x%X\n\r", SD_EXTCSD_BOOT_CONFIG(pSd));
    TRACE_INFO(" .BOOT_BUS_WIDTH       : 0x%X\n\r",
               SD_EXTCSD_BOOT_BUS_WIDTH(pSd));
    TRACE_INFO(" .ERASE_GROUP_DEF      : 0x%X\n\r",
               SD_EXTCSD_ERASE_GROUP_DEF(pSd));
#endif
}

//------------------------------------------------------------------------------
/// Display the content of the SCR register
/// \param pSd  Pointer to SdCard instance.
//------------------------------------------------------------------------------
void SD_DisplayRegisterSCR(SdCard * pSd)
{
#if 0
    if (pSd->cardType >= CARD_SD && pSd->cardType <= CARD_SDHC) {
    } else {
        TRACE_INFO("** SCR NOT Supported!\n\r");
        return;
    }
    TRACE_INFO("========== SCR ==========");
#if 0
    {
        unsigned int i;

        unsigned char *p = (unsigned char *)pSd->extData;

        //TRACE_INFO_WP("\n\r");
        //TRACE_INFO("DATA @ 0x%X", (unsigned int)p);
        for (i = 0; i < 16; i++) {
            if ((i % 8) == 0)
                TRACE_INFO_WP("\n\r [%3d]:", i);
            TRACE_INFO_WP(" %02x", p[i]);
        }
        TRACE_INFO_WP("\n\r");
        TRACE_INFO("------------------------\n\r");
    }
#else
    TRACE_INFO_WP("\n\r");
#endif

    TRACE_INFO(" .SCR_STRUCTURE         :0x%X\n\r", SD_SCR_SCR_STRUCTURE(pSd));
    TRACE_INFO(" .SD_SPEC               :0x%X\n\r", SD_SCR_SD_SPEC(pSd));
    TRACE_INFO(" .DATA_STAT_AFTER_ERASE :0x%X\n\r",
               SD_SCR_DATA_STAT_AFTER_ERASE(pSd));
    TRACE_INFO(" .SD_SECURITY           :0x%X\n\r", SD_SCR_SD_SECURITY(pSd));
    TRACE_INFO(" .SD_BUS_WIDTHS         :0x%X\n\r", SD_SCR_SD_BUS_WIDTHS(pSd));
#endif
}

//------------------------------------------------------------------------------
/// Display the content of the SD Status
/// \param pSd  Pointer to SdCard instance.
//------------------------------------------------------------------------------
void SD_DisplaySdStatus(SdCard * pSd)
{
#if 0
    if (pSd->cardType >= CARD_SD
        && pSd->cardType <= CARD_SDHC
        && (pSd->optCmdBitMap & SD_ACMD13_SUPPORT)) {
    } else {
        TRACE_INFO("** SD Status NOT Supported!\n\r");
        return;
    }
    TRACE_INFO("=========== STAT ============");
#if 0
    {
        unsigned int i;

        unsigned char *p = (unsigned char *)pSd->extData;

        //TRACE_INFO_WP("\n\r");
        //TRACE_INFO("DATA @ 0x%X", (unsigned int)p);
        for (i = 0; i < 72; i++) {
            if ((i % 8) == 0)
                TRACE_INFO_WP("\n\r [%3d]:", i);
            TRACE_INFO_WP(" %02x", p[i]);
        }
        TRACE_INFO_WP("\n\r");
        TRACE_INFO("------------------------\n\r");
    }
#else
    TRACE_INFO_WP("\n\r");
#endif

    TRACE_INFO(" .DAT_BUS_WIDTH          :0x%X\n\r",
               SD_STAT_DAT_BUS_WIDTH(pSd));
    TRACE_INFO(" .SECURED_MODE           :0x%X\n\r", SD_STAT_SECURED_MODE(pSd));
    TRACE_INFO(" .SD_CARD_TYPE           :0x%X\n\r", SD_STAT_SD_CARD_TYPE(pSd));
    TRACE_INFO(" .SIZE_OF_PROTECTED_AREA :0x%X\n\r",
               SD_STAT_SIZE_OF_PROTECTED_AREA(pSd));
    TRACE_INFO(" .SPEED_CLASS            :0x%X\n\r", SD_STAT_SPEED_CLASS(pSd));
    TRACE_INFO(" .PERFORMANCE_MOVE       :0x%X\n\r",
               SD_STAT_PERFORMANCE_MOVE(pSd));
    TRACE_INFO(" .AU_SIZE                :0x%X\n\r", SD_STAT_AU_SIZE(pSd));
    TRACE_INFO(" .ERASE_SIZE             :0x%X\n\r", SD_STAT_ERASE_SIZE(pSd));
    TRACE_INFO(" .ERASE_TIMEOUT          :0x%X\n\r",
               SD_STAT_ERASE_TIMEOUT(pSd));
    TRACE_INFO(" .ERASE_OFFSET           :0x%X\n\r", SD_STAT_ERASE_OFFSET(pSd));
#endif
}

void StopReading(SdCard * pSd)
{
    Cmd12(pSd, 1, NULL);

}

#endif
