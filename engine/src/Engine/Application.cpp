#include "epch.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Engine {
	Application::Application()
	{
		_window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (_isRunning)
		{
			glClearColor(1,0,1,1);
			glClear(GL_COLOR_BUFFER_BIT);
			_window->OnUpdate();
		}
	}
}
