#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader(const std::string& vertexFile = "Shaders/BasicVertex.glsl",
		const std::string& fragmentFile = "Shaders/BasicFragment.glsl");
	void loadProjectionViewMatrix(const glm::mat4& pMatrix);
	void loadModelMatrix(const glm::mat4& matrix);
private:
	virtual void getUniforms() override;
	GLuint m_locationProjectionViewMatrix;
	GLuint m_locationModelMatrix;
};