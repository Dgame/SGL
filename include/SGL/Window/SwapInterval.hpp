#ifndef SGL_WINDOW_SWAP_INTERVAL_HPP
#define SGL_WINDOW_SWAP_INTERVAL_HPP

namespace sgl {
    enum class SwapInterval : char {
        Immediate = 0,
        Synchronize = 1,
        LateSwapTearing = -1
    };
}

#endif // SGL_WINDOW_SWAP_INTERVAL_HPP
