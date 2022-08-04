#include "Shader.h"

#include "ShaderLoader.h"

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
	:m_id(loadShaders(vertexFile,fragmentFile))
{
	useProgram();
}

void Shader::loadInt(GLuint location, int value)
{
	glUniform1i(location, value);
}
//Key Point : normalized intege?
void Shader::loadFloat(GLuint location, GLfloat value)
{
	glUniform1f(location, value);
}

void Shader::loadVector2(GLuint location, const glm::vec2& vect)
{
	glUniform2f(location, vect.x, vect.y);
}

void Shader::loadVector3(GLuint location, const glm::vec3& vect)
{
	glUniform3f(location, vect.x, vect.y, vect.z);
}

void Shader::loadVector4(GLuint location, const glm::vec4& vect)
{
	glUniform4f(location, vect.x, vect.y, vect.z, vect.z);
}
//Key point : 注意列 还是 行传入
void Shader::loadMatrix4(GLuint location, const glm::mat4& matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::useProgram() const
{
	glUseProgram(m_id);
}