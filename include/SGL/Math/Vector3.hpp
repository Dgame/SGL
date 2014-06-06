#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>
#include <typeinfo>
#include <cmath>
#include <SGL/Core/Types.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace sgl {
	template <typename T>
	struct Vector3 {
		T x = 0;
		T y = 0;
		T z = 0;

		Vector3() = default;
		explicit Vector3(T px, T py, T pz = 0);

		template <typename U>
		explicit Vector3(const Vector3<U>& vec);

		void set(T x, T y, T z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		void move(T x, T y, T z = 0) {
			this->x += x;
			this->y += y;
			this->z += z;
		}

		float angle(const Vector3<T>& vec) const {
			return acosf(this->dot(vec) / (this->length() * vec.length()));
		}

		Vector3<T> rotate(float angle, int8 rx, int8 ry, int8 rz) const;

		Vector3<T> rotate(float angle, const Vector3<int8>& rot_axis) const {
			return this->rotate(angle, rot_axis.x, rot_axis.y, rot_axis.z);
		}

		Vector3<T> normalize() const;

		Vector3<T> abs() const {
			return Vector3<T>(std::abs(this->x), std::abs(this->y), std::abs(this->z));
		}

		/**
		* Calculate the diff between two vectors.
		*/
		float diff(const Vector3<T>& vec) const;

		float dot(const Vector3<T>& vec) const {
			return this->x * vec.x + this->y * vec.y + this->z * vec.z;
		}

		Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs) const;

		float length() const {
			return std::sqrt(std::pow(this->x, 2) * std::pow(this->y, 2) * std::pow(this->z, 2));
		}
	};

	template <typename T>
	Vector3<T>::Vector3(T px, T py, T pz) : x(px), y(py), z(pz) {

	}

	template <typename T>
	template <typename U>
	Vector3<T>::Vector3(const Vector3<U>& vec) :
		Vector3(static_cast<T>(vec.x), static_cast<T>(vec.y), static_cast<T>(vec.z)) {

	}

	template <typename T>
	Vector3<T> Vector3<T>::rotate(float angle, int8 rx, int8 ry, int8 rz) const {
		const float size1 = std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
		const float size2 = std::sqrt(std::pow(rx, 2) + std::pow(ry, 2) + std::pow(rz, 2));		const Vector3f norm(this->x / size1, this->y / size1, this->z / size1);
		const float rho_rad = angle / 180 * M_PI;

		const float c = std::cos(rho_rad);
		const float s = std::sin(rho_rad);
		const float t = 1 - c;

		const float tx = rx / size2;
		const float ty = ry / size2;
		const float tz = rz / size2;
		const float norm_final_x = norm.x * (t * tx * tx + c) + norm.y * (t * tx * ty - s * tz) + norm.z * (t * tx * tz + s * ty);
		const float norm_final_y = norm.x * (t * tx * ty + s * tz) + norm.y * (t * ty * ty + c) + norm.z * (t * ty * tz - s * tx);
		const float norm_final_z = norm.x * (t * tx * tz - s * ty) + norm.y * (t * ty * tz + s * tx) + norm.z * (t * tz * tz + c);

		Vector3f final_norm(norm_final_x * size1, norm_final_y * size1, norm_final_z * size1);
		//final_norm.x = std::round(final_norm.x * 1000000) / 1000000;
		//final_norm.y = std::round(final_norm.y * 1000000) / 1000000;
		//final_norm.z = std::round(final_norm.z * 1000000) / 1000000;

		return final_norm;
	}

	/**
	* Normalize the vector in which the coordinates are divided by the length.
	*/
	template <typename T>
	Vector3<T> Vector3<T>::normalize() const {
		const float len = this->length();
		if (len > 0) {
			Vector3<T> result = *this;
			result.x /= len;
			result.y /= len;
			result.z /= len;

			return result;
		}

		return *this;
	}

	/**
	* Calculate the diff between two vectors.
	*/
	template <typename T>
	float Vector3<T>::diff(const Vector3<T>& vec) const {
		const float vx = std::pow(this->x - vec.x, 2);
		const float vy = std::pow(this->y - vec.y, 2);
		const float vz = std::pow(this->z - vec.z, 2);

		return std::sqrt(vx + vy + vz);
	}

	template <typename T>
	Vector3<T> Vector3<T>::cross(const Vector3<T>& lhs, const Vector3<T>& rhs) const {
		const float cx = (lhs.y * rhs.z) - (lhs.z * rhs.y);
		const float cy = (lhs.z * rhs.x) - (lhs.x * rhs.z);
		const float cz = (lhs.x * rhs.y) - (lhs.y * rhs.x);

		return Vector3<T>(cx, cy, cz);
	}

	template <typename T>
	Vector3<T>& operator ++(Vector3<T>& vec) {
		vec.x++;
		vec.y++;
		vec.z++;

		return vec;
	}

	template <typename T>
	Vector3<T>& operator --(Vector3<T>& vec) {
		vec.x--;
		vec.y--;
		vec.z--;

		return vec;
	}

	template <typename T>
	bool operator ==(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return rhs.x == lhs.x && rhs.y == lhs.y && lhs.z == rhs.z;
	}

	template <typename T>
	bool operator !=(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator <(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
	}

	template <typename T>
	bool operator >(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z;
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& strm, const Vector3<T>& vec) {
		return strm << "Vector3<" << typeid(T).name() << ">(" << vec.x << ';' << vec.y << ';' << vec.z << ")";
	}

	// #1

	template <typename T>
	void operator +=(Vector3<T>& vec, T value) {
		vec.x += value;
		vec.y += value;
		vec.z += value;
	}

	template <typename T>
	void operator -=(Vector3<T>& vec, T value) {
		vec.x -= value;
		vec.y -= value;
		vec.z -= value;
	}

	template <typename T>
	void operator *=(Vector3<T>& vec, T value) {
		vec.x *= value;
		vec.y *= value;
		vec.z *= value;
	}

	template <typename T>
	void operator /=(Vector3<T>& vec, T value) {
		vec.x /= value;
		vec.y /= value;
		vec.z /= value;
	}

	// #2

	template <typename T>
	void operator +=(Vector3<T>& lhs, const Vector3<T>& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
	}

	template <typename T>
	void operator -=(Vector3<T>& lhs, const Vector3<T>& rhs) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
	}

	template <typename T>
	void operator *=(Vector3<T>& lhs, const Vector3<T>& rhs) {
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
	}

	template <typename T>
	void operator /=(Vector3<T>& lhs, const Vector3<T>& rhs) {
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
	}

	// #3

	template <typename T>
	Vector3<T> operator +(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	template <typename T>
	Vector3<T> operator -(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	template <typename T>
	Vector3<T> operator *(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	template <typename T>
	Vector3<T> operator /(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	using Vector3f = Vector3<float>;
	using Vector3s = Vector3<int16>;
	using Vector3i = Vector3<int>;
}

#endif