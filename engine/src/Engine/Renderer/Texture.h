#pragma once
#include "Engine/Core/Core.h"

namespace Engine
{


	class Texture
	{
	public:
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetData(void* data, unsigned int size) = 0;
		
		virtual void Bind(unsigned int slot = 0) const = 0;

		virtual ~Texture() = default;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(unsigned int width, unsigned int height);
		
	};
}

