#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity.h"
#include "../Item/ItemStack.h"
#include "../world/World.h"
#include "../ToggleKey.h"

class RenderMaster;

class Player : public Entity
{
public:
	Player();
	void handleInput(const sf::RenderWindow& window, World& world);
	void update(float dt , World& world);
	void collide(World& world, const glm::vec3& vel, float dt);

	void addItem(const Material& material);
	void draw(RenderMaster& master);
	ItemStack& getHeldItems();
private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);
	void mouseClick(World& world);
	void itemUpdate();
	bool m_isOnGround = false;

	std::vector<ItemStack> m_items;
	std::vector<sf::Text> m_itemText;
	int m_heldItem = 0;

	ToggleKey m_itemDown;
	ToggleKey m_itemUp;
};