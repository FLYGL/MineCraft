#include "Ray.h"
 
Ray::Ray(const glm::vec3& position, const glm::vec3& direction) noexcept :
	m_rayStart(position),
	m_rayEnd(position),
	m_direction(direction)
{

}

void Ray::step(float scale) noexcept
{
	float yaw = glm::radians(m_direction.y+180);
	float pitch = glm::radians(m_direction.x);    

	auto& p = m_rayEnd;          
    
	float cos = glm::cos(pitch);
	p.x += glm::sin(yaw) * scale* cos;
	p.z += glm::cos(yaw) * scale* cos;
	p.y += glm::sin(pitch) * scale;
}

const glm::vec3& Ray::getEnd() const noexcept
{
	return m_rayEnd;
}

float Ray::getLength() const noexcept
{
	return glm::distance(m_rayStart, m_rayEnd);
}