#pragma once

#include "StateBase.h"

class StatePlaying : public StateBase
{
public:
	StatePlaying(Application& app);
	void handleEvent(sf::Event e) override;
	void handleInput() override;
	void update(float deltaTime) override;
	void render(RenderMaster& render)override;
private:

};