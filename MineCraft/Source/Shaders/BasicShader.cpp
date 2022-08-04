#include "BasicShader.h"

BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile)
	:Shader(vertexFile,fragmentFile)
{

}

void BasicShader::loadProjectionViewMatrix(const glm::mat4& pMatrix)
{
	loadMatrix4(m_locationProjectionViewMatrix, pMatrix);
}

void BasicShader::getUniforms()
{
	m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMat");
}