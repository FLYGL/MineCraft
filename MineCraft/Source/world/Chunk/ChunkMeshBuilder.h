#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

class ChunkSection;
class ChunkMesh;
class BlockData;
class BlockDataHolder;

class ChunkMeshBuilder
{
public:

    ChunkMeshBuilder(ChunkSection& chunk,ChunkMesh& mesh);
    void buildMesh();

private:

    void tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
        const sf::Vector2i& textureCoords,
        const sf::Vector3i& blockPosition,
        const sf::Vector3i& blockFacing);
    bool shouldMakeFace(const sf::Vector3i& blockPosition,
        const BlockDataHolder& blockData);
    bool shouldMakeLayer(int y);

    ChunkMesh* m_pMesh = nullptr;
    ChunkSection* m_pChunk  = nullptr;
    const BlockDataHolder* m_pBlockData = nullptr;
};