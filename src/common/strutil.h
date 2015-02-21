/* xoreos-tools - Tools to help with xoreos development
 *
 * xoreos-tools is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos-tools is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos-tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos-tools. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Utility templates and functions for working with strings.
 */

#ifndef COMMON_STRUTIL_H
#define COMMON_STRUTIL_H

#include "common/types.h"
#include "common/ustring.h"

namespace Common {

class SeekableReadStream;
class MemoryWriteStreamDynamic;

/** Print a quick hex dump of the given data. */
void printDataHex(SeekableReadStream &stream);
/** Print a quick hex dump of the given data. */
void printDataHex(const byte *data, uint32 size);

/** Print a quick dump of the given (text) stream. */
void printStream(SeekableReadStream &stream);
/** Print a quick dump of the given (text) stream. */
void printStream(MemoryWriteStreamDynamic &stream);

} // End of namespace Common

#endif // COMMON_STRUTIL_H
