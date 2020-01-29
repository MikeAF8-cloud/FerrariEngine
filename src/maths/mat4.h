#pragma once

#include "vec3.h"
#include "vec4.h"
#include "maths_func.h"

namespace ferrari {
	namespace maths {

		struct mat4
		{
			union
			{
				// [row + column * 4]
				float elements[4 * 4];
				vec4 columns[4];
				vec4 rows[4];
			};
			
			mat4();
			mat4(float diagonal);
			mat4(float* elements);
			mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3);
			mat4::mat4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7,
					   float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15);

			vec4 GetColumn(int index) const;
			void SetColumn(unsigned int index, const vec4& column);

			vec4 GetRow(int index) const;
			void SetRow(unsigned int index, const vec4& row);

			static mat4 Identity();

			mat4& Multiply(const mat4 &other);
			friend mat4 operator*(mat4 left, const mat4& right);
			mat4& operator*=(const mat4 &other);

			mat4& Invert();

			inline vec3 GetPosition() const { return vec3(GetColumn(3)); }
			inline void SetPosition(const vec3& position) { SetColumn(3, vec4(position, 1.0f)); }

			static mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 Perspective(float fov, float aspectRatio, float near, float far);
			static mat4 LookAt(const vec3& camera, const vec3& object, const vec3& up);

			static mat4 Translation(const vec3& translation);
			static mat4 Rotation(float angle, const vec3 &axis);
			static mat4 Scale(const vec3 &scale);
			static mat4 X_Rotation(float angle);
			static mat4 Y_Rotation(float angle);
			static mat4 Z_Rotation(float angle);
			static mat4 X_Reflection();
			static mat4 Y_Reflection();
			static mat4 Z_Reflection();
			static mat4 XY_Reflection();
			static mat4 XZ_Reflection();
			static mat4 YZ_Reflection();
			static mat4 Shear(float yx, float zx, float xy, float zy, float xz, float yz);
			
			static mat4 Invert(const mat4& matrix);
			static mat4 Transpose(const mat4& matrix);

			friend std::ostream &operator<<(std::ostream &stream, const mat4 &vector);
		};
	}
}