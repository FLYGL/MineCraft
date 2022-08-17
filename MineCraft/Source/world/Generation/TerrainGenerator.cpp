#include "TerrainGenerator.h"
#include <functional>
#include <iostream>

#include "../Chunk/Chunk.h"
#include "../../Util/Random.h"
#include "TreeGenerator.h"
#include "../../Maths/GeneralMaths.h"

namespace
{
	int seed = RandomSingleton::get().intInRange(424, 325322);
}

NoiseGenerator TerrainGenerator::m_heightNoiseGen(seed);
NoiseGenerator TerrainGenerator::m_biomeNoiseGen(seed * 2);

TerrainGenerator::TerrainGenerator() :
	m_grassBiome(seed),
	m_lightForest(seed),
	m_desertBiome(seed)
{
	setUpNoise();
}

void TerrainGenerator::setUpNoise()
{
	static bool noiseGen = false;
	if (!noiseGen)
	{
		std::cout << "make noise\n";
		noiseGen = true;

		NoiseParamters biomePararms;
		biomePararms.octaves = 5;
		biomePararms.amplitude = 125;
		biomePararms.smoothness = 735;
		biomePararms.heightOffset = -5;
		biomePararms.roughness = 0.6;

		m_biomeNoiseGen.setParameters(biomePararms);
	}
}

void TerrainGenerator::generateTerrainFor(Chunk& chunk)
{
	m_pChunk = &chunk;
	auto location = chunk.getLocation();
	m_random.setSeed((location.x ^ location.y) << 2);
	getBiomeMap();
	getHeightMap();
	setBlocks();
}

void TerrainGenerator::getHeightIn(int xMin, int zMin, int xMax, int zMax)
{
	auto getHeightAt = [&](int x, int z)
	{
		const IBiome& biome = getBiome(x, z);
		return biome.getHeight(x, z, m_pChunk->getLocation().x, m_pChunk->getLocation().y);
	};
	int bottomLeft = getHeightAt(xMin, zMin);
	int bottomRight = getHeightAt(xMax, zMin);
	int topLeft = getHeightAt(xMin, zMax);
	int topRight = getHeightAt(xMax, zMax);
	for(int x = xMin; x<= xMax; x++)
		for (int z = zMin; z <= zMax; z++)
		{
			if (x == CHUNK_SIZE) continue;
			if (z == CHUNK_SIZE) continue;
			int h = (int)billinearInterpolation((float)bottomLeft, (float)topLeft, (float)bottomRight,
				(float)topRight, (float)xMin, (float)xMax, (float)zMin, (float)zMax, (float)x, (float)z);
			m_heightMap[x * CHUNK_SIZE + z] = h;
		}
}

void TerrainGenerator::getHeightMap()
{
	constexpr static auto HALF_CHUNK = CHUNK_SIZE / 2;
	constexpr static auto CHUNK = CHUNK_SIZE;
	getHeightIn(0, 0, HALF_CHUNK, HALF_CHUNK);
	getHeightIn(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
	getHeightIn(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
	getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
}

void TerrainGenerator::getBiomeMap()
{
	auto location = m_pChunk->getLocation();
	for (int x = 0; x < CHUNK_SIZE+1; x++)
		for (int z = 0; z < CHUNK_SIZE+1; z++)
		{
			int h =(int) m_biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
			m_biomeMap[x * CHUNK_SIZE + z] = h;
		}
}

void TerrainGenerator::setBlocks()
{
	std::vector<sf::Vector3i> trees;
	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int h = m_heightMap[x * CHUNK_SIZE + z];
			auto& biome = getBiome(x, z);

			for (int y = 0; y <= WATER_LEVEL && y < h; y++)
			{
				m_pChunk->setBlock(x, y, z, BlockId::Water);
			}
			for (int y = WATER_LEVEL+1; y < h - 3; y++)
			{
				m_pChunk->setBlock(x, y, z, BlockId::Stone);
			}
			for (int y = h - 3; y < h && y > 0; y++)
			{
				m_pChunk->setBlock(x, y, z, BlockId::Dirt);
			}
			if (h >= WATER_LEVEL)
			{
				if (m_random.intInRange(0, biome.getTreeFrequency()) == 5) trees.emplace_back(x, h, z);
				setTopBlock(x,h,z);
			}
			else m_pChunk->setBlock(x, h, z, m_random.intInRange(0,10)<5? BlockId::Dirt:BlockId::Sand);
		}
	for (auto& tree : trees)
	{
		int x = tree.x;
		int z = tree.z;
		getBiome(x, z).makeTree(m_random, *m_pChunk, x, tree.y, z);
	}
}

void TerrainGenerator::setTopBlock(int x, int y, int z)
{
	m_pChunk->setBlock(x, y, z, getBiome(x, z).getTopBlock(m_random));
}

const IBiome& TerrainGenerator::getBiome(int x, int z) const
{
	int biomeValue = m_biomeMap[x * (CHUNK_SIZE+1) + z];
	if (biomeValue > 155) return m_desertBiome;
	if (biomeValue > 135) return m_lightForest;
	return m_grassBiome;
}