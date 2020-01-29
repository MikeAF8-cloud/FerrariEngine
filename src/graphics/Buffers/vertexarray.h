#pragma once


#include <vector>
#include <GLEW\glew.h>

#include "vertexbuffer.h"

namespace ferrari {
	namespace graphics {

		class VertexArray
		{
		public:
			VertexArray();
			~VertexArray();

			void addBuffer(VertexBuffer* buffer, GLuint index);
			void Bind() const;
			void Unbind() const;
		private:
			GLuint m_ArrayID;
			std::vector<VertexBuffer*> m_Buffers;
		};

	}
}