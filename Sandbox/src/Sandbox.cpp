#include <Engine.h>

#include "../../engine/vendor/imgui/imgui.h"

#include "Platforms/OpenGl/OpenGLShader.h"

// ---- entry point ----
#include "Engine/Core/EntryPoint.h"

using namespace Engine;

class ExampleLayer : public Layer
{
public:
	
	ExampleLayer() : Layer("Example")
	{
		
	}

	void OnImGuiRender() override
	{
	
	}
	
	void OnUpdate(Timestep timestep) override
	{
		
	}
		
	void OnEvent(Event& e) override
	{
		
	}
	
private:
};

class EngineEditor: public Application
{
	
public:
	EngineEditor(): Application()
	{
		//PushLayer(new ExampleLayer());
		//PushLayer(new EditorLayer());
	}

	~EngineEditor() {

	};
};

Application* Engine::CreateApplication() {
	return new EngineEditor();
}