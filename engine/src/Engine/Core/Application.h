#pragma once

#include "epch.h"
#include "Core.h"
#include "Layer.h"
#include "Window.h"
#include "LayerStack.h"
#include "Log.h"
#include "Engine/Core/Timestep.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Renderer/OrthographicCamera.h"

namespace Engine {
	class  Application
	{
	private:
		std::unique_ptr<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _isRunning = true;
		LayerStack _layerStack;
		bool _minimized;
		static Application* instance;
		Timestep _time;
		float _lastFrameTime = 0.0f;
	public:

		static Application& Instance() { return *instance; }	
		
		Application();
		~Application();
		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);

		inline Window& GetWindow() { return *_window; }
	};

	Application* CreateApplication();
}

