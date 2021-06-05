#pragma once
#include <utility>

#include "epch.h"
#include "Engine/Core/Core.h"
#include "Engine/Event/Event.h"

namespace Engine {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(std::string title = "Engine", unsigned int width = 1280, unsigned int height = 720) : Title(
			std::move(title)), Width(width), Height(height)
		{			
		}
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallbackVSync(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		
		virtual void* GetNativeWindow() const = 0;
	
	
		static Window* Create(const WindowProps& props = WindowProps());
	};
}
