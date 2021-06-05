
#include "epch.h"
#include "Layer.h"

namespace Engine
{
	Layer::Layer(const std::string& name) : DebugName(name)
	{
		
	}

	Layer::~Layer()
	{
		
	}

	const std::string& Layer::GetName() const
	{
		return DebugName;
	}
}
