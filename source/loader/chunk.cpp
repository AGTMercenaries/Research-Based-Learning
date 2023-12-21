#include "loader/chunk.h"
#include "loader/compress.h"
#include "utils/trans.h"
#include "utils/file.h"

#include <cassert>
#include <iostream>
#include <memory>

Chunk::Chunk() {}
Chunk::Chunk(u8* rawData) {
	u32 rawLen = *(u32*)rawData;
	rawLen = BE2LE_32BIT(rawLen);
	assert(rawData[4] == 2);
	rawData += 5; // 4 byte :: lenght | 1 byte :: compress method

	auto binaryData = undeflate(rawData, rawLen);
	auto ptrData = binaryData;
	data = parseNBT(ptrData);
	delete[] binaryData;
}

void Chunk::debug() {
	auto root = dynamic_cast<Compound*>(data.get());
	auto level = dynamic_cast<Compound*>(root->val["Level"].get());
	auto sections = dynamic_cast<List*>(level->val["Sections"].get());
	sections->print();
}