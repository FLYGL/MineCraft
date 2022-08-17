#include "TerrainGenerator.h"
#include <functional>
#include <iostream>

#include "../Chunk/Chunk.h"
#include "../../Util/Random.h"
#include "TreeGenerator.h"

namespace
{
	int seed = 50424;
}

NoiseGenerator TerrainGenerator::m_heightNoiseGen(seed);
NoiseGenerator TerrainGenerator::m_biomeNoiseGen(seed * 2);

TerrainGenerator::TerrainGenerator()
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
		NoiseParamters  heightParams;
		heightParams.octaves = 7;
		heightParams.amplitude = 70;
		heightParams.smoothness = 235;
		heightParams.heightOffset = -5;
		heightParams.roughness = 0.53;

		NoiseParamters biomePararms;
		biomePararms.octaves = 5;
		biomePararms.amplitude = 90;
		biomePararms.smoothness = 735;
		biomePararms.heightOffset = -5;
		biomePararms.roughness = 0.6;

		m_heightNoiseGen.setParameters(heightParams);
		m_biomeNoiseGen.setParameters(biomePararms);
	}
}

void TerrainGenerator::generateTerrainFor(Chunk& chunk)
{
	m_pChunk = &chunk;
	auto location = chunk.getLocation();
	m_random.setSeed((location.x ^ location.y) << 2);
	getHeightMap();
	getBiomeMap();
	setBlocks();
}

void TerrainGenerator::getHeightMap()
{
	std::array<int, CHUNK_AREA> arr;
	auto location = m_pChunk->getLocation();
	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int h =(int) m_heightNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
			arr[x * CHUNK_SIZE + z] = h;
		}
	}
	m_heightMap = std::move( arr);
}

void TerrainGenerator::getBiomeMap()
{
	std::array<int, CHUNK_AREA> arr;
	auto location = m_pChunk->getLocation();

	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int h =(int) m_biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
			arr[x * CHUNK_SIZE + z] = h;
		}
	m_biomeMap =  std::move(arr);
}

void TerrainGenerator::setBlocks()
{
	std::vector<sf::Vector3i> trees;
	for (int x = 0; x < CHUNK_SIZE; x++)
		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			int h = m_heightMap[x * CHUNK_SIZE + z];
			int biome = m_biomeMap[x * CHUNK_SIZE + z];

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
				if (m_random.intInRange(0, 200) == 99) trees.emplace_back(x, h, z);
				setTopBlock(x,h,z);
			}
			else m_pChunk->setBlock(x, h, z, m_random.intInRange(0,10)<5? BlockId::Dirt:BlockId::Sand);
		}
	for (auto& tree : trees)
	{
		makeOakTree(*m_pChunk, m_random, tree.x, tree.y, tree.z);
	}
}

void TerrainGenerator::setTopBlock(int x, int y, int z)
{
	int biome = m_biomeMap[x * CHUNK_SIZE + z];

	if (biome < 100)
	{
		m_pChunk->setBlock(x, y, z, BlockId::Grass);
	}
	else
	{
		m_pChunk->setBlock(x, y, z, BlockId::Sand);
	}
}
