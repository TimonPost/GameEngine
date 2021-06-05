#pragma once

#include "IndexBuffer.h"
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
		static Ref<VertexArray> Create();
		
		/// <summary>
		/// Adds a buffer and a layout to this vertex array.
		/// </summary>
		/// <param name="vb"></param>
		/// <param name="layout"></param>
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vb) = 0;
		virtual void SetIndexBuffer(const  Ref<IndexBuffer>& ib) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		virtual void SetLayout(const VertexBufferLayout& layout) = 0;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual ~VertexArray(){}
	};
}