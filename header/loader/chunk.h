#pragma once

#include "loader/misc.h"
#include "loader/nbt.h"

struct Chunk {
	pNBT data;

	Chunk(u8* rawData);
	Chunk();
	void debug();
	/**
	* Get the information of a block in the chunk.
	* 
	* @param x - x towards the chunk
	* @param y - y
	* @param z - z towards the chunk
	* @return a pointer to Compound of the block.
	 */
	Compound* query(int x, int y, int z);
};