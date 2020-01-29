#include "shader.h"

namespace ferrari
{ 
	namespace graphics
	{
		Shader::Shader(const char* name, const char *vertSrc, const char *fragSrc)
			: m_Name(name), m_VertSource(vertSrc), m_FragSource(fragSrc)
		{
				m_ShaderID = Load(m_VertPath, m_FragPath);
		}

		Shader::Shader(const char *vertPath, const char *fragPath)
			: m_Name(vertPath), m_VertPath(vertPath), m_FragPath(fragPath)
		{

			std::string vertSourceString = FileUtils::read_file(m_VertPath);
			std::string fragSourceString = FileUtils::read_file(m_FragPath);

			m_VertSource = vertSourceString.c_str();
			m_FragSource = fragSourceString.c_str();

			m_ShaderID = Load(m_VertSource, m_FragSource);

		}

		Shader* Shader::FromFile(const char* vertPath, const char* fragPath)
		{
			return new Shader(vertPath, fragPath);
		}

		Shader* Shader::FromSource(const char* vertSrc, const char* fragSrc)
		{
			return new Shader(vertSrc, vertSrc, fragSrc);
		}

		Shader* Shader::FromSource(const char* name, const char* vertSrc, const char* fragSrc)
		{
			return new Shader(name, vertSrc, fragSrc);
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_ShaderID);
		}

		GLuint Shader::Load(const char* vertSrc, const char* fragSrc)
		{
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			GLint result;

			glShaderSource(vertex, 1, &vertSrc, NULL);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}


			glShaderSource(fragment, 1, &fragSrc, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << std::endl;
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

		GLint Shader::getUniformLocation(const GLchar* name)
		{
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float value)
		{
			glUniform1f(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar* name, const maths::vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3f(const GLchar* name, const maths::vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar* name, const maths::vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniform1i(const GLchar* name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform2i(const GLchar* name, const maths::vec2& vector)
		{
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}

		void Shader::setUniform3i(const GLchar* name, const maths::vec3& vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4i(const GLchar* name, const maths::vec4& vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::setUniform1fv(const GLchar* name, float* value, GLsizei count)
		{
			glUniform1fv(getUniformLocation(name), count, value);
		}

		void Shader::setUniform1iv(const GLchar* name, int* value, GLsizei count)
		{
			glUniform1iv(getUniformLocation(name), count, value);
		}

		void Shader::setUniformMat3(const GLchar* name, const maths::mat3& matrix)
		{
			glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}

		void Shader::Enable() const
		{
			glUseProgram(m_ShaderID);
		}

		void Shader::Disable() const
		{
			glUseProgram(0);
		}

	}
}