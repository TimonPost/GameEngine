#include "epch.h"
#include "VertexBuffer.h"

#include "IndexBuffer.h"
#include "Engine/Core.h"
#include "Engine/Log.h"
#include "Engine/Renderer/Renderer.h"
#include "Platforms/OpenGl/OpenGLVertexBuffer.h"

namespace Engine {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::RenderAPI)
		{
		case RendererAPI::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		return nullptr;
	}

}
