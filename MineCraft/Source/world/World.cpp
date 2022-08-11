#include "World.h"
#include "../Renderer/RenderMaster.h"
#include "../Maths/Vector2XZ.h"

namespace
{
	constexpr int temp_worldSize = 16;
	bool isOutOfBounds(const VectorXZ& chunkPos)
	{
		if (chunkPos.x < 0) return true;
		if (chunkPos.z < 0) return true;
		if (chunkPos.x >= temp_worldSize) return true;
		if (chunkPos.z >= temp_worldSize) return true;
		return false;
	}
}

World::World():m_chunkManager(*this)
{
	
}

bool World::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (y <= 0) return false;
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	if (isOutOfBounds(cp))
	{
		return false;
	}
	return m_chunkManager.getChunk(cp.x, cp.z).setBlock(bp.x, y, bp.z, block);
}

ChunkBlock World::getBlock(int x, int y, int z)
{
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	if (isOutOfBounds(cp))
	{
		return BlockId::Air;
	}
	return m_chunkManager.getChunk(cp.x,cp.z).getBlock(bp.x, y, bp.z);
}

void World::update(const Camera& camera)
{
	for (auto& event : m_events)
	{
		event->handle(*this);
	}
	m_events.clear();
	for (int x = 0; x < temp_worldSize; x++)
	{
		for (int z = 0; z < temp_worldSize; z++)
		{
			if (!m_chunkManager.chunkExistsAt(x, z))
			{
				m_chunkManager.loadChunk(x, z);
			}
			if (m_chunkManager.makeMesh(x, z)) return;
		}
	}
}

void World::renderWorld(RenderMaster& renderer)
{
	//renderer.drawSky();
	auto& chunkMap = m_chunkManager.getChunks();
	for (auto& chunk : chunkMap)
	{
		chunk.second.drawChunks(renderer);
	}
}

const ChunkManager& World::getChunkManager() const
{
	return m_chunkManager;
}

VectorXZ World::getBlockXZ(int x, int z)
{
	x = x % CHUNK_SIZE;
	z = z% CHUNK_SIZE;
	return
	{
			x<0?x+CHUNK_SIZE:x,
			z<0?z+CHUNK_SIZE:z
	};
}

VectorXZ World::getChunkXZ(int x, int z)
{
	x = x < 0 ? (int)std::floor((double)x / (double)CHUNK_SIZE) : x / CHUNK_SIZE;
	z = z < 0 ? (int)std::floor((double)z / (double)CHUNK_SIZE) : z/ CHUNK_SIZE;
	return
	{
		x ,
		z 
	};
}