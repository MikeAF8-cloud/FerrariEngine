#pragma once

#include <string>

#include "../../Externals/freetype-gl/freetype-gl.h"

#include "../maths/vec2.h"

namespace ferrari {
	namespace graphics {

		class Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			float m_Size;
			maths::vec2 m_Scale;
			std::string m_Name;
			std::string m_Filename;
		public:
			Font(std::string name, std::string filename, float size);

			void setScale(float x, float y);

			inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }
			
			inline const unsigned int getID() const { return m_FTAtlas->id; }
			inline const maths::vec2 getScale() const { return m_Scale; }
			inline const std::string& getName() const { return m_Name; }
			inline const std::string& getFilename() const { return m_Filename; }
			inline const float getSize() const { return m_Size; }
		};

	}
}