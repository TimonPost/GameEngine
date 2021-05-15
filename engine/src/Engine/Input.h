#pragma once

#include "Core.h"

namespace Engine
{
	class ENGINE_API Input {
	public:
		static bool IsKeyPressed(int keyCode) { return _instance->IsKeyPressedImpl(keyCode); }

		static bool IsMouseButtonPressed(int button) { return _instance->IsMouseButtonPressedImpl(button); }

		static std::pair<float,float> GetMousePosition() { return _instance->GetMousePositionImpl(); }
		static bool GetMouseX() { return _instance->GetMouseXImpl(); }
		static bool GetMouseY() { return _instance->GetMouseYImpl(); }
		
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int keyCode) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* _instance;
	};
}
