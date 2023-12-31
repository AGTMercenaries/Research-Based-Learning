#include "loader/map/chunk.h"
#include "loader/utils/compress.h"
#include "loader/utils/trans.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <cmath>

Chunk::Chunk() {}
Chunk::Chunk(u32 rawLen, u8* rawData) {
	auto binaryData = undeflate(rawData, rawLen);
	auto ptrData = binaryData;
	data = parseNBT(ptrData);
	delete[] binaryData;
}

void Chunk::debug() {
	auto root = dynamic_cast<Compound*>(data.get());
	auto sections = dynamic_cast<List*>(root->val["sections"].get());
	sections->print();
}

Compound* Chunk::query(int x, int y, int z){
	Compound* blockStates = NULL;
	LongArray* dataArray = NULL;
	List* palette = NULL;
	int dataBit = 0, blockId = 0;
	if (!data) {
		std::cout << "Chunk : query a null chunk" << std::endl;
		assert(false);
	}

	{
		int id = (y + 64) / 16;
		auto root = dynamic_cast<Compound*>(data.get());
		auto sections = dynamic_cast<List*>(root->val["sections"].get());
		auto sub = dynamic_cast<Compound*>(sections->val[id].get());
		blockStates = dynamic_cast<Compound*>(sub->val["block_states"].get());
		palette = dynamic_cast<List*>(blockStates->val["palette"].get());
		dataArray = dynamic_cast<LongArray*>(blockStates->val["data"].get());
		dataBit = static_cast<int>(ceil(log2((palette->val).size())));
	}
	y = (y + 64) % 16;
	blockId = (y << 8 | z << 4 | x);
	if (dataArray->val.size() <= blockId / (64 / dataBit)) {
		fprintf(stderr, "Data array's length not enough!\n");
		assert(false);
	}
	auto sngLong = dataArray->val[blockId/(64 / dataBit)];
	bool bits[64];
	for (int i = 0; i < 8; ++i) {
		u8 revee = sngLong >> (i << 3) & 0xff;
		for (int j = 0; j < 8; ++j) {
			bits[i << 3 | j] = revee & 1;
			revee >>= 1;
		}
	}

	int index = 0;
	for (int l = blockId % (64 / dataBit) * dataBit, r = l + dataBit, i = r-1; i >= l; --i)
		index = index << 1 | (int)bits[i];
	if (palette->val.size() <= index) {
		fprintf(stderr, "palette length not enough!\n");
		assert(false);
	}
	return dynamic_cast<Compound*>(palette->val[index].get());
}