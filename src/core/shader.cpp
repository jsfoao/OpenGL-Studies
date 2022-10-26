#include "shader.h"

namespace Nata
{
	Shader::Shader(const char* vertPath, const char* fragPath)
	{
		m_VertPath = vertPath;
		m_FragPath = fragPath;

		m_ShaderID = Load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_ShaderID);
	}

	unsigned int Shader::Load()
	{
		unsigned int program = glCreateProgram();

		// VERTEX
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		std::string tempVertSource = FileUtils::ReadFile(m_VertPath);
		const char* vertSource = tempVertSource.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		// shader error handling
		int result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			LOG("Failed to compile vertex shader!");
			glDeleteShader(vertex);
			return 0;
		}

		// FRAGMENT
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		std::string tempFragSource = FileUtils::ReadFile(m_FragPath);
		const char* fragSource = tempFragSource.c_str();

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		// shader error handling
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			LOG("Failed to compile fragment shader!");
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::Enable() const
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Disable() const
	{
		glUseProgram(NULL);
	}

	void Shader::SetUniform1f(const char* name, const float value)
	{
		glUniform1f(glGetUniformLocation(m_ShaderID, name), value);
	}

	void Shader::SetUniform1i(const char* name, const int value)
	{
		glUniform1i(glGetUniformLocation(m_ShaderID, name), value);
	}

	void Shader::SetUniform2f(const char* name, Vector2& v)
	{
		glUniform2f(glGetUniformLocation(m_ShaderID, name), v.x, v.y);
	}

	void Shader::SetUniform2f(const char* name, Vector2 v)
	{
		glUniform2f(glGetUniformLocation(m_ShaderID, name), v.x, v.y);
	}

	void Shader::SetUniform3f(const char* name, Vector3& v)
	{
		glUniform3f(glGetUniformLocation(m_ShaderID, name), v.x, v.y, v.z);
	}

	void Shader::SetUniform4f(const char* name, Vector4& v)
	{
		glUniform4f(glGetUniformLocation(m_ShaderID, name), v.x, v.y, v.z, v.w);
	}

	void Shader::SetUniform2f(const char* name, float v0, float v1)
	{
		glUniform2f(glGetUniformLocation(m_ShaderID, name), v0, v1);
	}

	void Shader::SetUniform3f(const char* name, float v0, float v1, float v2)
	{
		glUniform3f(glGetUniformLocation(m_ShaderID, name), v0, v1, v2);
	}

	void Shader::SetUniform4f(const char* name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(glGetUniformLocation(m_ShaderID, name), v0, v1, v2, v3);
	}

	void Shader::SetUniformMat4(const char* name, Matrix4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, matrix.elements);
	}
}