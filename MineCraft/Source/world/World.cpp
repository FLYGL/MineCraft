#include "World.h"
#include "../Renderer/RenderMaster.h"
#include "../Maths/Vector2XZ.h"
#include "../Camera.h"

namespace
{
	constexpr int renderDistance = 5;
	// what means
	constexpr float GRAV = -3;
}

World::World():m_chunkManager(*this)
{
	
}

bool World::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (y <= 0) return false;
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	return m_chunkManager.getChunk(cp.x, cp.z).setBlock(bp.x, y, bp.z, block);
}

ChunkBlock World::getBlock(int x, int y, int z)
{
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	//�����µ�����飬�µĿ�ֻ��λ����Ϣ�� û��load��û�е����Լ������Ϣ����û������GPU buffer��
	return m_chunkManager.getChunk(cp.x,cp.z).getBlock(bp.x, y, bp.z);
}

void World::update(const Camera& camera)
{
	for (auto& event : m_events)
	{
		event->handle(*this);
	}
	m_events.clear();
	updateChunks();
	VectorXZ cp = getChunkXZ(camera.position.x, camera.position.z);
	int minX = cp.x - renderDistance;
	int maxX = cp.x + renderDistance;
	int minZ = cp.z - renderDistance;
	int maxZ = cp.z + renderDistance;
	minRenderPosition.x = minX;
	minRenderPosition.z = minZ;
	maxRenderPosition.x = maxX;
	maxRenderPosition.z = maxZ;
	for (int x = minX; x < maxX; x++)
	{
		for (int z = minZ; z < maxZ; z++)
		{
			if (m_chunkManager.makeMesh(x, z)) return;
		}
	}
}

void World::renderWorld(RenderMaster& renderer)
{
	for (int x = minRenderPosition.x; x < maxRenderPosition.x; x++)
	{
		for (int z = minRenderPosition.z; z < maxRenderPosition.z; z++)
		{
			auto& chunk = m_chunkManager.getChunk(x, z);
			chunk.drawChunks(renderer);
		}
	}
}

void World::updateChunk(int blockX, int blockY, int blockZ)
{
	auto addChunkToUpdateBatch = [&](const sf::Vector3i& key, ChunkSection& section)
	{
		m_chunkUpdates.emplace(key, &section);
	};
	auto cp = getChunkXZ(blockX, blockZ);
	auto cy = blockY / CHUNK_SIZE;
	sf::Vector3i key(cp.x, cy, cp.z);
	addChunkToUpdateBatch(key, m_chunkManager.getChunk(cp.x, cp.z).getSection(cy));
	auto sectionBlockXZ = getBlockXZ(blockX, blockZ);
	auto sectionBlockY = blockY % CHUNK_SIZE;
	if (sectionBlockXZ.x == 0)
	{
		sf::Vector3i newKey(cp.x - 1, cy, cp.z);
		addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
	else if (sectionBlockXZ.x == CHUNK_SIZE - 1)
	{
		sf::Vector3i newKey(cp.x + 1, cy, cp.z);
		addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}

	if (sectionBlockY == 0)
	{
		sf::Vector3i newKey(cp.x, cy-1, cp.z);
		addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
	else if (sectionBlockY == CHUNK_SIZE - 1)
	{
		sf::Vector3i newKey(cp.x, cy + 1, cp.z);
		addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}

	if (sectionBlockXZ.z == 0)
	{
		sf::Vector3i newKey(cp.x , cy, cp.z - 1);
		addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
	else if (sectionBlockXZ.z == CHUNK_SIZE - 1)
	{
		sf::Vector3i newKey(cp.x, cy, cp.z + 1);
		addChunkToUpdateBatch(newKey, m_chunkManager.getChunk(newKey.x, newKey.z).getSection(newKey.y));
	}
}

void World::updateChunks()
{
	for (auto& chunk : m_chunkUpdates)
	{
		ChunkSection& s = *chunk.second;
		s.makeMesh();
	}
	m_chunkUpdates.clear();
}

const ChunkManager& World::getChunkManager() const
{
	return m_chunkManager;
}

VectorXZ World::getBlockXZ(int x, int z)
{
	x = x % CHUNK_SIZE;
	z = z% CHUNK_SIZE;
	return
	{
			x<0?x+CHUNK_SIZE:x,
			z<0?z+CHUNK_SIZE:z
	};
}
VectorXZ World::getChunkXZ(int x, int z)
{
	x = x < 0 ? (int)std::floor((float)x / (float)CHUNK_SIZE) : x / CHUNK_SIZE;
	z = z < 0 ? (int)std::floor((float)z / (float)CHUNK_SIZE) : z/ CHUNK_SIZE;
	return
	{
		x ,
		z 
	};
}

VectorXZ World::getChunkXZ(float x, float z)
{
	x = x < 0 ? std::floor(x / (float)CHUNK_SIZE) : x / CHUNK_SIZE;
	z = z < 0 ? std::floor(z / (float)CHUNK_SIZE) : z / CHUNK_SIZE;
	return
	{
		(int) x ,
		(int) z
	};
}