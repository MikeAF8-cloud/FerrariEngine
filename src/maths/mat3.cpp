#include "mat3.h"

namespace ferrari {
	namespace maths {

		mat3::mat3()
		{
			for (int i = 0; i < 3 * 3; i++)
				elements[i] = 0;
		}

		mat3::mat3(float diagonal)
		{
			for (int i = 0; i < 3 * 3; i++)
				elements[i] = 0;

			elements[0 + 0 * 3] = diagonal;
			elements[1 + 1 * 3] = diagonal;
			elements[2 + 2 * 3] = diagonal;
		}

		mat3::mat3(float* elements)
		{
			for (int i = 0; i < 3 * 3; i++)
				elements[i] = *elements;
		}

		mat3::mat3(const vec3& row0, const vec3& row1, const vec3& row2)
		{
			rows[0] = row0;
			rows[1] = row1;
			rows[2] = row2;
		}

		mat3::mat3(float a0, float a1, float a2, 
				   float a3, float a4, float a5, 
				   float a6, float a7,float a8)
		{
			elements[0] = a0; elements[3] = a3; elements[6] = a6;
			elements[1] = a1; elements[4] = a4; elements[7] = a7;
			elements[2] = a2; elements[5] = a5; elements[8] = a8;
		}

		mat3 mat3::Identity()
		{
			return mat3(1.0f);
		}

		mat3 &mat3::Multiply(const mat3 &other)
		{
			float data[9];
			for (int y = 0; y < 3; y++)
			{
				for (int x = 0; x < 3; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 3; e++)
					{
						sum += elements[x + e * 3] * other.elements[e + y * 3];
					}
					data[x + y * 3] = sum;
				}
			}
			memcpy(elements, data, 3 * 3 * sizeof(float));
			return *this;
		}

		mat3 operator*(mat3 left, const mat3& right)
		{
			return left.Multiply(right);
		}

		mat3 &mat3::operator*=(const mat3 &other)
		{
			return Multiply(other);
		}

		vec3 mat3::GetColumn(int index) const
		{
			return vec3(elements[0 + index * 3], elements[1 + index * 3], elements[2 + index * 3]);
		}

		void mat3::SetColumn(unsigned int index, const vec3& column)
		{
			elements[0 + index * 3] = column.x;
			elements[1 + index * 3] = column.y;
			elements[2 + index * 3] = column.z;
		}

		vec3 mat3::GetRow(int index) const
		{
			return vec3(elements[index + 0 * 3], elements[index + 1 * 3], elements[index + 2 * 3]);
		}

		void mat3::SetRow(unsigned int index, const vec3& row)
		{
			elements[index + 0 * 3] = row.x;
			elements[index + 1 * 3] = row.y;
			elements[index + 2 * 3] = row.z;
		}

		mat3& mat3::Invert()
		{
			double temp[9];

			temp[0] = elements[4] * elements[8] -
				elements[5] * elements[7];

			temp[3] = -(elements[3] * elements[8] -
				elements[5] * elements[6]);

			temp[6] = elements[3] * elements[7] - 
				elements[4] * elements[6];

			temp[1] = -(elements[1] * elements[8] - 
				elements[2] * elements[7]);

			temp[4] = elements[0] * elements[8] -
				elements[2] * elements[6];

			temp[7] = -(elements[0] * elements[7] - 
				elements[1] * elements[6]);

			temp[2] = elements[1] * elements[5] - 
				elements[2] * elements[4];

			temp[5] = -(elements[0] * elements[5] - 
				elements[2] * elements[3]);

			temp[8] = elements[0] * elements[4] - 
				elements[1] * elements[3];

			double determinant = elements[0] * temp[0] - elements[3] * -temp[1] + elements[6] * temp[6];
			
			if (determinant == 0)
			{
				std::cout << "Determinant is 0. Not Invertable\n" << std::endl;
				return *this;
			}

			determinant = 1.0 / determinant;

			for (int i = 0; i < 3 * 3; i++)
				elements[i] = temp[i] * determinant;

			return *this;
		}

		mat3 mat3::Translation(const vec2& translation)
		{
			mat3 result(1.0f);

			result.elements[0 + 2 * 3] = translation.x;
			result.elements[1 + 2 * 3] = translation.y;

			return result;
		}

		mat3 mat3::Rotation(float angle, const vec2 &axis)
		{
			mat3 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;

			result.elements[0 + 0 * 3] = x * x * omc + c;
			result.elements[1 + 0 * 3] = y * x * omc + 1 * s;

			result.elements[0 + 1 * 3] = x * y * omc - 1 * s;
			result.elements[1 + 1 * 3] = y * y * omc + c;

			return result;
		}

		mat3 mat3::C_Rotation(float angle)
		{
			mat3 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);

			result.elements[0 + 0 * 3] = c;
			result.elements[1 + 0 * 3] = -s;
			result.elements[0 + 1 * 3] = s;
			result.elements[1 + 1 * 3] = c;

			return result;
		}
		
		mat3 mat3::CC_Rotation(float angle)
		{
			mat3 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);

			result.elements[0 + 0 * 3] = c;
			result.elements[1 + 0 * 3] = s;
			result.elements[0 + 1 * 3] = -s;
			result.elements[1 + 1 * 3] = c;

			return result;
		}

		mat3 mat3::Scale(const vec3 &scale)
		{
			mat3 result(1.0f);

			result.elements[0 + 0 * 3] = scale.x;
			result.elements[1 + 1 * 3] = scale.y;
			result.elements[2 + 2 * 3] = scale.z;

			return result;
		}

		mat3 mat3::X_Reflection()
		{
			mat3 result(1.0f);

			result.elements[1 + 1 * 3] = -1.0f;

			return result;
		}

		mat3 mat3::Y_Reflection()
		{
			mat3 result(1.0f);

			result.elements[0 + 0 * 3] = -1.0f;
			
			return result;
		}

		mat3 mat3::PosX_Equal_Y_Reflection()
		{
			mat3 result(0.0f);

			result.elements[1 + 0 * 3] = 1.0f;
			result.elements[0 + 1 * 3] = 1.0f;
			result.elements[2 + 2 * 3] = 1.0f;

			return result;
		}

		mat3 mat3::NegX_Equal_Y_Reflection()
		{
			mat3 result(0.0f);

			result.elements[1 + 0 * 3] = -1.0f;
			result.elements[0 + 1 * 3] = -1.0f;
			result.elements[2 + 2 * 3] = 1.0f;

			return result;
		}

		mat3 mat3::Origin_Reflection()
		{
			mat3 result(1.0f);

			result.elements[0 + 0 * 3] = -1.0f;
			result.elements[1 + 1 * 3] = -1.0f;

			return result;
		}

		mat3 mat3::Shear(const vec2& shear)
		{
			mat3 result(1.0f);

			result.elements[1 + 0 * 2] = shear.x;
			result.elements[0 + 1 * 2] = shear.y;

			return result;
		}

		mat3 mat3::Invert(const mat3& matrix)
		{
			mat3 result = matrix;
			return result.Invert();
		}
		
		mat3 mat3::Transpose(const mat3& matrix)
		{
			return mat3(
				vec3(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x),
				vec3(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y),
				vec3(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z)
				);
		}

		std::ostream &operator<<(std::ostream &stream, const mat3 &matrix)
		{
			stream << "mat3: (" << matrix.rows[0].x << ", " << matrix.rows[1].x << ", " << matrix.rows[2].x << "),\n      ";
			stream <<       "(" << matrix.rows[0].y << ", " << matrix.rows[1].y << ", " << matrix.rows[2].y << "),\n      ";
			stream <<       "(" << matrix.rows[0].z << ", " << matrix.rows[1].z << ", " << matrix.rows[2].z << ")\n";
			return stream;
		}
	}
}