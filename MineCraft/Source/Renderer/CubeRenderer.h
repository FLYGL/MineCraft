#pragma once
#include <vector>

#include "../Model.h"
#include "../Maths/glm.h"
#include "../Shaders/BasicShader.h"
#include "../Texture/BasicTexture.h"
#include "../Texture/TextureAtlas.h"
#include "../Entity.h"
class Camera;

class CubeRenderer
{
public:
	CubeRenderer();
	void add(const Entity& entity);
	void render(const Camera& camera);
private:
	std::vector<const Entity*> m_cubes;
	Model m_cubeModel;
	BasicShader m_shader;
	BasicTexture m_basicTexture;
	TextureAtlas m_atlasTest;
};