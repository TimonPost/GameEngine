#include <Engine.h>

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		
	}
};

class SandboxApplication: public Engine::Application
{
public:
	SandboxApplication(): Application()
	{
		PushLayer(new ExampleLayer());
	}

	~SandboxApplication() {

	};
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApplication();
}