#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity.h"
#include "../Item/ItemStack.h"
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

	std::vector<ItemStack> m_items;
};