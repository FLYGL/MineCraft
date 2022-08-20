#include "TemperateForestBiome.h"
#include "TreeGenerator.h"

TemperateForestBiome::TemperateForestBiome(int seed) noexcept :
	Biome(getNoiseParameters(), 55, seed)
{

}

BlockId TemperateForestBiome::getTopBlock(Rand& rand) const noexcept
{
	return rand.intInRange(0,10) < 8 ? BlockId::Grass : BlockId::Dirt;
}

void TemperateForestBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z)const
{
	makeOakTree(chunk, rand, x, y, z);
}

NoiseParamters TemperateForestBiome::getNoiseParameters() noexcept
{
    NoiseParamters heightParams;
    heightParams.octaves = 5;
    heightParams.amplitude = 100;
    heightParams.smoothness = 195;
    heightParams.heightOffset = -30;
    heightParams.roughness = 0.52;

    return heightParams;
}