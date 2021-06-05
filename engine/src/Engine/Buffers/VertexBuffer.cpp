#include "epch.h"
#include "VertexBuffer.h"

#include "Engine/Core/Core.h"
#include "Engine/Core/Log.h"
#include "Engine/Renderer/Renderer.h"
#include "Platforms/OpenGl/OpenGLVertexBuffer.h"

namespace Engine {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		return nullptr;
	}

}
