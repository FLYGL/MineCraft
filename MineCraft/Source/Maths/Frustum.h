#pragma once

#include <array>
#include "glm.h"
#include "../Physics/AABB.h"
class Camera;
struct Plane
{
	float distanceToPoint(const glm::vec3& point) const;
	float distanceToOrigin;
	//����������ָ��ԭ��
	glm::vec3 normal;
};

class ViewFrustum
{
public:
	//void update(const glm::mat4& projViewMatrix);
	void update(Camera& camera);
	bool isBoxInFrustum(const AABB& box) const noexcept;
private:
	std::array<Plane, 6> m_planes;
};