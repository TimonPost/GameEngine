#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Clear() override;
		void SetClearColor(const glm::vec4& color) override;
		void SetViewPort(int i, int y, unsigned width, unsigned height) override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		void Init() override;
	};	
}
