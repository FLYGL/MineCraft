#pragma once

#include <vector>

#include "ChunkSection.h"

class RenderMaster;

class Chunk : public IChunk
{
public:
	Chunk(World& world,const sf::Vector2i& location);
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;
	void drawChunks(RenderMaster& renderer);
	void makeAllMeshtemp();
private:
	bool outOfBound(int x, int y, int z) const noexcept;
	std::vector<ChunkSection> m_chunks;
	sf::Vector2i m_location;
	World* m_pWorld;
};