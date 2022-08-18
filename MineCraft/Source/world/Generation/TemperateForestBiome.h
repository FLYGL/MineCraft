#pragma once

#include "Biome.h"
class TemperateForestBiome : public Biome
{
public:
	TemperateForestBiome(int seed);
	BlockId getTopBlock(Rand& rand) const;
	void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)const;
private:
	NoiseParamters getNoiseParameters() override;
};