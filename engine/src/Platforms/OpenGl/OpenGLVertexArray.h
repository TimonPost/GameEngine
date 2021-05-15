#pragma once
#include "Engine/Buffers/VertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;
		void AddBuffer(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<VertexBufferLayout>& layout) const override;
		~OpenGLVertexArray() override;
	private:
		unsigned int _registerId = -1;
	};
}
