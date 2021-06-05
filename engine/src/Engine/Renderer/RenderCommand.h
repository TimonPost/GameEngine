#pragma once
#include "RendererAPI.h"

namespace Engine
{
	class RenderCommand
	{
	public:
		void static DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			_rendererAPI->DrawIndexed(vertexArray);
		}

		static void Clear()
		{
			_rendererAPI->Clear();
		}
		
		static void SetClearColor(const glm::vec4& color)
		{
			_rendererAPI->SetClearColor(color);
		}

		static void SetViewPort(int x, int y, unsigned width, unsigned height)
		{
			_rendererAPI->SetViewPort(x, y, width, height);
		}
		
		inline static void Init()
		{
			_rendererAPI->Init();
		}

	
	
	private:
		static RendererAPI* _rendererAPI;
	};
}
