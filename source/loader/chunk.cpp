#include "loader/chunk.h"
#include "utils/file.h"

#include <cassert>
#include <iostream>

#include <zlib/zlib.h>

#define BE2LE_32BIT(x) ((x & 0x000000ff) << 24) | ((x & 0x0000ff00) << 8) | ((x & 0x00ff0000) >> 8) | ((x & 0xff000000) >> 24)

static inline u8* undeflate(u8* rawData, u32 rawLen) {
	unsigned long dataLen = rawLen * 50;
	while (true) {
		u8* data = new u8[dataLen];
		auto res = uncompress(data, &dataLen, rawData, rawLen);
		if (res == Z_OK) return data;
		delete[] data;
		dataLen <<= 1;
		if (res == Z_MEM_ERROR) {
			std::cout << "CHUNK_LOADER::memory error" << std::endl;
			assert(false);
		}
		if (res == Z_DATA_ERROR) {
			std::cout << "CHUNK_LOADER::rawData is wrong formatted" << std::endl;
			assert(false);
		}
	}
}

Chunk::Chunk() {}
Chunk::Chunk(u8* rawData) {
	u32 rawLen = *(u32*)rawData;
	rawLen = BE2LE_32BIT(rawLen);
	assert(rawData[4] == 2);
	rawData += 5; // 4 byte :: lenght | 1 byte :: compress method

	auto data = undeflate(rawData, rawLen);


//	std::ofstream ofs(getFullPath("temp\\test.nbt"), std::ios::out | std::ios::binary);
//	ofs.write((char*)data, length);
//	ofs.close();

}