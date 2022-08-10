#pragma once

#include <vector>

#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"

class RenderMaster;

class World
{
public:
	World();
	ChunkBlock getBlock(int x, int y, int z) ;
	bool setBlock(int x, int y, int z, ChunkBlock block);
	void renderWorld(RenderMaster& master);
private:
	ChunkManager m_chunkManager;
	std::unordered_set<sf::Vector3i> m_rebuildChunks;
};