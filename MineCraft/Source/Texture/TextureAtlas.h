#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BasicTexture.h"

class TextureAtlas : public BasicTexture
{
public:
	TextureAtlas(const std::string& textureFileName);
	std::vector<GLfloat> getTexture(const sf::Vector2i& coords);
private:
	int m_imageSize;
	int m_individualTextureSize;
};