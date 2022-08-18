#pragma once

#include "../../Model.h"
#include <SFML/Graphics.hpp>
#include <vector>

class ChunkMesh
{
public:
	ChunkMesh();
	void addFace(const std::vector<GLfloat>& blockFace,
		const std::vector<GLfloat>& textureCoords,
		const sf::Vector3i& chunkPosition,
		const sf::Vector3i& blockPosition,
		GLfloat cardinalLight);
	void bufferMesh();
	const Model& getModel() const;

	int faces = 0;
private:
	Mesh m_mesh;
	Model m_model;
	GLuint m_indexIndex = 0;
	std::vector<GLfloat> m_light;
};