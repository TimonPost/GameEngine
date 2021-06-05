#include "epch.h"
#include "Texture.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platforms/OpenGl/OpenGLTexture2D.h"

namespace Engine {


	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(path);
		}
	}

	Ref<Texture2D> Texture2D::Create(unsigned width, unsigned height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height);
		}
	}
}
