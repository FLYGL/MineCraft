#pragma once

#include "../Entity.h"
#include <SFML/Graphics.hpp>
#include "../world/World.h"


class Player : public Entity
{
public:
	Player();
	void handleInput(const sf::RenderWindow& window, World& world);
	void update(float dt , World& world);
	void collide(World& world, const glm::vec3& vel, float dt);
private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);
	void mouseClick(World& world);
	bool m_isOnGround = false;
	//glm::vec3 m_velocity;
};