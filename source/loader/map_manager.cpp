#include "loader/map_manager.h"
#include "game.h"

#include <string>
#include <format>
#include <vector>
#include <memory>

void MapManager::loadAnvil(int anvilX, int anvilZ) {
	if (anvils.contains({ anvilX, anvilZ })) return;
	auto location = std::format("r.{}.{}", anvilX, anvilZ);
	anvils[{ anvilX, anvilZ }] = pAnvil(new Anvil(location));
}

void MapManager::loadChunk(int chunkX, int chunkZ) {
	if (chunks.contains({ chunkX, chunkZ })) return;
	int anvilX = chunkX >> 5, anvilZ = chunkZ >> 5;
	loadAnvil(anvilX, anvilZ);
	
	auto [rawData, rawLen] = anvils[{ anvilX, anvilZ }]->getChunkData(chunkX & 31, chunkZ & 31);
	chunks[{ chunkX, chunkZ }] = pChunk(new Chunk(std::move(rawData), rawLen));
}
void MapManager::unloadChunk(int chunkX, int chunkZ) {
	chunks.erase({ chunkX, chunkZ });
}

void MapManager::updateChunks() {
	int Px = static_cast<int>(floor(game.cam.pos.x / 16));
	int Pz = static_cast<int>(floor(game.cam.pos.z / 16));

	const int loadDistance = 10;

	for (int x = Px - loadDistance; x <= Px + loadDistance; x++)
		for (int z = Pz - loadDistance; z <= Pz + loadDistance; z++) loadChunk(x, z);

	std::vector<Coordinate> loaded;
	for (auto& [coord, _] : chunks) loaded.push_back(coord);

	for (auto &[x, z] : loaded)
		if (abs(Px - x) > loadDistance || abs(Pz - z) > loadDistance) unloadChunk(x, z);
}
