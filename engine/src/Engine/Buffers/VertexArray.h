#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace Engine
{

	/// <summary>
	/// Abstraction for the opengl vertex array.
	/// </summary>
	class VertexArray
	{
	public:
		VertexArray() {};

		virtual VertexArray* Create(float* vertices, uint32_t size);
		
		/// <summary>
		/// Adds a buffer and a layout to this vertex array.
		/// </summary>
		/// <param name="vb"></param>
		/// <param name="layout"></param>
		virtual void AddBuffer(std::shared_ptr<Engine::VertexBuffer>& vb, std::shared_ptr<VertexBufferLayout>& layout) const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual ~VertexArray() = 0;
	};
}