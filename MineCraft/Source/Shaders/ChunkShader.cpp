#include "ChunkShader.h"

ChunkShader::ChunkShader():
	BasicShader("Shaders/ChunkVertex.glsl","Shaders/ChunkFragment.glsl")
{
	getUniforms();
}

void ChunkShader::getUniforms()
{
	BasicShader::getUniforms();
}