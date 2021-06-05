#pragma once
#include "Engine/Core/Input.h"

namespace Engine {
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keyCode) override;
		virtual bool IsMouseButtonPressedImpl(int keyCode) override;
		virtual std::pair<float, float> GetMousePositionImpl();
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}