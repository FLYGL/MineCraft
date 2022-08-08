#pragma once

#include "../Entity.h"
#include <SFML/Graphics.hpp>
#include "../world/World.h"

class Player : public Entity
{
public:
	Player();
	void handleInput(const sf::RenderWindow& window, World& world);
	void update(float dt);
private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);
	void mouseClick(World& world);
	glm::vec3 m_velocity;
};