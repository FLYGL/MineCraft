#pragma once

#include <vector>

#include "ChunkSection.h"

class RenderMaster;
class Camera;

class Chunk : public IChunk
{
public:
	Chunk() = default;
	Chunk(World& world,const sf::Vector2i& location);
	bool setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;
	void drawChunks(RenderMaster& renderer,const Camera& camera);
	bool makeMesh();
	bool hashLoaded() const noexcept;
	void load();
	ChunkSection& getSection(int index);
	const sf::Vector2i& getLocation()const noexcept
	{
		return m_location;
	}
	std::vector<ChunkSection>& testGetChunks();
	int getSectionNumber();
private:
	void addSection();
	void addSectionBlockTarget(int blockY);
	void addSectionIndexTarget(int index);
	bool outOfBound(int x, int y, int z) const noexcept;
	std::vector<ChunkSection> m_chunks;
	sf::Vector2i m_location;
	World* m_pWorld;
	bool m_isLoaded = false;
};