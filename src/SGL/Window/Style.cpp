#include <SGL/Window/Style.hpp>

namespace sgl {
    Style& operator |=(Style& lhs, Style rhs) {
        const int left  = static_cast<int>(lhs);
        const int right = static_cast<int>(rhs);

        lhs = static_cast<Style>(left | right);

        return lhs;
    }

    bool operator &(Style lhs, Style rhs) {
        const int left  = static_cast<int>(lhs);
        const int right = static_cast<int>(rhs);

        return (left & right) != 0;
    }
}
