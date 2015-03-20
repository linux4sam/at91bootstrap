/*
 * @file at91_dma.h
 * @breif this file contains the DMA centric stuff (cstes, structures definitions)
 *  Created on: 21 juin 2013
 *      Author: eric based on ATMEL source code, see below.
 */

/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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
#ifndef AT91_DMA_H_
#define AT91_DMA_H_

/** \file */

/** \addtogroup dmac_module Working with DMAC
 *
 * \section Usage
 * <ul>
 * <li> Enable or disable the a DMAC controller with DMAC_Enable() and or DMAC_Disable().</li>
 * <li> Enable or disable %Dma interrupt using DMAC_EnableIt()or DMAC_DisableIt().</li>
 * <li> Get %Dma interrupt status by DMAC_GetStatus() and DMAC_GetInterruptMask().</li>
 * <li> Enable or disable specified %Dma channel with DMAC_EnableChannel() or DMAC_DisableChannel().</li>
 * <li> Get %Dma channel status by DMAC_GetChannelStatus().</li>
 * <li> ControlA and ControlB register is set by DMAC_SetControlA() and DMAC_SetControlB().</li>
 * <li> Configure source and/or destination start address with DMAC_SetSourceAddr() and/or DMAC_SetDestinationAddr().</li>
 * <li> Set %Dma descriptor address using DMAC_SetDescriptorAddr().</li>
 * <li> Set source transfer buffer size with DMAC_SetBufferSize().</li>
 * <li> Configure source and/or destination Picture-In-Picutre mode with DMAC_SetSourcePip() and/or DMAC_SetDestPip().</li>
 * </ul>
 *
 * For more accurate information, please look at the DMAC section of the
 * Datasheet.
 *
 * \sa \ref dmad_module
 *
 * Related files :\n
 * \ref dmac.c\n
 * \ref dmac.h.\n
 *
 */

/**@{*/

/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "dma_component.h"

/*------------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

/** \addtogroup dmac_defines DMAC Definitions
 *      @{
 */
/** Number of DMA channels */
#define DMAC_CHANNEL_NUM          8
/** Max DMA single transfer size */
#define DMAC_MAX_BT_SIZE          0xFFFF
/**     @}*/

/*------------------------------------------------------------------------------
 *         Data structs
 *----------------------------------------------------------------------------*/

/** \addtogroup dmac_struct DMAC Data Structs
 *      @{
 */
/** DMA Transfer Descriptor as well as Linked List Item */
typedef struct _DmaTransferDescriptor {
    unsigned int dwSrcAddr;     /**< Source buffer address */
    unsigned int dwDstAddr;     /**< Destination buffer address */
    unsigned int dwCtrlA;       /**< Control A register settings */
    unsigned int dwCtrlB;       /**< Control B register settings */
    unsigned int dwDscAddr;     /**< Next descriptor address */
} sDmaTransferDescriptor;

/** DMA channel control A */
typedef struct _DmaCtrlA {
    unsigned int btSize:16,     /**< Buffer Transfer size */
             scSize:3,      /**< Source Chunk Transfer size */
             reserve1:1,
             dcSize:3,      /**< Destination Chunk Transfer size */
             reserve2:1,
             srcWidth:2,    /**< Source width */
             reserve3:2,
             dstWidth:2,    /**< Destination width */
             reserve4:1,
             done:1;        /**< The transfer is done */
} sDmaCtrlA;

/** DMA channel control B */
typedef struct _DmaCtrlB {
    unsigned int sIf:2,         /**< Source Interface Selection Field */
             reserve1:2,
             dIf:2,         /**< Destination Interface Selection Field */
             reserve2:2,
             srcPip:1,      /**< Source Picture-in-picture mode enable */
             reserve3:3,
             dstPip:1,      /**< Destination Picture-in-picture mode enable */
             reserve4:3,
             srcDscr:1,     /**< Source Descriptor disabled */
             reserve5:3,
             dstDscr:1,     /**< Destination Descriptor disabled */
             fc:3,          /**< Flow Controller */
             srcIncr:2,     /**< Source Fixed/Dec/Inc setting */
             reserve6,
             dstIncr:2,     /**< Destination Fixed/Dec/Inc setting */
             iEn:1,         /**< Active low to enable interrupt */
             autoEn:1;      /**< Automatic multiple buffer transfer */
} sDmaCtrlB;

/** DMA channel Picture-In-Picture */
typedef struct _DmaPip {
    unsigned int pipHole:16,    /**< Hole size */
             pipBoundary:10,/**< Number of transfers to perform before
                                 hole increse */
             reserve:6;
} sDmaPIP;
/**         @}*/




/*------------------------------------------------------------------------------
 *         Global functions
 *------------------------------------------------------------------------------*/
/** \addtogroup dmac_functions
 *      @{
 */

#ifdef __cplusplus
 extern "C" {
#endif

extern void DMAC_Modified_Arbiter( Dmac *pDmac);
extern void DMAC_Enable( Dmac *pDmac );
extern void DMAC_Disable( Dmac *pDmac );
extern void DMAC_EnableIt (Dmac *pDmac, unsigned int dwInteruptMask );
extern void DMAC_DisableIt (Dmac *pDmac, unsigned int dwInteruptMask );
extern unsigned int DMAC_GetInterruptMask( Dmac *pDmac );
extern unsigned int DMAC_GetStatus( Dmac *pDmac );
extern unsigned int DMAC_GetMaskedStatus( Dmac *pDmac );
extern void DMAC_EnableChannel( Dmac *pDmac, unsigned char channel );
extern void DMAC_EnableChannels( Dmac *pDmac, unsigned char bmChannels );
extern void DMAC_DisableChannel( Dmac *pDmac, unsigned char channel );
extern void DMAC_DisableChannels( Dmac *pDmac, unsigned char bmChannels );
extern void DMAC_SuspendChannel( Dmac *pDmac, unsigned char channel );
extern void DMAC_KeepChannel( Dmac *pDmac, unsigned char channel );
extern void DMAC_RestoreChannel( Dmac *pDmac, unsigned char channel );
extern unsigned int DMAC_GetChannelStatus( Dmac *pDmac );
extern void DMAC_SetSourceAddr( Dmac *pDmac,
                                unsigned char channel,
                                unsigned int saddr );
extern unsigned int DMAC_GetSourceAddr( Dmac * pDmac,
                                unsigned char channel );
extern void DMAC_SetDestinationAddr( Dmac *pDmac,
                                     unsigned char channel,
                                     unsigned int daddr );
extern unsigned int DMAC_GetDestinationAddr( Dmac * pDmac,
                                     unsigned char channel );
extern void DMAC_SetDescriptorAddr( Dmac *pDmac,
                                    unsigned char channel,
                                    unsigned int descr,
                                    unsigned char descrif );
extern void DMAC_SetControlA( Dmac *pDmac,
                              unsigned char channel,
                              unsigned int controlA );
extern void DMAC_SetBufferSize( Dmac *pDmac,
                                unsigned char channel,
                                unsigned short int bsize);
extern void DMAC_SetSingleTransferSize ( Dmac *pDmac,
                                         unsigned char channel,
                                         unsigned char srcWidth,
                                         unsigned char dstWidth );
extern void DMAC_SetChunkTransferSize ( Dmac *pDmac,
                                        unsigned char channel,
                                        unsigned char scSize,
                                        unsigned char dcSize);
extern void DMAC_SetControlB( Dmac *pDmac,
                              unsigned char channel,
                              unsigned int controlB );
extern void DMAC_EnableAutoMode( Dmac *pDmac, unsigned char channel );
extern void DMAC_DisableAutoMode( Dmac *pDmac, unsigned char channel );
extern void DMAC_SelectAHBInterface( Dmac *pDmac,
                                     unsigned char channel,
                                     unsigned char srcIf,
                                     unsigned char dstIf );
extern void DMAC_SetPipMode( Dmac *pDmac,
                             unsigned char channel,
                             unsigned char srcPip,
                             unsigned char dstPip );
extern void DMAC_SetDescFetchMode( Dmac *pDmac,
                                   unsigned char channel,
                                   unsigned char srcDscr,
                                   unsigned char dstDscr );
extern void DMAC_SetFlowControl( Dmac *pDmac,
                                 unsigned char channel,
                                 unsigned char flowControl );
extern void DMAC_SetCFG( Dmac *pDmac,
                         unsigned char channel,
                         unsigned int configuration );
extern void DMAC_SetReloadMode( Dmac *pDmac,
                                unsigned char channel,
                                unsigned char srcRep,
                                unsigned char dstRep );
extern void DMAC_SethandshakeInterface( Dmac *pDmac,
                                        unsigned char channel,
                                        unsigned char srcH2sel,
                                        unsigned char dstH2sel );
extern void DMAC_SetSourcePip( Dmac *pDmac,
                               unsigned char channel,
                               unsigned short int pipHole,
                               unsigned short int pipBoundary);
extern void DMAC_SetDestPip( Dmac *pDmac,
                             unsigned char channel,
                             unsigned short int pipHole,
                             unsigned short int pipBoundary);
#ifdef __cplusplus
}
#endif

#endif /* AT91_DMA_H_ */
 /**     @}*/
 /**@}*/
