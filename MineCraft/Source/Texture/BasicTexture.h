#pragma once
#include <GL/glew.h>
#include <string>
#include "../Util/NonCopyable.h"
#include <SFML/Graphics.hpp>

class BasicTexture : public NonCopyable
{
public:
	BasicTexture() = default;
	BasicTexture(const std::string& file);

	~BasicTexture();

	void loadFromFile(const std::string& file);
	void loadFromImage(const sf::Image& image);
	void bindTexture() const;
private:
	GLuint m_id;
};