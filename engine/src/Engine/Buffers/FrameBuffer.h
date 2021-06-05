#pragma once
#include "Engine/Core/Core.h"

namespace Engine {

	struct FrameBufferSpecification
	{
		unsigned int width = SCREEN_WIDTH;
		unsigned int height = SCREEN_HEIGHT;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetColorAttachementRenderID() const = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification specification);
	};
}