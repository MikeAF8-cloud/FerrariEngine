#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include "mat4.h"

namespace ferrari {
	namespace maths {

		vec4::vec4(const float &x, const float &y, const float &z, const float &w)
			: x(x), y(y), z(z), w(w) {}

		vec4::vec4(float scalar)
			:x(scalar), y(scalar), z(scalar), w(scalar) {}

		vec4::vec4(const vec3& xyz, float w)
			:x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}

		vec4::vec4(const vec2& xy, float z, float w)
			: x(xy.x), y(xy.y), z(z), w(w) {}

		vec4::vec4(const vec2& other)
			: x(other.x), y(other.y), z(0.0f), w(0.0f) {}

		vec4::vec4(const vec3& other)
			: x(other.x), y(other.y), z(other.z), w(0.0f) {}

		vec4 vec4::Up()
		{
			return vec4(0.0f, 1.0f, 0.0f, 1.0f);
		}

		vec4 vec4::Down()
		{
			return vec4(0.0f, -1.0f, 0.0f, 1.0f);
		}

		vec4 vec4::Left()
		{
			return vec4(-1.0f, 0.0f, 0.0f, 1.0f);
		}

		vec4 vec4::Right()
		{
			return vec4(1.0f, 0.0f, 0.0f, 1.0f);
		}

		vec4 vec4::Near()
		{
			return vec4(0.0f, 0.0f, 1.0f, 1.0f);
		}

		vec4 vec4::Far()
		{
			return vec4(0.0f, 0.0f, -1.0f, 1.0f);
		}

		vec4 vec4::Up(float w)
		{
			return vec4(0.0f, 1.0f, 0.0f, w);
		}

		vec4 vec4::Down(float w)
		{
			return vec4(0.0f, -1.0f, 0.0f, w);
		}

		vec4 vec4::Left(float w)
		{
			return vec4(-1.0f, 0.0f, 0.0f, w);
		}

		vec4 vec4::Right(float w)
		{
			return vec4(1.0f, 0.0f, 0.0f, w);
		}

		vec4 vec4::Near(float w)
		{
			return vec4(0.0f, 0.0f, 1.0f, w);
		}

		vec4 vec4::Far(float w)
		{
			return vec4(0.0f, 0.0f, -1.0f, w);
		}

		vec4 vec4::Zero()
		{
			return vec4(0.0f, 0.0f, 0.0f, 0.0f);
		}

		vec4 vec4::X_Axis()
		{
			return vec4(1.0f, 0.0f, 0.0f, 1.0f);
		}

		vec4 vec4::Y_Axis()
		{
			return vec4(0.0f, 1.0f, 0.0f, 1.0f);
		}

		vec4 vec4::Z_Axis()
		{
			return vec4(0.0f, 0.0f, 1.0f, 1.0f);
		}

		vec4 vec4::X_Axis(float w)
		{
			return vec4(1.0f, 0.0f, 0.0f, w);
		}

		vec4 vec4::Y_Axis(float w)
		{
			return vec4(0.0f, 1.0f, 0.0f, w);
		}

		vec4 vec4::Z_Axis(float w)
		{
			return vec4(0.0f, 0.0f, 1.0f, w);
		}

		vec4 &vec4::Add(const vec4 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		vec4 &vec4::Subtract(const vec4 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		vec4 &vec4::Multiply(const vec4 &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		vec4 &vec4::Divide(const vec4 &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		vec4& vec4::Add(float value)
		{
			x += value;
			y += value;
			z += value;
			w += value;

			return *this;
		}

		vec4& vec4::Subtract(float value)
		{
			x -= value;
			y -= value;
			z -= value;
			w += value;

			return *this;
		}

		vec4& vec4::Multiply(float value)
		{
			x *= value;
			y *= value;
			z *= value;
			w *= value;

			return *this;
		}

		vec4& vec4::Divide(float value)
		{
			x /= value;
			y /= value;
			z /= value;
			w /= value;

			return *this;
		}

		vec4 operator+(vec4 left, const vec4 &right)
		{
			return left.Add(right);
		}

		vec4 operator-(vec4 left, const vec4 &right)
		{
			return left.Subtract(right);
		}

		vec4 operator*(vec4 left, const vec4 &right)
		{
			return left.Multiply(right);
		}

		vec4 operator/(vec4 left, const vec4 &right)
		{
			return left.Divide(right);
		}

		vec4 operator+(vec4 left, float value)
		{
			return left.Add(value);
		}

		vec4 operator-(vec4 left, float value)
		{
			return left.Subtract(value);
		}

		vec4 operator*(vec4 left, float value)
		{
			return left.Multiply(value);
		}

		vec4 operator/(vec4 left, float value)
		{
			return left.Divide(value);
		}

		vec4 &vec4::operator+=(const vec4 &other)
		{
			return Add(other);
		}

		vec4 &vec4::operator-=(const vec4 &other)
		{
			return Subtract(other);
		}

		vec4 &vec4::operator*=(const vec4 &other)
		{
			return Multiply(other);
		}

		vec4 &vec4::operator/=(const vec4 &other)
		{
			return Divide(other);
		}

		vec4& vec4::operator+=(float value)
		{
			return Add(value);
		}

		vec4& vec4::operator-=(float value)
		{
			return Subtract(value);
		}

		vec4& vec4::operator*=(float value)
		{
			return Multiply(value);
		}

		vec4& vec4::operator/=(float value)
		{
			return Divide(value);
		}

		bool vec4::operator==(const vec4 &other)
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		bool vec4::operator!=(const vec4 &other)
		{
			return !(*this == other);
		}

		bool vec4::operator<(const vec4 &other) const
		{
			return x < other.x && y < other.y && z < other.z && w < other.w;
		}

		bool vec4::operator<=(const vec4 &other) const
		{
			return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
		}

		bool vec4::operator>(const vec4 &other) const
		{
			return x > other.x && y > other.y && z > other.z && w > other.w;
		}

		bool vec4::operator>=(const vec4 &other) const
		{
			return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
		}

		float vec4::sqrLength() const
		{
			return x * x + y * y + z * z + w * w;
		}

		float vec4::Length() const
		{
			return sqrt(sqrLength());
		}

		vec4 vec4::Normalize() const
		{
			float unit_vector = 1 / Length();
			return vec4(x * unit_vector, y * unit_vector, z * unit_vector, w * unit_vector);
		}

		float vec4::Dot(const vec4& other) const
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		float vec4::cos_theta(const vec4& right)
		{
			return (this->Dot(right)) / (this->Length() * right.Length());
		}

		float vec4::Distance(const vec4& other) const
		{
			float a = x - other.x;
			float b = y - other.y;
			float c = z - other.z;
			float d = w - other.w;

			return sqrt(a * a + b * b + c * c + d * d);
		}

		vec4 vec4::multiply(const mat4& matrix) const
		{
			return vec4(
				matrix.columns[0].x * x + matrix.columns[1].x * y + matrix.columns[2].x * z + matrix.columns[3].x * w,
				matrix.columns[0].y * x + matrix.columns[1].y * y + matrix.columns[2].y * z + matrix.columns[3].y * w,
				matrix.columns[0].z * x + matrix.columns[1].z * y + matrix.columns[2].z * z + matrix.columns[3].z * w,
				matrix.columns[0].w * x + matrix.columns[1].w * y + matrix.columns[2].w * z + matrix.columns[3].w * w
				);
		}

		vec4 operator*(const mat4& left, const vec4& right)
		{
			return right.multiply(left);
		}

		std::ostream &operator<<(std::ostream &stream, const vec4 &vector)
		{
			stream << "vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")\n";
			return stream;
		}
	}
}