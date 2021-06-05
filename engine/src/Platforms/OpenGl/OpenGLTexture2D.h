#pragma once
#include "Engine/Renderer/Texture.h"
#include "glad/glad.h"


namespace Engine
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		
		virtual ~OpenGLTexture2D();
		
		unsigned OpenGLTexture2D::GetWidth() const
		{
			return _width;
		}

		unsigned OpenGLTexture2D::GetHeight() const
		{
			return _height;
		}
		
		void Bind(unsigned int slot = 0) const override;

		void SetData(void* data, unsigned size) override;
	private:
		std::string _path;
		unsigned int _width;
		unsigned int _height;
		GLuint _renderId;
		GLenum _internalFormat, _dataFormat;
	};
}

