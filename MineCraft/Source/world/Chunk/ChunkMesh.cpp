#include "ChunkMesh.h"
#include "../WorldConstants.h"
ChunkMesh::ChunkMesh()
{

}
void ChunkMesh::addFace(const std::vector<GLfloat>& blockFace,
	const std::vector<GLfloat>& textureCoords,
	const sf::Vector3i& chunkPosition,
	const sf::Vector3i& blockPosition)
{
	faces++;
	auto& verticies = m_mesh.vertexPositions;
	auto& texCoords = m_mesh.textureCoords;
	auto& indices = m_mesh.indices;

	texCoords.insert(texCoords.end(), textureCoords.begin(), textureCoords.end());
	for (int vertexNumber = 0, index = 0; vertexNumber < 4; vertexNumber++)
	{
		verticies.push_back(blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x);
		verticies.push_back(blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y);
		verticies.push_back(blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z);
	}

	indices.insert(indices.end(),
		{
			m_indexIndex,
			m_indexIndex + 1,
			m_indexIndex + 2,

			m_indexIndex + 2,
			m_indexIndex + 3,
			m_indexIndex
		});
	m_indexIndex += 4;
}

void ChunkMesh::bufferMesh()
{
	m_model.addData(m_mesh);
	m_mesh.vertexPositions.clear();
	m_mesh.textureCoords.clear();
	m_mesh.indices.clear();
	m_mesh.vertexPositions.shrink_to_fit();
	m_mesh.textureCoords.shrink_to_fit();
	m_mesh.indices.shrink_to_fit();
	m_indexIndex = 0;
}

const Model& ChunkMesh::getModel() const
{
	return m_model;
}