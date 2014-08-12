#ifndef SGL_RECT_HPP
#define SGL_RECT_HPP

#include <SGL/Core/SDL.hpp>
#include <SGL/Core/Types.hpp>
#include <SGL/Math/vec2.hpp>

namespace sgl {
	template <typename T>
	struct Rect {
		T x = 0;
		T y = 0;
		T width = 0;
		T height = 0;

		Rect() = default;
		explicit Rect(T mx, T my, T w, T h);

		template <typename U>
		explicit Rect(const Rect<U>& rect);

		vec2<T> getCenter() const;

		void move(T x, T y) {
			this->x += x;
			this->y += y;
		}

		void move(const vec2<T>& vec) {
			this->move(vec.x, vec.y);
		}

		void increase(T w, T h) {
			this->width += w;
			this->height += h;
		}

		bool isEmpty() const;
		bool contains(T x, T y) const;
		bool contains(const vec2<T>&) const;
		bool intersects(const Rect<T>&, Rect<T>* intersection = nullptr) const;

		SDL_Rect* copyTo(SDL_Rect*) const;
		void copyFrom(const SDL_Rect*);
	};

	template <typename T>
	Rect<T>::Rect(T mx, T my, T w, T h) : x(my), y(my), width(w), height(h) {

	}

	template <typename T>
	template <typename U>
	Rect<T>::Rect(const Rect<U>& rect) : 
		x(static_cast<T>(rect.x)),
		y(static_cast<T>(rect.y)),
		width(static_cast<T>(rect.width)),
		height(static_cast<T>(rect.height))
	{

	}

	template <typename T>
	vec2<T> Rect<T>::getCenter() const {
		return vec2<T>(this->x + this->width / 2, this->y + this->height / 2);
	}

	template <typename T>
	bool Rect<T>::isEmpty() const {
		SDL_Rect a;

		return SDL_RectEmpty(this->copyTo(&a));
	}

	template <typename T>
	bool Rect<T>::contains(T x, T y) const {
		SDL_Rect a;
		SDL_Point point(x, y);

		return SDL_PointInRect(&point, this->copyTo(&a));
	}

	template <typename T>
	bool Rect<T>::contains(const vec2<T>& vec) const {
		SDL_Rect a;
		SDL_Point point;

		return SDL_PointInRect(vec->copyTo(&point), this->copyTo(&a));
	}

	template <typename T>
	bool Rect<T>::intersects(const Rect<T>& other, Rect<T>* intersection) const {
		SDL_Rect a, b;

		if (intersection != nullptr) {
			SDL_Rect c;

			const bool result = SDL_IntersectRect(this->copyTo(&a), other->copyTo(&b), &c);
			intersection->copyFrom(&c);

			return result;
		}

		return SDL_HasIntersection(this->copyTo(&a), other->copyTo(&b));
	}

	template <typename T>
	SDL_Rect* Rect<T>::copyTo(SDL_Rect* dst) const {
		if (dst != nullptr) {
			dst->x = static_cast<int>(this->x);
			dst->y = static_cast<int>(this->y);
			dst->w = static_cast<int>(this->width);
			dst->h = static_cast<int>(this->height);
		}
		
		return dst;
	}

	template <typename T>
	void Rect<T>::copyFrom(const SDL_Rect* src) {
		if (src != nullptr) {
			this->x = static_cast<T>(src->x);
			this->y = static_cast<T>(src->y);
			this->width  = static_cast<T>(src->w);
			this->height = static_cast<T>(src->h);
		}
	}

	template <typename T>
	bool operator ==(const Rect<T>& lhs, const Rect<T>& rhs) {
		SDL_Rect a, b;

		return SDL_RectEquals(lhs->copyTo(&a), rhs->copyTo(&b));
	}

	template <typename T>
	bool operator !=(const Rect<T>& lhs, const Rect<T>& rhs) {
		return !(lhs == rhs);
	}

	using IntRect   = Rect<int32>;
	using ShortRect = Rect<int16>;
	using FloatRect = Rect<float>;
}

#endif