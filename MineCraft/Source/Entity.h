#pragma once

#include "Maths/Matrix.h"
#include "Physics/AABB.h"

struct Entity
{
	Entity() :box({0,0,0})
	{}
	Entity(const glm::vec3& pos, const glm::vec3& rot):
		position(pos),
		rotation(rot),
		box({0,0,0})
	{

	}
	Entity(const glm::vec3& pos,const glm::vec3& rot,const glm::vec3& box):
		position(pos),
		rotation(rot),
		box(box)
	{

	}

	glm::vec3 position;
	//KeyPoint :  这里的旋转是指什么样的旋转,根据上下文理解即可。
	// 玩家视角相机 是球面坐标，只有 x y 维度分量有效。
	glm::vec3 rotation;
	glm::vec3 velocity;
	AABB box;
};