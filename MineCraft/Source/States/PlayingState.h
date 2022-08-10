#pragma once

#include "StateBase.h"
#include "../Player/Player.h"
#include "../world/Chunk/Chunk.h"
#include "../world/World.h"
#include "../Util/FPSCounter.h"

class StatePlaying : public StateBase
{
public:
	StatePlaying(Application& app);
	void handleEvent(sf::Event e) override;
	void handleInput() override;
	void update(float deltaTime) override;
	void render(RenderMaster& render)override;
	void onOpen() override;
private:
	Player m_player;
	World m_world;
	FPSCounter m_fpsCounter;
};