#include "PlayingState.h"
#include "../Application.h"
#include "../Renderer/RenderMaster.h"

StatePlaying::StatePlaying(Application& app):StateBase(app)
{
	app.getCamera().hookEntity(m_player);
	m_chTexture.loadFromFile("Res/Textures/ch.png");
	m_crosshair.setTexture(&m_chTexture);
	m_crosshair.setSize({ 20,20 });
	m_crosshair.setOrigin(m_crosshair.getGlobalBounds().width / 2, m_crosshair.getGlobalBounds().height / 2);
	m_crosshair.setPosition(app.getWindow().getSize().x / 2.f, app.getWindow().getSize().y / 2.f);
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
	m_player.update(deltaTime, m_world);
	m_world.update(m_pApplication->getCamera());
}

void StatePlaying::render(RenderMaster& renderer)
{
	static Entity cubeTest({ 30,500,30 }, { 50,70,25 });
	m_fpsCounter.draw(renderer);
	renderer.drawSFML(m_crosshair);
	m_world.renderWorld(renderer,m_pApplication->getCamera());
	m_player.draw(renderer);
}

void StatePlaying::onOpen()
{
	m_pApplication->turnOffMouse();
}