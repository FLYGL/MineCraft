#include <iostream>

#include "ChunkMeshBuilder.h"
#include "../Block/BlockDatabase.h"


namespace
{
    const std::vector<GLfloat> frontFace
    {
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
    };

    const std::vector<GLfloat> backFace
    {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
    };

    const std::vector<GLfloat> leftFace
    {
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,
    };

    const std::vector<GLfloat> rightFace
    {
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,
    };

    const std::vector<GLfloat> topFace
    {
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,
    };

    const std::vector<GLfloat> bottomFace
    {
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1
    };

    const std::vector<GLfloat> xFace1
    {
        0,0,0,
        1,0,1,
        1,1,1,
        0,1,0,
    };

    const std::vector<GLfloat> xFace2
    {
        0,0,1,
        1,0,0,
        1,1,0,
        0,1,1,
    };

    constexpr GLfloat LIGHT_TOP = 1.0f;
    constexpr GLfloat LIGHT_X = 0.8f;
    constexpr GLfloat LIGHT_Z = 0.6f;
    constexpr GLfloat LIGHT_BOT = 0.4f;
}


ChunkMeshBuilder::ChunkMeshBuilder(ChunkSection& chunk, ChunkMeshCollection& meshes) :
    m_pChunk(&chunk), m_pMeshes(&meshes)
{
}

struct AdjacentBlockPositions
{
    void update(int x, int y, int z)
    {
        up = { x , y + 1, z };
        down = { x, y - 1,z };
        left = { x - 1 , y, z };
        right = { x + 1 , y , z };
        front = { x , y ,  z + 1 };
        back = { x , y , z - 1 };
    }
    sf::Vector3i up;
    sf::Vector3i down;
    sf::Vector3i left;
    sf::Vector3i right;
    sf::Vector3i front;
    sf::Vector3i back;
};

int faces = 0;

void ChunkMeshBuilder::buildMesh()
{
    sf::Clock c;
    //std::cout << "Begin mesh build\n";
    AdjacentBlockPositions directions;
    for (int8_t y = 0; y < CHUNK_SIZE; ++y)
    {
        if (!shouldMakeLayer(y)) continue;
        for (int8_t x = 0; x < CHUNK_SIZE; ++x)
            for (int8_t z = 0; z < CHUNK_SIZE; ++z)
            {
                sf::Vector3i position(x, y, z);
                ChunkBlock block = m_pChunk->getBlock(x, y, z);
                setActiveMesh(block);
                if (block == BlockId::Air)
                {
                    continue;
                }

                m_pBlockData = &block.getData();
                auto& data = *m_pBlockData;

                if (data.meshType == BlockMeshType::X)
                {
                    addXBlockToMesh(data.texTopCoord, position);
                    continue;
                }

                directions.update(x, y, z);
                tryAddFaceToMesh(backFace, data.texSideCoord, position, directions.back,LIGHT_Z);
                tryAddFaceToMesh(frontFace, data.texSideCoord, position, directions.front, LIGHT_Z);
                tryAddFaceToMesh(rightFace, data.texSideCoord, position, directions.right,LIGHT_X);
                tryAddFaceToMesh(leftFace, data.texSideCoord, position, directions.left, LIGHT_X);
                tryAddFaceToMesh(topFace, data.texTopCoord, position, directions.up,LIGHT_TOP);
                tryAddFaceToMesh(bottomFace, data.texBottomCoord, position, directions.down,LIGHT_BOT);
            }
    }

    //std::cout << "End mesh build, faces: " << faces << " Time: " << c.getElapsedTime().asMilliseconds() << "ms\n";
}

void ChunkMeshBuilder::tryAddFaceToMesh(const std::vector<GLfloat>& blockFace,
    const sf::Vector2i& textureCoords,
    const sf::Vector3i& blockPosition,
    const sf::Vector3i& blockFacing,
    GLfloat cardinalLight)
{
    if (shouldMakeFace(blockFacing, *m_pBlockData))
    {
        faces++;
        auto texCoords = BlockDatabase::get().textureAtlas.getTexture(textureCoords);
        m_pActiveMesh->addFace(blockFace, texCoords, m_pChunk->getLocation(), blockPosition,cardinalLight);
    }
}

void ChunkMeshBuilder::addXBlockToMesh(const sf::Vector2i& textureCoords, const sf::Vector3i& blockPosition)
{
    faces++;
    auto texCoords = BlockDatabase::get().textureAtlas.getTexture(textureCoords);
    m_pActiveMesh->addFace(xFace1, texCoords, m_pChunk->getLocation(),
        blockPosition, LIGHT_X);
    m_pActiveMesh->addFace(xFace2, texCoords, m_pChunk->getLocation(),
        blockPosition, LIGHT_X);
}

bool ChunkMeshBuilder::shouldMakeFace(const sf::Vector3i& blockPosition,
    const BlockDataHolder& blockData)
{
    auto block = m_pChunk->getBlock(blockPosition.x, blockPosition.y, blockPosition.z);
    auto& data = block.getData();
    if (block == BlockId::Air) {
        return true;
    }
    //TODO : why
    else if((!data.isOpaque) && (data.id != m_pBlockData->id))
    {
        return true;
    }
    return false;
}

bool ChunkMeshBuilder::shouldMakeLayer(int y)
{
    auto adjIsSolid = [&](int dx, int dz)
    {
        const ChunkSection& section = m_pChunk->getAdjacent(dx, dz);
        return section.getLayer(y).isAllSolid();
    };
    return (!m_pChunk->getLayer(y).isAllSolid()) ||
        (!m_pChunk->getLayer(y + 1).isAllSolid()) ||
        (!m_pChunk->getLayer(y - 1).isAllSolid()) ||
        (!adjIsSolid(1, 0)) || (!adjIsSolid(0, 1)) || (!adjIsSolid(-1, 0)) || (!adjIsSolid(0, -1));
}

void ChunkMeshBuilder::setActiveMesh(ChunkBlock block)
{
    if (block.id == (int)BlockId::Water)
    {
        m_pActiveMesh = &m_pMeshes->waterMesh;
    }
    else
    {
        m_pActiveMesh = &m_pMeshes->solidMesh;
    }
}