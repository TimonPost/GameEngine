#pragma once

#include "Engine/Core.h"
#include "Event/Event.h"

namespace Engine
{
	class ENGINE_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnImGuiRender() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};
		const std::string& GetName() const;

	protected:
		std::string DebugName;
		
	};


	
}
