#include "loader/anvil.h"
#include "utils/file.h"
#include "utils/trans.h"

#include <iostream>
#include <cassert>
#include <fstream>


Anvil::Anvil(std::string location) {
	std::ifstream ifs(getFullPath(location), std::ios::in | std::ios::binary);
	if (!ifs.is_open()) {
		std::cout << "ANVIL_LOADER::unable to open anvil " << location << std::endl;
		assert(false);
	}
	// get the size of file
	ifs.seekg(0, ifs.end);
	size_t fileSize = ifs.tellg();
	ifs.seekg(ifs.beg);

	u8* buf = new u8[fileSize];
	ifs.read((char*)buf, fileSize);
	ifs.close();

	for (int x = 0; x < 32; x++)
		for (int y = 0; y < 32; y++) {
			int p = (x << 5) | y;
			u32 chunkInfo = *(u32*)(buf + p * 4);
			if (chunkInfo != 0) {
				u8* infoPtr = (u8*)&chunkInfo;
				infoPtr[3] = 0; // Useless info : chunk size
				/* Big endian to Little endian */
				chunkInfo = BE2LE_32BIT(chunkInfo);
				size_t chunkOffset = (chunkInfo >> 8) * 4096;
				chunk[x][y] = Chunk(buf + chunkOffset);
			}
		}
	delete[] buf;
}

Compound* Anvil::query(int x, int y, int z) {
	int chunkx, chunkz;
	chunkx = x / 16;
	chunkz = z / 16;
	if (chunkx < 0 || chunkx >= 32 || chunkz < 0 || chunkz >= 32) {
		fprintf(stderr, "x or z exceed the range!");
		assert(false);
	}

	return chunk[chunkz][chunkx].query(x % 16, y, z % 16);
}

