#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string& textureFileName)
{
	sf::Image i;
	if (!i.loadFromFile("Res/Textures/" + textureFileName + ".png"))
	{
		throw std::runtime_error("Unable to open image: " + textureFileName);
	}
	loadFromImage(i);

	m_imageSize = 256;
	m_individualTextureSize = 16;
}

//TODO : static 变量 存储区域 生命周期
std::vector<GLfloat> TextureAtlas::getTexture(const sf::Vector2i& coords)
{
	static const GLfloat TEX_PER_ROW = (GLfloat)m_imageSize / (GLfloat)m_individualTextureSize;
	static const GLfloat INDV_TEX_SIZE = 1.f / TEX_PER_ROW;
	static const GLfloat PIXEL_SIZE = 1.f / (float)m_imageSize;

	GLfloat xMin = (coords.x * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;
	GLfloat yMin = (coords.y * INDV_TEX_SIZE) + 0.5f * PIXEL_SIZE;

	GLfloat xMax = (xMin + INDV_TEX_SIZE) - 0.5f * PIXEL_SIZE;
	GLfloat yMax = (yMin + INDV_TEX_SIZE) - 0.5f * PIXEL_SIZE;

	return {
		xMin,yMax,
		xMax,yMax,
		xMax,yMin,
		xMin,yMin,
	};
}