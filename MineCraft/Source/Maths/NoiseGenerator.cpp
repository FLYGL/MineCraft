#include "NoiseGenerator.h"
#include "../world/WorldConstants.h"
#include <cmath>

NoiseGenerator::NoiseGenerator(int seed) :m_seed(seed)
{
	m_noiseParameters.octaves = 7;
	m_noiseParameters.amplitude = 70;
	m_noiseParameters.smoothness = 235;
	m_noiseParameters.heightOffset = -5;
	m_noiseParameters.roughness = 0.53;
}

//What means : ????? wtf
double NoiseGenerator::getNoise(int n) const
{
	n += m_seed;
	n = (n << 13) ^ n;
	auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
	return 1.0 - ((double)newN / 1073741824.0);
}

double NoiseGenerator::getNoise(double x, double z) const
{
	return getNoise((int)(x + z * 57.0));
}

double NoiseGenerator::lerp(double a, double b, double z) const
{
	double mu2 = (1 - std::cos(z * 3.14)) / 2;
	return (a * (1 - mu2) + b * mu2);
}

double NoiseGenerator::noise(double x, double z) const
{
	auto floorX = (double)((int)x);
	auto floorZ = (double)((int)x);
	auto s = 0.0, t = 0.0, u = 0.0, v = 0.0;
	s = getNoise(floorX, floorZ);
	t = getNoise(floorX + 1, floorZ);
	u = getNoise(floorX, floorZ + 1);
	v = getNoise(floorX + 1, floorZ + 1);
	auto rec1 = lerp(s, t, x - floorX);
	auto rec2 = lerp(u, v, x - floorX);
	auto rec3 = lerp(rec1, rec2, z - floorZ);
	return rec3;
}

double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ)const
{
	auto newX = (x + (chunkX * CHUNK_SIZE));
	auto newZ = (z + (chunkZ * CHUNK_SIZE));
	if (newX < 0 || newZ < 0)
	{
		return WATER_LEVEL - 1;
	}
	auto totalValue = 0.0;
	for (auto a = 0; a < m_noiseParameters.octaves - 1; a++)
	{
		auto frequency = pow(2.0, a);
		auto amplitude = pow(m_noiseParameters.roughness, a);
		totalValue += noise(((double)newX) * frequency / m_noiseParameters.smoothness,
			((double)newZ) * frequency / m_noiseParameters.smoothness)
			* amplitude;
	}

	auto val =
		(((totalValue / 2.1) + 1.2) * m_noiseParameters.amplitude) + m_noiseParameters.heightOffset;
	return val > 0 ? val : 1;
}

void NoiseGenerator::setParameters(const NoiseParamters& pararms)
{
	m_noiseParameters = pararms;
}