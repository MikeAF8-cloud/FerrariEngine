#include "Texture.h"

namespace ferrari {
	namespace graphics {

		TextureWrap Texture::s_WrapMode = REPEAT;

		Texture::Texture(const std::string& name, const std::string& filepath)
			:m_Name(name), m_FilePath(filepath)
		{
			m_TextureID = Load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_TextureID);
		}
		
		GLuint Texture::Load()
		{
			BYTE* pixels = load_image(m_FilePath.c_str(), &m_Width, &m_Height, &m_Bits);
			
			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s_WrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)s_WrapMode);
			
			GLint internalFormat = m_Bits == 32 ? GL_RGBA : GL_RGB;
			GLenum format = m_Bits == 32 ? GL_BGRA : GL_BGR;

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, pixels); //adjust this for bit depth
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels;
			return result;
		}

		void Texture::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_TextureID);
		}

		void Texture::Unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
}