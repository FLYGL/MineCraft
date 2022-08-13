#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "../../Maths/Vector2XZ.h"
#include "Chunk.h"

class World;

using ChunkMap = std::unordered_map<VectorXZ, Chunk>;

class ChunkManager
{
public:
	ChunkManager(World& world);
	Chunk* newChunk(int x, int z);
	Chunk& qGetChunk(int x, int z);
	Chunk& getChunk(int x, int z);
	ChunkMap& getChunks();
	bool makeMesh(int x, int z);
	
	bool chunkLoadedAt(int x, int z) const;
	bool chunkExistsAt(int x, int z) const;
	void loadChunk(int x, int y);
	void unloadChunk(int x, int z);
private:
	ChunkMap m_chunks;
	World* m_world;
};