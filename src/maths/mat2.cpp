#include "mat2.h"

namespace ferrari {
	namespace maths {

		mat2::mat2()
		{
			for (int i = 0; i < 2 * 2; i++)
				elements[i] = 0;
		}

		mat2::mat2(float diagonal)
		{
			for (int i = 0; i < 2 * 2; i++)
				elements[i] = 0;

			elements[0 + 0 * 2] = diagonal;
			elements[1 + 1 * 2] = diagonal;
		}

		mat2::mat2(float* elements)
		{
			std::cout << *elements << std::endl;
			for (int i = 0; i < 2 * 2; i++)
				elements[i] = 5;// *elements;
		}
		
		mat2::mat2(const vec2& row0, const vec2& row1)
		{
			rows[0] = row0;
			rows[1] = row1;
		}

		mat2::mat2(float a0, float a1, float a2, float a3)
		{
			elements[0] = a0; elements[2] = a2;
			elements[1] = a1; elements[3] = a3;
		}

		vec2 mat2::GetColumn(int index)
		{
			return vec2(elements[0 + index * 2], elements[1 + index * 2]);
		}

		void mat2::SetColumn(unsigned int index, const vec2& column)
		{
			elements[0 + index * 2] = column.x;
			elements[1 + index * 2] = column.y;
		}

		vec2 mat2::GetRow(int index) const
		{
			return vec2(elements[index + 0 * 2], elements[index + 1 * 2]);
		}

		void mat2::SetRow(unsigned int index, const vec2& row)
		{
			elements[index + 0 * 2] = row.x;
			elements[index + 1 * 2] = row.y;
		}

		mat2 mat2::Identity()
		{
			return mat2(1.0f);
		}

		mat2 &mat2::Multiply(const mat2 &other)
		{
			float data[4];
			for (int y = 0; y < 2; y++)
			{
				for (int x = 0; x < 2; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 2; e++)
					{
						sum += elements[x + e * 2] * other.elements[e + y * 2];
					}
					data[x + y * 2] = sum;
				}
			}
			memcpy(elements, data, 2 * 2 * sizeof(float));
			return *this;
		}

		mat2 operator*(mat2 left, const mat2& right)
		{
			return left.Multiply(right);
		}

		mat2 &mat2::operator*=(const mat2 &other)
		{
			return Multiply(other);
		}

		mat2& mat2::Invert()
		{
			float temp[16];

			temp[0] = elements[3];

			temp[1] = -elements[1];

			temp[2] =  -elements[2];

			temp[3] = elements[0];

			float determinant = elements[0] * elements[3] - elements[1] * elements[2];

			if (determinant == 0)
			{
				std::cout << "Determinant is 0. Not Invertable\n" << std::endl;
				return *this;
			}

			determinant = 1.0 / determinant;

			for (int i = 0; i < 2 * 2; i++)
				elements[i] = temp[i] * determinant;

			return *this;
		}

		mat2 mat2::Rotation(float angle)
		{
			mat2 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			result.elements[0 + 0 * 2] = c;
			result.elements[1 + 0 * 2] = s;

			result.elements[0 + 1 * 2] = -s;
			result.elements[1 + 1 * 2] = c;

			return result;
		}

		mat2 mat2::Scale(const vec2 &scale)
		{
			mat2 result(1.0f);

			result.elements[0 + 0 * 2] = scale.x;
			result.elements[1 + 1 * 2] = scale.y;

			return result;
		}

		mat2 mat2::X_AxisReflection()
		{
			mat2 result(0.0f);

			result.elements[0 + 0 * 2] = 1.0f;
			result.elements[1 + 1 * 2] = -1.0f;

			return result;
		}

		mat2 mat2::Y_AxisReflection()
		{
			mat2 result(0.0f);

			result.elements[0 + 0 * 2] = -1.0f;
			result.elements[1 + 1 * 2] = 1.0f;

			return result;
		}

		mat2 mat2::PosX_Equal_Y_Reflection()
		{
			mat2 result(0.0f);

			result.elements[1 + 0 * 2] = 1.0f;
			result.elements[0 + 1 * 2] = 1.0f;

			return result;
		}

		mat2 mat2::NegX_Equal_Y_Reflection()
		{
			mat2 result(0.0f);

			result.elements[1 + 0 * 2] = -1.0f;
			result.elements[0 + 1 * 2] = -1.0f;

			return result;
		}

		mat2 mat2::Invert(const mat2& matrix)
		{
			mat2 result = matrix;
			return result.Invert();
		}

		mat2 mat2::Transpose(const mat2& matrix)
		{
			return mat2(
				vec2(matrix.rows[0].x, matrix.rows[1].x),
				vec2(matrix.rows[0].y, matrix.rows[1].y)
				);
		}

		mat2 mat2::Shear(const vec2& shear)
		{
			mat2 result(1.0f);

			result.elements[1 + 0 * 2] = shear.x;
			result.elements[0 + 1 * 2] = shear.y;

			return result;
		}

		std::ostream &operator<<(std::ostream &stream, const mat2 &matrix)
		{
			stream << "mat2: (" << matrix.rows[0].x << ", " << matrix.rows[1].x << "),\n      ";
			stream <<       "(" << matrix.rows[0].y << ", " << matrix.rows[1].y << ")\n";
			return stream;
		}
	}
}