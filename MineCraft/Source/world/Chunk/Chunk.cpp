#include <iostream>
#include "Chunk.h"
#include "../../Renderer/RenderMaster.h"
#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../../Camera.h"
#include "../../Debug/Debug.h"
#include "../Generation/TerrainGenerator.h"

Chunk::Chunk(World& world,const sf::Vector2i& location): m_location(location), m_pWorld(&world)
{
}
bool Chunk::makeMesh()
{
	bool res = false;
	for (auto& chunk : m_chunks)
	{
		if (!chunk.hashMesh())
		{
			chunk.makeMesh();
			res = true;
		}
	}
	return res;
}
bool Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
	// 确保足够的y 高度 有 chunksection
	addSectionBlockTarget(y);
	if (outOfBound(x, y, z))
	{
		return false;
	}
	int bY = y % CHUNK_SIZE;

	return m_chunks[y / CHUNK_SIZE].setBlock(x, bY, z, block);
}
ChunkBlock Chunk::getBlock(int x, int y, int z) const
{
	if (outOfBound(x, y, z)) return BlockId::Air;
	int bY = y % CHUNK_SIZE;
	return m_chunks[y / CHUNK_SIZE].getBlock(x, bY, z);
}

void Chunk::drawChunks(RenderMaster& renderer,const Camera& camera)
{
	for (auto& chunk : m_chunks)
	{
		if (chunk.hashMesh())
		{
			if (!chunk.hashBuffered())
			{
				chunk.bufferMesh();;
			}
			if (camera.getFrustum().isBoxInFrustum(chunk.m_aabb))
			{
				renderer.drawChunk(chunk.m_mesh);
			}
		}
	}
}

bool Chunk::hashLoaded()const
{
	return m_isLoaded;
}

void Chunk::load()
{
	if (hashLoaded()) return;
	TerrainGenerator gen;
	gen.generateTerrainFor(*this);
	m_isLoaded = true;
}

bool Chunk::outOfBound(int x, int y, int z) const noexcept
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;
	if (x < 0 || z < 0 || y < 0) return true;
	if (y >= (int)m_chunks.size() * CHUNK_SIZE) return true;
	return false;
}

ChunkSection& Chunk::getSection(int index)
{
	static ChunkSection errorSection({ 444,444,444 }, *m_pWorld);
	if (index >= (int) m_chunks.size() || index < 0) return errorSection;
	return m_chunks.at(index);
}

void Chunk::addSection()
{
	int y = m_chunks.size();
	m_chunks.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
}

void Chunk::addSectionBlockTarget(int blockY)
{
	int index = blockY / CHUNK_SIZE;
	addSectionIndexTarget(index);
}

void Chunk::addSectionIndexTarget(int index)
{
	while ((int)m_chunks.size() < index + 1)
	{
		addSection();
	}
}

std::vector<ChunkSection>& Chunk::testGetChunks()
{
	return m_chunks;
}

int Chunk::getSectionNumber()
{
	return (int)m_chunks.size();
}