#pragma once

#include "../Shaders/SkyboxShader.h"
#include "../Texture/CubeTexture.h"
#include "../Model.h"

class Camera;

class SkyboxRenderer
{
public:
	SkyboxRenderer();
	void render(const Camera& camera);
private:
	Model m_skyCube;
	SkyboxShader m_shader;
	CubeTexture m_cubeTexture;
};