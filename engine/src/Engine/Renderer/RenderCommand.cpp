#include "epch.h"
#include "RenderCommand.h"
#include "Platforms/OpenGl/OpenGLRendererAPI.h"

namespace Engine
{
	RendererAPI* RenderCommand::_rendererAPI = new OpenGLRendererAPI();
}
