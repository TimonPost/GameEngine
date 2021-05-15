#include "epch.h"
#include "IndexBuffer.h"

#include "epch.h"

#include "Engine/Core.h"
#include "Engine/Log.h"
#include "Engine/Renderer/Renderer.h"
#include "Platforms/OpenGl/OpenGLIndexBuffer.h"

namespace Engine {
	IndexBuffer* IndexBuffer::Create(unsigned int* indicies, uint32_t size)
	{
		switch (Renderer::RenderAPI)
		{
		case RendererAPI::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indicies, size);
		}

		return nullptr;
	}
}

