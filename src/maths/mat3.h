#pragma once

#include "vec3.h"
#include "vec2.h"
#include "maths_func.h"

namespace ferrari {
	namespace maths {

		struct mat3
		{
			union
			{
				float elements[3 * 3];
				vec3 columns[3];
				vec3 rows[3];
			};

			mat3();
			mat3(float diagonal);
			mat3(float* elements); 
			mat3(const vec3& row0, const vec3& row1, const vec3& row2); 
			mat3::mat3(float a0, float a1, float a2, float a3, float a4, 
				       float a5, float a6, float a7, float a8);

			vec3 GetColumn(int index) const;
			void SetColumn(unsigned int index, const vec3& column);
			
			vec3 GetRow(int index) const;
			void SetRow(unsigned int index, const vec3& row);

			static mat3 Identity();

			mat3& Multiply(const mat3 &other);
			friend mat3 operator*(mat3 left, const mat3& right);
			mat3& operator*=(const mat3 &other);

			mat3& Invert();

			inline vec2 GetPosition() const { return vec2(GetColumn(2)); }
			inline void SetPosition(const vec2& position) { SetColumn(2, vec3(position, 1.0f)); }

			static mat3 Translation(const vec2& translation);
			static mat3 Rotation(float angle, const vec2 &axis);
			static mat3 C_Rotation(float angle);
			static mat3 CC_Rotation(float angle);
			static mat3 Scale(const vec3 &scale);
			static mat3 X_Reflection();
			static mat3 Y_Reflection();
			static mat3 PosX_Equal_Y_Reflection();
			static mat3 NegX_Equal_Y_Reflection();
			static mat3 Origin_Reflection();
			static mat3 Shear(const vec2& shear);
			static mat3 Invert(const mat3& matrix);
			static mat3 Transpose(const mat3& matrix);

			friend std::ostream &operator<<(std::ostream &stream, const mat3 &vector);
		};
	}
}