#include <SGL/Math/vec2.hpp>
#include <SGL/Core/Traits.hpp>

namespace sgl {
    template <>
    bool operator ==(const vec2<float>& lhs, const vec2<float>& rhs) {
        return equal_floating_point(lhs.x, rhs.x) && equal_floating_point(lhs.y, rhs.y);
    }

    template <>
    bool operator ==(const vec2<double>& lhs, const vec2<double>& rhs) {
        return equal_floating_point(lhs.x, rhs.x) && equal_floating_point(lhs.y, rhs.y);
    }

    template <>
    bool operator ==(const vec2<long double>& lhs, const vec2<long double>& rhs) {
        return equal_floating_point(lhs.x, rhs.x) && equal_floating_point(lhs.y, rhs.y);
    }
}
