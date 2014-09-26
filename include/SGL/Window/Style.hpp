#ifndef SGL_WINDOW_STYLE_HPP
#define SGL_WINDOW_STYLE_HPP

#include <SGL/Core/SDL.hpp>

namespace sgl {
    enum class Style {
        Fullscreen = SDL_WINDOW_FULLSCREEN,
        Desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
        Shown = SDL_WINDOW_SHOWN,
        Hidden = SDL_WINDOW_HIDDEN,
        Borderless = SDL_WINDOW_BORDERLESS,
        Resizeable = SDL_WINDOW_RESIZABLE,
        Minimized = SDL_WINDOW_MINIMIZED,
        Maximized = SDL_WINDOW_MAXIMIZED,
        Focus = SDL_WINDOW_INPUT_GRABBED,
        InputFocus = SDL_WINDOW_INPUT_FOCUS,
        MouseFocus = SDL_WINDOW_MOUSE_FOCUS,
        HighDPI = SDL_WINDOW_ALLOW_HIGHDPI,

        Windowed = ~(SDL_WINDOW_FULLSCREEN | SDL_WINDOW_FULLSCREEN_DESKTOP),

        Default = Shown | HighDPI
    };

    Style& operator |=(Style&, Style rhs);
    bool operator &(Style lhs, Style rhs);

    Style& operator |=(Style&, int right);
    bool operator &(Style lhs, int right);
}

#endif // SGL_WINDOW_STYLE_HPP
