#include "epch.h"

#include "Engine/Core.h"
#include "WindowsWindow.h"

#include "GLFW/glfw3.h"

namespace Engine
{
	bool glfwInitialized = false;
	
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		_data.Width = props.Width;
		_data.Height = props.Height;
		_data.Title = props.Title;

		ENGINE_CORE_INFO("Creating window {} ({}, {})", props.Title, props.Width, props.Height);

		if (!glfwInitialized)
		{
			int success = glfwInit();
			ENGINE_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwInitialized = true;
		}

		/* Create a windowed mode window and its OpenGL context */
		_window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), nullptr, nullptr);

		if (!_window)
		{
			glfwTerminate();
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);
	}

	
	bool WindowsWindow::IsVSync() const
	{
		return _data.VSync;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.VSync = enabled;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(_window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}	
}
