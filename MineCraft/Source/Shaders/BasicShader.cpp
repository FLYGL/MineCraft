#include "BasicShader.h"

BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile)
	:Shader(vertexFile,fragmentFile)
{
	getUniforms();
}

void BasicShader::loadProjectionViewMatrix(const glm::mat4& pMatrix)
{
	loadMatrix4(m_locationProjectionViewMatrix, pMatrix);
}

void BasicShader::loadModelMatrix(const glm::mat4& matrix)
{
	loadMatrix4(m_locationModelMatrix,matrix);
}

void BasicShader::getUniforms()
{
	m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMatrix");
	m_locationModelMatrix = glGetUniformLocation(m_id, "modelMatrix");
}