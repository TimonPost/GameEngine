#pragma once
#include "Engine/Buffers/IndexBuffer.h"

namespace Engine
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	private:
		unsigned int _indexBufferId{};
		unsigned int _count;

	public:
		OpenGLIndexBuffer(const unsigned int* data, unsigned int count);
				
		unsigned int GetCount() const override { return _count; }
		~OpenGLIndexBuffer() override;
		void Bind() override;
		void Unbind() override;
	};
}

