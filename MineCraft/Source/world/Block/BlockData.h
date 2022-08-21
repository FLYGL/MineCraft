#pragma once

#include <SFML/Graphics.hpp>
#include "../../Util/NonCopyable.h"
#include "BlockId.h"

enum class BlockMeshType
{
	Cube = 0,
	X = 1,
};

struct BlockDataHolder :  public NonCopyable
{
	BlockId id;
	sf::Vector2i texTopCoord;
	sf::Vector2i texSideCoord;
	sf::Vector2i texBottomCoord;
	bool isOpaque;
	BlockMeshType meshType;
};

class BlockData : public NonCopyable
{
public:
	BlockData(const std::string& fileName);
	const BlockDataHolder& getBlockData() const;
private:
	BlockDataHolder m_data;
};