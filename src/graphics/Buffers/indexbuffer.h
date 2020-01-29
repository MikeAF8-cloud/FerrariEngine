#pragma once

#include <GLEW/glew.h>

namespace ferrari {
	namespace graphics {

		class IndexBuffer
		{ 
		public:
			IndexBuffer(GLuint* data, GLsizei count);
			IndexBuffer(GLushort* data, GLsizei count);
			~IndexBuffer();
			void Bind() const;
			void Unbind() const;

			inline GLuint getCount() const { return m_Count; }
		private:
			GLuint m_BufferID;
			GLuint m_Count;


		};

	}
}