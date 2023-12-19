#include "loader/chunk.h"
#include "utils/file.h"

#include <fstream>

#define BE2LE_32BIT(x) ((x & 0x000000ff) << 24) | ((x & 0x0000ff00) << 8) | ((x & 0x00ff0000) >> 8) | ((x & 0xff000000) >> 24)

Chunk::Chunk(u8* data) {
	u32 length = *(u32*)data;
	length = BE2LE_32BIT(length);
	data += 5; // 4 byte :: lenght | 1 byte :: compress method

	std::ofstream ofs(getFullPath("temp\\test.nbt"), std::ios::out | std::ios::binary);
	ofs.write((char*)data, length);
	ofs.close();
}