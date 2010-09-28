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

//------------------------------------------------------------------------------
/// \unit
/// !Purpose
/// 
/// Generic Media type, which provides transparent access to all types of
/// memories.
///
/// \note The physical or HW related media operations (physical device
///       connection & protection detecting, PIO configurations and interface
///       driver initialization) are excluded.
/// 
/// !Usage
/// -# Do PIO initialization for peripheral interfaces.
/// -# Initialize peripheral interface driver & device driver.
/// -# Initialize specific media interface and link to this initialized driver.
///
//------------------------------------------------------------------------------

#ifndef MEDIA_H
#define MEDIA_H

//------------------------------------------------------------------------------
//      Definitions
//------------------------------------------------------------------------------

//! \brief  Operation result code returned by media methods
#define MED_STATUS_SUCCESS      0x00
#define MED_STATUS_ERROR        0x01
#define MED_STATUS_BUSY         0x02
#define MED_STATUS_PROTECTED    0x04

//! \brief Media statuses
#define MED_STATE_READY         0x00    /// Media is ready for access
#define MED_STATE_BUSY          0x01    /// Media is busy

//------------------------------------------------------------------------------
//      Types
//------------------------------------------------------------------------------
typedef struct _Media Media;

typedef void (*MediaCallback) (void *argument,
                               unsigned char status,
                               unsigned int transferred,
                               unsigned int remaining);

typedef unsigned char (*Media_write) (Media * media,
                                      unsigned int address,
                                      void *data,
                                      unsigned int length,
                                      MediaCallback callback, void *argument);

typedef unsigned char (*Media_read) (Media * media,
                                     unsigned int address,
                                     void *data,
                                     unsigned int length,
                                     MediaCallback callback, void *argument);

typedef unsigned char (*Media_cancelIo) (Media * media);

typedef unsigned char (*Media_lock) (Media * media,
                                     unsigned int start,
                                     unsigned int end,
                                     unsigned int *pActualStart,
                                     unsigned int *pActualEnd);

typedef unsigned char (*Media_unlock) (Media * media,
                                       unsigned int start,
                                       unsigned int end,
                                       unsigned int *pActualStart,
                                       unsigned int *pActualEnd);

typedef unsigned char (*Media_ioctl) (Media * media,
                                      unsigned char ctrl, void *buff);

typedef unsigned char (*Media_flush) (Media * media);

typedef void (*Media_handler) (Media * media);

//! \brief  Media transfer
//! \see    TransferCallback
typedef struct {

    void *data;                 //!< Pointer to the data buffer
    unsigned int address;       //!< Address where to read/write the data
    unsigned int length;        //!< Size of the data to read/write
    MediaCallback callback;     //!< Callback to invoke when the transfer done
    void *argument;             //!< Callback argument

} MEDTransfer;

//! \brief  Media object
//! \see    MEDTransfer
struct _Media {

    Media_write write;          //!< Write method
    Media_read read;            //!< Read method
    Media_cancelIo cancelIo;    //!< Cancel pending IO method
    Media_lock lock;            //!< lock method if possible
    Media_unlock unlock;        //!< unlock method if possible
    Media_flush flush;          //!< Flush method
    Media_handler handler;      //!< Interrupt handler
    unsigned int blockSize;     //!< Block size in bytes (1, 512, 1K, 2K ...)
    unsigned int baseAddress;   //!< Base address of media in number of blocks
    unsigned int size;          //!< Size of media in number of blocks
    MEDTransfer transfer;       //!< Current transfer operation
    void *interface;            //!< Pointer to the physical interface used
    unsigned char bReserved:4, mappedRD:1,      //!< Mapped to memory space to read
     mappedWR:1,                //!< Mapped to memory space to write
     protected:1,               //!< Protected media?
     removable:1;               //!< Removable/Fixed media?
    unsigned char state;        //!< Status of media
    unsigned short reserved;
};

/// Available medias.
extern Media medias[];

/// Number of medias which are effectively used.
/// Defined by Media, shared usage by USB MSD & FS ...
extern unsigned int numMedias;

//------------------------------------------------------------------------------
//      Inline Functions
//------------------------------------------------------------------------------
unsigned char MED_Write(Media * media,
                        unsigned int address,
                        void *data,
                        unsigned int length,
                        MediaCallback callback, void *argument);

unsigned char MED_Read(Media * media,
                       unsigned int address,
                       void *data,
                       unsigned int length,
                       MediaCallback callback, void *argument);

unsigned char MED_Lock(Media * media,
                       unsigned int start,
                       unsigned int end,
                       unsigned int *pActualStart, unsigned int *pActualEnd);

unsigned char MED_Unlock(Media * media,
                         unsigned int start,
                         unsigned int end,
                         unsigned int *pActualStart, unsigned int *pActualEnd);

unsigned char MED_Flush(Media * media);

void MED_Handler(Media * media);

//------------------------------------------------------------------------------
//      Exported functions
//------------------------------------------------------------------------------

extern void MED_HandleAll(Media * medias, unsigned char numMedias);

#endif                          // _MEDIA_H
