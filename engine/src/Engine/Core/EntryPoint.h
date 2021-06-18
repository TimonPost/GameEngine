#pragma once
#include "Log.h"
#include "Engine/Debug/Instrumentor.h"

extern Engine::Application* Engine::CreateApplication();

#ifdef ENGINE_PLATFORM_WINDOWS 

int main(int argc, char** argv)
{
	Engine::Log::Init();

	ENGINE_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
	auto app = Engine::CreateApplication();
	ENGINE_PROFILE_END_SESSION();
	
	ENGINE_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");	
	app->Run();
	ENGINE_PROFILE_END_SESSION();
	

	
	delete app;
}

#endif