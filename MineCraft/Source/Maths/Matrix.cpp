#include "Matrix.h"

#include "../Camera.h"
#include "../Entity.h"

glm::mat4 makeModelMatrix(const Entity& entity)
{
	glm::mat4 matrix(1.0f);

	matrix = glm::rotate(matrix, glm::radians(entity.rotation.x), { 1,0,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.y), { 0,1,0 });
	matrix = glm::rotate(matrix, glm::radians(entity.rotation.z), { 0,0,1 });
	matrix = glm::translate(matrix, entity.position);

	return matrix;
}



//KeyPoint : Camera Space Transform
glm::mat4 makeViewMatrix(const Camera& camera)
{
	glm::mat4 matrix(1.0f);
	//glm::mat4 translateMat(1.f);
	//translateMat[3] = glm::vec4(-camera.position, 1.f);
	//glm::vec3 tmpR = -glm::radians(camera.rotation);
	//glm::mat4 rotateX(1.f);
	//rotateX[1] = glm::vec4(0, glm::cos(tmpR.x), glm::sin(tmpR.x), 0);
	//rotateX[2] = glm::vec4(0, -glm::sin(tmpR.x), glm::cos(tmpR.x), 0);
	//glm::mat4 rotateY(1.f);
	//rotateY[0] = glm::vec4(glm::cos(tmpR.y), 0, -glm::sin(tmpR.y), 0);
	//rotateY[2] = glm::vec4(glm::sin(tmpR.y),  0, glm::cos(tmpR.y), 0);
	//matrix = rotateX * rotateY * translateMat;
	matrix = glm::rotate(matrix, glm::radians(-camera.rotation.x), { 1,0,0 });
	matrix = glm::rotate(matrix, glm::radians(-camera.rotation.y), { 0,1,0 });
	matrix = glm::translate(matrix, -camera.position);

	return matrix;
}

glm::mat4 makeProjectionMatrix(float fov)
{
	return glm::perspective(glm::radians(fov), 1280.f / 720.f, 0.1f, 1000.0f);
}