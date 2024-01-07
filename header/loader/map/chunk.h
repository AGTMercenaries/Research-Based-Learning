#pragma once

#include "loader/utils/misc.h"
#include "loader/utils/nbt.h"

struct Chunk {
	pNBT data = nullptr;
	List* sections = nullptr;

	Chunk() = delete;
	Chunk(std::unique_ptr<u8[]> rawData, u32 rawLen);

	// worked by Zaunese
	/**
	* Get the information of a block in the chunk.
	* 
	* @param x - x towards the chunk
	* @param y - y
	* @param z - z towards the chunk
	* @return a pointer to Compound of the block.
	 */
	Compound* query(int x, int y, int z) const;
};