#pragma once

#include "epch.h"
#include "Core.h"
#include "Layer.h"
#include "Window.h"
#include "LayerStack.h"
#include "Log.h"
#include "ImGui/ImGuiLayer.h"

namespace Engine {
	class ENGINE_API Application
	{
	private:
		std::unique_ptr<Window> _window;
		ImGuiLayer* _imGuiLayer;
		bool _isRunning = true;
		LayerStack _layerStack;
		static Application* instance;

		unsigned int _vertexArray, _vertexBuffer, _indeBuffer;
		
	public:

		static Application& Instance() { return *instance; }	
		
		Application();
		~Application();
		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *_window; }
	};

	Application* CreateApplication();
}

