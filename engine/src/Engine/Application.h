#pragma once

#include "epch.h"
#include "Core.h"
#include "Window.h"

namespace Engine {
	class ENGINE_API Application
	{
	private:
		std::unique_ptr<Window> _window;
		bool _isRunning = true;

	public:
		Application();
		~Application();
		void Run();
	};

	Application* CreateApplication();
}

