#pragma once
#include "glm.h"

class Camera;

glm::mat4 makeViewMatrix(const Camera& camera);

glm::mat4 makeProjectionMatrix(float fov);