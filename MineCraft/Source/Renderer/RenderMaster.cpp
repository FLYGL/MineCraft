#include "RenderMaster.h"

#include <SFML/Graphics.hpp>

#include <iostream>

void RenderMaster::drawQuad(const glm::vec3& pos)
{
	m_quadRenderer.add(pos);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	glClearColor(0.1f, 0.5f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	m_quadRenderer.renderQuads(camera);

	window.display();
}