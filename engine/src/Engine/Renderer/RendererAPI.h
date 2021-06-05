#pragma once
#include "Engine/Buffers/VertexArray.h"
#include "glm/glm.hpp"

namespace Engine
{
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;
		virtual void Init() = 0;
		virtual void SetViewPort(int i, int y, unsigned width, unsigned height) = 0;

		enum class API
		{
			None = 0,
			OpenGL = 2,
		};

		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;		
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return _api; }
	
	private:
		static API _api;
	};
}
