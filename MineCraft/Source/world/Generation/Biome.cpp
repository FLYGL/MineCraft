#include "Biome.h"
#include "TreeGenerator.h"

Biome::Biome(const NoiseParamters& params, int treeFreq, int seed):m_heightGenerator(seed),m_treeFreq(treeFreq)
{
	m_heightGenerator.setParameters(params);
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
{
	return (int)m_heightGenerator.getHeight(x, z, chunkX, chunkZ);
}

int Biome::getTreeFrequency() const
{
	return m_treeFreq;
}
