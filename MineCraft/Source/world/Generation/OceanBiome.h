#pragma once

#include "Biome.h"

class OceanBiome : public Biome
{
public:
	OceanBiome(int seed);
	BlockId getTopBlock(Rand& rand) const;
	void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;
private:
	NoiseParamters getNoiseParameters() override;
};