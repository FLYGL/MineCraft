#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "../WorldConstants.h"
#include "IChunk.h"
#include "ChunkMesh.h"

class World;

class ChunkSection : public IChunk
{
public:
	ChunkSection(const sf::Vector3i& position,World& world);
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;
	const sf::Vector3i getLocation() const;
	ChunkMesh m_mesh;
private:
	static bool outOfBounds(int value);
	static int getIndex(int x, int y, int z);
	sf::Vector3i toWorldPosition(int x, int y, int z) const noexcept;
	std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
	sf::Vector3i m_location;
	World* m_pWorld;
};

