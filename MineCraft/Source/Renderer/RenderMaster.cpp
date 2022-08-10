#include "RenderMaster.h"

#include <SFML/Graphics.hpp>

#include <iostream>

void RenderMaster::drawQuad(const glm::vec3& pos)
{
	m_quadRenderer.add(pos);
}

void RenderMaster::drawCube(const glm::vec3& pos)
{
	m_cubeRenderer.add(pos);
}

void RenderMaster::drawChunk(const ChunkMesh& mesh)
{
	m_chunkRenderer.add(mesh);
}

void RenderMaster::finishRender(sf::RenderWindow& window, const Camera& camera)
{
	glClearColor(0.1f, 0.5f, 1.0f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	m_quadRenderer.render(camera);
	m_cubeRenderer.render(camera);
	m_chunkRenderer.render(camera);
	m_skyboxRenderer.render(camera);
	window.display();
}