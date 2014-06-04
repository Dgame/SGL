#ifndef RECT_HPP
#define RECT_HPP

#include <SDL.h>
#include <typeinfo>
#include <SGL/Math/Vector2.hpp>

namespace sgl {
	template <typename T>
	struct Rect {
		T x = 0;
		T y = 0;
		T width = 0;
		T height = 0;

		Rect() = default;
		explicit Rect(T px, T py, T pw, T ph);
		explicit Rect(const Vector2s& vec, T pw, T ph);

		static SDL_Rect* Copy(const Rect<T>* from, SDL_Rect& too);

		bool isEmpty() const;
		Rect<T> getUnion(const Rect<T>& rect) const;

		/**
		* Checks whether this Rect contains the given coordinates.
		*/
		bool contains(T x, T y) const {
			return (x >= this->x)
				&& (x <= this->x + this->width)
				&& (y >= this->y)
				&& (y <= this->y + this->height);
		}

		bool contains(const Vector2<T>& vec) const {
			return this->contains(vec.x, vec.y);
		}

		bool intersects(const Rect<T>& rect, Rect<T>* overlap = nullptr) const;

		void setSize(T width, T height) {
			this->width = width;
			this->height = height;
		}

		/**
		* Increase current size.
		*/
		void increase(T width, T height) {
			this->width += width;
			this->height += height;
		}

		/**
		* Move the object.
		*/
		void move(T x, T y) {
			this->x += x;
			this->y += y;
		}

		void setPosition(T x, T y) {
			this->x = x;
			this->y = y;
		}

		Vector2s getPosition() const {
			return Vector2s(x, y);
		}
	};

	template <typename T>
	Rect<T>::Rect(T px, T py, T pw, T ph) : x(px), y(py), width(pw), height(ph) {

	}

	template <typename T>
	Rect<T>::Rect(const Vector2s& vec, T pw, T ph) : Rect(vec.x, vec.y, pw, ph) {

	}

	template <typename T>
	SDL_Rect* Rect<T>::Copy(const Rect<T>* from, SDL_Rect& too) {
		if (!from)
			return nullptr;
		else {
			too.x = from->x;
			too.y = from->y;
			too.w = from->width;
			too.h = from->height;
		}

		return &too;
	}

	template <typename T>
	bool Rect<T>::isEmpty() const {
		SDL_Rect a;
		Rect<T>::Copy(this, &a);

		return SDL_RectEmpty(&a) == SDL_TRUE;
	}

	template <typename T>
	Rect<T> Rect<T>::getUnion(const Rect<T>& rect) const {
		SDL_Rect a;
		SDL_Rect b;
		SDL_Rect c;

		Rect<T>::Copy(this, a);
		Rect<T>::Copy(&rect, b);

		SDL_UnionRect(&a, &b, &c);

		return Rect<T>(c.x, c.y, c.w, c.h);
	}

	template <typename T>
	bool Rect<T>::intersects(const Rect<T>& rect, Rect<T>* overlap) const {
		SDL_Rect a;
		SDL_Rect b;

		Rect<T>::Copy(this, a);
		Rect<T>::Copy(&rect, b);

		if (overlap == nullptr)
			return SDL_HasIntersection(&a, &b) == SDL_TRUE;

		SDL_Rect c;
		const bool intersects = SDL_IntersectRect(&a, &b, &c) == SDL_TRUE;

		overlap->setPosition(c.x, c.y);
		overlap->setSize(c.w, c.h);

		return intersects;
	}

	template <typename T>
	bool operator ==(const Rect<T>& lhs, const Rect<T>& rhs) {
		SDL_Rect a;
		SDL_Rect b;

		Rect<T>::Copy(&lhs, a);
		Rect<T>::Copy(&rhs, b);

		return SDL_RectEquals(&a, &b);
	}

	template <typename T>
	bool operator !=(const Rect<T>& lhs, const Rect<T>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& strm, const Rect<T>& rect) {
		return strm << "Rect<" << typeid(T).name() << ">(" << rect.x << ',' << rect.y << ',' << rect.width, ',' << rect.height << ")";
	}

	using FloatRect = Rect<float>;
	using ShortRect = Rect<int16>;
	using IntRect = Rect<int>;
}

#endif