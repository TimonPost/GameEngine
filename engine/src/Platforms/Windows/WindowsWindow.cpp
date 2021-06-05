#include "epch.h"
#include "WindowsWindow.h"

#include "Engine/Core/Core.h"
#include "Engine/Event/Event.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/Application.h"

#include "Platforms/OpenGl/OpenGLContext.h"

#include "Engine/Debug/Instrumentor.h"

namespace Engine
{
	bool glfwInitialized = false;

	static void glfwErrorCallback(int error, const char* description)
	{
		ENGINE_CORE_ERROR("GLFW Error ({0}): {1}", error, description)

	};
	
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		ENGINE_PROFILE_FUNCTION();
		
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ENGINE_PROFILE_FUNCTION();
		
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		ENGINE_PROFILE_FUNCTION();
		
		_data.Width = props.Width;
		_data.Height = props.Height;
		_data.Title = props.Title;
				
		ENGINE_CORE_INFO("Creating window {} ({}, {})", props.Title, props.Width, props.Height);

		if (!glfwInitialized)
		{
			int success;
			{
				ENGINE_PROFILE_SCOPE("glfwInit")
				success = glfwInit();
			}
			
			ENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(glfwErrorCallback);
			glfwInitialized = true;
		}

		{
			ENGINE_PROFILE_SCOPE("glfwCreateWindow")
			/* Create a windowed mode window and its OpenGL context */
			_window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), nullptr, nullptr);
		}
		
		_context = new OpenGLContext(_window);
		_context->Init();
		
		if (!_window)
		{
			glfwTerminate();
		}
		
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);
				
		glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});
		
		glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
				data.EventCallback(event);
			});
	}

	
	bool WindowsWindow::IsVSync() const
	{
		return _data.VSync;
	}
		
	void WindowsWindow::SetVSync(bool enabled)
	{
		ENGINE_PROFILE_FUNCTION();
		
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.VSync = enabled;
	}

	void WindowsWindow::Shutdown()
	{
		ENGINE_PROFILE_FUNCTION();
		
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		ENGINE_PROFILE_FUNCTION();
		
		glfwPollEvents();
		_context->SwapBuffers();
		
	}	
}
