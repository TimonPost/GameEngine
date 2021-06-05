#pragma once
#include "Engine/Core/Core.h"

namespace Engine {
	/// <summary>
	/// Abstraction for the opengl index buffer.
	/// </summary>
	class IndexBuffer
	{
	public:
		static Ref<IndexBuffer> Create(unsigned int* indicies, uint32_t size);

		/// <summary>
		/// Return the number of indexes.
		/// </summary>
		/// <returns></returns>
		virtual unsigned int GetCount() const = 0;
				
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual ~IndexBuffer() = default;
	};
}
