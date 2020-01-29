#pragma once

#include <GLEW/glew.h>

namespace ferrari {
	namespace graphics {

		class VertexBuffer
		{	
		public:
			VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~VertexBuffer();

			void Bind() const;
			void Unbind() const;

			GLuint getComponentCount() const { return m_ComponentCount; }
		private:
			GLuint m_BufferID;
			GLuint m_ComponentCount;
		};

	}
}