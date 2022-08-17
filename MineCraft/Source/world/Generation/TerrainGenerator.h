#pragma once

#include <array>

#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"
#include "../../Util/Random.h"

class Chunk;
class TerrainGenerator
{
public:
	TerrainGenerator();
	void generateTerrainFor(Chunk& chunk);
private:

	void setBlocks();
	void setTopBlock(int x, int y, int z);

	void  getHeightMap();
	void getBiomeMap();

	static void setUpNoise();
	static NoiseGenerator m_heightNoiseGen;
	static NoiseGenerator m_biomeNoiseGen;

	Chunk* m_pChunk = nullptr;
	std::array<int, CHUNK_AREA> m_heightMap;
	std::array<int, CHUNK_AREA> m_biomeMap;

	Random<std::minstd_rand> m_random;
};