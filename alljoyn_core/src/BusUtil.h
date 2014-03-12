#ifndef _ALLJOYN_BUSUTIL_H
#define _ALLJOYN_BUSUTIL_H
/**
 * @file
 *
 * This file defines a namespace for utility functions
 *
 */

/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef __cplusplus
#error Only include BusUtil.h in C++ code.
#endif

#include <qcc/platform.h>
#include <qcc/String.h>

#include <alljoyn/Status.h>

namespace ajn {
/**
 * Checks if the string passed is a well-formed unique name.
 *
 * A well-formed unique name means it begins with a @c ':' and has
 * the form @c i.j[.k]* where  <tt> i, j, k </tt> are integers.
 * Unique names are nul terminated and have a maximum length of 255
 * characters not including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed unique name
 */
bool IsLegalUniqueName(const char* str);

/**
 * Checks if the string passed is a well-formed bus name.
 *
 * A well-formed bus name means it is either a legal unique name or a series of alphanumeric
 * characters, underscores, and hyphens separated by period characters.  A bus name must have
 * at least one period character and cannot start with a period character. Bus names are nul
 * terminated and have a maximum length of 255 characters not including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed bus name
 */
bool IsLegalBusName(const char* str);

/**
 * Checks if the string passed is a well-formed object path.
 *
 * An object path is sequences of alphanumeric characters and underscores separated by
 * forward slashes ('/'). The first character must be a forward slash, the last character
 * cannot be a forward slash unless the entire path is a single forward slash (denoting the root object).
 * Object paths are nul terminated and unlike other names have no length limit.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed object path
 */
bool IsLegalObjectPath(const char* str);

/**
 * Checks if the string passed is a well-formed interface name.
 *
 * An interface name is sequences of alphanumeric characters and underscores separated by
 * period characters. An interface name must have at least one period character and cannot
 * start with a period character. They are nul terminated and have a maximum length of 255
 * characters not including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed interface name
 */
bool IsLegalInterfaceName(const char* str);

/**
 * Checks if the string passed is a well-formed error name.
 *
 * An error name has the same format as an interface name.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed error name
 *
 * @see IsLegalInterfaceName
 */
bool IsLegalErrorName(const char* str);

/**
 * Checks if the string passed is a well-formed member name.
 *
 * Member names contain only alphanumeric characters and underscores and must not begin
 * with a digit. They are nul terminated and have a maximum length of 255 characters not
 * including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed member name
 */
bool IsLegalMemberName(const char* str);

/**
 * Generate a well-known bus name from an object path.
 *
 * The well-known name is generated by removing the leading slash and replacing all
 * other slashes by periods. Returns an empty string if the parameter is not a legal
 * object path.
 *
 * For example: @c /org/alljoyn/Bus/Test ---> @c org.alljoyn.Bus.Test
 *
 * @param str  The object path to convert
 *
 * @return A bus name
 */
qcc::String BusNameFromObjPath(const char* str);

}

#endif