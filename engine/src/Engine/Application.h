#pragma once

#include "epch.h"
#include "Core.h"

namespace Engine {
	class ENGINE_API Application
	{
	public:
		Application();
		~Application();
		void Run();
	};

	Application* CreateApplication();
}

