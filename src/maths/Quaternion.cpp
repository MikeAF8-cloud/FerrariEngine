#include "Quaternion.h"

namespace ferrari {
	namespace maths {

		Quaternion::Quaternion()
			: r(0), i(0), j(0), k(0) {}

		Quaternion::Quaternion(const Quaternion& quaternion)
			: r(quaternion.r), i(quaternion.i), j(quaternion.j), k(quaternion.k) {}

		Quaternion::Quaternion(float x, float y, float z, float w)
			: r(x), i(y), j(z), k(w) {}

		Quaternion::Quaternion(const vec2& xy, float z, float w)
			: r(xy.x), i(xy.y), j(z), k(w) {}

		Quaternion::Quaternion(const vec3& xyz, float w)
			: r(xyz.x), i(xyz.y), j(xyz.z), k(w) {}

		Quaternion::Quaternion(const vec4& vec)
			: r(vec.x), i(vec.y), j(vec.z), k(vec.w) {}

		Quaternion::Quaternion(float scalar)
			: r(scalar), i(scalar), j(scalar), k(scalar) {}

		Quaternion& Quaternion::SetXYZ(const vec3& vec)
		{
			r = vec.x;
			i = vec.y;
			j = vec.z;

			return *this;
		}

		const vec3 Quaternion::GetXYZ() const
		{
			return vec3(r, i, j);
		}

		Quaternion& Quaternion::SetElem(int idx, float value)
		{
			*(&r + idx) = value;
			return *this;
		}

		float Quaternion::GetElem(int idx) const
		{
			return *(&r + idx);
		}

		vec3 Quaternion::GetAxis() const
		{
			float x = 1.0f - k * k;
			if (x < 0.0000001f) // Divide by zero safety check
				return vec3::X_Axis();

			float x2 = x * x;

			return GetXYZ() / x2;
		}

		Quaternion Quaternion::Identity()
		{
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		}

		vec3 Quaternion::ToEulerAngles() const
		{
			//roll, pitch, yaw
			return vec3(atan2(2 * r * i + 2 * j * k, 1 - 2 * r * r + 2 * i * i),
						asin(2 * r * j - 2 * i * k),
						atan2(2 * r * k + 2 * i + 2 * j, 1 - 2 * i * i + 2 * j * j)
						);
		}

		const Quaternion Quaternion::RotationX(float radians)
		{
			float angle = radians * 0.5f;
			return Quaternion(sin(angle), 0.0f, 0.0f, cos(angle));
		}

		const Quaternion Quaternion::RotationY(float radians)
		{
			float angle = radians * 0.5f;
			return Quaternion(0.0f, sin(angle), 0.0f, cos(angle));
		}

		const Quaternion Quaternion::RotationZ(float radians)
		{
			float angle = radians * 0.5f;
			return Quaternion(0.0f, 0.0f, sin(angle), cos(angle));
		}

		Quaternion& Quaternion::operator=(const Quaternion & Quaternion)
		{
			r = Quaternion.r;
			i = Quaternion.i;
			j = Quaternion.j;
			k = Quaternion.k;

			return *this;
		}

		const Quaternion Quaternion::operator+(const Quaternion& quaternion) const
		{
			return Quaternion(r + quaternion.r, i + quaternion.i, j + quaternion.j, k + quaternion.k);
		}

		const Quaternion Quaternion::operator-(const Quaternion& quaternion) const
		{
			return Quaternion(r - quaternion.r, i - quaternion.i, j - quaternion.j, k - quaternion.k);
		}

		const Quaternion Quaternion::operator*(const Quaternion& quat) const
		{
			return Normalize(Quaternion(
				(((r * quat.r) - (i * quat.i)) - (j * quat.j)) - (k * quat.k),
				(((r * quat.i) + (i * quat.r)) - (j * quat.k)) + (k * quat.j),
				(((r * quat.j) + (i * quat.k)) + (j * quat.r)) - (k * quat.i),
				(((r * quat.k) - (i * quat.j)) + (j * quat.i)) + (k * quat.r)
				));
		}

		const Quaternion Quaternion::operator/(const Quaternion& quat) const
		{
			float denominator = quat.r * quat.r + quat.i * quat.i + quat.j * quat.j + quat.k * quat.k;
			return Normalize(Quaternion(
				((r * quat.r) + (i * quat.i) + (j * quat.j) + (k * quat.k)) / denominator,
				((r * quat.i) - (i * quat.r) - (j * quat.k) + (k * quat.j)) / denominator,
				((r * quat.j) + (i * quat.k) - (j * quat.r) - (k * quat.i)) / denominator,
				((r * quat.k) - (i * quat.j) + (j * quat.i) - (k * quat.r)) / denominator
				));
		}

		const Quaternion Quaternion::operator+(float scalar) const
		{
			return Quaternion(r + scalar, i + scalar, j + scalar, k + scalar);
		}

		const Quaternion Quaternion::operator-(float scalar) const
		{
			return Quaternion(r - scalar, i - scalar, j - scalar, k - scalar);
		}

		const Quaternion Quaternion::operator*(float scalar) const
		{
			return Quaternion(r * scalar, i * scalar, j * scalar, k * scalar);
		}

		const Quaternion Quaternion::operator/(float scalar) const
		{
			return Quaternion(r / scalar, i / scalar, j / scalar, k / scalar);
		}

		Quaternion& Quaternion::operator+=(const Quaternion& Quaternion)
		{
			*this = *this + Quaternion;
			return *this;
		}

		Quaternion& Quaternion::operator-=(const Quaternion& Quaternion)
		{
			*this = *this - Quaternion;
			return *this;
		}

		Quaternion& Quaternion::operator/=(const Quaternion& Quaternion)
		{
			*this = *this - Quaternion;
			return *this;
		}

		Quaternion& Quaternion::operator*=(const Quaternion& Quaternion)
		{
			*this = *this * Quaternion;
			return *this;
		}

		Quaternion& Quaternion::operator+=(float scalar)
		{
			*this = *this + scalar;
			return *this;
		}

		Quaternion& Quaternion::operator-=(float scalar)
		{
			*this = *this - scalar;
			return *this;
		}

		Quaternion& Quaternion::operator*=(float scalar)
		{
			*this = *this * scalar;
			return *this;
		}

		Quaternion& Quaternion::operator/=(float scalar)
		{
			*this = *this / scalar;
			return *this;
		}

		bool Quaternion::operator==(const Quaternion & Quaternion) const
		{
			return (r == Quaternion.r) && (i == Quaternion.i) && (j == Quaternion.j) && (k == Quaternion.k);
		}

		bool Quaternion::operator!=(const Quaternion & Quaternion) const
		{
			return !(*this == Quaternion);
		}

		const Quaternion Quaternion::operator-() const
		{
			return Quaternion(-r, -i, -j, -k);
		}

		float Quaternion::operator[](int idx) const
		{
			return *(&r + idx);
		}

		//roll, pitch, yaw
		Quaternion Quaternion::FromEulerAngles(const vec3& angles)
		{
			float cy = cos(angles.z * 0.5);
			float cr = cos(angles.x * 0.5);
			float cp = cos(angles.y * 0.5);
			float sy = sin(angles.z * 0.5);
			float sr = sin(angles.x * 0.5);
			float sp = sin(angles.y * 0.5);
			
			return vec4(
				cy * cr * cp - sy * sr * sp,
				sy * sr * cp + cy * cr * sp,
				sy * cr * cp + cy * sr * sp,
				cy * sr * cp - sy * cr * sp
				);
		}

		const Quaternion Quaternion::Rotation(const vec3& unitVec0, const vec3& unitVec1)
		{
			float cosHalfAngleX2, recipCosHalfAngleX2;
			cosHalfAngleX2 = sqrt((2.0f * (1.0f + unitVec0.Dot(unitVec1))));
			recipCosHalfAngleX2 = (1.0f / cosHalfAngleX2);
			return Quaternion((unitVec0.Cross(unitVec1) * recipCosHalfAngleX2), (cosHalfAngleX2 * 0.5f));
		}

		const Quaternion Quaternion::Rotation(float radians, const vec3 & unitVec)
		{
			float angle = radians * 0.5f;
			return Quaternion((unitVec * sin(angle)), cos(angle));
		}

		vec3 Quaternion::Rotate(const Quaternion& quat, const vec3& vec)
		{
			float tmpX, tmpY, tmpZ, tmpW;
			tmpX = (((quat.k * vec.x) + (quat.i * vec.z)) - (quat.j * vec.y));
			tmpY = (((quat.k * vec.y) + (quat.j * vec.x)) - (quat.r * vec.z));
			tmpZ = (((quat.k * vec.z) + (quat.r * vec.y)) - (quat.i * vec.x));
			tmpW = (((quat.r * vec.x) + (quat.i * vec.y)) + (quat.j * vec.z));
			return vec3(
				((((tmpW * quat.r) + (tmpX * quat.k)) - (tmpY * quat.j)) + (tmpZ * quat.i)),
				((((tmpW * quat.i) + (tmpY * quat.k)) - (tmpZ * quat.r)) + (tmpX * quat.j)),
				((((tmpW * quat.j) + (tmpZ * quat.k)) - (tmpX * quat.j)) + (tmpY * quat.r))
				);
		}

		float Quaternion::Length(const Quaternion& quaternion)
		{
			return sqrt(Norm(quaternion));
		}

		const Quaternion Quaternion::Normalize(const Quaternion& quaternion)
		{
			float lenSqr, lenInv;
			lenSqr = Norm(quaternion);
			lenInv = rsqrt(lenSqr);
			return quaternion * lenInv;
		}

		const Quaternion Quaternion::NormalizeEst(const Quaternion& quaternion)
		{
			float lenSqr, lenInv;
			lenSqr = Norm(quaternion);
			lenInv = rsqrt(lenSqr);
			return quaternion * lenInv;
		}

		float Quaternion::Norm(const Quaternion& quaternion)
		{
			float result;
			result = (quaternion.r * quaternion.r);
			result = (result + (quaternion.i * quaternion.i));
			result = (result + (quaternion.j * quaternion.j));
			result = (result + (quaternion.k * quaternion.k));
			return result;
		}

		float Quaternion::Dot(const Quaternion& other) const
		{
			float result = (r * other.r);
			result = (result + (i * other.i));
			result = (result + (j * other.j));
			result = (result + (k * other.k));

			return result;
		}

		Quaternion Quaternion::Conjugate() const
		{
			return Quaternion(r, -i, -j, -k);
		}

		const Quaternion Quaternion::Select(const Quaternion& quat0, const Quaternion& quat1, bool select1)
		{
			return Quaternion(select1 ? quat1.r : quat0.r, select1 ? quat1.i : quat0.i, select1 ? quat1.j : quat0.j, select1 ? quat1.k : quat0.k);
		}

		std::ostream &operator<<(std::ostream &stream, const Quaternion &quat)
		{
			stream << "Quaterion: (" << quat.r << ", " << quat.i << ", " << quat.j << ", " << quat.k << ")\n";
			return stream;
		}
	}
}