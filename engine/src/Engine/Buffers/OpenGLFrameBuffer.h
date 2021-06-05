#pragma once

#include "Engine/Buffers/FrameBuffer.h"
#include "glad/glad.h"

namespace Engine {
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(FrameBufferSpecification frameBufferSpecification);
		~OpenGLFrameBuffer();
		void Bind() override;
		void Unbind() override;
		unsigned GetColorAttachementRenderID() const override;
		const FrameBufferSpecification& GetSpecification() const override;
		void Invalidate();
		FrameBufferSpecification _specification;
		GLuint _colorAttachment;
		GLuint _rendererID;
		GLuint _depthAttachment;
	};
}

