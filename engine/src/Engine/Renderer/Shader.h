#pragma once

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
	class Shader final 
	{
		unsigned int _registerId;
		std::string _filePath;
		std::unordered_map<std::string, int> uniformLocationCache;

		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		static unsigned int CompileShader(unsigned int type, const std::string& source);
		shader_program_source ParseShader(const std::string& filePath) const;

	public:
		std::string Label;

		Shader(const std::string& filePath, std::string label);
		~Shader();

		void Bind() const;
		void Unbind() const;

		/// <summary>
		/// Returns the shader path.
		/// </summary>
		/// <returns></returns>
		std::string Path() const;

		// Set uniforms
		void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform1i(const std::string& name, int value);
		void SetUniform3fv(const std::string& name, glm::vec3 value);
		void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);
		int GetUniformLocation(const std::string& name);
		int GetAttributeLocation(const std::string& name) const;

	};
}
