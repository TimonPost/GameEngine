#pragma once

#include "Engine/Layer.h"
#include "Engine/Log.h"
#include "Engine/Event/Application.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

namespace Engine 
{
	class ENGINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
		void OnUpdate() override {};
		void OnEvent(Event& event) override {} ;
		float _time;
	};
}
