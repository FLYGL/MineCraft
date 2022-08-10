#pragma once

#include "Shader.h"

class SkyboxShader : public Shader
{
public:
	SkyboxShader();
	void loadViewMatrix(glm::mat4 viewMatrix);
	void loadProjectionMatrix(const glm::mat4& proj);
private:
	void getUniforms() override;
	GLuint m_locationProjection;
	GLuint m_locationView;
};