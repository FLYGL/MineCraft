#pragma once

#include <vector>
#include <memory>

#include "Chunk/Chunk.h"
#include "Chunk/ChunkManager.h"
#include "Event/IWorldEvent.h"

class RenderMaster;
class Camera;
class World
{
public:
	World();
	ChunkBlock getBlock(int x, int y, int z) ;
	bool setBlock(int x, int y, int z, ChunkBlock block);
	void update(const Camera& camera);
	void renderWorld(RenderMaster& master);

	const ChunkManager& getChunkManager() const;
	static VectorXZ getBlockXZ(int x, int z);
	static VectorXZ getChunkXZ(int x, int z);
	static VectorXZ getChunkXZ(float x, float z);
	template<typename T,typename... Args>
	void addEvent(Args&&... args)
	{
		m_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
private:
	std::vector<std::unique_ptr<IWorldEvent>> m_events;
	ChunkManager m_chunkManager;
	VectorXZ minRenderPosition;
	VectorXZ maxRenderPosition;
};