#include "loader/chunk.h"
#include "loader/compress.h"
#include "utils/trans.h"
#include "utils/file.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <cmath>

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
	//auto level = dynamic_cast<Compound*>(root->val["Level"].get());
	auto sections = dynamic_cast<List*>(root->val["sections"].get());
	sections->print();
}

Compound* Chunk::query(int x, int y, int z) {
	Compound* blockStates = NULL;
	LongArray* dataArray = NULL;
	List* palette = NULL;
	int dataBit = 0, blockId = 0;
	{
		int id = (y + 64) / 16;
		auto root = dynamic_cast<Compound*>(data.get());
		auto sections = dynamic_cast<List*>(root->val["sections"].get());
		auto sub = dynamic_cast<Compound*>(sections->val[id].get());
		blockStates = dynamic_cast<Compound*>(sub->val["block_states"].get());
		palette = dynamic_cast<List*>(blockStates->val["palette"].get());
		fprintf(stderr, "%d\n", (int) blockStates->val.size());
		dataArray = dynamic_cast<LongArray*>(blockStates->val["data"].get());
		dataBit = ceil(log2((palette->val).size()));
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
	for (int i = 0; i < 64; ++i) fprintf(stderr, "%d", bits[i]);
	fprintf(stderr, "\n");

	int index = 0;
	for (int l = blockId % (64 / dataBit) * dataBit, r = l + dataBit, i = r-1; i >= l; --i)
		index = index << 1 | bits[i];
	if (palette->val.size() <= index) {
		fprintf(stderr, "palette length not enough!\n");
		assert(false);
	}
	return dynamic_cast<Compound*>(palette->val[index].get());
}