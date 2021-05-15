#include "epch.h"
#include "Application.h"

#include "Input.h"
#include "glad/glad.h"
#include <Engine/Buffers/VertexBufferLayout.h>

namespace Engine {

	Application* Application::instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}

		ENGINE_ASSERT(false, "Can not convert shader data type to open gl base type for: {0}", type);
		return 0;
	}
	
	Application::Application()
	{
		ENGINE_ASSERT(!instance, "Instance already initialized")
		
		instance = this;		
				
		_window = std::unique_ptr<Window>(Window::Create());
		_window->SetEventCallbackVSync([this](auto&& PH1) { OnEvent(std::forward<decltype(PH1)>(PH1)); });
		_imGuiLayer = new ImGuiLayer();
		PushOverlay(_imGuiLayer);

		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);

		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

		float vertices[3 * 3]
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &_indeBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indeBuffer);

		unsigned int indices[3]
		{
			0,1,2
		};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		VertexBufferLayout layout = {
			{ShaderDataType::Float3, "position"},
			{ShaderDataType::Float4, "color"},
			{ShaderDataType::Float3, "normal"},
		};

		while (_isRunning)
		{
			glClearColor(0.1f, 0.1f, 0.1f,1);
			glClear(GL_COLOR_BUFFER_BIT);

		
			
			for (Layer* layer : _layerStack)
				layer->OnUpdate();			

			_imGuiLayer->Begin();

			for (Layer* layer : _layerStack)
				layer->OnImGuiRender();
			
			_imGuiLayer->End();
			
			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		ENGINE_CORE_INFO("{0}", event.ToString())

		EventDispatcher dispatcher(event);

		for (auto it = _layerStack.end(); it != _layerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}
