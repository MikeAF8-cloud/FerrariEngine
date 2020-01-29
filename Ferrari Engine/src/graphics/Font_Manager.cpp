#include "Font_Manager.h"

namespace ferrari {
	namespace graphics {

		std::vector<Font*> FontManager::m_Fonts;

		void FontManager::Add(Font* font)
		{
			m_Fonts.push_back(font);
		}

		Font* FontManager::Get()
		{
			return m_Fonts[0];
		}

		Font* FontManager::Get(const std::string& name)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getName() == name)
					return font;
			}
			return nullptr;
		}

		Font* FontManager::Get(const std::string& name, unsigned int size)
		{
			for (Font* font : m_Fonts)
			{
				if (font->getSize() == size && font->getName() == name)
					return font;
			}
			return nullptr;
		}

		void FontManager::Terminate()
		{
			for (unsigned int i = 0; i < m_Fonts.size(); i++)
				delete m_Fonts[i];
		}
	}
}