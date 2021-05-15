#pragma once
#include "Engine/Buffers/VertexBuffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);				
		void Bind() const override;
		void Unbind() const override;

		void SetBufferLayout(const VertexBufferLayout& layout) override { _layout = layout; }
		const VertexBufferLayout& GetLayout() const override { return _layout; }

		~OpenGLVertexBuffer() override;
	private:
		unsigned int _registerId = -1;
		VertexBufferLayout _layout;
	};	
}
