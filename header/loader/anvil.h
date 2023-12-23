#pragma once
#include <string>

#include "loader/misc.h"
#include "loader/chunk.h"

struct Anvil {
	Chunk chunk[32][32];

	Anvil(std::string location);
	/**
	* Get the information of a block in the anvil.
	*
	* @param x - x towards the anvil
	* @param y - y
	* @param z - z towards the anvil
	* @return a pointer to Compound of the block.
	 */
	Compound* query(int x, int y, int z);
};