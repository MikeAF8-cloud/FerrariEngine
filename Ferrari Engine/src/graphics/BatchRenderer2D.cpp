#include "BatchRenderer2D.h"

namespace ferrari {
	namespace graphics  {

		BatchRenderer2D::BatchRenderer2D()
		{
			Init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::Init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO); 

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_TEXTURE_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_TEXTURE_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::colors)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[  i  ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}
			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void BatchRenderer2D::Begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::DrawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color)
		{
			float tSlot = 0.0f;
			bool found = false;
			for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == font.getID())
				{
					tSlot = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found)
			{
				if (m_TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				m_TextureSlots.push_back(font.getID());
				tSlot = (float)(m_TextureSlots.size());
			}

			const maths::vec2& scale = font.getScale();

			float x = position.x;

			ftgl::texture_font_t* ftFont = font.getFTFont();

			for (unsigned int i = 0; i < text.length(); i++)
			{
				char c = text[i];
				ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);

				if (glyph != NULL)
				{
					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scale.x;
					}

					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x0, y0, 0);
					m_Buffer->uv = maths::vec2(u0, v0);
					m_Buffer->tid = tSlot;
					m_Buffer->colors = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x0, y1, 0);
					m_Buffer->uv = maths::vec2(u0, v1);
					m_Buffer->tid = tSlot;
					m_Buffer->colors = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x1, y1, 0);
					m_Buffer->uv = maths::vec2(u1, v1);
					m_Buffer->tid = tSlot;
					m_Buffer->colors = color;
					m_Buffer++;

					m_Buffer->vertex = *m_TransformationBack * maths::vec3(x1, y0, 0);
					m_Buffer->uv = maths::vec2(u1, v0);
					m_Buffer->tid = tSlot;
					m_Buffer->colors = color;
					m_Buffer++;

					m_IndexCount += 6;
					x += glyph->advance_x / scale.x;
				}
			}
		}

		void BatchRenderer2D::Submit(const Renderable2D* renderable)
		{
			const maths::vec3& position = renderable->getPosition();
			const maths::vec2& size = renderable->getSize();
			const unsigned int color = renderable->getColor();
			const std::vector<maths::vec2>& tex = renderable->getTextures();
			const GLuint tid = renderable->getTID();

			float tSlot = 0.0f;

			if (tid > 0)
			{
				bool found = false;
				for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i] == tid)
					{
						tSlot = (float)(i + 1);
						found = true;
						break;
					}
				}
				if (!found)
				{
					if (m_TextureSlots.size() >= RENDERER_MAX_TEXTURES)
					{
						End(); 
						Flush();
						Begin();
					}
					m_TextureSlots.push_back(tid);
					tSlot = (float)(m_TextureSlots.size());
				}
			}

			m_Buffer->vertex = *m_TransformationBack * position;
			m_Buffer->uv = tex[0];
			m_Buffer->tid = tSlot;
			m_Buffer->colors = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x, position.y + size.y, position.z);
			m_Buffer->uv = tex[1];
			m_Buffer->tid = tSlot;
			m_Buffer->colors = color;
			m_Buffer++;

			m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->uv = tex[2];
			m_Buffer->tid = tSlot;
			m_Buffer->colors = color;
			m_Buffer++;
			
			m_Buffer->vertex = *m_TransformationBack * maths::vec3(position.x + size.x, position.y, position.z);
			m_Buffer->uv = tex[3];
			m_Buffer->tid = tSlot;
			m_Buffer->colors = color;
			m_Buffer++;

			m_IndexCount +=  6;
		}

		void BatchRenderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::Flush()
		{
			for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->Bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->Unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
			m_TextureSlots.clear();
		}
	}
}

