#include "Context.h"
#include <GL/glew.h>

//KeyPoint : init sfml and glew  context
Context::Context()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;
	settings.stencilBits = 8;

	window.create({ 1280,720 }, "MineCraft", sf::Style::Close, settings);

	glewInit();
	glewExperimental = GL_TRUE;
	glViewport(0, 0, 1280, 720);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CCW);
	//window.setFramerateLimit(144);
	//window.setVerticalSyncEnabled(true);
}