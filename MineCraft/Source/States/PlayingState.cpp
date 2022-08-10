#include "PlayingState.h"

#include "../Renderer/RenderMaster.h"
#include "../Application.h"

StatePlaying::StatePlaying(Application& app):StateBase(app)
{
	app.getCamera().hookEntity(m_player);
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput()
{
	m_player.handleInput(m_pApplication->getWindow(), m_world);
}

void StatePlaying::update(float deltaTime)
{
	m_fpsCounter.update();
	m_player.update(deltaTime);
	m_world.update(m_pApplication->getCamera());
}

void StatePlaying::render(RenderMaster& renderer)
{
	m_world.renderWorld(renderer);
	m_fpsCounter.draw(renderer);
}

void StatePlaying::onOpen()
{
	m_pApplication->turnOffMouse();
}