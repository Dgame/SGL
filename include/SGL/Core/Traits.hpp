#ifndef SGL_TRAITS_HPP
#define SGL_TRAITS_HPP

#include <limits>
#include <type_traits>

template <typename T>
inline bool equal_floating_point(T lhs, T rhs) {
    static_assert(std::is_floating_point<T>::value, "That is not a floating point");
    return (lhs - rhs) < std::numeric_limits<T>::epsilon();
}

#endif // SGL_TRAITS_HPP
