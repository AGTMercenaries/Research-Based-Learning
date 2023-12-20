#pragma once

#include "loader/misc.h"
#include "loader/nbt.h"

struct Chunk {
	pNBT data;

	Chunk(u8* rawData);
	Chunk();
};