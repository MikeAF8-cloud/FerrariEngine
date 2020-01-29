#pragma once

#include <iostream>

namespace ferrari {
	namespace maths {

		struct vec2;
		struct vec3;
		struct mat4;

		struct vec4
		{
			float x, y, z, w;

			vec4() = default;
			vec4(float scalar);
			vec4(const float &x, const float &y, const float &z, const float &w);
			vec4(const vec2& xy, float z, float w);
			vec4(const vec3& xyz, float w);
			vec4(const vec2& other);
			vec4(const vec3& other);

			static vec4 Up();
			static vec4 Down();
			static vec4 Left();
			static vec4 Right();
			static vec4 Near();
			static vec4 Far();

			static vec4 Up(float w);
			static vec4 Down(float w);
			static vec4 Left(float w);
			static vec4 Right(float w);
			static vec4 Near(float w);
			static vec4 Far(float w);
			static vec4 Zero();

			static vec4 X_Axis();
			static vec4 Y_Axis();
			static vec4 Z_Axis();

			static vec4 X_Axis(float w);
			static vec4 Y_Axis(float w);
			static vec4 Z_Axis(float w);

			vec4 &Add(const vec4 &other);
			vec4 &Subtract(const vec4 &other);
			vec4 &Multiply(const vec4 &other);
			vec4 &Divide(const vec4 &other);

			vec4& Add(float value);
			vec4& Subtract(float value);
			vec4& Multiply(float value);
			vec4& Divide(float value);

			friend vec4 operator+(vec4 left, const vec4 &right);
			friend vec4 operator-(vec4 left, const vec4 &right);
			friend vec4 operator*(vec4 left, const vec4 &right);
			friend vec4 operator/(vec4 left, const vec4 &right);

			friend vec4 operator+(vec4 left, float value);
			friend vec4 operator-(vec4 left, float value);
			friend vec4 operator*(vec4 left, float value);
			friend vec4 operator/(vec4 left, float value);

			vec4 &operator+=(const vec4 &other);
			vec4 &operator-=(const vec4 &other);
			vec4 &operator*=(const vec4 &other);
			vec4 &operator/=(const vec4 &other);

			vec4& operator+=(float value);
			vec4& operator-=(float value);
			vec4& operator*=(float value);
			vec4& operator/=(float value);

			bool operator==(const vec4 &other);
			bool operator!=(const vec4 &other);

			bool operator<(const vec4& other) const;
			bool operator<=(const vec4& other) const;
			bool operator>(const vec4& other) const;
			bool operator>=(const vec4& other) const;

			float sqrLength() const;
			float Length() const;
			vec4 Normalize() const;

			float Dot(const vec4& other) const;
			float cos_theta(const vec4& right);
			float Distance(const vec4& other) const;

			vec4 multiply(const mat4& matrix) const;
			friend vec4 operator*(const mat4& left, const vec4& right);

			friend std::ostream &operator<<(std::ostream &stream, const vec4 &vector);
		};

	}
}