#pragma once

class World;

struct IWorldEvent
{
	virtual void handle(World& world) = 0;
};