#ifndef SGL_SDL_IMAGE_HPP
#define SGL_SDL_IMAGE_HPP

#include <SGL/Core/Config.hpp>

#if defined(SGL_OS_WIN64) && SGL_USE_X64
    #include "../libs/64/SDL2/SDL_image.h"
#else
    #include "../libs/32/SDL2/SDL_image.h"
#endif

#endif
