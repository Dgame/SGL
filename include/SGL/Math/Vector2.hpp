#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <typeinfo>
#include <cmath>
#include <SGL/Core/Types.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace sgl {
	template <typename T>
	struct Vector2 {
		T x = 0;
		T y = 0;

		Vector2() = default;
		explicit Vector2(T px, T py);

		template <typename U>
		explicit Vector2(const Vector2<U>& vec);

		void set(T x, T y) {
			this->x = x;
			this->y = y;
		}

		void move(T x, T y) {
			this->x += x;
			this->y += y;
		}

		float angle(const Vector2<T>& vec) const {
			return acosf(this->dot(vec) / (this->length() * vec.length()));
		}

		Vector2<T> rotate(float angle) const;
		Vector2<T> normalize() const;

		Vector2<T> abs() const {
			return Vector2<T>(std::abs(this->x), std::abs(this->y));
		}

		/**
		* Calculate the diff between two vectors.
		*/
		float diff(const Vector2<T>& vec) const;

		float dot(const Vector2<T>& vec) const {
			return this->x * vec.x + this->y * vec.y;
		}

		float length() const {
			return std::sqrt(std::pow(this->x, 2) * std::pow(this->y, 2));
		}
	};

	template <typename T>
	Vector2<T>::Vector2(T px, T py) : x(px), y(py) {

	}

	template <typename T>
	template <typename U>
	Vector2<T>::Vector2(const Vector2<U>& vec) : Vector2(static_cast<T>(vec.x), static_cast<T>(vec.y)) {

	}

	template <typename T>
	Vector2<T> Vector2<T>::rotate(float angle) const {
		const float radians = angle * M_PI / 180.f;
		const T nx = static_cast<T>(this->x * std::cos(radians) - this->y * std::sin(radians));
		const T ny = static_cast<T>(this->x * std::sin(radians) + this->y * std::cos(radians));

		return Vector2<T>(nx, ny);
	}

	/**
	* Normalize the vector in which the coordinates are divided by the length.
	*/
	template <typename T>
	Vector2<T> Vector2<T>::normalize() const {
		const float len = this->length();
		if (len > 0) {
			Vector2<T> result = *this;
			result.x /= len;
			result.y /= len;

			return result;
		}

		return *this;
	}

	/**
	* Calculate the diff between two vectors.
	*/
	template <typename T>
	float Vector2<T>::diff(const Vector2<T>& vec) const {
		const float vx = std::pow(this->x - vec.x, 2);
		const float vy = std::pow(this->y - vec.y, 2);

		return std::sqrt(vx + vy);
	}

	template <typename T>
	Vector2<T>& operator ++(Vector2<T>& vec) {
		vec.x++;
		vec.y++;

		return vec;
	}

	template <typename T>
	Vector2<T>& operator --(Vector2<T>& vec) {
		vec.x--;
		vec.y--;

		return vec;
	}

	template <typename T>
	bool operator ==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return rhs.x == lhs.x && rhs.y == lhs.y;
	}

	template <typename T>
	bool operator !=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	bool operator <(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return lhs.x < rhs.x && lhs.y < rhs.y;
	}

	template <typename T>
	bool operator >(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return lhs.x > rhs.x && lhs.y > rhs.y;
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& strm, const Vector2<T>& vec) {
		return strm << "Vector2<" << typeid(T).name() << ">(" << vec.x << ';' << vec.y << ")";
	}

	// #1

	template <typename T>
	void operator +=(Vector2<T>& vec, T value) {
		vec.x += value;
		vec.y += value;
	}

	template <typename T>
	void operator -=(Vector2<T>& vec, T value) {
		vec.x -= value;
		vec.y -= value;
	}

	template <typename T>
	void operator *=(Vector2<T>& vec, T value) {
		vec.x *= value;
		vec.y *= value;
	}

	template <typename T>
	void operator /=(Vector2<T>& vec, T value) {
		vec.x /= value;
		vec.y /= value;
	}

	// #2

	template <typename T>
	void operator +=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
	}

	template <typename T>
	void operator -=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
	}

	template <typename T>
	void operator *=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
	}

	template <typename T>
	void operator /=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
	}

	// #3

	template <typename T>
	Vector2<T> operator +(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template <typename T>
	Vector2<T> operator -(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template <typename T>
	Vector2<T> operator *(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	template <typename T>
	Vector2<T> operator /(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	using Vector2f = Vector2<float>;
	using Vector2s = Vector2<int16>;
	using Vector2i = Vector2<int>;
}

#endif