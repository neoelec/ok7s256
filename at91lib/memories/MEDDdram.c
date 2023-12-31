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

#include "MEDDdram.h"
#include <board.h>
#include <board_memories.h>
#include <utility/trace.h>

#if defined(AT91C_BASE_DDR2C)

//------------------------------------------------------------------------------
//      Internal Functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//! \brief  Reads a specified amount of data from a DDRAM memory
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
static unsigned char MEDDdram_Read(Media         *media,
                                   unsigned int  address,
                                   void          *data,
                                   unsigned int  length,
                                   MediaCallback callback,
                                   void          *argument)
{
    unsigned char *source = (unsigned char *)address;
    unsigned char *dest = (unsigned char *) data;

    // Check that the media is ready
    if (media->state != MED_STATE_READY) {

        TRACE_INFO("Media busy\n\r");
        return MED_STATUS_BUSY;
    }

    // Check that the data to read is not too big
    if ((length + address) > (media->baseAddress + media->size)) {

        TRACE_WARNING("MEDDdram_Read: Data too big: %u, 0x%08X\n\r", length, address);
        return MED_STATUS_ERROR;
    }

    // Enter Busy state
    media->state = MED_STATE_BUSY;

    // Read data
    while (length > 0) {

        *dest = *source;

        dest++;
        source++;
        length--;
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
//! \brief  Writes data on a DDRAM media
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
static unsigned char MEDDdram_Write(Media         *media,
                                    unsigned int  address,
                                    void          *data,
                                    unsigned int  length,
                                    MediaCallback callback,
                                    void          *argument)
{
    unsigned int i;
    unsigned int *source;
    unsigned int *dest;

    //TRACE_DEBUG("MEDDdram_Write\n\r");

    // Check that the media if ready
    if (media->state != MED_STATE_READY) {

        TRACE_WARNING("MEDDdram_Write: Media is busy\n\r");
        return MED_STATUS_BUSY;
    }

    // Check that address is dword-aligned
    if (address%4 != 0) {

        TRACE_WARNING("MEDDdram_Write: Address must be dword-aligned\n\r");
        return MED_STATUS_ERROR;
    }

    // Check that length is a multiple of 4
    if (length%4 != 0) {

        TRACE_WARNING("MEDDdram_Write: Data length must be a multiple of 4 bytes\n\r");
        return MED_STATUS_ERROR;
    }

    // Check that the data to write is not too big
    if ((length + address) > (media->baseAddress + media->size)) {

        TRACE_WARNING("MEDDdram_Write: Data too big\n\r");
        return MED_STATUS_ERROR;
    }

    // Put the media in Busy state
    media->state = MED_STATE_BUSY;

    // Compute function parameters
    // Source address
    source = (unsigned int *) data;

    // Destination address
    dest = (unsigned int *) address;

    // Copy the data to write
    i = 0;
    while (i < length) {

      *dest = *source;

      dest++;
      source++;
      i += 4;
    }

    // Leave the Busy state
    media->state = MED_STATE_READY;

    // Invoke the callback if it exists
    if (callback != 0) {

        callback(argument, MED_STATUS_SUCCESS, 0, 0);
    }

    return MED_STATUS_SUCCESS;
}

//------------------------------------------------------------------------------
//      Exported Functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! \brief  Initializes a Media instance and the associated physical interface
//! \param  media Pointer to the Media instance to initialize
//! \see    Media
//------------------------------------------------------------------------------
void MEDDdram_Initialize(Media *media,
                         unsigned int baseAddress,
                         unsigned int size)
{
    unsigned int value;

    TRACE_INFO("MEDDdram init\n\r");

    // Initialize DDRAM if not already done
    //--------------------------------------------------------------------------
    value = *((volatile unsigned int *) AT91C_DDR2);
    *((volatile unsigned int *) AT91C_DDR2) = 0xDEADBEEF;

    if (*((volatile unsigned int *) AT91C_DDR2) == 0xDEADBEEF) {

        TRACE_INFO("DDRAM already initialized\n\r");
        *((volatile unsigned int *) AT91C_DDR2) = value;
    }
    else {

        TRACE_INFO("Initializing the DDRAM ...\n\r");
        BOARD_ConfigureDdram(0, BOARD_DDRAM_BUSWIDTH); // Micron, 16 bit data bus size
    }

    // Initialize media fields
    //--------------------------------------------------------------------------
    media->write = MEDDdram_Write;
    media->read = MEDDdram_Read;
    media->handler = 0;
    media->flush = 0;
    media->baseAddress = baseAddress;
    media->size = size;
    media->state = MED_STATE_READY;

    media->transfer.data = 0;
    media->transfer.address = 0;
    media->transfer.length = 0;
    media->transfer.callback = 0;
    media->transfer.argument = 0;
}
#endif //#if defined(AT91C_BASE_DDR2C)

