#include "Camera.h"
#include "Maths/Matrix.h"

Camera::Camera()
{
	m_projectionMatrix = makeProjectionMatrix(90);
}

void Camera::update()
{
	m_viewMatrix = makeViewMatrix(*this);
	m_projViewMatrix = m_projectionMatrix * m_viewMatrix;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix() const noexcept
{
	return m_projectionMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const noexcept
{
	return m_projViewMatrix;
}

const glm::vec3& Camera::getPosition() const noexcept
{
	return m_worldPosition;
}

//KeyPoint :  这里的旋转是指什么样的旋转
const glm::vec3& Camera::getRotation() const noexcept
{
	return m_rotation;
}