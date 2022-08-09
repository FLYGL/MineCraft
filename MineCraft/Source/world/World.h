#pragma once

#include <vector>

#include "Chunk/Chunk.h"

class RenderMaster;

class World : IChunk
{
public:
	World();
	ChunkBlock getBlock(int x, int y, int z) const override;
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	void renderWorld(RenderMaster& master);
	void editBlock(int x, int y, int z, ChunkBlock block);
	void AddBlock(int x, int y, int z, ChunkBlock block);
private:
	std::vector<Chunk> m_chunks;
	std::vector<Chunk*> m_changedChunks;
};