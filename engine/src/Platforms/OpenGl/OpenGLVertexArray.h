#pragma once
#include "Engine/Buffers/IndexBuffer.h"
#include "Engine/Buffers/VertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;
			
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb) override;
		void SetIndexBuffer(const  std::shared_ptr<IndexBuffer>& ib) override;
		void SetLayout(const VertexBufferLayout& layout) override;
		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override;
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;
		
		~OpenGLVertexArray() override;
		
	private:
		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;
		
		unsigned int _registerId = -1;
	};
}
