#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <math.h>

namespace sgl {
	template<typename T>
	struct Vector2 {
		T x = 0;
		T y = 0;

		explicit Vector2();
		explicit Vector2(T px, T py);

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

		float angle(const Vector2<T>& vec, bool inDegrees = true) const;
		Vector2<T> normalized() const;

		/**
		* Calculate the diff between two vectors.
		*/
		float diff(const Vector2<T>& vec) const {
			return std::sqrtf(std::powf(this->x - vec.x, 2) + std:::powf(this->y - vec.y, 2));
		}

		float scalar(const Vector2<T>& lhs, const Vector2<T>& rhs) const {
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		float length() const {
			return std::sqrtf(std::powf(this->x, 2) * std::pow(this->y, 2));
		}
	};

	template <typename T>
	Vector2<T>::Vector2() : x(0), y(0) {

	}

	template <typename T>
	Vector2<T>::Vector2(T px, T py) : x(px), y(py) {

	}

	template <typename T>
	float Vector2<T>::angle(const Vector2<T>& vec, bool inDegrees = true) const {
		const float angle = std::acosf(this->scalar(vec) / (this->length() * vec.length()));
		if (inDegrees)
			return angle * 180 / PI;

		return angle;
	}

	/**
	* Normalize the vector in which the coordinates are divided by the length.
	*/
	template <typename T>
	Vector2<T> Vector2<T>::normalized() const {
		Vector2<T> result = *this;

		const float len = this->length();
		if (len > 0) {
			result.x /= len;
			result.y /= len;
		}

		return result;
	}

	template<typename T>
	bool operator ==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return rhs.x == lhs.x && rhs.y == lhs.y;
	}

	template<typename T>
	bool operator !=(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return !(lhs == rhs);
	}

	template<typename T>
	std::ostream& operator <<(std::ostream& strm, const Vector2<T>& vec) {
		return strm << "Vector2<" << typeid(T).name() << ">(" << vec.x << ';' << vec.y << ")";
	}

	// #1

	template<typename T>
	void operator +=(Vector2<T>& vec, T value) {
		vec.x += value;
		vec.y += value;
	}

	template<typename T>
	void operator -=(Vector2<T>& vec, T value) {
		vec.x -= value;
		vec.y -= value;
	}

	template<typename T>
	void operator *=(Vector2<T>& vec, T value) {
		vec.x *= value;
		vec.y *= value;
	}

	template<typename T>
	void operator /=(Vector2<T>& vec, T value) {
		vec.x /= value;
		vec.y /= value;
	}

	// #2

	template<typename T>
	void operator +=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x += rhs.x;
		lhs.y += rhs.y;
	}

	template<typename T>
	void operator -=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
	}

	template<typename T>
	void operator *=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
	}

	template<typename T>
	void operator /=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
	}

	// #3

	template<typename T>
	Vector2<T> operator +(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template<typename T>
	Vector2<T> operator -(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template<typename T>
	Vector2<T> operator *(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	template<typename T>
	Vector2<T> operator /(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	// #4

	template<typename T>
	Vector2<T> operator +(const Vector2<T>& vec, T value) {
		return Vector2f(vec.x + value, vec.y + value);
	}

	template<typename T>
	Vector2<T> operator -(const Vector2<T>& vec, T value) {
		return Vector2f(vec.x - value, vec.y - value);
	}

	template<typename T>
	Vector2<T> operator *(const Vector2<T>& vec, T value) {
		return Vector2f(vec.x * value, vec.y * value);
	}

	template<typename T>
	Vector2<T> operator /(const Vector2<T>& vec, T value) {
		return Vector2f(vec.x / value, vec.y / value);
	}

	using Vector2f = Vector2<float>;
	using Vector2s = Vector2<int16>;
	using Vector2us = Vector2<uint16>;
}

#endif