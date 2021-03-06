#pragma once
#include "epch.h"
#include "Engine/Core/Window.h"
#include "Engine/Renderer/GraphicsContext.h"
#include "Engine/Core/Log.h"
#include "GLFW/glfw3.h"

namespace Engine {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();
		void OnUpdate() override;
		unsigned GetWidth() const override { return _data.Width; }
		unsigned GetHeight() const override { return _data.Height; }
		void SetEventCallbackVSync(const EventCallbackFn& callback) override
		{
			_data.EventCallback = callback;
		}
		
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override
		{
			return _window;
		}
	private:
		
		virtual void Init(const WindowProps&);
		virtual void Shutdown();
		GLFWwindow* _window;
		GraphicsContext* _context;
		
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData _data;
	};
}
