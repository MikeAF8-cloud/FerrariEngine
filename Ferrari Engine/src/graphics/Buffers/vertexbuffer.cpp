#include "vertexbuffer.h"

namespace ferrari {
	namespace graphics {

		VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount)
			:m_ComponentCount(componentCount)
		{
			glGenBuffers(1, &m_BufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &m_BufferID);
		}

		void VertexBuffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		}

		void VertexBuffer::Unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

	}
}