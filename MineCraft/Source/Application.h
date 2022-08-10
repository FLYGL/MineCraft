#pragma once
#include <vector>
#include <memory>

#include "States/StateBase.h"
#include "Renderer/RenderMaster.h"

#include "Context.h"
#include "Camera.h"

class Application
{
public:
	//KeyPoint : stringbuf
	Application(const char* name);

	void runLoop();
	//What mean : new usage?
	template<typename T, typename... Args>
	void pushState(Args&&... args)
	{
		//What mean: forward?
		m_states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		auto& s = m_states.back();
		s->onOpen();
	}
	void popState();
	void turnOffMouse();
	void turnOnMouse();
	Camera& getCamera() { return m_camera; }

	const sf::RenderWindow& getWindow() const { return m_context.window; }
private:
	void handleEvents();

	std::vector<std::unique_ptr<StateBase>> m_states;

	Context m_context;
	RenderMaster m_masterRenderer;
	Camera m_camera;

	bool m_isPopState = false;
};