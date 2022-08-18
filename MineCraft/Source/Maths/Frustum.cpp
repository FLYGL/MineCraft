#include "Frustum.h"
#include "../Camera.h"
#include "../Debug/Debug.h"

enum Planes
{
	Near,
	Far,
	Left,
	Right,
	Top,
	Bottom
};

float Plane::distanceToPoint(const glm::vec3& point) const noexcept
{
	return glm::dot(point, normal) + distanceToOrigin;
}

void ViewFrustum::update(Camera& camera) noexcept
{
	glm::mat4 mat = camera.getProjectionViewMatrix();
	//left
	m_planes[Planes::Left].normal.x = mat[0][3] + mat[0][0];
	m_planes[Planes::Left].normal.y = mat[1][3] + mat[1][0];
	m_planes[Planes::Left].normal.z = mat[2][3] + mat[2][0];
	m_planes[Planes::Left].distanceToOrigin = mat[3][3] + mat[3][0];
	//right
	m_planes[Planes::Right].normal.x = mat[0][3] - mat[0][0];
	m_planes[Planes::Right].normal.y = mat[1][3] - mat[1][0];
	m_planes[Planes::Right].normal.z = mat[2][3] - mat[2][0];
	m_planes[Planes::Right].distanceToOrigin = mat[3][3] - mat[3][0];
	// bottom
	m_planes[Planes::Bottom].normal.x = mat[0][3] + mat[0][1];
	m_planes[Planes::Bottom].normal.y = mat[1][3] + mat[1][1];
	m_planes[Planes::Bottom].normal.z = mat[2][3] + mat[2][1];
	m_planes[Planes::Bottom].distanceToOrigin = mat[3][3] + mat[3][1];

	// top
	m_planes[Planes::Top].normal.x = mat[0][3] - mat[0][1];
	m_planes[Planes::Top].normal.y = mat[1][3] - mat[1][1];
	m_planes[Planes::Top].normal.z = mat[2][3] - mat[2][1];
	m_planes[Planes::Top].distanceToOrigin = mat[3][3] - mat[3][1];

	// near
	m_planes[Planes::Near].normal.x = mat[0][3] + mat[0][2];
	m_planes[Planes::Near].normal.y = mat[1][3] + mat[1][2];
	m_planes[Planes::Near].normal.z = mat[2][3] + mat[2][2];
	m_planes[Planes::Near].distanceToOrigin = mat[3][3] + mat[3][2];

	// far
	m_planes[Planes::Far].normal.x = mat[0][3] - mat[0][2];
	m_planes[Planes::Far].normal.y = mat[1][3] - mat[1][2];
	m_planes[Planes::Far].normal.z = mat[2][3] - mat[2][2];
	m_planes[Planes::Far].distanceToOrigin = mat[3][3] - mat[3][2];
}

bool ViewFrustum::isBoxInFrustum(const AABB& box)  const noexcept
{
	glm::vec3 tmp;
	bool result = true;
	int tmpN = 0;
	Debug::compareBlockNumbers++;
	for (auto& plane : m_planes)
	{
		Debug::comparePlaneTimes++;
		tmpN++;
		box.getVP(plane.normal, tmp);
		if (plane.distanceToPoint(tmp) < 0)
		{
			result = false;
			break;
		}
	}
	Debug::comparePlaneDistrubute[tmpN-1]++;
	Debug::comparePlaneDistrubute[6] += result ? 1 : 0;
 	return result;
}