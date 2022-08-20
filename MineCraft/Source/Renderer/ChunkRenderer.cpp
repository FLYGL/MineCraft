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
	if (m_chunks.empty())return;
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	m_shader.useProgram();
	BlockDatabase::get().textureAtlas.bindTexture();
	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	for (const ChunkMesh* mesh : m_chunks)
	{
		const ChunkMesh& m = *mesh;
		m.getModel().bindVAO();
		GL::drawElements(m.getModel().getIndicesCount());
	}
	m_chunks.clear();
}
