#ifndef SGL_SDL_HPP
#define SGL_SDL_HPP

#include <SGL/Core/Config.hpp>

#if defined(SGL_OS_WIN64) && SGL_USE_X64 == 1
    #include "../libs/64/SDL2/SDL.h"
    #include "../libs/64/SDL2/SDL_image.h"
    #include "../libs/64/SDL2/SDL_mixer.h"
    #include "../libs/64/SDL2/SDL_ttf.h"
#else
    #include "../libs/32/SDL2/SDL.h"
    #include "../libs/32/SDL2/SDL_image.h"
    #include "../libs/32/SDL2/SDL_mixer.h"
    #include "../libs/32/SDL2/SDL_ttf.h"
#endif

#undef main

#endif
