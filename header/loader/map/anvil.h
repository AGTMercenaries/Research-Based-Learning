#pragma once
#include <string>

#include "loader/utils/misc.h"
#include "loader/map/chunk.h"
#include "resource.h"

struct Anvil {
	Chunk chunk[32][32];
	u8 *offset;
	Binary data;

	Anvil(std::string location);
	Chunk &loadChunk(int x, int z);
	void unloadChunk(int x, int z);
	~Anvil();
};