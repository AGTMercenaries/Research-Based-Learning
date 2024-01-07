#pragma once

#include "loader/map/chunk.h"
#include "loader/map/anvil.h"

#include <map>
#include <utility>
#include <memory>

struct MapManager {
	using pChunk = std::unique_ptr<Chunk>;
	using pAnvil = std::unique_ptr<Anvil>;
	using Coordinate = std::pair<int, int>;

	std::map<Coordinate, pChunk> chunks;
	std::map<Coordinate, pAnvil> anvils;

	void loadAnvil(int anvilX, int anvilZ);
	void loadChunk(int chunkX, int chunkZ);
	void unloadChunk(int chunkX, int chunkZ);
	
	void updateChunks();
};