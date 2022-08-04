#pragma once

#include "Shader.h"

class BasicShader : public Shader
{
public:
	BasicShader(const std::string& vertexFile = "BasicVertex",
		const std::string& fragmentFile = "BasicFragment");
	void loadProjectionViewMatrix(const glm::mat4& pMatrix);
private:
	virtual void getUniforms() override;
	GLuint m_locationProjectionViewMatrix;
};