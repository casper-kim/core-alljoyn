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

package org.alljoyn.services.common;

/**
 * NOTE: The Common Service classes were incorporated from the now deprecated AJCore About Services project,
 *       so that Config Services no longer depends on alljoyn_about.jar.
 *       This specific class continues to be unnecessary. Remove in release 17.04.
 *
 * An exception that is thrown by the PropertyStore when illegal arguments are given in set/get methods.
 * @see PropertyStore
 * @deprecated see org.alljoyn.bus.ErrorReplyBusException
 */
@Deprecated
public class PropertyStoreException extends Exception {
    private static final long serialVersionUID = -8488311339426012157L;

    /**
     * The given key is not supported
     */
    public final static int UNSUPPORTED_KEY = 0;

    /**
     * The given language is not supported
     */
    public final static int UNSUPPORTED_LANGUAGE = 1;

    /**
     * Trying to set a read-only field
     */
    public final static int ILLEGAL_ACCESS = 2;

    /**
     * Trying to set a field to an invalid
     */
    public final static int INVALID_VALUE = 3;

    private int m_reason;

    @Deprecated
    public PropertyStoreException(int reason)
    {
        m_reason = reason;
    }

    /**
     * The reason for failure
     * @deprecated
     * @return reason for failure
     */
    @Deprecated
    public int getReason()
    {
        return m_reason;
    }
}
