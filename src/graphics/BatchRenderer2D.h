#pragma once

#include "renderer2D.h"
#include "renderable2D.h"

#include "Buffers\vertexarray.h"

#include <cstddef>

namespace ferrari {
	namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

#define SHADER_VERTEX_INDEX		0
#define SHADER_TEXTURE_INDEX	1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3

		class BatchRenderer2D : public Renderer2D
		{
		private:
			void Init();
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void Submit(const Renderable2D* renderable) override;
			void Flush() override;
			void DrawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) override;
			void Begin() override;
			void End()  override;

		private:
			GLuint m_VAO;
			IndexBuffer* m_IBO;
			VertexData* m_Buffer;
			GLsizei m_IndexCount = 0;
			GLuint m_VBO;
		
			std::vector<GLuint> m_TextureSlots;
		};

	}
}