#pragma once
#include "GL/glew.h"
#include <iostream>
#include "core/core.h"
#include "utils/fileutils.h"
#include <vector>
#include "math/math.h"

namespace Nata
{
	class Shader
	{
	private:
		unsigned int m_ShaderID;
		const char* m_VertPath;
		const char* m_FragPath;

	public:
		// Creates and loads
		Shader(const char* vertPath, const char* fragPath);
		~Shader();

		/// <summary>
		/// Equivalent to glUseProgram(this)
		/// </summary>
		void Enable() const;

		/// <summary>
		/// Equivalent to glUseProgram(NULL)
		/// </summary>
		void Disable() const;
		inline unsigned int GetID() { return m_ShaderID; }

		void SetUniform1f(const char* name, float value);
		void SetUniform1i(const char* name, int value);
		void SetUniform2f(const char* name, float v0, float v1);
		void SetUniform3f(const char* name, float v0, float v1, float v2);
		void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);

		void SetUniform2f(const char* name, Vector2& vector);
		void SetUniform2f(const char* name, Vector2 vector);
		void SetUniform3f(const char* name, Vector3& vector);
		void SetUniform4f(const char* name, Vector4& vector);
		void SetUniformMat4(const char* name, Matrix4& matrix);
		
		/// <summary>
		/// Creates program and attaches shaders to it. Returns program id
		/// </summary>
		unsigned int Load();
	};
}