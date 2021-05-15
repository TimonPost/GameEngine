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
		void Bind() const override;
		void Unbind() const override;
		unsigned int GetCount() const override { return _count; }
		~OpenGLIndexBuffer() override;
	};
}

