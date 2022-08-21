#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "../Block/ChunkBlock.h"
#include "../Block/BlockData.h"
#include "ChunkMesh.h"
#include "ChunkSection.h"


class ChunkMeshBuilder
{
public:

    ChunkMeshBuilder(ChunkSection& chunk,ChunkMeshCollection& meshes);
    void buildMesh();

private:
    void setActiveMesh(ChunkBlock block);
    void tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
        const sf::Vector2i& textureCoords,
        const sf::Vector3i& blockPosition,
        const sf::Vector3i& blockFacing,
        GLfloat cardinalLight);
    void addXBlockToMesh(const sf::Vector2i& textureCoords,
        const sf::Vector3i& blockPosition);
    bool shouldMakeFace(const sf::Vector3i& blockPosition,
        const BlockDataHolder& blockData);
    bool shouldMakeLayer(int y);

    ChunkMeshCollection* m_pMeshes = nullptr;
    ChunkMesh* m_pActiveMesh = nullptr;
    ChunkSection* m_pChunk  = nullptr;
    const BlockDataHolder* m_pBlockData = nullptr;
};