#pragma once

#include <iostream>
#include <vector>
#include <GLEW/glew.h>
#include "../utils/fileutils.h"
#include "../maths/maths.h"

namespace ferrari
{
	namespace graphics
	{
		class Shader
		{
		private:
			GLuint m_ShaderID;
			const char *m_Name;
			const char *m_VertPath, *m_FragPath;
			const char *m_VertSource, *m_FragSource;
		public:
			Shader(const char* name, const char* vertPath, const char *fragPath);
			Shader(const char* vertPath, const char *fragPath);

			~Shader();

			static Shader* FromFile(const char* vertPath, const char* fragPath);
			static Shader* FromSource(const char* vertSrc, const char* fragSrc);
			static Shader* FromSource(const char* name, const char* vertSrc, const char* fragSrc);



			void setUniform1f(const GLchar* name, float value);
			void setUniform2f(const GLchar* name, const maths::vec2& vector);
			void setUniform3f(const GLchar* name, const maths::vec3& vector);
			void setUniform4f(const GLchar* name, const maths::vec4& vector);

			void setUniform1i(const GLchar* name, int value);
			void setUniform2i(const GLchar* name, const maths::vec2& vector);
			void setUniform3i(const GLchar* name, const maths::vec3& vector);
			void setUniform4i(const GLchar* name, const maths::vec4& vector);

			void setUniform1iv(const GLchar* name, int* value, GLsizei count);
			void setUniform1fv(const GLchar* name, float* value, GLsizei count);

			void setUniformMat3(const GLchar* name, const maths::mat3& matrix);
			void setUniformMat4(const GLchar* name, const maths::mat4& matrix);

			void Enable() const;
			void Disable() const;
		private:
			GLint getUniformLocation(const GLchar* name);
			GLuint Load(const char* vertSrc, const char* fragSrc);

		};
	}
}