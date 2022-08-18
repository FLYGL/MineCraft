#include "Biome.h"
#include "TreeGenerator.h"

Biome::Biome(const NoiseParamters& params, int treeFreq, int seed)noexcept :
	m_heightGenerator(seed),m_treeFreq(treeFreq)
{
	m_heightGenerator.setParameters(params);
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const noexcept
{
	return (int)m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency() const noexcept
{
	return m_treeFreq;
}
