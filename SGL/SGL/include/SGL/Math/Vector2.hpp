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

		Vector2();
		explicit Vector2(T px, T py);
		template <typename U>
		explicit Vector2(const Vector2<U>& vec);

		bool isZero() const {
			return this->x == 0 && this->y == 0;
		}

		void set(T x, T y) {
			this->x = x;
			this->y = y;
		}

		void move(T x, T y) {
			this->x += x;
			this->y += y;
		}

		float angleBetween(const Vector2<T>& vec, bool inDegrees = true) const;
		Vector2<T> rotate(float angle) const;
		Vector2<T> normalize() const;

		/**
		* Calculate the diff between two vectors.
		*/
		float diff(const Vector2<T>& vec) const {
			return sqrtf(powf(this->x - vec.x, 2) + powf(this->y - vec.y, 2));
		}

		float scalar(const Vector2<T>& lhs, const Vector2<T>& rhs) const {
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		float length() const {
			return sqrtf(powf(this->x, 2) * pow(this->y, 2));
		}
	};

	template <typename T>
	Vector2<T>::Vector2() : x(0), y(0) {

	}

	template <typename T>
	Vector2<T>::Vector2(T px, T py) : x(px), y(py) {

	}

	template <typename T>
	template <typename U>
	Vector2<T>::Vector2(const Vector2<U>& vec) : Vector2(static_cast<T>(vec.x), static_cast<T>(vec.y)) {

	}

	template <typename T>
	float Vector2<T>::angleBetween(const Vector2<T>& vec, bool inDegrees) const {
		const float angle = acosf(this->scalar(vec) / (this->length() * vec.length()));
		if (inDegrees)
			return angle * 180 / M_PI;

		return angle;
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
		Vector2<T> result = *this;

		const float len = this->length();
		if (len > 0) {
			result.x /= len;
			result.y /= len;
		}

		return result;
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
	using Vector2us = Vector2<uint16>;
}

#endif