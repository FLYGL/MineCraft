#include "ChunkManager.h"

ChunkManager::ChunkManager(World& world):m_world(&world)
{

}

const std::unordered_map<VectorXZ, Chunk>& ChunkManager::getChunks()const
{
	return m_chunks;
}

Chunk* ChunkManager::getChunk(int x, int z)
{
	Chunk* res = nullptr;
	if (m_chunks.find({ x,z }) != m_chunks.end())
	{
		VectorXZ key{ x,z };
		res = &m_chunks.at({ x,z });
	}
	else
	{
		res = newChunk(x, z);
	}
	return res;
}
Chunk* ChunkManager::newChunk(int x, int z)
{
	Chunk* res = nullptr;
	if (m_chunks.find({ x,z }) == m_chunks.end())
	{
		VectorXZ key{ x,z };
		Chunk chunk{ *m_world,{x,z} };
		m_chunks.emplace(key, std::move(chunk));
		res = &m_chunks.at(key);
		res->load();
	}
	return res;
}

bool ChunkManager::makeMesh(int x, int z)
{
	Chunk* pChunk = getChunk(x, z);
	if (pChunk)
	{
		return pChunk->makeMesh();
	}
	return false;
}