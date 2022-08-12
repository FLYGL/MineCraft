#pragma once

#include "../Maths/glm.h"

struct AABB
{
	AABB(const glm::vec3& dim) : dimensions(dim)
	{

	}
	void update(const glm::vec3& location)
	{
		position = location;
	}
	glm::vec3 position;
	const glm::vec3 dimensions;
};