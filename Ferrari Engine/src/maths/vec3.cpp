#include "vec3.h"
#include "vec2.h"
#include "vec4.h"
#include "mat4.h"
#include "mat3.h"

namespace ferrari {
	namespace maths {
		
		//vec3::vec3()
		//	: x(0.0f), y(0.0f), z(0.0f) {}

		vec3::vec3(float scalar)
			: x(scalar), y(scalar), z(scalar) {}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z) {}
		
		vec3::vec3(const float &x, const float &y)
			: x(x), y(y), z(0.0f) {}

		vec3::vec3(const vec2& other)
			: x(other.x), y(other.y), z(0.0f) {}

		vec3::vec3(const vec4& other)
			: x(other.x), y(other.y), z(other.z) {}

		vec3::vec3(const vec2& xy, float z)
			: x(xy.x), y(xy.y), z(z) {}

		vec3 vec3::Up()
		{
			return vec3(0.0f, 1.0f, 0.0f);
		}

		vec3 vec3::Down()
		{
			return vec3(0.0f, -1.0f, 0.0f);
		}

		vec3 vec3::Left()
		{
			return vec3(-1.0f, 0.0f, 0.0f);
		}

		vec3 vec3::Right()
		{
			return vec3(1.0f, 0.0f, 0.0f);
		}

		vec3 vec3::Near()
		{
			return vec3(0.0f, 0.0f, 1.0f);
		}

		vec3 vec3::Far()
		{
			return vec3(0.0f, 0.0f, -1.0f);
		}

		vec3 vec3::Zero()
		{
			return vec3(0.0f, 0.0f, 0.0f);
		}

		vec3 vec3::X_Axis()
		{
			return vec3(1.0f, 0.0f, 0.0f);
		}

		vec3 vec3::Y_Axis()
		{
			return vec3(0.0f, 1.0f, 0.0f);
		}

		vec3 vec3::Z_Axis()
		{
			return vec3(0.0f, 0.0f, 1.0f);
		}

		vec3& vec3::Add(const vec3 &other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::Subtract(const vec3 &other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::Multiply(const vec3 &other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::Divide(const vec3 &other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3& vec3::Add(float value)
		{
			x += value;
			y += value;
			z += value;

			return *this;
		}

		vec3& vec3::Subtract(float value)
		{
			x -= value;
			y -= value;
			z -= value;

			return *this;
		}

		vec3& vec3::Multiply(float value)
		{
			x *= value;
			y *= value;
			z *= value;

			return *this;
		}

		vec3& vec3::Divide(float value)
		{
			x /= value;
			y /= value;
			z /= value;

			return *this;
		}

		vec3 operator+(vec3 left, const vec3 &right)
		{
			return left.Add(right);
		}

		vec3 operator-(vec3 left, const vec3 &right)
		{
			return left.Subtract(right);
		}

		vec3 operator*(vec3 left, const vec3 &right)
		{
			return left.Multiply(right);
		}

		vec3 operator/(vec3 left, const vec3 &right)
		{
			return left.Divide(right);
		}

		vec3 operator+(vec3 left, float value)
		{
			return left.Add(value);
		}

		vec3 operator-(vec3 left, float value)
		{
			return left.Subtract(value);
		}

		vec3 operator*(vec3 left, float value)
		{
			return left.Multiply(value);
		}

		vec3 operator/(vec3 left, float value)
		{
			return left.Divide(value);
		}

		vec3& vec3::operator+=(const vec3 &other)
		{
			return Add(other);
		}

		vec3& vec3::operator-=(const vec3 &other)
		{
			return Subtract(other);
		}

		vec3& vec3::operator*=(const vec3 &other)
		{
			return Multiply(other);
		}

		vec3& vec3::operator/=(const vec3 &other)
		{
			return Divide(other);
		}

		vec3& vec3::operator+=(float value)
		{
			return Add(value);
		}

		vec3& vec3::operator-=(float value)
		{
			return Subtract(value);
		}

		vec3& vec3::operator*=(float value)
		{
			return Multiply(value);
		}

		vec3& vec3::operator/=(float value)
		{
			return Divide(value);
		}

		bool vec3::operator==(const vec3 &other)
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3 &other)
		{
			return !(*this == other);
		}

		bool vec3::operator<(const vec3 &other) const
		{
			return x < other.x && y < other.y && z < other.z;
		}

		bool vec3::operator<=(const vec3 &other) const
		{
			return x <= other.x && y <= other.y && z <= other.z;
		}

		bool vec3::operator>(const vec3 &other) const
		{
			return x > other.x && y > other.y && z > other.z;
		}

		bool vec3::operator>=(const vec3 &other) const
		{
			return x >= other.x && y >= other.y && z >= other.z;
		}

		float vec3::sqrLength() const
		{
			return x * x + y * y + z * z;
		}

		vec3 operator-(const vec3& vector)
		{
			return vec3(-vector.x, -vector.y, -vector.z);
		}

		float vec3::Length() const
		{
			return sqrt(sqrLength());
		}

		vec3 vec3::Normalize() const
		{
			float unit_vector = 1 / Length();
			return vec3(x * unit_vector, y * unit_vector, z * unit_vector);
		}

		float vec3::Dot(const vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		float vec3::cos_theta(const vec3& right)
		{
			return (this->Dot(right)) / (this->Length() * right.Length());
		}

		vec3 vec3::Cross(const vec3& other) const
		{
			return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
		}

		float vec3::Distance(const vec3& other) const
		{
			float a = x - other.x;
			float b = y - other.y;
			float c = z - other.z;
			return sqrt(a * a + b * b + c * c);
		}

		vec3 vec3::multiply(const mat4& matrix) const
		{
			return vec3(
				matrix.columns[0].x * x + matrix.columns[1].x * y + matrix.columns[2].x * z + matrix.columns[3].x,
				matrix.columns[0].y * x + matrix.columns[1].y * y + matrix.columns[2].y * z + matrix.columns[3].y,
				matrix.columns[0].z * x + matrix.columns[1].z * y + matrix.columns[2].z * z + matrix.columns[3].z
				);
		}

		vec3 vec3::multiply(const mat3& matrix) const
		{
			return vec3(
				matrix.columns[0].x * x + matrix.columns[1].x * y + matrix.columns[2].x,
				matrix.columns[0].y * x + matrix.columns[1].y * y + matrix.columns[2].y,
				matrix.columns[0].z * x + matrix.columns[1].z * y + matrix.columns[2].z
				);
		}

		vec3 operator*(const mat4& left, const vec3& right)
		{
			return right.multiply(left);
		}

		vec3 operator*(const mat3& left, const vec3& right)
		{
			return right.multiply(left);
		}

		std::ostream &operator<<(std::ostream &stream, const vec3 &vector)
		{
			stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
			return stream;
		}
	}
}