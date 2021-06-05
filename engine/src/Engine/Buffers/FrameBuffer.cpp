#include "epch.h"
#include "FrameBuffer.h"

#include "Engine/Renderer/Renderer.h"
#include "Platforms/OpenGl/OpenGLFrameBuffer.h"

namespace Engine
{
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(specification);
		}

		return nullptr;
	}


}