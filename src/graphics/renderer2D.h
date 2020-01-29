#pragma once
#include "Font.h"
#include "../maths/maths.h"

#include <vector>

namespace ferrari{
	namespace graphics {

		class Renderable2D;

		class Renderer2D
		{
		protected:
			Renderer2D()
			{
				m_TransformationStack.push_back(maths::mat4::Identity());
				m_TransformationBack = &m_TransformationStack.back();
			}

		public:
			void Push(const maths::mat4& matrix, bool override = false)
			{
				if (override)
					m_TransformationStack.push_back(matrix);
				else 
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);
				m_TransformationBack = &m_TransformationStack.back();
			}

			void Pop()
			{
				if (m_TransformationStack.size() > 1)
					m_TransformationStack.pop_back();

				m_TransformationBack = &m_TransformationStack.back();
			}

			virtual void Begin() {}
			virtual void End() {}
			virtual void DrawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) {}
			virtual void Submit(const Renderable2D* renderable) = 0;
			virtual void Flush() = 0;
		protected:
			std::vector<maths::mat4> m_TransformationStack;
			const maths::mat4* m_TransformationBack;
		};
	}
}