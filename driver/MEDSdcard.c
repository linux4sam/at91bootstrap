/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support  
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
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
#include "part.h"
#include "MEDSdcard.h"
#include "fatfs_config.h"
#include "dbgu.h"
#include "debug.h"

#include "irq.h"
#include "pio.h"

#include "sdmmc_mci.h"
#if defined(MCI2_INTERFACE)
#include "dmad.h"
#endif

#include <string.h>

//------------------------------------------------------------------------------
//         Constants
//------------------------------------------------------------------------------

/// Number of SD Slots
#define NUM_SD_SLOTS            1
#define MAX_LUNS        1

#define SIZE_EBOOT 0x40000
#define SIZE_SETTING 0x1000

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------
Media medias[MAX_LUNS];

/// MCI driver instance.
static Mci mciDrv[NUM_SD_SLOTS];

/// SDCard driver instance.
static SdCard sdDrv[NUM_SD_SLOTS];

#if MCI_BUSY_CHECK_FIX && defined(BOARD_SD_DAT0)
/// SD DAT0 pin
static const Pin pinSdDAT0 = BOARD_SD_DAT0;
#endif

Media medias[1];

static FATFS fs;

static FIL fileObject;

FRESULT res;

void StopReading(SdCard * pSd);

//------------------------------------------------------------------------------
//      Internal Functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Optional: SD card detection
//------------------------------------------------------------------------------

/// SD card detection pin instance.
#if defined(BOARD_SD_PIN_CD)
static const Pin pinCardDetect = BOARD_SD_PIN_CD;
#endif

#if defined(BOARD_SD_MCI1_PIN_CD)
static const Pin pinCardDetect1 = BOARD_SD_MCI1_PIN_CD;
#endif

//------------------------------------------------------------------------------
/// Detect if SD card is connected
//------------------------------------------------------------------------------
#if 0
static unsigned char CardIsConnected(unsigned char slot)
{
    if (slot == 0) {
#if defined(BOARD_SD_PIN_CD)

        PIO_Configure(&pinCardDetect, 1);
        return PIO_Get(&pinCardDetect) ? 0 : 1;
#else
        return 1;
#endif
    }
    if (slot == 1) {
#if defined(BOARD_SD_MCI1_PIN_CD)

        PIO_Configure(&pinCardDetect1, 1);
        return PIO_Get(&pinCardDetect1) ? 0 : 1;
#else
        return 1;
#endif
    }

    return 0;
}
#endif
//------------------------------------------------------------------------------
//         Optional: Write protection status
//------------------------------------------------------------------------------

/// Write protection status pin instance.
#ifdef BOARD_SD_PIN_WP
static const Pin pinMciWriteProtect = BOARD_SD_PIN_WP;
#endif
#ifdef BOARD_SD_MCI1_PIN_WP
static const Pin pinMciWriteProtect1 = BOARD_SD_MCI1_PIN_WP;
#endif

//------------------------------------------------------------------------------
/// Checks if the device is write protected.
/// \return 1 if protected.
//------------------------------------------------------------------------------
static unsigned char CardIsProtected(unsigned char slot)
{
#if !defined(at91sam9g10)
    if (slot == 0) {
#ifdef BOARD_SD_PIN_WP
        PIO_Configure(&pinMciWriteProtect, 1);
        return (PIO_Get(&pinMciWriteProtect) != 0);
#else
        return 0;
#endif
    }

    if (slot == 1) {
#ifdef BOARD_SD_MCI1_PIN_WP
        PIO_Configure(&pinMciWriteProtect1, 1);
        return (PIO_Get(&pinMciWriteProtect1) != 0);
#else
        return 0;
#endif
    }
#endif
    return 0;
}

//------------------------------------------------------------------------------
/// Configure the PIO for SD
//------------------------------------------------------------------------------
static void ConfigurePIO(unsigned char mciID)
{
#ifdef BOARD_SD_PINS

    const Pin pinSd0[] = { BOARD_SD_PINS };
#endif

#ifdef BOARD_SD_MCI1_PINS
    const Pin pinSd1[] = { BOARD_SD_MCI1_PINS };
#endif

#if defined(at91sam9263)
    const Pin pinClkSel[] = { BOARD_CLK_SETTING };
#endif

    if (mciID == 0) {
#ifdef BOARD_SD_PINS
        PIO_Configure(pinSd0, PIO_LISTSIZE(pinSd0));
#endif

#if defined(at91sam9263)
        PIO_Configure(pinClkSel, PIO_LISTSIZE(pinClkSel));
#endif
    } else {
#ifdef BOARD_SD_MCI1_PINS
        PIO_Configure(pinSd1, PIO_LISTSIZE(pinSd1));
#endif
    }
}

//------------------------------------------------------------------------------
//! \brief  Reads a specified amount of data from a SDCARD memory
//! \param  media    Pointer to a Media instance
//! \param  address  Address of the data to read
//! \param  data     Pointer to the buffer in which to store the retrieved
//!                   data
//! \param  length   Length of the buffer
//! \param  callback Optional pointer to a callback function to invoke when
//!                   the operation is finished
//! \param  argument Optional pointer to an argument for the callback
//! \return Operation result code
//------------------------------------------------------------------------------
static unsigned char MEDSdcard_Read(Media * media,
                                    unsigned int address,
                                    void *data,
                                    unsigned int length,
                                    MediaCallback callback, void *argument)
{
    unsigned char error;

    unsigned int loop;

    unsigned int datap;

    // Check that the media is ready
    if (media->state != MED_STATE_READY) {

        return MED_STATUS_BUSY;
    }
    // Check that the data to read is not too big
    if ((length + address) > media->size) {

        return MED_STATUS_ERROR;
    }
    // Enter Busy state
    media->state = MED_STATE_BUSY;

    loop = length / FIRSTBOOT_BLOCK_LENGTH;

    while (loop > 0) {

        error =
            SD_ReadBlock((SdCard *) media->interface, address,
                         FIRSTBOOT_BLOCK_LENGTH, data);
        address += FIRSTBOOT_BLOCK_LENGTH;

        length -= FIRSTBOOT_BLOCK_LENGTH;

        datap = (unsigned int)data;
        datap += (FIRSTBOOT_BLOCK_LENGTH * FIRSTBOOT_BLOCK_SIZE);
        data = (void *)datap;

        loop--;

    }
    if (length > 0) {
        error =
            SD_ReadBlock((SdCard *) media->interface, address, length, data);
    }
    // Leave the Busy state
    media->state = MED_STATE_READY;

    // Invoke callback
    if (callback != 0) {

        callback(argument, MED_STATUS_SUCCESS, 0, 0);
    }

    return MED_STATUS_SUCCESS;
}

//------------------------------------------------------------------------------
//! \brief  Writes data on a SDRAM media
//! \param  media    Pointer to a Media instance
//! \param  address  Address at which to write
//! \param  data     Pointer to the data to write
//! \param  length   Size of the data buffer
//! \param  callback Optional pointer to a callback function to invoke when
//!                   the write operation terminates
//! \param  argument Optional argument for the callback function
//! \return Operation result code
//! \see    Media
//! \see    MediaCallback
//------------------------------------------------------------------------------
#if !defined(OP_BOOTSTRAP_MCI_on)
static unsigned char MEDSdcard_Write(Media * media,
                                     unsigned int address,
                                     void *data,
                                     unsigned int length,
                                     MediaCallback callback, void *argument)
{
    unsigned char error;

    unsigned int loop;

    unsigned int datap;

    // Check that the media if ready
    if (media->state != MED_STATE_READY) {

        return MED_STATUS_BUSY;
    }
    // Check that the data to write is not too big
    if ((length + address) > media->size) {

        return MED_STATUS_ERROR;
    }
    // Put the media in Busy state
    media->state = MED_STATE_BUSY;

    loop = length / FIRSTBOOT_BLOCK_LENGTH;
    while (loop > 0) {

        error =
            SD_WriteBlock((SdCard *) media->interface, address,
                          FIRSTBOOT_BLOCK_LENGTH, data);
        address += FIRSTBOOT_BLOCK_LENGTH;

        length -= FIRSTBOOT_BLOCK_LENGTH;

        datap = (unsigned int)data;
        datap += (FIRSTBOOT_BLOCK_LENGTH * FIRSTBOOT_BLOCK_SIZE);
        data = (void *)datap;

        loop--;

    }
    if (length > 0) {
        error =
            SD_WriteBlock((SdCard *) media->interface, address, length, data);
    }
    // Leave the Busy state
    media->state = MED_STATE_READY;

    // Invoke the callback if it exists
    if (callback != 0) {

        callback(argument, MED_STATUS_SUCCESS, 0, 0);
    }

    return MED_STATUS_SUCCESS;
}
#endif
//------------------------------------------------------------------------------
//! \brief Callback invoked when SD/MMC transfer done
//------------------------------------------------------------------------------
static void SdMmcCallback(unsigned char status, void *pCommand)
{
    SdCmd *pCmd = (SdCmd *) pCommand;

    Media *pMed = pCmd->pArg;

    MEDTransfer *pXfr = &pMed->transfer;

    // Error
    if (status == SD_ERROR_BUSY) {
        status = MED_STATUS_BUSY;
    } else if (status) {
        status = MED_STATUS_ERROR;
    }

    pMed->state = MED_STATE_READY;
    if (pXfr->callback) {
        pXfr->callback(pXfr->argument,
                       status, pXfr->length * pMed->blockSize, 0);
    }
}

//------------------------------------------------------------------------------
//! \brief  Writes data on a SDRAM media
//! \param  media    Pointer to a Media instance
//! \param  address  Address at which to write
//! \param  data     Pointer to the data to write
//! \param  length   Size of the data buffer
//! \param  callback Optional pointer to a callback function to invoke when
//!                   the write operation terminates
//! \param  argument Optional argument for the callback function
//! \return Operation result code
//! \see    Media
//! \see    MediaCallback
//------------------------------------------------------------------------------
#if !defined(OP_BOOTSTRAP_MCI_on)
static unsigned char MEDSdusb_Write(Media * media,
                                    unsigned int address,
                                    void *data,
                                    unsigned int length,
                                    MediaCallback callback, void *argument)
{
    MEDTransfer *pXfr;

    unsigned char error;

    // Check that the media if ready
    if (media->state != MED_STATE_READY) {

        return MED_STATUS_BUSY;
    }
    // Check that the data to write is not too big
    if ((length + address) > media->size) {

        return MED_STATUS_ERROR;
    }
    // Put the media in Busy state
    media->state = MED_STATE_BUSY;

    // Start media transfer
    pXfr = &media->transfer;
    pXfr->data = data;
    pXfr->address = address;
    pXfr->length = length;
    pXfr->callback = callback;
    pXfr->argument = argument;

    error = SD_Write((SdCard *) media->interface,
                     address, data, length, SdMmcCallback, media);

    return (error ? MED_STATUS_ERROR : MED_STATUS_SUCCESS);
}
#endif
//------------------------------------------------------------------------------
//      Exported Functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Detect if there is SD card in socket
//------------------------------------------------------------------------------
#if 0
unsigned char MEDSdcard_Detect(Media * media, unsigned char mciID)
{
    return CardIsConnected(mciID);
}
#endif
//------------------------------------------------------------------------------
/// Initializes a Media instance and the associated physical interface
/// \param  media Pointer to the Media instance to initialize
/// \return 1 if success.
//------------------------------------------------------------------------------
unsigned char MEDSdcard_Initialize(Media * media, unsigned char mciID)
{

    // Initialize SDcard
    //--------------------------------------------------------------------------

/*    if (!CardIsConnected(mciID)) return 0;
*/
    // Configure SDcard pins
    ConfigurePIO(mciID);

#if defined(MCI2_INTERFACE) && defined(MCI_DMA_ENABLE)
    DMAD_Initialize(BOARD_MCI_DMA_CHANNEL, DMAD_NO_DEFAULT_IT);
#endif
    // Initialize the MCI driver
    if (mciID == 0) {
//        IRQ_ConfigureIT(BOARD_SD_MCI_ID,  1, MCI0_IrqHandler);
        (*(unsigned int *)(AT91C_BASE_AIC + AIC_IDCR)) = 1 << BOARD_SD_MCI_ID;
        MCI_Init(mciDrv, BOARD_SD_MCI_BASE, BOARD_SD_MCI_ID, BOARD_SD_SLOT,
                 MCI_POLLING_MODE);
//        IRQ_EnableIT(BOARD_SD_MCI_ID);
    } else {
//              dbg_print("pos2.2\r\n");
#ifdef BOARD_SD_MCI1_ID
//        IRQ_ConfigureIT(BOARD_SD_MCI1_ID,  1, MCI0_IrqHandler);
        MCI_Init(mciDrv, BOARD_SD_MCI1_BASE, BOARD_SD_MCI1_ID,
                 BOARD_SD_MCI1_SLOT, MCI_POLLING_MODE);
//        IRQ_EnableIT(BOARD_SD_MCI1_ID);
#else

#endif
    }
//      dbg_print("pos2.3\r\n");
#if MCI_BUSY_CHECK_FIX && defined(BOARD_SD_DAT0)
    MCI_SetBusyFix(mciDrv, &pinSdDAT0);
#endif

    // Initialize the SD card driver
    if (SD_Init(sdDrv, (SdDriver *) mciDrv)) {

        return 0;
    } else {

        //SD_DisplayRegisterCSD(&sdDrv);

    }

    MCI_SetSpeed(mciDrv, sdDrv->transSpeed, sdDrv->transSpeed, BOARD_MCK);

    // Initialize media fields
    //--------------------------------------------------------------------------
    media->interface = sdDrv;
#if !defined(OP_BOOTSTRAP_MCI_on)
    media->write = MEDSdcard_Write;
#else
    media->write = 0;
#endif
    media->read = MEDSdcard_Read;
    media->lock = 0;
    media->unlock = 0;
    media->handler = 0;
    media->flush = 0;

    media->blockSize = SD_BLOCK_SIZE;
    media->baseAddress = 0;
    media->size = SD_TOTAL_BLOCK(sdDrv);

    media->mappedRD = 0;
    media->mappedWR = 0;
    media->protected = CardIsProtected(mciID);
    media->removable = 1;

    media->state = MED_STATE_READY;

    media->transfer.data = 0;
    media->transfer.address = 0;
    media->transfer.length = 0;
    media->transfer.callback = 0;
    media->transfer.argument = 0;

    return 1;
}

//------------------------------------------------------------------------------
/// Initializes a Media instance and the associated physical interface
/// \param  media Pointer to the Media instance to initialize
/// \return 1 if success.
//------------------------------------------------------------------------------
#if !defined(OP_BOOTSTRAP_MCI_on)
unsigned char MEDSdusb_Initialize(Media * media, unsigned char mciID)
{

    // Initialize SDcard
    //--------------------------------------------------------------------------

    if (!CardIsConnected(mciID))
        return 0;

    // Configure SDcard pins
    ConfigurePIO(mciID);

#if defined(MCI2_INTERFACE) && defined(MCI_DMA_ENABLE)
    DMAD_Initialize(BOARD_MCI_DMA_CHANNEL, DMAD_NO_DEFAULT_IT);
#endif
    // Initialize the MCI driver
    if (mciID == 0) {
//        IRQ_ConfigureIT(BOARD_SD_MCI_ID,  1, MCI0_IrqHandler);
        MCI_Init(mciDrv, BOARD_SD_MCI_BASE, BOARD_SD_MCI_ID, BOARD_SD_SLOT,
                 MCI_INTERRUPT_MODE);
//        IRQ_EnableIT(BOARD_SD_MCI_ID);
    } else {
#ifdef BOARD_SD_MCI1_ID
//        IRQ_ConfigureIT(BOARD_SD_MCI1_ID,  1, MCI0_IrqHandler);
        MCI_Init(mciDrv, BOARD_SD_MCI1_BASE, BOARD_SD_MCI1_ID, BOARD_SD_SLOT,
                 MCI_INTERRUPT_MODE);
//        IRQ_EnableIT(BOARD_SD_MCI1_ID);
#else

#endif
    }
#if MCI_BUSY_CHECK_FIX && defined(BOARD_SD_DAT0)
    MCI_SetBusyFix(mciDrv, &pinSdDAT0);
#endif

    // Initialize the SD card driver
    if (SD_Init(sdDrv, (SdDriver *) mciDrv)) {

        return 0;
    } else {

    }
    MCI_SetSpeed(mciDrv, sdDrv->transSpeed, sdDrv->transSpeed, BOARD_MCK);

    // Initialize media fields
    //--------------------------------------------------------------------------
    media->interface = sdDrv;
#if !defined(OP_BOOTSTRAP_MCI_on)
    media->write = MEDSdusb_Write;
#else
    media->write = 0;
#endif
    media->read = MEDSdusb_Read;
    media->lock = 0;
    media->unlock = 0;
    media->handler = 0;
    media->flush = 0;

    media->blockSize = SD_BLOCK_SIZE;
    media->baseAddress = 0;
    media->size = SD_TOTAL_BLOCK(sdDrv);

    media->mappedRD = 0;
    media->mappedWR = 0;
    media->protected = CardIsProtected(mciID);
    media->removable = 1;

    media->state = MED_STATE_READY;

    media->transfer.data = 0;
    media->transfer.address = 0;
    media->transfer.length = 0;
    media->transfer.callback = 0;
    media->transfer.argument = 0;

    return 1;
}
#endif
//------------------------------------------------------------------------------
/// erase all the Sdcard
/// \param  media Pointer to the Media instance to initialize
//------------------------------------------------------------------------------

#if !defined(OP_BOOTSTRAP_MCI_on)

void MEDSdcard_EraseAll(Media * media)
{
    unsigned char buffer[SD_BLOCK_SIZE];

    unsigned int block;

    unsigned int multiBlock = 1;        // change buffer size for multiblocks

    unsigned char error;

    // Clear the block buffer
    memset(buffer, 0, media->blockSize * multiBlock);

    for (block = 0;
         block < (SD_TOTAL_BLOCK((SdCard *) media->interface) - multiBlock);
         block += multiBlock) {

        error =
            SD_WriteBlock((SdCard *) media->interface, block, multiBlock,
                          buffer);

    }
}

//------------------------------------------------------------------------------
/// erase block
/// \param  media Pointer to the Media instance to initialize
/// \param  block to erase
//------------------------------------------------------------------------------
void MEDSdcard_EraseBlock(Media * media, unsigned int block)
{
    unsigned char buffer[SD_BLOCK_SIZE];

    unsigned char error;

    // Clear the block buffer
    memset(buffer, 0, media->blockSize);

    error = SD_WriteBlock((SdCard *) media->interface, block, 1, buffer);

}
#endif
//------------------------------------------------------------------------------
/// Get driver pointer
//------------------------------------------------------------------------------
#if 0
SdCard *MEDSdcard_GetDriver(unsigned int slot)
{
    if (slot >= NUM_SD_SLOTS)
        return 0;
    return &sdDrv[slot];
}
#endif

unsigned int load_SDCard()
{
    DWORD dwAddress;

    unsigned int ByteRead = 0;

    MEDSdcard_Initialize(&medias[0], BOARD_SD_MCI_ID_USE);

    memset(&fs, 0, sizeof (FATFS));     // Clear file system object    

    res = f_mount(0, &fs);
    if (res != FR_OK) {

        return 0;
    }

    res = f_open(&fileObject, OS_IMAGE_NAME, FA_OPEN_EXISTING | FA_READ);

    if (res != FR_OK) {
        return 0;
    }

    dwAddress = JUMP_ADDR;

    do {
        ByteRead = 0;
        res = f_read(&fileObject, (void *)(dwAddress), SIZE_EBOOT, &ByteRead);
        dwAddress += SIZE_EBOOT;
//              dbg_log(BOOTSTRAP_DEBUG_LEVEL,"%x, %x\r\n", dwAddress, ByteRead);
    } while (ByteRead >= SIZE_EBOOT);

    if (res != FR_OK) {

        return 0;
    }
#if !defined(at91sam9g10)

    res = f_close(&fileObject);
    if (res != FR_OK) {

        return 0;
    }
#endif

    StopReading((SdCard *) medias[0].interface);

//      Configure_System_Paramters();

    return 1;
}
#endif
