#pragma once
#include <string>

#include "loader/misc.h"
#include "loader/chunk.h"

struct Anvil {
	Chunk chunk[32][32];

	Anvil(std::string location);
};