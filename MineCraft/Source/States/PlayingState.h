#pragma once

#include "StateBase.h"
#include "../Player/Player.h"

class StatePlaying : public StateBase
{
public:
	StatePlaying(Application& app);
	virtual ~StatePlaying();
	void handleEvent(sf::Event e) override;
	void handleInput() override;
	void update(float deltaTime) override;
	void render(RenderMaster& render)override;
private:
	Player m_player;
};