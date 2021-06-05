#include "epch.h"
#include "IndexBuffer.h"
#include "Platforms/OpenGl/OpenGLIndexBuffer.h"
#include "Engine/Renderer/Renderer.h"


namespace Engine {
	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indicies, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indicies, size);
		}

		return nullptr;
	}
}

