#include "mat4.h"

namespace ferrari {
	namespace maths {

		mat4::mat4()
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0;
		}

		mat4::mat4(float diagonal)
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0;

			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		mat4::mat4(float* elements)
		{
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = *elements;
		}

		mat4::mat4(const vec4& row0, const vec4& row1, const vec4& row2, const vec4& row3)
		{
			rows[0] = row0;
			rows[1] = row1;
			rows[2] = row2;
			rows[3] = row3;
		}

		mat4::mat4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7,
			float a8, float a9, float a10, float a11, float a12, float a13, float a14, float a15)
		{
			elements[0] = a0; elements[4] = a4; elements[8] = a8; elements[12] = a12;   
			elements[1] = a1; elements[5] = a5; elements[9] = a9; elements[13] = a13;
			elements[2] = a2; elements[6] = a6; elements[10] = a10; elements[14] = a14;
			elements[3] = a3; elements[7] = a7; elements[11] = a11; elements[15] = a15;
		}

		mat4 mat4::Identity()
		{
			return mat4(1.0f);
		}

		vec4 mat4::GetColumn(int index) const
		{
			return vec4(elements[0 + index * 4], elements[1 + index * 4], elements[2 + index * 4], elements[3 + index * 4]);
		}

		void mat4::SetColumn(unsigned int index, const vec4& column)
		{
			elements[0 + index * 4] = column.x;
			elements[1 + index * 4] = column.y;
			elements[2 + index * 4] = column.z;
			elements[3 + index * 4] = column.w;
		}

		vec4 mat4::GetRow(int index) const
		{
			return vec4(elements[index + 0 * 4], elements[index + 1 * 4], elements[index + 2 * 4], elements[index + 3 * 4]);
		}

		void mat4::SetRow(unsigned int index, const vec4& row)
		{
			elements[index + 0 * 4] = row.x;
			elements[index + 1 * 4] = row.y;
			elements[index + 2 * 4] = row.z;
			elements[index + 3 * 4] = row.w;
		}

		mat4 &mat4::Multiply(const mat4 &other)
		{
			float data[16];
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					float sum = 0.0f;
					for (int e = 0; e < 4; e++)
					{
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					data[x + y * 4] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		mat4 operator*(mat4 left, const mat4& right)
		{
			return left.Multiply(right);
		}

		mat4 &mat4::operator*=(const mat4 &other)
		{
			return Multiply(other);
		}


		mat4& mat4::Invert()
		{
			double temp[16];

			temp[0] = elements[5] * elements[10] * elements[15] -
				elements[5] * elements[11] * elements[14] -
				elements[9] * elements[6] * elements[15] +
				elements[9] * elements[7] * elements[14] +
				elements[13] * elements[6] * elements[11] -
				elements[13] * elements[7] * elements[10];

			temp[4] = -elements[4] * elements[10] * elements[15] +
				elements[4] * elements[11] * elements[14] +
				elements[8] * elements[6] * elements[15] -
				elements[8] * elements[7] * elements[14] -
				elements[12] * elements[6] * elements[11] +
				elements[12] * elements[7] * elements[10];

			temp[8] = elements[4] * elements[9] * elements[15] -
				elements[4] * elements[11] * elements[13] -
				elements[8] * elements[5] * elements[15] +
				elements[8] * elements[7] * elements[13] +
				elements[12] * elements[5] * elements[11] -
				elements[12] * elements[7] * elements[9];

			temp[12] = -elements[4] * elements[9] * elements[14] +
				elements[4] * elements[10] * elements[13] +
				elements[8] * elements[5] * elements[14] -
				elements[8] * elements[6] * elements[13] -
				elements[12] * elements[5] * elements[10] +
				elements[12] * elements[6] * elements[9];

			temp[1] = -elements[1] * elements[10] * elements[15] +
				elements[1] * elements[11] * elements[14] +
				elements[9] * elements[2] * elements[15] -
				elements[9] * elements[3] * elements[14] -
				elements[13] * elements[2] * elements[11] +
				elements[13] * elements[3] * elements[10];

			temp[5] = elements[0] * elements[10] * elements[15] -
				elements[0] * elements[11] * elements[14] -
				elements[8] * elements[2] * elements[15] +
				elements[8] * elements[3] * elements[14] +
				elements[12] * elements[2] * elements[11] -
				elements[12] * elements[3] * elements[10];

			temp[9] = -elements[0] * elements[9] * elements[15] +
				elements[0] * elements[11] * elements[13] +
				elements[8] * elements[1] * elements[15] -
				elements[8] * elements[3] * elements[13] -
				elements[12] * elements[1] * elements[11] +
				elements[12] * elements[3] * elements[9];

			temp[13] = elements[0] * elements[9] * elements[14] -
				elements[0] * elements[10] * elements[13] -
				elements[8] * elements[1] * elements[14] +
				elements[8] * elements[2] * elements[13] +
				elements[12] * elements[1] * elements[10] -
				elements[12] * elements[2] * elements[9];

			temp[2] = elements[1] * elements[6] * elements[15] -
				elements[1] * elements[7] * elements[14] -
				elements[5] * elements[2] * elements[15] +
				elements[5] * elements[3] * elements[14] +
				elements[13] * elements[2] * elements[7] -
				elements[13] * elements[3] * elements[6];

			temp[6] = -elements[0] * elements[6] * elements[15] +
				elements[0] * elements[7] * elements[14] +
				elements[4] * elements[2] * elements[15] -
				elements[4] * elements[3] * elements[14] -
				elements[12] * elements[2] * elements[7] +
				elements[12] * elements[3] * elements[6];

			temp[10] = elements[0] * elements[5] * elements[15] -
				elements[0] * elements[7] * elements[13] -
				elements[4] * elements[1] * elements[15] +
				elements[4] * elements[3] * elements[13] +
				elements[12] * elements[1] * elements[7] -
				elements[12] * elements[3] * elements[5];

			temp[14] = -elements[0] * elements[5] * elements[14] +
				elements[0] * elements[6] * elements[13] +
				elements[4] * elements[1] * elements[14] -
				elements[4] * elements[2] * elements[13] -
				elements[12] * elements[1] * elements[6] +
				elements[12] * elements[2] * elements[5];

			temp[3] = -elements[1] * elements[6] * elements[11] +
				elements[1] * elements[7] * elements[10] +
				elements[5] * elements[2] * elements[11] -
				elements[5] * elements[3] * elements[10] -
				elements[9] * elements[2] * elements[7] +
				elements[9] * elements[3] * elements[6];

			temp[7] = elements[0] * elements[6] * elements[11] -
				elements[0] * elements[7] * elements[10] -
				elements[4] * elements[2] * elements[11] +
				elements[4] * elements[3] * elements[10] +
				elements[8] * elements[2] * elements[7] -
				elements[8] * elements[3] * elements[6];

			temp[11] = -elements[0] * elements[5] * elements[11] +
				elements[0] * elements[7] * elements[9] +
				elements[4] * elements[1] * elements[11] -
				elements[4] * elements[3] * elements[9] -
				elements[8] * elements[1] * elements[7] +
				elements[8] * elements[3] * elements[5];

			temp[15] = elements[0] * elements[5] * elements[10] -
				elements[0] * elements[6] * elements[9] -
				elements[4] * elements[1] * elements[10] +
				elements[4] * elements[2] * elements[9] +
				elements[8] * elements[1] * elements[6] -
				elements[8] * elements[2] * elements[5];

			double determinant = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];

			if (determinant == 0)
			{
				std::cout << "Determinant is 0. Not Invertable\n" << std::endl;
				return *this;
			}

			determinant = 1.0 / determinant;

			for (int i = 0; i < 4 * 4; i++)
				elements[i] = temp[i] * determinant;

			return *this;
		}

		mat4 mat4::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = 2.0f / (right - left);

			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.elements[2 + 2 * 4] = 2.0f / (near - far);

			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (near + far) / (near - far) ;

			return result;
		}

		mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);
			
			float q = 1.0f / (float)tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;

			return result;
		}

		mat4 mat4::LookAt(const vec3& camera, const vec3& object, const vec3& up)
		{
			mat4 result = Identity();
			vec3 f = (object - camera).Normalize();
			vec3 s = f.Cross(up.Normalize());
			vec3 u = s.Cross(f);

			result.elements[0 + 0 * 4] = s.x;
			result.elements[0 + 1 * 4] = s.y;
			result.elements[0 + 2 * 4] = s.z;

			result.elements[1 + 0 * 4] = u.x;
			result.elements[1 + 1 * 4] = u.y;
			result.elements[1 + 2 * 4] = u.z;

			result.elements[2 + 0 * 4] = -f.x;
			result.elements[2 + 1 * 4] = -f.y;
			result.elements[2 + 2 * 4] = -f.z;

			return result * Translation(vec3(-camera.x, -camera.y, -camera.z));
		}

		mat4 mat4::Translation(const vec3& translation)
		{
			mat4 result(1.0f);

			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;

			return result;
		}

		mat4 mat4::Rotation(float angle, const vec3 &axis)
		{
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * z * omc + c;

			return result;
		}

		mat4 mat4::Scale(const vec3 &scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;

			return result;
		}

		mat4 mat4::X_Rotation(float angle)
		{
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);

			result.elements[1 + 1 * 4] = c;
			result.elements[2 + 1 * 4] = s;
			result.elements[1 + 2 * 4] = -s;
			result.elements[2 + 2 * 4] = c;

			return result;
		}

		mat4 mat4::Y_Rotation(float angle)
		{
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);

			result.elements[0 + 0 * 4] = c;
			result.elements[2 + 0 * 4] = -s;
			result.elements[0 + 2 * 4] = s;
			result.elements[2 + 2 * 4] = c;

			return result;
		}

		mat4 mat4::Z_Rotation(float angle)
		{
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);

			result.elements[0 + 0 * 4] = c;
			result.elements[1 + 0 * 4] = s;
			result.elements[0 + 1 * 4] = -s;
			result.elements[1 + 1 * 4] = c;

			return result;
		}


		mat4 mat4::X_Reflection()
		{
			mat4 result(-1.0f);

			result.elements[0 + 0 * 4] = 1.0f;

			return result;
		}

		mat4 mat4::Y_Reflection()
		{
			mat4 result(-1.0f);

			result.elements[1 + 1 * 4] = 1.0f;

			return result;
		}

		mat4 mat4::Z_Reflection()
		{
			mat4 result(-1.0f);

			result.elements[2 + 2 * 4] = 1.0f;

			return result;
		}

		mat4 mat4::XY_Reflection()
		{
			mat4 result(1.0f);

			result.elements[2 + 2 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::XZ_Reflection()
		{
			mat4 result(1.0f);

			result.elements[1 + 1 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::YZ_Reflection()
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * 4] = -1.0f;

			return result;
		}

		mat4 mat4::Shear(float yx, float zx, float xy, float zy, float xz, float yz)
		{
			mat4 result(1.0f);

			result.elements[0 + 1 * 4] = yz;
			result.elements[0 + 2 * 4] = zx;
			result.elements[1 + 0 * 4] = xy;
			result.elements[1 + 2 * 4] = zy;
			result.elements[2 + 0 * 4] = xz;
			result.elements[2 + 1 * 4] = yz;

			return result;
		}

		mat4 mat4::Invert(const mat4& matrix)
		{
			mat4 result = matrix;
			return result.Invert();
		}

		mat4 mat4::Transpose(const mat4& matrix)
		{
			return mat4(
				vec4(matrix.rows[0].x, matrix.rows[1].x, matrix.rows[2].x, matrix.rows[3].x),
				vec4(matrix.rows[0].y, matrix.rows[1].y, matrix.rows[2].y, matrix.rows[3].y),
				vec4(matrix.rows[0].z, matrix.rows[1].z, matrix.rows[2].z, matrix.rows[3].z),
				vec4(matrix.rows[0].w, matrix.rows[1].w, matrix.rows[2].w, matrix.rows[3].w)
				);
		}

		std::ostream &operator<<(std::ostream &stream, const mat4 &matrix)
		{
			stream << "mat4: (" << matrix.rows[0].x << ", " << matrix.rows[1].x << ", " << matrix.rows[2].x << ", " << matrix.rows[3].x << "),\n      ";
			stream <<       "(" << matrix.rows[0].y << ", " << matrix.rows[1].y << ", " << matrix.rows[2].y << ", " << matrix.rows[3].y << "),\n      ";
			stream <<       "(" << matrix.rows[0].z << ", " << matrix.rows[1].z << ", " << matrix.rows[2].z << ", " << matrix.rows[3].z << "),\n      ";
			stream <<       "(" << matrix.rows[0].w << ", " << matrix.rows[1].w << ", " << matrix.rows[2].w << ", " << matrix.rows[3].w << ")\n";
			return stream;
		}
	}
}