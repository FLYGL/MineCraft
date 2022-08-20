#include "WaterShader.h"

WaterShader::WaterShader() :
	BasicShader("Shaders/WaterVertex.glsl", "Shaders/ChunkFragment.glsl")
{
	getUniforms();
}


void WaterShader::addTime(float time)
{
	Shader::loadFloat(m_locationTime, time);
}

void WaterShader::getUniforms()
{
	BasicShader::getUniforms();
	m_locationTime = glGetUniformLocation(m_id, "time");
}