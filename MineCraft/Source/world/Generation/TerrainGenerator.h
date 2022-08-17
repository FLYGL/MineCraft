#pragma once

#include <array>

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"
#include "../../Util/Random.h"
#include "Biome.h"

class Chunk;
class TerrainGenerator
{
public:
	TerrainGenerator();
	void generateTerrainFor(Chunk& chunk);
private:

	void setBlocks();
	void setTopBlock(int x, int y, int z);

	void getHeightIn(int xMin, int zMin, int xMax, int zMax);
	void  getHeightMap();
	void getBiomeMap();

	const IBiome& getBiome(int x, int z) const;

	static void setUpNoise();
	static NoiseGenerator m_heightNoiseGen;
	static NoiseGenerator m_biomeNoiseGen;

	Chunk* m_pChunk = nullptr;
	std::array<int, CHUNK_AREA> m_heightMap;
	std::array<int, (CHUNK_SIZE+1)*(CHUNK_SIZE+1)> m_biomeMap;

	GrasslandBiome m_grassBiome;
	LightForestBiome m_lightForest;
	DesertBiome m_desertBiome;

	Random<std::minstd_rand> m_random;
};