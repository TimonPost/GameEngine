#pragma once

#include "Engine/Core/Timestep.h"
#include "Engine/Core/Core.h"
#include "Engine/Event/Event.h"

namespace Engine
{
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnImGuiRender() {};
		virtual void OnUpdate(Timestep timestep) {};
		virtual void OnEvent(Event& event) {};
		const std::string& GetName() const;

	protected:
		std::string DebugName;
		
	};


	
}
