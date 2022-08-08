#include "World.h"

#include "../Renderer/RenderMaster.h"

constexpr int temp_worldSize = 8;

World::World() 
{
	for (int x = 0; x < temp_worldSize; x++)
	{
		for (int z = 0; z < temp_worldSize; z++)
		{
			m_chunks.emplace_back(*this, sf::Vector2i(x, z));
		}
	}
	for (auto& chunk : m_chunks)
	{
		chunk.makeAllMeshtemp();
	}
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
	int bX = x % CHUNK_SIZE;
	int bZ = z % CHUNK_SIZE;
	int cX = x / CHUNK_SIZE;
	int cZ = z / CHUNK_SIZE;

	if (cX < 0 || cZ < 0 || cX >= temp_worldSize || cZ >= temp_worldSize) return;
	m_chunks.at(cX * temp_worldSize + cZ).setBlock(bX, y, bZ, block);
}

void World::editBlock(int x, int y, int z, ChunkBlock block)
{
	int bX = x % CHUNK_SIZE;
	int bZ = z % CHUNK_SIZE;
	int cX = x / CHUNK_SIZE;
	int cZ = z / CHUNK_SIZE;
	if (cX < 0 || cZ < 0 || cX >= temp_worldSize || cZ >= temp_worldSize) return;

	setBlock(x, y, z, block);
	m_chunks.at(cX * temp_worldSize + cZ).makeAllMeshtemp();
}
ChunkBlock World::getBlock(int x, int y, int z) const
{
	int bX = x % CHUNK_SIZE;
	int bZ = z % CHUNK_SIZE;

	int cX = x / CHUNK_SIZE;
	int cZ = z / CHUNK_SIZE;

	if (cX < 0 || cZ < 0 || cX >= temp_worldSize || cZ >= temp_worldSize) return BlockId::Air;

	return m_chunks.at(cX * temp_worldSize + cZ).getBlock(bX, y, bZ);
}

void World::renderWorld(RenderMaster& renderer)
{
	for (auto& chunk : m_chunks)
	{
		chunk.drawChunks(renderer);
	}
}