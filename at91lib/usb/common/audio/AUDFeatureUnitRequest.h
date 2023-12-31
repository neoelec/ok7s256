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
///
/// !!!Purpose
///
/// Definitions of constants and methods for using USB %audio requests
/// targetted at a Feature unit.
///
/// !!!Usage
///
/// - For a USB %device:
///     -# Use AUDFeatureUnitRequest_GetControl to determine which control
///        shall be tweaked following a host request.
//      -# Use AUDFeatureUnitRequest_GetChannel to identify the channel which
//         will have its control altered.
//------------------------------------------------------------------------------

#ifndef AUDFEATUREUNITREQUEST_H
#define AUDFEATUREUNITREQUEST_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include <usb/common/core/USBGenericRequest.h>

//------------------------------------------------------------------------------
//         Constants
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "USB Audio Control selector values"
///
/// This page lists the available control selectors for a Feature Unit request.
///
/// !Controls
/// - AUDFeatureUnitRequest_MUTE

/// Mute control selector.
#define AUDFeatureUnitRequest_MUTE              0x01
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------
extern unsigned char AUDFeatureUnitRequest_GetControl(
    const USBGenericRequest *request);
extern unsigned char AUDFeatureUnitRequest_GetChannel(
    const USBGenericRequest *request);

#endif //#ifndef AUDFEATUREUNITREQUEST_H

