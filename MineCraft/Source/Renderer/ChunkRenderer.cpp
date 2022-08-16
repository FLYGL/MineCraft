#include <iostream>
#include "ChunkRenderer.h"
#include "../world/Block/BlockDatabase.h"
#include "../Debug/Debug.h"

void ChunkRenderer::add(const ChunkMesh& mesh)
{
	m_chunks.push_back(&mesh);
}

void ChunkRenderer::render(const Camera& camera)
{
	m_shader.useProgram();
	BlockDatabase::get().textureAtlas.bindTexture();
	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	Debug::renderBlockNumbers = m_chunks.size();
	int tmp = 0;
	for (const ChunkMesh* mesh : m_chunks)
	{
		const ChunkMesh& m = *mesh;
		m.getModel().bindVAO();
		if (m.getModel().getIndicesCount() <= 0) {
			tmp++;
		}
		GL::drawElements(m.getModel().getIndicesCount());
	}
	Debug::noneIndicesNumbers = tmp;
	m_chunks.clear();
}
