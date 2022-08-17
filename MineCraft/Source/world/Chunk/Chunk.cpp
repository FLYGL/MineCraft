#include <iostream>
#include "Chunk.h"
#include "../../Renderer/RenderMaster.h"
#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../../Camera.h"
#include "../../Debug/Debug.h"
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
	static int seed = RandomSingleton::get().intInRange(444, 4444);
	static Random<std::minstd_rand> rand((m_location.x ^ m_location.y) << 2);
	NoiseGenerator temp_noiseGen(seed);
	std::array<int, CHUNK_AREA> heightMap;
	std::vector<sf::Vector3i> treelocations;

	int maxValue = 0;
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int h = (int)temp_noiseGen.getHeight(x, z, m_location.x + 10, m_location.y + 10);
			heightMap[x * CHUNK_SIZE + z] = h;
			maxValue = std::max(maxValue, h);
		}
	}


	int sectionNumber = maxValue / CHUNK_SIZE + 1;
	int maxHeight = sectionNumber * CHUNK_SIZE;
	for (int y = 0; y < sectionNumber; y++)
	{
		m_chunks.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
	}
	for(int x = 0; x <CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int h = heightMap[x * CHUNK_SIZE + z];
			for (int y = 0; y < h - 3; y++)
			{
				setBlock(x, y, z, BlockId::Stone);
			}
			for (int y = h-3; y < h && y > 0; y++)
			{
				setBlock(x, y, z, BlockId::Dirt);
			}
			if (h > WATER_LEVEL)
			{
				setBlock(x, h, z, BlockId::Grass);
				if (rand.intInRange(0, 100) == 10)
				{
					treelocations.emplace_back(x, h, z);
				}
			}
			else setBlock(x, h, z, BlockId::Dirt);
		}
	for (auto& tree : treelocations)
	{
		int h = rand.intInRange(5, 9);
		//判断完整的树
		if (tree.x < 2 || tree.x > CHUNK_SIZE - 2) continue;
		if (tree.z < 2 || tree.z > CHUNK_SIZE - 2) continue;
		if (maxHeight < tree.y + h + 3) continue;
		for (int y = 0; y < h; y++)
		{
			setBlock(tree.x, tree.y + y, tree.z, BlockId::OakBark);
		}
		for (int x = -2; x < 2; x++)
			for (int z = -2; z < 2; z++)
				for (int y = 0; y < 3; y++)
				{
					setBlock(tree.x + x, tree.y + h + y, tree.z + z, BlockId::OakLeaf);
				}
	}
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