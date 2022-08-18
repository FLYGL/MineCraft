#pragma once
#include "glm.h"

class Camera;
class Entity;

glm::mat4 makeModelMatrix(const Entity& entity) noexcept;

glm::mat4 makeViewMatrix(const Camera& camera) noexcept;

glm::mat4 makeProjectionMatrix(float fov) noexcept;