#ifndef SGL_VEC2_HPP
#define SGL_VEC2_HPP

#include <algorithm>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Traits.hpp>

namespace sgl {
    template <typename T>
    struct vec2 {
        T x = 0;
        T y = 0;

        vec2() = default;
        explicit vec2(T cx, T cy);

        template <typename U>
        vec2(const vec2<U>&);

        float length() const {
            return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2));
        }
    };

    #include <SGL/Math/vec2.inl>

    using vec2i = vec2<int32>;
    using vec2s = vec2<int16>;
    using vec2f = vec2<float>;
}

#endif
