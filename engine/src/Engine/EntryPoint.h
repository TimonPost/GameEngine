#pragma once
#include "Log.h"

extern Engine::Application* Engine::CreateApplication();

#ifdef ENGINE_PLATFORM_WINDOWS 

int main(int argc, char** argv)
{
	Engine::Log::Init();
	
	auto app = Engine::CreateApplication();
	app->Run();
	delete app;
}

#endif