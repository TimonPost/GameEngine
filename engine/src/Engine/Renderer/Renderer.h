#pragma once
namespace Engine
{
	enum class RendererAPI
	{
		None = 0, OpenGL = 1,
	};

	class Renderer
	{
	public:
		static RendererAPI RenderAPI;
	};
}
