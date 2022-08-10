#pragma once
#include <SFML/Graphics.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "SkyboxRenderer.h"


class Camera;
class ChunkMesh;
class RenderMaster
{
public:
	void drawQuad(const glm::vec3& pos);
	void drawCube(const glm::vec3& pos);
	void drawChunk(const ChunkMesh& mesh);
	void finishRender(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer m_quadRenderer;
	CubeRenderer m_cubeRenderer;
	ChunkRenderer m_chunkRenderer;
	SkyboxRenderer m_skyboxRenderer;
};