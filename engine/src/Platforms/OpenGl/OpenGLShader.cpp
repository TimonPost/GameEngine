#include "epch.h"
#include "OpenGLShader.h"

#include "Engine/Core/Log.h"
#include <glad/glad.h>

namespace Engine {
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filePath) :_name(name)
	{
		ENGINE_PROFILE_FUNCTION();
		
		const shader_program_source source = ParseShader(filePath);
		_registerId = CreateShader(source.VertexSource, source.FragmentSource);
		_filePath = filePath;
		
		if (name == "") {
			// extract name from filepath.
			auto lastSlash = _filePath.find_last_of("/\\");
			lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = _filePath.rfind('.');
			auto count = lastDot == std::string::npos ? _filePath.size() - lastSlash : lastDot - lastSlash;
			_name = filePath.substr(lastSlash, count);
		}else
		{
			_name = name;
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(_registerId);
	}

	void OpenGLShader::Bind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glUseProgram(_registerId);
	}

	void OpenGLShader::Unbind() const
	{
		ENGINE_PROFILE_FUNCTION();
		
		glUseProgram(0);
	}
		
	std::string OpenGLShader::Path() const
	{
		return _filePath;
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4 value)
	{
		ENGINE_PROFILE_FUNCTION();
		
		SetUniformMatrix4fv(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3 value)
	{
		ENGINE_PROFILE_FUNCTION();
		
		SetUniform3fv(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4 value)
	{
		ENGINE_PROFILE_FUNCTION();
		
		SetUniform4fv(name, value);
	}

	void OpenGLShader::SetFloat(const char* str, float value)
	{
		ENGINE_PROFILE_FUNCTION();
		SetUniform1f(str, value);
	}

	void OpenGLShader::SetInt(const std::string& name, int i)
	{
		ENGINE_PROFILE_FUNCTION();
		
		SetUniform1i(name, i);
	}

	// Set uniforms
	void OpenGLShader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void OpenGLShader::SetUniform1f(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniform3fv(const std::string& name, glm::vec3 value)
	{
		glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUniform4fv(const std::string& name, glm::vec4 value)
	{
		glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUniformMatrix4fv(const std::string& name, glm::mat4 value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
		{
			return uniformLocationCache[name];
		}

		int location;
		location = glGetUniformLocation(_registerId, name.c_str());

		if (location == -1)
		{
			ENGINE_CORE_WARN("Warning: uniform {0} doesnt exist!", name);
		}
		uniformLocationCache[name] = location;
		return location;
	}

	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		ENGINE_PROFILE_FUNCTION();
		
		unsigned int id;
		id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			int lenght;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
			char* message = static_cast<char*>(alloca(lenght * sizeof(char)));
			glGetShaderInfoLog(id, lenght, &lenght, message);

			ENGINE_CORE_ERROR("Failed to compile {0} shader", (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"))

			glDeleteShader(0);

			return 0;
		}

		return id;
	}

	unsigned int OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		ENGINE_PROFILE_FUNCTION();
		
		unsigned int program;
		program = glCreateProgram();
		const unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	shader_program_source OpenGLShader::ParseShader(const std::string& filePath) const
	{
		ENGINE_PROFILE_FUNCTION();
		
		std::ifstream stream(filePath);

		std::string line;
		std::stringstream ss[2];
		shader_type type = shader_type::NONE;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = shader_type::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = shader_type::FRAGMENT;
				}
			}
			else
			{
				ss[static_cast<int>(type)] << line << '\n';
			}
		}

		return shader_program_source{ ss[0].str(), ss[1].str() };
	}

	int OpenGLShader::GetAttributeLocation(const std::string& name) const
	{
		return glGetAttribLocation(_registerId, name.c_str());
	}
}
