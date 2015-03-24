/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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

#ifndef _DMAD_H
#define _DMAD_H

#include "dma_component.h"
/** \addtogroup dmad_module
 *@{
 */

/*----------------------------------------------------------------------------
 *        Includes
 *----------------------------------------------------------------------------*/

#include "arch/at91_dma.h"

/** \addtogroup dmad_defines DMA Driver Defines
        @{*/
/*----------------------------------------------------------------------------
 *        Consts
 *----------------------------------------------------------------------------*/
#define DMAD_TRANSFER_MEMORY  0xFF   /**< DMA transfer from or to memory */
#define DMAD_ALLOC_FAILED     0xFFFF /**< Channel allocate failed */

#define DMAD_TRANSFER_TX      0
#define DMAD_TRANSFER_RX      1
/*----------------------------------------------------------------------------
 *        MACRO
 *----------------------------------------------------------------------------*/

/**     @}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/** \addtogroup dmad_structs DMA Driver Structs
        @{*/
/** DMA status or return code */
typedef enum _DmadStatus {
    DMAD_OK = 0,        /**< Operation is successful */
    DMAD_BUSY,          /**< Channel occupied or transfer not finished */
    DMAD_PARTIAL_DONE,  /**< Partial of LLI finished (on each buffer done) */
    DMAD_ERROR,         /**< Operation failed */
    DMAD_CANCELED       /**< Operation canceled */
} eDmadStatus, eDmadRC;

/** DMA state for channel */
typedef enum _DmadState {
    DMAD_FREE = 0,      /**< Free channel */
    DMAD_IN_USE,        /**< Allocated to some peripheral */
    DMAD_IN_XFR,        /**< Transferring something */
    DMAD_STALL          /**< Error stall */
} eDmadState;

/** DMA transfer callback */
typedef void (*DmadTransferCallback)(unsigned int status, void* pArg);

/** DMA driver channel */
typedef struct _DmadChannel {
    DmadTransferCallback fCallback; /**< Callback */
    void* pArg;                     /**< Callback argument */

    unsigned char bIrqOwner;              /**< Uses DMA handler or external one */
    unsigned char bSrcPeriphID;           /**< HW ID for source */
    unsigned char bDstPeriphID;           /**< HW ID for destination */
    unsigned char bSrcTxIfID;             /**< DMA Tx Interface ID for source */
    unsigned char bSrcRxIfID;             /**< DMA Rx Interface ID for source */
    unsigned char bDstTxIfID;             /**< DMA Tx Interface ID for destination */
    unsigned char bDstRxIfID;             /**< DMA Rx Interface ID for destination */

    volatile unsigned char state;         /**< DMA channel state */
} sDmadChannel;

#if 0
/** DMA driver controller */
typedef struct _DmadController {
    Dmac *pHw;                  /**< Pointer to controler HW base */
    sDmadChannel* dmadChannels; /**< Pointer to driver channels list */
    unsigned char* dmadIfUsage;       /**< AHB Interface usage counting */
    unsigned char  bHwID;             /**< ID for DMAC */
    unsigned char  bNumChannels;      /**< Number of channels for this controller */
    unsigned char  bNumAHBIf;         /**< Number of AHB Interface */
    unsigned char  reserved;
} sDmadController;
#endif

/** DMA driver instance */
typedef struct _Dmad {
    Dmac *pDmacs[2];
    sDmadChannel dmaChannels[2][8];
    unsigned char  numControllers;
    unsigned char  numChannels;
    unsigned char  pollingMode;
    unsigned char  pollingTimeout;
} sDmad;

/** DMA driver channel ID */
typedef struct _DmadChannelID {
    unsigned char bDmac;      /**< DMA Controller number */
    unsigned char bChannel;   /**< Channel number */
} sDmadChannelID;

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/** \addtogroup dmad_functions DMA Driver Functionos
        @{*/
extern void DMAD_Initialize( sDmad *pDmad,
                             unsigned char bPollingMode );

extern void DMAD_Handler( sDmad *pDmad );

extern unsigned int DMAD_AllocateChannel( sDmad *pDmad,
                                      unsigned char bSrcID, unsigned char bDstID);
extern eDmadRC DMAD_FreeChannel( sDmad *pDmad, unsigned int dwChannel );

extern eDmadRC DMAD_SetCallback( sDmad *pDmad, unsigned int dwChannel,
                                  DmadTransferCallback fCallback, void* pArg );

extern eDmadRC DMAD_ConfigurePIP( sDmad *pDmad, unsigned int dwChannel,
                                  unsigned int dwSrcPIP, unsigned int dwDstPIP );

extern eDmadRC DMAD_PrepareChannel( sDmad *pDmad, unsigned int dwChannel,
                                   unsigned int dwCfg );

extern eDmadRC DMAD_IsTransferDone( sDmad *pDmad, unsigned int dwChannel );

extern eDmadRC DMAD_StartTransfer( sDmad *pDmad, unsigned int dwChannel );
extern eDmadRC DMAD_StartTransfers( sDmad *pDmad,
                                    unsigned char bDmac, unsigned int bmChannels );

extern eDmadRC DMAD_StopTransfer( sDmad *pDmad, unsigned int dwChannel );
extern void DMAD_ClearAuto( sDmad *pDmad, unsigned int _dwChannel );
extern eDmadRC DMAD_PrepareSingleTransfer( sDmad *pDmad, unsigned int dwChannel,
                                           sDmaTransferDescriptor *pXfrDesc );

extern eDmadRC DMAD_PrepareMultiTransfer( sDmad *pDmad, unsigned int dwChannel,
                                          sDmaTransferDescriptor *pXfrDesc );
/**     @}*/
/**@}*/
#endif //#ifndef _DMAD_H

