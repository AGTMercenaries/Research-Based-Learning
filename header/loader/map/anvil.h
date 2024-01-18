#pragma once

#include "loader/utils/misc.h"
#include "loader/map/chunk.h"
#include "resource.h"

#include <string>
#include <memory>
#include <utility>


struct Anvil {
	std::unique_ptr<u8[]> offset = nullptr;
	Binary data;

	Anvil(std::string location);
	std::pair<std::unique_ptr<u8[]>, u32> getChunkData(int x, int z);
};