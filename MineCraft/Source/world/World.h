#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>

#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"
#include "Event/IWorldEvent.h"

class RenderMaster;
class Camera;
class Entity;

class World
{
public:
	World(const Camera& camera);
	//~World();
	ChunkBlock getBlock(int x, int y, int z) ;
	bool setBlock(int x, int y, int z, ChunkBlock block);
	void update(const Camera& camera);
	void updateChunk(int blockX, int blockY, int blockZ);
	void renderWorld(RenderMaster& master,const Camera& camera);
	ChunkManager& getChunkManager();
	static VectorXZ getBlockXZ(int x, int z);
	static VectorXZ getChunkXZ(int x, int z);
	static VectorXZ getChunkXZ(float x, float z);
	template<typename T,typename... Args>
	void addEvent(Args&&... args)
	{
		m_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	void collisionTest(Entity& entity);
private:
	void updateChunks();
	void loadChunks(const Camera& camera);
	std::vector<std::unique_ptr<IWorldEvent>> m_events;
	std::unordered_map<sf::Vector3i, ChunkSection*> m_chunkUpdates;
	ChunkManager m_chunkManager;

	//std::atomic<bool> m_running{ true };
	//std::thread m_thread;

	int m_loadDistance = 2;
	VectorXZ minRenderPosition;
	VectorXZ maxRenderPosition;
};