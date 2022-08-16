#include "RenderMaster.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Debug/Debug.h"

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

void RenderMaster::drawChunk(const ChunkMesh& mesh)
{
	if (mesh.faces > 0)
	{
		m_chunkRenderer.add(mesh);
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
	window.display();
	//std::cout << std::endl << std::endl;
	//std::cout << "One Frame ComparePlanesTimes: " << Debug::comparePlaneTimes << std::endl;       
	//std::cout << "One Frame CompareBlockNumbers: " << Debug::compareBlockNumbers << std::endl;
	//std::cout << " Distribute :" << std::endl;
	//for (int i = 0; i < 6;i++)
	//{
	//	std::cout <<"\t" << i + 1 << " : " << Debug::comparePlaneDistrubute[i] << std::endl;
	//}
	//std::cout << "One Frame CompareSuccess: " << Debug::comparePlaneDistrubute[6] << std::endl;
	//std::cout << "One Box Average CompareTimes:" << (float)Debug::comparePlaneTimes / (float)Debug::compareBlockNumbers << std::endl;
	//std::cout << "One Frame RenderMeshNumber: " << Debug::renderBlockNumbers << std::endl;
	//std::cout << "One Frame ChunkSectionNumber: " << Debug::checkSectionNumber << std::endl;
	//std::cout << "One Frame NoneIndicesMeshNumber: " << Debug::noneIndicesNumbers << std::endl;
	//Debug::comparePlaneTimes = 0;
	//Debug::compareBlockNumbers = 0;
	//Debug::checkSectionNumber = 0;
	//for (int i = 0; i < 7;i++)
	//{
	//	Debug::comparePlaneDistrubute[i] = 0;
	//}
}