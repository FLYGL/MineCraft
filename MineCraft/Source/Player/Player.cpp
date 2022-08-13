#include "Player.h"
#include "../Maths/Ray.h"
#include "../world/Block/BlockId.h"
#include "../world/Event/PlayerDigEvent.h"
#include <iostream>
namespace
{
	glm::vec3 GetNewBlockPosition(const glm::vec3& blockPosition,glm::vec3 playerPosition)
	{
		//变化坐标系
		playerPosition -= (blockPosition+glm::vec3(0.5f,0.5f,0.5f));
		glm::vec3 absPositon = glm::abs(playerPosition);
		std::cout << "Block: " << blockPosition.x << " " << blockPosition.y << " " << blockPosition.z << std::endl;
		std::cout <<"Abs: " << absPositon.x << " " << absPositon.y << " " << absPositon.z << std::endl;
		std::cout <<"Player: "<< playerPosition.x <<" "<< playerPosition.y<<" "<< playerPosition.z <<std::endl;
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
	bool IsInteract(glm::vec3 blockPosition,Player& player)
	{
		glm::vec3 maxPlayerPosition = player.position + player.box.dimensions;
		glm::vec3 minPlayerPosition = player.position - player.box.dimensions;
		glm::vec3 maxBlockPosition = blockPosition + glm::vec3(1, 1, 1);
		if (maxBlockPosition.x >= minPlayerPosition.x && maxBlockPosition.y >= minPlayerPosition.y &&
			maxBlockPosition.z >= minPlayerPosition.z && maxBlockPosition.x <= maxPlayerPosition.x &&
			maxBlockPosition.y <= maxPlayerPosition.y && maxBlockPosition.z <= maxPlayerPosition.z) return true;
		if (blockPosition.x >= minPlayerPosition.x && blockPosition.y >= minPlayerPosition.y &&
			blockPosition.z >= minPlayerPosition.z && blockPosition.x <= maxPlayerPosition.x &&
			blockPosition.y <= maxPlayerPosition.y && blockPosition.z <= maxPlayerPosition.z) return true;
		return false;
	}
}
Player::Player() : 
	Entity( { 25,500,25 } , { 0,0,0 },  {0.5f,1.5f,0.5f})
{
	
}
void Player::handleInput(const sf::RenderWindow& window, World& world)
{
	keyboardInput();
	mouseInput(window);
	mouseClick(world);
}

void Player::update(float dt,World& world)
{
	if (!m_isOnGround)
	{
		//velocity.y -= 55 * dt;
		velocity.y *= 0.95;
	}
	m_isOnGround = false;
	box.update(position);
	velocity.x *= 0.95;
	velocity.z *= 0.95;

	position.x += velocity.x * dt;
	collide(world, { velocity.x,0,0 }, dt);
	
	position.z += velocity.z * dt;
	collide(world, { 0,0,velocity.z }, dt);

	position.y += velocity.y * dt;
	collide(world, { 0,velocity.y,0 }, dt);
}
void Player::collide(World& world, const glm::vec3& vel, float dt)
{
	// TODO 0.001 是为了保证碰撞计算的浮点数问题，float->int 
	auto& d = box.dimensions;
	auto& p = position;
	auto& v = vel;
	for(int x = std::floor(p.x - d.x); x <= std::floor(p.x + d.x) ; x++)
		for(int z = std::floor(p.z - d.z); z <= std::floor(p.z + d.z); z++)
			for (int y = std::floor(p.y - d.y); y <= std::floor(p.y + d.y); y++)
			{
				auto block = world.getBlock(x, y, z);
				if (block != BlockId::Air)
				{
					if (v.x > 0) p.x = x - d.x-0.001;
					else if (v.x < 0) p.x =x + d.x + 1+0.001;
					if (v.y > 0) {
						p.y = y - d.y - 0.001;
						velocity.y = 0;
					}
					else if (v.y < 0)
					{
						p.y = y + d.y + 1+0.001;
						velocity.y = 0;
						m_isOnGround = true;
					}
					if (v.z > 0)
					{
						p.z = z - d.z - 0.001;
					}
					else if (v.z < 0)
					{
						p.z =z + d.z + 1+0.001;
					}
				}
			}	
}
void Player::keyboardInput()
{
	glm::vec3 change(0.f);
	float speed = 0.5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		speed = speed * 2;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isOnGround)
	{
		change.y += speed * 35;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		change.y -= speed;
	}
	velocity += change;
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
				int x = std::floor(end.x);
				int y = std::floor(end.y);
				int z = std::floor(end.z);

				auto block = world.getBlock(x, y, z);
				if (block != BlockId::Air)
				{
					timer.restart();
					//world.setBlock(x, y, z, BlockId::Air);

					world.addEvent<PlayerDigEvent>(sf::Mouse::Left, glm::vec3{ x,y,z }, *this);
					break;
				}
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			for (Ray ray(position, rotation); ray.getLength() < 6; ray.step(0.1f))
			{
				auto end = ray.getEnd();
				int x = std::floor(end.x);
				int y = std::floor(end.y);
				int z = std::floor(end.z);

				auto block = world.getBlock(x, y, z);
				if (block != BlockId::Air)
				{
					timer.restart();
					glm::vec3 newBlockPosition = GetNewBlockPosition({ x,y,z }, end);
					// 判断是否有足够的空间
					if (!IsInteract(newBlockPosition,*this))
					{
						world.addEvent<PlayerDigEvent>(sf::Mouse::Right, newBlockPosition, *this);
					}
					else std::cout << "No Spare Space to place the block" << std::endl;
					break;
				}
			}
		}
	}
}

