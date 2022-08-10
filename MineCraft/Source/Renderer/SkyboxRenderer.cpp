#include "SkyboxRenderer.h"
#include "../Camera.h"
#include <iostream>

SkyboxRenderer::SkyboxRenderer()
{
	constexpr GLfloat SIZE = 500;
    //方向错误，玩家在box内 注意展开顺序
    std::vector<GLfloat> vertexCoords
    {
        //Back
         SIZE, -SIZE, -SIZE,
        -SIZE, -SIZE, -SIZE,
        -SIZE,  SIZE, -SIZE,
         SIZE,  SIZE, -SIZE,

         //Front
         -SIZE, -SIZE, SIZE,
          SIZE, -SIZE, SIZE,
          SIZE,  SIZE, SIZE,
         -SIZE,  SIZE, SIZE,

         //Right
         SIZE, -SIZE,  SIZE,
         SIZE, -SIZE, -SIZE,
         SIZE,  SIZE, -SIZE,
         SIZE,  SIZE,  SIZE,

         //Left
         -SIZE, -SIZE, -SIZE,
         -SIZE, -SIZE,  SIZE,
         -SIZE,  SIZE,  SIZE,
         -SIZE,  SIZE, -SIZE,

         //Top
         -SIZE, SIZE,  SIZE,
          SIZE, SIZE,  SIZE,
          SIZE, SIZE, -SIZE,
         -SIZE, SIZE, -SIZE,

         //Bottom
         -SIZE, -SIZE, -SIZE,
          SIZE, -SIZE, -SIZE,
          SIZE, -SIZE,  SIZE,
         -SIZE, -SIZE,  SIZE,
    };

    std::vector<GLuint> indices
    {
        0, 3 ,2,
        2, 1, 0,

        4, 7, 6,
        6, 5, 4,

        8, 11, 10,
        10, 9, 8,

        12, 15, 14,
        14, 13, 12,

        16, 19, 18,
        18, 17, 16,

        20, 23, 22,
        22, 21, 20
    };
    m_skyCube.genVAO();
    m_skyCube.addVBO(3, vertexCoords);
    m_skyCube.addEBO(indices);
    m_cubeTexture.loadFromFiles({
        "right","left","top","bottom","back","front"
        });
}

void SkyboxRenderer::render(const Camera& camera)
{
    m_shader.useProgram();
    m_skyCube.bindVAO();
    m_cubeTexture.bindTexture();
    m_shader.loadViewMatrix(camera.getViewMatrix());
    m_shader.loadProjectionMatrix(camera.getProjMatrix());
    GL::drawElements(m_skyCube.getIndicesCount());
}