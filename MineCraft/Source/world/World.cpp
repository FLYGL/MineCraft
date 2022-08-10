#include "World.h"
#include "../Renderer/RenderMaster.h"
#include "../Maths/Vector2XZ.h"

namespace
{
	constexpr int temp_worldSize = 32;
	VectorXZ getBlockXZ(int x, int z)
	{
		return {
			x % CHUNK_SIZE,
			z % CHUNK_SIZE
		};
	}
	VectorXZ getChunkXZ(int x, int z)
	{
		return
		{
			 x / CHUNK_SIZE,
			 z / CHUNK_SIZE
		};
	}
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
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	if (isOutOfBounds(cp))
	{
		return false;
	}
	auto chunk = m_chunkManager.getChunk(cp.x, cp.z);
	bool success = chunk->setBlock(bp.x, y, bp.z, block);
	if (chunk->hashLoaded() && success)
	{
		m_rebuildChunks.emplace(cp.x, y / CHUNK_SIZE, cp.z);
	}
	return success;
}

ChunkBlock World::getBlock(int x, int y, int z)
{
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	if (isOutOfBounds(cp))
	{
		return BlockId::Air;
	}
	return m_chunkManager.getChunk(cp.x,cp.z)->getBlock(bp.x, y, bp.z);
}

void World::update(const Camera& camera)
{
	for (int x = 0; x < temp_worldSize; x++)
	{
		for (int z = 0; z < temp_worldSize; z++)
		{
			if (m_chunkManager.makeMesh(x, z)) return;
		}
	}
}

void World::renderWorld(RenderMaster& renderer)
{
	for (auto& location : m_rebuildChunks)
	{
		ChunkSection& section = m_chunkManager.getChunk(location.x, location.z)->getSection(location.y);
		section.makeMesh();
	}
	m_rebuildChunks.clear();
	const auto& chunkMap = m_chunkManager.getChunks();
	for (const auto& chunk : chunkMap)
	{
		chunk.second.drawChunks(renderer);
	}
}
