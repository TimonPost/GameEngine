#include "epch.h"
#include "OpenGLVertexArray.h"

namespace Engine
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &_registerId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &_registerId);
	}

	void OpenGLVertexArray::AddBuffer(std::shared_ptr<VertexBuffer>& vb, std::shared_ptr<VertexBufferLayout>& layout) const
	{
		Bind();
		vb->Bind();

	/*	const auto& elements = layout->GetElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];


			glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout->GetStride(), (const void*)offset);
			glEnableVertexAttribArray(i);

			offset += element.count * sizeof(element.type);
		}*/

		vb->Unbind();
		Unbind();
	}



	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(_registerId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

}

