#include "ChunkSection.h"
#include "../Block/BlockId.h"
#include "../World.h"
#include "ChunkMeshBuilder.h"
#include <iostream>
ChunkSection::ChunkSection(const sf::Vector3i& position, World& world):m_location(position),
	m_pWorld(&world)
{ 
}

bool ChunkSection::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
	{
		auto location = toWorldPosition(x, y, z);
		return m_pWorld->setBlock(location.x, location.y, location.z, block);
	}
	m_hasMesh = false;
	m_blocks[getIndex(x, y, z)] = block;
	return true;
}

void ChunkSection::makeMesh()
{
	ChunkMeshBuilder(*this, m_mesh).buildMesh();
	m_hasBufferedMesh = false;
	m_hasMesh = true;
}

void ChunkSection::bufferMesh()
{
	m_mesh.bufferMesh();
	m_hasBufferedMesh = true;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z)const
{
	if (outOfBounds(x) || outOfBounds(y) || outOfBounds(z))
	{
		auto location = toWorldPosition(x, y, z);
		return m_pWorld->getBlock(location.x, location.y, location.z);
	}
	return m_blocks[getIndex(x, y, z)];
}
const sf::Vector3i ChunkSection::getLocation() const noexcept
{
	return m_location;
}

sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z)const noexcept
{
	return {
		m_location.x * CHUNK_SIZE + x,
		m_location.y * CHUNK_SIZE + y,
		m_location.z * CHUNK_SIZE + z,
	};
}

bool ChunkSection::outOfBounds(int value)
{
	return value >= CHUNK_SIZE || value < 0;
}

int ChunkSection::getIndex(int x, int y, int z)
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}

bool ChunkSection::hashMesh() const noexcept
{
	return m_hasMesh;
}
bool ChunkSection::hashBuffered() const noexcept
{
	return m_hasBufferedMesh;
}

const ChunkMesh& ChunkSection::getMesh() const 
{
	return m_mesh;
}