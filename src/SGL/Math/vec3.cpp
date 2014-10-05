#include <SGL/Math/vec3.hpp>
#include <SGL/Core/Traits.hpp>

namespace sgl {
    template <>
    bool operator ==(const vec3<float>& lhs, const vec3<float>& rhs) {
        return equal_floating_point(lhs.x, rhs.x) && equal_floating_point(lhs.y, rhs.y) && equal_floating_point(lhs.z, rhs.z);
    }

    template <>
    bool operator ==(const vec3<double>& lhs, const vec3<double>& rhs) {
        return equal_floating_point(lhs.x, rhs.x) && equal_floating_point(lhs.y, rhs.y) && equal_floating_point(lhs.z, rhs.z);
    }

    template <>
    bool operator ==(const vec3<long double>& lhs, const vec3<long double>& rhs) {
        return equal_floating_point(lhs.x, rhs.x) && equal_floating_point(lhs.y, rhs.y) && equal_floating_point(lhs.z, rhs.z);
    }
}
