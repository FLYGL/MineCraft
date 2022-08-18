#pragma once

#include "../../Util/Array2D.h"
#include "../../Maths/NoiseGenerator.h"
#include "../WorldConstants.h"
#include "../../Util/Random.h"
#include "GrasslandBiome.h"
#include "TemperateForestBiome.h"
#include "DesertBiome.h"

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

	const Biome& getBiome(int x, int z) const;

	static void setUpNoise();
	static NoiseGenerator m_heightNoiseGen;
	static NoiseGenerator m_biomeNoiseGen;

	Chunk* m_pChunk = nullptr;
	Array2D<int, CHUNK_SIZE> m_heightMap;
	Array2D<int, CHUNK_SIZE+1> m_biomeMap;

	GrasslandBiome m_grassBiome;
	TemperateForestBiome m_lightForest;
	DesertBiome m_desertBiome;

	Random<std::minstd_rand> m_random;
};