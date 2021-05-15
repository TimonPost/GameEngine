#pragma once
#include <Engine/Buffers/VertexBufferLayout.h>

namespace Engine {
	/// <summary>
	/// Abstraction for the opengl vertex buffer.
	/// </summary>
	class VertexBuffer
	{
	public:
		VertexBuffer() {}

		VertexBuffer* Create(float* vertices, uint32_t size);
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void SetBufferLayout(const VertexBufferLayout& layout) = 0;
		virtual const VertexBufferLayout& GetLayout() const = 0;

		virtual virtual ~VertexBuffer();
	};
}
