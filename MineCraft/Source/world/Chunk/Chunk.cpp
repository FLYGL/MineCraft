#include "Chunk.h"

#include "../../Renderer/RenderMaster.h"
#include "ChunkMeshBuilder.h"

Chunk::Chunk(World& world,const sf::Vector2i& location): m_location(location), m_pWorld(&world)
{
	for (int y = 0; y < 3; y++)
	{
		m_chunks.emplace_back(sf::Vector3i(location.x, y, location.y), world);
	}
}
void Chunk::makeAllMeshtemp()
{
	for (auto& chunk : m_chunks)
	{
		ChunkMeshBuilder builder(chunk);
		builder.buildMesh(chunk.m_mesh);
		chunk.m_mesh.bufferMesh();
	}
}

void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBound(x, y, z))
	{
		return;
	}
}

ChunkBlock Chunk::getBlock(int x, int y, int z) const
{
	if (outOfBound(x, y, z)) return BlockId::Air;
	int bY = y % CHUNK_SIZE;
	return m_chunks.at(y / CHUNK_SIZE).getBlock(x, bY, z);
}

void Chunk::drawChunks(RenderMaster& renderer)
{
	for (auto& chunk : m_chunks)
	{
		renderer.drawChunk(chunk.m_mesh);
	}
}

bool Chunk::outOfBound(int x, int y, int z) const noexcept
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;
	if (x < 0 || z < 0 || y < 0) return true;
	if (y >= m_chunks.size() * CHUNK_SIZE) return true;
	return false;
}