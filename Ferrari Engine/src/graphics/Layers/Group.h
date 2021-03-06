#pragma once

#include "../renderable2D.h"

namespace ferrari {
	namespace graphics {

		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*>  m_Renderables;
			maths::mat4 m_TransformationMatrix;
		public:
			Group(const maths::mat4& transform);
			~Group();
			void Add(Renderable2D* renderable);
			void Submit(Renderer2D* renderer) const override;
		};
	}
}