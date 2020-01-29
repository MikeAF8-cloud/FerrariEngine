#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat2.h"

namespace ferrari {
	namespace maths {
		
		//vec2::vec2()
		//	:x(0.0f), y(0.0f) {}

		vec2::vec2(float scalar)
			: x(scalar), y(scalar) {}

		vec2::vec2(const float &x, const float &y)
			:x(x), y(y) {}

		vec2::vec2(const vec3 &other)
			: x(other.x), y(other.y) {}

		vec2::vec2(const vec4 &other)
			: x(other.x), y(other.y) {}

		vec2 vec2::Up()
		{
			return vec2(0.0f, 1.0f);
		}

		vec2 vec2::Down()
		{
			return vec2(0.0f, -1.0f);
		}

		vec2 vec2::Left()
		{
			return vec2(-1.0f, 0.0f);
		}

		vec2 vec2::Right()
		{
			return vec2(1.0f, 0.0f);
		}

		vec2 vec2::Zero()
		{
			return vec2(0.0f, 0.0f);
		}

		vec2 vec2::X_Axis()
		{
			return vec3(1.0f, 0.0f);
		}

		vec2 vec2::Y_Axis()
		{
			return vec3(0.0f, 1.0f);
		}

		vec2 &vec2::Add(const vec2 &other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		vec2 &vec2::Subtract(const vec2 &other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		vec2 &vec2::Multiply(const vec2 &other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		vec2 &vec2::Divide(const vec2 &other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		vec2& vec2::Add(float value)
		{
			x += value;
			y += value;

			return *this;
		}

		vec2& vec2::Subtract(float value)
		{
			x -= value;
			y -= value;

			return *this;
		}

		vec2& vec2::Multiply(float value)
		{
			x *= value;
			y *= value;

			return *this;
		}

		vec2& vec2::Divide(float value)
		{
			x /= value;
			y /= value;

			return *this;
		}

		vec2 vec2::Multiply(const mat2& matrix) const
		{
			return vec3(
				matrix.columns[0].x * x + matrix.columns[1].x * y,
				matrix.columns[0].y * x + matrix.columns[1].y * y
				);
		}

		vec2 operator*(const mat2& left, const vec2& right)
		{
			return right.Multiply(left);
		}

		vec2 operator+(vec2 left, const vec2 &right)
		{
			return left.Add(right);
		}

		vec2 operator-(vec2 left, const vec2 &right)
		{
			return left.Subtract(right);
		}

		vec2 operator*(vec2 left, const vec2 &right)
		{
			return left.Multiply(right);
		}

		vec2 operator/(vec2 left, const vec2 &right)
		{
			return left.Divide(right);
		}

		vec2 operator+(vec2 left, float value)
		{
			return left.Add(value);
		}

		vec2 operator-(vec2 left, float value)
		{
			return left.Subtract(value);
		}

		vec2 operator*(vec2 left, float value)
		{
			return left.Multiply(value);
		}

		vec2 operator/(vec2 left, float value)
		{
			return left.Divide(value);
		}

		vec2 &vec2::operator+=(const vec2 &other)
		{
			return Add(other);
		}

		vec2 &vec2::operator-=(const vec2 &other)
		{
			return Subtract(other);
		}

		vec2 &vec2::operator*=(const vec2 &other)
		{
			return Multiply(other);
		}

		vec2 &vec2::operator/=(const vec2 &other)
		{
			return Divide(other);
		}

		vec2& vec2::operator+=(float value)
		{
			return Add(value);
		}

		vec2& vec2::operator-=(float value)
		{
			return Subtract(value);
		}

		vec2& vec2::operator*=(float value)
		{
			return Multiply(value);
		}
		vec2& vec2::operator/=(float value)
		{
			return Divide(value);
		}

		bool vec2::operator==(const vec2 &other)
		{
			return x == other.x && y == other.y;
		}

		bool vec2::operator!=(const vec2 &other)
		{
			return !(*this == other);
		}

		bool vec2::operator<(const vec2 &other) const
		{
			return x < other.x && y < other.y;
		}

		bool vec2::operator<=(const vec2 &other) const
		{
			return x <= other.x && y <= other.y;
		}

		bool vec2::operator>(const vec2 &other) const
		{
			return x > other.x && y > other.y;
		}

		bool vec2::operator>=(const vec2 &other) const
		{
			return x >= other.x && y >= other.y;
		}

		float vec2::sqrLength() const
		{
			return x * x + y * y;
		}

		float vec2::Length() const
		{
			return sqrt(sqrLength());
		}

		vec2 vec2::Normalize() const
		{
			float unit_vector = 1 / Length();
			return vec2(x * unit_vector, y * unit_vector);
		}

		float vec2::Dot(const vec2& other) const
		{
			return x * other.x + y * other.y;
		}

		float vec2::cos_theta(const vec2& right)
		{
			return (this->Dot(right)) / (this->Length() * right.Length());
		}

		//will return a scalar on the z-axis
		float vec2::Cross_Z(const vec2& other) const
		{
			return x * other.y - y * other.x;
		}

		vec2 vec2::Cross_Pos(float s)
		{
			return vec2(s * y, -s * x);
		}

		vec2 vec2::Cross_Neg(float s)
		{
			return vec2(-s * y, s * x);
		}

		float vec2::Distance(const vec2& other) const
		{
			float a = x - other.x;
			float b = y - other.y;
			return sqrt(a * a + b * b);
		}

		std::ostream &operator<<(std::ostream &stream, const vec2 &vector)
		{
			stream << "vec2: (" << vector.x << ", " << vector.y << ")\n";
			return stream;
		}
	}
}