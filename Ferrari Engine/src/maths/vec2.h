#pragma once

#include <iostream>

namespace ferrari {
	namespace maths {
		
		struct vec3;
		struct vec4;
		struct mat2;

		struct vec2
		{
			float x, y;

			vec2() = default;
			vec2(float scalar);
			vec2(const float &x, const float &y);
			vec2(const vec3 &other);
			vec2(const vec4 &other);

			static vec2 Up();
			static vec2 Down();
			static vec2 Left();
			static vec2 Right();
			static vec2 Zero();

			static vec2 X_Axis();
			static vec2 Y_Axis();

			vec2& Add(const vec2 &other);
			vec2& Subtract(const vec2 &other);
			vec2& Multiply(const vec2 &other);
			vec2& Divide(const vec2 &other);

			vec2& Add(float value);
			vec2& Subtract(float value);
			vec2& Multiply(float value);
			vec2& Divide(float value);

			vec2 Multiply(const mat2& matrix) const;
			friend vec2 operator*(const mat2& left, const vec2& right);

			friend vec2 operator+(vec2 left, const vec2 &right);
			friend vec2 operator-(vec2 left, const vec2 &right);
			friend vec2 operator*(vec2 left, const vec2 &right);
			friend vec2 operator/(vec2 left, const vec2 &right);

			friend vec2 operator+(vec2 left, float value);
			friend vec2 operator-(vec2 left, float value);
			friend vec2 operator*(vec2 left, float value);
			friend vec2 operator/(vec2 left, float value);

			vec2 &operator+=(const vec2 &other);
			vec2 &operator-=(const vec2 &other);
			vec2 &operator*=(const vec2 &other);
			vec2 &operator/=(const vec2 &other);

			vec2& operator+=(float value);
			vec2& operator-=(float value);
			vec2& operator*=(float value);
			vec2& operator/=(float value);

			bool operator==(const vec2 &other);
			bool operator!=(const vec2 &other);

			bool operator<(const vec2& other) const;
			bool operator<=(const vec2& other) const;
			bool operator>(const vec2& other) const;
			bool operator>=(const vec2& other) const;

			float sqrLength() const;
			float Length() const;
			vec2 Normalize() const;

			float Dot(const vec2& other) const;
			float cos_theta(const vec2& right);
			float Cross_Z(const vec2& other) const;
			vec2 Cross_Pos(float s);
			vec2 Cross_Neg(float s);
			float Distance(const vec2& other) const;

			friend std::ostream &operator<<(std::ostream &stream, const vec2 &vector);
		};

	}
}