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
 *  Image related utility functions.
 */

#ifndef IMAGES_UTIL_H
#define IMAGES_UTIL_H

#include "src/common/types.h"
#include "src/common/util.h"
#include "src/common/maths.h"

#include "src/images/types.h"

namespace Images {

/** Return the number of bytes per pixel in this format. */
static inline int getBPP(PixelFormat format) {
	switch (format) {
		case kPixelFormatR8G8B8:
		case kPixelFormatB8G8R8:
			return 3;

		case kPixelFormatR8G8B8A8:
		case kPixelFormatB8G8R8A8:
			return 4;

		case kPixelFormatA1R5G5B5:
		case kPixelFormatR5G6B5:
		case kPixelFormatDepth16:
			return 2;

		default:
			return 0;
	}
}

/** Flip an image horizontally. */
static inline void flipHorizontally(byte *data, int width, int height, int bpp) {
	int halfWidth = width / 2;
	int pitch     = bpp * width;

	byte *buffer = new byte[bpp];

	while (height-- > 0) {
		byte *dataStart = data;
		byte *dataEnd   = data + pitch - bpp;

		for (int j = 0; j < halfWidth; j++) {
			memcpy(buffer   , dataStart, bpp);
			memcpy(dataStart, dataEnd  , bpp);
			memcpy(dataEnd  , buffer   , bpp);

			dataStart += bpp;
			dataEnd   -= bpp;
		}

		data += pitch;
	}

	delete[] buffer;
}

/** Flip an image vertically. */
static inline void flipVertically(byte *data, int width, int height, int bpp) {
	int halfHeight = height / 2;
	int pitch      = bpp * width;

	byte *dataStart = data;
	byte *dataEnd   = data + (pitch * height) - pitch;

	byte *buffer = new byte[pitch];

	while (halfHeight--) {
		memcpy(buffer   , dataStart, pitch);
		memcpy(dataStart, dataEnd  , pitch);
		memcpy(dataEnd  , buffer   , pitch);

		dataStart += pitch;
		dataEnd   -= pitch;
	}

	delete[] buffer;
}

/** De-"swizzle" a texture pixel offset. */
static inline uint32 deSwizzleOffset(uint32 x, uint32 y, uint32 width, uint32 height) {
	width  = Common::intLog2(width);
	height = Common::intLog2(height);

	uint32 offset     = 0;
	uint32 shiftCount = 0;

	while (width | height) {
		if (width) {
			offset |= (x & 0x01) << shiftCount;

			x >>= 1;

			shiftCount++;
			width--;
		}

		if (height) {
			offset |= (y & 0x01) << shiftCount;

			y >>= 1;

			shiftCount++;
			height--;
		}
	}

	return offset;
}

} // End of namespace Images

#endif // IMAGES_UTIL_H