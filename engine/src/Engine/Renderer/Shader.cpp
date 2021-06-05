#include "epch.h"
#include "Shader.h"

#include "Renderer.h"
#include "RendererAPI.h"
#include "Platforms/OpenGl/OpenGLShader.h"

namespace Engine
{
	Ref<Shader> Shader::Create(const std::string& filePath, const std::string& name)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			ENGINE_CORE_ASSERT(false, "No render api configured");
			break;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, filePath);
		}

		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& s)
	{
		ENGINE_ASSERT(!Exists(s->GetName()), "Shader already exist!")
		
		auto& name = s->GetName();
		_shaders[name] = s;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Shader::Create(filePath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Shader::Create(filePath, name);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ENGINE_ASSERT(!Exists(name), "Shader does not exist!")
		return _shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string&name) const
	{
		return _shaders.find(name) != _shaders.end();
	}
}
