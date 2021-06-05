#include <Engine.h>

#include "EditorLayer.h"
#include "../../engine/vendor/imgui/imgui.h"

#include "Platforms/OpenGl/OpenGLShader.h"

// ---- entry point ----
#include "Engine/Core/EntryPoint.h"

using namespace Engine;

class EngineEditor: public Application
{
	
public:
	EngineEditor(): Application("Engine Editor")
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new EditorLayer());
	}

	~EngineEditor() {

	};
};

Application* Engine::CreateApplication() {
	return new EngineEditor();
}