#include "WaterRenderer.h"

#include "../world/Chunk/ChunkMesh.h"
#include "../world/Block/BlockDatabase.h"

#include "../Camera.h"
#include <iostream>

void WaterRenderer::add(const ChunkMesh& mesh)
{
	m_chunks.push_back(&mesh);
}

void WaterRenderer::render(const Camera& camera)
{
	if (m_chunks.empty()) return;
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	m_shader.useProgram();
	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	m_shader.addTime(m_timer.getElapsedTime().asSeconds());
	for (const auto& mesh : m_chunks)
	{
		const ChunkMesh& m = *mesh;
		m.getModel().bindVAO();
		GL::drawElements(m.getModel().getIndicesCount());
	}
	m_chunks.clear();
}