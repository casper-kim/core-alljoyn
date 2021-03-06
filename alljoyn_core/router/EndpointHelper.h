/**
 * @file
 * Helper functions for dealing with endpoints
 */

/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF), AllJoyn Open Source
 *    Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/
#ifndef _ENDPOINT_HELPER_H
#define _ENDPOINT_HELPER_H

#include <qcc/platform.h>

#include "BusEndpoint.h"
#include "RemoteEndpoint.h"
#include "VirtualEndpoint.h"
#include "LocalTransport.h"

namespace ajn {

inline bool operator ==(const BusEndpoint& ep, const VirtualEndpoint& vep) {
    return ep.iden(vep);
}
inline bool operator ==(const VirtualEndpoint& vep, const BusEndpoint& ep) {
    return ep.iden(vep);
}
inline bool operator !=(const BusEndpoint& ep, const VirtualEndpoint& vep) {
    return !ep.iden(vep);
}
inline bool operator !=(const VirtualEndpoint& vep, const BusEndpoint& ep) {
    return !ep.iden(vep);
}

inline bool operator ==(const BusEndpoint& ep, const RemoteEndpoint& rep)  {
    return ep.iden(rep);
}
inline bool operator ==(const RemoteEndpoint& rep, const BusEndpoint& ep)  {
    return ep.iden(rep);
}
inline bool operator !=(const BusEndpoint& ep, const RemoteEndpoint& rep)  {
    return !ep.iden(rep);
}
inline bool operator !=(const RemoteEndpoint& rep, const BusEndpoint& ep)  {
    return !ep.iden(rep);
}

inline bool operator ==(const BusEndpoint& ep, const LocalEndpoint& lep)   {
    return ep.iden(lep);
}
inline bool operator ==(const LocalEndpoint& lep, const BusEndpoint& ep)   {
    return ep.iden(lep);
}
inline bool operator !=(const BusEndpoint& ep, const LocalEndpoint& lep)   {
    return !ep.iden(lep);
}
inline bool operator !=(const LocalEndpoint& lep, const BusEndpoint& ep)   {
    return !ep.iden(lep);
}

}

#endif
