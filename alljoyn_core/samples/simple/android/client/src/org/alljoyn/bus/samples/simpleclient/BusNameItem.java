/*
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
*
 */
package org.alljoyn.bus.samples.simpleclient;

public class BusNameItem {

    public BusNameItem(String busName, boolean isFound)
	{
        this.busName = busName;
        this.sessionId = 0;
        this.isFound = isFound;
        uniqueId = (long) busName.hashCode();
    }

    public String getBusName() {
        return busName;
    }

    public boolean isConnected() {
        return (sessionId != 0);
    }

    public int getSessionId() {
        return sessionId;
    }

    public void setSessionId(int sessionId) {
        this.sessionId = sessionId;
    }

    public long getId() {
        return uniqueId;
    }

    public boolean isFound() {
    	return isFound;
    }

    public void setIsFound(boolean isFound) {
    	this.isFound = isFound;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BusNameItem that = (BusNameItem) o;
        return busName != null ? busName.equals(that.busName) : that.busName == null;
    }

    @Override
    public int hashCode() {
        return busName != null ? busName.hashCode() : 0;
    }

    private String busName;
    private int sessionId;
    private boolean isFound;
    private long uniqueId;
}
