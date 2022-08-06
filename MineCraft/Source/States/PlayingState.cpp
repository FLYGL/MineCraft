#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"
#include <iostream>

StatePlaying::StatePlaying(Application& app):StateBase(app)
{
	app.getCamera().hookEntity(m_player);
}

StatePlaying::~StatePlaying() 
{
	std::cout << "StatePlaying Destroy" << std::endl;
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput()
{
	m_player.handleInput(m_pApplication->getWindow());
}

void StatePlaying::update(float deltaTime)
                                                                                                                                                                              {
	m_player.update(deltaTime);
}

void StatePlaying::render(RenderMaster& renderer)
{
	renderer.drawCube({ 0,0,0 });
}