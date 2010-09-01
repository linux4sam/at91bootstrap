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
#if defined(CONFIG_DMA)
//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "dmad.h"
#include "dma.h"
#include "irq.h"

//------------------------------------------------------------------------------
//         Local types
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// DMA transfer descriptor. Tracks the status and parameters of a transfer
/// on the DMA bus.
//------------------------------------------------------------------------------
typedef struct _DmaTransfer {
    /// Buffer transfer status.
    volatile unsigned char status;
    /// Transfer buffer size in byte.
    unsigned int bufSize;
    /// Total transfer size to byte.
    volatile unsigned int transferSize;
    /// Optional callback function.
    DmaCallback callback;
} DmaTransfer;

//------------------------------------------------------------------------------
/// DMAD driver structure. Monitors the status of transfers on all
/// DMA channels.
//------------------------------------------------------------------------------
typedef struct _Dmad {

    /// List of transfers occuring on each channel.
    DmaTransfer transfers[DMA_CHANNEL_NUM];
} Dmad;

//------------------------------------------------------------------------------
//         Local variables
//------------------------------------------------------------------------------

/// Global DMA transfer instance.
static Dmad dmad;

//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// This handler function must be called by the DMAC interrupt service routine.
/// Identifies which event was activated and calls the associated function.
//------------------------------------------------------------------------------ 
void DMAD_Handler()
{
    unsigned int status;

    unsigned char channel;

    DmaTransfer *pTransfer;

    status = DMA_GetStatus();
    // Check if the buffer transfer completed is set.
    if (status & AT91C_BTC) {
        // Scan each channel status.
        for (channel = 0; channel < DMA_CHANNEL_NUM; channel++) {
            if (!(status & (DMA_BTC << channel))) {
                continue;
            }

            dmad.transfers[channel].transferSize -=
                dmad.transfers[channel].bufSize;
            // if next buffer is to be the last buffer in the transfer, then clear the automatic mode bit.
            if (dmad.transfers[channel].transferSize <=
                dmad.transfers[channel].bufSize) {
                DMA_ClearAutoMode(channel);
            }
            // Transfer finished
            if (dmad.transfers[channel].transferSize == 0) {
                pTransfer = &(dmad.transfers[channel]);
                pTransfer->callback();
                DMA_DisableIt(DMA_BTC << channel);
                DMA_DisableChannel(channel);
            } else {
                // Write the KEEPON field to clear the STALL states.
                DMA_KeeponChannel(channel);
            }
        }
    }
}

//------------------------------------------------------------------------------
/// Initializes the DMA controller.
/// \param channel Particular channel number
/// \param defaultHandler Using the default dmad interrupt handler.
//------------------------------------------------------------------------------
void DMAD_Initialize(unsigned char channel, unsigned char defaultHandler)
{
    unsigned int status;

    unsigned int flag;

    // Enable peripheral clock
#if !defined(at91sam9rl64)
    (*(volatile unsigned int *)(AT91C_BASE_PMC + PMC_PCER)) =
        1 << AT91C_ID_HDMA;
#endif

    // Read the channel handler status to ensure the channel is a free channel.
    status = DMA_GetChannelStatus();

    // Clear any pending interrupts on the channel.
    DMA_GetStatus();
    // Disble the channel.
    DMA_DisableChannel(channel);

    do {
        status = DMA_GetChannelStatus();
    } while (status & (1 << channel));
    // Disable the interrupt
    flag = 0xffffff;
    DMA_DisableIt(flag);
    // Enable DMA.
    DMA_Enable();
    if (defaultHandler) {
//        IRQ_ConfigureIT(AT91C_ID_HDMA, 0, DMAD_Handler);
        (*(unsigned int *)(AT91C_BASE_AIC + AIC_IDCR)) = 1 << AT91C_ID_HDMA;
//        IRQ_EnableIT(AT91C_ID_HDMA);
    }
    // Initialize transfer instance.
    dmad.transfers[channel].transferSize = 0;
}

//------------------------------------------------------------------------------
/// Configure the DMA transfer buffer by giving transfer mode, it could be single 
/// buffer or multi-buffer(LLI/auto-reload/contiguous buffers) with or without 
/// Picture-In-Picture mode.
/// \param channel Particular channel number.
/// \param sourceTransferMode Source buffer transfer mode.
/// \param destTransferMode Destination buffer transfer mode.
/// \param lli Pointer to a DmaLinkList structure instance.
/// \param pip Pointer to a PictureInPicture structure.
//------------------------------------------------------------------------------
unsigned char DMAD_Configure_Buffer(unsigned char channel,
                                    unsigned char sourceTransferMode,
                                    unsigned char destTransferMode,
                                    DmaLinkList * lli, PictureInPicture * pip)
{
    DmaTransfer *pTransfer = &(dmad.transfers[channel]);

    // Check that no transfer is pending on the channel
    if (pTransfer->transferSize > 0) {

        return DMAD_ERROR_BUSY;
    }
    // Configure source transfer mode.
    DMA_SetSourceBufferMode(channel, sourceTransferMode, 0);

    // Configure destination transfer mode.
    DMA_SetDestBufferMode(channel, destTransferMode, 0);

    if (lli) {
        DMA_SetDescriptorAddr(channel, (unsigned int)(&lli[0]));
    } else {
        DMA_SetDescriptorAddr(channel, 0);
    }

    if (pip) {
#if defined(AT91C_SRC_PIP)
        // If source picture-in-picture mode is enabled, program the DMAC_SPIP.
        if (pip->pipSourceBoundarySize) {
            // If destination picture-in-picture mode is enabled, program the DMAC_DPIP.
            DMA_SPIPconfiguration(channel, pip->pipSourceHoleSize,
                                  pip->pipSourceBoundarySize);
        }
#endif

#if defined(AT91C_DST_PIP)
        if (pip->pipDestBoundarySize) {
            DMA_DPIPconfiguration(channel, pip->pipDestHoleSize,
                                  pip->pipDestBoundarySize);
        }
#endif
    }
    return 0;
}

//------------------------------------------------------------------------------
/// Configure the DMA transfer control infomation.
/// \param channel Particular channel number.
/// \param bufSize Buffer transfer size in byte.
/// \param sourceWidth Source transfer width.
/// \param destWidth Destination transfer width.
/// \param sourceAddress Destination transfer width.
/// \param destAddress Destination transfer width.
//------------------------------------------------------------------------------
unsigned char DMAD_Configure_TransferController(unsigned char channel,
                                                unsigned int bufSize,
                                                unsigned char sourceWidth,
                                                unsigned char destWidth,
                                                unsigned int sourceAddress,
                                                unsigned int destAddress)
{
    DmaTransfer *pTransfer = &(dmad.transfers[channel]);

    // Check that no transfer is pending on the channel
    if (pTransfer->transferSize > 0) {

        return DMAD_ERROR_BUSY;
    }
    pTransfer->bufSize = bufSize;

    // Set up the transfer width and transfer size.
    DMA_SetSourceBufferSize(channel, bufSize, sourceWidth, destWidth, 0);

    if (sourceAddress) {
        // Write the starting source address.
        DMA_SetSourceAddr(channel, sourceAddress);
    }
    if (destAddress) {
        // Write the starting destination address.
        DMA_SetDestinationAddr(channel, destAddress);
    }
    return 0;
}

//------------------------------------------------------------------------------
/// Starts buffer transfer on the given channel
/// \param channel Particular channel number.
/// \param size Total transfer size in byte.
/// \param callback Optional callback function.
/// \param polling Polling channel status enable.
//------------------------------------------------------------------------------
unsigned char DMAD_BufferTransfer(unsigned char channel,
                                  unsigned int size,
                                  DmaCallback callback, unsigned char polling)
{
    DmaTransfer *pTransfer = &(dmad.transfers[channel]);

    // Check that no transfer is pending on the channel
    if (pTransfer->transferSize > 0) {

        return DMAD_ERROR_BUSY;
    }
    pTransfer->status = DMAD_ERROR_BUSY;
    pTransfer->transferSize = size;
    pTransfer->callback = callback;

    if (!polling) {
        DMA_EnableIt(DMA_BTC << channel);
    }
    // Enable the channel.
    DMA_EnableChannel(channel);

    if (polling) {
        while ((DMA_GetChannelStatus() & (DMA_ENA << channel)) ==
               (DMA_ENA << channel)) ;
        if (pTransfer->callback) {
            pTransfer->callback();
        }
        pTransfer->transferSize = 0;
        DMA_DisableChannel(channel);
    }
    return 0;
}

//------------------------------------------------------------------------------
/// Returns 1 if no transfer is currently pending on the given channel;
/// otherwise, returns 0.
/// \param channel  Channel number.
//------------------------------------------------------------------------------
unsigned char DMAD_IsFinished(unsigned char channel)
{

    if (dmad.transfers[channel].transferSize > 0) {
        return 0;
    } else {
        DMA_DisableChannel(channel);
        return 1;
    }
}
#endif
