#pragma once
#include <SFML/Graphics.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"

class Camera;

class RenderMaster
{
public:
	void drawQuad(const glm::vec3& pos);
	void drawCube(const glm::vec3& pos);

	void finishRender(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer m_quadRenderer;
	CubeRenderer m_cubeRenderer;
};