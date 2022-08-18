#pragma once

#include "Biome.h"

class DesertBiome : public Biome
{
public:
	DesertBiome(int seed);
	BlockId getTopBlock(Rand& rand)const;
	void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)const;

private:
	NoiseParamters getNoiseParameters();
};