#include "Player.h"
#include "../Maths/Ray.h"
#include "../world/Block/BlockId.h"
Player::Player()
{
	position = { -5,5,5 };
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

	rotation.y += -change.x * 0.05;
	rotation.x += -change.y * 0.05;
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& timer.getElapsedTime().asSeconds() > 0.2)
	{
		for (Ray ray(position, rotation); ray.getLength() < 6; ray.step(0.1))
		{
			int x = ray.getEnd().x;
			int y = ray.getEnd().y;
			int z = ray.getEnd().z;

			auto block = world.getBlock(x, y, z);
			if (block != BlockId::Air)
			{
				timer.restart();
				world.editBlock(x, y, z, BlockId::Air);
				break;
			}
		}
	}
}