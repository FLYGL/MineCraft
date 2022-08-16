#pragma once

#include "Maths/glm.h"
#include "Maths/Frustum.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	void update();
	void hookEntity(const Entity& entity);
	const glm::mat4& getViewMatrix() const noexcept;
	const glm::mat4& getProjMatrix() const noexcept;
	const glm::mat4& getProjectionViewMatrix() const noexcept;
	const ViewFrustum& getFrustum()const noexcept;

private:
	const Entity* m_pEntity;
	ViewFrustum m_frustum;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrix;
};