#include "epch.h"
#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(const unsigned int* data, unsigned int count)
	{
		ENGINE_PROFILE_FUNCTION();
		
		_count = count;

		if (_count != 0)
		{
			glGenBuffers(1, &_indexBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		if (_count != 0)
		{
			glDeleteBuffers(1, &_indexBufferId);
		}
	}

	void OpenGLIndexBuffer::Bind()
	{
		ENGINE_PROFILE_FUNCTION();
		
		if (_count != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferId);
		}
	}

	void OpenGLIndexBuffer::Unbind()
	{
		ENGINE_PROFILE_FUNCTION();
		
		if (_count != 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}
