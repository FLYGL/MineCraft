#include "ChunkManager.h"

ChunkManager::ChunkManager(World& world):m_world(&world)
{

}

ChunkMap& ChunkManager::getChunks()
{
	return m_chunks;
}
Chunk& ChunkManager::qGetChunk(int x, int z)
{
	VectorXZ key{ x,z };
	return m_chunks.at(key);
}
Chunk& ChunkManager::getChunk(int x, int z)
{
	VectorXZ key{ x,z };
	if (!chunkExistsAt(x,z))
	{
		Chunk chunk{ *m_world, {x, z} };
		m_chunks.emplace(key, std::move(chunk));
	}
	return m_chunks[key];
}

bool ChunkManager::makeMesh(int x, int z)
{
	for (int nx = -1; nx <= 1; nx++)
		for (int nz = -1; nz <= 1; nz++)
		{
			getChunk(x + nz, z + nz).load();
		}
	return getChunk(x, z).makeMesh();
}

bool ChunkManager::chunkLoadedAt(int x, int z) const
{
	if (!chunkExistsAt(x, z))
	{
		return false;
	}
	return m_chunks.at({ x,z }).hashLoaded();
}

bool ChunkManager::chunkExistsAt(int x, int z) const
{
	return m_chunks.find({ x,z }) != m_chunks.end();
}

void ChunkManager::loadChunk(int x, int z)
{
	getChunk(x, z).load();
}

void ChunkManager::unloadChunk(int x, int z)
{
	//getChunk(x,z)
	//TODO
}