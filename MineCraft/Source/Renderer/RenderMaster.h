#pragma once
#include <SFML/Graphics.hpp>

#include "QuadRenderer.h"
#include "CubeRenderer.h"
#include "ChunkRenderer.h"
#include "SkyboxRenderer.h"
#include "SFMLRenderer.h"
#include "WaterRenderer.h"

class Camera;
class ChunkSection;
class RenderMaster
{
public:
	void drawSFML(const sf::Drawable& drawable);
	void drawQuad(const glm::vec3& pos);
	void drawCube(const Entity& cube);
	void drawChunk(const ChunkSection& chunk);
	void finishRender(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer m_quadRenderer;
	CubeRenderer m_cubeRenderer;
	ChunkRenderer m_chunkRenderer;
	SkyboxRenderer m_skyboxRenderer;
	SFMLRenderer m_sfmlRenderer;
	WaterRenderer m_waterRenderer;
};