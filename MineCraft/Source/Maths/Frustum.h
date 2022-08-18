#pragma once

#include <array>
#include "glm.h"
#include "../Physics/AABB.h"
class Camera;
struct Plane
{
	float distanceToPoint(const glm::vec3& point) const noexcept;
	float distanceToOrigin;
	//法向量必须指向原点
	glm::vec3 normal;
};

class ViewFrustum
{
public:
	//void update(const glm::mat4& projViewMatrix);
	void update(Camera& camera) noexcept;
	bool isBoxInFrustum(const AABB& box) const noexcept;
private:
	std::array<Plane, 6> m_planes;
};