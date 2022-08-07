#pragma once

#include <vector>

#include "../Shaders/ChunkShader.h"
#include "../world/Chunk/ChunkMesh.h"
#include "../Camera.h"

class ChunkRenderer
{
public:
	void add(const ChunkMesh& mesh);
	void render(const Camera& camera);
private:
	std::vector<const ChunkMesh*> m_chunks;
	ChunkShader m_shader;
};