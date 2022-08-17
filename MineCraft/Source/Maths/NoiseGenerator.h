#pragma once

struct NoiseParamters
{
	int octaves;
	int amplitude;
	int smoothness;
	int heightOffset;

	double roughness;
};

class NoiseGenerator
{
public:
	NoiseGenerator(int seed);
	double getHeight(int x, int z, int chunkX, int chunkZ) const;
	void setParameters(const NoiseParamters& pararms);
private:
	double getNoise(int n) const;
	double getNoise(double x, double z) const;
	double lerp(double a, double b, double z) const;
	double noise(double x, double z) const;

	NoiseParamters m_noiseParameters;
	int m_seed;
};