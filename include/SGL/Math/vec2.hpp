#ifndef SGL_VEC2_HPP
#define SGL_VEC2_HPP

#include <algorithm>
#include <SGL/Core/Types.hpp>

namespace sgl {
    template <typename T>
    struct vec2 {
        T x = 0;
        T y = 0;

        vec2() = default;
        explicit vec2(T mx, T my);

        template <typename U>
        vec2(const vec2<U>&);

        float length() const {
            return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
        }
    };

    using vec2i = vec2<int32>;
    using vec2s = vec2<int16>;
    using vec2f = vec2<float>;

    template <typename T>
    vec2<T>::vec2(T mx, T my) : x(mx), y(my) {

    }

    template <typename T>
    template <typename U>
    vec2<T>::vec2(const vec2<U>& vec) :
        x(static_cast<T>(vec.x)),
        y(static_cast<T>(vec.y))
    {

    }

    template <typename T>
    vec2<T> Rotate(const vec2<T>& vec, float angle) {
        static const double PI = 3.14159265358979;

        const float radians = angle * PI / 180.f;
        const T nx = vec.x * std::cos(radians) - vec.y * std::sin(radians);
        const T ny = vec.x * std::sin(radians) + vec.y * std::cos(radians);

        return vec2<T>(nx, ny);
    }

    template <typename T>
    vec2<T> Normalize(const vec2<T>& vec) {
        const float len = vec.length();
        if (len > 0)
            return vec / len;
        return vec;
    }

    template <typename T>
    float Dot(const vec2<T>& lhs, const vec2<T>& rhs) {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    template <typename T>
    float Angle(const vec2<T>& lhs, const vec2<T>& rhs) {
        return acosf(Dot(lhs, rhs) / (lhs.length() * rhs.length()));
    }

    template <typename T>
    float Diff(const vec2<T>& lhs, const vec2<T>& rhs) {
        const float vx = std::pow(lhs.x - rhs.x, 2);
        const float vy = std::pow(lhs.y - rhs.y, 2);

        return std::sqrt(vx + vy);
    }

    template <typename T>
    vec2<T>& operator +=(vec2<T>& lhs, const vec2<T>& rhs) {
        lhs.x += rhs.x;
        lhs.y += rhs.y;

        return lhs;
    }

    template <typename T>
    vec2<T>& operator -=(vec2<T>& lhs, const vec2<T>& rhs) {
        lhs.x -= rhs.x;
        lhs.y -= rhs.y;

        return lhs;
    }

    template <typename T>
    vec2<T> operator +(const vec2<T>& lhs, const vec2<T>& rhs) {
        return vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    template <typename T>
    vec2<T> operator -(const vec2<T>& lhs, const vec2<T>& rhs) {
        return vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    template <typename T>
    vec2<T> operator -(const vec2<T>& lhs) {
        return vec2<T>(-lhs.x, -lhs.y);
    }

    template <typename T>
    vec2<T> operator *(const vec2<T>& lhs, T num) {
        return vec2<T>(lhs.x * num, lhs.y * num);
    }

    template <typename T>
    vec2<T>& operator *=(vec2<T>& lhs, T num) {
        lhs.x *= num;
        lhs.y *= num;

        return lhs;
    }

    template <typename T>
    vec2<T> operator /(const vec2<T>& lhs, T num) {
        return vec2<T>(lhs.x / num, lhs.y / num);
    }

    template <typename T>
    vec2<T>& operator /=(vec2<T>& lhs, T num) {
        lhs.x /= num;
        lhs.y /= num;

        return lhs;
    }

    template <typename T>
    bool operator ==(const vec2<T>& lhs, const vec2<T>& rhs) {
        return lhs.x == rhs.x && lhs.y = rhs.y;
    }

    template <typename T>
    bool operator !=(const vec2<T>& lhs, const vec2<T>& rhs) {
        return !(lhs == rhs);
    }
}

#endif
