#pragma once

#include <iostream>
#include <GLEW/glew.h>
#include <FreeImage\FreeImage.h>

#include <string>

#include "../utils/ImageLoad.h"

namespace ferrari {
	namespace graphics {

		enum TextureWrap
		{
			REPEAT = GL_REPEAT,
			CLAMP = GL_CLAMP,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		class Texture
		{
		private:
			static TextureWrap s_WrapMode;

			std::string m_Name, m_FilePath;
			GLuint m_TextureID;
			GLsizei m_Width, m_Height;
			unsigned int m_Bits;
		public:
			Texture(const std::string& name, const std::string& filepath);
			~Texture();

			void Bind() const;
			void Unbind () const;

			inline const std::string& GetName() const { return m_Name; }
			inline const unsigned int GetID() const { return m_TextureID; }
			inline const unsigned int GetWidth() const { return m_Width; }
			inline const unsigned int GetHeight() const { return m_Height; }
		
			inline static void SetWrap(TextureWrap mode) { s_WrapMode = mode; }
		private:
			GLuint Load();

		};

	}
}