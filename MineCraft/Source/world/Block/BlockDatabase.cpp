#include "BlockDatabase.h"
#include <iostream>
BlockDatabase::BlockDatabase():textureAtlas("DefaultPack")
{
	std::cout << "BlockDatabase Construct" << std::endl;
	m_blocks[static_cast<int>(BlockId::Air)] = std::make_unique<DefaultBlock>("Air");
	m_blocks[static_cast<int>(BlockId::Grass)] = std::make_unique<DefaultBlock>("Grass");
	m_blocks[static_cast<int>(BlockId::Dirt)] = std::make_unique<DefaultBlock>("Dirt");
	m_blocks[static_cast<int>(BlockId::Stone)] = std::make_unique<DefaultBlock>("Stone");
	m_blocks[static_cast<int>(BlockId::OakBark)] = std::make_unique<DefaultBlock>("OakBark");
	m_blocks[static_cast<int>(BlockId::OakLeaf)] = std::make_unique<DefaultBlock>("OakLeaf");
	m_blocks[static_cast<int>(BlockId::Sand)] = std::make_unique<DefaultBlock>("Sand");
	m_blocks[static_cast<int>(BlockId::Water)] = std::make_unique<DefaultBlock>("Water");
	m_blocks[static_cast<int>(BlockId::Cactus)] = std::make_unique<DefaultBlock>("Cactus");
	m_blocks[static_cast<int>(BlockId::TallGrass)] = std::make_unique<DefaultBlock>("TallGrass");
	m_blocks[static_cast<int>(BlockId::Rose)] = std::make_unique<DefaultBlock>("Rose");
	m_blocks[static_cast<int>(BlockId::DeadShrub)] = std::make_unique<DefaultBlock>("DeadShrub");
}
// TODO : 这种static 什么时候初始化
BlockDatabase& BlockDatabase::get()  noexcept
{
	static BlockDatabase d;
	return d;
}

const BlockType& BlockDatabase::getBlock(BlockId id) const
{
	return *m_blocks[static_cast<int>(id)];
}

const BlockData& BlockDatabase::getData(BlockId id) const
{
	return m_blocks[static_cast<int>(id)]->getData();
}