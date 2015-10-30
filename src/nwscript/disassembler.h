/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Disassembling NWScript bytecode.
 */

#ifndef NWSCRIPT_DISASSEMBLER_H
#define NWSCRIPT_DISASSEMBLER_H

#include <vector>

#include "src/common/types.h"

#include "src/aurora/types.h"

namespace Common {
	class SeekableReadStream;
	class WriteStream;
};

namespace NWScript {

class NCSFile;
struct Block;

class Disassembler {
public:
	Disassembler(Common::SeekableReadStream &ncs, Aurora::GameID game = Aurora::kGameIDUnknown);
	Disassembler(NCSFile *ncs);
	~Disassembler();

	/** Perform a deep analysis of the script stack, so that more information is available. */
	void analyzeStack();

	/** Create a full disassembly listing, with addresses and raw bytes. */
	void createListing (Common::WriteStream &out, bool printStack);
	/** Create bare disassembly output, potentially capable of being re-assembled. */
	void createAssembly(Common::WriteStream &out, bool printStack);
	/** Create a graphviz dot file that can be plotted into a control flow graph. */
	void createDot     (Common::WriteStream &out);


private:
	NCSFile *_ncs;


	void writeDotClusteredBlocks(Common::WriteStream &out);
	void writeDotBlocks         (Common::WriteStream &out, const std::vector<const Block *> &blocks);
	void writeDotBlockEdges     (Common::WriteStream &out);
};

} // End of namespace NWScript

#endif // NWSCRIPT_DISASSEMBLER_H