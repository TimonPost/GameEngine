#include "epch.h"
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count)
	{
		_count = count;

		if (_count != 0)
		{
			glGenBuffers(1, &_indexBufferId);
			IndexBuffer::Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
			IndexBuffer::Unbind();
		}
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		if (_count != 0)
		{
			glDeleteBuffers(1, &_indexBufferId);
		}
	}

	void OpenGLIndexBuffer::Bind() const
	{
		if (_count != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
		}
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		if (_count != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
