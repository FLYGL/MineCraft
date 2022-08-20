#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "../WorldConstants.h"
#include "IChunk.h"
#include "ChunkMesh.h"
#include "../../Physics/AABB.h"

class World;

class ChunkSection : public IChunk
{
	friend class Chunk;
	class Layer
	{
	public:
		void update(ChunkBlock c) noexcept
		{
			if (c.getData().isOpaque)
			{
				m_solidBlockCount--;
			}
			else {
				m_solidBlockCount++;
			}
		}
		bool isAllSolid() const noexcept
		{
			return m_solidBlockCount == CHUNK_AREA;
		}
	private:
		int m_solidBlockCount = 0;
	};
public:
	ChunkSection(const sf::Vector3i& position,World& world);
	bool setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;
	const sf::Vector3i getLocation() const noexcept;
	bool hashMesh() const noexcept;
	bool hashBuffered() const noexcept;
	void makeMesh();
	void bufferMesh();

	const Layer& getLayer(int y) const;
	ChunkSection& getAdjacent(int dx, int dz);

	const ChunkMeshCollection& getMeshes() const
	{
		return m_meshes;
	}

private:
	static bool outOfBounds(int value);
	static int getIndex(int x, int y, int z);

	sf::Vector3i toWorldPosition(int x, int y, int z) const noexcept;
	std::array<Layer, CHUNK_SIZE> m_layers;
	std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
	sf::Vector3i m_location;
	World* m_pWorld;
	ChunkMeshCollection m_meshes;
	AABB m_aabb;
	bool m_hasMesh = false;
	bool m_hasBufferedMesh = false;
};

