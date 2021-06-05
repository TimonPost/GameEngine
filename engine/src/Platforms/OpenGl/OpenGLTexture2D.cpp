#include "epch.h"
#include "OpenGLTexture2D.h"

#include "glad/glad.h"
#include "stb_image.h"
#include "Engine/Core/Log.h"

namespace Engine
{
	
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : _path(path)
	{
		ENGINE_PROFILE_FUNCTION();

		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = nullptr;
		{
			ENGINE_PROFILE_SCOPE("stbi load OpenGLTexture2D::OpenGLTexture2D(const std::string&)")
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
			ENGINE_CORE_ASSERT(data, "Failed to load texture 2d");
		}
		_width = width;
		_height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		} else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		_internalFormat = internalFormat;
		_dataFormat = dataFormat;
		
		ENGINE_ASSERT(_internalFormat & _dataFormat, "Texture format not supported!");
		
		glCreateTextures(GL_TEXTURE_2D, 1, &_renderId);
		glTextureStorage2D(_renderId, 1, _internalFormat, _width, _height);

		glTextureParameteri(_renderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(_renderId, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(unsigned width, unsigned height) : _width(width), _height(height)
	{
		ENGINE_PROFILE_FUNCTION();
		
		_internalFormat = GL_RGBA8, _dataFormat= GL_RGBA;
		
		glCreateTextures(GL_TEXTURE_2D, 1, &_renderId);
		glTextureStorage2D(_renderId, 1, _internalFormat, _width, _height);

		glTextureParameteri(_renderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_renderId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(_renderId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(_renderId, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &_renderId);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glBindTextureUnit(slot, _renderId);
	}

	void OpenGLTexture2D::SetData(void* data, unsigned size)
	{
		ENGINE_PROFILE_FUNCTION();
		
		unsigned int bpp = _dataFormat == GL_RGBA ? 4 : 3;
		ENGINE_CORE_ASSERT(size == _width * _height * bpp, "Data must be entire texture!")
		
		glTextureSubImage2D(_renderId, 0, 0, 0, _width, _height, _dataFormat, GL_UNSIGNED_BYTE, data);
	}
}
