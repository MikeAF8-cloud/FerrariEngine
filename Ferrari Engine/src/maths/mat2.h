#include "vec2.h"
#include "maths_func.h"

namespace ferrari {
	namespace maths {

		struct mat2
		{
			union
			{
				// [row + column * 2]
				float elements[2 * 2];
				vec2 columns[2];
				vec2 rows[2];
			};

			mat2();
			mat2(float diagonal);
			mat2(float* elements);
			mat2(const vec2& row0, const vec2& row1);
			mat2::mat2(float a0, float a1, float a2, float a3);

			vec2 GetColumn(int index);
			void SetColumn(unsigned int index, const vec2& column);

			vec2 GetRow(int index) const;
			void SetRow(unsigned int index, const vec2& row);

			static mat2 Identity();

			mat2& Multiply(const mat2 &other);
			friend mat2 operator*(mat2 left, const mat2& right);
			mat2& operator*=(const mat2 &other);

			mat2& Invert();

			static mat2 Rotation(float angle);
			static mat2 Scale(const vec2 &scale);
			static mat2 X_AxisReflection();
			static mat2 Y_AxisReflection();
			static mat2 PosX_Equal_Y_Reflection();
			static mat2 NegX_Equal_Y_Reflection();
			static mat2 Shear(const vec2& Shear);

			static mat2 Invert(const mat2& matrix);
			static mat2 Transpose(const mat2& matrix);

			friend std::ostream &operator<<(std::ostream &stream, const mat2 &vector);
		};
	}
}