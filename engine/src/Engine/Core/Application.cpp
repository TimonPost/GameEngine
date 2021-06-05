#include "epch.h"
#include "Application.h"

#include "Input.h"
#include "glad/glad.h"
#include <Engine/Buffers/VertexBufferLayout.h>

#include "GLFW/glfw3.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Renderer.h"

namespace Engine {

	Application* Application::instance = nullptr;
	
	Application::Application()
	{
		ENGINE_PROFILE_FUNCTION();
		
		ENGINE_ASSERT(!instance, "Instance already initialized")
		
		instance = this;		
				
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallbackVSync([this](auto&& PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); });

		Renderer::Init();
		
		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		ENGINE_PROFILE_FUNCTION();
		
		while (_isRunning)
		{
			ENGINE_PROFILE_SCOPE("Main Game Loop");
			
			float time = (float)glfwGetTime();
			Timestep timeStep = time - _lastFrameTime;
			_lastFrameTime = time;

			if (!_minimized) {

				{
					ENGINE_PROFILE_SCOPE("Update Layer Stack ");
					for (Layer* layer : _layerStack)
						layer->OnUpdate(timeStep);
				}
			}

			_imGuiLayer->Begin();
			{
				ENGINE_PROFILE_SCOPE("Update IMGU LayerStack");			

				for (Layer* layer : _layerStack)
					layer->OnImGuiRender();			
			}
			
			_imGuiLayer->End();
			
			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		ENGINE_PROFILE_FUNCTION();
		
		ENGINE_CORE_INFO("{0}", event.ToString())

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND(Application::OnWindowResize));
		
		for (auto it = _layerStack.end(); it != _layerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		ENGINE_PROFILE_FUNCTION();
		
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		ENGINE_PROFILE_FUNCTION();
		
		_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		ENGINE_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			_minimized = true;
			return false;
		}
		_minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		_isRunning = false;
		return true;
	}
}
