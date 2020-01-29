#include "Label.h"

namespace ferrari {
	namespace graphics {

		Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
			:Renderable2D(), text(text), position(m_Position), m_Font(FontManager::Get("Arial"))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		}

		Label::Label(std::string text, float x, float y,const std::string& font, unsigned int color)
			:Renderable2D(), text(text), position(m_Position), m_Font(FontManager::Get(font))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;

			ValidateFont(font);
		}

		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
			:Renderable2D(), text(text), position(m_Position), m_Font(FontManager::Get(font, size))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;

			ValidateFont(font, size);
		}

		Label::Label(std::string text, float x, float y, unsigned int color)
			:Renderable2D(), text(text), position(m_Position), m_Font(FontManager::Get("Arial"))
		{
			m_Position = maths::vec3(x, y, 0.0f);
			m_Color = color;
		}

		void Label::Submit(Renderer2D* renderer) const
		{
			renderer->DrawString(text, position, *m_Font, m_Color);
		}

		void Label::ValidateFont(const std::string& name, int size)
		{
			if (m_Font != nullptr)
				return;

			std::cout << "Null Font: Font = " << name;
			if (size > 0)
				std::cout << ", Size = " << size;
			std::cout << std::endl;

			m_Font = FontManager::Get("Arial");
		}
	}
}