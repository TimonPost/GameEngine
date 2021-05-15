#pragma once

namespace Engine {
	/// <summary>
	/// Abstraction for the opengl index buffer.
	/// </summary>
	class IndexBuffer
	{
	public:
		IndexBuffer() {};

		virtual IndexBuffer* Create(unsigned int* indicies, uint32_t size);

		/// <summary>
		/// Return the number of indexes.
		/// </summary>
		/// <returns></returns>
		virtual unsigned int GetCount() const;
				
		virtual void Bind() const;
		virtual void Unbind() const;

		virtual ~IndexBuffer();
	};
}
