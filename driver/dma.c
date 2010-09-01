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

#include "dma.h"

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Configure a DMAC peripheral
//------------------------------------------------------------------------------
void DMA_Config(unsigned int flag)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_GCFG)) = flag;

}

//------------------------------------------------------------------------------
/// Enables a DMAC peripheral
//------------------------------------------------------------------------------
void DMA_Enable(void)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EN)) = AT91C_HDMA_ENABLE;
}

//------------------------------------------------------------------------------
/// Disables DMAC peripheral
//------------------------------------------------------------------------------
void DMA_Disable(void)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EN)) =
        ~(unsigned int)AT91C_HDMA_ENABLE;

}

//-----------------------------------------------------------------------------
/// Enable DMA interrupt
/// \param flag IT to be enabled
//-----------------------------------------------------------------------------
void DMA_EnableIt(unsigned int flag)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EBCIER)) = flag;
}

//-----------------------------------------------------------------------------
/// Disable DMA interrupt
/// \param flag IT to be enabled
//-----------------------------------------------------------------------------
void DMA_DisableIt(unsigned int flag)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EBCIDR)) = flag;
}

//-----------------------------------------------------------------------------
/// Return DMA Interrupt Status
//-----------------------------------------------------------------------------
unsigned int DMA_GetStatus(void)
{

    return (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EBCISR));
}

//-----------------------------------------------------------------------------
/// Return DMA Interrupt Mask Status
//-----------------------------------------------------------------------------
unsigned int DMA_GetInterruptMask(void)
{

    return (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EBCIMR));
}

//-----------------------------------------------------------------------------
/// Returns the current status register of the given DMA peripheral, but
/// masking interrupt sources which are not currently enabled.
//-----------------------------------------------------------------------------
unsigned int DMA_GetMaskedStatus(void)
{
    unsigned int status;

    status = (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EBCISR));

    status &= (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_EBCIMR));
    return status;
}

//------------------------------------------------------------------------------
/// Enables DMAC channel 
/// \param channel Particular channel number.
//------------------------------------------------------------------------------
void DMA_EnableChannel(unsigned int channel)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_CHER)) |=
        DMA_ENA << channel;
}

void DMA_EnableChannels(unsigned int bmChannels)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_CHER)) = bmChannels;
}

//------------------------------------------------------------------------------
/// Disables a DMAC channel 
/// \param channel Particular channel number.
//------------------------------------------------------------------------------
void DMA_DisableChannel(unsigned int channel)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_CHDR)) |=
        DMA_DIS << channel;

}

void DMA_DisableChannels(unsigned int bmChannels)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_CHDR)) = bmChannels;
}

//------------------------------------------------------------------------------
/// Resume DMAC channel from an stall state.
/// \param channel Particular channel number.
//------------------------------------------------------------------------------
void DMA_KeeponChannel(unsigned int channel)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_CHER)) |=
        DMA_KEEPON << channel;
}

//------------------------------------------------------------------------------
/// Clear automatic mode for multi-buffer transfer.
/// \param channel Particular channel number.
//------------------------------------------------------------------------------
void DMA_ClearAutoMode(unsigned int channel)
{

    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB)) &= 0x7FFFFFFF;
}

//------------------------------------------------------------------------------
/// Return DMAC channel status 
//------------------------------------------------------------------------------
unsigned int DMA_GetChannelStatus(void)
{
    return (*(volatile unsigned int *)(AT91C_BASE_HDMA + HDMA_CHSR));
}

//-----------------------------------------------------------------------------
/// Set DMA source address used by a HDMA channel.
/// \param channel Particular channel number.
/// \param sources sources address.
//-----------------------------------------------------------------------------
void DMA_SetSourceAddr(unsigned char channel, unsigned int address)
{
    if (((unsigned int)(address) & 0xFFF00000)) {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_SADDR)) = address;
    } else {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_SADDR)) =
            address + CHIP_SRAM0_BASEADDR;
    }

}

//-----------------------------------------------------------------------------
/// Set DMA destination address used by a HDMA channel.
/// \param channel Particular channel number.
/// \param sources destination address.
//-----------------------------------------------------------------------------
void DMA_SetDestinationAddr(unsigned char channel, unsigned int address)
{
    if (((unsigned int)(address) & 0xFFF00000)) {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_DADDR)) = address;
    } else {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_DADDR)) =
            address + CHIP_SRAM0_BASEADDR;
    }

}

//-----------------------------------------------------------------------------
/// Set DMA descriptor address used by a HDMA channel.
/// \param channel Particular channel number.
/// \param sources destination address.
//-----------------------------------------------------------------------------
void DMA_SetDescriptorAddr(unsigned char channel, unsigned int address)
{
    if (((unsigned int)(address) & 0xFFF00000)) {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_DSCR)) = address;
    } else {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_DSCR)) =
            address + CHIP_SRAM0_BASEADDR;
    }
}

//-----------------------------------------------------------------------------
/// Set DMA control A register used by a HDMA channel.
/// \param channel Particular channel number.
/// \param size Dma transfer size in byte.
/// \param sourceWidth Single transfer width for source.
/// \param destWidth Single transfer width for destination.
/// \param done Transfer done field.
//-----------------------------------------------------------------------------
void DMA_SetSourceBufferSize(unsigned char channel,
                             unsigned int size,
                             unsigned char sourceWidth,
                             unsigned char destWidth, unsigned char done)
{
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLA)) =
        (size | sourceWidth << 24 | destWidth << 28 | done << 31);
}

//-----------------------------------------------------------------------------
/// Set DMA transfer mode for source used by a HDMA channel.
/// \param channel Particular channel number.
/// \param transferMode Transfer buffer mode (single, LLI, reload or contiguous)
/// \param addressingType Type of addrassing mode
///                       0 : incrementing, 1: decrementing, 2: fixed.
//-----------------------------------------------------------------------------
void DMA_SetSourceBufferMode(unsigned char channel,
                             unsigned char transferMode,
                             unsigned char addressingType)
{
    unsigned int value;

    value = (*(volatile unsigned int *)
             (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB));
    value &= ~(AT91C_SRC_DSCR | AT91C_SRC_INCR | 1 << 31);
    switch (transferMode) {
    case DMA_TRANSFER_SINGLE:
        value |= AT91C_SRC_DSCR | addressingType << 24;
        break;
    case DMA_TRANSFER_LLI:
        value |= addressingType << 24;
        break;
    case DMA_TRANSFER_RELOAD:
    case DMA_TRANSFER_CONTIGUOUS:
        value |= AT91C_SRC_DSCR | addressingType << 24 | 1 << 31;
        break;
    }
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB)) = value;

    if (transferMode == DMA_TRANSFER_RELOAD
        || transferMode == DMA_TRANSFER_CONTIGUOUS) {
        value = (*(volatile unsigned int *)
                 (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG));
#if defined(AT91C_SRC_REP)
        value &= ~(unsigned int)AT91C_SRC_REP;
        // When automatic mode is activated, the source address and the control register are reloaded from previous transfer.
        if (transferMode == DMA_TRANSFER_RELOAD) {
            value |= AT91C_SRC_REP;
        }
#endif

        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG)) = value;
    } else {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG)) = 0;
    }
}

//-----------------------------------------------------------------------------
/// Set DMA transfer mode for destination used by a HDMA channel.
/// \param channel Particular channel number.
/// \param transferMode Transfer buffer mode (single, LLI, reload or contiguous)
/// \param addressingType Type of addrassing mode
///                       0 : incrementing, 1: decrementing, 2: fixed.
//-----------------------------------------------------------------------------
void DMA_SetDestBufferMode(unsigned char channel,
                           unsigned char transferMode,
                           unsigned char addressingType)
{
    unsigned int value;

    value = (*(volatile unsigned int *)
             (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB));
    value &= ~(unsigned int)(AT91C_DST_DSCR | AT91C_DST_INCR);

    switch (transferMode) {
    case DMA_TRANSFER_SINGLE:
    case DMA_TRANSFER_RELOAD:
    case DMA_TRANSFER_CONTIGUOUS:
        value |= AT91C_DST_DSCR | addressingType << 28;
        break;
    case DMA_TRANSFER_LLI:
        value |= addressingType << 28;
        break;
    }
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB)) = value;
    if (transferMode == DMA_TRANSFER_RELOAD
        || transferMode == DMA_TRANSFER_CONTIGUOUS) {
        value = (*(volatile unsigned int *)
                 (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG));
#if defined(AT91C_DST_REP)
        value &= ~(unsigned int)AT91C_DST_REP;
        // When automatic mode is activated, the source address and the control register are reloaded from previous transfer.
        if (transferMode == DMA_TRANSFER_RELOAD) {
            value |= AT91C_DST_REP;
        }
#endif
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG)) = value;
    } else {
        (*(volatile unsigned int *)
         (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG)) = 0;
    }
}

//------------------------------------------------------------------------------
/// Set DMA configuration registe used by a HDMA channel.
/// \param channel Particular channel number.
/// \param value configuration value.
//------------------------------------------------------------------------------
void DMA_SetConfiguration(unsigned char channel, unsigned int value)
{
    (*(volatile unsigned int *)(AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CFG))
        = value;
}

#if defined(AT91C_SRC_PIP)
//------------------------------------------------------------------------------
/// Set DMA source PIP configuration used by a HDMA channel.
/// \param channel Particular channel number.
/// \param pipHole stop on done mode.
/// \param pipBoundary lock mode.
//------------------------------------------------------------------------------
void DMA_SPIPconfiguration(unsigned char channel,
                           unsigned int pipHole, unsigned int pipBoundary)
{
    unsigned int value;

    value = (*(volatile unsigned int *)
             (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB));
    value &= ~(unsigned int)AT91C_SRC_PIP;
    value |= AT91C_SRC_PIP;
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB)) = value;
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_SPIP)) =
        (pipHole + 1) | pipBoundary << 16;
}
#endif

#if defined(AT91C_DST_PIP)
//------------------------------------------------------------------------------
/// Set DMA destination PIP configuration used by a HDMA channel.
/// \param channel Particular channel number.
/// \param pipHole stop on done mode.
/// \param pipBoundary lock mode.
//------------------------------------------------------------------------------
void DMA_DPIPconfiguration(unsigned char channel,
                           unsigned int pipHole, unsigned int pipBoundary)
{
    unsigned int value;

    value = (*(volatile unsigned int *)
             (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB));
    value &= ~(unsigned int)AT91C_DST_PIP;
    value |= AT91C_DST_PIP;
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB)) = value;

    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_DPIP)) =
        (pipHole + 1) | pipBoundary << 16;
}
#endif

//-----------------------------------------------------------------------------
/// Set DMA control B register Flow control bit field.
/// \param channel Particular channel number.
/// \param size Dma transfer size in byte.
/// \param sourceWidth Single transfer width for source.
/// \param destWidth Single transfer width for destination.
/// \param done Transfer done field.
//-----------------------------------------------------------------------------
void DMA_SetFlowControl(unsigned char channel, unsigned int flow)
{
    unsigned int value;

    value = (*(volatile unsigned int *)
             (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB));
    value &= ~(unsigned int)AT91C_FC;
    value |= flow << 21;
    (*(volatile unsigned int *)
     (AT91C_BASE_HDMA_CH_0 + channel * 40 + HDMA_CTRLB)) = value;
}

#endif
