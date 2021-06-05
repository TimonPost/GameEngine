#include "epch.h"
#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		ENGINE_PROFILE_FUNCTION();
		
		glGenBuffers(1, &_registerId);
		glBindBuffer(GL_ARRAY_BUFFER, _registerId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, _registerId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &_registerId);
	}
}
