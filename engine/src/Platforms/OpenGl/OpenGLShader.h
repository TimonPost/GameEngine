#pragma once

#include "Engine/Renderer/Shader.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Engine {
	/// <summary>
	/// Abstraction over an opgengl shader.
	/// </summary>
	class OpenGLShader final : public Shader
	{
		unsigned int _registerId;
		std::string _filePath;
		std::unordered_map<std::string, int> uniformLocationCache;
		std::string _name;

		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
		static unsigned int CompileShader(unsigned int type, const std::string& source);

		shader_program_source ParseShader(const std::string& filePath) const override;

	public:
		OpenGLShader(const std::string& name, const std::string& filePath);
		~OpenGLShader();
		void Bind() const override;
		void Unbind() const override;
		const std::string& GetName() const override { return _name; }		
		std::string Path() const;


		virtual void SetMat4(const std::string& name, const glm::mat4 value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3 value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4 value) override;

		void SetFloat(const char* str, float value) override;
		void SetInt(const std::string& name, int i) override;
		
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform1f(const std::string& name, float value);
		void SetUniform1i(const std::string& name, int value);
		void SetUniform3fv(const std::string& name, glm::vec3 value);
		void SetUniform4fv(const std::string& name, glm::vec4 value);
		void SetUniformMatrix4fv(const std::string& name, glm::mat4 value);
		int GetUniformLocation(const std::string& name);
		int GetAttributeLocation(const std::string& name) const;
	};
}
