#include <Engine.h>
#include "Engine.h"

class SandboxApplication: public Engine::Application
{
public:
	SandboxApplication(): Application()
	{
	}

	~SandboxApplication() {

	};
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApplication();
}