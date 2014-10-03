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
        explicit Rect(T cx, T cy, T w, T h);

        template <typename U>
        explicit Rect(const Rect<U>&);

        vec2<T> getCenter() const;

        void move(T cx, T cy) {
            this->x += cx;
            this->y += cy;
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
    };

    #include <SGL/Math/Rect.inl>

    using IntRect   = Rect<int32>;
    using ShortRect = Rect<int16>;
    using FloatRect = Rect<float>;
}

#endif
