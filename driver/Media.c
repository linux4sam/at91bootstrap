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
//         Headers
//------------------------------------------------------------------------------

#include "Media.h"

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

/// Number of medias which are effectively used.
unsigned int numMedias = 0;

//------------------------------------------------------------------------------
//! \brief  Handle interrupts on specified media
//! \param  pMedia    List of media
//! \param  bNumMedia Number of media in list
//! \see    S_media
//------------------------------------------------------------------------------
#if 0
void MED_HandleAll(Media * pMedia, unsigned char bNumMedia)
{
    // Check each media for interrupts to handle
    unsigned int i;

    for (i = 0; i < bNumMedia; i++) {

        MED_Handler(&(pMedia[i]));
    }
}
#endif

//! \brief  Writes data on a media
//! \param  media    Pointer to a Media instance
//! \param  address  Address at which to write
//! \param  data     Pointer to the data to write
//! \param  length   Size of the data buffer
//! \param  callback Optional pointer to a callback function to invoke when
//!                   the write operation terminates
//! \param  argument Optional argument for the callback function
//! \return Operation result code
//! \see    TransferCallback
//------------------------------------------------------------------------------
unsigned char MED_Write(Media * media,
                        unsigned int address,
                        void *data,
                        unsigned int length,
                        MediaCallback callback, void *argument)
{
    return media->write(media, address, data, length, callback, argument);
}

//------------------------------------------------------------------------------
//! \brief  Reads a specified amount of data from a media
//! \param  media    Pointer to a Media instance
//! \param  address  Address of the data to read
//! \param  data     Pointer to the buffer in which to store the retrieved
//!                   data
//! \param  length   Length of the buffer
//! \param  callback Optional pointer to a callback function to invoke when
//!                   the operation is finished
//! \param  argument Optional pointer to an argument for the callback
//! \return Operation result code
//! \see    TransferCallback
//------------------------------------------------------------------------------
unsigned char MED_Read(Media * media,
                       unsigned int address,
                       void *data,
                       unsigned int length,
                       MediaCallback callback, void *argument)
{
    return media->read(media, address, data, length, callback, argument);
}

//------------------------------------------------------------------------------
//! \brief  Locks all the regions in the given address range.
//! \param  media    Pointer to a Media instance
/// \param  start  Start address of lock range.
/// \param  end  End address of lock range.
/// \param  pActualStart  Start address of the actual lock range (optional).
/// \param  pActualEnd  End address of the actual lock range (optional).
/// \return 0 if successful; otherwise returns an error code.
//------------------------------------------------------------------------------
unsigned char MED_Lock(Media * media,
                       unsigned int start,
                       unsigned int end,
                       unsigned int *pActualStart, unsigned int *pActualEnd)
{
    if (media->lock) {
        return media->lock(media, start, end, pActualStart, pActualEnd);
    } else {
        return MED_STATUS_SUCCESS;
    }
}

//------------------------------------------------------------------------------
//! \brief  Unlocks all the regions in the given address range
//! \param  media    Pointer to a Media instance
/// \param start  Start address of unlock range.
/// \param end  End address of unlock range.
/// \param pActualStart  Start address of the actual unlock range (optional).
/// \param pActualEnd  End address of the actual unlock range (optional).
/// \return 0 if successful; otherwise returns an error code.
//------------------------------------------------------------------------------
unsigned char MED_Unlock(Media * media,
                         unsigned int start,
                         unsigned int end,
                         unsigned int *pActualStart, unsigned int *pActualEnd)
{
    if (media->unlock) {
        return media->unlock(media, start, end, pActualStart, pActualEnd);
    } else {
        return MED_STATUS_SUCCESS;
    }
}

//------------------------------------------------------------------------------
//! \brief  
//! \param  media Pointer to the Media instance to use
//------------------------------------------------------------------------------
unsigned char MED_Flush(Media * media)
{
    if (media->flush) {

        return media->flush(media);
    } else {

        return MED_STATUS_SUCCESS;
    }
}

//------------------------------------------------------------------------------
//! \brief  Invokes the interrupt handler of the specified media
//! \param  media Pointer to the Media instance to use
//------------------------------------------------------------------------------
void MED_Handler(Media * media)
{
    if (media->handler) {

        media->handler(media);
    }
}
