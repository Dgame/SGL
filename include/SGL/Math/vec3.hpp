#ifndef SGL_VE3_HPP
#define SGL_VE3_HPP

#include <algorithm>
#include <SGL/Core/Types.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace sgl {
	template <typename T>
	struct vec3 {
		T x = 0;
		T y = 0;
		T z = 0;

		vec3() = default;
		explicit vec3(T mx, T my, T mz);

		template <typename U>
		vec3(const vec3<U>&);

		float length() const {
			return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
		}
	};

	using vec3i = vec3<int32>;
	using vec3s = vec3<int16>;
	using vec3f = vec3<float>;

	template <typename T>
	vec3<T>::vec3(T mx, T my, T mz) :
		x(mx), y(my), z(mz)
	{

	}

	template <typename T>
	template <typename U>
	vec3<T>::vec3(const vec3<U>& vec) :
		x(static_cast<T>(vec.x)),
		y(static_cast<T>(vec.y)),
		z(static_cast<T>(vec.z))
	{

	}

	template <typename T>
	vec3<T> Rotate(const vec3<T>& vec, float angle, const vec3<T>& rot) {
		const vec3<T> norm1 = Normalize(vec);
		const vec3<T> norm2 = Normalize(rot);

		const float rho_rad = angle / 180 * M_PI;
		const float c = std::cos(rho_rad);
		const float s = std::sin(rho_rad);
		const float t = 1 - c;

		const float norm_final_x = norm1.x * (t * norm2.x * norm2.x + c) + norm1.y * (t * norm2.x * norm2.y - s * norm2.z) + norm1.z * (t * norm2.x * norm2.z + s * norm2.y);
		const float norm_final_y = norm1.x * (t * norm2.x * norm2.y + s * norm2.z) + norm1.y * (t * norm2.y * norm2.y + c) + norm1.z * (t * norm2.y * norm2.z - s * norm2.x);
		const float norm_final_z = norm1.x * (t * norm2.x * norm2.z - s * norm2.y) + norm1.y * (t * norm2.y * norm2.z + s * norm2.x) + norm1.z * (t * norm2.z * norm2.z + c);

		vec3f final_norm(norm_final_x, norm_final_y, norm_final_z);
		final_norm *= vec.length();

		return final_norm;
	}

	template <typename T>
	vec3<T> Normalize(const vec3<T>& vec) {
		const float len = vec.length();
		if (len > 0)
			return vec / len;
		return vec;
	}

	template <typename T>
	float Dot(const vec3<T>& lhs, const vec3<T>& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	template <typename T>
	float Angle(const vec3<T>& lhs, const vec3<T>& rhs) {
		return acosf(Dot(lhs, rhs) / (lhs.length() * rhs.length()));
	}

	template <typename T>
	float Diff(const vec3<T>& lhs, const vec3<T>& rhs) {
		const float vx = std::pow(lhs.x - rhs.x, 2);
		const float vy = std::pow(lhs.y - rhs.y, 2);
		const float vz = std::pow(lhs.z - rhs.z, 2);

		return std::sqrt(vx + vy + vz);
	}

	template <typename T>
	vec3<T> Cross(const vec3<T>& lhs, const vec3<T>& rhs) {
		const float cx = (lhs.y * rhs.z) - (lhs.z * rhs.y);
		const float cy = (lhs.z * rhs.x) - (lhs.x * rhs.z);
		const float cz = (lhs.x * rhs.y) - (lhs.y * rhs.x);

		return vec3<T>(cx, cy, cz);
	}

	template <typename T>
	vec3<T>& operator +=(vec3<T>& lhs, const vec3<T>& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;

		return lhs;
	}

	template <typename T>
	vec3<T>& operator -=(vec3<T>& lhs, const vec3<T>& rhs) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;

		return lhs;
	}

	template <typename T>
	vec3<T> operator +(const vec3<T>& lhs, const vec3<T>& rhs) {
		return vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	template <typename T>
	vec3<T> operator -(const vec3<T>& lhs, const vec3<T>& rhs) {
		return vec3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	template <typename T>
	vec3<T> operator -(const vec3<T>& lhs) {
		return vec3<T>(-lhs.x, -lhs.y, -lhs.z);
	}

	template <typename T>
	vec3<T> operator *(const vec3<T>& lhs, T num) {
		return vec3<T>(lhs.x * num, lhs.y * num, lhs.z * num);
	}

	template <typename T>
	vec3<T>& operator *=(vec3<T>& lhs, T num) {
		lhs.x *= num;
		lhs.y *= num;
		lhs.z *= num;

		return lhs;
	}

	template <typename T>
	vec3<T> operator /(const vec3<T>& lhs, T num) {
		return vec3<T>(lhs.x / num, lhs.y / num, lhs.z / num);
	}

	template <typename T>
	vec3<T>& operator /=(vec3<T>& lhs, T num) {
		lhs.x /= num;
		lhs.y /= num;
		lhs.z /= num;

		return lhs;
	}

	template <typename T>
	bool operator ==(const vec3<T>& lhs, const vec3<T>& rhs) {
		return lhs.x == rhs.x && lhs.y = rhs.y && lhs.z == rhs.z;
	}

	template <typename T>
	bool operator !=(const vec3<T>& lhs, const vec3<T>& rhs) {
		return !(lhs == rhs);
	}
}

#endif
