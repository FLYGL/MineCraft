#pragma once

#include "Biome.h"

class GrasslandBiome : public Biome
{
public:
	GrasslandBiome(int seed);
	BlockId getTopBlock(Rand& rand) const;
	void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;
private:
	NoiseParamters getNoiseParameters();
};