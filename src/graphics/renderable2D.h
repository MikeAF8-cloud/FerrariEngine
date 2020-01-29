#pragma once

#include "../maths/maths.h"

#include "Buffers\vertexbuffer.h"
#include "Buffers\indexbuffer.h"
#include "Buffers\vertexarray.h"

#include "Texture.h"
#include "shader.h"
#include "renderer2D.h"

namespace ferrari {
	namespace graphics {

		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;
			float tid;
			unsigned int colors;
		};

		class Renderable2D
		{
		protected:
			maths::vec3 m_Position;
			maths::vec2 m_Size;
			unsigned int m_Color;
			std::vector<maths::vec2> m_Tex;
			Texture* m_texID;

		protected:
			Renderable2D() 
			{
				setTexDefaults();
			}
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
				:m_Position(position), m_Size(size), m_Color(color)
			{
				setTexDefaults();
			}

			virtual ~Renderable2D() {}


			virtual void Submit(Renderer2D* renderer) const
			{
				renderer->Submit(this);
			}

			void setColor(unsigned int color) { m_Color = color;}
			void setColor(const maths::vec4& color) 
			{
				unsigned int r = unsigned int(color.x * 255.0f);
				unsigned int g = unsigned int(color.y * 255.0f);
				unsigned int b = unsigned int(color.z * 255.0f);
				unsigned int a = unsigned int(color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

		public:
			inline const maths::vec3& getPosition() const{ return m_Position; }
			inline const maths::vec2& getSize() const{ return m_Size; }
			inline const unsigned int getColor() const{ return m_Color; }
			inline const std::vector<maths::vec2>& getTextures() const{ return m_Tex; }
			
			inline const GLuint getTID() const{ return m_texID == nullptr ? 0 : m_texID->GetID(); }

		private:
			void setTexDefaults()
			{
				m_Tex.push_back(maths::vec2(0, 0));
				m_Tex.push_back(maths::vec2(0, 1));
				m_Tex.push_back(maths::vec2(1, 1));
				m_Tex.push_back(maths::vec2(1, 0));
			}
		};

	}
}