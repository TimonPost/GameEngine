#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Core/Log.h"
#include "Engine/Event/Application.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"

namespace Engine 
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
		void OnUpdate(Timestep timeStep) override {};
		void OnEvent(Event& event) override {} ;
		float _time;
	};
}
