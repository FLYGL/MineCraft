#include "Matrix.h"

#include "../Camera.h"
#include "../Entity.h"

//TODO 关于模型空间旋转问题。
glm::mat4 makeModelMatrix(const Entity& entity)
{
	glm::mat4 matrix(1.0f);
	matrix = glm::translate(matrix, entity.position);
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0,0,1 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0,1,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1,0,0 });
	return matrix;
}




glm::mat4 makeViewMatrix(const Camera& camera)
{
	glm::mat4 tMatrix(1.0f);
	tMatrix = glm::translate(tMatrix, -camera.position);
	glm::mat4 rYMatrix(1.f);
	rYMatrix = glm::rotate(rYMatrix, glm::radians(camera.rotation.y), { 0,1,0 });
	glm::mat4 rXmatrix(1.f);
	glm::vec3 axis =glm::vec3(rYMatrix* glm::vec4(1,0,0,0));
	rXmatrix = glm::rotate(rXmatrix, glm::radians(camera.rotation.x), axis);
	return glm::transpose(rYMatrix)* glm::transpose(rXmatrix) * tMatrix;
}

glm::mat4 makeProjectionMatrix(float fov)
{
	return glm::perspective(glm::radians(fov), 1280.f / 720.f, 0.1f, 1000.0f);
}