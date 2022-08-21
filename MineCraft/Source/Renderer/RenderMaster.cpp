#include "RenderMaster.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Debug/Debug.h"
#include "../world//Chunk/ChunkSection.h"

void RenderMaster::drawSFML(const sf::Drawable& drawable)
{
	m_sfmlRenderer.add(drawable);
}
void RenderMaster::drawQuad(const glm::vec3& pos)
{
	m_quadRenderer.add(pos);
}

void RenderMaster::drawCube(const Entity& cube)
{
	m_cubeRenderer.add(cube);
}

void RenderMaster::drawChunk(const ChunkSection& chunk)
{
	const ChunkMesh& solidMesh = chunk.getMeshes().solidMesh;
	const ChunkMesh& waterMesh = chunk.getMeshes().waterMesh;

	if (solidMesh.faces > 0) m_chunkRenderer.add(solidMesh);
	if (waterMesh.faces > 0)
	{
		m_waterRenderer.add(waterMesh);
	}
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
	m_sfmlRenderer.render(window);
	m_waterRenderer.render(camera);
	window.display();
}