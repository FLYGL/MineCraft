#pragma once

#include <GL/glew.h>
#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "../Util/NonCopyable.h"

class CubeTexture : public NonCopyable
{
public:
	CubeTexture() = default;
	CubeTexture(const std::array<std::string, 6>& files);
	~CubeTexture();
	// order: right left top bottom front
	void loadFromFiles(const std::array<std::string, 6>& files);
	void bindTexture() const;
private:
	GLuint m_texId;
};
