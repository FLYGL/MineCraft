#pragma once

#include "BasicShader.h"

class WaterShader : public BasicShader
{
public:
	WaterShader();
	void addTime(float time);
private:
	void getUniforms() override;
	GLuint m_locationTime;
};