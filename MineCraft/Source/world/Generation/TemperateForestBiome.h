#pragma once

#include "Biome.h"
class TemperateForestBiome : public Biome
{
public:
	TemperateForestBiome(int seed) noexcept;
	BlockId getTopBlock(Rand& rand) const noexcept;
	void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)const;
private:
	NoiseParamters getNoiseParameters() noexcept override;
};