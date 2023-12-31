#include "loader/map/anvil.h"
#include "loader/utils/trans.h"

#include <iostream>
#include <cassert>
#include <fstream>
#include "resource.h"

Anvil::Anvil(Location loc) {
	Binary data(AnvilFile(loc));
	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 32; y++) {
			int p = (x << 5) | y;
			u32 chunkInfo = *(u32*)(data.data + p * 4);
			if (chunkInfo != 0) {
				u8* infoPtr = (u8*)&chunkInfo;
				infoPtr[3] = 0; // Useless info : chunk size
				/* Big endian to Little endian */
				chunkInfo = BE2LE_32BIT(chunkInfo);
				size_t chunkOffset = (chunkInfo >> 8) * 4096;
				chunk[x][y] = Chunk(data.data + chunkOffset);
			}
		}
}
