/**
 * @file spi_flash_dma.c
 * @brief This file contains the SPI Flash access with DMA help.
 *
 *  Created on: 21 juin 2013
 *      Author: eric
 */
/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, HAGER Security
 * Copyright (c) 2012, ATMEL
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
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY HAGER Security / ATMEL "AS IS" AND
 * ANY EXPRESS OR
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

#include <stdbool.h>
#include "hardware.h"
#include "dma_hardware_interface.h"
#include "dma_dev.h"
#include "arch/at91_spi.h"
#include "spi.h"
#include "dmad.h"
#include "gpio.h"
#include "usart.h"
#include "debug.h"

//! DMA_DEV_WITH_DMA_IRQ Will be set when IRQ support will be needed and set (IRQ stack in startup code)
#define NO_DMA_DEV_WITH_DMA_IRQ

//***********************************************************
/** Global DMA driver for all transfer */
static sDmad dmad;

//! Driver initialization flag.
static bool IsDriverInitDone = false;

#ifdef DMA_DEV_WITH_DMA_IRQ
//! Last Rx operation DMA status
static eDmadRC sRxLastStatus;

//! Last Tx operation DMA status
static eDmadRC sTxLastStatus;

/** reception done flag*/
//TODO : check the flag is only set when everything is done (even on multi-transfers conditions)
volatile bool recvDone0 = false;
#endif

#ifdef DMA_DEV_WITH_DMA_IRQ
//************* ISR DEBUG SUPPORT *****
/* The ISR debug pin through PortA pin 0*/
static const uint32_t isrPinId = 0;

/* The rx ISR debug pin through PortA pin 2*/
static const uint32_t rxIsrPinId = 2;

/* The tx ISR debug pin through PortA pin 2*/
static const uint32_t txIsrPinId = 4;
//***********************************************************
/**
 * ISR for DMA interrupt
 */
static void ISR_DMA(void)
  {
    pio_set_value(isrPinId, 0);

    DMAD_Handler(&dmad);

    pio_set_value(isrPinId, 1);
  }
//***********************************************************
/**
 *  \brief Callback function for DMA0 receiving.
 */
static void _DmaRxCallback0( uint32_t dmaStatus, void* arg )
  {
#if defined (CONFIG_WITH_CACHE)
    //Force a cache re-load
    CP15_invalidate_dcache_for_dma((uint32_t)RES_BUFFER, ((uint32_t)RES_BUFFER) + RAM_BUFFER_SIZE);
#endif
    sRxLastStatus = dmaStatus;
    //Set the PIN according to status
    if (dmaStatus == DMAD_OK)
    pio_set_value(rxIsrPinId, 0);
    else
    pio_set_value(rxIsrPinId, 1);
    recvDone0 = true;
  }
//***********************************************************
static void _DmaTxCallback0( uint32_t dmaStatus, void* arg )
  {
#if defined (CONFIG_WITH_CACHE)
    //Force a cache re-load
    CP15_invalidate_dcache_for_dma((uint32_t)CMD_BUFFER, ((uint32_t)(CMD_BUFFER)) + RAM_BUFFER_SIZE);
#endif
    sTxLastStatus = dmaStatus;
    //Set the PIN according to status
    if (dmaStatus == DMAD_OK)
    pio_set_value(txIsrPinId, 0);
    else
    pio_set_value(txIsrPinId, 1);
  }
//***********************************************************
#endif /*DMA_DEV_WITH_DMA_IRQ*/

uint32_t
DMA_DEV_OpenSPIIOStream(DMA_DEV_IOStream_t* const stream, const uint32_t spi_ctrlr_base_addr, const uint32_t spi_id)
{
  uint32_t dwCfg;
  uint8_t iController/*, iChannel*/;
  /* Driver initialization if needed*/
  if (!IsDriverInitDone)
    {

#ifdef DMA_DEV_WITH_DMA_IRQ
      /* Debug Pin set*/
      pio_set_gpio_output(isrPinId,0);
      pio_set_gpio_output(txIsrPinId,0);
      pio_set_gpio_output(rxIsrPinId,0);
#endif /*DMA_DEV_WITH_DMA_IRQ*/

      DMAD_Initialize(&dmad, 0);
      IsDriverInitDone = true;

#ifdef DMA_DEV_WITH_DMA_IRQ
      /* IRQ configure */
      IRQ_ConfigureIT(AT91C_ID_DMAC0, 0, ISR_DMA);
      IRQ_ConfigureIT(AT91C_ID_DMAC1, 0, ISR_DMA);
      IRQ_EnableIT(AT91C_ID_DMAC0);
      IRQ_EnableIT(AT91C_ID_DMAC1);
#endif /*DMA_DEV_WITH_DMA_IRQ*/
    }

  /* Allocate TWO DMA channels for SPI */
  stream->TxChannel = DMAD_AllocateChannel(&dmad, AT91C_ID_MEMORY, spi_id);
  stream->RxChannel = DMAD_AllocateChannel(&dmad, spi_id, AT91C_ID_MEMORY);
  if (stream->TxChannel == DMAD_ALLOC_FAILED || stream->RxChannel == DMAD_ALLOC_FAILED)
    {
      usart_puts("DMA channel allocation error\n");
      return 1;
    }

#ifdef DMA_DEV_WITH_DMA_IRQ
  /* Set RX callback */
  DMAD_SetCallback(&dmad, stream->RxChannel, (DmadTransferCallback)_DmaRxCallback0, 0);
#endif

  /* Configure DMA RX channel */
  iController = (stream->RxChannel >> 8);
  dwCfg = 0 | DMAC_CFG_SRC_PER( DMAIF_Get_ChannelNumber( iController, spi_id, DMAD_TRANSFER_RX ))
      | DMAC_CFG_DST_PER( DMAIF_Get_ChannelNumber( iController, spi_id, DMAD_TRANSFER_RX )) | DMAC_CFG_SRC_H2SEL | DMAC_CFG_SOD
      | DMAC_CFG_FIFOCFG_ALAP_CFG;
  DMAD_PrepareChannel(&dmad, stream->RxChannel, dwCfg);
  /* Configure DMA TX channel */
  iController = (stream->TxChannel >> 8);
  dwCfg = 0 | DMAC_CFG_SRC_PER( DMAIF_Get_ChannelNumber( iController, spi_id, DMAD_TRANSFER_TX ))
      | DMAC_CFG_DST_PER( DMAIF_Get_ChannelNumber( iController, spi_id, DMAD_TRANSFER_TX )) | DMAC_CFG_DST_H2SEL | DMAC_CFG_SOD
      | DMAC_CFG_FIFOCFG_ALAP_CFG;
  DMAD_PrepareChannel(&dmad, stream->TxChannel, dwCfg);
#ifdef DMA_DEV_WITH_DMA_IRQ
  //TX Callback
  DMAD_SetCallback(&dmad, stream->TxChannel, (DmadTransferCallback)_DmaTxCallback0, 0);
#else
  dmad.pollingMode = 1;
#endif
  stream->spi_ctrlr_base_addr = spi_ctrlr_base_addr;
  return 0;
}
//*******************************************************************
void
DMA_DEV_CloseSPIIOStream(DMA_DEV_IOStream_t* const stream)
{
  DMAD_StopTransfer(&dmad, stream->RxChannel);
  DMAD_FreeChannel(&dmad, stream->RxChannel);

  DMAD_StopTransfer(&dmad, stream->TxChannel);
  DMAD_FreeChannel(&dmad, stream->TxChannel);
}
//*******************************************************************
uint32_t
DMA_DEV_SPICommandResponse(const DMA_DEV_IOStream_t* const stream, void* toSend, const uint32_t sendLength, void* toRecv,
    const uint32_t recvLength)
{
  /** Dual transfer descriptors : an array with
   * - [0] : Command phase
   * - [1] : Response phase
   * On for each way (Send / Receive).
   */
  sDmaTransferDescriptor tdSendStream[2];
  sDmaTransferDescriptor tdReceiveStream[2];

  uint8_t junkByte = 0; //Used to handle the unused send/received byte in inactive phase of each transfer.

#ifdef DMA_DEV_WITH_DMA_IRQ
  recvDone0 = 0;
#endif
  eDmadRC driverReturnStatus = DMAD_OK;

  //Activate IO sync on SPI
  at91_spi_oisync(1);

  //Force stop transfer on the channel if in use : Not always Ok once actually ended.
  if (DMAD_IsTransferDone(&dmad, stream->TxChannel) != DMAD_OK)
    DMAD_StopTransfer(&dmad, stream->TxChannel);

  if (DMAD_IsTransferDone(&dmad, stream->RxChannel) != DMAD_OK)
    DMAD_StopTransfer(&dmad, stream->RxChannel);

  dbg_log(DEBUG_LOUD,"============= SEND Command ==============\n");
  //First phase : send the command
  tdSendStream[0].dwSrcAddr = (uint32_t) toSend;
  tdSendStream[0].dwDstAddr = stream->spi_ctrlr_base_addr + SPI_TDR;
  tdSendStream[0].dwCtrlA = (sendLength & 0xFFFF) | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
  tdSendStream[0].dwCtrlB = DMAC_CTRLB_SIF_AHB_IF0 | DMAC_CTRLB_DIF_AHB_IF2 | DMAC_CTRLB_FC_MEM2PER_DMA_FC
      | DMAC_CTRLB_SRC_INCR_INCREMENTING | DMAC_CTRLB_DST_INCR_FIXED;
  tdSendStream[0].dwDscAddr = (uint32_t) &tdSendStream[1];

  //First phase : just dump the received byte
  tdReceiveStream[0].dwSrcAddr = stream->spi_ctrlr_base_addr + SPI_RDR;
  tdReceiveStream[0].dwDstAddr = (uint32_t) &junkByte;
  tdReceiveStream[0].dwCtrlA = (sendLength & 0xFFFF) | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
  tdReceiveStream[0].dwCtrlB = DMAC_CTRLB_SIF_AHB_IF2 | DMAC_CTRLB_DIF_AHB_IF0 | DMAC_CTRLB_FC_PER2MEM_DMA_FC
      | DMAC_CTRLB_SRC_INCR_FIXED | DMAC_CTRLB_DST_INCR_FIXED;
  tdReceiveStream[0].dwDscAddr = (uint32_t) &tdReceiveStream[1];

  dbg_log(DEBUG_LOUD,"============= RECEIVE Response ==============\n");
  //Second phase : just drive the bus to get the response.
  tdSendStream[1].dwSrcAddr = (uint32_t) &junkByte;
  tdSendStream[1].dwDstAddr = stream->spi_ctrlr_base_addr + SPI_TDR;
  tdSendStream[1].dwCtrlA = (recvLength & 0xFFFF) | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
  tdSendStream[1].dwCtrlB = DMAC_CTRLB_SIF_AHB_IF0 | DMAC_CTRLB_DIF_AHB_IF2 | DMAC_CTRLB_FC_MEM2PER_DMA_FC
      | DMAC_CTRLB_SRC_INCR_FIXED | DMAC_CTRLB_DST_INCR_FIXED;
  tdSendStream[1].dwDscAddr = 0;

  //Second Phase : Actually receive the data
  tdReceiveStream[1].dwSrcAddr = stream->spi_ctrlr_base_addr + SPI_RDR;
  tdReceiveStream[1].dwDstAddr = (uint32_t) toRecv;
  tdReceiveStream[1].dwCtrlA = (recvLength & 0xFFFF) | DMAC_CTRLA_SRC_WIDTH_BYTE | DMAC_CTRLA_DST_WIDTH_BYTE;
  tdReceiveStream[1].dwCtrlB = DMAC_CTRLB_SIF_AHB_IF2 | DMAC_CTRLB_DIF_AHB_IF0 | DMAC_CTRLB_FC_PER2MEM_DMA_FC
      | DMAC_CTRLB_SRC_INCR_FIXED | DMAC_CTRLB_DST_INCR_INCREMENTING;
  tdReceiveStream[1].dwDscAddr = 0;

  //Prepare the transfers
  driverReturnStatus = DMAD_PrepareMultiTransfer(&dmad, stream->RxChannel, tdReceiveStream);
  dbg_log(DEBUG_VERY_LOUD, "DBG : RX DMAD_PrepareMultiTransfer()=>%d\n", driverReturnStatus);
  if (driverReturnStatus != DMAD_OK)
    {
      goto EXIT_POINT;
    }

  driverReturnStatus = DMAD_PrepareMultiTransfer(&dmad, stream->TxChannel, tdSendStream);
  dbg_log(DEBUG_VERY_LOUD, "DBG:TX : DMAD_PrepareMultiTransfer()=>%d\n",driverReturnStatus);
  if (driverReturnStatus != DMAD_OK)
    {
      goto EXIT_POINT;
    }

  //Start !!
#if defined (CONFIG_WITH_CACHE)
//Flush (clean and invalidate) the cached DMA parameters into the memory for the DMA controller.
  CP15_flush_dcache_for_dma((uint32_t)tdReceiveStream, (uint32_t)tdReceiveStream + 2*sizeof(sDmaTransferDescriptor));
  CP15_flush_dcache_for_dma((uint32_t)tdSendStream, (uint32_t)tdSendStream + 2*sizeof(sDmaTransferDescriptor));
  CP15_flush_dcache_for_dma((uint32_t)toSend, ((uint32_t)(toSend + sendLength)));
  CP15_flush_dcache_for_dma((uint32_t)toRecv, ((uint32_t)(toRecv + recvLength)));
#endif

  driverReturnStatus = DMAD_StartTransfer(&dmad, stream->RxChannel);
  dbg_log(DEBUG_VERY_LOUD, "DBG : RX DMAD_StartTransfer()=>%d\n", driverReturnStatus);
  if (driverReturnStatus != DMAD_OK)
    goto EXIT_POINT;

  driverReturnStatus = DMAD_StartTransfer(&dmad, stream->TxChannel);
  dbg_log(DEBUG_VERY_LOUD, "DBG, TX : DMAD_StartTransfer()=>%d\n", driverReturnStatus);
  if (driverReturnStatus != DMAD_OK)
    {
      DMAD_StopTransfer(&dmad, stream->RxChannel);
      goto EXIT_POINT;
    }
  //Wait the end of the transfer : operation is synchronous. Use RX  && TX (need at91_spi_oisync activated !!)
  while ((driverReturnStatus = DMAD_IsTransferDone(&dmad, stream->TxChannel)) == DMAD_BUSY)
    ;
  while ((driverReturnStatus = DMAD_IsTransferDone(&dmad, stream->RxChannel)) == DMAD_BUSY)
    ;

#if defined (CONFIG_WITH_CACHE)
//Force a fresh copy of the transfered AREA into the cache. note : not actually needed as a flush is done before.
  CP15_invalidate_dcache_for_dma((uint32_t)&tdReceiveStream, (uint32_t)&tdReceiveStream + 2*sizeof(sDmaTransferDescriptor));
  CP15_invalidate_dcache_for_dma((uint32_t)&tdSendStream, (uint32_t)&tdSendStream + 2*sizeof(sDmaTransferDescriptor));
  CP15_invalidate_dcache_for_dma((uint32_t)toSend, ((uint32_t)(toSend + sendLength)));
  CP15_invalidate_dcache_for_dma((uint32_t)toRecv, ((uint32_t)(toRecv + recvLength)));
#endif

  EXIT_POINT: at91_spi_oisync(0);
  return driverReturnStatus;
}
//************************************************************
bool
DMA_DEV_IsTransferInProgress(const DMA_DEV_IOStream_t* const stream)
{
  return !(DMAD_IsTransferDone(&dmad, stream->RxChannel) || DMAD_IsTransferDone(&dmad, stream->TxChannel));
}
//*************************************************************
