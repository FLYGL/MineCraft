#pragma once

#include "QuadRenderer.h"
#include <SFML/Graphics.hpp>

class Camera;

class RenderMaster
{
public:
	void drawQuad(const glm::vec3& pos);
	void finishRender(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer m_quadRenderer;
};