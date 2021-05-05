#pragma once
#include "epch.h"
#include "Engine/Window.h"
#include "Engine/Log.h"
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


	private:
		virtual void Init(const WindowProps&);
		virtual void Shutdown();
		private:
			GLFWwindow* _window{};

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
