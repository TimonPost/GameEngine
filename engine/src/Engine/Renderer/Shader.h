#pragma once

#include "Engine/Core/Core.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Engine {
	struct shader_program_source
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	enum class shader_type
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	/// <summary>
	/// Abstraction over an opgengl shader.
	/// </summary>
	class Shader
	{	
		virtual shader_program_source ParseShader(const std::string& filePath) const = 0;

	public:
		virtual ~Shader() = default;
		
		static Ref<Shader> Create(const std::string& filePath, const std::string& name = "");

		virtual const std::string& GetName() const = 0;
		
		virtual void  Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetMat4(const std::string& name, const glm::mat4 value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3 value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4 value) = 0;

		virtual void SetFloat(const char* str, float value) = 0;
		virtual void SetInt(const std::string& name, int i) = 0;
		
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& s);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);

		Ref<Shader> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> _shaders;
	};
}
