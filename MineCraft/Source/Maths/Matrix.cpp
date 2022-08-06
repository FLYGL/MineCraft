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
	glm::mat4 matrix = makeViewMatrixDirUp(camera);
	return matrix;
}
glm::mat4 makeViewMatrixDirUp(const Camera& camera)
{
	glm::mat4 rotatMatrix(1.0f);
	//rotatMatrix = glm::rotate(rotatMatrix, glm::radians(camera.rotation.x), { 1,0,0 });
	rotatMatrix = glm::rotate(rotatMatrix, glm::radians(camera.rotation.y), { 0,1,0 });
	glm::vec3 cameraPosition = glm::vec3(rotatMatrix * glm::vec4(camera.position,1.f));
	glm::vec3 lookDir = -cameraPosition;
	glm::vec3 lookUp = glm::vec3(0.f, 1.0f, 0.f);
	glm::vec3 right = glm::cross(lookDir, lookUp);
	glm::vec3 up = glm::cross(right, lookDir);
	lookDir = glm::normalize(lookDir);
	right = glm::normalize(right);
	up = glm::normalize(up);
	glm::mat4 CameraToWorld(1.f);
	CameraToWorld[0] = glm::vec4(right, 0.f);
	CameraToWorld[1] = glm::vec4(up, 0.f);
	CameraToWorld[2] = glm::vec4(-lookDir, 0.f);
	CameraToWorld[3] = glm::vec4(cameraPosition, 1.f);
	return glm::inverse(CameraToWorld);
}
glm::mat4 makeProjectionMatrix(float fov)
{
	return glm::perspective(glm::radians(fov), 1280.f / 720.f, 0.1f, 1000.0f);
}