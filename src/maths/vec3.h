#pragma once

#include <iostream>

namespace ferrari {
	namespace maths {

		struct vec2;
		struct vec4;
		struct mat4;
		struct mat3;

		struct vec3
		{
			float x, y, z;

			vec3() = default;
			vec3(float scalar);
			vec3(float x, float y, float z);
			vec3(const float &x,const float &y);
			vec3(const vec2& other);
			vec3(const vec4& other);
			vec3(const vec2& xy, float w);

			static vec3 Up();
			static vec3 Down();
			static vec3 Left();
			static vec3 Right();
			static vec3 Near();
			static vec3 Far();
			static vec3 Zero();

			static vec3 X_Axis();
			static vec3 Y_Axis();
			static vec3 Z_Axis();

			vec3 &Add(const vec3 &other);
			vec3 &Subtract(const vec3 &other);
			vec3 &Multiply(const vec3 &other);
			vec3 &Divide(const vec3 &other);

			vec3& Add(float value);
			vec3& Subtract(float value);
			vec3& Multiply(float value);
			vec3& Divide(float value);

			friend vec3 operator+(vec3 left, const vec3 &right);
			friend vec3 operator-(vec3 left, const vec3 &right);
			friend vec3 operator*(vec3 left, const vec3 &right);
			friend vec3 operator/(vec3 left, const vec3 &right);

			friend vec3 operator+(vec3 left, float value);
			friend vec3 operator-(vec3 left, float value);
			friend vec3 operator*(vec3 left, float value);
			friend vec3 operator/(vec3 left, float value);

			vec3 &operator+=(const vec3 &other);
			vec3 &operator-=(const vec3 &other);
			vec3 &operator*=(const vec3 &other);
			vec3 &operator/=(const vec3 &other);

			vec3& operator+=(float value);
			vec3& operator-=(float value);
			vec3& operator*=(float value);
			vec3& operator/=(float value);

			bool operator==(const vec3 &other);
			bool operator!=(const vec3 &other);

			bool operator<(const vec3& other) const;
			bool operator<=(const vec3& other) const;
			bool operator>(const vec3& other) const;
			bool operator>=(const vec3& other) const;

			float sqrLength() const;
			float Length() const;
			vec3 Normalize() const;

			float Dot(const vec3& other) const;
			vec3 Cross(const vec3& other) const;
			float cos_theta(const vec3& right);
			float Distance(const vec3& other) const;

			vec3 multiply(const mat4& matrix) const;
			vec3 multiply(const mat3& matrix) const;
			friend vec3 operator*(const mat4& left, const vec3& right);
			friend vec3 operator*(const mat3& left, const vec3& right);

			friend std::ostream &operator<<(std::ostream &stream, const vec3 &vector);
		};

	}
}