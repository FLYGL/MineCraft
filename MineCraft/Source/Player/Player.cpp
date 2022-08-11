#include "Player.h"
#include "../Maths/Ray.h"
#include "../world/Block/BlockId.h"
#include <iostream>
namespace
{
	glm::vec3 GetNewBlockPosition(const glm::vec3& blockPosition,glm::vec3 playerPosition)
	{
		//变化坐标系
		playerPosition -= blockPosition+glm::vec3(-0.5f,0.5f,0.5f);
		glm::vec3 absPositon = glm::abs(playerPosition);
		// 在 x方向
		if (absPositon.x > absPositon.y && absPositon.x > absPositon.z)
		{
			if (playerPosition.x > 0) {
				return blockPosition + glm::vec3(1,0,0);
			}
			else {
				return blockPosition + glm::vec3(-1, 0, 0);
			}
		}
		// 在 z 方向
		if (absPositon.z > absPositon.y && absPositon.z > absPositon.x)
		{
			if (playerPosition.z > 0) {
				return blockPosition + glm::vec3(0, 0, 1);
			}
			else {
				return blockPosition + glm::vec3(0, 0, -1);
			}
		}
		//在y方向
		if (absPositon.y > absPositon.x && absPositon.y > absPositon.z)
		{
			if (playerPosition.y > 0) {
				return blockPosition + glm::vec3(0, 1, 0);
			}
			else {
				return blockPosition + glm::vec3(0, -1, 0);
			}
		}
		return blockPosition;
	}
}
Player::Player()
{
	position = { 50,200,50 };
	m_velocity = { 0,0,0 };
	rotation = { 0,0,0 };
}
void Player::handleInput(const sf::RenderWindow& window, World& world)
{
	keyboardInput();
	mouseInput(window);
	mouseClick(world);
}

void Player::update(float dt)
{
	position += m_velocity * dt;
	m_velocity *= 0.95;
}
void Player::keyboardInput()
{
	glm::vec3 change(0.f);
	float speed = 0.5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		speed = speed * 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		change.x = glm::sin(glm::radians(rotation.y+180)) * speed;
		change.z = glm::cos(glm::radians(rotation.y+180)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		change.x = glm::sin(glm::radians(rotation.y)) * speed;
		change.z = glm::cos(glm::radians(rotation.y)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		change.x = glm::sin(glm::radians(rotation.y+270)) * speed;
		change.z = glm::cos(glm::radians(rotation.y+270)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		change.x = glm::sin(glm::radians(rotation.y+90)) * speed;
		change.z = glm::cos(glm::radians(rotation.y+90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		change.y += speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		change.y -= speed;
	}

	m_velocity += change;
}
void Player::mouseInput(const sf::RenderWindow& window)
{
	static auto const BOUND = 80;
	static auto lastMousePosition = sf::Mouse::getPosition(window);
	auto change = sf::Mouse::getPosition() - lastMousePosition;

	rotation.y += static_cast<float>(-change.x) * 0.05f;
	rotation.x += static_cast<float>(-change.y) * 0.05f;
	if (rotation.x > BOUND) rotation.x = BOUND;
	else if (rotation.x < -BOUND) rotation.x = -BOUND;

	if (rotation.y > 360) rotation.y = 0;
	else if (rotation.y < 0) rotation.y = 360;

	auto cx = static_cast<int>(window.getSize().x / 2);
	auto cy = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({ cx,cy }, window);

	lastMousePosition = sf::Mouse::getPosition();
}

void Player::mouseClick(World& world)
{
	static sf::Clock timer;
	if (timer.getElapsedTime().asSeconds() > 0.2)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (Ray ray(position, rotation); ray.getLength() < 6; ray.step(0.1f))
			{
				auto end = ray.getEnd();
				int x = static_cast<int>(end.x);
				int y = static_cast<int>(end.y);
				int z = static_cast<int>(end.z);

				auto block = world.getBlock(x, y, z);
				if (block != BlockId::Air)
				{
					timer.restart();
					world.setBlock(x, y, z, BlockId::Air);
					break;
				}
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			for (Ray ray(position, rotation); ray.getLength() < 6; ray.step(0.1f))
			{
				auto end = ray.getEnd();
				int x = static_cast<int>(end.x);
				int y = static_cast<int>(end.y);
				int z = static_cast<int>(end.z);

				auto block = world.getBlock(x, y, z);
				if (block != BlockId::Air)
				{
					timer.restart();
					glm::u32vec3 newBlockPosition = GetNewBlockPosition({ x,y,z }, position);
					world.setBlock(newBlockPosition.x, newBlockPosition.y, newBlockPosition.z, BlockId::Grass);
					break;
				}
			}
		}
	}
}

