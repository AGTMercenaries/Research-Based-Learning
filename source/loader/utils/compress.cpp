#include "loader/utils/compress.h"
#include <zlib/zlib.h>
#include <iostream>
#include <cassert>

u8* undeflate(u8* rawData, u32 rawLen) {
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