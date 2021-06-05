#include "epch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Engine
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		ENGINE_PROFILE_FUNCTION();
		
		glGenVertexArrays(1, &_registerId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_registerId);
	}
	
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3: return GL_FLOAT;
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Int2: return GL_INT;
		case ShaderDataType::Int3: return GL_INT;
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}

		ENGINE_ASSERT(false, "Can not convert shader data type to open gl base type for: {0}", type);
		return 0;
	}

	void OpenGLVertexArray::Bind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindVertexArray(_registerId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vb)
	{
		Bind();
		vb->Bind();

		unsigned int index = 0;
		const auto& layout = vb->GetLayout();
		
		for(const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		_vertexBuffers.push_back(vb);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
	{
		Bind();
		ib->Bind();
		
		_indexBuffer = ib;
	}

	void OpenGLVertexArray::SetLayout(const VertexBufferLayout& layout)
	{
		
	}

	const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return _vertexBuffers;
	}

	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return _indexBuffer;
	}
}

