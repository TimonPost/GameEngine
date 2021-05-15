#include "epch.h"
#include "VertexArray.h"

#include "Engine/Renderer/Renderer.h"
#include "Platforms/OpenGl/OpenGLVertexArray.h"

namespace  Engine
{
	VertexArray* VertexArray::Create(float* vertices, uint32_t size)
	{
		switch (Engine::Renderer::RenderAPI)
		{
		case Engine::RendererAPI::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case Engine::RendererAPI::OpenGL:
			return new Engine::OpenGLVertexArray();
		}
	}
}
