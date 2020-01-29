#pragma once

#include "mat4.h"
#include "vec2.h"

namespace ferrari {
	namespace maths {
		
		struct Quaternion
		{
			float r, i, j, k;

			Quaternion();
			Quaternion(const Quaternion& quaternion);
			Quaternion(float x, float y, float z, float w);
			Quaternion(const vec2& xy, float z, float w);
			Quaternion(const vec3& xyz, float w);
			Quaternion(const vec4& vec);
			Quaternion(float scalar);

			Quaternion& SetXYZ(const vec3& vec);
			const vec3 GetXYZ() const;

			Quaternion& SetElem(int idx, float value);
			float GetElem(int idx) const;

			vec3 GetAxis() const;
			vec3 ToEulerAngles() const;

			Quaternion& operator=(const Quaternion& quat);
			const Quaternion operator+(const Quaternion& Quaternion) const;
			const Quaternion operator-(const Quaternion& Quaternion) const;
			const Quaternion operator*(const Quaternion& Quaternion) const;
			const Quaternion operator/(const Quaternion& Quaternion) const;
			const Quaternion operator+(float scalar) const;
			const Quaternion operator-(float scalar) const;
			const Quaternion operator*(float scalar) const;
			const Quaternion operator/(float scalar) const;
			Quaternion& operator+=(const Quaternion& Quaternion);
			Quaternion& operator-=(const Quaternion& Quaternion);
			Quaternion& operator*=(const Quaternion& Quaternion);
			Quaternion& operator/=(const Quaternion& Quaternion);
			Quaternion& operator+=(float scalar);
			Quaternion& operator-=(float scalar);
			Quaternion& operator*=(float scalar);
			Quaternion& operator/=(float scalar);
			bool operator==(const Quaternion& quaternion) const;
			bool operator!=(const Quaternion& quaternion) const;
			const Quaternion operator-() const;
			float operator[](int idx) const;

			static Quaternion Identity();
			static Quaternion FromEulerAngles(const vec3& angles);

			static const Quaternion RotationX(float radians);
			static const Quaternion RotationY(float radians);
			static const Quaternion RotationZ(float radians);
			static const Quaternion Rotation(const vec3& unitVec0, const vec3& unitVec1);
			static const Quaternion Rotation(float radians, const vec3& unitVec);
			static float Length(const Quaternion& quaternion);
			static const Quaternion Normalize(const Quaternion& quaternion);
			static const Quaternion NormalizeEst(const Quaternion& quaternion);
			static float Norm(const Quaternion& quaternion);

			static vec3 Rotate(const Quaternion & quat, const vec3 & vec);

			float Dot(const Quaternion& other) const;
			Quaternion Conjugate() const;

			const Quaternion Select(const Quaternion& quat0, const Quaternion& quat1, bool select1);
		
			friend std::ostream &operator<<(std::ostream &stream, const Quaternion &quat);
		};
	}
}