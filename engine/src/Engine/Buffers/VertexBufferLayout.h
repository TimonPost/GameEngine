#pragma once

#include "Engine/Core/Core.h"
#include "Engine/Core/Log.h"

namespace Engine {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static unsigned int ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::Float: return 4;
			case ShaderDataType::Float2:return 4 * 2;
			case ShaderDataType::Float3:return 4 * 3;
			case ShaderDataType::Float4:return 4 * 4;
			case ShaderDataType::Mat3:	return 4 * 3 * 3;
			case ShaderDataType::Mat4:	return 4 * 4 * 4;
			case ShaderDataType::Int:	return 4;
			case ShaderDataType::Int2:	return 4 * 2;
			case ShaderDataType::Int3:	return 4 * 3;
			case ShaderDataType::Int4:	return 4 * 4;
			case ShaderDataType::Bool:	return 1;		
		}
		ENGINE_ASSERT(false, "Can not get shader data type size for type {0}", type);
		return 0;
	}

	/// <summary>
	/// Specifies the layout in a buffer.
	/// </summary>
	struct VertexLayoutElement
	{
		std::string Name;
		ShaderDataType Type;
		unsigned int Offset;
		unsigned char Normalized;
		unsigned int Size;

		VertexLayoutElement() {  }
		
		VertexLayoutElement(ShaderDataType type, const std::string& name, bool normalized =false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		unsigned int GetElementCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;
				case ShaderDataType::Mat3: return 3*3;
				case ShaderDataType::Mat4: return 4*4;
				case ShaderDataType::Int: return 1;
				case ShaderDataType::Int2: return 2;
				case ShaderDataType::Int3: return 3;
				case ShaderDataType::Int4: return 4;
				case ShaderDataType::Bool: return 1;
			}
			ENGINE_ASSERT(false, "Can not get element count of type {0}", Type);
			return 0;
		}
	};

	/// <summary>
	/// Layout manager for the opengl buffer.
	/// </summary>
	class VertexBufferLayout
	{
		unsigned int _stride;
		std::vector<VertexLayoutElement> _elements;

	public:
		VertexBufferLayout() {}
		VertexBufferLayout(const std::initializer_list<VertexLayoutElement>& layout) :
			_stride(0), _elements(layout)
		{
			CalculateOffsetAndStride();
		}
		
		/// <summary>
		/// Gets the layout elements making up the layout.
		/// </summary>
		/// <param name="count"></param>
		std::vector<VertexLayoutElement> GetElements() const { return _elements; }

		unsigned int GetStride() const { return _stride; }

		std::vector<VertexLayoutElement>::iterator begin() { return _elements.begin(); }
		std::vector<VertexLayoutElement>::iterator end() { return _elements.end(); }
		std::vector<VertexLayoutElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<VertexLayoutElement>::const_iterator end() const { return _elements.end(); }

	private:
		void CalculateOffsetAndStride() {
			unsigned int offset = 0;
			_stride = 0;
			for (auto& element : _elements) {
				element.Offset = offset;
				offset += element.Size;
				_stride += element.Size;
			}
		}	
	};
}
