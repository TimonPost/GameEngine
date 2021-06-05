#include "epch.h"
#include "VertexArray.h"

#include "Engine/Renderer/Renderer.h"
#include "Platforms/OpenGl/OpenGLVertexArray.h"

namespace  Engine
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		return nullptr;
	}
}
