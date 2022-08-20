#include "GrasslandBiome.h"
#include "TreeGenerator.h"

GrasslandBiome::GrasslandBiome(int seed)noexcept :
	Biome(getNoiseParameters(), 100, seed)
{

}

BlockId GrasslandBiome::getTopBlock(Rand& rand)const noexcept
{
	return BlockId::Grass;
}

void GrasslandBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const
{
	makeOakTree(chunk, rand, x, y, z);
}

NoiseParamters GrasslandBiome::getNoiseParameters() noexcept
{
    NoiseParamters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 85;
    heightParams.smoothness = 235;
    heightParams.heightOffset = -20;
    heightParams.roughness = 0.51;

    return heightParams;
}
