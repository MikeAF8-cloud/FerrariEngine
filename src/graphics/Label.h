#pragma once

#include "renderable2D.h"

#include "Font_Manager.h"

namespace ferrari {
	namespace graphics {

		class Label : public Renderable2D
		{
		public:
			Font* m_Font;
			std::string text;
			maths::vec3& position;
			float x, y;
		public:
			Label(std::string text, float x, float y, Font* font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);
			Label(std::string text, float x, float y, unsigned int color);

			void ValidateFont(const std::string& name, int size = -1);
			void Submit(Renderer2D* renderer) const override;
		};
	}
}