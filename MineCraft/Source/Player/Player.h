#pragma once

#include "../Entity.h"
#include <SFML/Graphics.hpp>

class Player : public Entity
{
public:
	Player();
	void handleInput(const sf::RenderWindow& window);
	void update(float dt);
private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);

	glm::vec3 m_velocity;
};