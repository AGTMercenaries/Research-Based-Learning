#include "loader/map/anvil.h"
#include "loader/utils/trans.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include "resource.h"

Anvil::Anvil(Location loc) : data(AnvilFile(loc)) {
	offset = data.getData(0, 4096);
}
Chunk& Anvil::loadChunk(int x, int z) {
	if (chunk[x][z].data) return chunk[x][z];
	int p = (x << 5) | z;
	auto pChunkInfo = data.getData(p * 4, 4);
	u32 chunkInfo = *(u32*)(pChunkInfo);
	delete pChunkInfo;
	if (chunkInfo != 0) {
		u8* infoPtr = (u8*)&chunkInfo;
		infoPtr[3] = 0; // Useless info : chunk size
		/* Big endian to Little endian */
		chunkInfo = BE2LE_32BIT(chunkInfo);
		size_t chunkOffset = (chunkInfo >> 8) * 4096;

		u8 *pRawLen = data.getData(chunkOffset, 4);
		u32 rawLen = *(u32*)pRawLen;
		delete pRawLen;
		rawLen = BE2LE_32BIT(rawLen);
		
		u8* rawData = data.getData(chunkOffset + 5, rawLen); // 4 byte length | 1 byte compress method
		
		chunk[x][z] = Chunk(rawLen, rawData);
		
		delete rawData;
	}
	return chunk[x][z];
}
void Anvil::unloadChunk(int x, int z) {
	chunk[x][z].data.release();
}

Anvil::~Anvil() {
	delete offset;
}