#include "BlockDatabase.h"

BlockDatabase::BlockDatabase():textureAtlas("DefaultPack")
{
	m_blocks[static_cast<int>(BlockId::Air)] = std::make_unique<DefaultBlock>("Air");
	m_blocks[static_cast<int>(BlockId::Grass)] = std::make_unique<DefaultBlock>("Grass");
	m_blocks[static_cast<int>(BlockId::Dirt)] = std::make_unique<DefaultBlock>("Dirt");
	m_blocks[static_cast<int>(BlockId::Stone)] = std::make_unique<DefaultBlock>("Stone");
}
// TODO : 这种static 什么时候初始化
BlockDatabase& BlockDatabase::get() 
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