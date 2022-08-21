#pragma once

#include "Biome.h"

class GrasslandBiome : public Biome
{
public:
	GrasslandBiome(int seed) noexcept;
	BlockId getPlant(Rand& rand) const noexcept override;
	BlockId getTopBlock(Rand& rand) const noexcept;
	void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const;
private:
	NoiseParamters getNoiseParameters() noexcept;
};