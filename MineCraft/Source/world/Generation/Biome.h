#pragma once

#include "../../Maths/NoiseGenerator.h"
#include "../../Util/Random.h"
#include "../Block/BlockId.h"

using Rand = Random<std::minstd_rand>;
class Chunk;

struct Biome
{
public:
	Biome(const NoiseParamters& parameters, int treeFreq, int seed) noexcept;
	virtual BlockId getTopBlock(Rand& rand) const = 0;
	virtual void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const = 0;
	int getHeight(int x, int z, int chunkX, int chunkZ) const noexcept;
	int getTreeFrequency() const noexcept;
protected:
	virtual NoiseParamters getNoiseParameters() = 0;
private:
	NoiseGenerator m_heightGenerator;
	int m_treeFreq;
};