#pragma once
#include <Engine/Buffers/VertexBufferLayout.h>

namespace Engine {
	/// <summary>
	/// Abstraction for the opengl vertex buffer.
	/// </summary>
	class VertexBuffer
	{
	public:
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetBufferLayout(const VertexBufferLayout& layout) = 0;
		virtual const VertexBufferLayout& GetLayout() const = 0;

		virtual ~VertexBuffer() {}
	};
}
