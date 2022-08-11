#include "World.h"
#include "../Renderer/RenderMaster.h"
#include "../Maths/Vector2XZ.h"
#include "../Camera.h"

namespace
{
	constexpr int temp_worldSize = 16;
	constexpr int renderDistance = 8;
	bool isOutOfBounds(const VectorXZ& chunkPos)
	{
		if (chunkPos.x < 0) return true;
		if (chunkPos.z < 0) return true;
		if (chunkPos.x >= temp_worldSize) return true;
		if (chunkPos.z >= temp_worldSize) return true;
		return false;
	}
}

World::World():m_chunkManager(*this)
{
	
}

bool World::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (y <= 0) return false;
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	if (isOutOfBounds(cp))
	{
		//return false;
	}
	return m_chunkManager.getChunk(cp.x, cp.z).setBlock(bp.x, y, bp.z, block);
}

ChunkBlock World::getBlock(int x, int y, int z)
{
	auto bp = getBlockXZ(x, z);
	auto cp = getChunkXZ(x, z);
	if (isOutOfBounds(cp))
	{
		//return BlockId::Air;
		//不返回，生成新的区域块，新的块只有位置信息。 没有load（没有地形以及面的信息），没有申请GPU buffer。
	}
	return m_chunkManager.getChunk(cp.x,cp.z).getBlock(bp.x, y, bp.z);
}

void World::update(const Camera& camera)
{
	for (auto& event : m_events)
	{
		event->handle(*this);
	}
	m_events.clear();
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
			if (!m_chunkManager.chunkLoadedAt(x, z))
			{
				m_chunkManager.loadChunk(x, z);
			}
			if (m_chunkManager.makeMesh(x, z)) return;
		}
	}
}

void World::renderWorld(RenderMaster& renderer)
{
	//auto& chunkMap = m_chunkManager.getChunks();
	//for (auto& chunk : chunkMap)
	//{
	//	chunk.second.drawChunks(renderer);
	//}
	for (int x = minRenderPosition.x; x < maxRenderPosition.x; x++)
	{
		for (int z = minRenderPosition.z; z < maxRenderPosition.z; z++)
		{
			auto& chunk = m_chunkManager.getChunk(x, z);
			chunk.drawChunks(renderer);
		}
	}
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