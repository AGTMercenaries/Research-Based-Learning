#include "loader/map/anvil.h"
#include "loader/utils/trans.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include "resource.h"

Anvil::Anvil(Location loc) : data(AnvilFile(loc)) {
	if (data.stream.good()) offset = data.getData(0, 4096);
}
std::pair<std::unique_ptr<u8[]>, u32> Anvil::getChunkData(int x, int z) {
	if (!offset) return { nullptr, 0 };

	int p = (x << 5) | z;
	auto pChunkInfo = data.getData(p * 4, 4);
	u32 chunkInfo = *(u32*)(pChunkInfo.get());
	if (chunkInfo != 0) {
		u8* infoPtr = (u8*)&chunkInfo;
		infoPtr[3] = 0; // Useless info : chunk size
		/* Big endian to Little endian */
		chunkInfo = BE2LE_32BIT(chunkInfo);
		size_t chunkOffset = (chunkInfo >> 8) * 4096;

		auto pRawLen = data.getData(chunkOffset, 4);
		u32 rawLen = *(u32*)(pRawLen.get());
		rawLen = BE2LE_32BIT(rawLen);
		
		auto rawData = data.getData(chunkOffset + 5, rawLen); // 4 byte length | 1 byte compress method
		return { std::move(rawData), rawLen};
		
	}
	
	return { nullptr, 0 };
}
