#pragma once
#include "Log.h"

extern Engine::Application* Engine::CreateApplication();

#ifdef ENGINE_PLATFORM_WINDOWS 

int main(int argc, char** argv)
{
	Engine::Log::Init();

	ENGINE_CORE_ERROR("Test");
	ENGINE_WARN("Test");
	
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif