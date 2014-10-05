#ifndef SGL_VE3_HPP
#define SGL_VE3_HPP

#include <algorithm>
#include <SGL/Core/Types.hpp>
#include <SGL/Core/Traits.hpp>

namespace sgl {
    template <typename T>
    struct vec3 {
        T x = 0;
        T y = 0;
        T z = 0;

        vec3() = default;
        explicit vec3(T cx, T cy, T cz);

        template <typename U>
        vec3(const vec3<U>&);

        float length() const {
            return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
        }
    };

    #include <SGL/Math/vec3.inl>

    using vec3i = vec3<int32>;
    using vec3s = vec3<int16>;
    using vec3f = vec3<float>;
}

#endif
